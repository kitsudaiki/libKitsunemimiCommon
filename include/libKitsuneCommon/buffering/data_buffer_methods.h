/**
 *  @file    data_buffer_methods.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef DATA_BUFFER_METHODS_H
#define DATA_BUFFER_METHODS_H

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

#endif // DATABUFFERMETHODS_H
