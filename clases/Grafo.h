#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>
#include <bitset>
#include <map>
#include "Lista.h"

using namespace std;

#define n 7

struct Celda
{
    bitset<n> place[n];
};

class Grafo
{
private:
    int matrixCost[n][n];
    Lista<Celda> M_i[n][n];
    bitset<n> M[n];
    map<int, string> cities;

public:
    Grafo(){}
    Grafo(int _matrixCost[n][n])
    {
        copyMatrix(matrixCost, _matrixCost);
        cities.insert(pair<int, string>(0,"MA"));
        cities.insert(pair<int, string>(1,"BA"));
        cities.insert(pair<int, string>(2,"RO"));
        cities.insert(pair<int, string>(3,"PA"));
        cities.insert(pair<int, string>(4,"LO"));
        cities.insert(pair<int, string>(5,"BE"));
        cities.insert(pair<int, string>(6,"AM"));
    }

    ~Grafo() {}

    template <class T> void copyMatrix(T copy[][n], T base[][n])
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                copy[i][j] = base[i][j];
    }

    //carga las matrices M_i y M
    void loadMatrices() {
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(matrixCost[i][j] != 0){
                    //M_i
                    Celda newCelda;
                    newCelda.place[0].set(i);
                    newCelda.place[1].set(j);
                    M_i[i][j].add(newCelda);
                    //M
                    M[i].set(j);
                }
            }
        }
    }

    void calcuHamilt(){
        for(int i=1; i<n-1; i++) {
            multiMatrices(i);
        }
    }

    // Funciona similar a una multiplicacion de matrices comun
    void multiMatrices(int degree){
        Lista<Celda> mAux[n][n];
        copyMatrix(mAux, M_i);
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                // Se hace la multiplicacion latina entre la fila
                // y la columna, dentro del mismo metodo se carga
                // el resultado a la matriz principal
                bitset<n> column = getColumn(M, j);
                multiLatina(mAux[i], i, column, j, degree);
            }
        }
    }

    // Hace la multiplicacion latina entre la fila y la columna recibida
    void multiLatina(Lista<Celda> fila[n], int _fila, bitset<n> col, int _col, int degree){
        // En (celAux) se guarda la celda actual. Se recorren sus elementos
        // (celFinal) guarda las multiplicaciones no nulas que al final
        // se cargan a la matriz principal
        Lista<Celda> celAux, celFinal;
        Celda newCel;
        for(int i=0; i<n; i++){
            celAux = fila[i];
            while(!celAux.esVacia() && col[i]){
                if(!anyCol(celAux.cabeza().place, _col)){
                    newCel = celAux.cabeza();
                    newCel.place[degree+1].set(_col);
                    celFinal.add(newCel);
                }
                celAux = *(celAux.resto());
            }
        }
        
        M_i[_fila][_col] = celFinal;
    }

    // True si hay al menos un bit esta seteado en la columna
    bool anyCol(bitset<n> m[n], int col){
        for(int i=0; i<n; i++)
            if(m[i][col]) return true;
        return false;
    }

    bitset<n> getColumn(bitset<n> matrix[n], int _col){
        bitset<n> col;
        for(int i=0; i<n; i++)
            if(matrix[i][_col])
                col.set(i);
        return col;
    }

    void showPath(Celda path){
        int city;
        cout << "\nCamino: ";
        for(int i=0; i<n; i++){
            city = getColFirstBit(path.place[i]);
            cout << "->" << this->cities[city];
        }
    }

    Celda getMinPath(int start, int end) {
        Lista<Celda> caminos;
        Celda minPaht;
        int length1, length2;

        caminos = M_i[start][0];
        minPaht = caminos.cabeza();
        
        //for(int i=0; i<n; i++){
            caminos = M_i[start][end];
            while(!caminos.esVacia()){
                length1 = getPathLenght(minPaht);
                length2 = getPathLenght(caminos.cabeza());
                if(length1 > length2){
                    minPaht = caminos.cabeza();
                }
                caminos = *(caminos.resto());
            }            
        //}
        return minPaht;
    }

    int getPathLenght(Celda cel) {
        // pathLenght guarda la distancia total
        // actualCity y tmp se usan para calcular las 
        // distancias entre dos cuidades
        int pathLenght, actualCity, tmp;
        pathLenght = 0;
        actualCity = getColFirstBit(cel.place[0]);
        for(int i=1; i<n; i++){
            tmp = getColFirstBit(cel.place[i]);
            pathLenght += this->matrixCost[actualCity][tmp];
            actualCity = tmp;
        }
        return (pathLenght == 0) ? 99999 : pathLenght;
    }

    int getColFirstBit(bitset<n> bit){
        for(int i=0; i<n; i++)
            if(bit[i])  return i;
        return 0;
    }

    // Camino Hamiltoniano minimo desde start hasta end
    void showHamiltonianPath(int start, int end){
        Celda minPath = this->getMinPath(start, end);
        cout << "Camino Hamiltoniano Minimo" << endl;
        this->showPath(minPath);
        cout << "\n\nCosto: " << this->getPathLenght(minPath) << endl;
    }

    // Camino Hamiltoniano minimo de Madrid a Barcelona o Roma
    void showHamiltonianPath() {
        Celda min1, min2;
        int cost1, cost2;
        min1 = this->getMinPath(0,1);
        cost1 = getPathLenght(min1);
        min2 = this->getMinPath(0,2);
        cost2 = getPathLenght(min2);
        cout << "Camino Hamiltoniano Minimo" << endl;
        if(cost1 < cost2){
            this->showPath(min1);
            cout << "\nCosto: " << cost1 << endl;
        }            
        else{
            this->showPath(min2);
            cout << "\nCosto: " << cost2 << endl;
        }    
    }

    // Ciclo Hamiltoniano desde Madrid
    void showHamiltoCicle() {
        Celda hamilCicle, temp;
        int length, lenAux;
        hamilCicle = getMinPath(0,1);
        length = getPathLenght(hamilCicle) + matrixCost[1][0];
        cout << "\nCiclo Hamiltoniano Minimo" << endl;
        for(int i=2; i<n; i++){
            temp = getMinPath(0,i);
            lenAux = getPathLenght(temp) + matrixCost[i][0];
            if(lenAux < length)
                hamilCicle = temp;
        }
        showPath(hamilCicle);
        cout << "->" << this->cities[0] << endl;
        cout << "Costo: " << length << endl;
    }

};

#endif