#ifndef TDAINDEXFILE_H
#define TDAINDEXFILE_H
#include "TDARecordFile.h"
#include <vector>
class TDAIndexFile : public TDARecordFile
{
public:
    TDAIndexFile();
    virtual int readrecord(char*,int)=0;
    virtual int writerecord(const char*,int ind)=0;
    virtual int findrecord(int)=0;
    virtual int findrecord(const char*,int)=0;
    virtual void seek(int)=0;
    virtual void seek(ios::seekdir mode=ios::beg)=0;
    virtual int tell()=0;
    virtual int eraserecord(int)=0;
    virtual int updaterecord(const char*, int offset)=0;
    virtual int recordsSize()=0;
};

#endif // TDAINDEXFILE_H
