#ifndef ARBOLBNODO_H
#define ARBOLBNODO_H

class ArbolBNodo
{


    int t;  //minimo de ramas en un nodo
    ArbolBNodo **c; //arreglo de hijos punteros
    int n;  //llaves actuales

    bool hoja;//si es hoja
public:
    struct llave{//structura de nuestra llave que contiene llave y offset
        int llave1;
        int pos;
    };
    llave* llaves;//arreglo de llaves
    ArbolBNodo(int, bool); //constructor del nodo
    ~ArbolBNodo();//destructor
    void agregarNoLleno(int,int); //agrega una llave al nodo que no esta lleno
    void partirHijo(int, ArbolBNodo*); //parte el nodo si este esta lleno
    void recorrer();//recorre los nodos en un subarbol
    ArbolBNodo* buscar(int); //busca la llave deseada
    int* getPosicion();//devuelve el offset
    friend class ArbolB; //hacemos la clase ArbolB amiga para que podamos accesar a los

};

#endif // ARBOLBNODO_H
