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

void hexlify(std::string &outputString,
             void* object,
             const uint64_t size);

template <typename T>
void
hexlify(std::string &outputString, T* object)
{
    hexlify(outputString, object, sizeof(T));
}

} // namespace Kitsunemimi
#endif // OBJECT_METHODS_H
