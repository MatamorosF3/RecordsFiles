#ifndef ARBOLBNODO_H
#define ARBOLBNODO_H

class ArbolBNodo
{
    int *llave;
    int t;
    ArbolBNodo **c;
    int n;
    bool hoja;
public:
    ArbolBNodo(int, bool);
    void agregarNoLleno(int);
    void partirHijo(int, ArbolBNodo*);
    void recorrer();
    ArbolBNodo* buscar(int k);
    friend class ArbolB;
};

#endif // ARBOLBNODO_H
