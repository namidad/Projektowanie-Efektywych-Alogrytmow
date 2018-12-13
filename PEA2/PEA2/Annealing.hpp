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
    
    // waga rozwiazania problemu
    int minWeight;
    
    // mierzenie czasu
    double time;
    
    // nazwa pliku
    string fileN;
    
    // macierz wag pomiedzy miastami
    int **Weight;
    
    // droga miedzy miastami
    int *finalPath, *tempPath;

    
    
public:
    // rozpoczenie algorytmu
    void tsp(double temperatureMax, double temperatureMin);
    
    // wczytanie z pliku macierzy o podanej nazwie pliku
    bool initializeMatrix(string filename);
    
    // wyswietl rozwiazanie
    void displaySolution(int* finalPath, int numberOfCities, int minWeight);
    
    // ustaw nowa sciezke pod zmienna koncowa
    int* setFinalPath();
    
    // wygeneruj losowa zmiane miast
    int* generateRandomSwap(int *path);
    
    // policz koszt podrozy pomiedzy miastami
    int calculateCost(int **Weight, int *tempPath, int numberOfCities);
    
    // policz prawdopodobienstwo zaakceptowania nowego rozwiazania
    double generateProbaility(int temperature, int* pathA, int* pathB);
    
    //destruktor
    ~Annealing();
    
};

#endif
