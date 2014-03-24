#ifndef ARBOLB_H
#define ARBOLB_H
#include "arbolbnodo.h"

class ArbolB
{
    ArbolBNodo* raiz;//el nodo raiz del arbol!
    int t;//el minimo ramas en un nodo
public:
    ArbolB();
    ArbolB(int);//inicializa arbol vacio
    void recorrer();
    ArbolBNodo* buscar(int);
    ArbolBNodo* getRaiz();
    int getT();
    void insertar(int,int);
    int* getPosocion();
};

#endif // ARBOLB_H
