//
//  Graph.hpp
//  PEA1
//
//  Created by Oliwier Salamon on 15.11.2018.
//  Copyright © 2018 Oliwier Salamon. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

class Graph {
private:
    // ilosc miast
    int numberOfCities;
    
    //miasto startowe
    int initialCity;
    
    // waga rozwiazania problemu
    int minWeight, currWeight;
    
    // ilosc rekurencji
    int iteration;
    
    // liczniki
    int counter, currCounter;
    
    // mierzenie czasu
    double time;
    
    // nazwa pliku
    string fileN;
    
    // macierz wag pomiedzy miastami
    int **Weight;
    
    // tablica miast odwiedzonych
    bool *visitedCities;
    
    
    // droga miedzy miastami - stosy wierzcholkow
    int *finalPath, *tempPath;
    
    void tsp(int city);
    
    
public:
    // wczytanie z pliku macierzy o podanej nazwie pliku
    bool initializeMatrix(string filename);
    ~Graph();
    
    // poczatkowa metoda startujaca poszukiwania
    bool startProgram(int initialC);
    
    // display results
    void displaySolution();
    
    
    
    
};

#endif /* Graph_hpp */
