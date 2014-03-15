#ifndef CLIENTFILE_H
#define CLIENTFILE_H
#include "tdafsrecordfile.h"
#include "linearindexfile.h"
#include <QString>

#include <list>
class ClientFile : public TDAFSRecordFile{

    struct Cliente{
        char id[5];
        char nombre[40];
        char correo[40];
    };

public:
    ClientFile();
    int readrecord(char*,int);
    int writerecord(const char*,int ind);
    int findrecord(int);
    int findrecord(char*,int);
    void seek(int);
    void seek(ios::seekdir mode=ios::beg);
    int tell();
    int eraserecord(int);
    int updaterecord(const char*, int offset);
    int recordsSize();
    int updateAvail();
    QString path;
    list <int> avail;
    Cliente cliente;
    //LinearIndexFile idx;
};

#endif // CLIENTFILE_H
