QT += core network
QT -= gui

TARGET = server
CONFIG += console
CONFIG -= app_bundle

CONFIG += c++11

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp

HEADERS += \
    server.h

