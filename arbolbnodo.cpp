#include "arbolbnodo.h"


ArbolBNodo::ArbolBNodo(int t1, bool hoja)
{
    this->t=t1;
    this->hoja=hoja;
    this->llave=new int [2*this->t-1];
    this->c= new ArbolBNodo* [2*t];
    this->n=0;
}

void ArbolBNodo::recorrer()
{
    int i;
    for(i=0;i<this->n;i++){
        if(!this->hoja)
            this->c[i]->recorrer();
    }
   if(!this->hoja)
       this->c[i]->recorrer();
}

ArbolBNodo* ArbolBNodo::buscar(int k){
    int i=0;
    while (i < this->n && this->llave[i])
        i++;

    if(this->llave[i] ==k)
        return this;

    if(hoja){
       return '\0';
    }
    //ir al hijo apropiado
    return this->c[i]->buscar(k);

}

void ArbolBNodo::agregarNoLleno(int k){
    int i=this->n-1;

    if (hoja){

        while (i>=0 && this->llave[i] >k){
            this->llave[i+1]=this->llave[i];
            i--;
        }

        this->llave[i+1]=k;
        this->n=this->n+1;
    }else{//si el nodo no es hoja
        while(i>=0 && this->llave[i] >k)
            i--;
        if(this->c[i+1]->n == 2*this->t-1){
            partirHijo(i+1, this->c[i+1]);

            if(this->llave[i+1] <k)
                i++;
        }
        this->c[i+1]->agregarNoLleno(k);
    }
}


void ArbolBNodo::partirHijo(int i, ArbolBNodo* y){
    ArbolBNodo* z = new ArbolBNodo(y->t, y->hoja);
    z->n=t-1;

    for(int j=0; j<t-1; j++)
        z->llave[j]=y->llave[j+t];

    if(!y->hoja){
        for(int j=0; j<this->t; j++)
            z->c[j]= y->c[j+t];
    }

    y->n=this->t-1;//reduce el # de llaves en y

    for(int j=this->n;j>=i+1;j--)
        this->c[j+1]=this->c[j];


    this->c[i+1]=z;//enlaza el nueco hijo al nodo


    for(int j=this->n-1; j>=i; j--)
        this->llave[j+1]=this->llave[j];

    this->llave[i]=y->llave[this->t-1];
    this->n=this->n+1;

}
