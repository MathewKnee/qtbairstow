QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bairstowMethod.cpp \
    fpinsertwindow.cpp \
    fpoutput.cpp \
    intervalinsertwindow.cpp \
    intervaloutput.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Interval.h \
    bairstowMethod.h \
    fpinsertwindow.h \
    fpoutput.h \
    intervalinsertwindow.h \
    intervaloutput.h \
    mainwindow.h \
    string_utils.h

FORMS += \
    fpinsertwindow.ui \
    fpoutput.ui \
    intervalinsertwindow.ui \
    intervaloutput.ui \
    mainwindow.ui

LIBS += \
    -lmpfr \
    -lgmpxx \
    -lgmp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
