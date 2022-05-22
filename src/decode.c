#include <stdint.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t byte;

static const uint8_t DAT_00480db8[] = {
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

const uint8_t DAT_00480db0[] = { 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff };

void decode(uint16_t *buffer, byte *destBuffer)
{
  byte *pbVar1;
  short sVar2;
  uint16_t uVar3;
  uint32_t uVar4;
  short uVar5;
  byte bVar7;
  byte bVar8;
  short sVar6;
  uint16_t uVar9;
  int iVar10;
  const uint8_t *puVar11;
  byte *pbVar12;
  byte *pbVar13;
  byte *pbVar14;
  uint16_t TwoFirstBytes;
  byte bVar9;
  byte bVar10;

  TwoFirstBytes = buffer[0]; // TwoFirstBytes = *buffer;
  bVar9 = buffer[2]; // bVar9 = *(byte *)(buffer + 2);
  bVar10 = buffer[4]; // bVar10 = *(byte *)(buffer + 4);
  destBuffer[0] = bVar10; // *destBuffer = bVar10;
  uVar5 = (uint16_t)bVar10;
  sVar2 = TwoFirstBytes - 1;
  pbVar13 = (byte *)(buffer + 9);
  pbVar14 = destBuffer + 1;
  while (sVar2 != 0) {
    pbVar12 = pbVar13 + 1;
    bVar10 = *pbVar13;
    pbVar13 = pbVar12;
    if ((bVar10 & 0x80) == 0) {
      if ((bVar10 & 0x40) == 0) {
        iVar10 = (bVar10 & 0xf) * 0x10;
        puVar11 = &DAT_00480db0[iVar10];
        if ((bVar10 & 0x30) == 0x10) {
          uVar3 = (uint16_t)(bVar9 >> 3);
          bVar10 = DAT_00480db8[iVar10];
          do {
            pbVar13 = pbVar12 + 1;
            bVar8 = *pbVar12;
            uVar9 = (uint16_t)bVar10;
            if (bVar8 < 0) {
              bVar7 = (byte)((uint32_t)(uint16_t)(uVar5 + uVar9) >> 8);
              uVar5 = uVar5 + uVar9 & 0xff | (uint16_t)bVar7 << 8;
              if (bVar7 != 0) {
                uVar5 = 0xff;
              }
            }
            else {
              uVar5 -= uVar9;
              if (uVar5 < 0) {
                uVar5 = 0;
              }
            }
            *pbVar14 = (byte)uVar5;
            if ((bVar8 << 1) < 0) {
              bVar7 = (byte)((uint32_t)(uint16_t)(uVar5 + uVar9) >> 8);
              uVar5 = uVar5 + uVar9 & 0xff | (uint16_t)bVar7 << 8;
              if (bVar7 != 0) {
                uVar5 = 0xff;
              }
            }
            else {
              uVar5 -= uVar9;
              if (uVar5 < 0) {
                uVar5 = 0;
              }
            }
            pbVar14[1] = (byte)uVar5;
            if ((bVar8 << 2) < 0) {
              bVar7 = (byte)((uint32_t)(uint16_t)(uVar5 + uVar9) >> 8);
              uVar5 = uVar5 + uVar9 & 0xff | (uint16_t)bVar7 << 8;
              if (bVar7 != 0) {
                uVar5 = 0xff;
              }
            }
            else {
              uVar5 -= uVar9;
              if (uVar5 < 0) {
                uVar5 = 0;
              }
            }
            pbVar14[2] = (byte)uVar5;
            if ((bVar8 << 3) < 0) {
              bVar7 = (byte)((uint32_t)(uint16_t)(uVar5 + uVar9) >> 8);
              uVar5 = uVar5 + uVar9 & 0xff | (uint16_t)bVar7 << 8;
              if (bVar7 != 0) {
                uVar5 = 0xff;
              }
            }
            else {
              uVar5 -= uVar9;
              if (uVar5 < 0) {
                uVar5 = 0;
              }
            }
            pbVar14[3] = (byte)uVar5;
            if ((bVar8 << 4) < 0) {
              bVar7 = (byte)((uint32_t)(uint16_t)(uVar5 + uVar9) >> 8);
              uVar5 = uVar5 + uVar9 & 0xff | (uint16_t)bVar7 << 8;
              if (bVar7 != 0) {
                uVar5 = 0xff;
              }
            }
            else {
              uVar5 -= uVar9;
              if (uVar5 < 0) {
                uVar5 = 0;
              }
            }
            pbVar14[4] = (byte)uVar5;
            if ((bVar8 << 5) < 0) {
              bVar7 = (byte)((uint32_t)(uint16_t)(uVar5 + uVar9) >> 8);
              uVar5 = uVar5 + uVar9 & 0xff | (uint16_t)bVar7 << 8;
              if (bVar7 != 0) {
                uVar5 = 0xff;
              }
            }
            else {
              uVar5 -= uVar9;
              if (uVar5 < 0) {
                uVar5 = 0;
              }
            }
            pbVar14[5] = (byte)uVar5;
            if ((bVar8 << 6) < 0) {
              bVar7 = (byte)((uint32_t)(uint16_t)(uVar5 + uVar9) >> 8);
              uVar5 = uVar5 + uVar9 & 0xff | (uint16_t)bVar7 << 8;
              if (bVar7 != 0) {
                uVar5 = 0xff;
              }
            }
            else {
              uVar5 -= uVar9;
              if (uVar5 < 0) {
                uVar5 = 0;
              }
            }
            pbVar12 = pbVar14 + 7;
            pbVar14[6] = (byte)uVar5;
            if ((bVar8 << 7) < 0) {
              bVar8 = (byte)((uint32_t)(uint16_t)(uVar5 + uVar9) >> 8);
              uVar5 = uVar5 + uVar9 & 0xff | (uint16_t)bVar8 << 8;
              if (bVar8 != 0) {
                uVar5 = 0xff;
              }
            }
            else {
              uVar5 -= uVar9;
              if (uVar5 < 0) {
                uVar5 = 0;
              }
            }
                    // [CatchableType,12]{class exception `RTTI Type Descriptor'}{public: __thiscall
                    // exception::exception(class exception const &)}
            pbVar14 = pbVar14 + 8;
            *pbVar12 = (byte)uVar5;
            uVar3 -= 1;
            pbVar12 = pbVar13;
          } while (uVar3 != 0);
        }
        else if ((bVar10 & 0x30) == 0x20) {
          uVar4 = (uint32_t)(*puVar11 & 0xffff0000) | (uint32_t)(puVar11 + 6);
                    // [CatchableType,12]{class __non_rtti_object `RTTI Type Descriptor'}{public:
                    // __thiscall __non_rtti_object::__non_rtti_object(class __non_rtti_object const
                    // &)}
          uVar3 = (uint16_t)(bVar9 >> 2);
          do {
            pbVar13 = pbVar12 + 1;
            sVar6 = uVar5 + (short)*(char *)(uVar4 + (*pbVar12 >> 6));
            if (sVar6 < 0) {
              sVar6 = 0;
            }
            if ((char)((uint16_t)sVar6 >> 8) != 0) {
              sVar6 = 0xff;
            }
            *pbVar14 = (byte)sVar6;
                    // [CatchableType,12]{class bad_typeid `RTTI Type Descriptor'}{public:
                    // __thiscall bad_typeid::bad_typeid(class bad_typeid const &)}
            sVar6 += *(char *)(uVar4 + (*pbVar12 >> 4 & 3));
            if (sVar6 < 0) {
              sVar6 = 0;
            }
            if ((char)((uint16_t)sVar6 >> 8) != 0) {
              sVar6 = 0xff;
            }
            pbVar14[1] = (byte)sVar6;
                    // [CatchableTypeArray,2]{class bad_typeid}
            sVar6 += *(char *)(uVar4 + (*pbVar12 >> 2 & 3));
            if (sVar6 < 0) {
              sVar6 = 0;
            }
                    // [ThrowInfo,3]{class __non_rtti_object}
            if ((char)((uint16_t)sVar6 >> 8) != 0) {
              sVar6 = 0xff;
            }
            pbVar1 = pbVar14 + 3;
            pbVar14[2] = (byte)sVar6;
                    // [ThrowInfo,2]{class bad_typeid}
            uVar5 = sVar6 + *(char *)(uVar4 + (*pbVar12 & 3));
            if (uVar5 < 0) {
              uVar5 = 0;
            }
            if ((char)(uVar5 >> 8) != 0) {
              uVar5 = 0xff;
            }
            pbVar14 = pbVar14 + 4;
            *pbVar1 = (byte)uVar5;
            uVar3 -= 1;
            pbVar12 = pbVar13;
          } while (uVar3 != 0);
        }
        else {
          uVar3 = (uint16_t)(bVar9 >> 1);
          do {
            pbVar13 = pbVar12 + 1;
            sVar6 = uVar5 + (short)(char)puVar11[*pbVar12 >> 4];
            if (sVar6 < 0) {
              sVar6 = 0;
            }
                    // [CatchableTypeArray,2]{class bad_cast}
            if ((char)((uint16_t)sVar6 >> 8) != 0) {
              sVar6 = 0xff;
            }
            pbVar1 = pbVar14 + 1;
            *pbVar14 = (byte)sVar6;
                    // [ThrowInfo,2]{class bad_cast}
            uVar5 = sVar6 + (char)puVar11[*pbVar12 & 0xf];
            if (uVar5 < 0) {
              uVar5 = 0;
            }
            if ((char)(uVar5 >> 8) != 0) {
              uVar5 = 0xff;
            }
            pbVar14 = pbVar14 + 2;
            *pbVar1 = (byte)uVar5;
            uVar3 -= 1;
            pbVar12 = pbVar13;
          } while (uVar3 != 0);
        }
        sVar2 -= (uint16_t)bVar9;
      }
      else {
        uVar4 = bVar10 & 0x3f;
        sVar6 = (short)uVar4;
        for (; uVar4 != 0; uVar4 -= 1) {
          *pbVar14 = (byte)uVar5;
          pbVar14 = pbVar14 + 1;
        }
        sVar2 -= sVar6;
      }
    }
    else {
      uVar5 = (uint16_t)(byte)(bVar10 << 1);
      *pbVar14 = bVar10 << 1;
      sVar2 += -1;
      pbVar14 = pbVar14 + 1;
    }
  }

  // return CONCAT44(param_2,(uint32_t)TwoFirstBytes);
}

int main(int argc, char const *argv[])
{
  // if (argc < 2) {
  //   fprintf(stderr, "Usage: %s FILE\n", argv[0]);
  //   return 1;
  // }

  // const char *fileName = argv[2];
  const char *fileName = "../out/10.SND";
  FILE *file = fopen(fileName, "rb");
  if (file == NULL) {
    fprintf(stderr, "Invalid file: %s\n", fileName);
    return 1;
  }

  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  fseek(file, 13, SEEK_SET);

  uint8_t *data = calloc(1, size + 1);
  uint16_t *buffer = calloc(1, 16);

  while (fread(buffer, 16, 1, file)) {
    decode(buffer, data);
  }

  free(buffer);
  free(data);
  fclose(file);
  return 0;
}
