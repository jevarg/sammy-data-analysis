#pragma once

#include <stdint.h>

typedef struct FileChunk
{
    uint32_t offset;
    uint16_t encodedSize;
    uint16_t decodedSize;
} FileChunk;

typedef struct FileHeader
{
    uint16_t    numberOfChunks;
    uint8_t     unknownData[8];
    FileChunk *chunks;
} FileHeader;
