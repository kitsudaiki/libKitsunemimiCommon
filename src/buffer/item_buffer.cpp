/**
 *  @file       item_buffer.cpp
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <libKitsunemimiCommon/buffer/item_buffer.h>

namespace Kitsunemimi
{

struct EmptyPlaceHolder
{
    uint8_t status = ItemBuffer::DELETED_SECTION;
    uint64_t bytePositionOfNextEmptyBlock = 0xFFFFFFFFFFFFFFFF;
} __attribute__((packed));

ItemBuffer::ItemBuffer() {}

/**
 * @brief ItemBuffer::deleteAll
 * @return
 */
void
ItemBuffer::deleteAll()
{
    while(m_lock.test_and_set(std::memory_order_acquire)) { asm(""); }
    for(uint64_t i = 0; i < itemCapacity; i++) {
        deleteItem(i);
    }
    m_lock.clear(std::memory_order_release);
}

/**
 * initialize the node-list of the brick
 *
 * @return false if nodes are already initialized, esle true
*/
bool
ItemBuffer::initDataBlocks(const uint64_t numberOfItems,
                           const uint32_t itemSize)
{
    if(itemSize == 0) {
        return false;
    }

    // update meta-data of the brick
    this->itemSize = itemSize;
    this->itemCapacity = numberOfItems;
    const uint64_t requiredNumberOfBlocks = ((numberOfItems * itemSize)
                                             / buffer.blockSize) + 1;

    // allocate blocks in buffer
    //data.buffer = DataBuffer(requiredNumberOfBlocks);
    Kitsunemimi::allocateBlocks_DataBuffer(buffer, requiredNumberOfBlocks);
    buffer.bufferPosition = numberOfItems * itemSize;

    return true;
}

/**
* delete a specific item from the buffer by replacing it with a placeholder-item
*
* @return false if buffer is invalid or item already deleted, else true
*/
bool
ItemBuffer::deleteItem(const uint64_t itemPos)
{
    if(itemPos >= itemCapacity
            || numberOfItems == 0)
    {
        return false;
    }

    // get buffer
    uint8_t* blockBegin = static_cast<uint8_t*>(buffer.data);

    // data of the position
    const uint64_t currentBytePos = itemPos * itemSize;
    void* voidBuffer = static_cast<void*>(&blockBegin[currentBytePos]);
    EmptyPlaceHolder* placeHolder = static_cast<EmptyPlaceHolder*>(voidBuffer);

    // check that the position is active and not already deleted
    if(placeHolder->status == DELETED_SECTION) {
        return false;
    }

    // overwrite item with a placeholder and set the position as delted
    placeHolder->bytePositionOfNextEmptyBlock = 0xFFFFFFFFFFFFFFFF;
    placeHolder->status = DELETED_SECTION;

    // modify last place-holder
    const uint64_t blockPosition = m_bytePositionOfLastEmptyBlock;
    if(blockPosition != 0xFFFFFFFFFFFFFFFF)
    {
        voidBuffer = static_cast<void*>(&blockBegin[blockPosition]);
        EmptyPlaceHolder* lastPlaceHolder = static_cast<EmptyPlaceHolder*>(voidBuffer);
        lastPlaceHolder->bytePositionOfNextEmptyBlock = currentBytePos;
    }

    // set global values
    m_bytePositionOfLastEmptyBlock = currentBytePos;
    if(m_bytePositionOfFirstEmptyBlock == 0xFFFFFFFFFFFFFFFF) {
        m_bytePositionOfFirstEmptyBlock = currentBytePos;
    }

    numberOfItems--;

    return true;
}

//==================================================================================================

/**
 * try to reuse a deleted buffer segment
 *
 * @return item-position in the buffer, else UNINIT_STATE_32 if no empty space in buffer exist
 */
uint64_t
ItemBuffer::reuseItemPosition()
{
    // get byte-position of free space, if exist
    const uint64_t selectedPosition = m_bytePositionOfFirstEmptyBlock;
    if(selectedPosition == 0xFFFFFFFFFFFFFFFF) {
        return 0xFFFFFFFFFFFFFFFF;
    }

    // set pointer to the next empty space
    uint8_t* blockBegin = static_cast<uint8_t*>(buffer.data);
    void* voidBuffer = static_cast<void*>(&blockBegin[selectedPosition]);
    EmptyPlaceHolder* secetedPlaceHolder = static_cast<EmptyPlaceHolder*>(voidBuffer);
    m_bytePositionOfFirstEmptyBlock = secetedPlaceHolder->bytePositionOfNextEmptyBlock;

    // reset pointer, if no more free spaces exist
    if(m_bytePositionOfFirstEmptyBlock == 0xFFFFFFFFFFFFFFFF) {
        m_bytePositionOfLastEmptyBlock = 0xFFFFFFFFFFFFFFFF;
    }

    // convert byte-position to item-position and return this
    numberOfItems++;
    assert(selectedPosition % itemSize == 0);

    return selectedPosition / itemSize;
}

//==================================================================================================

/**
* add a new forward-edge-section
*
* @return id of the new section, else UNINIT_STATE_32 if allocation failed
*/
uint64_t
ItemBuffer::reserveDynamicItem()
{
    // try to reuse item
    const uint64_t reusePos = reuseItemPosition();
    if(reusePos != 0xFFFFFFFFFFFFFFFF) {
        return reusePos;
    }

    // calculate size information
    const uint32_t blockSize = buffer.blockSize;
    const uint64_t numberOfBlocks = buffer.numberOfBlocks;
    const uint64_t newNumberOfBlocks = (((itemCapacity + 1) * itemSize) / blockSize) + 1;

    // allocate a new block, if necessary
    if(numberOfBlocks < newNumberOfBlocks) {
        Kitsunemimi::allocateBlocks_DataBuffer(buffer, newNumberOfBlocks - numberOfBlocks);
    }

    itemCapacity++;

    return itemCapacity-1;
}

}
