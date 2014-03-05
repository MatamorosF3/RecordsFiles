#include "catfile.h"
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include <QDebug>
Catfile::Catfile()
{

}


int Catfile::readrecord( char* rec, int offset){

    this->open("Categories.txt",ios_base::in);
    this->seek(offset);
    this->read(rec,24);
    this->close();
    if(offset == 0){
        this->open("AvailCat.txt",ios_base::in | ios_base::out);
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
                AvailCat.push_back(number);
                numero = "";
            }
        }
        this->close();
    }
    return 0;
}
//OJO
int Catfile::writerecord(const char *buffer, int ind){
    this->open("Categories.txt",ios_base::in | ios_base::out);
    if(ind == 1){
        this->seek(0);
    }
    if(ind != 1){
        ind--;
        this->seek(ind*24);
    }

    this->write(buffer,24);
    this->close();
    return 0;
}

int Catfile::findrecord(int id){
    /*TDAFile f;
    f.open("Categories.txt",ios::in);
    int i=0,idd=-1;
    while(!f.isEOF()){
        f.seek(24*i);
        char [24] buffer;
        f.read(buffer,24);
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

int Catfile::findrecord(const char* rec,int ind){

    return 0;
}

void Catfile::seek(int ind){
    TDAFile::seek(ind);

}

void Catfile::seek(ios::seekdir mode)
{
    TDAFile::seek(mode);
}

int Catfile::tell(){

    return TDAFile::tell();

}

int Catfile::eraserecord(int ind){
    AvailCat.push_back(ind);
    this->open("Categories.txt",ios_base::in | ios_base::out);
    if(ind == 1){
        this->seek(0);
        // this->seek(0);
    }
    if(ind != 1){
        ind--;
        this->seek(ind*24);
        //this->seek(ind*24);
    }

    if(!AvailCat.empty())
        qDebug() << " agrego al AvailCat list, no esta vacia la lista";
    char asterisco [] = "*";
    this->write(asterisco,1);
    this->close();
    return 0;
}

int Catfile::updaterecord(const char* rec, int ind){
    this->open("Categories.txt",ios_base::in | ios_base::out);
    if(ind == 1){
        this->seek(0);
    }
    if(ind != 1){
        ind--;
        this->seek(ind*24);
    }

    this->write(rec,24);
    this->close();
    return 0;
}

int Catfile::recordsSize()
{
    this->open("Categories.txt");
    this->seek(ios_base::end);
    int tel = this->tell();
    this->close();
    return tel;

}

int Catfile::updateAvailCat()
{
    this->open("AvailCat.txt",ios_base::out);

    for (std::list<int>::iterator it=AvailCat.begin() ; it != AvailCat.end(); ++it){
        char ft[ (strlen(QString::number(*it).toStdString().c_str())) +2];
        ft[sizeof(ft) -1] = '\0';
        strcpy(ft,QString::number(*it).toStdString().c_str());
        ft[sizeof(ft) - 2] = '\n';
        this->write(ft,(sizeof(ft)) - 1);
    }

    this->close();

}



