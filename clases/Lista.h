#ifndef LISTA_H
#define LISTA_H
#include "Nodo.h"

template <class T> class Lista {
private:
    Nodo<T>* comienzo;
public:
    Lista() { comienzo = new Nodo<T>(); }
    Lista(Nodo<T>* n) { comienzo = n; }
    void add(T d) {
        Nodo<T>* nuevo = new Nodo<T>(d);
        nuevo->setNext(comienzo);
        comienzo = nuevo;
    }
    bool esVacia() {
        return comienzo->esVacio();
    }
    T cabeza() {
        return comienzo->getDato();
    }
    Lista* resto() {
        Lista* nuevaLista = new Lista(comienzo->getNext());
        return nuevaLista;
    }
    void borrar() {
        if(!this->esVacia()) {
            Nodo<T>* tmp = comienzo;
            comienzo = comienzo->getNext();
            delete tmp;
        }
    }
    T last() {
        if((this->resto())->esVacia())
            return this->cabeza();
        return this->resto()->last();
    }
    void borrarLast() {
        if (!this->esVacia()) {
            if ((comienzo->getNext())->getNext() == NULL) {
                delete comienzo->getNext();
                comienzo->setNext(NULL);
            }
            else this->resto()->borrarLast();
        }
    }
};
#endif