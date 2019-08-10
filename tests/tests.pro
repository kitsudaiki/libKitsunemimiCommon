include(../defaults.pri)

QT -= qt core gui

CONFIG   -= app_bundle
CONFIG += c++14 console

INCLUDEPATH += $$PWD

LIBS += -L../src -lKitsuneCommon

HEADERS += \
    libKitsuneCommon/commonMethods/stringMethods_test.hpp \
    libKitsuneCommon/commonMethods/vectorMethods_test.hpp \
    libKitsuneCommon/buffering/dataBuffer_test.hpp \
    libKitsuneCommon/buffering/dataBufferMethods_test.hpp \
    libKitsuneCommon/statemachine/state_test.hpp \
    libKitsuneCommon/statemachine/statemachine_test.hpp \
    libKitsuneCommon/data_structure/dataItems_dataObject_test.hpp \
    libKitsuneCommon/data_structure/dataItems_dataValue_test.hpp \
    libKitsuneCommon/data_structure/dataItems_dataArray_test.hpp

SOURCES += \
    main.cpp \
    libKitsuneCommon/commonMethods/stringMethods_test.cpp \
    libKitsuneCommon/commonMethods/vectorMethods_test.cpp \
    libKitsuneCommon/buffering/dataBuffer_test.cpp \
    libKitsuneCommon/buffering/dataBufferMethods_test.cpp \
    libKitsuneCommon/statemachine/state_test.cpp \
    libKitsuneCommon/statemachine/statemachine_test.cpp \
    libKitsuneCommon/data_structure/dataItems_dataArray_test.cpp \
    libKitsuneCommon/data_structure/dataItems_dataObject_test.cpp \
    libKitsuneCommon/data_structure/dataItems_dataValue_test.cpp
