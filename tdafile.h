#ifndef TDAFILE_H
#define TDAFILE_H

#include <fstream>
#include <string>
#include <ios>
//#include <iostream>

using std::fstream;
using std::streamsize;
using std::string;
using std::ios_base;
using std::ios;
using std::streampos;

class TDAFile
{
public:
    TDAFile();
    TDAFile(const string&, ios_base::openmode = ios_base::in | ios_base::out);
    bool open(const string&, ios_base::openmode = ios_base::in | ios_base::out);
    int read(char *, streamsize);
    int write(const char *, streamsize);
    bool isEOF();
    bool isBOF();
    int isOK();
    bool is_open()const;
    void seek(int);
    void seek(ios::seekdir mode=ios::beg);
    void flush();
    void close();
    int tell();
    void trunc();


    ~TDAFile();
private:
    string fileName;
    fstream fileStream;




};

#endif // TDAFILE_H
