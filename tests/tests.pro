include(../defaults.pri)

QT -= qt core gui

CONFIG   -= app_bundle
CONFIG += c++14 console

INCLUDEPATH += $$PWD

LIBS += -L../src -lKitsuneCommon

HEADERS += \
    libKitsuneCommon/statemachine/state_test.h \
    libKitsuneCommon/statemachine/statemachine_test.h \
    libKitsuneCommon/common_methods/string_methods_test.h \
    libKitsuneCommon/common_methods/vector_methods_test.h \
    libKitsuneCommon/buffering/data_buffer_methods_test.h \
    libKitsuneCommon/buffering/data_buffer_test.h \
    libKitsuneCommon/common_items/data_items_DataArray_test.h \
    libKitsuneCommon/common_items/data_items_DataValue_test.h \
    libKitsuneCommon/common_items/table_item_test.h \
    libKitsuneCommon/common_items/data_items_DataMap_test.h

SOURCES += \
    main.cpp \
    libKitsuneCommon/statemachine/state_test.cpp \
    libKitsuneCommon/statemachine/statemachine_test.cpp \
    libKitsuneCommon/buffering/data_buffer_test.cpp \
    libKitsuneCommon/common_methods/string_methods_test.cpp \
    libKitsuneCommon/common_methods/vector_methods_test.cpp \
    libKitsuneCommon/buffering/data_buffer_methods_test.cpp \
    libKitsuneCommon/common_items/data_items_DataArray_test.cpp \
    libKitsuneCommon/common_items/data_items_DataValue_test.cpp \
    libKitsuneCommon/common_items/table_item_test.cpp \
    libKitsuneCommon/common_items/data_items_DataMap_test.cpp
