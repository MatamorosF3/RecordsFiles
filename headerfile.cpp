#include "headerfile.h"

headerfile::headerfile()
{
}

int headerfile::readrecord( char* rec, int offset){

    this->open(path.toStdString().c_str(),ios_base::in);
    this->seek(offset);
    this->read(rec,25);

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
int headerfile::writerecord(const char *buffer, int ind){
    this->open(path.toStdString().c_str(),ios_base::in | ios_base::out);
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

int headerfile::findrecord(int id){
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

int headerfile::findrecord(char* rec,int ind){

    this->open(path.toStdString().c_str(),ios_base::in);
     if(ind<1){
        this->seek(ind);
    }else{
        ind--;
        this->seek(ind*84);
    }
    this->read(rec,84);
    this->close();
    return 0;
}

void headerfile::seek(int ind){
    TDAFile::seek(ind);

}

void headerfile::seek(ios::seekdir mode)
{
    TDAFile::seek(mode);
}

int headerfile::tell(){

    return TDAFile::tell();

}

int headerfile::eraserecord(int ind){
    //avail.push_back(ind);
    this->open(path.toStdString().c_str(),ios_base::in | ios_base::out);
    if(ind == 1){
        this->seek(0);
    }
    if(ind != 1){
        ind--;
        this->seek(ind*84);
    }

    char asterisco [] = "*";
    this->write(asterisco,1);
    this->close();
    return 0;
}

int headerfile::updaterecord(const char* rec, int ind){
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

int headerfile::recordsSize()
{
    this->open(path.toStdString().c_str());
    this->seek(ios_base::end);
    int tel = this->tell();
    this->close();
    return tel;

}





