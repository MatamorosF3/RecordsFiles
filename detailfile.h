#ifndef DETAILFILE_H
#define DETAILFILE_H
#include "tdafsrecordfile.h"
#include <QString>

class detailfile :public TDAFSRecordFile
{
public:
    detailfile();
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

#endif // DETAILFILE_H
