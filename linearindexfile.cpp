#include "linearindexfile.h"

LinearIndexFile::LinearIndexFile()
{
}
/*
LinearIndexFile::LinearIndexFile()
{
    ClientFile cliente;
    cliente.path="Clientes.txt";
    cliente.seek(0);
    int cont=0;
    //while(!cliente.isEOF()){
        char buffer[5];
        cliente.read(buffer,4);
        buffer[4]='/0';
        indice ind;
        for(int i=0;i<4;i++){
            ind.llave[i]=buffer[i];
        }
        char* c;itoa(cont,ind.offset,10);
        //ind.offset=itoa(cont);
        ClientIndex.push_back(ind);
        cont+=84;
        cliente.seek(cont);
    //}
    for(int i=0;i<ClientIndex.size();i++){
        qDebug()<<"i: " << ((indice)ClientIndex.at(i)).llave[1] <<","<<((indice)ClientIndex.at(i)).offset[1];
    }

    TDAFile* fcli=new TDAFile("ClientesIndex.txt",ios_base::in);
    TDAFile* fcat=new TDAFile("CategoriasIndex.txt",ios_base::in);
    TDAFile* fprod=new TDAFile("ProductosIndex.txt",ios_base::in);
    //Leer desde el archivo BaseClientes.txt y colocarlo en el ClientFile
    char actual='k';//lo primero que lee es la llave
    stringstream ssllave,ssoffset;
    indice iActual;
    char caracter[1];
    while(!fcli->isEOF()){
        fcli->read(caracter,1);
        //cout<<caracter[0];
        if(caracter[0]=='\n'){
            strcpy(iActual.offset,(ssoffset.str()).c_str());
            iActual.offset[6]='\0';
            if(fcli->isEOF()){
                break;
            }else{
                ClientIndex.push_back(iActual);
            }
            actual='k';
            ssoffset.str("");
            continue;
        }
        if(caracter[0]==','){//Si encuentra una coma
            if(actual=='k'){//si estaba leyendo llave
                strcpy(iActual.llave,(ssllave.str()).c_str());
                iActual.llave[4]='\0';
                actual='l';
                ssllave.str("");
            }
            continue;
        }
        if(actual=='k'){
            ssllave<<caracter[0];

        }else if(actual=='l'){
            ssoffset<<caracter[0];
        }
    }
    fcli->close();
    //termina de leer del archivo ClientesIndex.txt

}
int LinearIndexFile::readrecord( char* rec, int offset,QString filename){

    this->open(filename,ios_base::in);
    this->seek(offset);
    this->read(rec,84);
    this->close();
    if(offset == 0){
        this->open("Avail.txt",ios_base::in | ios_base::out);
        char entero[2];
        string numero = "";
        int number;
        while(!this->isEOF()){
            this->read(entero,1);
            entero[1] = '\0';
            if(entero[0] != '\n')
                numero += entero[0];
            else{
                if((number = atoi(numero.c_str())) == 0)
                    break;
                //avail.push_back(number);
                numero = "";
            }
        }
        this->close();
    }


    return 0;
}
//OJO
int LinearIndexFile::writerecord(const char *buffer, int ind){
    this->open("Clientes.txt",ios_base::in | ios_base::out);
    if(ind == 1){
        this->seek(0);
    }
    if(ind != 1){
        ind--;
        this->seek(ind*84);
    }

    this->write(buffer,84);
    this->close();
    return 0;
}

int LinearIndexFile::findrecord(int id){
    /*TDAFile f;
    f.open("clientes.txt",ios::in);
    int i=0,idd=-1;
    while(!f.isEOF()){
        f.seek(84*i);
        char [84] buffer;
        f.read(buffer,84);
        buffer[83]='\0';
        string identidad="";
        stringstream ss;
        for(int j=0;j<4;j++){
            ss<<buffer[j];
        }
        identidad=ss.str();
        char * ide=identidad;
        idd=atoi(ide);
        if(id==idd){
            break;
        }
        i++;
    }
    return idd;
}

int LinearIndexFile::findrecord(const char* rec,int ind){

    return 0;
}

void LinearIndexFile::seek(int ind){
    TDAFile::seek(ind);

}

void LinearIndexFile::seek(ios::seekdir mode)
{
    TDAFile::seek(mode);
}

int LinearIndexFile::tell(){

    return TDAFile::tell();

}

int LinearIndexFile::eraserecord(int ind){
    //avail.push_back(ind);
    this->open("Clientes.txt",ios_base::in | ios_base::out);
    if(ind == 1){
        this->seek(0);
        // this->seek(0);
    }
    if(ind != 1){
        ind--;
        this->seek(ind*84);
        //this->seek(ind*84);
    }

    //if(!avail.empty())
    //qDebug() << " agrego al avail list, no esta vacia la lista";
    char asterisco [] = "*";
    this->write(asterisco,1);
    this->close();
    return 0;
}

int LinearIndexFile::updaterecord(const char* rec, int ind){
    this->open("Clientes.txt",ios_base::in | ios_base::out);
    if(ind == 1){
        this->seek(0);
    }
    if(ind != 1){

        this->seek(ind*84);
    }

    this->write(rec,84);
    this->close();
    return 0;
}

int LinearIndexFile::recordsSize()
{
    this->open("Clientes.txt");
    this->seek(ios_base::end);
    int tel = this->tell();
    this->close();
    return tel;

}*/
