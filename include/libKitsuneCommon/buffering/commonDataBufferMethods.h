#ifndef COMMONDATABUFFERMETHODS_H
#define COMMONDATABUFFERMETHODS_H

#include <stdint.h>
#include <string.h>
#include <iostream>
#include <string>
#include <assert.h>

namespace Kitsune
{
struct CommonDataBuffer;


void addDataToBuffer(CommonDataBuffer *buffer,
                     uint8_t *data,
                     const uint64_t size);
bool allocateBlocks(CommonDataBuffer *buffer,
                    const uint32_t numberOfBlocks);
void resetBuffer(CommonDataBuffer *buffer);
uint8_t* aligned_malloc(const uint32_t numberOfBlocks,
                        const uint32_t blockSize);
bool aligned_free(uint8_t *ptr);

}

#endif // COMMONDATABUFFERMETHODS_H
