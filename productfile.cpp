#include "productfile.h"
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include <QDebug>
#include <stdio.h>

ProductFile::ProductFile()
{
}
int ProductFile::readrecord( char* rec, int offset){

    this->open("Productos.txt",ios_base::in);
    this->seek(offset);
    this->read(rec,36);
    this->close();
    if(offset == 0){
        this->open("AvailProductos.txt",ios_base::in | ios_base::out);
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
                avail.push_back(number);
                numero = "";
            }
        }
        this->close();
    }
    return 0;
}
//OJO
int ProductFile::writerecord(const char *buffer, int ind){
    this->open("Productos.txt",ios_base::in | ios_base::out);
    if(ind == 1){
        this->seek(0);
    }
    if(ind != 1){
        ind--;
        this->seek(ind*36);
    }

    this->write(buffer,36);
    this->close();
    return 0;
}

int ProductFile::findrecord(int id){
    /*TDAFile f;
    f.open("Productos.txt",ios::in);
    int i=0,idd=-1;
    while(!f.isEOF()){
        f.seek(36*i);
        char [36] buffer;
        f.read(buffer,36);
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
    return idd;*/
}

int ProductFile::findrecord(char* rec,int ind){

    return 0;
}

void ProductFile::seek(int ind){
    TDAFile::seek(ind);

}

void ProductFile::seek(ios::seekdir mode)
{
    TDAFile::seek(mode);
}

int ProductFile::tell(){

    return TDAFile::tell();

}

int ProductFile::eraserecord(int ind){
    avail.push_back(ind);
    this->open("Productos.txt",ios_base::in | ios_base::out);
    if(ind == 1){
        this->seek(0);
        // this->seek(0);
    }
    if(ind != 1){
        ind--;
        this->seek(ind*36);
        //this->seek(ind*36);
    }

    if(!avail.empty())
        qDebug() << " agrego al avail list, no esta vacia la lista";
    char asterisco [] = "*";
    this->write(asterisco,1);
    this->close();
    return 0;
}

int ProductFile::updaterecord(const char* rec, int ind){
    this->open("Productos.txt",ios_base::in | ios_base::out);
    if(ind == 1){
        this->seek(0);
    }
    if(ind != 1){
        ind--;
        this->seek(ind*36);
    }

    this->write(rec,36);
    this->close();

    return 0;
}

int ProductFile::recordsSize()
{
    this->open("Productos.txt");
    this->seek(ios_base::end);
    int tel = this->tell();
    this->close();
    return tel;

}

int ProductFile::updateAvail()
{    
    if(!avail.empty()){

        this->open("AvailProductos.txt",ios_base::out);

        for (std::list<int>::iterator it=avail.begin() ; it != avail.end(); ++it){
            char ft[ (strlen(QString::number(*it).toStdString().c_str())) +2];
            ft[sizeof(ft) -1] = '\0';
            strcpy(ft,QString::number(*it).toStdString().c_str());
            ft[sizeof(ft) - 2] = '\n';
            this->write(ft,(sizeof(ft)) - 1);
        }

        this->close();
    }else{
        remove("AvailProductos.txt");
        this->open("AvailProductos.txt",ios_base::out);
        this->close();
    }
}



