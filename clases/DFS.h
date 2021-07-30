#ifndef DFS_H
#define DFS_H
#include "Pila.h"
#include "Cola.h"
#include <iostream>

using namespace std;

int calcCostos(Pila<int> cam, int costos[MAX][MAX]){
            Pila<int> aux;
            int costo=0;
            int c1=cam.tope();
            aux.apilar(cam.tope());
            cam.desapilar();
            int c2=0;
            while(!cam.esVacia()){
                c2=cam.tope();
                costo += costos[c2][c1];
                c1=c2;
                aux.apilar(cam.tope());
                cam.desapilar();
            }
            while(!aux.esVacia()){
                cam.apilar(aux.tope());
                aux.desapilar();
            }
            return costo;
        }

string convCity(int a){

            switch (a)
            {
            case 0:
                return "MA";
                break;

            case 1:
                return "BA";
                break;
                
            case 2:
                return "RO";
                break;
                
            case 3:
                return "PA";
                break;
                
            case 4:
                return "LO";
                break;
                
            case 5:
                return "BE";
                break;
                
            case 6:
                return "AM";
                break;
                
            default:
                return "no_city";
                break;
            }

        }

class listCaminos{

    private:
    Cola<Pila<int> > caminosEco;
    int costos[MAX][MAX];

    public:
    listCaminos(){}

    ~listCaminos(){}

    void setCosto(int cost[MAX][MAX]){
        copyMatrix(costos, cost);
    }    

    void copyMatrix(int copy[][MAX], int base[][MAX]){
            for (int i = 0; i < MAX; i++)
                for (int j = 0; j < MAX; j++)
                    copy[i][j] = base[i][j];
        }

    void addCamino(Pila<int> cam){

        Pila<int> aux;
        Pila<int> aux2;
            while(!cam.esVacia()){
                aux.apilar(cam.tope());
                cam.desapilar();
            }
            while(!aux.esVacia()){
                cam.apilar(aux.tope());
                aux2.apilar(aux.tope());
                aux.desapilar();
            }

        caminosEco.encolar(aux2);
    }

    void vaciar(){
        while(!caminosEco.esVacia()){
            caminosEco.desencolar();
        }
    }

    void print(){
        int i=1;
         while(!caminosEco.esVacia()){
             cout << "Camino Opcion: " << i << endl;    //PRINT
                Pila<int> aux;
                Pila<int> cam;
                cam = caminosEco.tope();
                while(!cam.esVacia()){
                    aux.apilar(cam.tope());
                    cam.desapilar();
                }
                while(!aux.esVacia()){
                    cout << convCity(aux.tope()) << "-->";    //PRINT
                    cam.apilar(aux.tope());
                    aux.desapilar();
                }
                cout << endl;    //PRINT
                cout << "Costo: " << calcCostos(cam,costos) << endl;    //PRINT
                caminosEco.desencolar();
                i++;
            }
    }

    int costoCam(){ //Costo del ultimo camino agregado, metodo solo utilizado para el apartado 1
        int c = calcCostos(caminosEco.tope(),costos);
        return c;
    }

};

class caminoDFS
{
    private:
        int costos[MAX][MAX];
        bool czo;
        Pila<int> camino1;
        Pila<int> camino2;
        Cola<int> colaV1;
        Cola<int> colaVisit;
        listCaminos lCaminos; //cola de caminos 
        int cCzo; //ciudad de comienzo
        int d; //ciudad de destino
        int arrayCity[MAX]={0,1,2,3,4,5,6};
        int cuenta; //Numero total de caminos
        int costoCam; //Costo del Camino mas economico
        int cuentaCam; //Cantidad de caminos economicos
        int numCam;//Numero del ultimo camino mas economico
        Pila<int> arrayNumCam; //pila con el numero correspondiente a la combinacion que pertenece al camino economico agregado

