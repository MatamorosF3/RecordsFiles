#ifndef ARBOLB_H
#define ARBOLB_H
#include "arbolbnodo.h"

class ArbolB
{
    ArbolBNodo* raiz;
    int t;
public:
    ArbolB();
    ArbolB(int);
    void recorrer();
    ArbolBNodo* buscar(int);
    ArbolBNodo* getRaiz();
    int getT();
    void insertar(int,int);
};

#endif // ARBOLB_H
