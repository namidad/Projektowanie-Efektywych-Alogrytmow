//
//  Graph.cpp
//  PEA1
//
//  Created by Oliwier Salamon on 15.11.2018.
//  Copyright © 2018 Oliwier Salamon. All rights reserved.
//

#include "Graph.hpp"

bool Graph::initializeMatrix (string filename){
    
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
        visitedCities = new bool [n];
        finalPath = new int[n];
        tempPath = new int[n];
        for(int i=0;i<n;i++){
            Weight[i]=new int[n];
            tempPath[i]=0;
            for(int j=0;j<n;j++){
                file>>weight;
                Weight[i][j]=weight;
                visitedCities[i]=false;
            }
        }
        file.close();
        return true;
    }
}



bool Graph::startProgram(int initialC){
    if(initialC>=0 && initialC<numberOfCities){
        minWeight = 9999999;
        currWeight=0;
        initialCity=initialC;
        currCounter=0;
        iteration=0;
        
        clock_t start=clock();
        tsp(initialCity);
        time = (clock()-start) / (double)(CLOCKS_PER_SEC / 1000 );
        displaySolution();
        return true;
    } else {
        cout<<"Nie ma takiego wierzchołka.."<<endl;
        return false;
    }
    
}

void Graph::tsp(int city){
    int neihgbor;
    
    // zapamietujemy biezacy wierzcholek w tymczasowej tablicy wierzcholkow
    tempPath[currCounter++] = city;

    //jezeli nie mamy w cyklu wszystkich wierzcholkow, to szukamy kolejnego
    if(currCounter<numberOfCities){
        
        // ustawiamy wierzcholek -city- jako odwiedzony
        visitedCities[city]=true;

        // sprawdzamy sasiadow wierzcholka city
        for(neihgbor=0;neihgbor<numberOfCities;neihgbor++){
            
            // sprawdzamy czy sasiad byl odwiedzony i czy istnieje droga pomiedzy wierzcholkami
            if(Weight[city][neihgbor]>0 && !visitedCities[neihgbor]){
                
                // dodajemy wage krawedzi pomiedzy miastem i sasiadem do obecnej sumy
                currWeight+=Weight[city][neihgbor];
                
                // wywolujemy rekurencyjnie poszukiwanie cyklu
                tsp(neihgbor);
                
                // usuwamy wage krawedzi z sumy
                currWeight-=Weight[city][neihgbor];
                
            }
            
        }
        // zwalniamy biezacy wierzcholek
        visitedCities[city] = false;
        
        //jezeli znaleziona sciezka jest cyklem hamiltona
    } else if (Weight[city][initialCity]!=0){
        iteration++;
        // jezeli istnieje droga z ostatniego miasta do poczatkowego to dodajemy wage

        currWeight+=Weight[city][initialCity];
        if(currWeight<minWeight){
            minWeight=currWeight;
            for(int i=0;i<numberOfCities;i++){
                finalPath[i]=tempPath[i];
            }
            finalPath[numberOfCities]=initialCity;
            counter = currCounter;
        }
        currWeight-=Weight[city][initialCity];
    }
    currCounter--;
}


void Graph::displaySolution(){
    if(counter){
        cout<<"================================================================="<<endl;
        cout<<fileN<<endl;
        cout<<"-------------------------------------------------"<<endl;
        cout<<"Number of cities:      "<<numberOfCities<<endl;
        cout<<"-----------------------"<<endl;
        cout<<"       ";
        for(int i=0;i<numberOfCities;i++){
            cout<<i<<"   ";
        }
        cout<<endl<<"    ------------------------"<<endl;
        for(int i=0;i<numberOfCities;i++){
            if(i<10){
                cout<<" "<<i<<" |   ";
                for(int j=0;j<numberOfCities;j++){
                    cout<<Weight[i][j]<<"  ";
                }
            } else {
                cout<<" "<<i<<"|   ";
                for(int j=0;j<numberOfCities;j++){
                    cout<<Weight[i][j]<<"  ";
                }
            }
            
            cout<<endl;
        }
        cout<<endl;
        
        cout<<"--------------------------------------"<<endl;
        cout<<"ALGORITHM - BRUTE FORCE"<<endl;
        cout<<"--------------------------------------"<<endl;
        cout<<"Iterations = "<<iteration<<endl<<endl;
        cout<<"Time: "<<time<<" ms"<<endl<<endl;
        cout << "Solution = " << minWeight << endl <<"-----------------------"<<endl;
        cout<<"Path = ";
        for(int i=0;i<=counter;i++){
            if(i!=counter){
                cout<<finalPath[i]<<" - ";
            } else {
                cout<<finalPath[i]<<endl;
            }
            
        }
        
    } else {
        cout << "NO HAMILTONIAN CYCLE" << endl;
    }
}

Graph::~Graph(){
    for(int i=0;i<numberOfCities;i++){
        delete Weight[i];
    }
    delete Weight;
    delete visitedCities;
    delete finalPath;
    delete tempPath;
}



