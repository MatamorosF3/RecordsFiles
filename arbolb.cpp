#include "arbolb.h"
#include "arbolbnodo.h"

ArbolB::ArbolB(){}
ArbolB::ArbolB(int t){

        this->raiz = '\0';
        this->t = t;
    }
void ArbolB::recorrer(){
    if(this->raiz!='\0')
        this->raiz->recorrer();

}
ArbolBNodo* ArbolB::getRaiz(){
    return this->raiz;
}

int ArbolB::getT(){
    return this->t;
}

ArbolBNodo* ArbolB::buscar(int k){
    /*if(this->raiz=='\0')
        return '\0';
    else
        return this->raiz->buscar(k);*/
    return (this->raiz == '\0')? '\0' : this->raiz->buscar(k);
}

void ArbolB::insertar(int k,int p){
    if (this->raiz=='\0'){

        this->raiz=new ArbolBNodo(t,true);
        this->raiz->llaves[0].llave1 = k;
        this->raiz->llaves[0].pos=p;
        this->raiz->n=1;
    }else{
        if(this->raiz->n == 2*t-1){
             ArbolBNodo* s =new ArbolBNodo(t,false);

             s->c[0]=this->raiz;
             s->partirHijo(0,this->raiz);

             int i=0;
             if (s->llaves[0].llave1 < k)
                 i++;
             s->c[i]->agregarNoLleno(k,p);

             this->raiz=s;
        }else
            this->raiz->agregarNoLleno(k,p);
    }

}


