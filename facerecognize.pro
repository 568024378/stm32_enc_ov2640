#-------------------------------------------------
#
# Project created by QtCreator 2019-05-06T12:08:43
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = f-acs
TEMPLATE = app


SOURCES += main.cpp\
    facedetect.cpp \
    csvfile.cpp \
    facerecognize.cpp \
    fMenu.cpp

HEADERS  += \
    facedetect.h \
    csvfile.h \
    facerecognize.h \
    fMenu.h

FORMS    += \
    register.ui \
    fMenu.ui

CONFIG += C++11

INCLUDEPATH += /usr/local/include
#INCLUDEPATH += /usr/local/arm/opencv-arm/include \
#              /usr/local/arm/opencv-arm/include/opencv \
#               /usr/local/arm/opencv-arm/include/opencv2

#LIBS += /usr/local/arm/opencv-arm/lib/libopencv*

LIBS += /usr/local/lib/libopencv*


#include(/opt/qt_opencv/opencv_arm.pri)
