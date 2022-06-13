#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

class punkty
{
public:
    long long int x;
    long long int y;
    punkty(long long int nx, long long int ny)
    {
        x = nx;
        y = ny;
    }
};
//dodaje punkty
void punk(int ild, vector<punkty>& pkt)
{
    int x, y;
    for (int i = 0; i < ild; i++)
    {
        cin >> x >> y;
        pkt.push_back(punkty(x, y));
    }
}
//znajduje najmniejszy y
int najy(int ild, vector<punkty>& pkt)
{
    int najin = 0;
    long long int naj = pkt[0].y;
    for (int i = 1; i < ild; i++)
    {
        if (pkt[i].y < naj)
        {
            najin = i;
            naj = pkt[i].y;
        }
        if (pkt[i].y == naj && pkt[i].x < pkt[najin].x)
        {
            najin = i;
        }
    }
    return najin;
}

double angle(punkty o, punkty a)
{
    if ((a.x == 0 && o.x == 0))
    {
        return 0;
    }
    else{
        double t = tan((double)(a.y - o.y) / (double)(a.x - o.x));
        return t;
        }
    
}
double dystans(punkty a, punkty b)
{
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}
//ustawia punkt z najmniejszym indeksem na 0
void zamien(vector<punkty>& pkt, int najin)
{
    punkty tym = pkt[0];
    pkt[0] = pkt[najin];
    pkt[najin] = tym;

}
//ustawia najnizej polozony punkt jako poczatek ukladu wspolrzednych
void przes(int ild, vector<punkty>& pkt, vector<punkty> pktD)
{
    long long int mx, my;
    mx = pktD[0].x;
    my = pktD[0].y;
    for (int i = 0; i < ild; i++)
    {

        pkt[i].x -= mx;
        pkt[i].y -= my;

    }
}
long long int operator^(punkty a, punkty b)
{
    return a.x * b.y - a.y * b.x;
}

bool operator<(punkty a, punkty b)
{
    if (a.y == 0 && a.x > 0)
        return true;
    if (b.y == 0 && b.x > 0)
        return false;
    if (a.y > 0 && b.y < 0)
        return true;
    if (a.y < 0 && b.y>0)
        return false;
    return (a ^ b) > 0;
}
//wyznacza kierunek -1 prawo 1 lewo
int kierunek(punkty a, punkty b, punkty c)
{
    long long int dir = ((b.x - a.x) * (c.y - a.y)) - ((b.y - a.y) * (c.x - a.x));
    if (dir > 0)
        return -1;
    else if (0>dir)
        return 1;
    return 0;
}
//usuwa punkty z takim samym katem
void usun(vector<punkty>& pktD)
{

    for (size_t i = 1; i < pktD.size() - 1; i++)
    {
        if (angle(pktD[0], pktD[i]) == angle(pktD[0], pktD[i + 1]))
        {
            if (dystans(pktD[0], pktD[i]) >= dystans(pktD[0], pktD[i + 1]))
            {
                pktD.erase(pktD.begin() + i + 1);
                i--;
            }
            else
            {
                pktD.erase(pktD.begin() + i);
                i--;
            }

        }
    }
}

//heapsort
void sortowanie(vector<punkty>& pkt)
{
    punkty tym(0, 0);
    int j = 0;
    int rozmiar = pkt.size();
    while (rozmiar > 0)
    {
        while (j < rozmiar)
        {
            for (int i = j; i != 0; i = (i - 1) / 2)
            {
                if (pkt[(i - 1) / 2] < pkt[i])
                {
                    tym = pkt[i];
                    pkt[i] = pkt[(i - 1) / 2];
                    pkt[(i - 1) / 2] = tym;
                }
                else break;
            }
            j++;
        }
        j = 0;
        tym = pkt[0];
        pkt[0] = pkt[rozmiar - 1];
        pkt[rozmiar - 1] = tym;
        rozmiar--;
    }
   
}
//usuwanie punktow nie nalezacych do otoczki
void otoczka(vector<punkty>& pkt, int indO, int &indS)
{
    
    if (kierunek(pkt[indS+1], pkt[indS+2], pkt[indS+3]) != -1)
    {
        pkt.erase(pkt.begin() + indS+2);
        if (indO != indS)
        {
            indS--;
        }
        otoczka(pkt, indO, indS);
    }
    
}
int main()
{
    //lista duzych punktow
    vector<punkty> pktD;
    vector<punkty> pktM;
    //liczba duzych punktow
    int ild;
    bool ch = false;
    //liczba malych punktow
    int ilm;
    //indeks punktu ktory ma najmniejszy y
    int najin;
    cin >> ild;
    punk(ild, pktD);
    cin >> ilm;
    punk(ilm, pktM);
    najin = najy(ild, pktD);
   zamien(pktD, najin);
  // cout << "\nnajnizszy punkt: " << pktD[0].x << " " << pktD[0].y << endl;
   przes(ilm, pktM, pktD);
   przes(ild, pktD, pktD);
   sortowanie(pktD);
   punkty tym = pktD.back();
   pktD.pop_back();
   pktD.insert(pktD.begin(), tym);
   /* for (int i = 0; i < ild; i++)
    {
        cout << pktD[i].x << " " << pktD[i].y;
        cout << endl;
    }*/
    usun(pktD);
    
    //for (size_t i = 0; i < pktD.size(); i++)
    //{
    //    cout << /*angle(pktD[0],pktD[i])<<" "<<*/pktD[i].x << " " << pktD[i].y;
    //    cout << endl;
    //}
    size_t indP = 0;
    int indS = 0;
     while(indP<pktD.size()-3)
    {
         otoczka(pktD, 0, indS);
         indS++;
         indP = indS;
    }
     pktD.push_back(pktD[0]);
     //cout << "\n wyniki: " << endl;
     //for (size_t i = 0; i < pktD.size(); i++)
     //{
     //    cout << /*angle(pktD[0],pktD[i])<<" "<<*/pktD[i].x << " " << pktD[i].y;
     //    cout << endl;
     //}

     //cout << "\nSzukane: " << endl;
     //for (size_t i = 0; i < pktM.size(); i++)
     //{
     //    cout << /*angle(pktD[0],pktD[i])<<" "<<*/pktM[i].x << " " << pktM[i].y;
     //    cout << endl;
     //}
     for (size_t i = 0; i < pktD.size()-1; i++)
     {
         for (size_t j = 0; j < pktM.size(); j++)
         {
             if (kierunek(pktD[i], pktM[j], pktD[i + 1]) ==-1) //dziala(?)
             {
                 pktM.erase(pktM.begin() + j);
             }
         }
     }

     cout <<pktM.size();

}




//bubble sort
//void sortowanie(vector <punkty>& pkt)
//{
//    punkty tym(0, 0);
//    for (size_t j = 0; j < pkt.size(); j++)
//    {
//        for (size_t i = 2; i < pkt.size() - j; i++)
//        {
//            if (pkt[i] < pkt[i - 1])
//            {
//                tym = pkt[i];
//                pkt[i] = pkt[i - 1];
//                pkt[i - 1] = tym;
//            }
//        }
//    }
//}