//
//  Graph.hpp
//  PEA3
//
//  Created by Oliwier Salamon on 16.01.2019.
//  Copyright © 2019 Oliwier Salamon. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;

class Graph {
private:
    // ilosc miast
    int numberOfCities;
    
    //indeks wagi sciezki
    int weightIndex;
    
    int numberOfPopulation;
    
    int numberOfIterations;
    
    int numberOfCrossing;
    
    int numberOfMutations;
    
    int currentSizeOfPopulation;
    
    // mierzenie czasu
    double time;
    
    // nazwa pliku
    string fileN;
    
    // macierz wag pomiedzy miastami
    int **Weight;
            
    //
    int **population;
    
    
public:
    // rozpoczenie algorytmu
    int tsp();
    
    //
    void generateRandomPopulation();
    
    int calculatePathCost(int *path);
    
    void displayPopulation();
    
    int **crossingOperation(int** array);
    
    int **copyPopulation(int **array,int limitY, int limitX);
    
    void populationMutation();
    
    void sortPopulation(int x);
    
    
    // wczytanie z pliku macierzy o podanej nazwie pliku
    bool initializeMatrix(string filename);
    
    
    //destruktor
    ~Graph();
    
};

#endif
