/**
 *  @file    commonDataBuffer.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef RAMMEMORY_H
#define RAMMEMORY_H

#include <string.h>
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#include <buffering/commonDataBufferMethods.h>

namespace Kitsune
{

struct CommonDataBuffer
{
    uint32_t blockSize = 4096;
    uint64_t numberOfBlocks = 0;
    uint64_t bufferPosition = 0;
    uint64_t totalBufferSize = 0;
    uint8_t* data = nullptr;

    CommonDataBuffer(const uint32_t numberOfBlocks=1)
    {
        assert(blockSize % 512 == 0);
        if(numberOfBlocks < 1) {
            allocateBlocks(this, 1);
        }
        allocateBlocks(this, numberOfBlocks);
    }

    CommonDataBuffer(uint8_t *data, const uint32_t size)
    {
        if(data == nullptr && size > 0)
        {
            this->data = data;
            numberOfBlocks = (size / blockSize) + 1;
        }
    }

    ~CommonDataBuffer()
    {
        // deallocate the buffer
        if(data != nullptr)
        {
            free(data);
            data = nullptr;
            numberOfBlocks = 0;
        }
    }

    uint8_t*
    getBlock(const uint32_t blockPosition)
    {
        if(blockPosition >= numberOfBlocks) {
            return nullptr;
        }

        return &data[blockPosition * blockSize];
    }

    template <typename T>
    bool
    addData(T *data)
    {
        if(data != nullptr && data != nullptr)
        {
            addDataToBuffer(this, (uint8_t*)data, sizeof(T));
            return true;
        }
        return false;
    }
} __attribute__((packed));

}

#endif // RAMMEMORY_H
