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
<<<<<<< HEAD
    productfile.cpp \
    tdaindexfile.cpp \
    linearindexfile.cpp \
    catfile.cpp
=======
    indexfile.cpp
>>>>>>> e4f50335b997f6e14bc1df6cb11264c2f990d496

HEADERS  += mainwindow.h \
    clientfile.h \
    tdafile.h \
    tdafsrecordfile.h \
    TDARecordFile.h \
<<<<<<< HEAD
    productfile.h \
    tdaindexfile.h \
    linearindexfile.h \
    catfile.h
=======
    indexfile.h
>>>>>>> e4f50335b997f6e14bc1df6cb11264c2f990d496

FORMS    += mainwindow.ui
