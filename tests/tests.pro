include(../defaults.pri)

QT -= qt core gui

CONFIG   -= app_bundle
CONFIG += c++14 console

LIBS += -L../src -lKitsunemimiCommon
INCLUDEPATH += $$PWD

HEADERS += \
    libKitsunemimiCommon/state_test.h \
    libKitsunemimiCommon/statemachine_test.h \
    libKitsunemimiCommon/common_methods/string_methods_test.h \
    libKitsunemimiCommon/common_methods/vector_methods_test.h \
    libKitsunemimiCommon/data_buffer_methods_test.h \
    libKitsunemimiCommon/data_buffer_test.h \
    libKitsunemimiCommon/common_items/data_items_DataArray_test.h \
    libKitsunemimiCommon/common_items/data_items_DataValue_test.h \
    libKitsunemimiCommon/common_items/table_item_test.h \
    libKitsunemimiCommon/common_items/data_items_DataMap_test.h

SOURCES += \
    main.cpp \
    libKitsunemimiCommon/state_test.cpp \
    libKitsunemimiCommon/statemachine_test.cpp \
    libKitsunemimiCommon/data_buffer_test.cpp \
    libKitsunemimiCommon/common_methods/string_methods_test.cpp \
    libKitsunemimiCommon/common_methods/vector_methods_test.cpp \
    libKitsunemimiCommon/data_buffer_methods_test.cpp \
    libKitsunemimiCommon/common_items/data_items_DataArray_test.cpp \
    libKitsunemimiCommon/common_items/data_items_DataValue_test.cpp \
    libKitsunemimiCommon/common_items/table_item_test.cpp \
    libKitsunemimiCommon/common_items/data_items_DataMap_test.cpp
