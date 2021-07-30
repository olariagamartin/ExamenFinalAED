#ifndef PILA_H
#define PILA_H
#include "Lista.h"
template <class T> class Pila: public Lista<T> {
private:
    int largo;
public:
    Pila() { Lista<T>(); largo=0;}
    void apilar(T d) { this->add(d); largo++;}
    T tope() { return this->cabeza(); }
    void desapilar() { this->borrar(); largo--;}
    bool pilaVacia() { return this->esVacia(); }
    int getLargo(){return largo;}
};
#endif