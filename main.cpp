#include <iostream>
#include <map>
#define MAX 7
#include "clases/DFS.h"
#include "clases/Pila.h"
#include "clases/Grafo.h"

using namespace std;

int costos[MAX][MAX]={ 0,  150,  180,  210,  340,  160,  280,
							 150, 0,  220,  250,  350,  290,  220, 
							 180,  220, 0,  350,  440,  240,  200,
							 210,  250,  350, 0,   95,  180,  200,
							 340,  350,  440,   95, 0,  300,  180,
							 160,  290,  240,  180,  300, 0,  150,
							 280,  220,  200,  200,  180,  150, 0,
						};



listCaminos calCamEco(listCaminos lCam1, listCaminos lCam2){
    if(lCam1.costoCam() < lCam2.costoCam()){
        return lCam1;
    }else{
        return lCam2;
    }
}

//FUNCIONES MENU

void apartado1(){
    cout << endl << "---/Camino mas economico/---" << endl;
    caminoDFS dRO(1,3,costos); 
    dRO.calCaminoEco(6);
    listCaminos lCamRO = dRO.getlCaminos();
    caminoDFS dBA(1,2,costos); 
    dBA.calCaminoEco(6);
    listCaminos lCamBA = dBA.getlCaminos();
    listCaminos lCamEco = calCamEco(lCamRO,lCamBA);
    lCamEco.print();
    cout << endl << "---/Ciclo mas economico/---" << endl;
    caminoDFS ciloEco(1,1,costos); 
    ciloEco.calCaminoEco(7);
    ciloEco.printCaminos();
    cin.ignore();
}

void apartado2(){
    cout << "---//Ciudades//---" << endl;
    cout << "1.Madrid" << endl;
    cout << "2.Barcelona" << endl;
    cout << "3.Roma" << endl;
    cout << "4.Paris" << endl;
    cout << "5.Londres" << endl;
    cout << "6.Berlin" << endl;
    cout << "7.Amsterdam" << endl;
    int cityCzo = 0;
    int cityFin = 0;
    while(cityCzo<1 or cityCzo>7){
        cout << "Ciudad de partida: ";
        cin >> cityCzo;
    }
    while(cityFin==0 or cityFin>7){
        cout << "Ciudad de destino: ";
        cin >> cityFin;
    }
    cout << endl << "---/Camino mas largo y menor o igual a 700/---" << endl;
    caminoDFS punto1(cityCzo,cityFin,costos); 
    punto1.calCaminoL(6);
    cout << "Menor costo: " << punto1.getCostoCam() << endl;
    cout << "Cantidad de caminos: " << punto1.getCuentaCam() << endl;
    punto1.printCaminos();
    cout << endl << "---/Ciclo mas largo y menor o igual a 700/---" << endl;
    caminoDFS punto2(cityCzo,cityCzo,costos); 
    punto2.calCaminoL(7);
    cout << "Menor costo: " << punto2.getCostoCam() << endl;
    cout << "Cantidad de ciclos: " << punto2.getCuentaCam() << endl;
    punto2.printCaminos();
    cin.ignore();
}

void apartado3(){
    Grafo* grafo = new Grafo(costos);
    grafo->loadMatrices();
    grafo->calcuHamilt();
    grafo->showHamiltonianPath();
    grafo->showHamiltoCicle();
    cin.ignore();
}

void printMenu(){
    cout << "----//Algoritmos y Estructuras de Datos - Parcial de Promoción 2020//----" << endl;
    cout << "---//Acciones//---" << endl;
    cout << "1.Apartado 1" << endl;
    cout << "2.Apartado 2" << endl;
    cout << "3.Apartado 3" << endl;
    int resp=0;
    while(resp<1 or resp>3){
        cin >> resp;
    }
    switch (resp)
    {
    case 1:
        apartado1();
        break;
    case 2:
        apartado2();
        break;
    case 3:
        apartado3();
        break;
    default:
        break;
    }
}

int main(){
    printMenu();
    cin.ignore();
    
    system("Pause");
    return 0;
}

