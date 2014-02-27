#ifndef TDARECORDFILE
#define TDARECORDFILE
#include "tdafile.h"
using namespace::std;
class TDARecordFile : public TDAFile
{
public:
    TDARecordFile();
	~TDARecordFile();
    virtual int readrecord(char*,int)=0;
    virtual int writerecord(const char*,int ind)=0;
    virtual int findrecord(int)=0;
    virtual int findrecord(const char*,int)=0;
    virtual void seek(int)=0;
    virtual int tell()=0;
    virtual int eraserecord(int)=0;
    virtual int updaterecord(const char*,int offset)=0;
};
#endif
