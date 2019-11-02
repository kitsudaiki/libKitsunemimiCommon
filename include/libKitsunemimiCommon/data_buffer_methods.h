/**
 *  @file       data_buffer_methods.h
 *
 *  @brief      Methods for the data-buffer.
 *
 *  @details    Besause I don't wanted to press all the methods into the data-buffer struct-object
 *              I separated these into this file without class. It for memory allocation and delete
 *              in data-buffers.
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef DATA_BUFFER_METHODS_H
#define DATA_BUFFER_METHODS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

namespace Kitsunemimi
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
} // namespace Kitsunemimi

#endif // DATA_BUFFER_METHODS_H
