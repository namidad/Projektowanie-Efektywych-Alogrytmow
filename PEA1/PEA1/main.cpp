//
//  main.cpp
//  PEA1
//
//  Created by Oliwier Salamon on 15.11.2018.
//  Copyright © 2018 Oliwier Salamon. All rights reserved.
//

#include <iostream>
#include <curses.h>
#include "Graph.hpp"
using namespace std;

int main(int argc, const char * argv[]) {

    
    int choice;
    do{
        cout<<"======================"<<endl;
        cout<<"Projektowanie Efektywnych Algorytmow"<<endl;
        cout<<"1.Brute Force"<<endl;
        cout<<"2.Wyjdz"<<endl;
        cout<<"Twoj wybor: ";
        cin>>choice;
        
        if(choice==1){
            Graph *graph;
            string filename;
            int initialCity;
            graph=new Graph();
            do{
                cout<<endl<<endl<<"Podaj nazwe pliku: ";
                cin>>filename;
            } while (!graph->initializeMatrix(filename));
            
            do{
                cout<<endl<<endl<<"Podaj wierzcholek poczatkowy: ";
                cin>>initialCity;
            }while(!graph->startProgram(initialCity));
            choice=2;
        }
    }while(choice!=2);
    

    return 0;
}
