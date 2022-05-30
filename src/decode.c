#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "decode.h"

#define PTR_LOBYTE (UINTPTR_MAX >> ((CHAR_BIT * sizeof(void *)) / 2))
#define reverse_bytes_16(num) (((num & 0xFF00) >> 8) | ((num & 0x00FF) << 8))
#define HIBYTE(x) (x >> 8)
#define LOBYTE(x) (x << 8)
#define HI_NIBBLE(b) (((b) >> 4) & 0x0F)
#define LO_NIBBLE(b) ((b)&0x0F)

static int8_t gLookupTable[] = {
        0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff,
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
        0xf0, 0xf2, 0xf4, 0xf6, 0xf8, 0xfa, 0xfc, 0xfe,
        0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e, 0x10,
        0xe8, 0xeb, 0xee, 0xf1, 0xf4, 0xf7, 0xfa, 0xfd,
        0x03, 0x06, 0x09, 0x0c, 0x0f, 0x12, 0x15, 0x18,
        0xe0, 0xe4, 0xe8, 0xec, 0xf0, 0xf4, 0xf8, 0xfc,
        0x04, 0x08, 0x0c, 0x10, 0x14, 0x18, 0x1c, 0x20,
        0xd8, 0xdd, 0xe2, 0xe7, 0xec, 0xf1, 0xf6, 0xfb,
        0x05, 0x0a, 0x0f, 0x14, 0x19, 0x1e, 0x23, 0x28,
        0xd0, 0xd6, 0xdc, 0xe2, 0xe8, 0xee, 0xf4, 0xfa,
        0x06, 0x0c, 0x12, 0x18, 0x1e, 0x24, 0x2a, 0x30,
        0xc8, 0xcf, 0xd6, 0xdd, 0xe4, 0xeb, 0xf2, 0xf9,
        0x07, 0x0e, 0x15, 0x1c, 0x23, 0x2a, 0x31, 0x38,
        0xc0, 0xc8, 0xd0, 0xd8, 0xe0, 0xe8, 0xf0, 0xf8,
        0x08, 0x10, 0x18, 0x20, 0x28, 0x30, 0x38, 0x40,
        0xb8, 0xc1, 0xca, 0xd3, 0xdc, 0xe5, 0xee, 0xf7,
        0x09, 0x12, 0x1b, 0x24, 0x2d, 0x36, 0x3f, 0x48,
        0xb0, 0xba, 0xc4, 0xce, 0xd8, 0xe2, 0xec, 0xf6,
        0x0a, 0x14, 0x1e, 0x28, 0x32, 0x3c, 0x46, 0x50,
        0xa8, 0xb3, 0xbe, 0xc9, 0xd4, 0xdf, 0xea, 0xf5,
        0x0b, 0x16, 0x21, 0x2c, 0x37, 0x42, 0x4d, 0x58,
        0xa0, 0xac, 0xb8, 0xc4, 0xd0, 0xdc, 0xe8, 0xf4,
        0x0c, 0x18, 0x24, 0x30, 0x3c, 0x48, 0x54, 0x60,
        0x98, 0xa5, 0xb2, 0xbf, 0xcc, 0xd9, 0xe6, 0xf3,
        0x0d, 0x1a, 0x27, 0x34, 0x41, 0x4e, 0x5b, 0x68,
        0x90, 0x9e, 0xac, 0xba, 0xc8, 0xd6, 0xe4, 0xf2,
        0x0e, 0x1c, 0x2a, 0x38, 0x46, 0x54, 0x62, 0x70,
        0x88, 0x97, 0xa6, 0xb5, 0xc4, 0xd3, 0xe2, 0xf1,
        0x0f, 0x1e, 0x2d, 0x3c, 0x4b, 0x5a, 0x69, 0x78,
        0x80, 0x90, 0xa0, 0xb0, 0xc0, 0xd0, 0xe0, 0xf0,
        0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x7f
};

