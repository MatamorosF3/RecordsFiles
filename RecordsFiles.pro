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
    TDARecordFile.cpp

HEADERS  += mainwindow.h \
    clientfile.h \
    tdafile.h \
    tdafsrecordfile.h \
    TDARecordFile.h

FORMS    += mainwindow.ui
