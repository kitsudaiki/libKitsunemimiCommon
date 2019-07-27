/**
 *  @file    commonTest.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef COMMONDATABUFFERMETHODS_H
#define COMMONDATABUFFERMETHODS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

namespace Kitsune
{
struct CommonDataBuffer;


bool addDataToBuffer(CommonDataBuffer *buffer,
                     const void* data,
                     const uint64_t size);
bool allocateBlocks(CommonDataBuffer* buffer,
                    const uint64_t numberOfBlocks);
void resetBuffer(CommonDataBuffer* buffer,
                 const uint64_t numberOfBlocks = 1);

void* alignedMalloc(const uint16_t blockSize,
                    const uint64_t numberOfBytes);
bool alignedFree(void *ptr);

}

#endif // COMMONDATABUFFERMETHODS_H
