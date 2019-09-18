/**
 *  @file    data_items_DataArray_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "data_items_DataArray_test.h"
#include <common_items/data_items.h>

namespace Kitsune
{
namespace Common
{

DataItems_DataArray_Test::DataItems_DataArray_Test()
    : Kitsune::Common::UnitTest("DataItems_DataArray_Test")
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
    getString_getInt_getFloat_test();

    // array-exclusive
    append_test();
}

/**
 * append_test
 */
void
DataItems_DataArray_Test::append_test()
{
    DataArray array;
    DataValue defaultValue;
    DataValue stringValue("test");
    DataValue intValue(42);
    DataValue floatValue(42.5f);

    array.append(defaultValue.copy());
    array.append(stringValue.copy());
    array.append(intValue.copy());
    array.append(floatValue.copy());
    array.append(nullptr);

    UNITTEST(array.size(), 5);
}

/**
 * operator_test
 */
void
DataItems_DataArray_Test::operator_test()
{
    DataArray array = initTestArray();

    UNITTEST(array[1]->toString(), "test");

    // negative tests
    bool isNullptr = array[10] == nullptr;
    UNITTEST(isNullptr, true);
    isNullptr = array["2"] == nullptr;
    UNITTEST(isNullptr, true);
}

/**
 * get_test
 */
void
DataItems_DataArray_Test::get_test()
{
    DataArray array = initTestArray();

    UNITTEST(array.get(1)->getString(), "test");

    // negative tests
    bool isNullptr = array.get(10) == nullptr;
    UNITTEST(isNullptr, true);
    isNullptr = array.get("2") == nullptr;
    UNITTEST(isNullptr, true);
}

/**
 * getSize_test
 */
void
DataItems_DataArray_Test::getSize_test()
{
    DataArray array = initTestArray();
    UNITTEST(array.size(), 5);
}

/**
 * remove_test
 */
void
DataItems_DataArray_Test::remove_test()
{
    DataArray array = initTestArray();
    UNITTEST(array.remove(1), true);
    UNITTEST(array.remove("2"), true);

    UNITTEST(array.get(1)->getInt(), 42);
    UNITTEST(array.size(), 3);

    // negative tests
    UNITTEST(array.remove(10), false);
}

/**
 * copy_test
 */
void
DataItems_DataArray_Test::copy_test()
{
    DataArray array = initTestArray();

    DataArray* arrayCopy = dynamic_cast<DataArray*>(array.copy());

    bool isNullptr = arrayCopy == nullptr;
    UNITTEST(isNullptr, false);

    UNITTEST(array.toString(), arrayCopy->toString());

    delete arrayCopy;
}

/**
 * toString_test
 */
void
DataItems_DataArray_Test::toString_test()
{
    DataArray array = initTestArray();

    std::string compare = "[\"\",\"test\",42,42.500000,null]";
    UNITTEST(array.toString(), compare);

    compare = "[\n"
              "    \"\",\n"
              "    \"test\",\n"
              "    42,\n"
              "    42.500000,\n"
              "    null\n"
              "]";
    UNITTEST(array.toString(true), compare);
}

/**
 * getType_test
 */
void
DataItems_DataArray_Test::getType_test()
{
    DataArray array = initTestArray();
    UNITTEST(array.getType(), DataItem::ARRAY_TYPE);
}

/**
 * isValue_isMap_isArray_test
 */
void
DataItems_DataArray_Test::isValue_isMap_isArray_test()
{
    DataArray array = initTestArray();
    UNITTEST(array.isValue(), false);
    UNITTEST(array.isMap(), false);
    UNITTEST(array.isArray(), true);
}

/**
 * toValue_toMap_toArray_test
 */
void
DataItems_DataArray_Test::toValue_toMap_toArray_test()
{
    DataArray array = initTestArray();

    bool isNullptr = array.toMap() == nullptr;
    UNITTEST(isNullptr, true);

    isNullptr = array.toArray() == nullptr;
    UNITTEST(isNullptr, false);

    isNullptr = array.toValue() == nullptr;
    UNITTEST(isNullptr, true);
}

/**
 * getString_getInt_getFloat_test
 */
void
DataItems_DataArray_Test::getString_getInt_getFloat_test()
{
    DataArray array = initTestArray();
    UNITTEST(array.getString(), "");
    UNITTEST(array.getInt(), 0);
    UNITTEST(array.getFloat(), 0.0f);
}

/**
 * create test data-array
 *
 * @return data-array for tests
 */
DataArray
DataItems_DataArray_Test::initTestArray()
{
    DataArray array;
    DataValue defaultValue;
    DataValue stringValue("test");
    DataValue intValue(42);
    DataValue floatValue(42.5f);

    array.append(defaultValue.copy());
    array.append(stringValue.copy());
    array.append(intValue.copy());
    array.append(floatValue.copy());
    array.append(nullptr);

    return array;
}

}  // namespace Common
}  // namespace Kitsune
