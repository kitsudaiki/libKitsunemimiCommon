include(../defaults.pri)

QT -= qt core gui

CONFIG   -= app_bundle
CONFIG += c++14 console

INCLUDEPATH += $$PWD

LIBS += -L../src -lKitsuneCommon

HEADERS += \
    libKitsuneCommon/buffering/commonDataBufferMethods_test.hpp \
    libKitsuneCommon/buffering/commonDataBuffer_test.hpp \
    libKitsuneCommon/commonMethods/stringMethods_test.hpp \
    libKitsuneCommon/commonMethods/vectorMethods_test.hpp

SOURCES += \
    main.cpp \
    libKitsuneCommon/buffering/commonDataBufferMethods_test.cpp \
    libKitsuneCommon/buffering/commonDataBuffer_test.cpp \
    libKitsuneCommon/commonMethods/stringMethods_test.cpp \
    libKitsuneCommon/commonMethods/vectorMethods_test.cpp
