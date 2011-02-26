

HEADERS = qcommandline.h \
    options.h

TEMPLATE = app
TARGET = phantomjs
DESTDIR = ../bin
SOURCES = phantomjs.cpp qcommandline.cpp \
    options.cpp
RESOURCES = phantomjs.qrc
QT += network webkit debug
CONFIG += console

