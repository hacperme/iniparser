TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        example/iniexample.c \
        src/dictionary.c \
        src/iniparser.c \
        src/iniparser_buffer.c

HEADERS += \
    src/dictionary.h \
    src/iniparser.h \
    src/iniparser_buffer.h

INCLUDEPATH += src
