/**
 *  @file       item_buffer.h
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef ITEM_BUFFER_H
#define ITEM_BUFFER_H

#include <libKitsunemimiCommon/buffer/data_buffer.h>

#define ITEM_BUFFER_UNDEFINE_POS 0xFFFFFFFFFFFFFFFF

namespace Kitsunemimi
{

class ItemBuffer;
template<typename T>
inline T* getBuffer(ItemBuffer &itembuffer);

class ItemBuffer
{
public:
    enum SectionStatus
    {
        UNDEFINED_SECTION = 0,
        ACTIVE_SECTION = 1,
        DELETED_SECTION = 2,
    };

    uint32_t itemSize = 0;
    uint64_t itemCapacity = 0;
    uint64_t numberOfItems = 0;
    DataBuffer buffer = DataBuffer(1);
    void* staticData = nullptr;
    void* itemData = nullptr;

    ItemBuffer();

    /**
     * @brief initialize buffer by allocating memory and init with default-items
     *
     * @param numberOfItems number of items to preallocate
     *
     * @return true, if successfull, else false
     */
    template<typename T>
    bool initBuffer(const uint64_t numberOfItems,
                    const uint64_t staticSize = 0)
    {
        // allocate memory
        const bool ret = initDataBlocks(numberOfItems, sizeof(T), staticSize);
        if(ret == false) {
            return false;
        }

        // init buffer with default-itemes
        T* items = static_cast<T*>(itemData);
        T newItem;
        std::fill_n(items, numberOfItems, newItem);
        this->numberOfItems = numberOfItems;

        return true;
    }

    /**
     * @brief add a new items at an empty position inside of the buffer
     *
     * @param item new item to write into the buffer
     *
     * @return position inside of the buffer, where the new item was added, if successful, or
     *         2^64-1 if the buffer is already full
     */
    template<typename T>
    uint64_t addNewItem(const T &item)
    {
        // init invalid default-value
        uint64_t position = ITEM_BUFFER_UNDEFINE_POS;

        // precheck
        if(numberOfItems >= itemCapacity) {
            return position;
        }

        while(m_lock.test_and_set(std::memory_order_acquire)) { asm(""); }

        // get item-position inside of the buffer
        position = reserveDynamicItem();
        if(position == ITEM_BUFFER_UNDEFINE_POS) {
            return position;
        }

        // write new item at the position
        T* array = static_cast<T*>(itemData);
        array[position] = item;

        m_lock.clear(std::memory_order_release);

        return position;
    }

    bool deleteItem(const uint64_t itemPos);
    void deleteAll();

private:
    std::atomic_flag m_lock = ATOMIC_FLAG_INIT;

    uint64_t m_bytePositionOfFirstEmptyBlock = ITEM_BUFFER_UNDEFINE_POS;
    uint64_t m_bytePositionOfLastEmptyBlock = ITEM_BUFFER_UNDEFINE_POS;

    bool initDataBlocks(const uint64_t numberOfItems,
                        const uint32_t itemSize,
                        const uint64_t staticSize);

    uint64_t reuseItemPosition();
    uint64_t reserveDynamicItem();
};

/**
 * @brief get content of an item-buffer as array
 *
 * @param itembuffer buffer to convert
 *
 * @return casted pointer of the item-buffer-content
 */
template<typename T>
inline T*
getBuffer(ItemBuffer &itembuffer)
{
    return static_cast<T*>(itembuffer.itemData);
}

}

#endif // ITEM_BUFFER_H
