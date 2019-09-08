/**
 *  @file    data_items.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 *
 *  @brief data-items for universal data-structures
 *
 *  @detail These was originally created in libKitsuneJson. Thats why the strint-output of the
 *          structure has still json-format. It can handle list, maps and values and is used
 *          in all of the kitsune-parser libraries as internal data-representation.
 */

#ifndef DATAITEMS_H
#define DATAITEMS_H

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <map>

namespace Kitsune
{
namespace Common
{
class DataArray;
class DataMap;
class DataValue;

//===================================================================
// DataItem
//===================================================================
class DataItem
{
public:
    virtual ~DataItem();

    enum dataTypes {
        UNINIT_TYPE = 0,
        VALUE_TYPE = 1,
        MAP_TYPE = 2,
        ARRAY_TYPE = 3
    };

    enum dataValueTypes {
        UNINIT_VALUE_TYPE = 0,
        STRING_TYPE = 1,
        INT_TYPE = 2,
        FLOAT_TYPE = 3,
        BOOL_TYPE = 4,
    };

    // getter
    virtual DataItem* operator[](const std::string key) = 0;
    virtual DataItem* operator[](const uint64_t index) = 0;
    virtual DataItem* get(const std::string key) = 0;
    virtual DataItem* get(const uint64_t index) = 0;
    virtual uint64_t size() = 0;

    // delete
    virtual bool remove(const std::string &key) = 0;
    virtual bool remove(const uint64_t index) = 0;

    // output
    virtual DataItem* copy() = 0;
    virtual std::string toString(bool indent=false,
                                 std::string *output=nullptr,
                                 uint32_t step=0) = 0;

    // checker
    dataTypes getType() const;
    bool isValue() const;
    bool isMap() const;
    bool isArray() const;

    // converter
    DataArray* toArray();
    DataMap* toMap();
    DataValue* toValue();

    // value-getter
    const std::string getString() const;
    int getInt();
    float getFloat();
    bool getBool();

protected:
    dataTypes m_type = UNINIT_TYPE;
    dataValueTypes m_valueType = UNINIT_VALUE_TYPE;

    void addIndent(std::string* output,
                   const bool indent,
                   const uint32_t level);
};

//===================================================================
// DataValue
//===================================================================
class DataValue : public DataItem
{
public:
    DataValue();
    DataValue(const char* text);
    DataValue(const std::string &text);
    DataValue(const int value);
    DataValue(const float value);
    DataValue(const bool value);
    ~DataValue();

    // setter
    dataValueTypes getValueType();
    void setValue(const char *item);
    void setValue(const std::string &item);
    void setValue(const int &item);
    void setValue(const float &item);
    void setValue(const bool &item);

    // getter
    DataItem* operator[](const std::string);
    DataItem* operator[](const uint64_t);
    DataItem* get(const std::string);
    DataItem* get(const uint64_t);
    uint64_t size();

    // delete
    bool remove(const std::string&);
    bool remove(const uint64_t);

    // output
    DataItem* copy();
    std::string toString(const bool=false,
                         std::string* output=nullptr,
                         const uint32_t=0);

    // content
    union DataValueContent
    {
        char* stringValue;
        int intValue;
        float floatValue;
        bool boolValue;
    };

    DataValueContent m_content;
};

//===================================================================
// DataMap
//===================================================================
class DataMap : public DataItem
{
public:
    DataMap();
    ~DataMap();

    // add
    bool insert(const std::string &key,
                DataItem* value,
                bool force = false);

    // getter
    DataItem* operator[](const std::string key);
    DataItem* operator[](const uint64_t index);
    DataItem* get(const std::string key);
    DataItem* get(const uint64_t index);
    uint64_t size();

    std::vector<std::string> getKeys();
    std::vector<DataItem*> getValues();
    bool contains(const std::string &key);

    // get values by keys
    std::string getStringByKey(const std::string &key);
    int getIntByKey(const std::string &key);
    float getFloatByKey(const std::string &key);

    // delete
    bool remove(const std::string &key);
    bool remove(const uint64_t index);

    // output
    DataItem* copy();
    std::string toString(const bool=false,
                         std::string* output=nullptr,
                         const uint32_t level=0);

    // content
    std::map<std::string, DataItem*> m_map;
};

//===================================================================
// DataArray
//===================================================================
class DataArray : public DataItem
{
public:
    DataArray();
    ~DataArray();

    // add
    bool append(DataItem* item);

    // getter
    DataItem* operator[](const std::string key);
    DataItem* operator[](const uint64_t index);
    DataItem* get(const std::string);
    DataItem* get(const uint64_t index);
    uint64_t size();

    // delete
    bool remove(const std::string &key);
    bool remove(const uint64_t index);

    // output
    DataItem* copy();
    std::string toString(const bool indent=false,
                         std::string* output=nullptr,
                         const uint32_t level=0);

    // content
    std::vector<DataItem*> m_array;
};

}  // namespace Common
}  // namespace Kitsune

#endif // DATAITEMS_H
