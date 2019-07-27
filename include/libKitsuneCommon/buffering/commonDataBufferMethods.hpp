/**
 *  @file    commonTest.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef COMMONDATABUFFERMETHODS_HPP
#define COMMONDATABUFFERMETHODS_HPP

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

namespace Kitsune
{
struct CommonDataBuffer;


bool addDataToBuffer(CommonDataBuffer *buffer,
                     const void* data,
                     const uint64_t dataSize);
bool allocateBlocks(CommonDataBuffer* buffer,
                    const uint64_t numberOfBlocks);
bool resetBuffer(CommonDataBuffer* buffer,
                 const uint64_t numberOfBlocks = 1);

void* alignedMalloc(const uint16_t blockSize,
                    const uint64_t numberOfBytes);
bool alignedFree(void *ptr);

} // namespace Kitsune

#endif // COMMONDATABUFFERMETHODS_HPP
