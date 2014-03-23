#ifndef ARBOLBNODO_H
#define ARBOLBNODO_H

class ArbolBNodo
{
    int *llave;
    int *posicion;
    int t;//minimo de llaves
    ArbolBNodo **c;
    int n;//llave actual
    //int pos;//posicion actual
    bool hoja;//si es hoja
public:
    int pos;//posicion actual
    ArbolBNodo();
    ArbolBNodo(int, bool);
    ~ArbolBNodo();
    void agregarNoLleno(int,int);
    void partirHijo(int, ArbolBNodo*);
    void recorrer();
    ArbolBNodo* buscar(int k);
    friend class ArbolB;
};

#endif // ARBOLBNODO_H
