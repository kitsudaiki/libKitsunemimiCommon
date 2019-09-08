/**
 *  @file    data_items_DataValue_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "data_items_DataValue_test.h"
#include <common_items/data_items.h>

namespace Kitsune
{
namespace Common
{

DataItems_DataValue_Test::DataItems_DataValue_Test()
    : Kitsune::Common::UnitTest("DataItems_DataValue_Test")
{
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
 * operator_test
 */
void
DataItems_DataValue_Test::operator_test()
{
    DataValue defaultValue;

    // int-access
    bool isNullptr = defaultValue[1] == nullptr;
    UNITTEST(isNullptr, true);

    // string-access
    isNullptr = defaultValue["1"] == nullptr;
    UNITTEST(isNullptr, true);
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
    UNITTEST(isNullptr, true);

    // string-access
    isNullptr = defaultValue.get("1") == nullptr;
    UNITTEST(isNullptr, true);
}

/**
 * getSize_test
 */
void
DataItems_DataValue_Test::getSize_test()
{
    DataValue defaultValue;
    UNITTEST(defaultValue.size(), 0);
}

/**
 * remove_test
 */
void
DataItems_DataValue_Test::remove_test()
{
    DataValue defaultValue;
    UNITTEST(defaultValue.remove(1), false);
}

/**
 * copy_test
 */
void
DataItems_DataValue_Test::copy_test()
{
    // init
    DataValue defaultValue;
    DataValue stringValue(std::string("test"));
    DataValue intValue(42);
    DataValue floatValue(42.5f);
    DataValue boolValue(true);

    // default-value
    DataValue* defaultValueCopy = dynamic_cast<DataValue*>(defaultValue.copy());
    UNITTEST(std::string(defaultValue.m_content.stringValue),
             std::string(defaultValueCopy->m_content.stringValue));

    // string-value
    DataValue* stringValueCopy = dynamic_cast<DataValue*>(stringValue.copy());
    UNITTEST(std::string(stringValue.m_content.stringValue),
             std::string(stringValueCopy->m_content.stringValue));

    // int-value
    DataValue* intValueCopy = dynamic_cast<DataValue*>(intValue.copy());
    UNITTEST(intValue.m_content.intValue, intValueCopy->m_content.intValue);

    // float-value
    DataValue* floatValueCopy = dynamic_cast<DataValue*>(floatValue.copy());
    UNITTEST(floatValue.m_content.floatValue, floatValueCopy->m_content.floatValue);

    // bool-value
    DataValue* boolValueCopy = dynamic_cast<DataValue*>(boolValue.copy());
    UNITTEST(boolValue.m_content.boolValue, boolValueCopy->m_content.boolValue);

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
    DataValue stringValue(std::string("test"));
    DataValue intValue(42);
    DataValue floatValue(42.5f);
    DataValue boolValue(true);

    UNITTEST(defaultValue.toString(), "\"\"");
    UNITTEST(stringValue.toString(), "\"test\"");
    UNITTEST(intValue.toString(), "42");
    UNITTEST(floatValue.toString(), "42.500000");
    UNITTEST(boolValue.toString(), "true");
}

/**
 * getType_test
 */
void
DataItems_DataValue_Test::getType_test()
{
    DataValue defaultValue;
    DataValue stringValue(std::string("test"));
    DataValue intValue(42);
    DataValue floatValue(42.5f);
    DataValue boolValue(true);

    UNITTEST(defaultValue.getType(), DataItem::VALUE_TYPE);
    UNITTEST(stringValue.getType(), DataItem::VALUE_TYPE);
    UNITTEST(intValue.getType(), DataItem::VALUE_TYPE);
    UNITTEST(floatValue.getType(), DataItem::VALUE_TYPE);
    UNITTEST(boolValue.getType(), DataItem::VALUE_TYPE);
}

/**
 * isValue_isMap_isArray_test
 */
