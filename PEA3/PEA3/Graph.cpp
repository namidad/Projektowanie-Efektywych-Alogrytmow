//
//  Graph.cpp
//  PEA3
//
//  Created by Oliwier Salamon on 16.01.2019.
//  Copyright © 2019 Oliwier Salamon. All rights reserved.
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
        weightIndex=numberOfCities+1;
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


int Graph::tsp(){
    currentSizeOfPopulation=100;
    numberOfPopulation=currentSizeOfPopulation;
    numberOfIterations=200;
    numberOfCrossing=100;
    numberOfMutations=50;
    population = new int*[currentSizeOfPopulation];
    for(int i=0;i<numberOfPopulation;i++){
        population[i]=new int[numberOfCities+1];
        for(int j=0;j<=numberOfCities+1;j++){
            population[i][j]=0;
        }
    }
    generateRandomPopulation();
    for(int i=0;i<numberOfIterations;i++){
        for(int j=0;j<numberOfCrossing;j++){
            population=crossingOperation(population);
        }
        
        for(int j=0; j<numberOfMutations;j++){
            if(rand()/RAND_MAX<0.3){
                populationMutation();
            }
        }
        
        sortPopulation(currentSizeOfPopulation);
        currentSizeOfPopulation=numberOfPopulation;
    }
    

    cout<<endl<<"NAJLEPSZA ZNALEZIONA SCIEZKA"<<endl;
    for(int i=0;i<=numberOfCities;i++){
        if(i!=numberOfCities){
            cout<<population[0][i]<<" -> ";
        } else {
            cout<<population[0][i]<<endl;
        }
    }
    
    cout<<"WAGA SCIEZKI: "<<population[0][weightIndex]<<endl;
    
    
    return population[0][weightIndex];
}

void Graph::sortPopulation(int sizeOfPopulation){
    for(int i=0; i<sizeOfPopulation-1;i++){
        for(int j=0;j<sizeOfPopulation-i-1;j++){
            if(population[j][weightIndex]>population[j+1][weightIndex]){
                int *tmp=new int [numberOfCities+1];
                for(int k=0;k<=numberOfCities+1;k++){
                    tmp[k]=population[j][k];
                    population[j][k]=population[j+1][k];
                    population[j+1][k]=tmp[k];
                }
                delete[] tmp;
            }
        }
    }
}


int** Graph::crossingOperation(int ** population){
    int randomA,randomB;
    //wybieramy dwie losowe sciezki do polaczenia
    do{
        randomA = rand() % (numberOfPopulation);
        randomB = rand() % (numberOfPopulation);
    } while (randomA==randomB);
    
    int *tempA = population[randomA];

    int *tempB = population[randomB];
    
    int *child = new int[numberOfCities+1];
    bool *visited = new bool[numberOfCities];
    
    for(int i=0;i<numberOfCities;i++){
        visited[i]=false;
    }
    
    int crossingIndex = 0;
    
    for(int i=0;i<(numberOfCities+1)/2;i++){
        child[crossingIndex]=tempA[crossingIndex];
        visited[tempA[i]] = true;
        crossingIndex++;
    }
    
    for(int i=0; i<numberOfCities;i++){
        if(visited[tempB[i]]==false){
            child[crossingIndex]=tempB[i];
            visited[tempB[i]]=true;
            crossingIndex++;
        }
    }
    
    child[numberOfCities]=0;
    
    
    child[weightIndex] =calculatePathCost(child);
    currentSizeOfPopulation++;
    
    int ** tempArr = new int*[currentSizeOfPopulation];
    
    for(int i=0;i<currentSizeOfPopulation;i++){
        tempArr[i]=new int[numberOfCities+1];
        for(int j=0;j<numberOfCities+1;j++){
            tempArr[i][j]=0;
        }
    }
    
    for(int i=0;i<currentSizeOfPopulation-1;i++){
        for(int j=0;j<=numberOfCities+1;j++){
            tempArr[i][j]=population[i][j];
        }
    }
    
    for(int i=0;i<=numberOfCities+1;i++){
        tempArr[currentSizeOfPopulation-1][i]=child[i];
    }

    delete[] tempA;
    delete[] tempB;
    delete[] visited;
    delete[] child;
    return tempArr;
}



void Graph::populationMutation(){
    int randomA,randomB,randomC;
    do{
        randomA = rand() % (numberOfPopulation);
        randomB = rand() % (numberOfCities-1) +1;
        randomC = rand() % (numberOfCities-1) +1;
    }while(randomB==randomC);
    
    int tmp = population[randomA][randomB];
    population[randomA][randomB]=population[randomA][randomC];
    population[randomA][randomC]=tmp;
    population[randomA][weightIndex]=calculatePathCost(population[randomA]);
}



void Graph::generateRandomPopulation(){
    
    for(int i=0;i<numberOfPopulation;i++){
        int *singlePopulation = new int[numberOfCities+1];
        int randomA,randomB;
        
        do{
            randomA = rand() % (numberOfCities-1) + 1;
            randomB = rand() % (numberOfCities-1) + 1;
        } while(randomA==randomB);
        
        for(int j=0;j< numberOfCities;j++){
            singlePopulation[j]=j;
        }
        int tmp = singlePopulation[randomA];
        singlePopulation[randomA]=singlePopulation[randomB];
        singlePopulation[randomB]=tmp;
        
        singlePopulation[numberOfCities]=0;
        singlePopulation[weightIndex]= calculatePathCost(singlePopulation);
        for(int j=0;j<=numberOfCities+1;j++){
            population[i][j]=singlePopulation[j];
        }

        delete[] singlePopulation;
    }
}



int Graph::calculatePathCost(int *path){
    int sum=0;
    for(int i=0;i<numberOfCities;i++){
        sum+= Weight[path[i]][path[i+1]];
    }
    return sum;
}

void Graph::displayPopulation(){
    cout<<endl<<"POPULATION"<<endl;
    for(int i=0;i<currentSizeOfPopulation;i++){
        cout<< i << " === ";
        for(int j=0; j<=numberOfCities;j++){
            cout<<population[i][j] << " ";
        }
        cout<< " w("<<population[i][weightIndex]<<") "<<endl;
    }
}


Graph::~Graph(){
    for(int i=0;i<numberOfCities;i++){
        delete [] Weight[i];
    }
    
    for(int i=0;i<numberOfPopulation;i++){
        delete [] population[i];
    }

    delete[] Weight;
    delete[] population;
}
