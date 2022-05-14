#include <libKitsunemimiCommon/common_items/data_items2.h>

namespace Kitsunemimi
{

/**
 * @brief DataItem2::DataItem2
 */
DataItem2::DataItem2()
{
    basicInit();
}

/**
 * @brief DataItem2::DataItem2
 * @param otherItem
 */
DataItem2::DataItem2(const DataItem2 &otherItem)
{
    m_buffer = DataBuffer(otherItem.m_buffer);
    m_rootEntry = static_cast<KEntry*>(m_buffer.data);
    assert(m_rootEntry != nullptr);
}

/**
 * @brief DataItem2::DataItem2
 * @param value
 */
DataItem2::DataItem2(const char* value)
{
    const std::string strVal(value);
    allocateBlocks_DataBuffer(m_buffer, calclulateBlocks(strVal.size()));
    basicInit();

    m_rootEntry->metaType = kType::VALUE_KTYPE;
    m_rootEntry->type = kType::STRING_KTYPE;
    m_rootEntry->valSize = strVal.size();

    char* ptr = getPayload<char>(0);
    memcpy(ptr, value, strVal.size());
}

/**
 * @brief DataItem2::DataItem2
 * @param value
 */
DataItem2::DataItem2(const std::string &value)
{
    allocateBlocks_DataBuffer(m_buffer, calclulateBlocks(value.size()));
    basicInit();

    m_rootEntry->metaType = kType::VALUE_KTYPE;
    m_rootEntry->type = kType::STRING_KTYPE;
    m_rootEntry->valSize = value.size();

    char* ptr = getPayload<char>(0);
    memcpy(ptr, value.c_str(), value.size());
}

/**
 * @brief DataItem2::DataItem2
 * @param value
 */
DataItem2::DataItem2(const int64_t value)
{
    basicInit();

    m_rootEntry->metaType = kType::VALUE_KTYPE;
    m_rootEntry->type = kType::INT64_KTYPE;
    m_rootEntry->valSize = sizeof(int64_t);

    int64_t* ptr = getPayload<int64_t>(0);
    ptr[0] = value;
}

/**
 * @brief DataItem2::DataItem2
 * @param value
 */
DataItem2::DataItem2(const uint64_t value)
{
    basicInit();

    m_rootEntry->metaType = kType::VALUE_KTYPE;
    m_rootEntry->type = kType::UINT64_KTYPE;
    m_rootEntry->valSize = sizeof(uint64_t);

    uint64_t* ptr = getPayload<uint64_t>(0);
    ptr[0] = value;
}

/**
 * @brief DataItem2::DataItem2
 * @param value
 */
DataItem2::DataItem2(const double value)
{
    basicInit();

    m_rootEntry->metaType = kType::VALUE_KTYPE;
    m_rootEntry->type = kType::FLOAT64_KTYPE;
    m_rootEntry->valSize = sizeof(double);

    double* ptr = getPayload<double>(0);
    ptr[0] = value;
}

/**
 * @brief DataItem2::DataItem2
 * @param value
 */
DataItem2::DataItem2(const bool value)
{
    basicInit();

    m_rootEntry->metaType = kType::VALUE_KTYPE;
    m_rootEntry->type = kType::BOOL_KTYPE;
    // give bool also a size of 8 bytes in buffer to avoid spcific handling only for bool
    // this way there exist only 8-byte values of byte-lists
    m_rootEntry->valSize = 8;

    bool* ptr = getPayload<bool>(0);
    ptr[0] = value;
}

/**
 * @brief DataItem2::operator []
 * @param key
 * @return
 */
DataItem2*
DataItem2::operator[](const std::string &key) const
{

}

/**
 * @brief DataItem2::operator []
 * @param index
 * @return
 */
DataItem2*
DataItem2::operator[](const uint64_t index) const
{

}

/**
 * @brief DataItem2::get
 * @param key
 * @return
 */
DataItem2*
DataItem2::get(const std::string key) const
{

}

/**
 * @brief DataItem2::get
 * @param index
 * @return
 */
DataItem2*
DataItem2::get(const uint64_t index) const
{

}

/**
 * @brief DataItem2::size
 * @return
 */
uint64_t
DataItem2::size() const
{

}

/**
 * @brief DataItem2::remove
 * @param key
 * @return
 */
bool
DataItem2::remove(const std::string &key)
{

}

/**
 * @brief DataItem2::remove
 * @param index
 * @return
 */
bool
DataItem2::remove(const uint64_t index)
{

}

/**
 * @brief DataItem2::clear
 */
void
DataItem2::clear()
{

}

/**
 * @brief DataItem2::copy
 * @return
 */
DataItem2*
DataItem2::copy() const
{

}

/**
 * @brief DataItem2::toString
 * @param indent
 * @param output
 * @param step
 * @return
 */
const std::string
DataItem2::toString(bool indent, std::string *output, uint32_t step) const
{

}

/**
 * @brief DataItem2::getType
 * @return
 */
DataItem2::kType
DataItem2::getType() const
{

}

/**
 * @brief DataItem2::isValue
 * @return
 */
bool
DataItem2::isValue() const
{

}

/**
 * @brief DataItem2::isMap
 * @return
 */
bool
DataItem2::isMap() const
{

}

/**
 * @brief DataItem2::isArray
 * @return
 */
bool
DataItem2::isArray() const
{

}

/**
 * @brief DataItem2::isStringValue
 * @return
 */
bool
DataItem2::isStringValue() const
{

}

/**
 * @brief DataItem2::isIntValue
 * @return
 */
bool
DataItem2::isIntValue() const
{

}

/**
 * @brief DataItem2::isFloatValue
 * @return
 */
bool
DataItem2::isFloatValue() const
{

}

/**
 * @brief DataItem2::isBoolValue
 * @return
 */
bool
DataItem2::isBoolValue() const
{

}

/**
 * @brief DataItem2::isNull
 * @return
 */
bool
DataItem2::isNull() const
{

}

/**
 * @brief DataItem2::getString
 * @return
 */
const std::string
DataItem2::getString() const
{
    if(m_rootEntry->type != kType::STRING_KTYPE) {
        return std::string();
    }

    const char* content = static_cast<const char*>(static_cast<const void*>(&m_rootEntry[1]));
    const std::string result(content, m_rootEntry->valSize);
    return result;
}

/**
 * @brief DataItem2::getInt64
 * @return
 */
int64_t
DataItem2::getInt64()
{
    if(m_rootEntry->type != kType::INT64_KTYPE) {
        return 0;
    }

    return getSimpleVal<int64_t>();
}

/**
 * @brief DataItem2::getUInt64
 * @return
 */
uint64_t
DataItem2::getUInt64()
{
    if(m_rootEntry->type != kType::UINT64_KTYPE) {
        return 0;
    }

    return getSimpleVal<uint64_t>();
}

/**
 * @brief DataItem2::getDouble
 * @return
 */
double
DataItem2::getDouble()
{
    if(m_rootEntry->type != kType::FLOAT64_KTYPE) {
        return 0.0f;
    }

    return getSimpleVal<double>();
}

/**
 * @brief DataItem2::getBool
 * @return
 */
bool
DataItem2::getBool()
{
    if(m_rootEntry->type != kType::BOOL_KTYPE) {
        return false;
    }

    return getSimpleVal<bool>();
}

/**
 * @brief DataItem2::getKeys
 * @return
 */
const std::vector<std::string>
DataItem2::getKeys() const
{

}

uint64_t
DataItem2::calclulateBlocks(const uint64_t size)
{
    return calcBytesToBlocks(size + sizeof(KEntry));
}

void DataItem2::basicInit()
{
    m_rootEntry = static_cast<KEntry*>(m_buffer.data);
    assert(m_rootEntry != nullptr);
    m_rootEntry[0] = KEntry();
}

}
