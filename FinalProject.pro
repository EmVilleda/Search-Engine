TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    datacrunch.cpp \
    docparser.cpp \
    indexhandler.cpp \
    queryhandler.cpp \
    document.cpp \
    avltree.cpp \
    hashtable.cpp \
    query.cpp \
    avlnode.cpp \
    hashentry.cpp \
    indexentry.cpp \
    userinterface.cpp \
    stemmer.cpp \
    page.cpp

HEADERS += \
    datacrunch.h \
    docparser.h \
    indexhandler.h \
    queryhandler.h \
    document.h \
    index.h \
    avltree.h \
    hashtable.h \
    query.h \
    avlnode.h \
    hashentry.h \
    indexentry.h \
    stemmer.h \
    userinterface.h \
    page.h

