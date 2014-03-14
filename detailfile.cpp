#include "detailfile.h"
#include <stdio.h>

detailfile::detailfile()
{
}

int detailfile::readrecord( char* rec, int offset){

    this->open(path.toStdString().c_str(),ios_base::in);
    this->seek(offset);
    this->read(rec,12);

    // otra forma de leer los archivos
    /*this->read((char*)&cliente,84);
    cliente.id[4] = '\0';
    cliente.correo[38] = '\0';
    cliente.nombre[38] = '\0';
    */


    this->close();



    return 0;
}
//OJO
int detailfile::writerecord(const char *buffer, int ind){
    this->open(path.toStdString().c_str(),ios_base::in | ios_base::out);
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

int detailfile::findrecord(int id){
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
    return 0;
}

int detailfile::findrecord(char* rec,int ind){

    this->open(path.toStdString().c_str(),ios_base::in);
     if(ind<1){
        this->seek(ind);
    }else{
        ind--;
        this->seek(ind*12);
    }
    this->read(rec,12);
    this->close();
    return 0;
}

void detailfile::seek(int ind){
    TDAFile::seek(ind);

}

void detailfile::seek(ios::seekdir mode)
{
    TDAFile::seek(mode);
}

int detailfile::tell(){

    return TDAFile::tell();

}

int detailfile::eraserecord(int ind){
    this->open(path.toStdString().c_str(),ios_base::in | ios_base::out);
    if(ind == 1){
        this->seek(0);
    }
    if(ind != 1){
        ind--;
        this->seek(ind*12);
    }

    char asterisco [] = "*";
    this->write(asterisco,1);
    this->close();
    return 0;
}

int detailfile::updaterecord(const char* rec, int ind){
    this->open(path.toStdString().c_str(),ios_base::in | ios_base::out);
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

int detailfile::recordsSize()
{
    this->open(path.toStdString().c_str());
    this->seek(ios_base::end);
    int tel = this->tell();
    this->close();
    return tel;

}

