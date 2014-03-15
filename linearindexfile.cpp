#include "linearindexfile.h"
#include <QString>
#include <qDebug>
#include <algorithm>
#include <stdio.h>

LinearIndexFile::LinearIndexFile()
{}
int LinearIndexFile::readrecord( char* rec, int offset){return 0;}
int LinearIndexFile::readrecord(QString filename){

    int c = recordsSize(filename);
    this->open(filename.toStdString().c_str() ,ios_base::in);
    char buffer[12];
    int cont=0;
    while(cont < c){
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

        indices2.insert(atoi(sLlave.toStdString().c_str()),atoi(sOffset.toStdString().c_str()));
        cont+=11;
    }
    this->close();
    return 0;
}
//OJO
int LinearIndexFile::writerecord(const char *buffer, int ind){
    int key = ind;
    if(ind < 1)
        ind--;
    // indices2.insert(key,84*ind);
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

int LinearIndexFile::findrecord(char* rec,int ind){

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

    indices2.remove(ind);
    return 0;
}

int LinearIndexFile::updaterecord(const char* rec, int ind){return 0;}
int LinearIndexFile::updaterecord(QString filename){
    if(tamanioInicial!=indices2.size()){
        remove(filename.toStdString().c_str());
        this->open(filename.toStdString().c_str(),ios_base::out);
        qDebug() << "Creo archivo de indice";
        int cont=0;

        for (QMap<int,int>::iterator it=indices2.begin(); it!=indices2.end(); ++it){

            QString sLlave;
            QString sOffset;
            //inicio llave
            if(it.key()<10){
                sLlave="000 ";
                sLlave.replace(3,strlen(QString::number(it.key()).toStdString().c_str()),QString::number(it.key()));
            }else if(it.key()<100){
                sLlave="00  ";
                sLlave.replace(2,strlen(QString::number(it.key()).toStdString().c_str()),QString::number(it.key()));
            }else if(it.key()<1000){
                sLlave="0   ";
                sLlave.replace(1,strlen(QString::number(it.key()).toStdString().c_str()),QString::number(it.key()));
            }else{
                sLlave="    ";
                sLlave.replace(0,strlen(QString::number(it.key()).toStdString().c_str()),QString::number(it.key()));
            }
            //fin llave
            //inicio offset
            if(it.value()<10){
                sOffset="00000 ";
                sOffset.replace(5,strlen(QString::number(it.value()).toStdString().c_str()),QString::number(it.value()));
            }else if(it.value()<100){
                sOffset="0000  ";
                sOffset.replace(4,strlen(QString::number(it.value()).toStdString().c_str()),QString::number(it.value()));
            }else if(it.value()<1000){
                sOffset="000   ";
                sOffset.replace(3,strlen(QString::number(it.value()).toStdString().c_str()),QString::number(it.value()));
            }else if(it.value()<10000){
                sOffset="00    ";
                sOffset.replace(2,strlen(QString::number(it.value()).toStdString().c_str()),QString::number(it.value()));
            }else if(it.value()<100000){
                sOffset="0     ";
                sOffset.replace(1,strlen(QString::number(it.value()).toStdString().c_str()),QString::number(it.value()));
            }else{
                sOffset="      ";
                sOffset.replace(0,strlen(QString::number(it.value()).toStdString().c_str()),QString::number(it.value()));
            }
            //fin offset
            QString sInd="";
            sInd.append(sLlave);
            sInd.append(" ");
            sInd.append(sOffset);
            this->write(sInd.toStdString().c_str(),11);
            cont+=11;
            sInd.clear();
        } // fin for
        this->close();
    }//fin if para volver a generar archivo de indice

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
