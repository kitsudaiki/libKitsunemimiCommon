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
    CommonDataBuffer(const uint32_t numberOfBlocks = 1);
    CommonDataBuffer(void* data, uint32_t size);
    ~CommonDataBuffer();

    void addData(void* data, const uint64_t size);

    bool allocateBlocks(const uint32_t numberOfBlocks);
    void resetBuffer();

    uint32_t getNumberOfBlocks() const;
    uint32_t getBlockSize() const;
    uint64_t getTotalBufferSize() const;

    uint8_t *getBufferPointer();
    uint8_t *getBlock(const uint32_t blockNumber);

    void addNumberOfWrittenBytes(const uint64_t numberOfWrittenBytes);
    uint64_t getNumberOfWrittenBytes() const;

    template <typename T>
    bool addData(T *data)
    {
        if(data != nullptr && this != nullptr) {
            addData((void*)data, sizeof(T));
            return true;
        }
        return false;
    }

private:
    uint32_t m_numberOfBlocks = 0;
    uint64_t m_numberOfWrittenBytes = 0;

    void* m_buffer = nullptr;

    void* aligned_malloc(const uint32_t numberOfBytes);
    bool aligned_free(void *ptr);
};

}

#endif // RAMMEMORY_H