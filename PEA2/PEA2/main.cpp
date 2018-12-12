//
//  main.cpp
//  PEA2
//
//  Created by Oliwier Salamon on 12.12.2018.
//  Copyright © 2018 Oliwier Salamon. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ctime>

#include "Annealing.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    srand( static_cast<unsigned int>(time(NULL)));

    int choice;
    double tmin,tmax;
    do{
        cout<<"======================"<<endl;
        cout<<"Projektowanie Efektywnych Algorytmow"<<endl;
        cout<<"1.Symulowane wyzarzanie"<<endl;
        cout<<"2.Wyjdz"<<endl;
        cout<<"Twoj wybor: ";
        cin>>choice;

        if(choice==1){
            Annealing *anal = new Annealing();
            string filename;
            do{
                cout<<endl<<endl<<"Podaj nazwe pliku: ";
                cin>>filename;
            } while (!anal->initializeMatrix(filename));
            anal->initializeMatrix("12.txt");
            do{
                cout<<endl<<endl<<"Podaj tmin: ";
                cin>>tmin;
                cout<<endl<<endl<<"Podaj tmax: ";
                cin>>tmax;
            }while(tmin>tmax);

            anal->tsp(tmax, tmin);
            choice=2;
        }
    }while(choice!=2);

    
    
    
    return 0;
}