    public:
        caminoDFS(int cityCzo, int cityFin, int cost[MAX][MAX]){
			czo = true;
            cCzo=cityCzo-1;
            d=cityFin-1;
            setColaV1();
            costoCam=0;
            cuenta=0;
            cuentaCam=0;
            numCam=0;
            copyMatrix(costos, cost);
            lCaminos.setCosto(costos);
		}

		~caminoDFS(){}

        void copyMatrix(int copy[][MAX], int base[][MAX]){
            for (int i = 0; i < MAX; i++)
                for (int j = 0; j < MAX; j++)
                    copy[i][j] = base[i][j];
        }

        void setColaV1(){
           colaV1.encolar(cCzo);
           for(int i=0; i<MAX; i++){
               if(arrayCity[i] !=cCzo and arrayCity[i] !=d){
                        colaV1.encolar(arrayCity[i]);
               }    
           }
           colaV1.encolar(d);
        }

        void copiarCam(){
            cuentaCam++;
            //IMPRESION DEL CAMINO Y ADEMAS COMPLETO CAMINO2
            Pila<int> aux;
            while(!camino1.esVacia()){
                aux.apilar(camino1.tope());
                //cout << convCity(camino1.tope()) << endl; //PRINT
                camino1.desapilar();
            }
            while(!aux.esVacia()){
                camino1.apilar(aux.tope());
                camino2.apilar(aux.tope());
                aux.desapilar();
            }
            //IMPRESION DEL CAMINO Y ADEMAS COMPLETO CAMINO2
            lCaminos.addCamino(camino1);
            arrayNumCam.apilar(cuenta);
            numCam= cuenta;
            cuentaCam=1;
            cuenta++;
        }

        void comparaCam(){
            //IMPRESION DEL CAMINO
            Pila<int> aux;
            while(!camino1.esVacia()){
                aux.apilar(camino1.tope());
                //cout << convCity(camino1.tope()) << endl; //PRINT
                camino1.desapilar();
            }
            while(!aux.esVacia()){
                camino1.apilar(aux.tope());
                aux.desapilar();
            }
            //IMPRESION DEL CAMINO
            if(calcCostos(camino1,costos) == calcCostos(camino2,costos)){
                lCaminos.addCamino(camino1);
                cuentaCam++;
                numCam= cuenta;
                arrayNumCam.apilar(cuenta);
                while(!camino2.esVacia()){
                    camino2.desapilar();
                }
                Pila<int> aux;
                while(!camino1.esVacia()){
                    aux.apilar(camino1.tope());
                    camino1.desapilar();
                }
                while(!aux.esVacia()){
                    camino1.apilar(aux.tope());
                    camino2.apilar(aux.tope());
                    aux.desapilar();
                }
            }else if (calcCostos(camino1,costos) < calcCostos(camino2,costos)){
                lCaminos.vaciar();
                while(!arrayNumCam.esVacia()){
                    arrayNumCam.desapilar();
                }
                arrayNumCam.apilar(cuenta);
                costoCam = calcCostos(camino1,costos);
                numCam= cuenta;
                cuentaCam=1;
                while(!camino2.esVacia()){
                    camino2.desapilar();
                }
                Pila<int> aux;
                while(!camino1.esVacia()){
                    aux.apilar(camino1.tope());
                    camino1.desapilar();
                }
                while(!aux.esVacia()){
                    camino1.apilar(aux.tope());
                    camino2.apilar(aux.tope());
                    aux.desapilar();
                }
                lCaminos.addCamino(camino1);
            }
            cuenta++;
        }

        void printCaminos(){
            lCaminos.print();
        }

        listCaminos getlCaminos(){
            return lCaminos;
        }

