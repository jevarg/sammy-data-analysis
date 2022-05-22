
undefined8 __fastcall
FUN_0045ded6(undefined4 param_1,undefined4 param_2,ushort *param_3,byte *param_4)

{
  byte bVar1;
  byte bVar2;
  ushort uVar3;
  byte *pbVar4;
  short sVar5;
  ushort uVar6;
  uint uVar7;
  ushort uVar8;
  byte bVar10;
  byte bVar11;
  short sVar9;
  ushort uVar12;
  int iVar13;
  undefined *puVar14;
  byte *pbVar15;
  byte *pbVar16;
  byte *pbVar17;
  
  uVar3 = *param_3;
  bVar1 = *(byte *)(param_3 + 2);
  bVar2 = *(byte *)(param_3 + 4);
  *param_4 = bVar2;
  uVar8 = (ushort)bVar2;
  sVar5 = uVar3 - 1;
  pbVar16 = (byte *)((int)param_3 + 9);
  pbVar17 = param_4 + 1;
  while (sVar5 != 0) {
    pbVar15 = pbVar16 + 1;
    bVar2 = *pbVar16;
    pbVar16 = pbVar15;
    if ((bVar2 & 0x80) == 0) {
      if ((bVar2 & 0x40) == 0) {
        iVar13 = (bVar2 & 0xf) * 0x10;
        puVar14 = &DAT_0049dae0 + iVar13;
        if ((bVar2 & 0x30) == 0x10) {
          uVar6 = (ushort)(bVar1 >> 3);
          bVar2 = (&DAT_0049dae8)[iVar13];
          do {
            pbVar16 = pbVar15 + 1;
            bVar11 = *pbVar15;
            uVar12 = (ushort)bVar2;
            if ((char)bVar11 < '\0') {
              bVar10 = (byte)((uint)(ushort)(uVar8 + uVar12) >> 8);
              uVar8 = uVar8 + uVar12 & 0xff | (ushort)bVar10 << 8;
              if (bVar10 != 0) {
                uVar8 = 0xff;
              }
            }
            else {
              uVar8 = uVar8 - uVar12;
              if ((short)uVar8 < 0) {
                uVar8 = 0;
              }
            }
            *pbVar17 = (byte)uVar8;
            if ((char)(bVar11 << 1) < '\0') {
              bVar10 = (byte)((uint)(ushort)(uVar8 + uVar12) >> 8);
              uVar8 = uVar8 + uVar12 & 0xff | (ushort)bVar10 << 8;
              if (bVar10 != 0) {
                uVar8 = 0xff;
              }
            }
            else {
              uVar8 = uVar8 - uVar12;
              if ((short)uVar8 < 0) {
                uVar8 = 0;
              }
            }
            pbVar17[1] = (byte)uVar8;
            if ((char)(bVar11 << 2) < '\0') {
              bVar10 = (byte)((uint)(ushort)(uVar8 + uVar12) >> 8);
              uVar8 = uVar8 + uVar12 & 0xff | (ushort)bVar10 << 8;
              if (bVar10 != 0) {
                uVar8 = 0xff;
              }
            }
            else {
              uVar8 = uVar8 - uVar12;
              if ((short)uVar8 < 0) {
                uVar8 = 0;
              }
            }
            pbVar17[2] = (byte)uVar8;
            if ((char)(bVar11 << 3) < '\0') {
              bVar10 = (byte)((uint)(ushort)(uVar8 + uVar12) >> 8);
              uVar8 = uVar8 + uVar12 & 0xff | (ushort)bVar10 << 8;
              if (bVar10 != 0) {
                uVar8 = 0xff;
              }
            }
            else {
              uVar8 = uVar8 - uVar12;
              if ((short)uVar8 < 0) {
                uVar8 = 0;
              }
            }
            pbVar17[3] = (byte)uVar8;
            if ((char)(bVar11 << 4) < '\0') {
              bVar10 = (byte)((uint)(ushort)(uVar8 + uVar12) >> 8);
              uVar8 = uVar8 + uVar12 & 0xff | (ushort)bVar10 << 8;
              if (bVar10 != 0) {
                uVar8 = 0xff;
              }
            }
            else {
              uVar8 = uVar8 - uVar12;
              if ((short)uVar8 < 0) {
                uVar8 = 0;
              }
            }
            pbVar17[4] = (byte)uVar8;
            if ((char)(bVar11 << 5) < '\0') {
              bVar10 = (byte)((uint)(ushort)(uVar8 + uVar12) >> 8);
              uVar8 = uVar8 + uVar12 & 0xff | (ushort)bVar10 << 8;
              if (bVar10 != 0) {
                uVar8 = 0xff;
              }
            }
            else {
              uVar8 = uVar8 - uVar12;
              if ((short)uVar8 < 0) {
                uVar8 = 0;
              }
            }
            pbVar17[5] = (byte)uVar8;
            if ((char)(bVar11 << 6) < '\0') {
              bVar10 = (byte)((uint)(ushort)(uVar8 + uVar12) >> 8);
              uVar8 = uVar8 + uVar12 & 0xff | (ushort)bVar10 << 8;
              if (bVar10 != 0) {
                uVar8 = 0xff;
              }
            }
            else {
              uVar8 = uVar8 - uVar12;
              if ((short)uVar8 < 0) {
                uVar8 = 0;
              }
            }
            pbVar15 = pbVar17 + 7;
            pbVar17[6] = (byte)uVar8;
            if ((char)(bVar11 << 7) < '\0') {
              bVar11 = (byte)((uint)(ushort)(uVar8 + uVar12) >> 8);
              uVar8 = uVar8 + uVar12 & 0xff | (ushort)bVar11 << 8;
              if (bVar11 != 0) {
                uVar8 = 0xff;
              }
            }
            else {
              uVar8 = uVar8 - uVar12;
              if ((short)uVar8 < 0) {
                uVar8 = 0;
              }
            }
            pbVar17 = pbVar17 + 8;
            *pbVar15 = (byte)uVar8;
            uVar6 = uVar6 - 1;
            pbVar15 = pbVar16;
          } while (uVar6 != 0);
        }
        else if ((bVar2 & 0x30) == 0x20) {
          uVar7 = (uint)puVar14 & 0xffff0000 | (uint)(ushort)((short)puVar14 + 6);
          uVar6 = (ushort)(bVar1 >> 2);
          do {
            pbVar16 = pbVar15 + 1;
            sVar9 = uVar8 + (short)*(char *)(uVar7 + (*pbVar15 >> 6));
            if (sVar9 < 0) {
              sVar9 = 0;
            }
            if ((char)((ushort)sVar9 >> 8) != '\0') {
              sVar9 = 0xff;
            }
            *pbVar17 = (byte)sVar9;
            sVar9 = sVar9 + *(char *)(uVar7 + (*pbVar15 >> 4 & 3));
            if (sVar9 < 0) {
              sVar9 = 0;
            }
            if ((char)((ushort)sVar9 >> 8) != '\0') {
              sVar9 = 0xff;
            }
            pbVar17[1] = (byte)sVar9;
            sVar9 = sVar9 + *(char *)(uVar7 + (*pbVar15 >> 2 & 3));
            if (sVar9 < 0) {
              sVar9 = 0;
            }
            if ((char)((ushort)sVar9 >> 8) != '\0') {
              sVar9 = 0xff;
            }
            pbVar4 = pbVar17 + 3;
            pbVar17[2] = (byte)sVar9;
            uVar8 = sVar9 + *(char *)(uVar7 + (*pbVar15 & 3));
            if ((short)uVar8 < 0) {
              uVar8 = 0;
            }
            if ((char)(uVar8 >> 8) != '\0') {
              uVar8 = 0xff;
            }
            pbVar17 = pbVar17 + 4;
            *pbVar4 = (byte)uVar8;
            uVar6 = uVar6 - 1;
            pbVar15 = pbVar16;
          } while (uVar6 != 0);
        }
        else {
          uVar6 = (ushort)(bVar1 >> 1);
          do {
            pbVar16 = pbVar15 + 1;
            sVar9 = uVar8 + (short)(char)puVar14[*pbVar15 >> 4];
            if (sVar9 < 0) {
              sVar9 = 0;
            }
            if ((char)((ushort)sVar9 >> 8) != '\0') {
              sVar9 = 0xff;
            }
            pbVar4 = pbVar17 + 1;
            *pbVar17 = (byte)sVar9;
            uVar8 = sVar9 + (char)puVar14[*pbVar15 & 0xf];
            if ((short)uVar8 < 0) {
              uVar8 = 0;
            }
            if ((char)(uVar8 >> 8) != '\0') {
              uVar8 = 0xff;
            }
            pbVar17 = pbVar17 + 2;
            *pbVar4 = (byte)uVar8;
            uVar6 = uVar6 - 1;
            pbVar15 = pbVar16;
          } while (uVar6 != 0);
        }
        sVar5 = sVar5 - (ushort)bVar1;
      }
      else {
        uVar7 = bVar2 & 0x3f;
        sVar9 = (short)uVar7;
        for (; uVar7 != 0; uVar7 = uVar7 - 1) {
          *pbVar17 = (byte)uVar8;
          pbVar17 = pbVar17 + 1;
        }
        sVar5 = sVar5 - sVar9;
      }
    }
    else {
      uVar8 = (ushort)(byte)(bVar2 << 1);
      *pbVar17 = bVar2 << 1;
      sVar5 = sVar5 + -1;
      pbVar17 = pbVar17 + 1;
    }
  }
  return CONCAT44(param_2,(uint)uVar3);
}

