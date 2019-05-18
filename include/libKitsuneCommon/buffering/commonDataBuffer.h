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

    /**
     * create and initialize a new buffer
     *
     * @param numberOfBlocks number of block of the initial allocation (at least one)
     */
    CommonDataBuffer(const uint32_t numberOfBlocks=1)
    {
        assert(blockSize % 512 == 0);
        if(numberOfBlocks < 1) {
            allocateBlocks(this, 1);
        }
        allocateBlocks(this, numberOfBlocks);
    }

    /**
     * simple construct which use allready allocated memory.
     * If this existing buffer is not a multiple of the blocksize,
     * it allocate new memory with a valid size.
     *
     * @param data pointer to the already allocated memory
     * @param size size of the allocated memory
     */
    CommonDataBuffer(uint8_t* data, const uint32_t size)
    {
        if(data == nullptr && size > 0)
        {
            this->data = data;
            numberOfBlocks = (size / blockSize) + 1;
            totalBufferSize = blockSize * numberOfBlocks;

            if(size % blockSize != 0) {
                allocateBlocks(this, 1);
            }
        }
    }

    /**
     * destructor to clear the allocated memory inside this object
     */
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

    /**
     * get a pointer to a specific block inside the buffer
     *
     * @param blockPosition number of the block inside the buffer
     * @return pointer to the buffer-position
     */
    uint8_t*
    getBlock(const uint32_t blockPosition)
    {
        if(blockPosition >= numberOfBlocks) {
            return nullptr;
        }

        return &data[blockPosition * blockSize];
    }

    /**
     * add an object to the buffer
     *
     * @param data pointer to the object, which shoulb be written to the buffer
     */
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
