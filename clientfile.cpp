#include "clientfile.h"
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include <QDebug>
ClientFile::ClientFile()
{

}


int ClientFile::readrecord( char* rec, int offset){

    this->open("Clientes.txt",ios_base::in);
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
                avail.push_back(number);
                numero = "";
            }
        }
        this->close();
    }


    return 0;
}
//OJO
int ClientFile::writerecord(const char *buffer, int ind){
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

int ClientFile::findrecord(int id){
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
    return idd;*/
}

int ClientFile::findrecord(const char* rec,int ind){

    return 0;
}

void ClientFile::seek(int ind){
    TDAFile::seek(ind);

}

void ClientFile::seek(ios::seekdir mode)
{
    TDAFile::seek(mode);
}

int ClientFile::tell(){

    return TDAFile::tell();

}

int ClientFile::eraserecord(int ind){
    avail.push_back(ind);
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

    if(!avail.empty())
        qDebug() << " agrego al avail list, no esta vacia la lista";
    char asterisco [] = "*";
    this->write(asterisco,1);
    this->close();
    return 0;
}

int ClientFile::updaterecord(const char* rec, int ind){
    this->open("Clientes.txt",ios_base::in | ios_base::out);
    if(ind == 1){
        this->seek(0);
    }
    if(ind != 1){
        ind--;
        this->seek(ind*84);
    }

    this->write(rec,84);
    this->close();
    return 0;
}

int ClientFile::recordsSize()
{
    this->open("Clientes.txt");
    this->seek(ios_base::end);
    int tel = this->tell();
    this->close();
    return tel;

}

int ClientFile::updateAvail()
{
    this->open("Avail.txt",ios_base::out);

    for (std::list<int>::iterator it=avail.begin() ; it != avail.end(); ++it){
        char ft[ (strlen(QString::number(*it).toStdString().c_str())) +2];
        ft[sizeof(ft) -1] = '\0';
        strcpy(ft,QString::number(*it).toStdString().c_str());
        ft[sizeof(ft) - 2] = '\n';
        this->write(ft,(sizeof(ft)) - 1);
    }

    this->close();

}