        void calCaminoEco(int niv){
                niv; //nivel = 6 (es decir quedan 6 ciudades)
                int ady=niv-1; //cantidad total de ciudades adyacentes por visitar
                int contR=0; //cantidad de ciudades adyacentes visitadas
                if(niv == 1 and czo == true){
                    camino1.apilar(colaV1.tope()); //guardo elemento del nivel = 1
                    colaV1.desencolar();//desencolo el elemento que apile en la linea anterior
                    camino1.apilar(d); //apilo RO
                    copiarCam(); //copio camino1 a camino2
                    camino1.desapilar(); //desapilar ultimo elemento de la pila, desapilo RO
                    colaVisit.encolar(camino1.tope());
                    camino1.desapilar(); //desapilar ultimo elemento de la pila, desapilo AM
                    czo = false;
                }else{
                    if(niv == 1 and czo == false){
                        camino1.apilar(d); //apilo RO
                        comparaCam();//compara camino1 y camino2 y guarda en camino2 el mas economico
                        camino1.desapilar(); //desapilar ultimo elemento de la pila, desapilo RO
                        colaVisit.encolar(camino1.tope());
                        camino1.desapilar(); //desapilar ultimo elemento de la pila, desapilo AM
                    }else{
                        while(contR<ady){
                            if(czo == true){
                                camino1.apilar(colaV1.tope());//MA
                                colaV1.desencolar();
                                calCaminoEco(niv-1);
                                contR++;
                                if (niv == 2){
                                    colaVisit.encolar(camino1.tope());
                                    camino1.desapilar(); //desapilar ultimo elemento de la pila, desapilo BE
                                }
                            }else{
                                    camino1.apilar(colaVisit.tope());
                                    colaVisit.desencolar();
                                    calCaminoEco(niv-1);
                                    contR++;
                                    if((ady-contR) == 0){
                                        colaVisit.encolar(camino1.tope());
                                        camino1.desapilar();
                                    }
                            }
                        }
                    }
                }
        }

        bool sonIdent(Pila<int> cam1, Pila<int> cam2){
            bool resp=false;
            int largoT=cam1.getLargo();
            int cuentaCam=0;
            Pila<int> aux;
            Pila<int> aux2;
            while(!cam1.esVacia()){
                if(cam1.tope() == cam2.tope()){
                    cuentaCam++;
                }
                aux.apilar(cam1.tope());
                aux2.apilar(cam2.tope());
                cam1.desapilar();
                cam2.desapilar();
            }
            while(!aux.esVacia()){
                cam1.apilar(aux.tope());
                cam2.apilar(aux2.tope());
                aux.desapilar();
                aux2.desapilar();
            }
            if(cuentaCam == largoT){
                resp=true;
            }
            return resp;
        }

        void copiarCamL(){
            cuentaCam++;
            Pila<int> aux;
            Pila<int> aux2;
            while(!camino1.esVacia()){
                aux.apilar(camino1.tope());
                camino1.desapilar();
            }
            while(!aux.esVacia()){
                camino1.apilar(aux.tope());
                aux2.apilar(aux.tope());
                aux.desapilar();
            }
            while(calcCostos(aux2,costos) > 700){
                int dAux=0;
                dAux=aux2.tope();
                aux2.desapilar();
                aux2.desapilar();
                aux2.apilar(dAux);
            }
            //IMPRESION DEL CAMINO Y ADEMAS COMPLETO CAMINO2
            while(!aux2.esVacia()){
                aux.apilar(aux2.tope());
                //cout << convCity(aux2.tope()) << endl; //PRINT
                aux2.desapilar();
            }
            while(!aux.esVacia()){
                camino2.apilar(aux.tope());
                aux.desapilar();
            }
            //IMPRESION DEL CAMINO Y ADEMAS COMPLETO CAMINO2
            lCaminos.addCamino(camino2);
            arrayNumCam.apilar(cuenta);
            numCam= cuenta;
            cuentaCam=1;
            cuenta++;
        }

