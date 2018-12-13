//
//  Annealing.cpp
//  PEA2
//
//  Created by Oliwier Salamon on 12.12.2018.
//  Copyright © 2018 Oliwier Salamon. All rights reserved.
//

#include "Annealing.hpp"


bool Annealing::initializeMatrix (string filename){
    
    ifstream file;
    fileN=filename;
    file.open(filename.c_str());
    if(!file.good()){
        cout<<endl<<"Zly plik."<<endl;
        return false;
    } else {
        int word, weight;
        file>>word;
        numberOfCities=word;
        int n=numberOfCities;
        Weight = new int *[n];
        
        for(int i=0;i<n;i++){
            Weight[i]=new int[n];
            for(int j=0;j<n;j++){
                file>>weight;
                Weight[i][j]=weight;
            }
        }
        file.close();
        return true;
    }
}


void Annealing::tsp(double temperatureMax, double temperatureMin){
    minWeight = INT_MAX;
    finalPath = new int[numberOfCities];
    tempPath = new int[numberOfCities];
    int *temp = new int [numberOfCities];
    int calculate;
    

    //losowa sciezka startowa
    for(int i=0; i<=numberOfCities;i++){
        if(i==numberOfCities){
            tempPath[i]=0;
        } else {
             tempPath[i]=i;
        }
    }
    
    finalPath=setFinalPath();
    
    while(temperatureMin<temperatureMax){
        // rozwiazanie generowane przez zamiane dwoch losowych miast
        temp = generateRandomSwap(tempPath);

        //prawdopodobienstwo zaakceptowania nowego rozwiazania
        if(((double) rand() / (RAND_MAX)) < generateProbaility(temperatureMax, temp, tempPath)){
            for(int i=0;i<=numberOfCities;i++){
                if(i!=numberOfCities){
                    tempPath[i]=temp[i];
                } else {
                    tempPath[i]=0;
                }
            }
            
            calculate =calculateCost(Weight, tempPath, numberOfCities);
            if(calculate<minWeight){
                minWeight= calculate;
                finalPath=setFinalPath();
            }
        }
        temperatureMax=temperatureMax*0.999;
    }

    displaySolution(finalPath,numberOfCities,minWeight);
    delete [] temp;
    delete [] tempPath;
    delete [] finalPath;
    
}


int Annealing::calculateCost(int **Weight, int *tempPathh, int numberOfCities){
    int sum=0;
    for(int i=0;i<numberOfCities;i++){
        sum+=Weight[tempPathh[i]][tempPathh[i+1]];
    }
    return sum;
}

double Annealing::generateProbaility(int temperature, int* pathA, int* pathB){
    
    int diff = calculateCost(Weight, pathA, numberOfCities)-calculateCost(Weight, pathB, numberOfCities);

    int exponanta = exp((-1)*diff/temperature);

    return min(1,exponanta);
}

int* Annealing::generateRandomSwap(int *path){
    
    int cityA;
    int cityB;
    
    int *newPath= new int [numberOfCities];
    for(int i=0;i<=numberOfCities;i++){
        newPath[i]=path[i];
    }
    int indexToSwap=numberOfCities-1;
    do{
        cityA=(rand() % indexToSwap)+1;
        cityB=(rand() % indexToSwap)+1;
    }while(cityA == cityB);
    
    double temp = newPath[cityA];
    newPath[cityA]=newPath[cityB];
    newPath[cityB]=temp;
    return newPath;
}


void Annealing::displaySolution(int* finalPath, int numberOfCities, int minWeight){
    cout<<"COST: "<<minWeight<<endl;
    cout<<"Final path: ";
    for(int i=0;i<numberOfCities;i++){
        cout<<finalPath[i]<<" -> ";
    }
    cout<<finalPath[numberOfCities]<<endl;
}



int* Annealing::setFinalPath(){
    cout<<"Set final path: ";
    for(int i=0;i<numberOfCities;i++){
        cout<<tempPath[i]<<" -> ";
        finalPath[i]=tempPath[i];
    }
    finalPath[numberOfCities]=0;
    cout<<finalPath[numberOfCities]<<endl;
    return finalPath;
}




Annealing::~Annealing(){
    for(int i=0;i<numberOfCities;i++){
        delete [] Weight[i];
    }
    delete[] Weight;
}
