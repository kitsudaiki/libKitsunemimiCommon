/**
 *  @file    dataBufferMethods.hpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef DATABUFFERMETHODS_HPP
#define DATABUFFERMETHODS_HPP

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

namespace Kitsune
{
namespace Common
{

struct DataBuffer;


bool addDataToBuffer(DataBuffer *buffer,
                     const void* data,
                     const uint64_t dataSize);
bool allocateBlocks(DataBuffer* buffer,
                    const uint64_t numberOfBlocks);
bool resetBuffer(DataBuffer* buffer,
                 const uint64_t numberOfBlocks = 1);

void* alignedMalloc(const uint16_t blockSize,
                    const uint64_t numberOfBytes);
bool alignedFree(void *ptr);

} // namespace Common
} // namespace Kitsune

#endif // DATABUFFERMETHODS_HPP
