#ifndef LINEARINDEXFILE_H
#define LINEARINDEXFILE_H
#include "tdaindexfile.h"
#include <vector>
#include <QString>
class LinearIndexFile : public TDAIndexFile
{
public:
    struct indice{
        int llave;
        int offset;
    };
    int tamanioInicial;
    vector<indice> indices;
    LinearIndexFile();
    int readrecord(QString);
    int readrecord(char*, int);
    int writerecord(const char*,int ind);
    int findrecord(int);
    int findrecord(const char*,int);
    void seek(int);
    void seek(ios::seekdir mode=ios::beg);
    int tell();
    int eraserecord(int);
    int updaterecord(const char*, int offset);
    int updaterecord(QString);
    int recordsSize();
    int recordsSize(QString);
};
#endif // LINEARINDEXFILE_H
