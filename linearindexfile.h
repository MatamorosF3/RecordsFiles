#ifndef LINEARINDEXFILE_H
#define LINEARINDEXFILE_H
#include "tdaindexfile.h"
class LinearIndexFile //: public TDAIndexFile
{
public:
    LinearIndexFile();
    char* Search(int);
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
};

#endif // LINEARINDEXFILE_H
