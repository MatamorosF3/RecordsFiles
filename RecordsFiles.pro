#-------------------------------------------------
#
# Project created by QtCreator 2014-02-23T22:25:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RecordsFiles
TEMPLATE = app
qt += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    clientfile.cpp \
    tdafile.cpp \
    tdafsrecordfile.cpp \
    TDARecordFile.cpp \
    catfile.cpp \
    linearindexfile.cpp \
    productfile.cpp \
    tdaindexfile.cpp \
    headerfile.cpp \
    detailfile.cpp \
    arbolbnodo.cpp \
    arbolb.cpp

HEADERS  += mainwindow.h \
    clientfile.h \
    tdafile.h \
    tdafsrecordfile.h \
    TDARecordFile.h \
    catfile.h \
    linearindexfile.h \
    productfile.h \
    tdaindexfile.h \
    headerfile.h \
    detailfile.h \
    arbolbnodo.h \
    arbolb.h

FORMS    += mainwindow.ui
