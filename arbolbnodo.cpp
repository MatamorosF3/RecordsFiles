#include "arbolbnodo.h"
//ArbolBNodo::ArbolBNodo(){}

ArbolBNodo::ArbolBNodo(int t1, bool hoja)//constructor del nodo
{
    this->t=t1;//se copia el minimo de ramas
    this->hoja=hoja;//asigna si es hoja o no

    llaves =new llave [2*this->t-1];//asigna el maximo numero de llaves

    this->c= new ArbolBNodo* [2*t];//asigna el maximo numero de hijos punteros
    this->n=0;//no hay llaves en el arbol

}

void ArbolBNodo::recorrer()
{
    //ya que hay n llaves y n+1 llaves, recorre por n llaves
    int i;
    for(i=0;i<this->n;i++){        
        //mientras no sea hoja recorre el subarbolito con la raiz c[i]
        if(!this->hoja)
             this->c[i]->recorrer();
    }

    if(!this->hoja)
        this->c[i]->recorrer();
}


ArbolBNodo* ArbolBNodo::buscar(int k){//busca la llave
    int i=0;//busca la llave mayor a K
    while (i < this->n && k > llaves[i].llave1)
        i++;
    //si la llave es igual a K, que retorne este nodo
    if(llaves[i].llave1 ==k){
        this->llaves->llave1 = llaves[i].llave1;
        this->llaves->pos= llaves[i].pos;
        return this;
    }
    //si la llave no se encontro y llego a una hoja retornar NULL
    if(this->hoja==true){
       return '\0';
    }
    //ir al hijo apropiado, que siga buscando
    return this->c[i]->buscar(k);

}

void ArbolBNodo::agregarNoLleno(int k,int p){//agrega cuando el nodo no esta lleno
    int i=this->n-1;//llevamos a i a la llave mas a la derecha

    if (hoja){
            //encontramos un lugar para insertar nueva llave
            //tambien se mueven las llaven mayores hacia un lado
        while (i >= 0 && this->llaves[i].llave1 > k){
            this->llaves[i+1].llave1=this->llaves[i].llave1;
            this->llaves[i+1].pos=this->llaves[i].pos;
            i--;
        }
        //agreagar la nueva llave en el lugar encontrado
        this->llaves[i+1].llave1=k;
        this->llaves[i+1].pos=p;
        this->n=this->n+1;

    }else{//si el nodo no es hoja
        //encontramos el hijo que donde se va a poner la nueva llave
        while(i>=0 && this->llaves[i].llave1 > k)
            i--;
        if(this->c[i+1]->n == 2*this->t-1){//mira se el nodo encontrado esta lleno
            partirHijo(i+1, this->c[i+1]);//como esta llleno lo partimos
            //despues que se parte, la llave de enmedio de c[1] va arriba y c[1] se divide

            if(this->llaves[i+1].llave1 <k)//a donde vamos a meter la llave
                i++;
        }
        this->c[i+1]->agregarNoLleno(k,p);//insertamos la llave
    }
}


void ArbolBNodo::partirHijo(int i, ArbolBNodo* y){//parte el nodo Y que esta lleno
    //se crea el nodo el cual va a tener t-1 llavez
    ArbolBNodo* z = new ArbolBNodo(y->t, y->hoja);
    z->n=t-1;

    for(int j=0; j<t-1; j++){//copia el la ultima llave (t-1) de Y a Z
        z->llaves[j].llave1=y->llaves[j+t].llave1;
        z->llaves[j].pos=y->llaves[j+t].pos;
    }

    //copia el ultimo hijo t(rama) de Y a Z
    if(!y->hoja){
        for(int j=0; j<this->t; j++)
            z->c[j]= y->c[j+t];
    }


    y->n=this->t-1;//se reduce el # de llaves en Y

    for(int j=this->n;j>=i+1;j--)//ya que este nodo va a tener nuevo hijo tambien se crea espacio para eeste
        this->c[j+1]=this->c[j];


    this->c[i+1]=z;//enlaza el nuevo hijo al nodo

    //una llave de Y se va a mover a este nodo(this), entonces se encuentra el lugar de la nueva llave y mueve todas las llaves mayores hacia la derecha
    for(int j=this->n-1; j>=i; j--){
        this->llaves[j+1].llave1=this->llaves[j].llave1;
        this->llaves[j+1].pos=this->llaves[j].pos;
    }
    //copia la llave de enmedio de Y a este nodo(this)
    this->llaves[i].llave1=y->llaves[this->t-1].llave1;
    this->llaves[i].pos=y->llaves[this->t-1].pos;

    //Incremetamos el # de llaves en este nodo
    this->n=this->n+1;


}

ArbolBNodo::~ArbolBNodo(){//destructor del arbol
    for(int i=0;i<t;i++){
        delete [] c[i];
    }
    delete [] c;
}
