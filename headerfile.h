#ifndef HEADERFILE_H
#define HEADERFILE_H
#include "tdafsrecordfile.h"
#include <QString>

class headerfile: public TDAFSRecordFile
{
public:
    headerfile();
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
    QString path;
};

#endif // HEADERFILE_H
