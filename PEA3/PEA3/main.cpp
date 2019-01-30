//
//  main.cpp
//  PEA3
//
//  Created by Oliwier Salamon on 16.01.2019.
//  Copyright © 2019 Oliwier Salamon. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ctime>

#include "Graph.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    srand( static_cast<unsigned int>(time(NULL)));
    Graph *graph = new Graph();
    graph->initializeMatrix("323.txt");
    double time;
    clock_t start = clock();
    graph->tsp();
    time=(clock()-start)/ (double)(CLOCKS_PER_SEC / 1000);
    cout<<"Czas: "<< time<<endl;
    graph->~Graph();
    
    
//    if(graph->initializeMatrix("443.txt")){
//        int sum=0;
//        for(int i=0;i<8;i++){
//            sum+=graph->tsp();
//        }
//        cout<<"SUMA: "<<sum<<endl;
//        cout<<"Średnio: "<<sum/8<<endl;
//    }


//    int choice;
//    double tmin,tmax;
//    do{
//        cout<<"======================"<<endl;
//        cout<<"Projektowanie Efektywnych Algorytmow"<<endl;
//        cout<<"1.Symulowane wyzarzanie"<<endl;
//        cout<<"2.Wyjdz"<<endl;
//        cout<<"Twoj wybor: ";
//        cin>>choice;
//
//        if(choice==1){
//            Annealing *aneaaling = new Annealing();
//            string filename;
//            do{
//                cout<<endl<<endl<<"Podaj nazwe pliku: ";
//                cin>>filename;
//            } while (!aneaaling->initializeMatrix(filename));
//            aneaaling->initializeMatrix(filename);
//            do{
//                cout<<endl<<endl<<"Podaj tmin: ";
//                cin>>tmin;
//                cout<<endl<<endl<<"Podaj tmax: ";
//                cin>>tmax;
//            }while(tmin>tmax);
//
//            aneaaling->tsp(tmax, tmin);
//            aneaaling->~Annealing();
//
//        }
//    }while(choice!=2);

    return 0;
}
