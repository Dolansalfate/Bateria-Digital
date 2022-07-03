QT       += core gui multimedia network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    asignarcanal.cpp \
    clock.cpp \
    configuracion.cpp \
    datosgrilla.cpp \
    elegirbeat.cpp \
    main.cpp \
    mainwindow.cpp \
    ventanamixer.cpp

HEADERS += \
    asignarcanal.h \
    clock.h \
    configuracion.h \
    datosgrilla.h \
    elegirbeat.h \
    mainwindow.h \
    ventanamixer.h

FORMS += \
    elegirbeat.ui \
    mainwindow.ui \
    ventanamixer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
