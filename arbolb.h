#ifndef ARBOLB_H
#define ARBOLB_H
#include "arbolbnodo.h"

class ArbolB
{
    ArbolBNodo* raiz;
    int t;
public:
    ArbolB(int);
    void recorrer();
    ArbolBNodo* buscar(int);
    void insertar(int);
};

#endif // ARBOLB_H
