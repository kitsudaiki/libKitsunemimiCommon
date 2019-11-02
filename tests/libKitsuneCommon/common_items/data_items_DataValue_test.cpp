/**
 *  @file    data_items_DataValue_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "data_items_DataValue_test.h"
#include <libKitsuneCommon/common_items/data_items.h>

namespace Kitsune
{
namespace Common
{

DataItems_DataValue_Test::DataItems_DataValue_Test()
    : Kitsune::Common::Test("DataItems_DataValue_Test")
{
    copy_assingment_constructor_test();
    copy_assingment_operator_test();
    operator_test();
    get_test();
    getSize_test();
    remove_test();
    copy_test();
    toString_test();
    getType_test();
    isValue_isMap_isArray_test();
    toValue_toMap_toArray_test();
    getString_getInt_getFloat_getBool_test();

    // value-exclusive
    getValueType_test();
    setValue_test();
}

/**
 * copy_assingment_constructor_test
 */
void
DataItems_DataValue_Test::copy_assingment_constructor_test()
{
    DataValue value("test");
    DataValue valueCopy = value;
    TEST_EQUAL(valueCopy.toString(), value.toString());
}

/**
 * copy_assingment_operator_test
 */
void
DataItems_DataValue_Test::copy_assingment_operator_test()
{
    DataValue value("test");
    DataValue valueCopy;
    valueCopy = value;
    TEST_EQUAL(valueCopy.toString(), value.toString());
}

/**
 * operator_test
 */
void
DataItems_DataValue_Test::operator_test()
{
    DataValue defaultValue;

    // int-access
    bool isNullptr = defaultValue[1] == nullptr;
    TEST_EQUAL(isNullptr, true);

    // string-access
    isNullptr = defaultValue["1"] == nullptr;
    TEST_EQUAL(isNullptr, true);
}

/**
 * get_test
 */
void
DataItems_DataValue_Test::get_test()
{
    DataValue defaultValue;

    // int-access
    bool isNullptr = defaultValue.get(1) == nullptr;
    TEST_EQUAL(isNullptr, true);

    // string-access
    isNullptr = defaultValue.get("1") == nullptr;
    TEST_EQUAL(isNullptr, true);
}

/**
 * getSize_test
 */
void
DataItems_DataValue_Test::getSize_test()
{
    DataValue defaultValue;
    TEST_EQUAL(defaultValue.size(), 0);
}

/**
 * remove_test
 */
void
DataItems_DataValue_Test::remove_test()
{
    DataValue defaultValue;
    TEST_EQUAL(defaultValue.remove(1), false);
}

/**
 * copy_test
 */
void
DataItems_DataValue_Test::copy_test()
{
    // init
    DataValue defaultValue;
    DataValue stringValue("test");
    DataValue intValue(42);
    DataValue floatValue(42.5f);
    DataValue boolValue(true);

    // default-value
    DataValue* defaultValueCopy = dynamic_cast<DataValue*>(defaultValue.copy());
    TEST_EQUAL(std::string(defaultValue.m_content.stringValue),
             std::string(defaultValueCopy->m_content.stringValue));

    // string-value
    DataValue* stringValueCopy = dynamic_cast<DataValue*>(stringValue.copy());
    TEST_EQUAL(std::string(stringValue.m_content.stringValue),
             std::string(stringValueCopy->m_content.stringValue));

    // int-value
    DataValue* intValueCopy = dynamic_cast<DataValue*>(intValue.copy());
    TEST_EQUAL(intValue.m_content.intValue, intValueCopy->m_content.intValue);

    // float-value
    DataValue* floatValueCopy = dynamic_cast<DataValue*>(floatValue.copy());
    TEST_EQUAL(floatValue.m_content.floatValue, floatValueCopy->m_content.floatValue);

    // bool-value
    DataValue* boolValueCopy = dynamic_cast<DataValue*>(boolValue.copy());
    TEST_EQUAL(boolValue.m_content.boolValue, boolValueCopy->m_content.boolValue);

    // cleanup
    delete defaultValueCopy;
    delete stringValueCopy;
    delete intValueCopy;
    delete floatValueCopy;
}

/**
 * toString_test
 */
void
DataItems_DataValue_Test::toString_test()
{
    DataValue defaultValue;
    DataValue stringValue("test");
    DataValue intValue(42);
    DataValue floatValue(42.5f);
    DataValue boolValue(true);

    TEST_EQUAL(defaultValue.toString(), "");
    TEST_EQUAL(stringValue.toString(), "test");
    TEST_EQUAL(intValue.toString(), "42");
    TEST_EQUAL(floatValue.toString(), "42.500000");
    TEST_EQUAL(boolValue.toString(), "true");
}

/**
 * getType_test
 */
