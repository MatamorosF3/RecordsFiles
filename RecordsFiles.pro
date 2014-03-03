#-------------------------------------------------
#
# Project created by QtCreator 2014-02-23T22:25:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RecordsFiles
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    clientfile.cpp \
    tdafile.cpp \
    tdafsrecordfile.cpp \
    TDARecordFile.cpp \
    productfile.cpp \
    tdaindexfile.cpp \
    linearindexfile.cpp \
    catfile.cpp

HEADERS  += mainwindow.h \
    clientfile.h \
    tdafile.h \
    tdafsrecordfile.h \
    TDARecordFile.h \
    productfile.h \
    tdaindexfile.h \
    linearindexfile.h \
    catfile.h

FORMS    += mainwindow.ui
