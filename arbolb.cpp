#include "arbolb.h"
#include "arbolbnodo.h"

ArbolB::ArbolB(){}
ArbolB::ArbolB(int t){//constructor del arbol lo inicializa vacio

        this->raiz = '\0';//la raiz de inicializa en NULL ya que esta vacia
        this->t = t; //
    }
void ArbolB::recorrer(){//metodo recorrer el nodo
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

void ArbolB::insertar(int k,int p){//inserta una nueva llave en el arbol
    if (this->raiz=='\0'){//si la raiz esta vacia

        this->raiz=new ArbolBNodo(t,true);//Se crea el nodo raiz
        this->raiz->llaves[0].llave1 = k;
        this->raiz->llaves[0].pos=p;
        this->raiz->n=1;// se actualiza el numero de llaves
    }else{//si el arbol no esta vaciio
        if(this->raiz->n == 2*t-1){//si el nodo esta lleno, entonces se le quiebra el nodo
             ArbolBNodo* s =new ArbolBNodo(t,false); //se crea el nueno nodo

             s->c[0]=this->raiz; //cambianos al nuevo nodo raiz

             s->partirHijo(0,this->raiz);//partimos el nodo y se mueve una llave al nuevo nodo

             //el nodo tiene dos hijos ahora se inserta la llave
             int i=0;
             if (s->llaves[0].llave1 < k)
                 i++;
             s->c[i]->agregarNoLleno(k,p);

             this->raiz=s;//se actualiza la raiz
        }else //si el nodo no esta lleno
            this->raiz->agregarNoLleno(k,p);
    }

}


