QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    buscar.cpp \
    eliminar.cpp \
    main.cpp \
    mainwindow.cpp \
    siguiente.cpp \
    verregistros.cpp

HEADERS += \
    buscar.h \
    eliminar.h \
    mainwindow.h \
    siguiente.h \
    verregistros.h

FORMS += \
    buscar.ui \
    eliminar.ui \
    mainwindow.ui \
    siguiente.ui \
    verregistros.ui

TRANSLATIONS += \
    GUI_database_es_PE.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    imagenes/icono.png

RESOURCES += \
    resource.qrc
