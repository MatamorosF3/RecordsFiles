#include "arbolbnodo.h"
//ArbolBNodo::ArbolBNodo(){}
ArbolBNodo::~ArbolBNodo(){
    //delete [] llave;

    for(int i=0;i<t;i++){
        delete [] c[i];
    }
    delete [] c;
}
ArbolBNodo::ArbolBNodo(int t1, bool hoja)
{
    this->t=t1;
    this->hoja=hoja;
    llaves =new llave [2*this->t-1];

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
    while (i < this->n && k > llaves[i].llave1)
        i++;

    if(llaves[i].llave1 ==k){
        this->llaves->llave1 = llaves[i].llave1;
        this->llaves->pos= llaves[i].pos;
        return this;
    }

    if(this->hoja==true){
       return '\0';
    }
    //ir al hijo apropiado
    return this->c[i]->buscar(k);

}

void ArbolBNodo::agregarNoLleno(int k,int p){
    int i=this->n-1;

    if (hoja){

        while (i >= 0 && this->llaves[i].llave1 > k){
            this->llaves[i+1].llave1=this->llaves[i].llave1;
            this->llaves[i+1].pos=this->llaves[i].pos;
            i--;
        }

        this->llaves[i+1].llave1=k;
        this->llaves[i+1].pos=p;
        this->n=this->n+1;

    }else{//si el nodo no es hoja
        while(i>=0 && this->llaves[i].llave1 >k)
            i--;
        if(this->c[i+1]->n == 2*this->t-1){
            partirHijo(i+1, this->c[i+1]);

            if(this->llaves[i+1].llave1 <k)
                i++;
        }
        this->c[i+1]->agregarNoLleno(k,p);
    }
}


void ArbolBNodo::partirHijo(int i, ArbolBNodo* y){
    ArbolBNodo* z = new ArbolBNodo(y->t, y->hoja);
    z->n=t-1;

    for(int j=0; j<t-1; j++){

        z->llaves[j].llave1=y->llaves[j+t].llave1;
        z->llaves[j].pos=y->llaves[j+t].pos;
    }

    if(!y->hoja){
        for(int j=0; j<this->t; j++)
            z->c[j]= y->c[j+t];
    }

    y->n=this->t-1;//reduce el # de llaves en y

    for(int j=this->n;j>=i+1;j--)
        this->c[j+1]=this->c[j];


    this->c[i+1]=z;//enlaza el nueco hijo al nodo


    for(int j=this->n-1; j>=i; j--){
        this->llaves[j+1].llave1=this->llaves[j].llave1;
        this->llaves[j+1].pos=this->llaves[j].pos;
    }

    this->llaves[i].llave1=y->llaves[this->t-1].llave1;
    this->llaves[i].pos=y->llaves[this->t-1].pos;
    this->n=this->n+1;

}