void decode(int8_t *buffer, int8_t *destBuffer) {
    int16_t ax = *((uint16_t *) buffer + 3);
    uint16_t outSize = *(int16_t *) buffer; // 27FF == 10239
    uint16_t v56 = (uint8_t) buffer[4];

    int8_t *v4 = (int8_t *) &ax;
    int8_t *hgh = (int8_t *) &ax + 1;
    *v4 = buffer[8];
    int8_t *data = &buffer[9];
    *destBuffer = *v4;
    int8_t *dest = &destBuffer[1];

    uint16_t v7 = (uint8_t) buffer[8];
    uint16_t remainingSize = outSize - 1;
    uint16_t v12 = 0;
    int16_t counter = 0;

    int8_t *ebx = NULL;

    if (remainingSize) {
        *hgh = *v4;
        do {
            while (1) {
                while (1) {
                    *v4 = *data++;
                    if (!(*v4 & 0x80)) {
                        break;
                    }

                    v7 = (uint8_t) (2 * *v4);
                    *dest++ = 2 * *v4;
                    if (!--remainingSize) {
                        return;
                    }
                }

                if (!(*v4 & 0x40)) {
                    break;
                }

                // int16_t v10 = remainingSize;
                int length = *v4 & 0x3F;
                memset(dest, v7, length);
                dest += length;

                // remainingSize = v10 - length;
                if (remainingSize == length) {
                    return;
                }

                remainingSize -= length;
            }

            // ebx = &gLookupTable[(*v4 & 0xF) * 16];
            int test = (*v4 & 0xF) * 16;
            ebx = &gLookupTable[test];
            *v4 &= 0x30u; // is highest byte 16, 32 or 48?
            counter = remainingSize;
            if (*v4 == 16) {
                remainingSize = v56 >> 3; // v56 comes from file data directly.
                v12 = gLookupTable[test + 8];
                do {
                    *v4 = *data++;
                    ax = reverse_bytes_16(ax);
//          int16_t qwe = *v4;
//          *v4 = (uint8_t)v7;
                    for (size_t i = 1; i <= 8; i++) {

                        if ((*hgh <<= 1) < 0) {
                            v7 += v12;
                            if (HIBYTE(v7)) {
                                v7 = 0xFF;
                            }
                        } else {
                            v7 -= v12;
                            if (v7 < 0) {
                                v7 = 0;
                            }
                        }

                        *v4 = v7;
                        *dest++ = (int8_t) v7;
                        printf("ASD\n");
                    }
                    --remainingSize;
                } while (remainingSize);
            } else if (*v4 == 32) {
                int8_t *ptr = ((uintptr_t) ebx & ~PTR_LOBYTE) | (uintptr_t) (ebx + 6);
                // ebx = ((uintptr_t)ebx & ~PTR_LOBYTE) | (uintptr_t)(ebx + 6);
                // int8_t *ptr = ebx;
                remainingSize = v56 >> 2; // TODO: Check what v56 is. it comes from the file directly

                do {
                    uint8_t b = *data++;
                    *v4 = ptr[b >> 6];
                    if (*v4 & 0x80) {
                        *hgh = 0xff;
                    } else {
                        *hgh = 0;
                    }
                    v7 += *v4;
                    if (v7 < 0) {
                        v7 = 0;
                    }
                    if (HIBYTE(v7)) {
                        v7 = 0xFF;
                    }

                    *dest++ = (int8_t) v7;

                    *v4 = ptr[b >> 4 & 3];
                    if (*v4 & 0x80) {
                        *hgh = 0xff;
                    } else {
                        *hgh = 0;
                    }
                    v7 += *v4;
                    if (v7 < 0) {
                        v7 = 0;
                    }
                    if (HIBYTE(v7)) {
                        v7 = 0xFF;
                    }

                    *dest++ = (int8_t) v7;

                    *v4 = ptr[b >> 2 & 3];
                    if (*v4 & 0x80) {
                        *hgh = 0xff;
                    } else {
                        *hgh = 0;
                    }
                    v7 += *v4;
                    if (v7 < 0) {
                        v7 = 0;
                    }
                    if (HIBYTE(v7)) {
                        v7 = 0xFF;
                    }

                    *dest++ = (int8_t) v7;

                    *v4 = ptr[b & 3];
                    if (*v4 & 0x80) {
                        *hgh = 0xff;
                    } else {
                        *hgh = 0;
                    }
                    v7 += *v4;
                    if (v7 < 0) {
                        v7 = 0;
                    }
                    if (HIBYTE(v7)) {
                        v7 = 0xFF;
                    }

                    *dest++ = (int8_t) v7;
                    --remainingSize;
                } while (remainingSize);
            } else {
                remainingSize = (v56 >> 1);
                do {
                    uint8_t b = *data++;

                    *v4 = ebx[b >> 4];
                    if (*v4 & 0x80) {
                        *hgh = 0xff;
                    } else {
                        *hgh = 0;
                    }
                    v7 += *v4;
                    if (v7 < 0) {
                        v7 = 0;
                    }
                    if (HIBYTE(v7)) {
                        v7 = 0xFF;
                    }

                    *dest++ = (int8_t) v7;

                    *v4 = ebx[b & 0xf];
                    if (*v4 & 0x80) {
                        *hgh = 0xff;
                    } else {
                        *hgh = 0;
                    }
                    v7 += *v4;
                    if (v7 < 0) {
                        v7 = 0;
                    }
                    if (HIBYTE(v7)) {
                        v7 = 0xFF;
                    }

                    *dest++ = (int8_t) v7;
                    *hgh = 0;
                    --remainingSize;
                } while (remainingSize);
            }

            remainingSize = counter - v56;
        } while (counter != v56);
    }
}

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s FILE\n", argv[0]);
        return 1;
    }

    const char *fileName = argv[1];
    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        fprintf(stderr, "Invalid file: %s\n", fileName);
        return 1;
    }

    FileHeader header = {0};
    fread(&header, 10, 1, file);
    printf("File is composed of %d chunks\n", header.numberOfChunks);

    header.chunks = malloc(sizeof(FileChunk) * header.numberOfChunks);
    if (header.chunks == NULL) {
        fprintf(stderr, "Could not allocate memory\n");
        fclose(file);
        return 1;
    }

    for (size_t i = 0; i < header.numberOfChunks; i++) {
        fread(&header.chunks[i], sizeof(FileChunk), 1, file);
        // printf("\nChunk #%d/%d\n", i + 1, header.numberOfChunks);
        printf(
                "\nChunk #%d/%d\n"
                "\tOffset: %d\n"
                "\tEncoded size: %d\n"
                "\tDecoded size: %d\n",
                i + 1, header.numberOfChunks,
                header.chunks[i].offset,
                header.chunks[i].encodedSize,
                header.chunks[i].decodedSize
        );
    }

    FILE *f = fopen("./out.SND", "w+");
    if (f == NULL) {
        perror("Error file");
        return 1;
    }

    for (size_t i = 0; i < header.numberOfChunks; i++) {
        uint32_t baseSize = header.chunks[i].encodedSize;
        int8_t buffer[baseSize];
        int8_t destBuffer[header.chunks[i].decodedSize];

        fseek(file, header.chunks[i].offset, SEEK_SET);
        fread(buffer, baseSize, 1, file);
        decode(buffer, destBuffer);

        fwrite(destBuffer, header.chunks[i].decodedSize, 1, f);
    }

    fclose(f);

    free(header.chunks);
    fclose(file);
    return 0;
}
