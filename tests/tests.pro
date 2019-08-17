include(../defaults.pri)

QT -= qt core gui

CONFIG   -= app_bundle
CONFIG += c++14 console

INCLUDEPATH += $$PWD

LIBS += -L../src -lKitsuneCommon

HEADERS += \
    libKitsuneCommon/statemachine/state_test.h \
    libKitsuneCommon/statemachine/statemachine_test.h \
    libKitsuneCommon/commonMethods/string_methods_test.h \
    libKitsuneCommon/commonMethods/vector_methods_test.h \
    libKitsuneCommon/buffering/data_buffer_methods_test.h \
    libKitsuneCommon/buffering/data_buffer_test.h \
    libKitsuneCommon/data_structure/data_items_DataArray_test.h \
    libKitsuneCommon/data_structure/data_items_DataObject_test.h \
    libKitsuneCommon/data_structure/data_items_DataValue_test.h

SOURCES += \
    main.cpp \
    libKitsuneCommon/statemachine/state_test.cpp \
    libKitsuneCommon/statemachine/statemachine_test.cpp \
    libKitsuneCommon/buffering/data_buffer_test.cpp \
    libKitsuneCommon/commonMethods/string_methods_test.cpp \
    libKitsuneCommon/commonMethods/vector_methods_test.cpp \
    libKitsuneCommon/buffering/data_buffer_methods_test.cpp \
    libKitsuneCommon/data_structure/data_items_DataArray_test.cpp \
    libKitsuneCommon/data_structure/data_items_DataObject_test.cpp \
    libKitsuneCommon/data_structure/data_items_DataValue_test.cpp
