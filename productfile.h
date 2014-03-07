#ifndef PRODUCTFILE_H
#define PRODUCTFILE_H
#include "tdafsrecordfile.h"
#include <QString>
#include <list>
class ProductFile : public TDAFSRecordFile{
public:
    ProductFile();
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
    int updateAvail();

    QString path;
    list <int> avail;
};

#endif // PRODUCTFILE_H
