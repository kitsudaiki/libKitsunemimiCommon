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
                     const uint8_t *data,
                     const uint64_t size);
bool allocateBlocks(CommonDataBuffer *buffer,
                    const uint64_t numberOfBlocks);
void resetBuffer(CommonDataBuffer *buffer);
}

#endif // COMMONDATABUFFERMETHODS_H
