//
//  Annealing.hpp
//  PEA2
//
//  Created by Oliwier Salamon on 12.12.2018.
//  Copyright © 2018 Oliwier Salamon. All rights reserved.
//

#ifndef Annealing_hpp
#define Annealing_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;

class Annealing {
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
    
    // droga miedzy miastami - stosy wierzcholkow
    int *finalPath, *tempPath;
    
    
    
    
public:
    
    void tsp(double temperatureMax, double temperatureMin);
    // wczytanie z pliku macierzy o podanej nazwie pliku
    bool initializeMatrix(string filename);
    ~Annealing();
    
    // poczatkowa metoda startujaca poszukiwania
    bool startProgram(int initialC);
    
    // display results
    void displaySolution(int* finalPath, int numberOfCities, int minWeight);
    
    int* setFinalPath();
    int* generateRandomSwap(int *path);
    int calculateCost(int **Weight, int *tempPath, int numberOfCities);
    double generateProbaility(int temperature, int* pathA, int* pathB);
    
    
    
};

#endif
