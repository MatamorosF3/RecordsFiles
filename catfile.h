#ifndef CATFILE
#define CATFILE
#include "tdafsrecordfile.h"
#include <QString>
#include <list>
class Catfile : public TDAFSRecordFile{
public:
    Catfile();
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
    int updateAvailCat();

    QString path;
    list <int> AvailCat;

};

#endif // CATFILE
