include(../defaults.pri)

QT -= qt core gui

CONFIG   -= app_bundle
CONFIG += c++14 console

INCLUDEPATH += $$PWD

LIBS += -L../src -lKitsuneCommon

HEADERS += \
    buffering/commonDataBufferMethods_test.hpp \
    buffering/commonDataBuffer_test.hpp \
    commonMethods/stringMethods_test.hpp \
    commonMethods/vectorMethods_test.hpp

SOURCES += \
    main.cpp \
    buffering/commonDataBufferMethods_test.cpp \
    buffering/commonDataBuffer_test.cpp \
    commonMethods/stringMethods_test.cpp \
    commonMethods/vectorMethods_test.cpp
