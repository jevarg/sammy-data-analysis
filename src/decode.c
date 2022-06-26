#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "audio_decoder.h"

#define PTR_LOBYTE (UINTPTR_MAX >> ((CHAR_BIT * sizeof(void *)) / 2))
#define reverse_bytes_16(num) (((num & 0xFF00) >> 8) | ((num & 0x00FF) << 8))
#define HIBYTE(x) (x >> 8)
#define LOBYTE(x) (x << 8)
#define HI_NIBBLE(b) (((b) >> 4) & 0x0F)
#define LO_NIBBLE(b) ((b) & 0x0F)

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
//    int16_t ax = *((uint16_t *) buffer + 3);
    uint16_t outSize = *(int16_t *) buffer; // 27FF == 10239
    uint16_t v56 = (uint8_t) buffer[4];

//    int8_t v4 = (int8_t *) &ax;
//    int8_t *hgh = (int8_t *) &ax + 1;
    int8_t v4 = buffer[8];
    int8_t *data = &buffer[9];
    *destBuffer = v4;
    int8_t *dest = &destBuffer[1];

    uint16_t v7 = (uint8_t) buffer[8];
    uint16_t remainingSize = outSize - 1;
    int16_t counter = 0;

    int8_t *ebx = NULL;

    if (remainingSize) {
//        *hgh = v4;
        do {
            while (1) {
                while (1) {
                    v4 = *data++;
                    if (!(v4 & 0x80)) { // Checking if negative bit is set (0x80 == 0b10000000)
                        break;
                    }

                    // We left shift byte by 1 (* 2 is same as << 1)
                    // Note that we cast to 1 byte size.
                    // Seems like we try to get rid of 1st byte
                    // in order to keep result it 1 byte long
                    v7 = (uint8_t) (v4 * 2);
                    *dest++ = (uint8_t) (v4 * 2);
                    if (!--remainingSize) {
                        return;
                    }
                }

                // Checking if second bit is set (0x40 == 0b01000000)
                if (!(v4 & 0x40)) {
                    break;
                }

                // We keep the last 6 bits. (0x3F == 0b00111111)
                // And store it as length
                int length = v4 & 0x3F;

                // We write {length} times the current value
                memset(dest, v7, length);
                dest += length; // Our dest pointer is moved

                // Have we decoded all bytes?
                if (remainingSize == length) {
                    return;
                }

                // We subtract the number of bytes decoded.
                remainingSize -= length;
            }

            // ebx = &gLookupTable[(v4 & 0xF) * 16];
            /**
             * We keep the low nibble (lower-half of byte)
             * of the current value and shift it to the left by 4.
             * e.g:
             *     0x3d (0b00111101)
             *   & 0x0f (0b00001111)
             *   = 0x0d (0b00001101)
             * <<4 0xd0 (0b11010000)
             */
            int test = (v4 & 0xF) << 4;
            ebx = &gLookupTable[test];

            /**
             * We check the 2 last bits of the high nibble
             * of the current value.
             * see if conditions a bit later...
             */
            v4 &= 0x30u; // is highest byte 16, 32 or 48?
            counter = remainingSize;

            /**
             * Is the current flag == 16
             * means that 2 last bits
             * of high nibble were == 01
             * ex: 0x18 (0b00[01]1000)
             *
             * For each byte, we check from
             * left to right if which bits are set.
             * 
             * If a bit is set, we add the lookup
             * table data to the result.
             * If not, we subtract it from the result.
             */
            if (v4 == 0x10) {
                // printf("0x10\n");
                remainingSize = v56 >> 3; // v56 comes from file data directly.
                uint16_t v12 = (uint16_t)gLookupTable[8];
                do {
                    v4 = *data++;
                    for (size_t i = 0; i < 8; i++) {
                        /**
                         * For each iteration, we shift left using i
                         * before checking if the MSB is set.
                         * This is how we test if each bit is set.
                         * Example with v4 == 0x18 (00011000)
                         *  i == 0: 00011000 (24)
                         *  i == 1: 00110000 (48)
                         *  i == 2: 01100000 (96)
                         *  i == 3: 11000000 (-64)
                         *  i == 4: 10000000 (-128)
                         *  i == 5: 00000000 (0)
                         *  i == 6: 00000000 (0)
                         */
                        if ((v4 << i) < 0) {
                            v7 += v12;
                            if (HIBYTE(v7)) {
                                v7 = 0xFF;
                            }
                        }
                        else {
                            v7 -= v12;
                            if (v7 < 0) {
                                v7 = 0;
                            }
                        }

                        *dest++ = (int8_t)v7;
                    }
                    --remainingSize;
                } while (remainingSize);
            }
                /**
                 * Is the current flag == 32
                 * means that 2 last bits
                 * of high nibble were == 10
                 * ex: 0x28 (0b00[10]1000)
                 *
                 * For each byte, we get each half-nibble (2 bits)
                 * in order to calculate its result
                 */
            else if (v4 == 32) {
                // printf("32\n");
                int8_t *ptr = &ebx[6];
                // int8_t *ptr = ((uintptr_t) ebx & ~PTR_LOBYTE) | (uintptr_t) (ebx + 6);
                // ebx = ((uintptr_t)ebx & ~PTR_LOBYTE) | (uintptr_t)(ebx + 6);
                // int8_t *ptr = ebx;
                remainingSize = v56 >> 2;

                do {
                    uint8_t b = *data++;

                    /**
                     * we look for an association of
                     * the MSB of current
                     * value's high nibble in lookup table.
                     * Right shifting by 6 allows to
                     * get those bits.
                     *
                     * e.g with b = 0x90:
                     *      0x90 (0b[10]010000)
                     *  >>6 0x02 (0b000000[10])
                     */
                    v4 = ptr[b >> 6];
                    v7 += v4;
                    if (v7 < 0) {
                        v7 = 0;
                    }
                    if (HIBYTE(v7)) {
                        v7 = 0xFF;
                    }

                    /**
                     * We add the byte-clamped result
                     * in the result buffer
                     */
                    *dest++ = (int8_t) v7;

                    /**
                     * we look for an association of
                     * the LSB of current
                     * value's high nibble in lookup table.
                     *
                     * e.g with b = 0x90:
                     *      0x90 (0b10[01]0000)
                     *  >>4 0x09 (0b0000[1001])
                     *  & 3 0x01 (0b000000[01])
                     */
                    v4 = ptr[b >> 4 & 3];
                    v7 += v4;
                    if (v7 < 0) {
                        v7 = 0;
                    }
                    if (HIBYTE(v7)) {
                        v7 = 0xFF;
                    }

                    /**
                     * We add the byte-clamped result
                     * in the result buffer
                     */
                    *dest++ = (int8_t) v7;

                    /**
                    * we look for an association of
                    * the MSB of current
                    * value's low nibble in lookup table.
                    *
                    * e.g with b = 0x90:
                    *      0x84 (0b1000[01]00)
                    *  >>2 0x21 (0b001000[01])
                    *  & 3 0x01 (0b000000[01])
                    */
                    v4 = ptr[b >> 2 & 3];
                    v7 += v4;
                    if (v7 < 0) {
                        v7 = 0;
                    }
                    if (HIBYTE(v7)) {
                        v7 = 0xFF;
                    }

                    /**
                     * We add the byte-clamped result
                     * in the result buffer
                     */
                    *dest++ = (int8_t) v7;

                    /**
                    * we look for an association of
                    * the LSB of current
                    * value's low nibble in lookup table.
                    *
                    * e.g with b = 0x42:
                    *      0x42 (0b010000[10])
                    *  & 3 0x02 (0b000000[10])
                    */
                    v4 = ptr[b & 3];
                    v7 += v4;
                    if (v7 < 0) {
                        v7 = 0;
                    }
                    if (HIBYTE(v7)) {
                        v7 = 0xFF;
                    }

                    /**
                     * We add the byte-clamped result
                     * in the result buffer
                     */
                    *dest++ = (int8_t) v7;
                    --remainingSize;
                } while (remainingSize);
            }
                /**
                * Is the current flag not 16 or 32
                * means that 2 LSB
                * of high nibble were == 00
                * ex: 0x08 (0b00[00]1000)
                *
                * For each byte, we get each nibble (4 bits)
                * in order to calculate its result
                */
            else {
                // printf("other\n");
                // v56 is divided by 2 (>> 1)
                remainingSize = (v56 >> 1);
                do {
                    uint8_t b = *data++;

                    /**
                     * we look for an association of
                     * the high nibble of current
                     * value in lookup table.
                     */
                    v4 = ebx[b >> 4];
//                    if (v4 & 0x80) {
//                        *hgh = 0xff;
//                    } else {
//                        *hgh = 0;
//                    }
                    v7 += v4;
                    if (v7 < 0) {
                        v7 = 0;
                    }
                    if (HIBYTE(v7)) {
                        v7 = 0xFF;
                    }

                    /**
                     * We add the byte-clamped result
                     * in the result buffer
                     */
                    *dest++ = (int8_t) v7;

                    /**
                     * we look for an association of
                     * the low nibble of current
                     * value in lookup table.
                     */
                    v4 = ebx[b & 0xf];
//                    if (v4 & 0x80) {
//                        *hgh = 0xff;
//                    } else {
//                        *hgh = 0;
//                    }
                    v7 += v4;
                    if (v7 < 0) {
                        v7 = 0;
                    }
                    if (HIBYTE(v7)) {
                        v7 = 0xFF;
                    }

                    /**
                     * We add the byte-clamped result
                     * in the result buffer
                     */
                    *dest++ = (int8_t) v7;
                    --remainingSize;
                } while (remainingSize);
            }

            remainingSize = counter - v56;
        } while (counter != v56);
    }
}

int main(int argc, char const *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s IN_FILE OUT_FILE\n", argv[0]);
        return 1;
    }

    const char *fileName = argv[1];
    const char *outFile = argv[2];
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
        // printf(
        //         "\nChunk #%d/%d\n"
        //         "\tOffset: %d\n"
        //         "\tEncoded size: %d\n"
        //         "\tDecoded size: %d\n",
        //         i + 1, header.numberOfChunks,
        //         header.chunks[i].offset,
        //         header.chunks[i].encodedSize,
        //         header.chunks[i].decodedSize
        // );
    }

    FILE *f = fopen(outFile, "w+");
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
