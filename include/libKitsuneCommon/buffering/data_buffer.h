/**
 *  @file    dataBuffer.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef DATA_BUFFER_H
#define DATA_BUFFER_H

#include <string.h>
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#include <buffering/data_buffer_methods.h>

namespace Kitsune
{
namespace Common
{

struct DataBuffer
{
    uint16_t blockSize = 4096;
    uint64_t numberOfBlocks = 0;
    uint64_t bufferPosition = 0;
    uint64_t totalBufferSize = 0;
    void* data = nullptr;
    uint8_t inUse = 0;
    // padding to expand the size of the struct to a multiple of 8
    uint8_t padding[5];

    /**
     * @brief constructor
     *
     * @param numberOfBlocks number of block of the initial allocation (at least one)
     */
    DataBuffer(const uint32_t numberOfBlocks = 1)
    {
        assert(blockSize % 512 == 0);
        if(numberOfBlocks < 1) {
            allocateBlocks(this, 1);
        }
        allocateBlocks(this, numberOfBlocks);
    }

    /**
     * @brief copy-constructor
     */
    DataBuffer(const DataBuffer &other)
    {
        // copy blockSize first to make sure, that the reset reallocate the correct total memroy
        blockSize = other.blockSize;
        allocateBlocks(this, other.numberOfBlocks);
        assert(totalBufferSize == other.totalBufferSize);

        inUse = other.inUse;
        bufferPosition = other.bufferPosition;
        memcpy(data, other.data, bufferPosition);
    }

    /**
     * @brief simple additonal construct which use allready allocated memory.
     *        If this existing buffer is not a multiple of the blocksize,
     *        it allocate new memory with a valid size.
     *
     * @param data pointer to the already allocated memory
     * @param size size of the allocated memory
     */
    DataBuffer(void* data, const uint64_t size)
    {
        if(data == nullptr
                && size > 0)
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
     * @brief destructor to clear the allocated memory inside this object
     */
    ~DataBuffer()
    {
        // deallocate the buffer
        if(data != nullptr
                && inUse == 1)
        {
            alignedFree(data);
            inUse = 0;
            data = nullptr;
            numberOfBlocks = 0;
        }
    }

    /**
     * @brief get a pointer to a specific block inside the buffer
     *
     * @param blockPosition number of the block inside the buffer
     *
     * @return pointer to the buffer-position
     */
    uint8_t*
    getBlock(const uint32_t blockPosition)
    {
        // precheck
        if(blockPosition >= numberOfBlocks) {
            return nullptr;
        }

        // get specific block of the data
        uint8_t* dataByte = static_cast<uint8_t*>(data);
        return &dataByte[blockPosition * blockSize];
    }

    /**
     * @brief add an object to the buffer
     *
     * @param data pointer to the object, which shoulb be written to the buffer
     */
    template <typename T>
    bool
    addData(T* data)
    {
        return addDataToBuffer(this, data, sizeof(T));
    }

    /**
     * @brief reset a buffer and clears the data, so it is like the buffer is totally new
     *
     * @return false if precheck or allocation failed, else true
     */
    bool
    reset()
    {
        return resetBuffer(this);
    }

} __attribute__((packed));

} // namespace Common
} // namespace Kitsune

#endif // DATABUFFER_H
