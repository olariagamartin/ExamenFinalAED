#ifndef COLA_H
#define COLA_H
#include "Lista.h"
template <class T> class Cola: public Lista<T> {
public:
    Cola() { Lista<T>(); }
    T tope() { return this->last();	}
    bool colaVacia() { return this->esVacia(); }
    void encolar(T a) { this->add(a); }
    void desencolar() { this->borrarLast();	}
    T ultimo() { return this->cabeza();	}
    Cola* restoCola(){
        Cola* colaNueva = new Cola();
        colaNueva->concat(this);
        colaNueva->desencolar();
        return colaNueva;
    }
};
#endif