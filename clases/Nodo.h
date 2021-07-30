#ifndef NODO_H
#define NODO_H

template <class T> class Nodo {
private:
    T dato;
    Nodo* next;

public:
    Nodo() { next = NULL; }
    Nodo(T a) { dato = a; next = NULL;}
    ~Nodo(){};
    void setDato(T a) { dato = a; }
    void setNext(Nodo* n) { next = n; }
    T getDato() { return dato; }
    Nodo* getNext() { return next; }
    bool esVacio() { return (next == NULL); }
};


#endif
