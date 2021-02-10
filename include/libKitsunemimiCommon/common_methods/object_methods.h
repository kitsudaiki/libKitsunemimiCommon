/**
 *  @file       object_methods.h
 *
 *  @brief      often used methods for object-operations
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef OBJECT_METHODS_H
#define OBJECT_METHODS_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

namespace Kitsunemimi
{
struct DataBuffer;

void hexlify(std::string &outputString,
             const void* object,
             const uint64_t size);

template <typename T>
void hexlify(std::string &outputString, T* object) {
    hexlify(outputString, object, sizeof(T));
}

void encodeBase64(std::string &output,
                  const void* data,
                  const uint64_t dataSize);

template <typename T>
void encodeBase64(std::string &outputString, T* object) {
    encodeBase64(outputString, object, sizeof(T));
}

bool decodeBase64(DataBuffer &result,
                  const std::string &input);

} // namespace Kitsunemimi

#endif // OBJECT_METHODS_H
