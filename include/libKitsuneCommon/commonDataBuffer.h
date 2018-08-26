/**
 *  @file    commonDataBuffer.h
 *  @author  Tobias Anker
 *
 *  @section DESCRIPTION
 *
 *  TODO: Description
 */

#ifndef RAMMEMORY_H
#define RAMMEMORY_H

#include <stdint.h>
#include <string.h>
#include <iostream>
#include <string>
#include <assert.h>

namespace Kitsune
{
class CommonDataBuffer
{
public:
    CommonDataBuffer();
    CommonDataBuffer(void* data, uint32_t size);
    ~CommonDataBuffer();

    bool allocateBlocks(const uint32_t numberOfBlocks);

    uint32_t getNumberOfBlocks() const;
    uint32_t getBlockSize() const;

    uint8_t *getBufferPointer();
    uint8_t *getBlock(const uint32_t blockNumber);

    void setNumberOfWrittenBytes(const uint32_t numberOfWrittenBytes);
    uint64_t getNumberOfWrittenBytes() const;

private:
    uint32_t m_numberOfBlocks = 0;
    uint32_t m_numberOfWrittenBytes = 0;

    void *m_buffer = nullptr;

    void* aligned_malloc(const uint32_t numberOfBytes);
    bool aligned_free(void *ptr);
};

}

#endif // RAMMEMORY_H
