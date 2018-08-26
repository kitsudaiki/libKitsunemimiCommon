/**
 *  @file    commonDataBuffer.cpp
 *  @author  Tobias Anker
 *
 *  @section DESCRIPTION
 *
 *  TODO: Description
 */

#include <commonDataBuffer.h>

#define BLOCKSIZE 4096

namespace Kitsune
{

/**
 * @brief CommonDataBuffer::CommonDataBuffer creates and initialize a buffer with a file
 */
CommonDataBuffer::CommonDataBuffer()
{
    assert(BLOCKSIZE % 512 == 0);
    allocateBlocks(1);
}

/**
 * @brief CommonDataBuffer::CommonDataBuffer init data-buffer with existing datas
 * @param data already existing data
 */
CommonDataBuffer::CommonDataBuffer(void *data, uint32_t size)
{
    if(m_buffer == nullptr && size > 0) {
        m_buffer = data;
        m_numberOfBlocks = (size / BLOCKSIZE) + 1;
    }
}

/**
 * @brief CommonDataBuffer::~IOBuffer close the buffer at the end
 */
CommonDataBuffer::~CommonDataBuffer()
{
    // deallocate the buffer
    if(aligned_free(m_buffer)) {
        m_buffer = nullptr;
        m_numberOfBlocks = 0;
    }
}

/**
 * @brief CommonDataBuffer::getNumberOfBlocks
 * @return number of current allocated blocks
 */
uint32_t CommonDataBuffer::getNumberOfBlocks() const
{
    return m_numberOfBlocks;
}

/**
 * @brief CommonDataBuffer::getBlockSize
 * @return
 */
uint32_t CommonDataBuffer::getBlockSize() const
{
    return BLOCKSIZE;
}

/**
 * @brief CommonDataBuffer::getBufferPointer
 * @return
 */
uint8_t *CommonDataBuffer::getBufferPointer()
{
    return (uint8_t*)m_buffer;
}

/**
 * @brief CommonDataBuffer::getBlock
 * @param blockNumber
 * @return
 */
uint8_t* CommonDataBuffer::getBlock(const uint32_t blockNumber)
{
    if(blockNumber >= m_numberOfBlocks) {
        return nullptr;
    }

    return (uint8_t*)m_buffer+(blockNumber * BLOCKSIZE);
}

/**
 * @brief CommonDataBuffer::setNumberOfWrittenBytes
 */
void CommonDataBuffer::setNumberOfWrittenBytes(const uint32_t numberOfWrittenBytes)
{
    m_numberOfWrittenBytes = numberOfWrittenBytes;
}

/**
 * @brief CommonDataBuffer::getNumberOfWrittenBytes
 * @return
 */
uint32_t CommonDataBuffer::getNumberOfWrittenBytes() const
{
    return m_numberOfWrittenBytes;
}

/**
 * @brief CommonDataBuffer::allocateBlocks allocate more memory for the buffer
 * @param numberOfBlocks number of blocks to allocate
 * @return true, if successful, else false
 */
bool CommonDataBuffer::allocateBlocks(const uint32_t numberOfBlocks)
{
    if(numberOfBlocks == 0) {
        return true;
    }

    // create the new buffer
    uint32_t newSize = m_numberOfBlocks + numberOfBlocks;
    void* newBuffer = aligned_malloc(newSize * BLOCKSIZE);
    memset(newBuffer, 0, newSize * BLOCKSIZE);

    // copy the content of the old buffer to the new and deallocate the old
    if(m_buffer != nullptr) {
        memcpy(newBuffer, m_buffer, m_numberOfBlocks * BLOCKSIZE);
        aligned_free(m_buffer);
    }

    // set the new values
    m_numberOfBlocks = newSize;
    m_buffer = newBuffer;

    return true;
}

/**
 * @brief CommonDataBuffer::aligned_malloc allocate a number of aligned bytes
 * @param numberOfBytes bytes to allocate
 * @return pointer to the allocated memory
 */
void* CommonDataBuffer::aligned_malloc(const uint32_t numberOfBytes)
{
    void *mem = malloc(numberOfBytes+BLOCKSIZE+sizeof(void*));
    void **ptr = (void**)((uintptr_t)((uint8_t*)mem+BLOCKSIZE+sizeof(void*)) & ~(BLOCKSIZE-1));
    ptr[-1] = mem;
    memset(ptr, 0, numberOfBytes);
    return ptr;
}

/**
 * @brief CommonDataBuffer::aligned_free to free aligned memory
 * @param ptr pointer to the memory to free
 * @return true, if pointer not nullptr, else false
 */
bool CommonDataBuffer::aligned_free(void *ptr)
{
    if(ptr != nullptr) {
        free(((void**)ptr)[-1]);
        ptr = nullptr;
        return true;
    }
    return false;
}

}
