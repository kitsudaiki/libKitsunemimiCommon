#ifndef DATAITEMS2_H
#define DATAITEMS2_H

#include <stdint.h>
#include <vector>
#include <string>
#include <map>

#include <libKitsunemimiCommon/buffer/data_buffer.h>

namespace Kitsunemimi
{

class DataItem2
{
public:
    enum kType
    {
        UNDEFINED_KTYPE = 0,
        INT64_KTYPE = 1,
        UINT64_KTYPE = 2,
        FLOAT64_KTYPE = 3,
        BOOL_KTYPE = 4,
        STRING_KTYPE = 5,
        BYTE_KTYPE = 6,
        ARRAY_KTYPE = 7,
        MAP_KTYPE = 8,
        VALUE_KTYPE = 9,
    };

    DataItem2();
    DataItem2(const DataItem2 &otherItem);
    DataItem2(const char* value);
    DataItem2(const std::string &value);
    DataItem2(const int64_t value);
    DataItem2(const uint64_t value);
    DataItem2(const double value);
    DataItem2(const bool value);

    // getter
    DataItem2* operator[](const std::string &key) const;
    DataItem2* operator[](const uint64_t index) const;
    DataItem2* get(const std::string key) const;
    DataItem2* get(const uint64_t index) const;
    uint64_t size() const;

    bool setValue(const char* value);
    bool setValue(const std::string &value);
    bool setValue(const int64_t &value);
    bool setValue(const uint64_t &value);
    bool setValue(const double &value);
    bool setValue(const bool &value);
    bool insert(const std::string &key,
                const DataItem2 &value,
                bool force = false);
    bool append(const DataItem2 &value);
    bool replaceItem(const uint32_t index,
                     const DataItem2 &value);
    bool deleteContent();

    // delete
    bool remove(const std::string &key);
    bool remove(const uint64_t index);
    void clear();

    // output
    DataItem2* copy() const;
    const std::string toString(bool indent = false,
                               std::string* output = nullptr,
                               uint32_t step = 0) const;

    // checker
    kType getType() const;
    bool isValue() const;
    bool isMap() const;
    bool isArray() const;
    bool isStringValue() const;
    bool isIntValue() const;
    bool isFloatValue() const;
    bool isBoolValue() const;
    bool isNull() const;

    // value-getter
    const std::string getString() const;
    int64_t getInt64();
    uint64_t getUInt64();
    double getDouble();
    bool getBool();
    const std::vector<std::string> getKeys() const;

private:
    struct KEntry
    {
        uint8_t type = UNDEFINED_KTYPE;
        uint8_t metaType = UNDEFINED_KTYPE;
        uint8_t padding[2];
        uint32_t keySize = 0;
        uint64_t valSize = 0;
        uint64_t posParent = 0;
        uint64_t posNext = 0;
    }; // size: 32

    template<typename T>
    inline T
    getSimpleVal()
    {
        return *static_cast<T*>(static_cast<void*>(&m_rootEntry[1]));
    }

    template<typename T>
    inline T*
    getPayload(const uint64_t pos)
    {
        uint8_t* ptr = static_cast<uint8_t*>(m_buffer.data);
        return static_cast<T*>(static_cast<void*>(&ptr[pos + sizeof(KEntry)]));
    }

    uint64_t calclulateBlocks(const uint64_t size);

    DataBuffer m_buffer;
    KEntry* m_rootEntry = nullptr;
    bool m_deletable = true;

    void basicInit();
};

}

#endif // DATAITEMS2_H
