#include "linearindexfile.h"
#include <QString>
#include <qDebug>
#include <algorithm>
#include <stdio.h>

LinearIndexFile::LinearIndexFile()
{}
int LinearIndexFile::readrecord( char* rec, int offset){return 0;}
int LinearIndexFile::readrecord(QString filename){
    this->open(filename.toStdString().c_str() ,ios_base::in);
    char buffer[12];
    int cont=0;
    while(!this->isEOF()){
        this->seek(cont);
        this->read(buffer,11);
        buffer[11]='\0';
        QString sLlave="";
        QString sOffset="";
        for(int i=0;i<4;i++){
            sLlave.append(buffer[i]);
        }
        for(int i=5;i<11;i++){
            sOffset.append(buffer[i]);
        }
        indice temp;
        temp.llave=atoi(sLlave.toStdString().c_str());
        temp.offset=atoi(sOffset.toStdString().c_str());
        indices.push_back(temp);
        cont+=11;
    }
    this->close();
    return 0;
}
//OJO
int LinearIndexFile::writerecord(const char *buffer, int ind){
    indice temp;
    temp.llave=ind;
    ind--;
    temp.offset=84*ind;
    indices.push_back(temp);
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
    return idd;*/
    return 0;
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
    for(int i=0;i<indices.size();i++){
        if(((indice)indices.at(i)).llave==ind){
            indices.erase(indices.begin()+i);
        }
    }
    return 0;
}

int LinearIndexFile::updaterecord(const char* rec, int ind){return 0;}
int LinearIndexFile::updaterecord(QString filename){
    if(tamanioInicial!=indices.size()){
        remove(filename.toStdString().c_str());
        this->open(filename.toStdString().c_str(),ios_base::out);
        int cont=0;
        for(int i=0;i<indices.size();i++){
            indice temp;
            temp.llave=((indice)indices.at(i)).llave;
            temp.offset=((indice)indices.at(i)).offset;
            QString sLlave;
            QString sOffset;
            //inicio llave
            if(temp.llave<10){
                sLlave="000 ";
                sLlave.replace(3,strlen(QString::number(temp.llave).toStdString().c_str()),QString::number(temp.llave));
            }else if(temp.llave<100){
                sLlave="00  ";
                sLlave.replace(2,strlen(QString::number(temp.llave).toStdString().c_str()),QString::number(temp.llave));
            }else if(temp.llave<1000){
                sLlave="0   ";
                sLlave.replace(1,strlen(QString::number(temp.llave).toStdString().c_str()),QString::number(temp.llave));
            }else{
                sLlave="    ";
                sLlave.replace(0,strlen(QString::number(temp.llave).toStdString().c_str()),QString::number(temp.llave));
            }
            //fin llave
            //inicio offset
            if(temp.offset<10){
                sOffset="00000 ";
                sOffset.replace(5,strlen(QString::number(temp.offset).toStdString().c_str()),QString::number(temp.offset));
            }else if(temp.offset<100){
                sOffset="0000  ";
                sOffset.replace(4,strlen(QString::number(temp.offset).toStdString().c_str()),QString::number(temp.offset));
            }else if(temp.offset<1000){
                sOffset="000   ";
                sOffset.replace(3,strlen(QString::number(temp.offset).toStdString().c_str()),QString::number(temp.offset));
            }else if(temp.offset<10000){
                sOffset="00    ";
                sOffset.replace(2,strlen(QString::number(temp.offset).toStdString().c_str()),QString::number(temp.offset));
            }else if(temp.offset<100000){
                sOffset="0     ";
                sOffset.replace(1,strlen(QString::number(temp.offset).toStdString().c_str()),QString::number(temp.offset));
            }else{
                sOffset="      ";
                sOffset.replace(0,strlen(QString::number(temp.offset).toStdString().c_str()),QString::number(temp.offset));
            }
            //fin offset
            QString sInd="";
            sInd.append(sLlave);
            sInd.append(" ");
            sInd.append(sOffset);
            qDebug() << "sInd:" << sInd;
            this->write(sInd.toStdString().c_str(),11);
            cont+=11;
            sInd.clear();
        }
        this->close();
        qDebug() << "generar nuevo archivo";
    }//fin if

    return 0;
}
int LinearIndexFile::recordsSize(){return 0;}
int LinearIndexFile::recordsSize(QString filename)
{
    this->open(filename.toStdString().c_str());
    this->seek(ios_base::end);
    int tel = this->tell();
    this->close();
    return tel;

}
