/**
 *  @file    data_buffer_methods.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 *
 *  @brief methods for the data-buffer
 *
 *  @detail Besause I don't wanted to press all the methods into the data-buffer struct-object
 *          I separated these into this file without class. It for memory allocation and
 *          delete in data-buffers.
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