void
DataItems_DataValue_Test::isValue_isMap_isArray_test()
{
    DataValue defaultValue;
    UNITTEST(defaultValue.isValue(), true);
    UNITTEST(defaultValue.isMap(), false);
    UNITTEST(defaultValue.isArray(), false);
}

/**
 * toValue_toMap_toArray_test
 */
void
DataItems_DataValue_Test::toValue_toMap_toArray_test()
{
    DataValue defaultValue;

    bool isNullptr = defaultValue.toMap() == nullptr;
    UNITTEST(isNullptr, true);

    isNullptr = defaultValue.toArray() == nullptr;
    UNITTEST(isNullptr, true);

    isNullptr = defaultValue.toValue() == nullptr;
    UNITTEST(isNullptr, false);
}

/**
 * getString_getInt_getFloat_test
 */
void
DataItems_DataValue_Test::getString_getInt_getFloat_getBool_test()
{
    DataValue defaultValue;
    DataValue stringValue(std::string("test"));
    DataValue intValue(42);
    DataValue floatValue(42.5f);
    DataValue boolValue(true);

    // default-value
    UNITTEST(defaultValue.getString(), "");
    UNITTEST(defaultValue.getInt(), 0);
    UNITTEST(defaultValue.getFloat(), 0.0f);
    UNITTEST(defaultValue.getBool(), false);

    // string-value
    UNITTEST(stringValue.getString(), "test");
    UNITTEST(stringValue.getInt(), 0);
    UNITTEST(stringValue.getFloat(), 0.0f);
    UNITTEST(stringValue.getBool(), false);

    // int-value
    UNITTEST(intValue.getString(), "");
    UNITTEST(intValue.getInt(), 42);
    UNITTEST(intValue.getFloat(), 0.0f);
    UNITTEST(intValue.getBool(), false);

    // float-value
    UNITTEST(floatValue.getString(), "");
    UNITTEST(floatValue.getInt(), 0);
    UNITTEST(floatValue.getFloat(), 42.5f);
    UNITTEST(floatValue.getBool(), false);

    // bool-value
    UNITTEST(boolValue.getString(), "");
    UNITTEST(boolValue.getInt(), 0);
    UNITTEST(boolValue.getFloat(), 0.0f);
    UNITTEST(boolValue.getBool(), true);
}

/**
 * getValueType_test
 */
void
DataItems_DataValue_Test::getValueType_test()
{
    DataValue defaultValue;
    DataValue stringValue(std::string("test"));
    DataValue intValue(42);
    DataValue floatValue(42.5f);
    DataValue boolValue(true);

    UNITTEST(defaultValue.getValueType(), DataItem::STRING_TYPE);
    UNITTEST(stringValue.getValueType(), DataItem::STRING_TYPE);
    UNITTEST(intValue.getValueType(), DataItem::INT_TYPE);
    UNITTEST(floatValue.getValueType(), DataItem::FLOAT_TYPE);
    UNITTEST(boolValue.getValueType(), DataItem::BOOL_TYPE);
}

/**
 * setValue_test
 */
void
DataItems_DataValue_Test::setValue_test()
{
    DataValue defaultValue;

    // string-value
    defaultValue.setValue(std::string("test"));
    UNITTEST(defaultValue.getValueType(), DataItem::STRING_TYPE);
    UNITTEST(std::string(defaultValue.m_content.stringValue), "test");

    // int-value
    defaultValue.setValue(42);
    UNITTEST(defaultValue.getValueType(), DataItem::INT_TYPE);
    UNITTEST(defaultValue.m_content.intValue, 42);

    // float-value
    defaultValue.setValue(42.5f);
    UNITTEST(defaultValue.getValueType(), DataItem::FLOAT_TYPE);
    UNITTEST(defaultValue.m_content.floatValue, 42.5f);

    // bool-value
    defaultValue.setValue(true);
    UNITTEST(defaultValue.getValueType(), DataItem::BOOL_TYPE);
    UNITTEST(defaultValue.m_content.boolValue, true);
}

}  // namespace Common
}  // namespace Kitsune
