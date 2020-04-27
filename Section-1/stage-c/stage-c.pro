TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
        obj_control.c \
        objects.c

HEADERS += \
    obj_control.h \
    objects.h

STATECHARTS += \
    state.scxml \
    sttate.scxml

DISTFILES += \
    modell.qmodel
