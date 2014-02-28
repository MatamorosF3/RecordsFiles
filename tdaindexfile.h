#ifndef TDAINDEXFILE_H
#define TDAINDEXFILE_H
#include "TDARecordFile.h"
#include <vector>
class TDAIndexFile : public TDARecordFile
{
public:
    TDAIndexFile();
    struct indice{
        char llave[5],offset[7];
    };

    int readrecord(char*,int);
    int writerecord(const char*,int ind);
    int findrecord(int);
    int findrecord(const char*,int);
    void seek(int);
    void seek(ios::seekdir mode=ios::beg);
    int tell();
    int eraserecord(int);
    int updaterecord(const char*, int offset);
    int recordsSize();
    vector<indice> ClientIndex;
    vector<indice> ProductIndex;
    vector<indice> CategIndex;
};

#endif // TDAINDEXFILE_H
