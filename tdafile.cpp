#include "tdafile.h"
#include <QDebug>

TDAFile::TDAFile(){
    fileName = "";
}

TDAFile::TDAFile(const string & filename, ios_base::openmode mode ){
    //this->fileName = filename;
    //this->fileStream.open(filename.c_str(),mode);
    this->fileStream.open(filename.c_str(),ios_base::in | ios_base::out);

}

TDAFile::~TDAFile(){
}

bool TDAFile::open(const string& filename, ios_base::openmode mode){
    this->fileName = filename;
    this->fileStream.open(filename.c_str(),mode);
    /*this->fileStream.open(f.c_str(),fstream::in |fstream::out);
    if(!fileStream.is_open()){//Se crea el archivo y se le escribe un espacio, ya que si no tiene un byte tiene problemas al momento de escribir
            fileStream.open(fileName.c_str(),fstream::out);
            fileStream.write(" ",1);
            fileStream.flush();
            fileStream.close();
            fileStream.open(f.c_str(), fstream::in | fstream::out);
        }
        if (fileStream.is_open())
            return true;//si no hubo problemas, signiica que esta abierto el archivo

        return false;//No se pudo abrir el archivo
*/
    if(!this->fileStream.is_open())
        return false;
    return true;

}

bool TDAFile::is_open()const{
    if(!this->fileStream.is_open())
        return false;

    return true;
}

void TDAFile::close(){
    this->fileStream.close();
}

int TDAFile::read(char * buffer, streamsize size){

    this->fileStream.read(buffer,size);

    if (this->isOK() != 0)
        return -1;

    return 0;

}

int TDAFile::write(const char * buffer, streamsize size){
    this->fileStream.write(buffer,size);

    if(this->isOK() != 0)
        return -1;

    return 0;
}

int TDAFile::isOK(){
    if(this->fileStream.rdstate() == ios::failbit)
        return 1;

    if(this->fileStream.rdstate() == ios::badbit)
        return 2;

    return 0;
}

int TDAFile::tell(){
    return fileStream.tellg();
}

void TDAFile::seek(int pos){
    this->fileStream.seekg(pos);
    this->fileStream.seekp(pos);
}


void TDAFile::seek(ios::seekdir mode){
    this->fileStream.seekg(0,mode);
    this->fileStream.seekp(0,mode);
}


bool TDAFile::isEOF(){
    return this->fileStream.eof();
}

void TDAFile::flush(){
    this->fileStream.flush();
}
