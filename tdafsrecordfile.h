#ifndef TDAFSRECORDFILE_H
#define TDAFSRECORDFILE_H
#include <cstring>
#include "TDARecordFile.h"
class TDAFSRecordFile : public TDARecordFile
{
public:
    TDAFSRecordFile();
    TDAFSRecordFile(string);


};

#endif // TDAFSRECORDFILE_H
