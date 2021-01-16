/**
 *  @file       object_methods.cpp
 *
 *  @brief      often used methods for object-operations
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <libKitsunemimiCommon/common_methods/object_methods.h>

namespace Kitsunemimi
{

/**
 * @brief hexlify an object into a string
 *
 * @param object pointer to the object, which should be hexlified
 * @param size size of the object
 *
 * @return hex-version of the input-object as string
 */
void
hexlify(std::string &outputString,
        void* object,
        const uint64_t size)
{
    uint8_t* bytestream = static_cast<uint8_t*>(object);
    std::stringstream stream;

    // iterate over all bytes of the object
    for(uint64_t i = size; i != 0; i--)
    {
        // special rul to fix the length
        if(bytestream[i - 1] < 16) {
            stream << "0";
        }
        stream << std::hex << (int)bytestream[i - 1];
    }

    outputString = stream.str();
}

struct Base64Buffer {
    uint8_t buffer[3];
};

/**
 * @brief convert value into a Base64 character
 *
 * @param val value to convert
 *
 * @return resulting character
 */
inline char
convertValueToBase64(const char val)
{
    if(val >= 0 && val < 26) {
        return val + 65;
    }

    if(val >= 26 && val < 52) {
        return val + 97 - 26;
    }

    if(val >= 52 && val < 62) {
        return val + 48 - 52;
    }

    if(val == 62) {
        return '+';
    }

    return '/';
}

/**
 * @brief convert one segment of 3 bytes into a Base64 segment of 4 characters
 *
 * @param result pointer at the specific position inside the char-arrary for the Base64 result
 * @param buf buffer with 3 Bytes to convert
 * @param count number of bytes in the buffer to convert
 */
inline void
convertToBase64(char* result,
                const Base64Buffer& buf,
                const uint8_t count)
{
    // prepare bufferValue
    uint32_t temp = 0;
    temp |= buf.buffer[0];
    temp = temp << 8;
    temp |= buf.buffer[1];
    temp = temp << 8;
    temp |= buf.buffer[2];

    // convert last byte
    if(count == 3) {
        result[3] = convertValueToBase64(static_cast<char>(temp & 0x3F));
    }

    temp = temp >> 6;

    // convert second byte
    if(count >= 2) {
        result[2] = convertValueToBase64(static_cast<char>(temp & 0x3F));
    }

    // convert first byte
    temp = temp >> 6;
    result[1] = convertValueToBase64(static_cast<char>(temp & 0x3F));
    temp = temp >> 6;
    result[0] = convertValueToBase64(static_cast<char>(temp & 0x3F));
}

/**
 * @brief encodeBase64
 *
 * @param output reference for the resulting string
 * @param data data to convert into Base64
 * @param dataSize number of bytes to convert
 */
void
encodeBase64(std::string &output,
             const void* data,
             const uint64_t dataSize)
{
    // prepare buffer for result
    uint64_t resultSize = dataSize / 3;
    if(dataSize % 3 != 0) {
        resultSize++;
    }
    resultSize *= 4;
    char* result = new char[resultSize];

    // convert input
    const Base64Buffer* buf = static_cast<const Base64Buffer*>(data);

    // convert base part
    for(uint64_t i = 0; i < dataSize / 3; i++) {
        convertToBase64(&result[i * 4], buf[i], 3);
    }

    // convert padding
    if(dataSize % 3 == 2)
    {
        const uint64_t endPos = dataSize / 3;
        Base64Buffer tempBuf = buf[endPos];
        tempBuf.buffer[1] = 0;
        tempBuf.buffer[2] = 0;
        convertToBase64(&result[endPos * 4], tempBuf, 2);
        result[resultSize - 1] = '=';
    }
    else if(dataSize % 3 == 1)
    {
        const uint64_t endPos = dataSize / 3;
        Base64Buffer tempBuf = buf[endPos];
        tempBuf.buffer[1] = 0;
        convertToBase64(&result[endPos * 4], tempBuf, 1);
        result[resultSize - 2] = '=';
        result[resultSize - 1] = '=';
    }

    // prepare output and delete buffer
    output = std::string(result, resultSize);
    delete[] result;
}


} // namespace Kitsunemimi
