//
// Created by igach on 13.11.2019.
//

#include "tsp.hpp"
double get_forbidden_cost(){
    return (NAN);
}
std::vector<int> tsp(std::vector<std::vector<double>> cost_matrix){
    TSP m(cost_matrix);
    return m.Salesman();
}

void TSP::wypisz_macierz(){
    for(auto el1:Matrix)
    {
        for(auto el2:el1)
        {
            std::cout<<el2<<" ";
        }
        std::cout<<std::endl;
    }
}
TSP::TSP(const dmacierz &Wejsciowa):Matrix(Wejsciowa){
    msize=Wejsciowa.size(); //zwraca ilosc wierszy- czyli tez il kolumn u nas
    LB=0;
    INF = get_forbidden_cost();
    msize_reduk=msize;
}
std::vector<std::pair<int,int>> TSP::szuk_Zer() const{ // ta funkcja zwraca mi pary, gdzie jest 0

    std::vector<std::pair<int,int>> vector;
    for(int i = 0;i< msize; i++)
    {
        for(int j = 0; j<msize; j++)
        {
            if (Matrix[i][j] == 0)
                vector.push_back(std::pair<int,int>(i,j));
        }
    }
    return vector;
    }
void TSP::pion()
{
    for(int i = 0; i<msize; i++)
    {
        double min_1 = Matrix[i][0];
        for(int j = 1; j<msize; j++)
        {
            if (min_1>Matrix[i][j]||std::isnan(min_1))  // macierz i wierszy na j kolumn
            {
                min_1 = Matrix[i][j];
            }
        }
        for(int j = 0; j<msize; j++)
        {
            Matrix[i][j] = Matrix[i][j] - min_1;
        }
    }
}
void TSP::poziom()
{
    for(int i = 0; i<msize; i++)
    {
        double min_2 = Matrix[0][i];
        for(int j = 0; j<msize; j++)
        {
            if (min_2>Matrix[j][i]||std::isnan(min_2))
            {
                min_2 = Matrix[j][i];
            }
        }
        for(int j = 0; j<msize; j++)
        {
            Matrix[j][i] = Matrix[j][i] - min_2;
        }
    }
}
double TSP::sum_Min(const std::pair<int, int> &para) const {
    double min1=INF;
    double min2=INF;
    for(int i=0;i<msize;i++)
    {
        if(i!=para.second)
            if(min1>Matrix[para.first][i]||std::isnan(min1))
                min1=Matrix[para.first][i];
    }
    for(int i=0;i<msize;i++)
    {
        if(i!=para.first)
            if(min2>Matrix[i][para.second]||std::isnan(min2))
                min2=Matrix[i][para.second];
    }
    return min1+min2;
}
void TSP::zmniejsz_m(const std::pair<int, int> &maxpara) {
    for(int i=0;i<msize;i++)
    {
        Matrix[maxpara.first][i]=INF;
    }
    for(int i=0;i<msize;i++)
    {
        Matrix[i][maxpara.second]=INF;
    }
    Matrix[maxpara.second][maxpara.first]=INF;
    msize_reduk-=1;
}
void TSP::szuk_Max(){
    std::vector<std::pair<int,int>> pary_zer;
    pary_zer=TSP::szuk_Zer();
    std::pair<int,int> para_maks=pary_zer[0];
    for(auto element:pary_zer)
    {
        if(TSP::sum_Min(element)>sum_Min(para_maks))
        {
            para_maks=element;
        }
    }
    droga.push_back(para_maks);
    TSP::zmniejsz_m(para_maks);
}
std::vector<int>  TSP::Salesman(){
    while(msize_reduk>2)
    {
        pion();
        poziom();
        szuk_Max();
    }
    pion();
    poziom();
    std::vector<std::pair<int,int>> pary_zer=TSP::szuk_Zer();
    for(auto element:pary_zer)
    {
        if(std::isnan(sum_Min(element)))
        {
            droga.push_back(element);
        }
    }
    sort();
    return droga_posort;
}
void TSP::sort(){
    int tmp;
    droga_posort.push_back(droga[0].first+1);
    tmp=droga[0].second;
    do
    {
        for(size_t i=0;i<droga.size();i++)
        {
            if(droga[i].first==tmp){
                tmp=droga[i].second;
                droga_posort.push_back(droga[i].first+1);
                if(droga_posort[0]==droga_posort[droga_posort.size()-1])break;
            }
        }

    }while(droga_posort[0]!=droga_posort[droga_posort.size()-1]);
}