void
DataItems_DataValue_Test::getType_test()
{
    DataValue defaultValue;
    DataValue stringValue("test");
    DataValue intValue(42);
    DataValue floatValue(42.5f);
    DataValue boolValue(true);

    TEST_EQUAL(defaultValue.getType(), DataItem::VALUE_TYPE);
    TEST_EQUAL(stringValue.getType(), DataItem::VALUE_TYPE);
    TEST_EQUAL(intValue.getType(), DataItem::VALUE_TYPE);
    TEST_EQUAL(floatValue.getType(), DataItem::VALUE_TYPE);
    TEST_EQUAL(boolValue.getType(), DataItem::VALUE_TYPE);
}

/**
 * isValue_isMap_isArray_test
 */
void
DataItems_DataValue_Test::isValue_isMap_isArray_test()
{
    DataValue defaultValue;
    TEST_EQUAL(defaultValue.isValue(), true);
    TEST_EQUAL(defaultValue.isMap(), false);
    TEST_EQUAL(defaultValue.isArray(), false);
}

/**
 * toValue_toMap_toArray_test
 */
void
DataItems_DataValue_Test::toValue_toMap_toArray_test()
{
    DataValue defaultValue;

    bool isNullptr = defaultValue.toMap() == nullptr;
    TEST_EQUAL(isNullptr, true);

    isNullptr = defaultValue.toArray() == nullptr;
    TEST_EQUAL(isNullptr, true);

    isNullptr = defaultValue.toValue() == nullptr;
    TEST_EQUAL(isNullptr, false);
}

/**
 * getString_getInt_getFloat_test
 */
void
DataItems_DataValue_Test::getString_getInt_getFloat_getBool_test()
{
    DataValue defaultValue;
    DataValue stringValue("test");
    DataValue intValue(42);
    DataValue floatValue(42.5f);
    DataValue boolValue(true);

    // default-value
    TEST_EQUAL(defaultValue.getString(), "");
    TEST_EQUAL(defaultValue.getInt(), 0);
    TEST_EQUAL(defaultValue.getFloat(), 0.0f);
    TEST_EQUAL(defaultValue.getBool(), false);

    // string-value
    TEST_EQUAL(stringValue.getString(), "test");
    TEST_EQUAL(stringValue.getInt(), 0);
    TEST_EQUAL(stringValue.getFloat(), 0.0f);
    TEST_EQUAL(stringValue.getBool(), false);

    // int-value
    TEST_EQUAL(intValue.getString(), "");
    TEST_EQUAL(intValue.getInt(), 42);
    TEST_EQUAL(intValue.getFloat(), 0.0f);
    TEST_EQUAL(intValue.getBool(), false);

    // float-value
    TEST_EQUAL(floatValue.getString(), "");
    TEST_EQUAL(floatValue.getInt(), 0);
    TEST_EQUAL(floatValue.getFloat(), 42.5f);
    TEST_EQUAL(floatValue.getBool(), false);

    // bool-value
    TEST_EQUAL(boolValue.getString(), "");
    TEST_EQUAL(boolValue.getInt(), 0);
    TEST_EQUAL(boolValue.getFloat(), 0.0f);
    TEST_EQUAL(boolValue.getBool(), true);
}

/**
 * getValueType_test
 */
void
DataItems_DataValue_Test::getValueType_test()
{
    DataValue defaultValue;
    DataValue stringValue("test");
    DataValue intValue(42);
    DataValue floatValue(42.5f);
    DataValue boolValue(true);

    TEST_EQUAL(defaultValue.getValueType(), DataItem::STRING_TYPE);
    TEST_EQUAL(stringValue.getValueType(), DataItem::STRING_TYPE);
    TEST_EQUAL(intValue.getValueType(), DataItem::INT_TYPE);
    TEST_EQUAL(floatValue.getValueType(), DataItem::FLOAT_TYPE);
    TEST_EQUAL(boolValue.getValueType(), DataItem::BOOL_TYPE);
}

/**
 * setValue_test
 */
void
DataItems_DataValue_Test::setValue_test()
{
    DataValue defaultValue;

    // string-value
    defaultValue.setValue("test");
    TEST_EQUAL(defaultValue.getValueType(), DataItem::STRING_TYPE);
    TEST_EQUAL(std::string(defaultValue.m_content.stringValue), "test");

    // int-value
    defaultValue.setValue(42);
    TEST_EQUAL(defaultValue.getValueType(), DataItem::INT_TYPE);
    TEST_EQUAL(defaultValue.m_content.intValue, 42);

    // float-value
    defaultValue.setValue(42.5f);
    TEST_EQUAL(defaultValue.getValueType(), DataItem::FLOAT_TYPE);
    TEST_EQUAL(defaultValue.m_content.floatValue, 42.5f);

    // bool-value
    defaultValue.setValue(true);
    TEST_EQUAL(defaultValue.getValueType(), DataItem::BOOL_TYPE);
    TEST_EQUAL(defaultValue.m_content.boolValue, true);
}

}  // namespace Common
}  // namespace Kitsune
