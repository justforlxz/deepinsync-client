QT += core
QT -= gui
QT += dbus websockets

CONFIG += c++11

TARGET = mkacgsync
CONFIG += console link_pkgconfig
CONFIG -= app_bundle

PKGCONFIG += dframeworkdbus

TEMPLATE = app

SOURCES += main.cpp \
    Wallpaper.cpp \
    Client.cpp

HEADERS += \
    Wallpaper.h \
    Client.h
