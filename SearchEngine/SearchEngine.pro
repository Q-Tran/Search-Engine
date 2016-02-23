TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += main.cpp \
    indexerinterface.cpp \
    avltree.cpp \
    listnode.cpp \
    docnode.cpp \
    indexhandler.cpp \
    hashtable.cpp \
    parsehandler.cpp \
    stemmer.cpp \
    documenthandler.cpp \
    indexio.cpp \
    userinterface.cpp \
    queryhandler.cpp

HEADERS += \
    indexerinterface.h \
    avltree.h \
    listnode.h \
    docnode.h \
    indexhandler.h \
    hashtable.h \
    parsehandler.h \
    stemmer.h \
    documenthandler.h \
    indexio.h \
    userinterface.h \
    queryhandler.h

