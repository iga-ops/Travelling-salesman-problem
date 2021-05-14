//
// Created by igach on 13.11.2019.
//

#ifndef SALESMAN_TSP_HPP
#define SALESMAN_TSP_HPP

#include <vector>
#include <cmath>
#include <iostream>
using dmacierz = std::vector<std::vector<double>>;
using vint = std::vector<int>;
std::vector<int> tsp(std::vector<std::vector<double>> cost_matrix);

double get_forbidden_cost();

class TSP{
public:
    TSP(const dmacierz & Wejsciowa);
    void pion(); // będę najpierw znajdowac te min, a potem od razu odejme
    void poziom();
    std::vector<int>  Salesman();
    void wypisz_macierz();
    std::vector<std::pair<int,int>> szuk_Zer() const; // tutaj od razu będzie mi szukać max
    double sum_Min(const std::pair<int,int> &para)const ; // tutaj bede krzyzowo
    void szuk_Max(); // będzie mial w sobie i,j dla którego max
    void zmniejsz_m(const std::pair<int, int>& maxpara); //dostaję parę z max sumą i robię odejmowanko wiersza i kolumny= zamienie sb na inf
    void sort();
private:
    dmacierz Matrix;
    double LB;
    int msize;
    int msize_reduk;
    std::vector<std::pair<int,int>> droga;
    std::vector<int> droga_posort;
    double INF;
};





#endif //SALESMAN_TSP_HPP

