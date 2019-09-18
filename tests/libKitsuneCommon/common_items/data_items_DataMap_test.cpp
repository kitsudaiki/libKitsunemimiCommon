/**
 *  @file    data_items_DataMap_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "data_items_DataMap_test.h"
#include <common_items/data_items.h>

namespace Kitsune
{
namespace Common
{

DataItems_DataMap_Test::DataItems_DataMap_Test()
    : Kitsune::Common::UnitTest("DataItems_DataMap_Test")
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

    // object-exclusive
    insert_test();
    getStringByKey_getIntByKey_getFloatByKey_test();
    getKeys_test();
    getValues_test();
    contains_test();
}

/**
 * operator_test
 */
void
DataItems_DataMap_Test::operator_test()
{
    DataMap object = initTestObject();

    UNITTEST(object[0]->getString(), "test");
    UNITTEST(object["hmm"]->getInt(), 42);

    // negative tests
    bool isNullptr = object[10] == nullptr;
    UNITTEST(isNullptr, true);
    isNullptr = object["k"] == nullptr;
    UNITTEST(isNullptr, true);
}

/**
 * get_test
 */
void
DataItems_DataMap_Test::get_test()
{
    DataMap object = initTestObject();

    UNITTEST(object.get(0)->getString(), "test");
    UNITTEST(object.get("hmm")->getInt(), 42);

    // negative tests
    bool isNullptr = object.get(10) == nullptr;
    UNITTEST(isNullptr, true);
    isNullptr = object.get("k") == nullptr;
    UNITTEST(isNullptr, true);
}

/**
 * getSize_test
 */
void
DataItems_DataMap_Test::getSize_test()
{
    DataMap object = initTestObject();
    UNITTEST(object.size(), 5);
}

/**
 * remove_test
 */
void
DataItems_DataMap_Test::remove_test()
{
    DataMap object = initTestObject();
    UNITTEST(object.remove(0), true);
    UNITTEST(object.remove("hmm"), true);

    UNITTEST(object.get(2)->toString(), "42.500000");
    UNITTEST(object.size(), 3);

    // negative tests
    UNITTEST(object.remove(10), false);
}

/**
 * copy_test
 */
void
DataItems_DataMap_Test::copy_test()
{
    DataMap object = initTestObject();

    DataMap* objectCopy = dynamic_cast<DataMap*>(object.copy());

    bool isNullptr = objectCopy == nullptr;
    UNITTEST(isNullptr, false);

    UNITTEST(object.toString(), objectCopy->toString());

    delete objectCopy;
}

/**
 * toString_test
 */
void
DataItems_DataMap_Test::toString_test()
{
    DataMap object = initTestObject();

    std::string compare = "{\"asdf\":\"test\","
                          "\"fail\":null,"
                          "\"hmm\":42,"
                          "\"poi\":\"\","
                          "\"xyz\":42.500000}";
    UNITTEST(object.toString(), compare);

    compare = "{\n"
              "    \"asdf\": \"test\",\n"
              "    \"fail\": null,\n"
              "    \"hmm\": 42,\n"
              "    \"poi\": \"\",\n"
              "    \"xyz\": 42.500000\n"
              "}";
    UNITTEST(object.toString(true), compare);
}

/**
 * getType_test
 */
void
DataItems_DataMap_Test::getType_test()
{
    DataMap object = initTestObject();
    UNITTEST(object.getType(), DataItem::MAP_TYPE);
}

/**
 * isValue_isMap_isArray_test
 */
void
DataItems_DataMap_Test::isValue_isMap_isArray_test()
{
    DataMap object = initTestObject();
    UNITTEST(object.isValue(), false);
    UNITTEST(object.isMap(), true);
    UNITTEST(object.isArray(), false);
}

/**
 * toValue_toMap_toArray_test
 */
void
DataItems_DataMap_Test::toValue_toMap_toArray_test()
{
    DataMap object = initTestObject();

    bool isNullptr = object.toMap() == nullptr;
    UNITTEST(isNullptr, false);

    isNullptr = object.toArray() == nullptr;
    UNITTEST(isNullptr, true);

    isNullptr = object.toValue() == nullptr;
    UNITTEST(isNullptr, true);
}

/**
 * getString_getInt_getFloat_test
 */
void
DataItems_DataMap_Test::getString_getInt_getFloat_test()
{
    DataMap object = initTestObject();
    UNITTEST(object.getString(), "");
    UNITTEST(object.getInt(), 0);
    UNITTEST(object.getFloat(), 0.0f);
}

/**
 * insert_test
 */
void
DataItems_DataMap_Test::insert_test()
{
    DataMap object;
    DataValue defaultValue;
    DataValue stringValue("test");
    DataValue intValue(42);
    DataValue floatValue(42.5f);

    UNITTEST(object.insert("poi", defaultValue.copy()), true);
    UNITTEST(object.insert("asdf", stringValue.copy()), true);
    UNITTEST(object.insert("hmm", intValue.copy()), true);
    UNITTEST(object.insert("xyz", floatValue.copy()), true);
    UNITTEST(object.insert("fail", nullptr), true);
}

/**
 * getStringByKey_getIntByKey_getFloatByKey_test
 */
void
DataItems_DataMap_Test::getStringByKey_getIntByKey_getFloatByKey_test()
{
    DataMap object = initTestObject();

    UNITTEST(object.getStringByKey("asdf"), "test");
    UNITTEST(object.getIntByKey("hmm"), 42);
    UNITTEST(object.getFloatByKey("xyz"), 42.5f);
}

/**
 * getKeys_test
 */
void
DataItems_DataMap_Test::getKeys_test()
{
    DataMap object = initTestObject();

    std::vector<std::string> keys = object.getKeys();
    UNITTEST(keys.size(), 5);
    UNITTEST(keys.at(0), "asdf");
    UNITTEST(keys.at(1), "fail");
    UNITTEST(keys.at(2), "hmm");
    UNITTEST(keys.at(3), "poi");
    UNITTEST(keys.at(4), "xyz");
}

/**
 * getValues_test
 */
void
DataItems_DataMap_Test::getValues_test()
{
    DataMap object = initTestObject();

    std::vector<DataItem*> values = object.getValues();
    UNITTEST(values.size(), 5);
    UNITTEST(values.at(0)->toString(), "test");
    UNITTEST(values.at(2)->toString(), "42");
    UNITTEST(values.at(3)->toString(), "");
    UNITTEST(values.at(4)->toString(), "42.500000");
}

/**
 * contains_test
 */
void
DataItems_DataMap_Test::contains_test()
{
    DataMap object = initTestObject();
    UNITTEST(object.contains("poi"), true);
    UNITTEST(object.contains("asdf"), true);
    UNITTEST(object.contains("hmm"), true);
    UNITTEST(object.contains("xyz"), true);

    UNITTEST(object.contains("12345"), false);
}

/**
 * create test data-map
 *
 * @return data-map for tests
 */
DataMap
DataItems_DataMap_Test::initTestObject()
{
    DataMap object;
    DataValue defaultValue;
    DataValue stringValue("test");
    DataValue intValue(42);
    DataValue floatValue(42.5f);

    object.insert("poi", defaultValue.copy());
    object.insert("asdf", stringValue.copy());
    object.insert("hmm", intValue.copy());
    object.insert("xyz", floatValue.copy());
    object.insert("fail", nullptr);

    return object;
}

}  // namespace Common
}  // namespace Kitsune
