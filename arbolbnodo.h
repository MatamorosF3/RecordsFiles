#ifndef ARBOLBNODO_H
#define ARBOLBNODO_H

class ArbolBNodo
{


    int t;//minimo de llaves
    ArbolBNodo **c;
    int n;//llave actual

    bool hoja;//si es hoja
public:
    struct llave{
        int llave1;
        int pos;
    };
    llave* llaves;
    ArbolBNodo(int, bool);
    ~ArbolBNodo();
    void agregarNoLleno(int,int);
    void partirHijo(int, ArbolBNodo*);
    void recorrer();
    ArbolBNodo* buscar(int k);
    int* getPosicion();
    friend class ArbolB;
};

#endif // ARBOLBNODO_H