        void comparaCamL(){
            Pila<int> aux;
            Pila<int> aux2;
            while(!camino1.esVacia()){
                aux.apilar(camino1.tope());
                camino1.desapilar();
            }
            while(!aux.esVacia()){
                camino1.apilar(aux.tope());
                aux2.apilar(aux.tope());
                aux.desapilar();
            }
            while(calcCostos(aux2,costos) > 700){
                int dAux=0;
                dAux=aux2.tope();
                aux2.desapilar();
                aux2.desapilar();
                aux2.apilar(dAux);
            }
            //IMPRESION DEL CAMINO
            while(!aux2.esVacia()){
                aux.apilar(aux2.tope());
                //cout << convCity(aux2.tope()) << endl; //PRINT
                aux2.desapilar();
            }
            while(!aux.esVacia()){
                aux2.apilar(aux.tope());
                aux.desapilar();
            }
            //IMPRESION DEL CAMINO
            if(aux2.getLargo() == camino2.getLargo()){
                if(!sonIdent(aux2,camino2)){
                    lCaminos.addCamino(aux2);
                    if(calcCostos(aux2,costos) < costoCam){
                        costoCam = calcCostos(aux2,costos);
                    }
                    cuentaCam++;
                    numCam= cuenta;
                    arrayNumCam.apilar(cuenta);
                    while(!camino2.esVacia()){
                        camino2.desapilar();
                    }
                    Pila<int> aux;
                    while(!aux2.esVacia()){
                        aux.apilar(aux2.tope());
                        aux2.desapilar();
                    }
                    while(!aux.esVacia()){
                        camino2.apilar(aux.tope());
                        aux.desapilar();
                    }
                }
            }else if (aux2.getLargo() > camino2.getLargo()){
                lCaminos.vaciar();
                while(!arrayNumCam.esVacia()){
                    arrayNumCam.desapilar();
                }
                arrayNumCam.apilar(cuenta);
                costoCam = calcCostos(aux2,costos);
                numCam= cuenta;
                cuentaCam=1;
                while(!camino2.esVacia()){
                    camino2.desapilar();
                }
                Pila<int> aux;
                while(!aux2.esVacia()){
                    aux.apilar(aux2.tope());
                    aux2.desapilar();
                }
                while(!aux.esVacia()){
                    camino2.apilar(aux.tope());
                    aux.desapilar();
                }
                lCaminos.addCamino(camino2);
            }
            cuenta++;
            
        }

        int getCostoCam(){
            return costoCam;
        }

        int getCuentaCam(){
            return cuentaCam;
        }

        void calCaminoL(int niv){
                niv; //nivel = 6 (es decir quedan 6 ciudades)
                int ady=niv-1; //cantidad total de ciudades adyacentes por visitar
                int contR=0; //cantidad de ciudades adyacentes visitadas
                if(niv == 1 and czo == true){
                    camino1.apilar(colaV1.tope()); //guardo elemento del nivel = 1
                    colaV1.desencolar();//desencolo el elemento que apile en la linea anterior
                    camino1.apilar(d); //apilo RO
                    copiarCamL(); //copio camino1 a camino2
                    camino1.desapilar(); //desapilar ultimo elemento de la pila, desapilo RO
                    colaVisit.encolar(camino1.tope());
                    camino1.desapilar(); //desapilar ultimo elemento de la pila, desapilo AM
                    czo = false;
                }else{
                    if(niv == 1 and czo == false){
                        camino1.apilar(d); //apilo RO
                        comparaCamL();//compara camino1 y camino2 y guarda en camino2 el mas economico
                        camino1.desapilar(); //desapilar ultimo elemento de la pila, desapilo RO
                        colaVisit.encolar(camino1.tope());
                        camino1.desapilar(); //desapilar ultimo elemento de la pila, desapilo AM
                    }else{
                        while(contR<ady){
                            if(czo == true){
                                camino1.apilar(colaV1.tope());//MA
                                colaV1.desencolar();
                                calCaminoL(niv-1);
                                contR++;
                                if (niv == 2){
                                    colaVisit.encolar(camino1.tope());
                                    camino1.desapilar(); //desapilar ultimo elemento de la pila, desapilo BE
                                }
                            }else{
                                    camino1.apilar(colaVisit.tope());
                                    colaVisit.desencolar();
                                    calCaminoL(niv-1);
                                    contR++;
                                    if((ady-contR) == 0){
                                        colaVisit.encolar(camino1.tope());
                                        camino1.desapilar();
                                    }
                            }
                        }
                    }
                }
        }
};

#endif
