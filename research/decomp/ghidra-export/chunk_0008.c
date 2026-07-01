// ==== 800617e4  FUN_800617e4 ====

void FUN_800617e4(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    *(undefined1 *)(param_1 + 0x545) = 0x1e;
    if (*(char *)(param_1 + 0x661) == '\x02') {
      *(undefined4 *)(param_1 + 0x754) = 0;
    }
    else {
      *(code **)(param_1 + 0x754) = FUN_80065e64;
    }
    *(undefined2 *)(param_1 + 0x7e) = 0;
    fVar1 = FLOAT_80437558;
    *(undefined2 *)(param_1 + 0x5ac) = 0;
    dVar3 = (double)FLOAT_804374e8;
    *(undefined2 *)(param_1 + 0x5aa) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(undefined1 *)(param_1 + 0x588) = 1;
    *(float *)(param_1 + 0x69c) = fVar1;
    zz_004beb8_(dVar3,param_1,2,0,0xc,0xffffffff,0xffffffff);
  }
  else {
    zz_004cd24_(param_1,2);
  }
  if (*(float *)(param_1 + 0x698) <= FLOAT_804374ec) {
    iVar2 = zz_0066ac0_(param_1,0);
    if (iVar2 != 0) {
      FUN_800676d8((double)*(float *)(*(int *)(param_1 + 0x4ac) + 0x54),param_1,
                   *(short *)(param_1 + 0x5ac));
    }
  }
  dVar3 = (double)FLOAT_80437510;
  *(float *)(param_1 + 0x44) =
       *(float *)(param_1 + 0x44) *
       (FLOAT_80437528 * (float)(dVar3 - (double)*(float *)(param_1 + 0x1dc8)) + FLOAT_80437524);
  if (*(char *)(param_1 + 0x1d0f) == '\0') {
    *(code **)(param_1 + 0x754) = FUN_80065e64;
    zz_0067458_(dVar3,param_1,*(short *)(param_1 + 0x5ae));
  }
  else {
    *(float *)(param_1 + 0x44) =
         *(float *)(param_1 + 0x44) *
         (FLOAT_8043756c * (float)(dVar3 - (double)*(float *)(param_1 + 0x1dc8)) + FLOAT_80437568);
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1d0e) != '\0') {
    *(undefined1 *)(param_1 + 0x590) = 1;
    zz_006a750_(param_1,6);
  }
  return;
}



// ==== 8006197c  FUN_8006197c ====

void FUN_8006197c(int param_1)

{
  double dVar1;
  double dVar2;
  short sVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    if (*(char *)(*(int *)(param_1 + 0x4ac) + 0x41) != '\0') {
      *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) | 5;
    }
    *(undefined1 *)(param_1 + 0x87) = 1;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x50;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffdfff;
    zz_0066ac0_(param_1,0);
    iVar5 = zz_0046510_(*(ushort *)(param_1 + 0x5aa),1);
    iVar6 = zz_0046510_(*(ushort *)(param_1 + 0x5aa),2);
    *(short *)(param_1 + 0x550) = (short)iVar6;
    fVar4 = FLOAT_804374ec;
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + iVar5 * 4 + 0x18);
    *(float *)(param_1 + 0x4c) = fVar4;
    *(float *)(param_1 + 0x48) = fVar4;
    *(float *)(param_1 + 0x50) = fVar4;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
    uVar8 = (uint)*(short *)(param_1 + 0x5aa);
    if (*(short *)(param_1 + 0x5aa) < 0) {
      if ((int)uVar8 < -0x4000) {
        fVar4 = (float)((double)CONCAT44(0x43300000,uVar8 + 0x8000 ^ 0x80000000) - DOUBLE_804374f8)
                / FLOAT_80437574;
      }
      else {
        fVar4 = (float)((double)CONCAT44(0x43300000,-uVar8 ^ 0x80000000) - DOUBLE_804374f8) /
                FLOAT_80437574;
      }
    }
    else if ((int)uVar8 < 0x4001) {
      fVar4 = (float)((double)CONCAT44(0x43300000,uVar8 ^ 0x80000000) - DOUBLE_804374f8) /
              FLOAT_80437574;
    }
    else {
      fVar4 = (float)((double)CONCAT44(0x43300000,0x8000 - uVar8 ^ 0x80000000) - DOUBLE_804374f8) /
              FLOAT_80437574;
    }
    uVar7 = (uint)*(ushort *)(*(int *)(param_1 + 0x4b0) + 0xc0);
    dVar1 = (double)CONCAT44(0x43300000,uVar7) - DOUBLE_80437500;
    dVar2 = (double)CONCAT44(0x43300000,
                             *(ushort *)(*(int *)(param_1 + 0x4b0) + 0xc4) - uVar7 ^ 0x80000000) -
            DOUBLE_804374f8;
    if (((int)uVar8 < 0x6000) && (-0x6000 < (int)uVar8)) {
      *(undefined1 *)(param_1 + 0x57c) = 0;
    }
    else {
      *(undefined1 *)(param_1 + 0x57c) = 1;
      *(short *)(param_1 + 0x5aa) = *(short *)(param_1 + 0x5aa) + -0x8000;
    }
    zz_0066ec0_(param_1,(int)(fVar4 * (float)dVar2 + (float)dVar1));
    if (*(char *)(*(int *)(param_1 + 0x4ac) + 0x41) != '\0') {
      sVar3 = *(short *)(param_1 + 0x550);
      if (sVar3 == 2) {
        *(undefined1 *)(param_1 + 0x709) = 2;
      }
      else if (sVar3 < 2) {
        if (sVar3 == 0) {
          *(undefined1 *)(param_1 + 0x709) = 1;
        }
        else if (-1 < sVar3) {
          *(undefined1 *)(param_1 + 0x709) = 8;
        }
      }
      else if (sVar3 < 4) {
        *(undefined1 *)(param_1 + 0x709) = 0x10;
      }
    }
  }
  else {
    zz_0067458_((double)FLOAT_804374ec,param_1,*(short *)(param_1 + 0x5ae));
    iVar5 = zz_0066f1c_(param_1);
    if (iVar5 != 0) {
      zz_006a750_(param_1,2);
    }
  }
  return;
}



// ==== 80061c44  FUN_80061c44 ====

void FUN_80061c44(int param_1)

{
  short sVar1;
  float fVar2;
  float fVar3;
  
  fVar2 = FLOAT_804374ec;
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    fVar3 = FLOAT_80437578;
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x2c);
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x568) = fVar3;
    if (*(char *)(param_1 + 0x57c) == '\0') {
      *(undefined1 *)(param_1 + 0x709) = 1;
    }
    else {
      *(undefined1 *)(param_1 + 0x709) = 2;
    }
    sVar1 = *(short *)(param_1 + 0x550);
    if (sVar1 != 2) {
      if (sVar1 < 2) {
        if (0 < sVar1) {
          *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) | 0x10;
        }
      }
      else if (sVar1 < 4) {
        *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) | 8;
      }
    }
  }
  else if (*(float *)(param_1 + 0x568) <= FLOAT_804374ec) {
    if (*(short *)(param_1 + 0x5aa) < 0x2001) {
      if (*(short *)(param_1 + 0x5aa) < -0x2000) {
        *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) & 0xf7;
        *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) | 0x10;
      }
      else {
        *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) & 0xe7;
      }
    }
    else {
      *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) & 0xef;
      *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) | 8;
    }
  }
  else {
    *(float *)(param_1 + 0x568) = *(float *)(param_1 + 0x568) - *(float *)(param_1 + 0x1dc8);
    if (*(float *)(param_1 + 0x568) <= fVar2) {
      *(float *)(param_1 + 0x568) = fVar2;
      *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) & 0xe7;
    }
  }
  zz_0066ac0_(param_1,0);
  if (*(char *)(param_1 + 0x57c) != '\0') {
    *(short *)(param_1 + 0x5aa) = *(short *)(param_1 + 0x5aa) + -0x8000;
  }
  zz_0066e40_(param_1,1);
  if (*(char *)(param_1 + 0x57c) == '\0') {
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  }
  else {
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x72) + -0x8000;
  }
  zz_0067458_((double)FLOAT_804374ec,param_1,*(short *)(param_1 + 0x5ae));
  return;
}



// ==== 80061e08  FUN_80061e08 ====

void FUN_80061e08(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    fVar1 = FLOAT_804374ec;
    *(undefined1 *)(param_1 + 0x87) = 1;
    fVar2 = FLOAT_80437510;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x50;
    *(float *)(param_1 + 0x4c) = fVar1;
    if (fVar2 <= *(float *)(param_1 + 0x44)) {
      if (*(char *)(param_1 + 0x57c) == '\0') {
        *(undefined1 *)(param_1 + 0x709) = 2;
      }
      else {
        *(undefined1 *)(param_1 + 0x709) = 1;
      }
    }
  }
  else if (*(float *)(param_1 + 0x44) < FLOAT_80437510) {
    *(undefined1 *)(param_1 + 0x709) = 0;
    zz_006a474_(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
  }
  dVar3 = (double)FLOAT_804374ec;
  *(float *)(param_1 + 0x44) =
       *(float *)(param_1 + 0x44) *
       (FLOAT_80437580 * (FLOAT_80437510 - *(float *)(param_1 + 0x1dc8)) + FLOAT_8043757c);
  zz_0067458_(dVar3,param_1,*(short *)(param_1 + 0x5ae));
  return;
}



// ==== 80061ef0  FUN_80061ef0 ====

void FUN_80061ef0(int param_1)

{
  double dVar1;
  
  if (*(char *)(param_1 + 0x540) == '\0') {
    dVar1 = (double)FLOAT_804374e8;
    *(undefined1 *)(param_1 + 0x540) = 1;
    zz_004beb8_(dVar1,param_1,0xd,0,*(char *)(param_1 + 0x5e7) + 4,0xffffffff,0xffffffff);
  }
  else {
    zz_004cd24_(param_1,0xd);
  }
  return;
}



// ==== 80061f50  FUN_80061f50 ====

void FUN_80061f50(int param_1)

{
  char cVar1;
  float fVar2;
  undefined4 uVar3;
  short sVar4;
  int iVar5;
  double dVar6;
  
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x01') {
    zz_00664a0_(param_1,1);
    zz_004cd24_(param_1,2);
    iVar5 = zz_0066f1c_(param_1);
    if (iVar5 != 0) {
      *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
    }
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      *(char *)(param_1 + 0x544) = cVar1 + '\x01';
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffffcf;
      uVar3 = zz_0066ac0_(param_1,0);
      *(short *)(param_1 + 0x550) = (short)uVar3;
      *(undefined1 *)(param_1 + 0x590) = 0;
      *(undefined1 *)(param_1 + 0x87) = 1;
      zz_00664a0_(param_1,0);
      *(undefined1 *)(param_1 + 0x5e7) = 0;
      *(float *)(param_1 + 0x690) =
           (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(*(int *)(param_1 + 0x4ac) + 0x3e)) -
                  DOUBLE_80437500);
      if ((*(short *)(param_1 + 0x550) != 0) &&
         (fVar2 = *(float *)(*(int *)(param_1 + 0x4ac) + 0x50), *(float *)(param_1 + 0x44) < fVar2))
      {
        *(float *)(param_1 + 0x44) = fVar2;
      }
      *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x48);
      *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
      fVar2 = FLOAT_80437520;
      if ((*(uint *)(param_1 + 0x5e0) & 0x2000) == 0) {
        *(float *)(param_1 + 0x568) = FLOAT_804374ec;
        *(undefined1 *)(param_1 + 0x588) = 1;
      }
      else {
        *(ushort *)(param_1 + 0x550) = (ushort)*(byte *)(*(int *)(param_1 + 0x4ac) + 0x3d);
        *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * fVar2;
        *(float *)(param_1 + 0x50) = *(float *)(param_1 + 0x50) * fVar2;
        zz_00b2190_(param_1,2);
        *(float *)(param_1 + 0x568) = FLOAT_80437540;
      }
      iVar5 = zz_0046510_(*(ushort *)(param_1 + 0x5aa),1);
      zz_0066ec0_(param_1,(uint)*(ushort *)(*(int *)(param_1 + 0x4b0) + iVar5 * 2 + 0xc0));
      zz_004beb8_((double)FLOAT_804374e8,param_1,2,0,*(char *)(param_1 + 0x5e7) + 4,0xffffffff,
                  0xffffffff);
      if (*(char *)(*(int *)(param_1 + 0x4ac) + 0x41) == '\0') {
        zz_00f036c_(param_1,0x1e);
      }
      else {
        *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) | 1;
      }
    }
  }
  else if (cVar1 < '\x03') {
    uVar3 = zz_0066ac0_(param_1,0);
    *(short *)(param_1 + 0x550) = (short)uVar3;
    zz_00664a0_(param_1,1);
    zz_0066e40_(param_1,1);
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    zz_004cd24_(param_1,2);
  }
  fVar2 = FLOAT_804374ec;
  if ((*(char *)(param_1 + 0x588) != '\x01') &&
     (*(float *)(param_1 + 0x568) = *(float *)(param_1 + 0x568) - *(float *)(param_1 + 0x1dc8),
     *(float *)(param_1 + 0x568) <= fVar2)) {
    *(undefined1 *)(param_1 + 0x588) = 1;
  }
  if (*(short *)(param_1 + 0x550) == 0) {
    sVar4 = 0;
  }
  else {
    sVar4 = *(short *)(*(int *)(param_1 + 0x4ac) + 0x42);
  }
  dVar6 = zz_0045204_(sVar4);
  *(float *)(param_1 + 0x4c) = (float)((double)*(float *)(*(int *)(param_1 + 0x4ac) + 0x44) * dVar6)
  ;
  iVar5 = *(int *)(param_1 + 0x4ac);
  dVar6 = zz_0045238_(sVar4);
  *(float *)(param_1 + 0x50) =
       (float)((double)*(float *)(iVar5 + 0x44) * dVar6 + (double)*(float *)(iVar5 + 0x68));
  if (sVar4 == 0) {
    *(float *)(param_1 + 0x44) =
         *(float *)(param_1 + 0x44) *
         (FLOAT_8043756c * (FLOAT_80437510 - *(float *)(param_1 + 0x1dc8)) + FLOAT_80437568);
  }
  if (*(char *)(param_1 + 0x588) == '\0') {
    FUN_80067310((double)FLOAT_80437510,param_1,*(short *)(param_1 + 0x5ae));
  }
  else {
    zz_0067458_((double)FLOAT_80437510,param_1,*(short *)(param_1 + 0x5ae));
  }
  zz_00677b0_(param_1);
  return;
}



// ==== 80062284  FUN_80062284 ====

void FUN_80062284(int param_1)

{
  char cVar1;
  double dVar2;
  
  cVar1 = *(char *)(param_1 + 0x540);
  if (cVar1 == '\x02') {
    dVar2 = (double)FLOAT_804374e8;
    *(undefined1 *)(param_1 + 0x540) = 3;
    zz_004beb8_(dVar2,param_1,0xd,0,0xf,0xffffffff,0xffffffff);
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      dVar2 = (double)FLOAT_804374e8;
      *(undefined1 *)(param_1 + 0x540) = 1;
      zz_004beb8_(dVar2,param_1,0xd,0,0xe,0xffffffff,0xffffffff);
    }
    else if ((-1 < cVar1) && (zz_004cd24_(param_1,0xd), '\x01' < *(char *)(param_1 + 0x544))) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    }
  }
  else if (cVar1 < '\x04') {
    zz_004cd24_(param_1,0xd);
  }
  return;
}



// ==== 8006235c  FUN_8006235c ====

void FUN_8006235c(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  short sVar4;
  double dVar5;
  
  iVar3 = zz_0066ac0_(param_1,0);
  if (iVar3 == 0) {
    sVar4 = 0;
  }
  else {
    sVar4 = *(short *)(*(int *)(param_1 + 0x4ac) + 0x42);
  }
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x02') {
    *(undefined1 *)(param_1 + 0x544) = 3;
    zz_00664a0_(param_1,1);
    zz_004beb8_((double)FLOAT_804374e8,param_1,2,0,0xf,0xffffffff,0xffffffff);
    if (*(char *)(*(int *)(param_1 + 0x4ac) + 0x41) == '\0') {
      zz_00f036c_(param_1,0x1e);
    }
    else {
      *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) | 1;
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0x544) = 1;
      fVar2 = FLOAT_80437540;
      *(undefined1 *)(param_1 + 0x87) = 1;
      *(undefined1 *)(param_1 + 0x590) = 2;
      *(float *)(param_1 + 0x690) = fVar2;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffdfff;
      zz_00664a0_(param_1,0);
      *(undefined1 *)(param_1 + 0x5e7) = 0;
      dVar5 = (double)FLOAT_804374e8;
      *(float *)(param_1 + 0x690) =
           (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(*(int *)(param_1 + 0x4ac) + 0x3e)) -
                  DOUBLE_80437500);
      *(float *)(param_1 + 0x48) =
           *(float *)(param_1 + 0x48) + *(float *)(*(int *)(param_1 + 0x4ac) + 0x4c);
      *(undefined1 *)(param_1 + 0x588) = 1;
      zz_004beb8_(dVar5,param_1,2,0,0xe,0xffffffff,0xffffffff);
      if (*(char *)(*(int *)(param_1 + 0x4ac) + 0x41) != '\0') {
        *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) | 1;
      }
    }
    else if (-1 < cVar1) {
      zz_00664a0_(param_1,1);
      iVar3 = zz_004cd24_(param_1,2);
      if (iVar3 != 0) {
        *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
      }
    }
  }
  else if (cVar1 < '\x04') {
    zz_00664a0_(param_1,1);
    zz_004cd24_(param_1,2);
  }
  zz_0066e40_(param_1,1);
  *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  dVar5 = zz_0045204_(sVar4);
  *(float *)(param_1 + 0x4c) = (float)((double)*(float *)(*(int *)(param_1 + 0x4ac) + 0x44) * dVar5)
  ;
  iVar3 = *(int *)(param_1 + 0x4ac);
  dVar5 = zz_0045238_(sVar4);
  *(float *)(param_1 + 0x50) =
       (float)((double)*(float *)(iVar3 + 0x44) * dVar5 + (double)*(float *)(iVar3 + 0x68));
  if (sVar4 == 0) {
    *(float *)(param_1 + 0x44) =
         *(float *)(param_1 + 0x44) *
         (FLOAT_8043756c * (FLOAT_80437510 - *(float *)(param_1 + 0x1dc8)) + FLOAT_80437568);
  }
  zz_0067458_((double)FLOAT_80437510,param_1,*(short *)(param_1 + 0x5ae));
  iVar3 = zz_00677b0_(param_1);
  if ((iVar3 != 0) && (*(float *)(param_1 + 0x48) < FLOAT_804374ec)) {
    *(float *)(param_1 + 0x48) =
         *(float *)(param_1 + 0x48) *
         (FLOAT_80437584 * (FLOAT_80437510 - *(float *)(param_1 + 0x1dc8)) + FLOAT_8043751c);
  }
  return;
}



// ==== 80062614  FUN_80062614 ====

void FUN_80062614(int param_1)

{
  double dVar1;
  
  if (*(char *)(param_1 + 0x540) == '\0') {
    dVar1 = (double)FLOAT_804374e8;
    *(undefined1 *)(param_1 + 0x540) = 1;
    zz_004beb8_(dVar1,param_1,0xd,0,0x22,0xffffffff,0xffffffff);
  }
  else {
    zz_004cd24_(param_1,0xd);
  }
  return;
}



// ==== 8006266c  FUN_8006266c ====

void FUN_8006266c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    fVar1 = FLOAT_804374ec;
    dVar4 = (double)FLOAT_804374e8;
    *(float *)(param_1 + 0x50) = FLOAT_804374ec;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(code **)(param_1 + 0x754) = FUN_80065e64;
    *(undefined1 *)(param_1 + 0x590) = 1;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffdfff;
    zz_004beb8_(dVar4,param_1,2,0,0x22,0xffffffff,0xffffffff);
  }
  else {
    zz_004cd24_(param_1,2);
  }
  fVar2 = FLOAT_80437588;
  fVar1 = FLOAT_80437570;
  dVar4 = (double)FLOAT_80437510;
  *(float *)(param_1 + 0x44) =
       *(float *)(param_1 + 0x44) *
       (FLOAT_80437588 * (float)(dVar4 - (double)*(float *)(param_1 + 0x1dc8)) + FLOAT_80437570);
  *(float *)(param_1 + 0x48) =
       *(float *)(param_1 + 0x48) *
       (fVar2 * (float)(dVar4 - (double)*(float *)(param_1 + 0x1dc8)) + fVar1);
  zz_0067458_(dVar4,param_1,*(short *)(param_1 + 0x5ae));
  iVar3 = zz_00677b0_(param_1);
  fVar1 = FLOAT_804374ec;
  if (iVar3 != 0) {
    *(float *)(param_1 + 0x50) = FLOAT_804374ec;
    *(float *)(param_1 + 0x48) = fVar1;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
    *(undefined2 *)(param_1 + 0x80) = 0;
    *(undefined2 *)(param_1 + 0x7e) = 0;
    *(undefined2 *)(param_1 + 0x7c) = 0;
  }
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x840;
  return;
}



// ==== 80062784  FUN_80062784 ====

void FUN_80062784(int param_1)

{
  zz_005f318_(param_1);
  return;
}



// ==== 800627a4  FUN_800627a4 ====

void FUN_800627a4(int param_1)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  double dVar5;
  
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffdfff;
    zz_0066ac0_(param_1,0);
    iVar2 = zz_0046510_(*(ushort *)(param_1 + 0x5aa),1);
    fVar1 = FLOAT_804374ec;
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + iVar2 * 4 + 0x18);
    *(float *)(param_1 + 0x4c) = fVar1;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
    uVar3 = (uint)*(short *)(param_1 + 0x5aa);
    if (*(short *)(param_1 + 0x5aa) < 0) {
      uVar3 = -uVar3;
    }
    uVar4 = (uint)*(ushort *)(*(int *)(param_1 + 0x4b0) + 0xc0);
    iVar2 = (int)(((float)((double)CONCAT44(0x43300000,uVar3 ^ 0x80000000) - DOUBLE_804374f8) /
                  FLOAT_804374f0) *
                  (float)((double)CONCAT44(0x43300000,
                                           *(ushort *)(*(int *)(param_1 + 0x4b0) + 200) - uVar4 ^
                                           0x80000000) - DOUBLE_804374f8) +
                 (float)((double)CONCAT44(0x43300000,uVar4) - DOUBLE_80437500));
    zz_0066ec0_(param_1,iVar2);
    zz_004beb8_((double)FLOAT_804374e8,param_1,2,0,1,iVar2,0xffffffff);
  }
  else {
    zz_004cd24_(param_1,2);
    iVar2 = zz_0066f1c_(param_1);
    if (iVar2 != 0) {
      zz_006a750_(param_1,0x14);
    }
  }
  dVar5 = (double)FLOAT_80437510;
  *(float *)(param_1 + 0x48) =
       *(float *)(param_1 + 0x48) *
       (FLOAT_80437588 * (float)(dVar5 - (double)*(float *)(param_1 + 0x1dc8)) + FLOAT_80437570);
  zz_0067458_(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x840;
  return;
}



// ==== 80062970  FUN_80062970 ====

void FUN_80062970(int param_1)

{
  zz_005f554_(param_1);
  return;
}



// ==== 80062990  FUN_80062990 ====

void FUN_80062990(int param_1)

{
  *(float *)(param_1 + 0x48) =
       *(float *)(param_1 + 0x48) *
       (FLOAT_80437588 * (FLOAT_80437510 - *(float *)(param_1 + 0x1dc8)) + FLOAT_80437570);
  zz_005f578_(param_1);
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x840;
  return;
}



// ==== 800629ec  FUN_800629ec ====

void FUN_800629ec(int param_1)

{
  zz_005f624_(param_1);
  return;
}



// ==== 80062a0c  FUN_80062a0c ====

void FUN_80062a0c(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  double dVar6;
  
  fVar5 = FLOAT_80437588;
  fVar4 = FLOAT_80437570;
  fVar3 = FLOAT_8043756c;
  fVar2 = FLOAT_80437568;
  fVar1 = FLOAT_80437510;
  *(float *)(param_1 + 0x44) =
       *(float *)(param_1 + 0x44) *
       (FLOAT_8043756c * (FLOAT_80437510 - *(float *)(param_1 + 0x1dc8)) + FLOAT_80437568);
  *(float *)(param_1 + 0x4c) =
       *(float *)(param_1 + 0x4c) * (fVar3 * (fVar1 - *(float *)(param_1 + 0x1dc8)) + fVar2);
  *(float *)(param_1 + 0x48) =
       *(float *)(param_1 + 0x48) * (fVar5 * (fVar1 - *(float *)(param_1 + 0x1dc8)) + fVar4);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x544) == '\0') {
    dVar6 = (double)FLOAT_804374e8;
    *(undefined1 *)(param_1 + 0x544) = 1;
    zz_004beb8_(dVar6,param_1,2,0,0,6,1);
  }
  else {
    zz_004cd24_(param_1,2);
    if (*(char *)(param_1 + 0x1b43) == '\0') {
      zz_006a4f4_(param_1);
    }
  }
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x840;
  return;
}



// ==== 80062afc  FUN_80062afc ====

void FUN_80062afc(int param_1)

{
  zz_0060be8_(param_1);
  return;
}



// ==== 80062b1c  FUN_80062b1c ====

void FUN_80062b1c(int param_1)

{
  zz_0060c94_(param_1);
  zz_006a750_(param_1,0x17);
  zz_0092dcc_(param_1,0);
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x840;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffdfff;
  return;
}



// ==== 80062b78  FUN_80062b78 ====

void FUN_80062b78(int param_1)

{
  zz_0060e94_(param_1);
  return;
}



// ==== 80062b98  FUN_80062b98 ====

void FUN_80062b98(int param_1)

{
  zz_0060f78_(param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x840;
  if (*(char *)(param_1 + 0x545) != '\0') {
    zz_006a750_(param_1,0x18);
  }
  return;
}



// ==== 80062bf4  FUN_80062bf4 ====

void FUN_80062bf4(int param_1)

{
  zz_0061048_(param_1);
  return;
}



// ==== 80062c14  FUN_80062c14 ====

void FUN_80062c14(int param_1)

{
  float fVar1;
  
  zz_0061160_(param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1d0e) != '\0') {
    zz_006a4f4_(param_1);
    fVar1 = FLOAT_804374ec;
    *(undefined1 *)(param_1 + 0x590) = 1;
    *(float *)(param_1 + 0x690) = fVar1;
  }
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x840;
  return;
}



// ==== 80062c7c  FUN_80062c7c ====

void FUN_80062c7c(int param_1)

{
  char cVar1;
  float fVar2;
  short sVar4;
  int iVar3;
  
  *(undefined1 *)(param_1 + 0x719) = 1;
  if (*(char *)(param_1 + 0x4a1) == '\0') {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a474_(param_1);
    }
    else {
      zz_006a5a4_(param_1);
    }
  }
  else {
    cVar1 = *(char *)(param_1 + 0x544);
    if (cVar1 == '\x02') {
      iVar3 = zz_004cd24_(param_1,0xf);
      if (iVar3 != 0) {
        *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
        *(undefined1 *)(param_1 + 0x4a1) = 2;
      }
    }
    else if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        *(undefined1 *)(param_1 + 0x544) = 1;
        *(undefined4 *)(param_1 + 0x754) = 0;
        *(undefined2 *)(param_1 + 0x272) = 0xc3;
        *(undefined1 *)(param_1 + 0x4a1) = 1;
        *(undefined2 *)(param_1 + 0x550) = 0x3c;
        *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffdfff;
        zz_00666c8_(param_1,(float *)(*(int *)(param_1 + 0x4a4) + 0x20));
        zz_0066ec0_(param_1,0x1e);
        zz_004beb8_((double)FLOAT_804374e8,param_1,0xf,0,0,0xffffffff,0xffffffff);
      }
      else if (-1 < cVar1) {
        zz_004cd24_(param_1,0xf);
        zz_0066f1c_(param_1);
        sVar4 = *(short *)(param_1 + 0x550) + -1;
        *(short *)(param_1 + 0x550) = sVar4;
        fVar2 = FLOAT_804374ec;
        if (sVar4 == 0) {
          *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
          *(float *)(param_1 + 0x50) = fVar2;
          *(float *)(param_1 + 0x4c) = fVar2;
          zz_00107a0_(param_1,6);
          zz_004beb8_((double)FLOAT_804374e8,param_1,0xf,0,0x23,0xffffffff,0xffffffff);
        }
      }
    }
    else if (cVar1 == '\x04') {
      iVar3 = zz_004cd24_(param_1,0xf);
      if (iVar3 != 0) {
        zz_006a750_(param_1,0x1a);
      }
    }
    else if ((cVar1 < '\x04') && (*(char *)(param_1 + 0x4a1) == '\x03')) {
      *(char *)(param_1 + 0x544) = cVar1 + '\x01';
      zz_004cff4_(param_1,0xf);
    }
  }
  return;
}



// ==== 80062e44  FUN_80062e44 ====

void FUN_80062e44(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  short sVar5;
  double dVar6;
  
  *(undefined1 *)(param_1 + 0x719) = 1;
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x02') {
    if (*(char *)(param_1 + 0x4a1) == '\x06') {
      *(undefined1 *)(param_1 + 0x544) = 3;
      *(undefined2 *)(param_1 + 0x550) = 0x1e;
      *(undefined2 *)(param_1 + 0x552) = 0;
      if (*(char *)(param_1 + 0x4a8) == '\x01') {
        *(float *)(param_1 + 0x48) =
             -(*(float *)(*(int *)(param_1 + 0x4a4) + 0x668) / FLOAT_80437558) * FLOAT_80437534;
        if (*(int *)(param_1 + 0x508) != 0) {
          zz_00666c8_(param_1,(float *)(param_1 + 0x50c));
        }
      }
      else {
        *(float *)(param_1 + 0x48) = (*(float *)(param_1 + 0x668) / FLOAT_80437558) * FLOAT_80437534
        ;
        if (*(int *)(*(int *)(param_1 + 0x4a4) + 0x508) != 0) {
          zz_00666c8_(param_1,(float *)(*(int *)(param_1 + 0x4a4) + 0x50c));
        }
      }
      zz_0066ec0_(param_1,0x14);
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0x544) = 1;
      fVar2 = FLOAT_804374ec;
      *(undefined2 *)(param_1 + 0x272) = 0xffff;
      fVar3 = FLOAT_8043758c;
      *(undefined1 *)(param_1 + 0x4a1) = 4;
      fVar4 = FLOAT_80437590;
      *(float *)(param_1 + 0x50) = fVar2;
      dVar6 = (double)FLOAT_804374e8;
      *(float *)(param_1 + 0x48) = fVar2;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(float *)(param_1 + 0x44) = fVar2;
      *(undefined2 *)(param_1 + 0x80) = 0;
      *(undefined2 *)(param_1 + 0x7e) = 0;
      *(undefined2 *)(param_1 + 0x7c) = 0;
      *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x8d4);
      *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x8e4);
      *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x8f4);
      *(float *)(param_1 + 0x44) = fVar3;
      *(undefined2 *)(param_1 + 0x550) = 0;
      *(float *)(param_1 + 0x568) = fVar4;
      *(undefined1 *)(param_1 + 0x579) = 7;
      zz_004beb8_(dVar6,param_1,0xf,0,0x25,0xffffffff,0xffffffff);
      zz_00f036c_(param_1,0xb2);
    }
    else if (-1 < cVar1) {
      zz_004cd24_(param_1,0xf);
      sVar5 = *(short *)(param_1 + 0x550) + 1;
      *(short *)(param_1 + 0x550) = sVar5;
      if (sVar5 < 2) {
        gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),
                         (float *)(param_1 + 0x20));
      }
      else {
        zz_006c440_((double)*(float *)(param_1 + 0x568),param_1,(float *)(param_1 + 0x7a4));
        fVar2 = FLOAT_80437590;
        *(undefined2 *)(param_1 + 0x550) = 0;
        fVar3 = FLOAT_80437594;
        *(float *)(param_1 + 0x568) = *(float *)(param_1 + 0x568) + fVar2;
        if (fVar3 < *(float *)(param_1 + 0x568)) {
          *(float *)(param_1 + 0x568) = fVar3;
        }
        fVar2 = FLOAT_80437540;
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) + FLOAT_804374e8;
        if (*(float *)(param_1 + 0x44) < fVar2) {
          *(float *)(param_1 + 0x44) = fVar2;
        }
      }
      dVar6 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x7a4));
      fVar2 = FLOAT_804374ec;
      if (dVar6 <= (double)FLOAT_80437598) {
        *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
        *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 4;
        *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x7a4);
        *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x7a8);
        *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x7ac);
        *(undefined1 *)(param_1 + 0x4a1) = 5;
        *(float *)(param_1 + 0x50) = fVar2;
        *(float *)(param_1 + 0x48) = fVar2;
        *(float *)(param_1 + 0x4c) = fVar2;
        *(float *)(param_1 + 0x44) = fVar2;
        *(undefined2 *)(param_1 + 0x80) = 0;
        *(undefined2 *)(param_1 + 0x7e) = 0;
        *(undefined2 *)(param_1 + 0x7c) = 0;
      }
    }
  }
  else if (cVar1 == '\x04') {
    sVar5 = *(short *)(param_1 + 0x550) + -1;
    *(short *)(param_1 + 0x550) = sVar5;
    if (sVar5 == 0) {
      *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
      *(undefined1 *)(param_1 + 0x4a1) = 7;
    }
  }
  else if ((cVar1 < '\x04') && (zz_004cd24_(param_1,0xf), *(short *)(param_1 + 0x550) != 0)) {
    zz_0067458_((double)FLOAT_80437510,param_1,*(short *)(param_1 + 0x5ae));
    zz_0066f1c_(param_1);
    zz_00677b0_(param_1);
    sVar5 = *(short *)(param_1 + 0x550) + -1;
    *(short *)(param_1 + 0x550) = sVar5;
    if (sVar5 < 1) {
      if (*(char *)(param_1 + 0x4a8) == '\x02') {
        zz_00f6654_(param_1);
        zz_00f036c_(param_1,0x9b);
      }
      else {
        *(uint *)(param_1 + 0x810) = *(uint *)(param_1 + 0x810) | 0x1000;
      }
      fVar2 = FLOAT_804374ec;
      *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
      *(undefined2 *)(param_1 + 0x550) = 0x1e;
      *(float *)(param_1 + 0x38) = fVar2;
      *(float *)(param_1 + 0x3c) = fVar2;
      *(float *)(param_1 + 0x40) = fVar2;
      *(float *)(param_1 + 0x50) = fVar2;
      *(float *)(param_1 + 0x48) = fVar2;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(float *)(param_1 + 0x44) = fVar2;
      *(undefined2 *)(param_1 + 0x80) = 0;
      *(undefined2 *)(param_1 + 0x7e) = 0;
      *(undefined2 *)(param_1 + 0x7c) = 0;
    }
  }
  if (*(char *)(*(int *)(param_1 + 0x4a4) + 0x4a1) == '\0') {
    dVar6 = (double)FLOAT_804374ec;
    *(undefined1 *)(param_1 + 0x579) = *(undefined1 *)(*(int *)(param_1 + 0x4b0) + 2);
    *(undefined2 *)(param_1 + 0x272) = 0;
    zz_004beb8_(dVar6,param_1,0xf,0,0xd,0,0);
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 80063230  FUN_80063230 ====

void FUN_80063230(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  *(undefined1 *)(param_1 + 0x719) = 1;
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x01') {
    iVar3 = zz_004cd24_(param_1,0xf);
    if (iVar3 != 0) {
      *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
      zz_0010784_(param_1);
      zz_0010784_(*(int *)(param_1 + 0x4a4));
      zz_008b1e8_();
      zz_004cff4_(param_1,0xf);
      zz_0067458_((double)FLOAT_80437510,param_1,*(short *)(param_1 + 0x5ae));
      zz_00677b0_(param_1);
      zz_00def38_(param_1);
    }
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      *(char *)(param_1 + 0x544) = cVar1 + '\x01';
      fVar2 = FLOAT_804374ec;
      *(undefined4 *)(param_1 + 0x754) = 0;
      *(float *)(param_1 + 0x50) = fVar2;
      *(float *)(param_1 + 0x48) = fVar2;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(float *)(param_1 + 0x44) = fVar2;
      *(undefined2 *)(param_1 + 0x80) = 0;
      *(undefined2 *)(param_1 + 0x7e) = 0;
      *(undefined2 *)(param_1 + 0x7c) = 0;
      zz_00107a0_(param_1,0x11);
      zz_00107a0_(*(int *)(param_1 + 0x4a4),0x11);
      iVar3 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0xf) * 0x30;
      local_18 = *(undefined4 *)(iVar3 + 0x8e0);
      local_14 = *(undefined4 *)(iVar3 + 0x8f0);
      local_10 = *(undefined4 *)(iVar3 + 0x900);
      zz_00e7018_(param_1,&local_18);
      zz_004beb8_((double)FLOAT_804374e8,param_1,0xf,0,0x25,0xffffffff,0xffffffff);
    }
  }
  else if (cVar1 < '\x03') {
    zz_0067458_((double)FLOAT_80437510,param_1,*(short *)(param_1 + 0x5ae));
    zz_00677b0_(param_1);
    iVar3 = zz_004cd24_(param_1,0xf);
    if (iVar3 != 0) {
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 800633c8  FUN_800633c8 ====

void FUN_800633c8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  undefined8 local_20;
  undefined8 local_18;
  
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    *(undefined1 *)(param_1 + 0x87) = 1;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffdfff;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x68);
    if (*(char *)(*(int *)(param_1 + 0x4ac) + 0x41) != '\0') {
      *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) | 1;
    }
  }
  zz_0066c58_(param_1);
  local_20 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x5aa)) ^ 0x80000000);
  fVar1 = FLOAT_8043759c * *(float *)(param_1 + 0x1dc8);
  *(short *)(param_1 + 0x1d68) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1d68) ^ 0x80000000) -
                           DOUBLE_804374f8) * (FLOAT_80437510 - fVar1) +
                   -((float)(local_20 - DOUBLE_804374f8) * FLOAT_8043759c) * fVar1);
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x1d64));
  *(float *)(param_1 + 0x4c) = (float)((double)*(float *)(*(int *)(param_1 + 0x4ac) + 0x44) * dVar4)
  ;
  dVar4 = zz_0045204_(-*(short *)(param_1 + 0x1d64));
  *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x67c) * dVar4);
  zz_0066e40_(param_1,1);
  *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  if ((*(char *)(param_1 + 0x18) == '\x01') && ('\x01' < *(char *)(param_1 + 0x19))) {
    FUN_80067310((double)FLOAT_804374ec,param_1,*(short *)(param_1 + 0x5ae));
  }
  fVar1 = *(float *)(*(int *)(param_1 + 0x4ac) + 0x2c);
  fVar2 = *(float *)(param_1 + 0x44) - fVar1;
  if (FLOAT_804374ec < fVar2) {
    if (*(float *)(param_1 + 0x4c) < fVar2) {
      *(float *)(param_1 + 0x44) =
           (FLOAT_80437588 * (FLOAT_80437510 - *(float *)(param_1 + 0x1dc8)) + FLOAT_80437570) *
           (*(float *)(param_1 + 0x44) - *(float *)(param_1 + 0x4c));
      fVar1 = *(float *)(*(int *)(param_1 + 0x4ac) + 0x2c);
      if (*(float *)(param_1 + 0x44) < fVar1) {
        *(float *)(param_1 + 0x44) = fVar1;
      }
    }
    else {
      *(float *)(param_1 + 0x44) = fVar1;
    }
  }
  iVar3 = zz_00677b0_(param_1);
  fVar1 = FLOAT_804374ec;
  if (iVar3 == 0) {
    *(undefined1 *)(param_1 + 0x545) = 0;
  }
  else {
    if (*(char *)(param_1 + 0x545) == '\0') {
      *(undefined1 *)(param_1 + 0x545) = 1;
      *(float *)(param_1 + 0x80c) = fVar1;
    }
    zz_00b22f4_(param_1);
    fVar1 = FLOAT_80437510;
    *(float *)(param_1 + 0x48) = FLOAT_804374ec;
    local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1d64)) ^ 0x80000000);
    *(short *)(param_1 + 0x1d64) =
         (short)(int)((float)(local_18 - DOUBLE_804374f8) *
                     (FLOAT_80437584 * (fVar1 - *(float *)(param_1 + 0x1dc8)) + FLOAT_8043751c));
  }
  return;
}



// ==== 80063644  FUN_80063644 ====

void FUN_80063644(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  double local_20;
  double local_18;
  
  zz_00664a0_(param_1,3);
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x80;
  zz_00f0104_(param_1,0x13,6);
  fVar2 = FLOAT_804374ec;
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x01') {
    *(float *)(param_1 + 0x568) = *(float *)(param_1 + 0x568) - *(float *)(param_1 + 0x5f4);
    if (*(float *)(param_1 + 0x568) <= fVar2) {
      *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
      *(float *)(param_1 + 0x4c) = fVar2;
      *(undefined1 *)(param_1 + 0x588) = 1;
    }
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    *(char *)(param_1 + 0x544) = cVar1 + '\x01';
    fVar2 = FLOAT_804374ec;
    *(undefined1 *)(param_1 + 0x546) = 1;
    *(undefined1 *)(param_1 + 0x87) = 1;
    *(undefined1 *)(param_1 + 0x5e6) = 0;
    *(undefined1 *)(param_1 + 0x656) = 1;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffdfff;
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x58);
    *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x5c);
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x70);
    *(undefined4 *)(param_1 + 0x568) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 100);
    *(float *)(param_1 + 0x56c) = fVar2;
    if (*(char *)(*(int *)(param_1 + 0x4ac) + 0x41) != '\0') {
      *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) | 1;
    }
  }
  zz_0066c58_(param_1);
  local_20 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x5aa)) ^ 0x80000000);
  fVar2 = FLOAT_8043759c * *(float *)(param_1 + 0x1dc8);
  *(short *)(param_1 + 0x1d68) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1d68) ^ 0x80000000) -
                           DOUBLE_804374f8) * (FLOAT_80437510 - fVar2) +
                   -((float)(local_20 - DOUBLE_804374f8) * FLOAT_8043759c) * fVar2);
  dVar4 = zz_0045204_(-*(short *)(param_1 + 0x1d64));
  *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x44) * dVar4);
  zz_0066e40_(param_1,2);
  dVar4 = (double)FLOAT_804374ec;
  *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  FUN_80067310(dVar4,param_1,*(short *)(param_1 + 0x5ae));
  fVar2 = FLOAT_804374ec;
  *(float *)(param_1 + 0x56c) = *(float *)(param_1 + 0x56c) - *(float *)(param_1 + 0x1dc8);
  if (*(float *)(param_1 + 0x56c) <= fVar2) {
    zz_0092dcc_(param_1,0);
    *(float *)(param_1 + 0x56c) = FLOAT_804375a0;
  }
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 == 0) {
    *(undefined1 *)(param_1 + 0x545) = 0;
  }
  else {
    if (*(char *)(param_1 + 0x546) != '\0') {
      zz_00b2190_(param_1,0);
    }
    fVar2 = FLOAT_804374ec;
    if (*(char *)(param_1 + 0x545) == '\0') {
      *(undefined1 *)(param_1 + 0x545) = 1;
      *(float *)(param_1 + 0x80c) = fVar2;
    }
    zz_00b22f4_(param_1);
    fVar2 = FLOAT_80437510;
    *(float *)(param_1 + 0x48) = FLOAT_804374ec;
    local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1d64)) ^ 0x80000000);
    *(short *)(param_1 + 0x1d64) =
         (short)(int)((float)(local_18 - DOUBLE_804374f8) *
                     (FLOAT_80437584 * (fVar2 - *(float *)(param_1 + 0x1dc8)) + FLOAT_8043751c));
  }
  *(undefined1 *)(param_1 + 0x546) = 0;
  return;
}



// ==== 80063910  FUN_80063910 ====

void FUN_80063910(int param_1)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    *(undefined1 *)(param_1 + 0x87) = 1;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x50;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffdfdf;
    zz_0066ac0_(param_1,0);
    iVar2 = zz_0046510_(*(ushort *)(param_1 + 0x5aa),1);
    fVar1 = FLOAT_804374ec;
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + iVar2 * 4 + 0x18);
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
    *(float *)(param_1 + 0x50) = fVar1;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
    uVar3 = (uint)*(short *)(param_1 + 0x5aa);
    if (*(short *)(param_1 + 0x5aa) < 0) {
      uVar3 = -uVar3;
    }
    uVar4 = (uint)*(ushort *)(*(int *)(param_1 + 0x4b0) + 0xc0);
    zz_0066ec0_(param_1,(int)(((float)((double)CONCAT44(0x43300000,uVar3 ^ 0x80000000) -
                                      DOUBLE_804374f8) / FLOAT_804374f0) *
                              (float)((double)CONCAT44(0x43300000,
                                                       *(ushort *)(*(int *)(param_1 + 0x4b0) + 200)
                                                       - uVar4 ^ 0x80000000) - DOUBLE_804374f8) +
                             (float)((double)CONCAT44(0x43300000,uVar4) - DOUBLE_80437500)));
  }
  else {
    zz_0067458_((double)FLOAT_80437510,param_1,*(short *)(param_1 + 0x5ae));
    iVar2 = zz_0066f1c_(param_1);
    if (iVar2 != 0) {
      zz_006a750_(param_1,0x1e);
    }
  }
  return;
}



// ==== 80063a90  FUN_80063a90 ====

void FUN_80063a90(int param_1)

{
  float fVar1;
  double dVar2;
  undefined8 local_18;
  undefined8 local_10;
  
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    fVar1 = FLOAT_804374ec;
    *(undefined1 *)(param_1 + 0x87) = 1;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x50;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffdfdf;
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x2c);
    *(float *)(param_1 + 0x4c) = fVar1;
    if (*(char *)(*(int *)(param_1 + 0x4ac) + 0x41) != '\0') {
      *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) | 5;
    }
  }
  fVar1 = FLOAT_804375a4;
  dVar2 = DOUBLE_804374f8;
  if ((*(uint *)(param_1 + 0x5b4) & 0x100) == 0) {
    if (FLOAT_804374ec < *(float *)(param_1 + 0x48)) {
      *(float *)(param_1 + 0x48) =
           *(float *)(param_1 + 0x48) *
           (FLOAT_80437518 * (FLOAT_80437510 - *(float *)(param_1 + 0x1dc8)) + FLOAT_80437514);
    }
    fVar1 = FLOAT_804375a4;
    dVar2 = DOUBLE_804374f8;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x70);
    local_10 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1d64)) ^ 0x80000000);
    fVar1 = fVar1 * *(float *)(param_1 + 0x1dc8);
    *(short *)(param_1 + 0x1d64) =
         (short)(int)(FLOAT_804375ac * fVar1 + (float)(local_10 - dVar2) * (FLOAT_80437510 - fVar1))
    ;
  }
  else {
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x44);
    local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1d64)) ^ 0x80000000);
    fVar1 = fVar1 * *(float *)(param_1 + 0x1dc8);
    *(short *)(param_1 + 0x1d64) =
         (short)(int)(FLOAT_804375a8 * fVar1 + (float)(local_18 - dVar2) * (FLOAT_80437510 - fVar1))
    ;
  }
  zz_0066ac0_(param_1,0);
  zz_0066e40_(param_1,1);
  dVar2 = (double)FLOAT_80437510;
  *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  zz_0067458_(dVar2,param_1,*(short *)(param_1 + 0x5ae));
  return;
}



// ==== 80063c48  FUN_80063c48 ====

void FUN_80063c48(int param_1)

{
  float fVar1;
  double dVar2;
  
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    fVar1 = FLOAT_804374ec;
    *(undefined1 *)(param_1 + 0x87) = 1;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x50;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffdfdf;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(undefined1 *)(param_1 + 0x709) = 0;
  }
  else if (*(float *)(param_1 + 0x44) < FLOAT_80437510) {
    zz_006a474_(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
  }
  dVar2 = (double)FLOAT_80437510;
  *(float *)(param_1 + 0x44) =
       *(float *)(param_1 + 0x44) *
       (FLOAT_80437518 * (float)(dVar2 - (double)*(float *)(param_1 + 0x1dc8)) + FLOAT_80437514);
  zz_0067458_(dVar2,param_1,*(short *)(param_1 + 0x5ae));
  *(short *)(param_1 + 0x1d64) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1d64) ^ 0x80000000) -
                           DOUBLE_804374f8) *
                   (FLOAT_80437588 * (FLOAT_80437510 - *(float *)(param_1 + 0x1dc8)) +
                   FLOAT_80437570));
  return;
}



// ==== 80063d58  FUN_80063d58 ====

void FUN_80063d58(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  fVar1 = FLOAT_804374ec;
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    fVar2 = FLOAT_804375b0;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x50) = fVar1;
    *(undefined1 *)(param_1 + 0x709) = 0;
    *(float *)(param_1 + 0x568) = fVar2;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffdfff;
  }
  fVar2 = FLOAT_80437588;
  fVar1 = FLOAT_80437570;
  dVar4 = (double)FLOAT_80437510;
  *(float *)(param_1 + 0x44) =
       *(float *)(param_1 + 0x44) *
       (FLOAT_80437588 * (float)(dVar4 - (double)*(float *)(param_1 + 0x1dc8)) + FLOAT_80437570);
  *(float *)(param_1 + 0x48) =
       *(float *)(param_1 + 0x48) *
       (fVar2 * (float)(dVar4 - (double)*(float *)(param_1 + 0x1dc8)) + fVar1);
  zz_0067458_(dVar4,param_1,*(short *)(param_1 + 0x5ae));
  fVar1 = FLOAT_804375b4;
  *(short *)(param_1 + 0x1d64) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1d64) ^ 0x80000000) -
                           DOUBLE_804374f8) *
                   (FLOAT_80437588 * (FLOAT_80437510 - *(float *)(param_1 + 0x1dc8)) +
                   FLOAT_80437570));
  if (*(float *)(param_1 + 0x44) < fVar1) {
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  }
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 != 0) {
    *(float *)(param_1 + 0x568) = FLOAT_804375b0;
  }
  fVar1 = FLOAT_804374ec;
  *(float *)(param_1 + 0x568) = *(float *)(param_1 + 0x568) - *(float *)(param_1 + 0x1dc8);
  if (*(float *)(param_1 + 0x568) < fVar1) {
    zz_006a750_(param_1,6);
  }
  return;
}



// ==== 80063eb8  FUN_80063eb8 ====

void FUN_80063eb8(int param_1)

{
  float fVar1;
  double dVar2;
  
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    *(undefined1 *)(param_1 + 0x87) = 1;
    fVar1 = FLOAT_804374ec;
    *(code **)(param_1 + 0x754) = FUN_80065e64;
    *(undefined2 *)(param_1 + 0x5aa) = 0;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(undefined1 *)(param_1 + 0x588) = 1;
  }
  *(float *)(param_1 + 0x44) =
       *(float *)(param_1 + 0x44) *
       (FLOAT_80437518 * (FLOAT_80437510 - *(float *)(param_1 + 0x1dc8)) + FLOAT_80437514);
  dVar2 = FUN_8003d6e4((double)*(float *)(param_1 + 0x668),param_1,(float *)(param_1 + 0x20));
  if ((float)((double)*(float *)(param_1 + 0x24) - dVar2) < *(float *)(param_1 + 0x668)) {
    *(float *)(param_1 + 0x48) =
         *(float *)(param_1 + 0x48) *
         (FLOAT_80437588 * (FLOAT_80437510 - *(float *)(param_1 + 0x1dc8)) + FLOAT_80437570);
  }
  zz_0067458_((double)FLOAT_80437510,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  return;
}



// ==== 80063fac  FUN_80063fac ====

void FUN_80063fac(int param_1)

{
  double dVar1;
  
  if (*(char *)(param_1 + 0x540) == '\0') {
    dVar1 = (double)FLOAT_804374e8;
    *(undefined1 *)(param_1 + 0x540) = 1;
    zz_004beb8_(dVar1,param_1,0xd,0,10,0xffffffff,0xffffffff);
  }
  else {
    zz_004cd24_(param_1,0xd);
  }
  return;
}



// ==== 80064004  FUN_80064004 ====

void FUN_80064004(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  undefined8 local_18;
  
  *(float *)(param_1 + 0x69c) = FLOAT_80437558;
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    *(undefined1 *)(param_1 + 0x87) = 1;
    *(undefined1 *)(param_1 + 0x5e6) = 0;
    *(undefined1 *)(param_1 + 0x656) = 1;
    zz_0066ac0_(param_1,0);
    fVar2 = FLOAT_80437534;
    fVar1 = FLOAT_804374ec;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffdfff;
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar2;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * fVar2;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    if (*(char *)(param_1 + 0x661) == '\x02') {
      iVar3 = zz_0046510_(*(ushort *)(param_1 + 0x5aa),1);
      local_18 = (double)CONCAT44(0x43300000,(uint)(byte)(&DAT_80433840)[iVar3]);
      *(float *)(param_1 + 0x568) = (float)(local_18 - DOUBLE_80437500);
    }
    else {
      iVar3 = zz_0046510_(*(ushort *)(param_1 + 0x5aa),1);
      local_18 = (double)CONCAT44(0x43300000,(uint)(byte)(&DAT_80433848)[iVar3]);
      *(float *)(param_1 + 0x568) = (float)(local_18 - DOUBLE_80437500);
    }
    zz_0066ec0_(param_1,(int)*(float *)(param_1 + 0x568));
    zz_004beb8_((double)FLOAT_804374e8,param_1,2,0,10,0xffffffff,0xffffffff);
  }
  else {
    zz_004cd24_(param_1,2);
    zz_0066f1c_(param_1);
    FUN_80067310((double)FLOAT_80437510,param_1,*(short *)(param_1 + 0x5ae));
    fVar1 = FLOAT_804374ec;
    *(float *)(param_1 + 0x568) = *(float *)(param_1 + 0x568) - *(float *)(param_1 + 0x1dc8);
    if (*(float *)(param_1 + 0x568) <= fVar1) {
      zz_00664a0_(param_1,2);
      zz_006a750_(param_1,0x21);
    }
  }
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 != 0) {
    *(float *)(param_1 + 0x48) = FLOAT_804374ec;
  }
  return;
}



// ==== 800641c0  FUN_800641c0 ====

void FUN_800641c0(int param_1)

{
  double dVar1;
  
  if (*(char *)(param_1 + 0x540) == '\0') {
    dVar1 = (double)FLOAT_804374e8;
    *(undefined1 *)(param_1 + 0x540) = 1;
    zz_004beb8_(dVar1,param_1,0xd,0,0xb,0xffffffff,0xffffffff);
  }
  else {
    zz_004cd24_(param_1,0xd);
  }
  return;
}



// ==== 80064218  FUN_80064218 ====

void FUN_80064218(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  fVar2 = FLOAT_804374ec;
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x01') {
    *(float *)(param_1 + 0x568) = *(float *)(param_1 + 0x568) - FLOAT_80437510;
    if (*(float *)(param_1 + 0x568) <= fVar2) {
      *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
      *(float *)(param_1 + 0x4c) = fVar2;
      *(undefined1 *)(param_1 + 0x588) = 1;
    }
  }
  else {
    if (cVar1 < '\x01') {
      if (-1 < cVar1) {
        *(char *)(param_1 + 0x544) = cVar1 + '\x01';
        zz_0092dcc_(param_1,0);
        zz_00f036c_(param_1,0x25);
        dVar4 = (double)FLOAT_804374e8;
        *(undefined4 *)(param_1 + 0x754) = 0;
        *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x58);
        *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x5c);
        *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x60);
        *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x70);
        *(undefined4 *)(param_1 + 0x568) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 100);
        zz_004beb8_(dVar4,param_1,2,0,0xb,0xffffffff,0xffffffff);
      }
      goto LAB_80064324;
    }
    if ('\x02' < cVar1) goto LAB_80064324;
  }
  zz_004cd24_(param_1,2);
LAB_80064324:
  if (*(char *)(*(int *)(param_1 + 0x4ac) + 0x41) != '\0') {
    *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) | 1;
  }
  *(float *)(param_1 + 0x69c) = FLOAT_80437558;
  zz_00664a0_(param_1,3);
  zz_0066ac0_(param_1,0);
  zz_0066e40_(param_1,2);
  dVar4 = (double)FLOAT_80437510;
  *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  zz_0067458_(dVar4,param_1,*(short *)(param_1 + 0x5ae));
  iVar3 = zz_00677b0_(param_1);
  if ((iVar3 != 0) && (*(float *)(param_1 + 0x48) < FLOAT_804374ec)) {
    *(float *)(param_1 + 0x48) =
         *(float *)(param_1 + 0x48) *
         (FLOAT_80437588 * (FLOAT_80437510 - *(float *)(param_1 + 0x1dc8)) + FLOAT_80437570);
  }
  return;
}



// ==== 800643d8  FUN_800643d8 ====

void FUN_800643d8(int param_1)

{
  double dVar1;
  
  if (*(char *)(param_1 + 0x540) == '\0') {
    dVar1 = (double)FLOAT_804374e8;
    *(undefined1 *)(param_1 + 0x540) = 1;
    zz_004beb8_(dVar1,param_1,0xd,0,0xc,0xffffffff,0xffffffff);
  }
  else {
    zz_004cd24_(param_1,0xd);
  }
  return;
}



// ==== 80064430  FUN_80064430 ====

void FUN_80064430(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    fVar1 = FLOAT_804374ec;
    *(undefined1 *)(param_1 + 0x545) = 0x1e;
    fVar2 = FLOAT_80437558;
    *(undefined4 *)(param_1 + 0x754) = 0;
    dVar3 = (double)FLOAT_804374e8;
    *(undefined2 *)(param_1 + 0x7e) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = 0;
    *(undefined2 *)(param_1 + 0x5aa) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(undefined1 *)(param_1 + 0x588) = 1;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x50) = fVar1;
    *(float *)(param_1 + 0x69c) = fVar2;
    zz_004beb8_(dVar3,param_1,2,0,0xc,0xffffffff,0xffffffff);
  }
  else {
    zz_004cd24_(param_1,2);
  }
  fVar2 = FLOAT_80437518;
  fVar1 = FLOAT_80437514;
  dVar3 = (double)FLOAT_80437510;
  *(float *)(param_1 + 0x44) =
       *(float *)(param_1 + 0x44) *
       (FLOAT_80437518 * (float)(dVar3 - (double)*(float *)(param_1 + 0x1dc8)) + FLOAT_80437514);
  *(float *)(param_1 + 0x48) =
       *(float *)(param_1 + 0x48) *
       (fVar2 * (float)(dVar3 - (double)*(float *)(param_1 + 0x1dc8)) + fVar1);
  zz_0067458_(dVar3,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1d0e) != '\0') {
    *(undefined1 *)(param_1 + 0x590) = 1;
    zz_006a750_(param_1,6);
  }
  return;
}



// ==== 80064548  FUN_80064548 ====

void FUN_80064548(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x7ca);
  if (cVar1 == '\x01') {
    cVar1 = *(char *)(param_1 + 0x7cb) + -1;
    *(char *)(param_1 + 0x7cb) = cVar1;
    if (cVar1 == '\0') {
      *(char *)(param_1 + 0x7ca) = *(char *)(param_1 + 0x7ca) + '\x01';
      *(undefined1 *)(param_1 + 0x7cb) = 2;
      zz_003f7d4_(param_1);
    }
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      *(char *)(param_1 + 0x7ca) = cVar1 + '\x01';
      *(undefined1 *)(param_1 + 0x7cb) = 2;
      *(undefined2 *)(param_1 + 0x272) = 0xffff;
    }
  }
  else if ((cVar1 < '\x03') &&
          (cVar1 = *(char *)(param_1 + 0x7cb) + -1, *(char *)(param_1 + 0x7cb) = cVar1,
          cVar1 == '\0')) {
    *(undefined1 *)(param_1 + 0x7c9) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffefff;
    *(char *)(param_1 + 0x7ca) = *(char *)(param_1 + 0x7ca) + '\x01';
    *(undefined2 *)(param_1 + 0x272) = 0;
    zz_0092dcc_(param_1,0);
    if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
      zz_006a7b4_(param_1,(int)*(char *)(param_1 + 1999));
      zz_006a7f4_(param_1,(int)*(char *)(param_1 + 0x7ce));
    }
    else {
      if ((*(uint *)(param_1 + 0x5e0) & 2) == 0) {
        *(undefined1 *)(param_1 + 0x73f) = 0;
        *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      }
      cVar1 = *(char *)(param_1 + 0x661);
      if (((cVar1 == '\x03') || ((byte)(cVar1 - 8U) < 2)) || (cVar1 == '\v')) {
        zz_006a474_(param_1);
      }
      else {
        zz_006a5a4_(param_1);
      }
    }
  }
  return;
}



// ==== 800646b0  FUN_800646b0 ====

void FUN_800646b0(int param_1)

{
  double dVar1;
  
  if (*(char *)(param_1 + 0x540) == '\0') {
    dVar1 = (double)FLOAT_804374e8;
    *(undefined1 *)(param_1 + 0x540) = 1;
    zz_004beb8_(dVar1,param_1,0xd,0,*(char *)(param_1 + 0x57c) + 0x1b,0xffffffff,0xffffffff);
  }
  else {
    zz_004cd24_(param_1,0xd);
  }
  return;
}



// ==== 80064710  FUN_80064710 ====

void FUN_80064710(int param_1)

{
  zz_0060c94_(param_1);
  zz_006a750_(param_1,0xd);
  *(float *)(param_1 + 0x80c) = FLOAT_804374ec;
  zz_00b2190_(param_1,0);
  return;
}



// ==== 8006475c  FUN_8006475c ====

void FUN_8006475c(int param_1)

{
  if (*(char *)(param_1 + 0x57e) == '\0') {
    zz_004cd24_(param_1,0xd);
  }
  return;
}



// ==== 8006478c  FUN_8006478c ====

void FUN_8006478c(int param_1)

{
  int iVar1;
  double dVar2;
  float local_18;
  float local_14;
  float local_10;
  
  zz_0060f78_(param_1);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  else {
    zz_0067458_((double)FLOAT_80437510,param_1,*(short *)(param_1 + 0x5ae));
    iVar1 = zz_00677b0_(param_1);
    if (iVar1 == 0) {
      *(undefined1 *)(param_1 + 0x7cc) = 0;
    }
    else {
      *(float *)(param_1 + 0x48) = FLOAT_804374ec;
      *(undefined1 *)(param_1 + 0x7cc) = 1;
    }
  }
  if ((*(uint *)(*(int *)(param_1 + 0x4b0) + 8) & 4) != 0) {
    zz_00b22f4_(param_1);
  }
  if (*(char *)(param_1 + 0x545) == '\0') {
    if ((*(char *)(param_1 + 0x57e) == '\x01') && (*(char *)(param_1 + 0x57d) != '\x02')) {
      dVar2 = zz_0045204_(*(short *)(param_1 + 0x5ae));
      local_18 = (float)dVar2;
      local_14 = FLOAT_804374ec;
      dVar2 = zz_0045238_(*(short *)(param_1 + 0x5ae));
      local_10 = (float)dVar2;
      gnt4_PSQUATScale_bl((double)(*(float *)(param_1 + 0x44) * *(float *)(param_1 + 0x568)),
                          &local_18,&local_18);
      gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),&local_18,&local_18);
      *(float *)(param_1 + 0x568) = FLOAT_804374ec;
      zz_006ab04_(param_1,&local_18,1);
    }
  }
  else {
    zz_006a750_(param_1,0xe);
  }
  return;
}



// ==== 800648bc  FUN_800648bc ====

void FUN_800648bc(int param_1)

{
  if (*(char *)(param_1 + 0x57e) == '\0') {
    zz_004cd24_(param_1,0xd);
  }
  else {
    zz_004cff4_(param_1,0xd);
  }
  return;
}



// ==== 800648f8  FUN_800648f8 ====

void FUN_800648f8(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_0061160_(param_1);
  if ((FLOAT_804374ec < *(float *)(param_1 + 0x44)) &&
     ((*(uint *)(*(int *)(param_1 + 0x4b0) + 8) & 4) != 0)) {
    zz_00b22f4_(param_1);
  }
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  else {
    zz_0067458_((double)FLOAT_80437510,param_1,*(short *)(param_1 + 0x5ae));
    iVar2 = zz_00677b0_(param_1);
    if (iVar2 == 0) {
      *(undefined1 *)(param_1 + 0x7cc) = 0;
      *(undefined1 *)(param_1 + 0x709) = 0;
    }
    else {
      *(float *)(param_1 + 0x48) = FLOAT_804374ec;
      if (*(char *)(param_1 + 0x545) == '\0') {
        *(undefined1 *)(param_1 + 0x7cc) = 1;
      }
    }
  }
  fVar1 = FLOAT_804374ec;
  if (*(char *)(param_1 + 0x1d0e) != '\0') {
    *(float *)(param_1 + 0x4c) = FLOAT_804374ec;
    *(float *)(param_1 + 0x44) = fVar1;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 800649d4  FUN_800649d4 ====

void FUN_800649d4(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
  *(undefined1 *)(param_1 + 0x7cc) = 1;
  *(undefined1 *)(param_1 + 0x5e6) = 0;
  *(undefined1 *)(param_1 + 0x656) = 1;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x20;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffdfff;
  zz_0066ac0_(param_1,1);
  *(undefined2 *)(param_1 + 0x550) = 0;
  iVar4 = zz_0046510_(*(ushort *)(param_1 + 0x5aa),0);
  *(undefined *)(param_1 + 0x57c) = (&DAT_80433850)[iVar4];
  iVar4 = zz_0046510_(*(ushort *)(param_1 + 0x734),2);
  *(char *)(param_1 + 0x57d) = (char)iVar4;
  fVar3 = FLOAT_804375b0;
  fVar2 = FLOAT_804374ec;
  *(float *)(param_1 + 0x50) = FLOAT_804374ec;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x56c) = fVar3;
  zz_00f036c_(param_1,0x1e);
  cVar1 = *(char *)(param_1 + 0x57c);
  iVar4 = *(int *)(param_1 + 0x4ac);
  if (cVar1 != '\x01') {
    if (cVar1 < '\x01') {
      if (-1 < cVar1) {
        *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(iVar4 + 0xf0);
        *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(iVar4 + 0xf4);
        *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(iVar4 + 0xf8);
        *(undefined4 *)(param_1 + 0x568) = *(undefined4 *)(iVar4 + 0xfc);
        if (*(char *)(*(int *)(param_1 + 0x4ac) + 0x41) != '\0') {
          *(undefined1 *)(param_1 + 0x709) = 5;
        }
        goto LAB_80064b70;
      }
    }
    else if (cVar1 < '\x03') {
      *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(iVar4 + 0x110);
      *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(iVar4 + 0x114);
      *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(iVar4 + 0x118);
      *(undefined4 *)(param_1 + 0x568) = *(undefined4 *)(iVar4 + 0x11c);
      if (*(char *)(*(int *)(param_1 + 0x4ac) + 0x41) != '\0') {
        *(undefined1 *)(param_1 + 0x709) = 3;
      }
      goto LAB_80064b70;
    }
  }
  *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(iVar4 + 0x100);
  *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(iVar4 + 0x104);
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(iVar4 + 0x108);
  *(undefined4 *)(param_1 + 0x568) = *(undefined4 *)(iVar4 + 0x10c);
  if (*(char *)(*(int *)(param_1 + 0x4ac) + 0x41) != '\0') {
    if (*(char *)(param_1 + 0x57c) == '\x01') {
      *(undefined1 *)(param_1 + 0x709) = 0x11;
    }
    else {
      *(undefined1 *)(param_1 + 0x709) = 9;
    }
  }
LAB_80064b70:
  *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x5b0) + -0x8000;
  zz_0065eb0_(param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  zz_006a750_(param_1,0x26);
  *(float *)(param_1 + 0x80c) = FLOAT_804374ec;
  zz_00b2190_(param_1,0);
  return;
}



// ==== 80064bc8  FUN_80064bc8 ====

void FUN_80064bc8(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  float fVar4;
  int iVar5;
  
  zz_0065eb0_(param_1);
  if (*(float *)(param_1 + 0x44) < *(float *)(param_1 + 0x38)) {
    *(float *)(param_1 + 0x4c) = FLOAT_804374ec;
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(param_1 + 0x38);
  }
  fVar1 = FLOAT_804374ec;
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    *(float *)(param_1 + 0x570) = fVar1;
  }
  zz_0067458_((double)FLOAT_80437510,param_1,*(short *)(param_1 + 0x5ae));
  fVar2 = FLOAT_804375b8;
  fVar4 = FLOAT_80437510;
  dVar3 = DOUBLE_804374f8;
  fVar1 = FLOAT_804375b8 * *(float *)(param_1 + 0x1dc8);
  *(short *)(param_1 + 0x1d64) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1d64) ^ 0x80000000) -
                           DOUBLE_804374f8) * (FLOAT_80437510 - fVar1) +
                   fVar1 * (float)((double)CONCAT44(0x43300000,
                                                    (int)*(short *)(&DAT_802d38e4 +
                                                                   *(char *)(param_1 + 0x57c) * 4) ^
                                                    0x80000000) - DOUBLE_804374f8));
  fVar2 = fVar2 * *(float *)(param_1 + 0x1dc8);
  *(short *)(param_1 + 0x1d68) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1d68) ^ 0x80000000) - dVar3
                           ) * (fVar4 - fVar2) +
                   fVar2 * (float)((double)CONCAT44(0x43300000,
                                                    (int)*(short *)(&DAT_802d38e6 +
                                                                   *(char *)(param_1 + 0x57c) * 4) ^
                                                    0x80000000) - dVar3));
  iVar5 = zz_00677b0_(param_1);
  if ((iVar5 != 0) && ((*(uint *)(*(int *)(param_1 + 0x4b0) + 8) & 4) != 0)) {
    zz_00b22f4_(param_1);
  }
  fVar1 = FLOAT_804374ec;
  if (*(float *)(param_1 + 0x56c) <= FLOAT_804374ec) {
    *(float *)(param_1 + 0x568) = *(float *)(param_1 + 0x568) - *(float *)(param_1 + 0x1dc8);
    if ((*(float *)(param_1 + 0x568) <= fVar1) ||
       ((*(uint *)(param_1 + 0x5b4) & *(uint *)(&DAT_802d38d4 + *(char *)(param_1 + 0x57d) * 4)) ==
        0)) {
      zz_006a750_(param_1,0x27);
    }
  }
  else {
    *(float *)(param_1 + 0x56c) = *(float *)(param_1 + 0x56c) - *(float *)(param_1 + 0x1dc8);
  }
  fVar1 = FLOAT_804374ec;
  *(float *)(param_1 + 0x570) = *(float *)(param_1 + 0x570) - *(float *)(param_1 + 0x1dc8);
  if (*(float *)(param_1 + 0x570) <= fVar1) {
    zz_0092dcc_(param_1,0);
    *(float *)(param_1 + 0x570) = FLOAT_804375a0;
  }
  return;
}



// ==== 80064de8  FUN_80064de8 ====

void FUN_80064de8(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_80437540;
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    *(float *)(param_1 + 0x56c) = fVar1;
    *(float *)(param_1 + 0x568) = fVar1;
    *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) / *(float *)(param_1 + 0x568);
    if (*(char *)(param_1 + 0x57c) != '\0') {
      *(undefined1 *)(param_1 + 0x709) = 0;
    }
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffffdf;
  }
  fVar1 = FLOAT_804374ec;
  *(float *)(param_1 + 0x568) = *(float *)(param_1 + 0x568) - *(float *)(param_1 + 0x1dc8);
  if (*(float *)(param_1 + 0x568) <= fVar1) {
    *(float *)(param_1 + 0x50) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
    *(undefined2 *)(param_1 + 0x80) = 0;
    *(undefined2 *)(param_1 + 0x7e) = 0;
    *(undefined2 *)(param_1 + 0x7c) = 0;
    zz_006a474_(param_1);
  }
  else {
    zz_0065eb0_(param_1);
    zz_0067458_((double)FLOAT_80437510,param_1,*(short *)(param_1 + 0x5ae));
    iVar2 = zz_00677b0_(param_1);
    if ((iVar2 != 0) && ((*(uint *)(*(int *)(param_1 + 0x4b0) + 8) & 4) != 0)) {
      zz_00b22f4_(param_1);
    }
  }
  return;
}



// ==== 80064ef0  FUN_80064ef0 ====

void FUN_80064ef0(int param_1)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    if (*(char *)(*(int *)(param_1 + 0x4ac) + 0x41) != '\0') {
      *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) | 5;
    }
    *(undefined1 *)(param_1 + 0x87) = 1;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x50;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffdfff;
    zz_0066ac0_(param_1,0);
    iVar2 = zz_0046510_(*(ushort *)(param_1 + 0x5aa),1);
    fVar1 = FLOAT_804374ec;
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + iVar2 * 4 + 0x18);
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
    *(float *)(param_1 + 0x50) = fVar1;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
    uVar3 = (uint)*(short *)(param_1 + 0x5aa);
    if (*(short *)(param_1 + 0x5aa) < 0) {
      uVar3 = -uVar3;
    }
    uVar4 = (uint)*(ushort *)(*(int *)(param_1 + 0x4b0) + 0xc0);
    zz_0066ec0_(param_1,(int)(((float)((double)CONCAT44(0x43300000,uVar3 ^ 0x80000000) -
                                      DOUBLE_804374f8) / FLOAT_804374f0) *
                              (float)((double)CONCAT44(0x43300000,
                                                       *(ushort *)(*(int *)(param_1 + 0x4b0) + 200)
                                                       - uVar4 ^ 0x80000000) - DOUBLE_804374f8) +
                             (float)((double)CONCAT44(0x43300000,uVar4) - DOUBLE_80437500)));
  }
  else {
    zz_0067458_((double)FLOAT_80437510,param_1,*(short *)(param_1 + 0x5ae));
    iVar2 = zz_0066f1c_(param_1);
    if (iVar2 != 0) {
      zz_006a750_(param_1,2);
    }
  }
  return;
}



// ==== 8006508c  FUN_8006508c ====

void FUN_8006508c(int param_1)

{
  float fVar1;
  double dVar2;
  
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    fVar1 = FLOAT_804374ec;
    *(undefined1 *)(param_1 + 0x87) = 1;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x50;
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x2c);
    *(float *)(param_1 + 0x4c) = fVar1;
    if (*(char *)(*(int *)(param_1 + 0x4ac) + 0x41) != '\0') {
      *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) | 5;
    }
  }
  zz_0066ac0_(param_1,0);
  zz_0066e40_(param_1,1);
  dVar2 = (double)FLOAT_80437510;
  *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  zz_0067458_(dVar2,param_1,*(short *)(param_1 + 0x5ae));
  return;
}



// ==== 8006513c  FUN_8006513c ====

void FUN_8006513c(int param_1)

{
  float fVar1;
  double dVar2;
  
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    fVar1 = FLOAT_804374ec;
    *(undefined1 *)(param_1 + 0x87) = 1;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x50;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(undefined1 *)(param_1 + 0x709) = 0;
  }
  else if (*(float *)(param_1 + 0x44) < FLOAT_80437510) {
    zz_006a474_(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
  }
  dVar2 = (double)FLOAT_80437510;
  *(float *)(param_1 + 0x44) =
       *(float *)(param_1 + 0x44) *
       (FLOAT_80437580 * (float)(dVar2 - (double)*(float *)(param_1 + 0x1dc8)) + FLOAT_8043757c);
  zz_0067458_(dVar2,param_1,*(short *)(param_1 + 0x5ae));
  *(short *)(param_1 + 0x1d64) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1d64) ^ 0x80000000) -
                           DOUBLE_804374f8) *
                   (FLOAT_80437588 * (FLOAT_80437510 - *(float *)(param_1 + 0x1dc8)) +
                   FLOAT_80437570));
  return;
}



// ==== 8006523c  FUN_8006523c ====

void FUN_8006523c(int param_1)

{
  char cVar1;
  int iVar2;
  double dVar3;
  
  cVar1 = *(char *)(param_1 + 0x540);
  if (cVar1 == '\x02') {
    dVar3 = (double)FLOAT_804374e8;
    *(undefined1 *)(param_1 + 0x540) = 3;
    zz_004beb8_(dVar3,param_1,0xd,0,2,0xffffffff,0xffffffff);
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0x540) = 1;
      cVar1 = *(char *)(param_1 + 0x547);
      if (cVar1 == '\x01') {
        if ((*(char *)(param_1 + 0x1cec) != '\0') || (*(char *)(param_1 + 0x1ced) != '\b')) {
          zz_004beb8_((double)FLOAT_804374e8,param_1,0xd,0,8,0xffffffff,0xffffffff);
        }
      }
      else if (cVar1 < '\x01') {
        if (-1 < cVar1) {
          zz_004beb8_((double)FLOAT_804374e8,param_1,0xd,0,0x1f,0xffffffff,0xffffffff);
        }
      }
      else if (cVar1 < '\x03') {
        zz_004beb8_((double)FLOAT_804374e8,param_1,0xd,0,2,0xffffffff,0xffffffff);
      }
    }
    else if (cVar1 < '\0') {
      return;
    }
    iVar2 = zz_004cd24_(param_1,0xd);
    if (iVar2 != 0) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    }
  }
  else if (cVar1 < '\x04') {
    zz_004cd24_(param_1,0xd);
  }
  return;
}



// ==== 80065394  FUN_80065394 ====

void FUN_80065394(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  fVar2 = FLOAT_804374ec;
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x02') {
    *(undefined1 *)(param_1 + 0x544) = 3;
    dVar4 = (double)FLOAT_804374e8;
    *(float *)(param_1 + 0x50) = fVar2;
    *(float *)(param_1 + 0x48) = fVar2;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x44) = fVar2;
    *(undefined2 *)(param_1 + 0x80) = 0;
    *(undefined2 *)(param_1 + 0x7e) = 0;
    *(undefined2 *)(param_1 + 0x7c) = 0;
    zz_004beb8_(dVar4,param_1,2,0,2,0xffffffff,0xffffffff);
    return;
  }
  if ('\x01' < cVar1) {
    if (cVar1 != '\x04') {
      if ('\x03' < cVar1) {
        return;
      }
      iVar3 = zz_004cd24_(param_1,2);
      if (iVar3 == 0) {
        return;
      }
      *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
    }
    zz_006a750_(param_1,5);
    return;
  }
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    fVar2 = FLOAT_804374ec;
    *(undefined1 *)(param_1 + 0x87) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffdfaf;
    *(float *)(param_1 + 0x50) = fVar2;
    *(float *)(param_1 + 0x48) = fVar2;
    cVar1 = *(char *)(param_1 + 0x7ce);
    if (cVar1 == '\x03') {
      *(undefined1 *)(param_1 + 0x547) = 3;
    }
    else {
      if (cVar1 < '\x03') {
        if ('\0' < cVar1) {
          *(undefined1 *)(param_1 + 0x547) = 0;
          zz_004beb8_((double)FLOAT_804374e8,param_1,2,0,0x1f,0xffffffff,0xffffffff);
          goto LAB_800654fc;
        }
      }
      else if (cVar1 == '\a') {
        *(undefined1 *)(param_1 + 0x547) = 1;
        if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\b')) {
          zz_004beb8_((double)FLOAT_804374e8,param_1,2,0,8,0xffffffff,0xffffffff);
        }
        goto LAB_800654fc;
      }
      *(undefined1 *)(param_1 + 0x544) = 3;
      fVar2 = FLOAT_804374ec;
      *(undefined1 *)(param_1 + 0x547) = 2;
      dVar4 = (double)FLOAT_804374e8;
      *(float *)(param_1 + 0x50) = fVar2;
      *(float *)(param_1 + 0x48) = fVar2;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(float *)(param_1 + 0x44) = fVar2;
      *(undefined2 *)(param_1 + 0x80) = 0;
      *(undefined2 *)(param_1 + 0x7e) = 0;
      *(undefined2 *)(param_1 + 0x7c) = 0;
      zz_004beb8_(dVar4,param_1,2,0,2,0xffffffff,0xffffffff);
    }
  }
  else if (cVar1 < '\0') {
    return;
  }
LAB_800654fc:
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  iVar3 = zz_004cd24_(param_1,2);
  if (iVar3 != 0) {
    if ((*(uint *)(param_1 + 0x5b4) & 0x100) == 0) {
      zz_006a474_(param_1);
    }
    else {
      *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
    }
  }
  return;
}



// ==== 800655cc  FUN_800655cc ====

void FUN_800655cc(int param_1)

{
  char cVar1;
  float fVar2;
  short sVar3;
  
  *(undefined1 *)(param_1 + 0x719) = 1;
  if (*(char *)(param_1 + 0x4a1) == '\0') {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a474_(param_1);
    }
    else {
      zz_006a5a4_(param_1);
    }
  }
  else {
    cVar1 = *(char *)(param_1 + 0x544);
    if (cVar1 == '\x02') {
      sVar3 = *(short *)(param_1 + 0x550) + -1;
      *(short *)(param_1 + 0x550) = sVar3;
      if (sVar3 == 0) {
        *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
        *(undefined1 *)(param_1 + 0x4a1) = 2;
      }
    }
    else if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        *(undefined1 *)(param_1 + 0x544) = 1;
        *(undefined4 *)(param_1 + 0x754) = 0;
        *(undefined2 *)(param_1 + 0x272) = 0xc3;
        *(undefined1 *)(param_1 + 0x4a1) = 1;
        *(undefined2 *)(param_1 + 0x550) = 0x3c;
        *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffdfff;
        zz_00666c8_(param_1,(float *)(*(int *)(param_1 + 0x4a4) + 0x20));
        zz_0066ec0_(param_1,0x1e);
        zz_004beb8_((double)FLOAT_804374e8,param_1,0xf,0,0,0xffffffff,0xffffffff);
      }
      else if (-1 < cVar1) {
        zz_004cd24_(param_1,0xf);
        zz_0066f1c_(param_1);
        sVar3 = *(short *)(param_1 + 0x550) + -1;
        *(short *)(param_1 + 0x550) = sVar3;
        fVar2 = FLOAT_804374ec;
        if (sVar3 == 0) {
          *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
          *(float *)(param_1 + 0x50) = fVar2;
          *(float *)(param_1 + 0x4c) = fVar2;
          *(undefined2 *)(param_1 + 0x550) = 0x28;
          zz_00107a0_(param_1,6);
        }
      }
    }
    else if (cVar1 == '\x04') {
      sVar3 = *(short *)(param_1 + 0x550) + -1;
      *(short *)(param_1 + 0x550) = sVar3;
      if (sVar3 == 0) {
        zz_006a750_(param_1,0x1a);
      }
    }
    else if ((cVar1 < '\x04') && (*(char *)(param_1 + 0x4a1) == '\x03')) {
      *(char *)(param_1 + 0x544) = cVar1 + '\x01';
      *(undefined2 *)(param_1 + 0x550) = 0x28;
    }
  }
  return;
}



// ==== 80065780  FUN_80065780 ====

void FUN_80065780(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  short sVar5;
  double dVar6;
  
  *(undefined1 *)(param_1 + 0x719) = 1;
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x02') {
    if (*(char *)(param_1 + 0x4a1) == '\x06') {
      *(undefined1 *)(param_1 + 0x544) = 3;
      *(undefined2 *)(param_1 + 0x550) = 0x1e;
      *(undefined2 *)(param_1 + 0x552) = 0;
      if (*(char *)(param_1 + 0x4a8) == '\x01') {
        *(float *)(param_1 + 0x48) =
             -((FLOAT_804375b8 * *(float *)(*(int *)(param_1 + 0x4a4) + 0x668)) / FLOAT_80437558);
      }
      else {
        *(float *)(param_1 + 0x48) = FLOAT_804374ec;
      }
      zz_0066ec0_(param_1,0x14);
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0x544) = 1;
      fVar2 = FLOAT_804374ec;
      *(undefined2 *)(param_1 + 0x272) = 0xffff;
      fVar3 = FLOAT_8043758c;
      *(undefined1 *)(param_1 + 0x4a1) = 4;
      fVar4 = FLOAT_80437590;
      *(float *)(param_1 + 0x50) = fVar2;
      dVar6 = (double)FLOAT_804374e8;
      *(float *)(param_1 + 0x48) = fVar2;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(float *)(param_1 + 0x44) = fVar2;
      *(undefined2 *)(param_1 + 0x80) = 0;
      *(undefined2 *)(param_1 + 0x7e) = 0;
      *(undefined2 *)(param_1 + 0x7c) = 0;
      *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x8d4);
      *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x8e4);
      *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x8f4);
      *(float *)(param_1 + 0x44) = fVar3;
      *(undefined2 *)(param_1 + 0x550) = 0;
      *(float *)(param_1 + 0x568) = fVar4;
      *(undefined1 *)(param_1 + 0x579) = 7;
      zz_004beb8_(dVar6,param_1,0xf,0,4,0xffffffff,0xffffffff);
    }
    else if (-1 < cVar1) {
      zz_004cd24_(param_1,0xf);
      sVar5 = *(short *)(param_1 + 0x550) + 1;
      *(short *)(param_1 + 0x550) = sVar5;
      if (sVar5 < 2) {
        gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),
                         (float *)(param_1 + 0x20));
      }
      else {
        zz_006c440_((double)*(float *)(param_1 + 0x568),param_1,(float *)(param_1 + 0x7a4));
        fVar2 = FLOAT_80437590;
        *(undefined2 *)(param_1 + 0x550) = 0;
        fVar3 = FLOAT_80437594;
        *(float *)(param_1 + 0x568) = *(float *)(param_1 + 0x568) + fVar2;
        if (fVar3 < *(float *)(param_1 + 0x568)) {
          *(float *)(param_1 + 0x568) = fVar3;
        }
        fVar2 = FLOAT_80437540;
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) + FLOAT_804374e8;
        if (*(float *)(param_1 + 0x44) < fVar2) {
          *(float *)(param_1 + 0x44) = fVar2;
        }
      }
      dVar6 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x7a4));
      fVar2 = FLOAT_804374ec;
      if (dVar6 <= (double)FLOAT_80437598) {
        *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
        *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 4;
        *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x7a4);
        *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x7a8);
        *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x7ac);
        *(undefined1 *)(param_1 + 0x4a1) = 5;
        *(float *)(param_1 + 0x50) = fVar2;
        *(float *)(param_1 + 0x48) = fVar2;
        *(float *)(param_1 + 0x4c) = fVar2;
        *(float *)(param_1 + 0x44) = fVar2;
        *(undefined2 *)(param_1 + 0x80) = 0;
        *(undefined2 *)(param_1 + 0x7e) = 0;
        *(undefined2 *)(param_1 + 0x7c) = 0;
      }
    }
  }
  else if (cVar1 == '\x04') {
    sVar5 = *(short *)(param_1 + 0x550) + -1;
    *(short *)(param_1 + 0x550) = sVar5;
    if (sVar5 == 0) {
      *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
      *(undefined1 *)(param_1 + 0x4a1) = 7;
    }
  }
  else if ((cVar1 < '\x04') && (zz_004cd24_(param_1,0xf), *(short *)(param_1 + 0x550) != 0)) {
    zz_0067458_((double)FLOAT_80437510,param_1,*(short *)(param_1 + 0x5ae));
    zz_0066f1c_(param_1);
    zz_00677b0_(param_1);
    sVar5 = *(short *)(param_1 + 0x550) + -1;
    *(short *)(param_1 + 0x550) = sVar5;
    if (sVar5 < 1) {
      if (*(char *)(param_1 + 0x4a8) == '\x02') {
        zz_00f6654_(param_1);
        zz_00f036c_(param_1,0x9b);
      }
      fVar2 = FLOAT_804374ec;
      *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
      *(undefined2 *)(param_1 + 0x550) = 0x1e;
      *(float *)(param_1 + 0x38) = fVar2;
      *(float *)(param_1 + 0x3c) = fVar2;
      *(float *)(param_1 + 0x40) = fVar2;
      *(float *)(param_1 + 0x50) = fVar2;
      *(float *)(param_1 + 0x48) = fVar2;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(float *)(param_1 + 0x44) = fVar2;
      *(undefined2 *)(param_1 + 0x80) = 0;
      *(undefined2 *)(param_1 + 0x7e) = 0;
      *(undefined2 *)(param_1 + 0x7c) = 0;
    }
  }
  if (*(char *)(*(int *)(param_1 + 0x4a4) + 0x4a1) == '\0') {
    dVar6 = (double)FLOAT_804374ec;
    *(undefined1 *)(param_1 + 0x579) = *(undefined1 *)(*(int *)(param_1 + 0x4b0) + 2);
    *(undefined2 *)(param_1 + 0x272) = 0;
    zz_004beb8_(dVar6,param_1,0xf,0,0xd,0,0);
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 80065b14  FUN_80065b14 ====

void FUN_80065b14(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  short sVar4;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  *(undefined1 *)(param_1 + 0x719) = 1;
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x01') {
    iVar3 = zz_004cd24_(param_1,0xf);
    if ((iVar3 != 0) ||
       (sVar4 = *(short *)(param_1 + 0x550) + -1, *(short *)(param_1 + 0x550) = sVar4, sVar4 < 1)) {
      *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
      zz_0010784_(param_1);
      zz_0010784_(*(int *)(param_1 + 0x4a4));
      zz_008b1e8_();
      zz_004beb8_((double)FLOAT_804374e8,param_1,0xf,0,0xd,0xffffffff,0xffffffff);
      zz_0067458_((double)FLOAT_80437510,param_1,*(short *)(param_1 + 0x5ae));
      zz_00677b0_(param_1);
      zz_00def38_(param_1);
    }
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      *(char *)(param_1 + 0x544) = cVar1 + '\x01';
      fVar2 = FLOAT_804374ec;
      *(undefined4 *)(param_1 + 0x754) = 0;
      *(undefined2 *)(param_1 + 0x550) = 0x78;
      *(float *)(param_1 + 0x50) = fVar2;
      *(float *)(param_1 + 0x48) = fVar2;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(float *)(param_1 + 0x44) = fVar2;
      *(undefined2 *)(param_1 + 0x80) = 0;
      *(undefined2 *)(param_1 + 0x7e) = 0;
      *(undefined2 *)(param_1 + 0x7c) = 0;
      zz_00107a0_(param_1,0x1b);
      zz_00107a0_(*(int *)(param_1 + 0x4a4),0x1b);
      zz_004beb8_((double)FLOAT_804374e8,param_1,0xf,3,2,0xffffffff,0xffffffff);
      local_18 = *(undefined4 *)(param_1 + 0x910);
      local_14 = *(undefined4 *)(param_1 + 0x920);
      local_10 = *(undefined4 *)(param_1 + 0x930);
      zz_00e7018_(param_1,&local_18);
    }
  }
  else if (cVar1 < '\x03') {
    zz_0067458_((double)FLOAT_80437510,param_1,*(short *)(param_1 + 0x5ae));
    zz_00677b0_(param_1);
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 80065cb4  FUN_80065cb4 ====

void FUN_80065cb4(int param_1)

{
  if (*(int *)(param_1 + 0x4e4) == 0) {
    zz_006a838_(param_1);
  }
  else {
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffdfff;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 3;
    *(undefined1 *)(param_1 + 0x57b) = 0;
    *(undefined1 *)(param_1 + 0x57a) = 0;
    (**(code **)(param_1 + 0x4e4))();
  }
  return;
}



// ==== 80065d14  FUN_80065d14 ====

void FUN_80065d14(int param_1)

{
  double dVar1;
  
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffdfff;
    if ((((int)(char)PTR_DAT_80433934[0x1f] & 1 << (int)*(char *)(param_1 + 0x88)) == 0) ||
       ((1 << (*(byte *)(param_1 + 0x3e9) & 0x1f) &
        *(uint *)(*(char *)(param_1 + 1000) * 8 + -0x7fd22b00 +
                 (*(byte *)(param_1 + 0x3e9) >> 5 & 1) * 4)) == 0)) {
      zz_004beb8_((double)FLOAT_804374e8,param_1,0xf,0,0,0xffffffff,0xffffffff);
    }
    else {
      dVar1 = (double)FLOAT_804374e8;
      *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
      zz_004beb8_(dVar1,param_1,0xf,0,0x28,0xffffffff,0xffffffff);
    }
  }
  else {
    zz_004cd24_(param_1,0xf);
  }
  return;
}



// ==== 80065dfc  FUN_80065dfc ====

void FUN_80065dfc(int param_1)

{
  (**(code **)(param_1 + 0x4b4))();
  return;
}



// ==== 80065e24  FUN_80065e24 ====

void FUN_80065e24(int param_1)

{
  zz_005c694_(param_1);
  return;
}



// ==== 80065e44  FUN_80065e44 ====

void FUN_80065e44(int param_1)

{
  zz_005bccc_(param_1);
  return;
}



// ==== 80065e64  FUN_80065e64 ====

void FUN_80065e64(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_804374ec;
  *(float *)(param_1 + 0x69c) = FLOAT_804374ec;
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  if (*(char *)(param_1 + 0x661) == '\x06') {
    zz_006a750_(param_1,0);
  }
  else {
    zz_006a750_(param_1,7);
  }
  return;
}



// ==== 80065eb0  zz_0065eb0_ ====

void zz_0065eb0_(int param_1)

{
  char cVar1;
  float fVar2;
  short sVar3;
  int iVar4;
  undefined8 local_18;
  
  iVar4 = *(int *)(param_1 + 0x4ac);
  if (*(char *)(param_1 + 0x547) != '\0') goto LAB_80065ff4;
  cVar1 = *(char *)(param_1 + 0x57d);
  if (cVar1 != '\x01') {
    if (cVar1 < '\x01') {
      if (-1 < cVar1) {
        if (*(float *)(param_1 + 0x75c) < *(float *)(iVar4 + 0x120)) {
          *(undefined1 *)(param_1 + 0x547) = 1;
        }
        else {
          *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x5b0) + -0x8000;
        }
        goto LAB_80065ff4;
      }
    }
    else if (cVar1 < '\x03') {
      *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5b0);
      goto LAB_80065ff4;
    }
  }
  if (*(float *)(iVar4 + 0x120) <= *(float *)(param_1 + 0x75c)) {
    if (*(float *)(iVar4 + 0x124) <= *(float *)(param_1 + 0x75c)) {
      sVar3 = 0x4000 - (short)(int)(FLOAT_804375bc * *(float *)(iVar4 + 0x130));
    }
    else {
      sVar3 = 0x4000 - (short)(int)(FLOAT_804375bc * *(float *)(iVar4 + 300));
    }
  }
  else {
    sVar3 = 0x4000 - (short)(int)(FLOAT_804375bc * (*(float *)(iVar4 + 300) - FLOAT_804375c0));
  }
  if (cVar1 == '\x01') {
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x5b0) + sVar3 + -0x8000;
  }
  else {
    *(short *)(param_1 + 0x5ae) = (*(short *)(param_1 + 0x5b0) + -0x8000) - sVar3;
  }
LAB_80065ff4:
  if ((*(uint *)(*(int *)(param_1 + 0x4b0) + 8) & 0x20) == 0) {
    *(short *)(param_1 + 0x5ac) = *(short *)(param_1 + 0x5ae) + *(char *)(param_1 + 0x57c) * -0x4000
    ;
  }
  else {
    *(short *)(param_1 + 0x5ac) = *(short *)(param_1 + 0x5b0) + -0x8000;
    if (*(char *)(param_1 + 0x57c) != '\x02') {
      *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(param_1 + 0x5ac);
    }
  }
  fVar2 = FLOAT_804374ec;
  *(short *)(param_1 + 0x5aa) = *(short *)(param_1 + 0x5ac) - *(short *)(param_1 + 0x72);
  if (fVar2 < *(float *)(param_1 + 0x44)) {
    local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x5aa)) ^ 0x80000000);
    sVar3 = (short)(int)(FLOAT_804375b8 * (float)(local_18 - DOUBLE_804374f8));
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + sVar3;
    *(short *)(param_1 + 0x5aa) = *(short *)(param_1 + 0x5aa) - sVar3;
  }
  return;
}



// ==== 800660b8  zz_00660b8_ ====

void zz_00660b8_(int param_1,byte param_2)

{
  *(byte *)(param_1 + 0x57b) = *(byte *)(param_1 + 0x57b) | param_2;
  return;
}



// ==== 800660c8  zz_00660c8_ ====

void zz_00660c8_(int param_1,byte param_2)

{
  *(byte *)(param_1 + 0x57a) = *(byte *)(param_1 + 0x57a) & ~param_2;
  *(byte *)(param_1 + 0x57b) = *(byte *)(param_1 + 0x57b) & ~param_2;
  return;
}



// ==== 800660e8  zz_00660e8_ ====

undefined4 zz_00660e8_(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (((*(char *)(param_2 + 0x662) == '\0') &&
      (*(short *)(param_2 + 1000) == *(short *)(param_1 + 0x94))) ||
     ('\x01' < *(char *)(param_1 + 0x18))) {
    uVar1 = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
    zz_0089444_(param_1);
    zz_008aff0_(param_1);
    uVar1 = 1;
  }
  return uVar1;
}



// ==== 80066168  zz_0066168_ ====

int zz_0066168_(char *param_1,int param_2)

{
  return (int)*(short *)((&PTR_DAT_802dd3b4)[*param_1] + (param_2 + (uint)(byte)param_1[1] * 6) * 2)
  ;
}



// ==== 80066198  zz_0066198_ ====

int zz_0066198_(char *param_1,int param_2,int param_3)

{
  return (int)*(short *)((&PTR_DAT_802f2988)[*param_1] +
                        (param_3 +
                        (uint)(byte)param_1[1] * 0x14 + (int)(char)(&DAT_804339e8)[param_2]) * 0x12)
  ;
}



// ==== 800661d8  zz_00661d8_ ====

int zz_00661d8_(char *param_1)

{
  return (int)*(short *)((&PTR_DAT_802f2c18)[*param_1] + (uint)(byte)param_1[1] * 2);
}



// ==== 80066200  zz_0066200_ ====

uint zz_0066200_(int param_1)

{
  uint uVar1;
  int iVar2;
  undefined **ppuVar3;
  byte *pbVar4;
  int iVar5;
  uint uVar6;
  
  ppuVar3 = &PTR_DAT_802f2c18;
  iVar5 = 0;
  pbVar4 = &DAT_802c3460;
  do {
    uVar6 = 0;
    iVar2 = 0;
    for (uVar1 = (uint)*pbVar4; uVar1 != 0; uVar1 = uVar1 - 1) {
      if (param_1 == *(short *)(*ppuVar3 + iVar2)) {
        return iVar5 << 8 | uVar6;
      }
      iVar2 = iVar2 + 2;
      uVar6 = uVar6 + 1;
    }
    iVar5 = iVar5 + 1;
    pbVar4 = pbVar4 + 1;
    ppuVar3 = ppuVar3 + 1;
  } while (iVar5 < 0x10);
  return 0xffffffff;
}



// ==== 80066270  zz_0066270_ ====

undefined4 zz_0066270_(char *param_1)

{
  return *(undefined4 *)((&PTR_PTR_803510d8)[*param_1] + (uint)(byte)param_1[1] * 4);
}



// ==== 80066298  zz_0066298_ ====

int zz_0066298_(char *param_1)

{
  return (int)*(short *)((&PTR_DAT_802f2e28)[*param_1] + (uint)(byte)param_1[1] * 2);
}



// ==== 800662c0  zz_00662c0_ ====

int zz_00662c0_(char *param_1,int param_2)

{
  return (int)*(short *)((&PTR_DAT_802f390c)[*param_1] + (param_2 + (uint)(byte)param_1[1] * 6) * 2)
  ;
}



// ==== 800662f0  zz_00662f0_ ====

int zz_00662f0_(char *param_1,uint param_2,int param_3)

{
  uint uVar1;
  
  if (param_3 < 9) {
    uVar1 = (uint)*(short *)((char)(&PTR_DAT_802f3a18)[*param_1][(byte)param_1[1]] * 0x12 +
                             -0x7fd0c5a8 + param_3 * 2);
    return ((int)param_2 >> 0x1f) + ((uint)(uVar1 <= param_2) - ((int)uVar1 >> 0x1f));
  }
  return 0;
}



// ==== 80066350  zz_0066350_ ====

void zz_0066350_(uint param_1)

{
  if ((param_1 & 1) != 0) {
    *(undefined1 *)(DAT_803c4e84 + 0x488) = 3;
  }
  if ((param_1 & 2) != 0) {
    *(undefined1 *)(DAT_803c4e88 + 0x488) = 3;
  }
  if ((param_1 & 4) != 0) {
    *(undefined1 *)(DAT_803c4e8c + 0x488) = 3;
  }
  if ((param_1 & 8) != 0) {
    *(undefined1 *)(DAT_803c4e90 + 0x488) = 3;
  }
  if ((param_1 & 0x10) != 0) {
    *(undefined1 *)(DAT_803c4e94 + 0x488) = 3;
  }
  if ((param_1 & 0x20) == 0) {
    return;
  }
  *(undefined1 *)(DAT_803c4e98 + 0x488) = 3;
  return;
}



// ==== 80066408  zz_0066408_ ====

void zz_0066408_(int param_1,int param_2,float *param_3,float *param_4)

{
  if (param_2 < 0) {
    param_2 = (int)*(char *)(*(int *)(param_1 + 0x4b0) + 0x10);
  }
  zz_004516c_((float *)(param_1 + param_2 * 0x30 + 0x8d4),param_3,param_4);
  return;
}



// ==== 80066454  zz_0066454_ ====

void zz_0066454_(int param_1,int param_2,float *param_3,float *param_4)

{
  if (param_2 < 0) {
    param_2 = (int)*(char *)(*(int *)(param_1 + 0x4b0) + 0x10);
  }
  zz_00451b8_((float *)(param_1 + param_2 * 0x30 + 0x8d4),param_3,param_4);
  return;
}



// ==== 800664a0  zz_00664a0_ ====

void zz_00664a0_(int param_1,int param_2)

{
  if (0 < *(short *)(param_1 + 0x736)) {
    *(short *)(param_1 + 0x736) =
         (short)(int)-((float)((double)CONCAT44(0x43300000,
                                                (int)*(short *)(*(int *)(param_1 + 0x4ac) +
                                                                param_2 * 2 + 10) ^ 0x80000000) -
                              DOUBLE_804375c8) * *(float *)(param_1 + 0x5f4) -
                      (float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x736) ^ 0x80000000) -
                             DOUBLE_804375c8));
    *(undefined2 *)(param_1 + 0x73a) = *(undefined2 *)(*(int *)(param_1 + 0x4ac) + 6);
    if (*(short *)(param_1 + 0x736) < 0) {
      *(undefined2 *)(param_1 + 0x736) = 0;
    }
  }
  return;
}



// ==== 80066530  zz_0066530_ ====

void zz_0066530_(int param_1,int param_2)

{
  float fVar1;
  
  if (param_2 == 0x2c) {
    *(undefined1 *)(param_1 + 0x5e4) = 0x2c;
    fVar1 = FLOAT_804375d0;
    *(undefined1 *)(param_1 + 0x87) = 0;
    *(float *)(param_1 + 0x69c) = fVar1;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff3f;
    return;
  }
  *(undefined1 *)(param_1 + 0x5e4) = 0x2d;
  *(undefined1 *)(param_1 + 0x87) = 1;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
  return;
}



// ==== 80066580  zz_0066580_ ====

int zz_0066580_(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x508) == 0) {
    iVar1 = (int)*(short *)(param_1 + 0x72);
  }
  else {
    iVar1 = FUN_800452a0((double)(*(float *)(param_1 + 0x50c) - *(float *)(param_1 + 0x20)),
                         (double)(*(float *)(param_1 + 0x514) - *(float *)(param_1 + 0x28)));
  }
  return iVar1;
}



// ==== 800665cc  zz_00665cc_ ====

void zz_00665cc_(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0xcc);
  if (iVar1 != 0) {
    if (*(char *)(iVar1 + 0x83) != '\0') {
      return;
    }
    if ((*(byte *)(iVar1 + 0x5e6) & *(byte *)(param_1 + 0x3e5)) != 0) {
      return;
    }
  }
  *(undefined4 *)(param_1 + 0xcc) = 0;
  *(undefined4 *)(param_1 + 200) = 0;
  return;
}



// ==== 8006660c  zz_006660c_ ====

void zz_006660c_(int param_1)

{
  int iVar1;
  uint uVar2;
  float local_18 [2];
  float local_10;
  
  iVar1 = *(int *)(param_1 + 0xcc);
  if (iVar1 != 0) {
    if (*(char *)(iVar1 + 0x83) == '\0') {
      uVar2 = (uint)(char)(*(byte *)(iVar1 + 0x5e6) & *(byte *)(param_1 + 0x3e5));
      uVar2 = (-uVar2 | uVar2) >> 0x1f;
    }
    else {
      uVar2 = 1;
    }
    if (uVar2 != 0) {
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),(float *)(param_1 + 0x20),local_18);
      iVar1 = FUN_800452a0((double)local_18[0],(double)local_10);
      *(short *)(param_1 + 0x5ac) = (short)iVar1;
      *(short *)(param_1 + 0x5aa) = *(short *)(param_1 + 0x5ac) - *(short *)(param_1 + 0x72);
      return;
    }
  }
  *(undefined4 *)(param_1 + 0xcc) = 0;
  *(undefined4 *)(param_1 + 200) = 0;
  *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  *(undefined2 *)(param_1 + 0x5aa) = 0;
  return;
}



// ==== 800666c8  zz_00666c8_ ====

void zz_00666c8_(int param_1,float *param_2)

{
  int iVar1;
  float local_18 [2];
  float local_10;
  
  gnt4_PSVECSubtract_bl(param_2,(float *)(param_1 + 0x20),local_18);
  iVar1 = FUN_800452a0((double)local_18[0],(double)local_10);
  *(short *)(param_1 + 0x5ac) = (short)iVar1;
  *(short *)(param_1 + 0x5aa) = *(short *)(param_1 + 0x5ac) - *(short *)(param_1 + 0x72);
  *(undefined4 *)(param_1 + 0xcc) = 0;
  *(undefined4 *)(param_1 + 200) = 0;
  return;
}



// ==== 8006672c  zz_006672c_ ====

int zz_006672c_(int param_1)

{
  int iVar1;
  float local_18 [2];
  float local_10;
  
  iVar1 = *(int *)(param_1 + 0xcc);
  if ((iVar1 != 0) &&
     ((*(char *)(iVar1 + 0x83) != '\0' ||
      ((*(byte *)(iVar1 + 0x5e6) & *(byte *)(param_1 + 0x3e5)) != 0)))) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),(float *)(param_1 + 0x20),local_18);
    iVar1 = FUN_800452a0((double)local_18[0],(double)local_10);
    return iVar1;
  }
  return (int)*(short *)(param_1 + 0x72);
}



// ==== 800667a0  FUN_800667a0 ====

/* WARNING: Removing unreachable block (ram,0x80066820) */
/* WARNING: Removing unreachable block (ram,0x800667b0) */

int FUN_800667a0(int param_1)

{
  int iVar1;
  double dVar2;
  double in_f31;
  double dVar3;
  double in_ps31_1;
  float fStack_28;
  float local_24;
  float local_8;
  float fStack_4;
  
  local_8 = (float)in_f31;
  fStack_4 = (float)in_ps31_1;
  iVar1 = *(int *)(param_1 + 0xcc);
  if ((iVar1 == 0) ||
     ((*(char *)(iVar1 + 0x83) == '\0' &&
      ((*(byte *)(iVar1 + 0x5e6) & *(byte *)(param_1 + 0x3e5)) == 0)))) {
    iVar1 = (int)*(short *)(param_1 + 0x70);
  }
  else {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),(float *)(param_1 + 0x20),&fStack_28);
    dVar3 = (double)local_24;
    local_24 = FLOAT_804375d0;
    dVar2 = gnt4_PSVECMag_bl(&fStack_28);
    iVar1 = FUN_800452a0(dVar3,dVar2);
  }
  return iVar1;
}



// ==== 80066838  FUN_80066838 ====

/* WARNING: Removing unreachable block (ram,0x800668b4) */
/* WARNING: Removing unreachable block (ram,0x80066848) */

uint FUN_80066838(double param_1,int param_2)

{
  uint uVar1;
  double dVar2;
  double in_f31;
  double dVar3;
  double in_ps31_1;
  float fStack_28;
  float local_24;
  float local_8;
  float fStack_4;
  
  local_8 = (float)in_f31;
  fStack_4 = (float)in_ps31_1;
  if (*(int *)(param_2 + 0xcc) == 0) {
    uVar1 = 0xffffffff;
  }
  else if ((*(byte *)(param_2 + 0x1dd) & 0x80) == 0) {
    dVar3 = (double)(float)(param_1 * (double)*(float *)(param_2 + 0xb4));
    gnt4_PSVECSubtract_bl((float *)(param_2 + 0x518),(float *)(param_2 + 0x20),&fStack_28);
    local_24 = FLOAT_804375d0;
    dVar2 = gnt4_PSVECMag_bl(&fStack_28);
    uVar1 = countLeadingZeros((uint)(dVar3 < dVar2));
    uVar1 = uVar1 >> 5;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



// ==== 800668cc  FUN_800668cc ====

/* WARNING: Removing unreachable block (ram,0x80066940) */
/* WARNING: Removing unreachable block (ram,0x800668dc) */

uint FUN_800668cc(double param_1,int param_2)

{
  uint uVar1;
  double dVar2;
  double in_f31;
  double dVar3;
  double in_ps31_1;
  float afStack_28 [8];
  float local_8;
  float fStack_4;
  
  local_8 = (float)in_f31;
  fStack_4 = (float)in_ps31_1;
  if (*(int *)(param_2 + 0xcc) == 0) {
    uVar1 = 0xffffffff;
  }
  else if ((*(byte *)(param_2 + 0x1dd) & 0x80) == 0) {
    dVar3 = (double)(float)(param_1 * (double)*(float *)(param_2 + 0xb4));
    gnt4_PSVECSubtract_bl((float *)(param_2 + 0x518),(float *)(param_2 + 0x20),afStack_28);
    dVar2 = gnt4_PSVECMag_bl(afStack_28);
    uVar1 = countLeadingZeros((uint)(dVar3 < dVar2));
    uVar1 = uVar1 >> 5;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}



// ==== 80066958  FUN_80066958 ====

double FUN_80066958(int param_1)

{
  double dVar1;
  float afStack_18 [6];
  
  if (*(int *)(param_1 + 0xcc) == 0) {
    dVar1 = (double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
  }
  else {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),(float *)(param_1 + 0x20),afStack_18);
    dVar1 = gnt4_PSVECMag_bl(afStack_18);
  }
  return dVar1;
}



// ==== 800669d0  FUN_800669d0 ====

void FUN_800669d0(int param_1,uint param_2)

{
  FUN_80066a30(param_1,param_2,
               (short)(int)((float)((double)CONCAT44(0x43300000,
                                                     (int)*(short *)(*(int *)(param_1 + 0x4ac) +
                                                                     (param_2 & 0xf) * 2 + 0xac) ^
                                                     0x80000000) - DOUBLE_804375c8) *
                           *(float *)(param_1 + 0x1dc8)));
  return;
}



// ==== 80066a30  FUN_80066a30 ====

undefined4 FUN_80066a30(int param_1,uint param_2,short param_3)

{
  int iVar1;
  short sVar2;
  
  sVar2 = *(short *)(param_1 + 0x5aa);
  iVar1 = (int)sVar2;
  if (sVar2 < 0) {
    iVar1 = -iVar1;
  }
  if (param_3 < iVar1) {
    if (sVar2 < 0) {
      param_3 = -param_3;
    }
    sVar2 = *(short *)(param_1 + 0x72) + param_3;
    *(short *)(param_1 + 0x5aa) = *(short *)(param_1 + 0x5aa) - param_3;
    if ((param_2 & 0x40) != 0) {
      *(short *)(param_1 + 0x5ae) = sVar2;
    }
    if ((param_2 & 0x80) != 0) {
      *(short *)(param_1 + 0x72) = sVar2;
    }
    return 0;
  }
  *(undefined2 *)(param_1 + 0x5aa) = 0;
  sVar2 = *(short *)(param_1 + 0x72) + sVar2;
  if ((param_2 & 0x40) != 0) {
    *(short *)(param_1 + 0x5ae) = sVar2;
  }
  if ((param_2 & 0x80) != 0) {
    *(short *)(param_1 + 0x72) = sVar2;
  }
  return 1;
}



// ==== 80066ac0  zz_0066ac0_ ====

undefined4 zz_0066ac0_(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  
  if (param_2 == 0) {
    iVar1 = zz_008b7b0_(*(uint *)(param_1 + 0x5b4) >> 0x10 & 0xf);
    if (iVar1 < 1) {
      uVar3 = 0;
      *(short *)(param_1 + 0x734) =
           *(short *)(param_1 + 0x72) - (*(short *)(param_1 + 0x5b0) + -0x8000);
      *(undefined2 *)(param_1 + 0x5aa) = 0;
      *(undefined2 *)(param_1 + 0x5ac) = 0;
    }
    else {
      *(short *)(param_1 + 0x734) = (short)(iVar1 + -1) * 0x2000;
      uVar2 = zz_0010514_((int)*(char *)(param_1 + 0x3e4));
      if (((uVar2 & 1) == 0) || (*(char *)(param_1 + 0x657) == '\0')) {
        *(short *)(param_1 + 0x5ac) =
             *(short *)(param_1 + 0x5b0) + *(short *)(param_1 + 0x734) + -0x8000;
      }
      else {
        *(short *)(param_1 + 0x5ac) =
             *(short *)(param_1 + 0x734) +
             *(short *)(&DAT_803c8b7a + *(char *)(param_1 + 0x3e4) * 0x3e4);
      }
      uVar3 = 1;
      *(short *)(param_1 + 0x5aa) = *(short *)(param_1 + 0x5ac) - *(short *)(param_1 + 0x72);
    }
  }
  else {
    iVar1 = zz_008b7b0_(*(byte *)(param_1 + 0x58f) & 0xf);
    if (iVar1 + -1 < 0) {
      uVar3 = 0;
      *(short *)(param_1 + 0x734) =
           *(short *)(param_1 + 0x72) - (*(short *)(param_1 + 0x5b0) + -0x8000);
      *(undefined2 *)(param_1 + 0x5aa) = 0;
      *(undefined2 *)(param_1 + 0x5ac) = 0;
    }
    else {
      if (param_2 == 1) {
        *(ushort *)(param_1 + 0x734) = (ushort)*(byte *)(iVar1 + -0x7fbcc7a9) << 8;
      }
      else {
        *(ushort *)(param_1 + 0x734) = (ushort)*(byte *)(iVar1 + -0x7fbcc7a1) << 8;
      }
      uVar3 = 1;
      *(short *)(param_1 + 0x5ac) =
           *(short *)(param_1 + 0x5b0) + *(short *)(param_1 + 0x734) + -0x8000;
      *(short *)(param_1 + 0x5aa) = *(short *)(param_1 + 0x5ac) - *(short *)(param_1 + 0x72);
    }
  }
  return uVar3;
}



// ==== 80066c58  zz_0066c58_ ====

undefined4 zz_0066c58_(int param_1)

{
  float fVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined8 local_18;
  undefined8 local_10;
  
  uVar2 = 0;
  uVar3 = *(uint *)(param_1 + 0x5b4);
  if ((uVar3 & 0x10000) == 0) {
    if ((uVar3 & 0x20000) == 0) {
      local_18 = (double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x5aa) ^ 0x80000000);
      *(short *)(param_1 + 0x5aa) =
           (short)(int)((float)(local_18 - DOUBLE_804375c8) *
                       (FLOAT_804375d8 * (FLOAT_804375dc - *(float *)(param_1 + 0x1dc8)) +
                       FLOAT_804375d4));
      *(short *)(param_1 + 0x5ac) = *(short *)(param_1 + 0x72) + *(short *)(param_1 + 0x5aa);
      *(undefined2 *)(param_1 + 0x734) = 0;
    }
    else {
      uVar2 = 1;
      *(undefined2 *)(param_1 + 0x5aa) = 0xc000;
      *(short *)(param_1 + 0x5ac) = *(short *)(param_1 + 0x72) + *(short *)(param_1 + 0x5aa);
      *(undefined2 *)(param_1 + 0x734) = *(undefined2 *)(param_1 + 0x5ac);
    }
  }
  else {
    uVar2 = 1;
    *(undefined2 *)(param_1 + 0x5aa) = 0x4000;
    *(short *)(param_1 + 0x5ac) = *(short *)(param_1 + 0x72) + *(short *)(param_1 + 0x5aa);
    *(undefined2 *)(param_1 + 0x734) = *(undefined2 *)(param_1 + 0x5ac);
  }
  if ((uVar3 & 0x80000) == 0) {
    if ((uVar3 & 0x40000) == 0) {
      local_10 = (double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1d64) ^ 0x80000000);
      *(short *)(param_1 + 0x1d64) =
           (short)(int)((float)(local_10 - DOUBLE_804375c8) *
                       (FLOAT_804375d8 * (FLOAT_804375dc - *(float *)(param_1 + 0x1dc8)) +
                       FLOAT_804375d4));
    }
    else {
      uVar2 = 1;
      fVar1 = FLOAT_804375e0 * *(float *)(param_1 + 0x1dc8);
      local_10 = (double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1d64) ^ 0x80000000);
      *(short *)(param_1 + 0x1d64) =
           (short)(int)(FLOAT_804375e8 * fVar1 +
                       (float)(local_10 - DOUBLE_804375c8) * (FLOAT_804375dc - fVar1));
    }
  }
  else {
    uVar2 = 1;
    fVar1 = FLOAT_804375e0 * *(float *)(param_1 + 0x1dc8);
    local_10 = (double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1d64) ^ 0x80000000);
    *(short *)(param_1 + 0x1d64) =
         (short)(int)(FLOAT_804375e4 * fVar1 +
                     (float)(local_10 - DOUBLE_804375c8) * (FLOAT_804375dc - fVar1));
  }
  return uVar2;
}



// ==== 80066e40  zz_0066e40_ ====

void zz_0066e40_(int param_1,int param_2)

{
  *(short *)(param_1 + 0x7e) =
       (short)(int)(*(float *)(param_1 + 0x664) *
                   *(float *)(param_1 + 0x1dc8) *
                   (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x5aa) ^ 0x80000000
                                           ) - DOUBLE_804375c8) *
                   *(float *)(*(int *)(param_1 + 0x4ac) + param_2 * 4 + 0x30));
  *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + *(short *)(param_1 + 0x7e);
  *(short *)(param_1 + 0x5aa) = *(short *)(param_1 + 0x5aa) - *(short *)(param_1 + 0x7e);
  return;
}



// ==== 80066ec0  zz_0066ec0_ ====

void zz_0066ec0_(int param_1,int param_2)

{
  if (param_2 == 0) {
    return;
  }
  *(short *)(param_1 + 0x7e) = (short)((int)*(short *)(param_1 + 0x5aa) / param_2);
  return;
}



// ==== 80066ed8  zz_0066ed8_ ====

void zz_0066ed8_(int param_1,ushort param_2,undefined2 param_3)

{
  ushort uVar1;
  
  *(ushort *)(param_1 + 0x5ac) = param_2;
  uVar1 = *(ushort *)(param_1 + 0x72);
  if (uVar1 < param_2) {
    *(ushort *)(param_1 + 0x5aa) = param_2 - uVar1;
  }
  else {
    *(ushort *)(param_1 + 0x5aa) = -(uVar1 - param_2);
  }
  *(undefined2 *)(param_1 + 0x7e) = param_3;
  return;
}



// ==== 80066f1c  zz_0066f1c_ ====

undefined4 zz_0066f1c_(int param_1)

{
  short sVar1;
  undefined4 uVar2;
  
  if (*(short *)(param_1 + 0x7e) == 0) {
    *(undefined2 *)(param_1 + 0x5aa) = 0;
    uVar2 = 1;
  }
  else {
    sVar1 = (short)(int)((float)((double)CONCAT44(0x43300000,
                                                  (int)*(short *)(param_1 + 0x7e) ^ 0x80000000) -
                                DOUBLE_804375c8) * *(float *)(param_1 + 0x1dc8));
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + sVar1;
    *(short *)(param_1 + 0x5aa) = *(short *)(param_1 + 0x5aa) - sVar1;
    if (sVar1 < 1) {
      if (-1 < *(short *)(param_1 + 0x5aa)) {
        *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + *(short *)(param_1 + 0x5aa);
        *(undefined2 *)(param_1 + 0x7e) = 0;
        *(undefined2 *)(param_1 + 0x5aa) = 0;
        return 1;
      }
    }
    else if (*(short *)(param_1 + 0x5aa) < 1) {
      *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + *(short *)(param_1 + 0x5aa);
      *(undefined2 *)(param_1 + 0x7e) = 0;
      *(undefined2 *)(param_1 + 0x5aa) = 0;
      return 1;
    }
    uVar2 = 0;
  }
  return uVar2;
}



// ==== 80066ff0  zz_0066ff0_ ====

undefined4 zz_0066ff0_(int param_1)

{
  ushort uVar1;
  undefined4 uVar2;
  short sVar3;
  int iVar4;
  
  if (*(short *)(param_1 + 0x7e) == 0) {
    *(undefined2 *)(param_1 + 0x5aa) = 0;
    uVar2 = 1;
  }
  else {
    uVar1 = *(ushort *)(param_1 + 0x5aa);
    sVar3 = (short)(int)((float)((double)CONCAT44(0x43300000,
                                                  (int)*(short *)(param_1 + 0x7e) ^ 0x80000000) -
                                DOUBLE_804375c8) * *(float *)(param_1 + 0x1dc8));
    if (sVar3 < 1) {
      iVar4 = (uint)uVar1 + (int)sVar3;
      *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) - sVar3;
      *(short *)(param_1 + 0x5aa) = *(short *)(param_1 + 0x5aa) + sVar3;
      if (iVar4 < 0) {
        *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + (short)iVar4;
        *(undefined2 *)(param_1 + 0x5aa) = 0;
        return 1;
      }
    }
    else {
      if ((int)(uint)uVar1 <= (int)sVar3) {
        *(ushort *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) - uVar1;
        *(undefined2 *)(param_1 + 0x5aa) = 0;
        return 1;
      }
      *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + sVar3;
      *(short *)(param_1 + 0x5aa) = *(short *)(param_1 + 0x5aa) - sVar3;
    }
    uVar2 = 0;
  }
  return uVar2;
}



// ==== 800670dc  zz_00670dc_ ====

/* WARNING: Removing unreachable block (ram,0x800672f0) */
/* WARNING: Removing unreachable block (ram,0x800670ec) */

void zz_00670dc_(int param_1,short param_2)

{
  float fVar1;
  undefined4 uVar2;
  float fVar3;
  undefined4 uVar4;
  double dVar5;
  double dVar6;
  float afStack_3c [3];
  float local_30;
  float local_2c;
  float local_28;
  float afStack_24 [3];
  
  if (*(char *)(param_1 + 0x598) == '\0') {
    fVar3 = *(float *)(param_1 + 0x44);
    if (fVar3 < FLOAT_804375d0) {
      fVar3 = -fVar3;
    }
    if (FLOAT_804375ec < fVar3) {
      dVar6 = (double)(*(float *)(param_1 + 0x5f4) * *(float *)(param_1 + 0x5f8));
      dVar5 = zz_0045204_(param_2);
      local_30 = (float)((double)*(float *)(param_1 + 0x44) * dVar5);
      local_2c = FLOAT_804375d0;
      dVar5 = zz_0045238_(param_2);
      local_28 = (float)((double)*(float *)(param_1 + 0x44) * dVar5);
      uVar4 = *(undefined4 *)(param_1 + 0x20);
      fVar3 = *(float *)(param_1 + 0x24);
      uVar2 = *(undefined4 *)(param_1 + 0x28);
      if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
        zz_003de80_((double)*(float *)(param_1 + 0x668),param_1,(float *)(param_1 + 0x20),afStack_24
                   );
        gnt4_PSVECCrossProduct_bl(afStack_24,&local_30,afStack_3c);
        gnt4_PSVECCrossProduct_bl(afStack_3c,afStack_24,&local_30);
        gnt4_PSVECNormalize_bl(&local_30,&local_30);
        gnt4_PSQUATScale_bl((double)(float)((double)*(float *)(param_1 + 0x44) * dVar6),&local_30,
                            &local_30);
        *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x20) + local_30;
        *(float *)(param_1 + 0x28) = *(float *)(param_1 + 0x28) + local_28;
        dVar5 = FUN_8003d6e4((double)*(float *)(param_1 + 0x668),param_1,(float *)(param_1 + 0x20));
        *(float *)(param_1 + 0x24) = (float)dVar5;
        fVar1 = FLOAT_804375d0;
        *(float *)(param_1 + 0x44) =
             *(float *)(param_1 + 0x4c) * *(float *)(param_1 + 0x5f4) + *(float *)(param_1 + 0x44);
        if (*(float *)(param_1 + 0x44) < fVar1) {
          *(float *)(param_1 + 0x44) = fVar1;
        }
        fVar1 = *(float *)(param_1 + 0x24) - fVar3;
        if (-*(float *)(param_1 + 0x674) <= fVar1) {
          if (*(float *)(param_1 + 0x674) < fVar1) {
            *(undefined4 *)(param_1 + 0x20) = uVar4;
            *(float *)(param_1 + 0x24) = fVar3;
            *(undefined4 *)(param_1 + 0x28) = uVar2;
          }
        }
        else {
          *(float *)(param_1 + 0x24) = fVar3;
        }
      }
      else {
        *(float *)(param_1 + 0x20) =
             (float)((double)local_30 * dVar6 + (double)*(float *)(param_1 + 0x20));
        *(float *)(param_1 + 0x28) =
             (float)((double)local_28 * dVar6 + (double)*(float *)(param_1 + 0x28));
        dVar5 = FUN_8003d6e4((double)*(float *)(param_1 + 0x668),param_1,(float *)(param_1 + 0x20));
        if ((double)*(float *)(param_1 + 0x24) < dVar5) {
          *(float *)(param_1 + 0x24) = (float)dVar5;
        }
        fVar3 = FLOAT_804375d0;
        *(float *)(param_1 + 0x44) =
             *(float *)(param_1 + 0x4c) * *(float *)(param_1 + 0x5f4) + *(float *)(param_1 + 0x44);
        if (*(float *)(param_1 + 0x44) < fVar3) {
          *(float *)(param_1 + 0x44) = fVar3;
        }
      }
    }
  }
  return;
}



// ==== 80067310  FUN_80067310 ====

/* WARNING: Removing unreachable block (ram,0x80067438) */
/* WARNING: Removing unreachable block (ram,0x80067430) */
/* WARNING: Removing unreachable block (ram,0x80067328) */
/* WARNING: Removing unreachable block (ram,0x80067320) */

void FUN_80067310(double param_1,int param_2,short param_3)

{
  float fVar1;
  double dVar2;
  double dVar3;
  
  dVar3 = (double)(*(float *)(param_2 + 0x5f4) * *(float *)(param_2 + 0x5f8));
  dVar2 = zz_0045204_(param_3);
  *(float *)(param_2 + 0x20) =
       (float)(dVar3 * (double)(float)((double)*(float *)(param_2 + 0x44) * dVar2) +
              (double)*(float *)(param_2 + 0x20));
  *(float *)(param_2 + 0x24) =
       (float)((double)*(float *)(param_2 + 0x48) * dVar3 + (double)*(float *)(param_2 + 0x24));
  dVar2 = zz_0045238_(param_3);
  *(float *)(param_2 + 0x28) =
       (float)(dVar3 * (double)(float)((double)*(float *)(param_2 + 0x44) * dVar2) +
              (double)*(float *)(param_2 + 0x28));
  zz_0068030_(param_2);
  fVar1 = FLOAT_804375d0;
  *(float *)(param_2 + 0x44) =
       *(float *)(param_2 + 0x4c) * *(float *)(param_2 + 0x5f4) + *(float *)(param_2 + 0x44);
  if (*(float *)(param_2 + 0x44) < fVar1) {
    *(float *)(param_2 + 0x44) = fVar1;
  }
  *(float *)(param_2 + 0x48) =
       *(float *)(param_2 + 0x5f4) * (float)((double)*(float *)(param_2 + 0x50) * param_1) +
       *(float *)(param_2 + 0x48);
  if ((*(char *)(param_2 + 0x741) == '\0') && (*(char *)(param_2 + 0x6cb) == '\0')) {
    fVar1 = *(float *)(param_2 + 0x680);
    if (fVar1 < *(float *)(param_2 + 0x48)) {
      fVar1 = *(float *)(param_2 + 0x48);
    }
    *(float *)(param_2 + 0x48) = fVar1;
  }
  else {
    fVar1 = FLOAT_804375f0;
    if (FLOAT_804375f0 < *(float *)(param_2 + 0x48)) {
      fVar1 = *(float *)(param_2 + 0x48);
    }
    *(float *)(param_2 + 0x48) = fVar1;
  }
  return;
}



// ==== 80067458  zz_0067458_ ====

void zz_0067458_(double param_1,int param_2,short param_3)

{
  float fVar1;
  float fVar2;
  
  FUN_80067310(param_1,param_2,param_3);
  if (FLOAT_804375d0 < *(float *)(param_2 + 0x4c)) {
    fVar1 = *(float *)(param_2 + 0x44);
    fVar2 = *(float *)(param_2 + 0x678);
    if ((fVar1 <= fVar2) && (fVar2 = fVar1, fVar1 < FLOAT_804375d0)) {
      fVar2 = FLOAT_804375d0;
    }
    *(float *)(param_2 + 0x44) = fVar2;
  }
  if ((*(char *)(param_2 + 0x741) == '\0') && (*(char *)(param_2 + 0x6cb) == '\0')) {
    fVar1 = *(float *)(param_2 + 0x48);
    fVar2 = *(float *)(param_2 + 0x67c);
    if ((fVar1 <= fVar2) && (fVar2 = fVar1, fVar1 < *(float *)(param_2 + 0x680))) {
      fVar2 = *(float *)(param_2 + 0x680);
    }
    *(float *)(param_2 + 0x48) = fVar2;
  }
  else {
    fVar1 = FLOAT_804375f0;
    if (FLOAT_804375f0 < *(float *)(param_2 + 0x48)) {
      fVar1 = *(float *)(param_2 + 0x48);
    }
    *(float *)(param_2 + 0x48) = fVar1;
  }
  return;
}



// ==== 80067524  FUN_80067524 ====

/* WARNING: Removing unreachable block (ram,0x800675f0) */
/* WARNING: Removing unreachable block (ram,0x800675e8) */
/* WARNING: Removing unreachable block (ram,0x8006753c) */
/* WARNING: Removing unreachable block (ram,0x80067534) */

void FUN_80067524(double param_1,int param_2,short param_3)

{
  float fVar1;
  double dVar2;
  double dVar3;
  
  dVar3 = (double)(*(float *)(param_2 + 0x5f4) * *(float *)(param_2 + 0x5f8));
  dVar2 = zz_0045204_(param_3);
  *(float *)(param_2 + 0x20) =
       (float)(dVar3 * (double)(float)((double)*(float *)(param_2 + 0x44) * dVar2) +
              (double)*(float *)(param_2 + 0x20));
  *(float *)(param_2 + 0x24) =
       (float)((double)*(float *)(param_2 + 0x48) * dVar3 + (double)*(float *)(param_2 + 0x24));
  dVar2 = zz_0045238_(param_3);
  fVar1 = FLOAT_804375d0;
  *(float *)(param_2 + 0x28) =
       (float)(dVar3 * (double)(float)((double)*(float *)(param_2 + 0x44) * dVar2) +
              (double)*(float *)(param_2 + 0x28));
  *(float *)(param_2 + 0x44) =
       *(float *)(param_2 + 0x4c) * *(float *)(param_2 + 0x5f4) + *(float *)(param_2 + 0x44);
  if (*(float *)(param_2 + 0x44) < fVar1) {
    *(float *)(param_2 + 0x44) = fVar1;
  }
  *(float *)(param_2 + 0x48) =
       *(float *)(param_2 + 0x5f4) * (float)((double)*(float *)(param_2 + 0x50) * param_1) +
       *(float *)(param_2 + 0x48);
  return;
}



// ==== 80067610  FUN_80067610 ====

/* WARNING: Removing unreachable block (ram,0x800676bc) */
/* WARNING: Removing unreachable block (ram,0x80067620) */

void FUN_80067610(int param_1)

{
  float fVar1;
  double dVar2;
  
  if (FLOAT_804375f4 <
      *(float *)(param_1 + 0x40) * *(float *)(param_1 + 0x40) +
      *(float *)(param_1 + 0x38) * *(float *)(param_1 + 0x38) +
      *(float *)(param_1 + 0x3c) * *(float *)(param_1 + 0x3c)) {
    dVar2 = (double)(*(float *)(param_1 + 0x5f4) * *(float *)(param_1 + 0x5f8));
    gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSQUATScale_bl((double)(float)((double)*(float *)(param_1 + 0x44) * dVar2),
                        (float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
    fVar1 = FLOAT_804375d0;
    *(float *)(param_1 + 0x44) =
         *(float *)(param_1 + 0x4c) * *(float *)(param_1 + 0x5f4) + *(float *)(param_1 + 0x44);
    if (*(float *)(param_1 + 0x44) < fVar1) {
      *(float *)(param_1 + 0x44) = fVar1;
    }
  }
  return;
}



// ==== 800676d8  FUN_800676d8 ====

/* WARNING: Removing unreachable block (ram,0x80067734) */
/* WARNING: Removing unreachable block (ram,0x800676e8) */

void FUN_800676d8(double param_1,int param_2,short param_3)

{
  double dVar1;
  double dVar2;
  
  dVar2 = (double)(*(float *)(param_2 + 0x5f8) *
                  (float)(param_1 * (double)*(float *)(param_2 + 0x5f4)));
  dVar1 = zz_0045204_(param_3);
  *(float *)(param_2 + 0x20) = (float)(dVar2 * dVar1 + (double)*(float *)(param_2 + 0x20));
  dVar1 = zz_0045238_(param_3);
  *(float *)(param_2 + 0x28) = (float)(dVar2 * dVar1 + (double)*(float *)(param_2 + 0x28));
  return;
}



// ==== 80067754  zz_0067754_ ====

void zz_0067754_(int param_1,short *param_2,short param_3)

{
  *param_2 = (short)(int)((float)((double)CONCAT44(0x43300000,(int)param_3 ^ 0x80000000) -
                                 DOUBLE_804375c8) * *(float *)(param_1 + 0x1dc8) +
                         (float)((double)CONCAT44(0x43300000,(int)*param_2 ^ 0x80000000) -
                                DOUBLE_804375c8));
  return;
}



// ==== 800677b0  zz_00677b0_ ====

/* WARNING: Removing unreachable block (ram,0x800679b0) */
/* WARNING: Removing unreachable block (ram,0x800677c0) */

undefined4 zz_00677b0_(int param_1)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  short sVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  if (*(char *)(param_1 + 0x7c9) == '\0') {
    dVar5 = FUN_8003e0a8((double)*(float *)(param_1 + 0x668),param_1,(float *)(param_1 + 0x20),
                         &local_28);
    if ((double)(*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x6d0)) <= dVar5) {
      if ((*(char *)(param_1 + 0x1db) == '\0') &&
         (gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x2c),&local_34),
         FLOAT_804375f8 < local_2c * local_2c + local_34 * local_34 + local_30 * local_30)) {
        gnt4_PSVECNormalize_bl(&local_34,&local_34);
        dVar6 = gnt4_PSQUATDotProduct_bl(&local_34,&local_28);
        if ((double)FLOAT_804375d0 < dVar6) {
          return 0;
        }
      }
      if (*(float *)(param_1 + 0x698) <= FLOAT_804375d0) {
        sVar4 = *(short *)(*(int *)(param_1 + 0x4b0) + 0xac);
      }
      else {
        sVar4 = *(short *)(*(int *)(param_1 + 0x4b0) + 0xae);
      }
      dVar6 = (double)(local_28 * local_28 + local_20 * local_20);
      if ((double)FLOAT_804375d0 < dVar6) {
        dVar7 = 1.0 / SQRT(dVar6);
        dVar7 = DOUBLE_80437600 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80437608);
        dVar7 = DOUBLE_80437600 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80437608);
        dVar6 = (double)(float)(dVar6 * DOUBLE_80437600 * dVar7 *
                                        -(dVar6 * dVar7 * dVar7 - DOUBLE_80437608));
      }
      iVar3 = FUN_800452a0(dVar6,(double)local_24);
      if (sVar4 < (short)iVar3) {
        dVar6 = zz_0045238_((short)iVar3);
        gnt4_PSQUATScale_bl((double)(float)((double)(float)(dVar5 - (double)*(float *)(param_1 +
                                                                                      0x24)) * dVar6
                                           ),&local_28,&local_28);
        gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),&local_28,(float *)(param_1 + 0x20));
        fVar1 = FLOAT_804375d4;
        uVar2 = 0;
        *(float *)(param_1 + 0x4c) = FLOAT_804375d0;
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
        *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * fVar1;
      }
      else {
        *(float *)(param_1 + 0x24) = (float)(dVar5 - (double)*(float *)(param_1 + 0x6d0));
        if (*(code **)(param_1 + 0x754) != (code *)0x0) {
          (**(code **)(param_1 + 0x754))(param_1);
        }
        uVar2 = 1;
      }
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



// ==== 800679d0  zz_00679d0_ ====

void zz_00679d0_(int param_1)

{
  int iVar1;
  
  iVar1 = zz_00677b0_(param_1);
  if ((iVar1 == 0) && ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0)) {
    *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x2c);
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x30);
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x34);
  }
  return;
}



// ==== 80067a28  zz_0067a28_ ====

void zz_0067a28_(int param_1)

{
  int iVar1;
  
  iVar1 = zz_00677b0_(param_1);
  if ((iVar1 == 0) && ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0)) {
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x840;
  }
  return;
}



// ==== 80067a70  zz_0067a70_ ====

void zz_0067a70_(int param_1)

{
  char cVar1;
  char *pcVar2;
  float afStack_88 [3];
  float afStack_7c [3];
  float afStack_70 [12];
  float afStack_40 [14];
  
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffefffff;
  *(undefined1 *)(param_1 + 0x598) = 0;
  if (((*(char *)(param_1 + 0x1db) != '\0') &&
      (pcVar2 = *(char **)(param_1 + 0x1e4), pcVar2 != (char *)0x0)) && (*pcVar2 != '\0')) {
    cVar1 = pcVar2[0x83];
    if (cVar1 == '\0') {
      cVar1 = zz_008b480_();
      if (((cVar1 == '\0') || ((pcVar2[0x3e5] & PTR_DAT_80433934[0xeb]) != 0)) &&
         (pcVar2[0x18] == '\x01')) {
        *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x100000;
        gnt4_PSMTXIdentity_bl(afStack_40);
        zz_020b4ac_((double)*(float *)(pcVar2 + 0x2c),(double)*(float *)(pcVar2 + 0x30),
                    (double)*(float *)(pcVar2 + 0x34),afStack_40,afStack_40);
        FUN_80045838(afStack_40,afStack_40,*(short *)(pcVar2 + 0x76),*(short *)(pcVar2 + 0x78),
                     *(short *)(pcVar2 + 0x7a));
        zz_00457d4_('z',afStack_40,afStack_40,*(short *)(pcVar2 + 0x1d6e));
        zz_00457d4_('x',afStack_40,afStack_40,*(short *)(pcVar2 + 0x1d6a));
        zz_00457d4_('y',afStack_40,afStack_40,*(short *)(pcVar2 + 0x1d6c));
        zz_004516c_(afStack_40,(float *)(param_1 + 0x20),afStack_7c);
        gnt4_PSMTXIdentity_bl(afStack_40);
        zz_020b4ac_((double)*(float *)(pcVar2 + 0x20),(double)*(float *)(pcVar2 + 0x24),
                    (double)*(float *)(pcVar2 + 0x28),afStack_40,afStack_40);
        FUN_80045838(afStack_40,afStack_40,*(short *)(pcVar2 + 0x70),*(short *)(pcVar2 + 0x72),
                     *(short *)(pcVar2 + 0x74));
        zz_00457d4_('z',afStack_40,afStack_40,*(short *)(pcVar2 + 0x1d68));
        zz_00457d4_('x',afStack_40,afStack_40,*(short *)(pcVar2 + 0x1d64));
        zz_00457d4_('y',afStack_40,afStack_40,*(short *)(pcVar2 + 0x1d66));
        gnt4_PSMTXMultVec_bl(afStack_40,afStack_7c,(float *)(param_1 + 0x20));
        *(short *)(param_1 + 0x72) =
             *(short *)(param_1 + 0x72) + (*(short *)(pcVar2 + 0x72) - *(short *)(pcVar2 + 0x78));
        if ((pcVar2[1000] != '\x0e') && ((*(uint *)(param_1 + 0x5e0) & 0x81000000) == 0)) {
          *(undefined1 *)(param_1 + 0x598) = 1;
        }
      }
    }
    else if (((cVar1 == '\x11') || (cVar1 == '\x16')) || (cVar1 == '\x17')) {
      cVar1 = zz_008b480_();
      if (cVar1 != '\0') {
        if (*(int *)(pcVar2 + 0x90) == 0) {
          return;
        }
        if ((*(byte *)(*(int *)(pcVar2 + 0x90) + 0x3e5) & PTR_DAT_80433934[0xeb]) == 0) {
          return;
        }
      }
      if (pcVar2[0x18] == '\x01') {
        *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x100000;
        gnt4_PSMTXIdentity_bl(afStack_70);
        zz_020b4ac_((double)*(float *)(pcVar2 + 0x2c),(double)*(float *)(pcVar2 + 0x30),
                    (double)*(float *)(pcVar2 + 0x34),afStack_70,afStack_70);
        FUN_80045838(afStack_70,afStack_70,*(short *)(pcVar2 + 0x76),*(short *)(pcVar2 + 0x78),
                     *(short *)(pcVar2 + 0x7a));
        zz_004516c_(afStack_70,(float *)(param_1 + 0x20),afStack_88);
        gnt4_PSMTXIdentity_bl(afStack_70);
        zz_020b4ac_((double)*(float *)(pcVar2 + 0x20),(double)*(float *)(pcVar2 + 0x24),
                    (double)*(float *)(pcVar2 + 0x28),afStack_70,afStack_70);
        FUN_80045838(afStack_70,afStack_70,*(short *)(pcVar2 + 0x70),*(short *)(pcVar2 + 0x72),
                     *(short *)(pcVar2 + 0x74));
        gnt4_PSMTXMultVec_bl(afStack_70,afStack_88,(float *)(param_1 + 0x20));
        *(short *)(param_1 + 0x72) =
             *(short *)(param_1 + 0x72) + (*(short *)(pcVar2 + 0x72) - *(short *)(pcVar2 + 0x78));
      }
    }
  }
  return;
}



// ==== 80067d70  zz_0067d70_ ====

double zz_0067d70_(int param_1,float *param_2,float *param_3)

{
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  
  local_1c = *param_2;
  local_18 = param_2[1];
  local_14 = param_2[2];
  gnt4_GXProject_bl((double)local_1c,(double)local_18,(double)local_14,
                    (float *)(&DAT_803c7744 + param_1 * 0x3e4),(float *)&DAT_803c0fd8,
                    (float *)&DAT_803c0fc0,&local_28,&local_24,&local_20);
  if (param_3 != (float *)0x0) {
    *param_3 = local_28;
    param_3[1] = local_24;
    param_3[2] = local_20;
  }
  return (double)local_20;
}



// ==== 80067e18  zz_0067e18_ ====

void zz_0067e18_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,int param_11,
                int *param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
                undefined4 param_16)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  float fVar4;
  int iVar5;
  undefined1 *puVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined1 *puVar11;
  double dVar12;
  
  iVar3 = zz_0006f98_(param_9);
  iVar8 = *(int *)(iVar3 + 0x604);
  iVar7 = *param_12;
  iVar5 = *(int *)(iVar8 + 4);
  iVar9 = iVar8 + *(int *)(iVar8 + 8);
  cVar1 = *(char *)(iVar9 + iVar7);
  iVar10 = (int)cVar1;
  *param_12 = iVar7 + 1;
  puVar11 = (undefined1 *)(iVar8 + iVar5 + iVar10 * 4);
  iVar3 = iVar3 + iVar10 * 0x30;
  if (param_10 == 0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80437610,
                     0x3e4,&DAT_80437618,iVar7,iVar9,param_14,param_15,param_16);
  }
  fVar4 = *(float *)(param_10 + 0x3c);
  puVar6 = (undefined1 *)(param_9 + iVar10 * 4 + 0x1994);
  uVar2 = *(undefined4 *)(param_10 + 0x40);
  dVar12 = (double)fVar4;
  *(undefined4 *)(iVar3 + 0xc) = *(undefined4 *)(param_10 + 0x38);
  *(float *)(iVar3 + 0x1c) = fVar4;
  *(undefined4 *)(iVar3 + 0x2c) = uVar2;
  *puVar6 = *puVar11;
  puVar6[1] = puVar11[1];
  puVar6[2] = puVar11[2];
  puVar6[3] = cVar1;
  *(int *)(param_11 + iVar10 * 4) = param_10;
  if (param_10 == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = *(int *)(param_10 + 0x10);
  }
  if (iVar3 != 0) {
    dVar12 = (double)zz_0067e18_(dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 param_9,iVar3,param_11,param_12,iVar9,param_14,param_15,param_16);
  }
  if (param_10 == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = *(int *)(param_10 + 8);
  }
  if (iVar3 != 0) {
    zz_0067e18_(dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar3,
                param_11,param_12,iVar9,param_14,param_15,param_16);
  }
  return;
}



// ==== 80067f54  zz_0067f54_ ====

void zz_0067f54_(int param_1,undefined1 param_2,undefined1 param_3)

{
  PTR_DAT_80433934[param_1 * 0x3c + 0x100] = param_2;
  PTR_DAT_80433934[param_1 * 0x3c + 0x101] = param_3;
  return;
}



// ==== 80067f74  zz_0067f74_ ====

void zz_0067f74_(int param_1)

{
  PTR_DAT_80433934[param_1 * 0x3c + 0x100] = 0;
  PTR_DAT_80433934[param_1 * 0x3c + 0x101] = 0;
  return;
}



// ==== 80067f98  zz_0067f98_ ====

void zz_0067f98_(int param_1,undefined2 param_2)

{
  char cVar1;
  
  cVar1 = zz_008b480_();
  if (cVar1 == '\0') {
    PTR_DAT_80433934[0xea] = PTR_DAT_80433934[0xea] | *(byte *)(param_1 + 0x3e5);
    *(undefined2 *)(PTR_DAT_80433934 + *(char *)(param_1 + 0x3e4) * 2 + 0xdc) = param_2;
  }
  return;
}



// ==== 80068004  zz_0068004_ ====

void zz_0068004_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar1 = *(float *)(*(int *)(param_1 + 0x4b0) + 0x4c);
  fVar2 = *(float *)(*(int *)(param_1 + 0x4b0) + 0x50);
  if (fVar2 < fVar1) {
    fVar2 = fVar1;
  }
  *(float *)(param_1 + 0x7fc) = fVar2 / FLOAT_80437620;
  return;
}



// ==== 80068030  zz_0068030_ ====

undefined4 zz_0068030_(int param_1)

{
  float fVar1;
  char cVar3;
  undefined4 uVar2;
  
  cVar3 = zz_008b290_();
  if ((((cVar3 != '\0') || (*(char *)(param_1 + 0x1db) != '\0')) ||
      (*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x668) <= *(float *)(DAT_8043625c + 0x34)))
     || (*(float *)(param_1 + 0x48) <= FLOAT_804375d0)) {
    uVar2 = 0;
  }
  else {
    *(float *)(param_1 + 0x48) = FLOAT_804375d0;
    fVar1 = *(float *)(DAT_8043625c + 0x34) - *(float *)(param_1 + 0x668);
    if (*(float *)(param_1 + 0x30) <= fVar1) {
      *(float *)(param_1 + 0x24) = fVar1;
    }
    else {
      *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x30);
    }
    uVar2 = 1;
  }
  return uVar2;
}



// ==== 800680d4  zz_00680d4_ ====

void zz_00680d4_(int param_1,int param_2)

{
  if (PTR_DAT_80433930[0x40] == '\0') {
    if ((*PTR_DAT_80433930 == '\x03') && ('\x04' < (char)PTR_DAT_80433934[0x45])) {
      return;
    }
    if (*(char *)(param_1 + 0x3e6) == '\0') {
      zz_010d880_((int)*(char *)(param_1 + 0x3e4),param_2);
    }
  }
  return;
}



// ==== 80068138  FUN_80068138 ====

void FUN_80068138(int param_1)

{
  if (PTR_DAT_80433934[0x1f] == '\0') {
    *(undefined1 *)(param_1 + 0x74a) = 0x10;
    *(undefined1 *)(param_1 + 0x74e) = 0;
    *(undefined2 *)(param_1 + 0x750) = 0;
    zz_006826c_(param_1);
  }
  return;
}



// ==== 8006817c  zz_006817c_ ====

void zz_006817c_(int param_1,int param_2)

{
  int iVar1;
  
  if (PTR_DAT_80433934[0x1f] == '\0') {
    iVar1 = *(char *)(param_1 + 0x74a) + param_2;
    if (iVar1 < 0x80) {
      if (iVar1 < -0x7f) {
        *(undefined1 *)(param_1 + 0x74a) = 0x81;
      }
      else {
        *(char *)(param_1 + 0x74a) = (char)iVar1;
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x74a) = 0x7f;
    }
    zz_006826c_(param_1);
  }
  return;
}



// ==== 800681e4  zz_00681e4_ ====

void zz_00681e4_(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  if (PTR_DAT_80433934[0x1f] == '\0') {
    iVar1 = (int)*(char *)(param_1 + 0x74a);
    iVar2 = iVar1 + param_2;
    if (iVar2 < 0x40) {
      if (iVar2 < -0x3f) {
        iVar1 = -0x3f - iVar1;
      }
      else {
        iVar1 = iVar2 - iVar1;
      }
    }
    else {
      iVar1 = 0x3f - iVar1;
    }
    if (iVar1 != 0) {
      *(char *)(param_1 + 0x74e) = *(char *)(param_1 + 0x74e) + (char)iVar1;
      if (*(char *)(param_1 + 0x74e) != '\0') {
        *(undefined2 *)(param_1 + 0x750) = 900;
      }
      zz_006817c_(param_1,iVar1);
    }
  }
  return;
}



// ==== 8006826c  zz_006826c_ ====

void zz_006826c_(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  
  if (*(int *)(param_1 + 0x4ac) == 0) {
    return;
  }
  cVar1 = *(char *)(param_1 + 0x74a);
  if (*(char *)(param_1 + 0x74d) < cVar1) {
    *(char *)(param_1 + 0x74b) = *(char *)(param_1 + 0x74d);
  }
  else if (cVar1 < *(char *)(param_1 + 0x74c)) {
    *(char *)(param_1 + 0x74b) = *(char *)(param_1 + 0x74c);
  }
  else {
    *(char *)(param_1 + 0x74b) = cVar1;
  }
  puVar2 = (undefined4 *)
           ((&PTR_DAT_804339e0)[*(byte *)(*(int *)(param_1 + 0x4ac) + 0xa3)] +
           *(char *)(param_1 + 0x74b) * 0xc);
  *(undefined4 *)(param_1 + 0xb8) = *puVar2;
  *(undefined4 *)(param_1 + 0x1dd0) = puVar2[1];
  *(undefined4 *)(param_1 + 0x5f8) = puVar2[2];
  return;
}



// ==== 800682f8  zz_00682f8_ ====

void zz_00682f8_(int param_1)

{
  undefined *puVar1;
  int iVar2;
  
  puVar1 = PTR_DAT_80433934;
  iVar2 = *(char *)(param_1 + 999) * 0x348 + *(char *)(param_1 + 0x492) * 0x1c;
  PTR_DAT_80433934[iVar2 + 0x1fe] = 1;
  *(undefined2 *)(puVar1 + iVar2 + 0x1f8) = *(undefined2 *)(param_1 + 0x1c4);
  *(undefined2 *)(puVar1 + iVar2 + 0x1fa) = *(undefined2 *)(param_1 + 0x1c6);
  *(undefined2 *)(puVar1 + iVar2 + 0x1fc) = *(undefined2 *)(param_1 + 0x1c8);
  return;
}



// ==== 80068344  FUN_80068344 ====

void FUN_80068344(int param_1)

{
  undefined *puVar1;
  int iVar2;
  
  *(undefined *)(param_1 + 0x492) = PTR_DAT_80433934[*(char *)(param_1 + 999) + 0x54];
  puVar1 = PTR_DAT_80433934;
  iVar2 = *(char *)(param_1 + 999) * 0x348 + *(char *)(param_1 + 0x492) * 0x1c;
  *(undefined *)(param_1 + 0x3ee) = PTR_DAT_80433934[iVar2 + 0x1eb];
  *(undefined4 *)(param_1 + 0x3f4) = *(undefined4 *)(puVar1 + iVar2 + 500);
  *(undefined4 *)(param_1 + 0x3f8) = *(undefined4 *)(puVar1 + iVar2 + 0x1ec);
  if (PTR_DAT_80433930[0x32] == '\0') {
    if (PTR_DAT_80433934[0x1f] == '\0') {
      *(undefined4 *)(puVar1 + iVar2 + 0x1f0) = 2;
    }
  }
  if (puVar1[iVar2 + 0x1fe] == '\0') {
    return;
  }
  *(undefined2 *)(param_1 + 0x1c4) = *(undefined2 *)(puVar1 + iVar2 + 0x1f8);
  *(undefined2 *)(param_1 + 0x1c6) = *(undefined2 *)(puVar1 + iVar2 + 0x1fa);
  *(undefined2 *)(param_1 + 0x1c8) = *(undefined2 *)(puVar1 + iVar2 + 0x1fc);
  return;
}



// ==== 800683ec  zz_00683ec_ ====

void zz_00683ec_(int param_1)

{
  undefined *puVar1;
  int iVar2;
  
  puVar1 = PTR_DAT_80433934;
  iVar2 = *(char *)(param_1 + 999) * 0x348 + *(char *)(param_1 + 0x492) * 0x1c;
  PTR_DAT_80433934[iVar2 + 0x1fe] = 1;
  puVar1[iVar2 + 0x200] = 1;
  return;
}



// ==== 80068424  zz_0068424_ ====

void zz_0068424_(int param_1,undefined2 *param_2,undefined1 *param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = param_1 * 0x348;
  cVar1 = PTR_DAT_80433934[param_1 + 0x15c8];
  PTR_DAT_80433934[param_1 + 0x54] = cVar1;
  iVar3 = cVar1 * 0x1c;
  iVar2 = cVar1 + 1;
  *param_2 = *(undefined2 *)(PTR_DAT_80433934 + iVar3 + iVar4 + 0x1e8);
  *param_3 = PTR_DAT_80433934[iVar3 + iVar4 + 0x1ea];
  PTR_DAT_80433934[iVar3 + iVar4 + 0x1ff] = 1;
  PTR_DAT_80433934[param_1 + 0x15c8] =
       (char)iVar2 -
       (char)(iVar2 / (int)(char)PTR_DAT_80433934[param_1 + 0x5a]) *
       PTR_DAT_80433934[param_1 + 0x5a];
  return;
}



// ==== 800684a4  zz_00684a4_ ====

void zz_00684a4_(int param_1,undefined2 *param_2,undefined1 *param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = param_1 * 0x348;
  PTR_DAT_80433934[param_1 + 0x15c8] = PTR_DAT_80433934[param_1 + 0x54];
  cVar1 = PTR_DAT_80433934[param_1 + 0x15ce];
  PTR_DAT_80433934[param_1 + 0x54] = cVar1;
  iVar3 = cVar1 * 0x1c;
  iVar2 = cVar1 + 1;
  *param_2 = *(undefined2 *)(PTR_DAT_80433934 + iVar3 + iVar4 + 0x1e8);
  *param_3 = PTR_DAT_80433934[iVar3 + iVar4 + 0x1ea];
  PTR_DAT_80433934[iVar3 + iVar4 + 0x1ff] = 1;
  *(short *)(PTR_DAT_80433934 + param_1 * 8 + 0x159e) =
       *(short *)(PTR_DAT_80433934 + param_1 * 8 + 0x159e) + -1;
  PTR_DAT_80433934[param_1 + 0x15ce] =
       (char)iVar2 -
       (char)(iVar2 / (int)(char)PTR_DAT_80433934[param_1 + 0x5a]) *
       PTR_DAT_80433934[param_1 + 0x5a];
  return;
}



// ==== 8006854c  zz_006854c_ ====

undefined1 zz_006854c_(char *param_1)

{
  return (&PTR_s_______________802dd4c0)[*param_1][(byte)param_1[1]];
}



// ==== 80068570  zz_0068570_ ====

uint zz_0068570_(int param_1,int param_2)

{
  if (param_2 < 0x20) {
    return 1 << param_2 & *(uint *)(&DAT_802f29c8 + param_1 * 8);
  }
  return 1 << param_2 + -0x20 & *(uint *)(&DAT_802f29cc + param_1 * 8);
}



// ==== 800685c0  zz_00685c0_ ====

void zz_00685c0_(int param_1)

{
  zz_0068980_(param_1,(byte *)(param_1 + 0x5fc));
  *(undefined4 *)(param_1 + 0x5d4) = 0;
  zz_0068b8c_(param_1,&DAT_802d38f8,(byte *)(param_1 + 0x614),0x20);
  zz_0068b8c_(param_1,&DAT_802d3904,(byte *)(param_1 + 0x618),0x40);
  zz_0068b8c_(param_1,&DAT_802d3910,(byte *)(param_1 + 0x61c),0x80);
  zz_0068b8c_(param_1,&DAT_802d391c,(byte *)(param_1 + 0x624),0x200);
  zz_0068b8c_(param_1,&DAT_802d3928,(byte *)(param_1 + 0x600),1);
  zz_0068b8c_(param_1,&DAT_802d3934,(byte *)(param_1 + 0x604),2);
  zz_0068b8c_(param_1,&DAT_802d3940,(byte *)(param_1 + 0x608),4);
  zz_0068b8c_(param_1,&DAT_802d394c,(byte *)(param_1 + 0x60c),8);
  zz_0068b8c_(param_1,&DAT_802d3958,(byte *)(param_1 + 0x610),0x10);
  zz_0068b8c_(param_1,&DAT_802d3964,(byte *)(param_1 + 0x628),0x2000);
  zz_00686f0_(param_1);
  return;
}



// ==== 800686f0  zz_00686f0_ ====

/* WARNING: Removing unreachable block (ram,0x80068964) */
/* WARNING: Removing unreachable block (ram,0x80068700) */

void zz_00686f0_(int param_1)

{
  char cVar1;
  float fVar2;
  byte bVar3;
  float fVar4;
  int iVar5;
  uint *puVar6;
  int iVar7;
  uint *puVar8;
  int iVar9;
  double dVar10;
  
  if (PTR_DAT_80433934[0x1829] == '\0') {
    dVar10 = (double)*(float *)(param_1 + 0x768);
    if (*(char *)(param_1 + 0x6fc) != '\0') {
      dVar10 = (double)(float)(dVar10 * (double)FLOAT_80437628);
    }
    cVar1 = *(char *)(param_1 + 0x655);
    iVar7 = 0;
    *(undefined1 *)(param_1 + 0x655) = 0;
    puVar8 = (uint *)0x802d3970;
    puVar6 = (uint *)0x802d397c;
    iVar5 = 0;
    iVar9 = param_1;
    do {
      fVar4 = FLOAT_8043762c;
      fVar2 = FLOAT_80437628;
      if (*(char *)(*(int *)(param_1 + 0x4b0) + iVar5 + 0xbb) != -1) {
        if (((*(uint *)(param_1 + 0x5e0) & 3) == 0) ||
           ((int)*(char *)(param_1 + 0x584) != iVar5 + 3)) {
          if (((uint)*(byte *)(param_1 + 0x58e) & 1 << iVar5 + 3) == 0) {
            if ((*(uint *)(param_1 + 0x5b4) & *puVar8) == 0) {
              if (*(float *)(*(int *)(param_1 + 0x4ac) + iVar7 + 0x184) <= *(float *)(iVar9 + 0x648)
                 ) {
                *(uint *)(param_1 + 0x5d4) = *(uint *)(param_1 + 0x5d4) | *puVar6;
              }
              fVar4 = FLOAT_80437634;
              fVar2 = FLOAT_8043762c;
              *(float *)(iVar9 + 0x63c) = FLOAT_8043762c;
              *(float *)(iVar9 + 0x648) =
                   -(fVar4 * *(float *)(param_1 + 0x768) - *(float *)(iVar9 + 0x648));
              *(byte *)(param_1 + 0x654) = *(byte *)(param_1 + 0x654) & ~(byte)(1 << iVar5);
              if (*(float *)(iVar9 + 0x648) <= fVar2) {
                *(float *)(iVar9 + 0x648) = fVar2;
              }
            }
            else if (*(float *)(iVar9 + 0x63c) < FLOAT_80437628) {
              *(float *)(iVar9 + 0x63c) = *(float *)(iVar9 + 0x63c) + FLOAT_80437630;
              if (fVar2 < *(float *)(iVar9 + 0x63c)) {
                *(float *)(iVar9 + 0x648) =
                     *(float *)(iVar9 + 0x648) + (*(float *)(iVar9 + 0x63c) - fVar2);
                *(float *)(iVar9 + 0x63c) = fVar2;
              }
            }
            else {
              *(float *)(iVar9 + 0x648) = (float)((double)*(float *)(iVar9 + 0x648) + dVar10);
              bVar3 = (byte)(1 << iVar5);
              *(byte *)(param_1 + 0x654) = *(byte *)(param_1 + 0x654) | bVar3;
              zz_00f0104_(param_1,1,4);
              fVar2 = *(float *)(*(int *)(param_1 + 0x4ac) + iVar7 + 0x184);
              if (fVar2 <= *(float *)(iVar9 + 0x648)) {
                *(float *)(iVar9 + 0x648) = fVar2;
                *(byte *)(param_1 + 0x655) = *(byte *)(param_1 + 0x655) | bVar3;
              }
            }
          }
          else {
            *(float *)(iVar9 + 0x63c) = FLOAT_8043762c;
            *(float *)(iVar9 + 0x648) = fVar4;
            *(byte *)(param_1 + 0x654) = *(byte *)(param_1 + 0x654) & ~(byte)(1 << iVar5);
          }
        }
        else {
          *(float *)(iVar9 + 0x63c) = FLOAT_8043762c;
          *(float *)(iVar9 + 0x648) = fVar4;
          *(byte *)(param_1 + 0x654) = *(byte *)(param_1 + 0x654) & ~(byte)(1 << iVar5);
        }
      }
      iVar5 = iVar5 + 1;
      puVar8 = puVar8 + 1;
      iVar7 = iVar7 + 4;
      puVar6 = puVar6 + 1;
      iVar9 = iVar9 + 4;
    } while (iVar5 < 3);
    if (cVar1 == '\0') {
      if (*(char *)(param_1 + 0x655) != '\0') {
        glxCopyMatrix_float(param_1,0x13);
      }
    }
    else if (*(char *)(param_1 + 0x655) == '\0') {
      glxCopyMatrix_float(param_1,0x14);
    }
  }
  return;
}



// ==== 80068980  zz_0068980_ ====

void zz_0068980_(int param_1,byte *param_2)

{
  uint uVar1;
  byte bVar3;
  int iVar2;
  
  if ((*param_2 & 1) == 0) {
    bVar3 = FUN_8008b73c(*(char *)(param_1 + 0x5ca),*(char *)(param_1 + 0x5cb),0x14);
    if (bVar3 != 0) {
      *param_2 = *param_2 | 1;
      *(ushort *)(param_1 + 0x5d8) = *(ushort *)(param_1 + 0x5d8) & 0xfff0;
      *(ushort *)(param_1 + 0x5d8) = *(ushort *)(param_1 + 0x5d8) | (ushort)bVar3;
      if ((*(ushort *)(param_1 + 0x5d8) & 0xc) == 0) {
        param_2[1] = 2;
      }
      else {
        param_2[1] = 3;
      }
    }
  }
  if ((*param_2 & 2) == 0) {
    bVar3 = FUN_8008b73c(*(char *)(param_1 + 0x5ca),*(char *)(param_1 + 0x5cb),0x34);
    if (bVar3 != 0) {
      *param_2 = *param_2 | 2;
      *(ushort *)(param_1 + 0x5d8) = *(ushort *)(param_1 + 0x5d8) & 0xff0f;
      *(ushort *)(param_1 + 0x5d8) =
           *(ushort *)(param_1 + 0x5d8) | (*(ushort *)(param_1 + 0x5d8) & (ushort)bVar3) << 4;
      param_2[1] = 0x14;
    }
  }
  if ((*param_2 & 8) == 0) {
    uVar1 = *(uint *)(param_1 + 0x5b4) & 0xf0000;
    if (uVar1 != 0) {
      *param_2 = *param_2 | 8;
      *(ushort *)(param_1 + 0x5d8) = *(ushort *)(param_1 + 0x5d8) & 0xf0ff;
      *(ushort *)(param_1 + 0x5d8) =
           *(ushort *)(param_1 + 0x5d8) |
           (ushort)(uVar1 >> 8) & (ushort)((int)(uint)*(ushort *)(param_1 + 0x5d8) >> 4);
      param_2[3] = 0x14;
    }
  }
  else if ((*(uint *)(param_1 + 0x5b4) & 0xf0000) == 0) {
    *param_2 = 0;
    *(ushort *)(param_1 + 0x5d8) = *(ushort *)(param_1 + 0x5d8) & 0xfff;
    *(ushort *)(param_1 + 0x5d8) = *(ushort *)(param_1 + 0x5d8) | *(short *)(param_1 + 0x5b8) << 0xc
    ;
    param_2[2] = 0x10;
  }
  if (param_2[1] != 0) {
    bVar3 = param_2[1] - 1;
    param_2[1] = bVar3;
    if ((char)bVar3 < '\x01') {
      *(ushort *)(param_1 + 0x5d8) = *(ushort *)(param_1 + 0x5d8) & 0xff00;
    }
  }
  if (param_2[3] != 0) {
    bVar3 = param_2[3] - 1;
    param_2[3] = bVar3;
    if ((char)bVar3 < '\x01') {
      *(ushort *)(param_1 + 0x5d8) = *(ushort *)(param_1 + 0x5d8) & 0xf0ff;
    }
  }
  if ((param_2[2] != 0) && (bVar3 = param_2[2] - 1, param_2[2] = bVar3, bVar3 == 0)) {
    *(ushort *)(param_1 + 0x5d8) = *(ushort *)(param_1 + 0x5d8) & 0xfff;
  }
  iVar2 = zz_006de44_(param_1,0xf0f00);
  *(char *)(param_1 + 0x749) = (char)iVar2;
  return;
}



// ==== 80068b8c  zz_0068b8c_ ====

bool zz_0068b8c_(int param_1,undefined4 param_2,byte *param_3,uint param_4)

{
  byte bVar1;
  
  (*(code *)(&PTR_FUN_802d3988)[*param_3])();
  bVar1 = param_3[3];
  if (bVar1 != 0) {
    param_3[3] = bVar1 - 1;
    *(uint *)(param_1 + 0x5d4) = *(uint *)(param_1 + 0x5d4) | param_4;
  }
  return bVar1 != 0;
}



// ==== 80068c14  FUN_80068c14 ====

undefined4 FUN_80068c14(int param_1,short *param_2,undefined1 *param_3)

{
  undefined4 uVar1;
  
  param_3[2] = 0;
  if (*param_2 == 1) {
    *param_3 = 2;
    param_3[1] = 0x7f;
    uVar1 = zz_0068d04_(param_1,(int)param_2,param_3);
  }
  else {
    if ((*(uint *)(param_1 + 0x5bc) & (uint)(ushort)param_2[4]) != 0) {
      *param_3 = 1;
      param_3[2] = 1;
      param_3[1] = (char)param_2[2];
    }
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80068d04  zz_0068d04_ ====

undefined4 zz_0068d04_(int param_1,int param_2,undefined1 *param_3)

{
  char cVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  
  cVar1 = param_3[1];
  param_3[1] = cVar1 + -1;
  if ((char)(cVar1 + -1) < '\x01') {
    *param_3 = 0;
    return 0;
  }
  uVar2 = *(ushort *)(param_2 + 2);
  if (((uVar2 & 2) != 0) && ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0)) {
    return 0;
  }
  if (((uVar2 & 4) != 0) && ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0)) {
    return 0;
  }
  if (((uVar2 & 8) != 0) && ((*(uint *)(param_1 + 0x5b4) & 0xf0000) == 0)) {
    return 0;
  }
  if ((uVar2 & 1) == 0) {
    uVar4 = *(uint *)(param_1 + 0x5bc);
  }
  else {
    uVar4 = *(uint *)(param_1 + 0x5b4);
  }
  uVar3 = (uint)*(ushort *)(param_2 + (uint)(byte)param_3[2] * 2 + 8);
  if ((uVar2 & 0x10) == 0) {
    uVar4 = countLeadingZeros((uVar3 & uVar4) - uVar3);
    uVar4 = uVar4 >> 5;
  }
  else {
    uVar4 = -(uVar4 & uVar3) >> 0x1f;
  }
  if (uVar4 != 0) {
    *param_3 = 0;
    param_3[3] = (char)*(undefined2 *)(param_2 + 6);
    return 1;
  }
  return 0;
}



// ==== 80068df8  FUN_80068df8 ====

/* WARNING: Removing unreachable block (ram,0x80068f80) */
/* WARNING: Removing unreachable block (ram,0x80068e08) */

undefined4 FUN_80068df8(int param_1)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    if (*(char *)(param_1 + 0x4a0) == '\x02') {
      uVar2 = 0;
    }
    else {
      dVar7 = (double)*(float *)(param_1 + 0x24);
      dVar4 = FUN_8003d6e4((double)*(float *)(param_1 + 0x668),param_1,(float *)(param_1 + 0x20));
      *(float *)(param_1 + 0x24) = (float)dVar4;
      fVar1 = *(float *)(param_1 + 0x24) - *(float *)(param_1 + 0x30);
      if ((fVar1 < -*(float *)(param_1 + 0x674)) || (*(char *)(param_1 + 0x732) != '\0')) {
        *(float *)(param_1 + 0x24) = (float)dVar7;
        dVar7 = (double)(*(float *)(param_1 + 0x28) - *(float *)(param_1 + 0x34));
        dVar4 = (double)(*(float *)(param_1 + 0x20) - *(float *)(param_1 + 0x2c));
        dVar6 = (double)(float)(dVar4 * dVar4 + (double)(float)(dVar7 * dVar7));
        if ((double)FLOAT_8043762c < dVar6) {
          dVar5 = 1.0 / SQRT(dVar6);
          dVar5 = DOUBLE_80437638 * dVar5 * -(dVar6 * dVar5 * dVar5 - DOUBLE_80437640);
          dVar5 = DOUBLE_80437638 * dVar5 * -(dVar6 * dVar5 * dVar5 - DOUBLE_80437640);
          dVar6 = (double)(float)(dVar6 * DOUBLE_80437638 * dVar5 *
                                          -(dVar6 * dVar5 * dVar5 - DOUBLE_80437640));
        }
        fVar1 = (float)(dVar6 / (double)*(float *)(param_1 + 0x5f8));
        if (*(float *)(param_1 + 0x44) < fVar1) {
          *(float *)(param_1 + 0x44) = fVar1;
          iVar3 = FUN_800452a0(dVar4,dVar7);
          *(short *)(param_1 + 0x5ae) = (short)iVar3;
        }
        *(float *)(param_1 + 0x698) = FLOAT_80437648;
        zz_006a5a4_(param_1);
        uVar2 = 1;
      }
      else {
        if ((*(float *)(param_1 + 0x674) < fVar1) &&
           ((*(float *)(param_1 + 0x20) != *(float *)(param_1 + 0x2c) ||
            (*(float *)(param_1 + 0x28) != *(float *)(param_1 + 0x34))))) {
          *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x2c);
          *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x30);
          *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x34);
        }
        uVar2 = 0;
      }
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



// ==== 80068f9c  FUN_80068f9c ====

undefined4 FUN_80068f9c(int param_1)

{
  undefined4 uVar1;
  
  if ((*(uint *)(param_1 + 0x5e0) & 2) == 0) {
    if ((*(uint *)(param_1 + 0x5b4) & 0xf0000) == 0) {
      uVar1 = 0;
    }
    else if (*(char *)(param_1 + 0x661) == '\x06') {
      uVar1 = zz_006a750_(param_1,0x1d);
    }
    else {
      uVar1 = zz_006a750_(param_1,1);
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80069000  FUN_80069000 ====

undefined4 FUN_80069000(int param_1)

{
  undefined4 uVar1;
  
  if ((*(uint *)(param_1 + 0x5b4) & 0xf0000) == 0) {
    uVar1 = zz_006a750_(param_1,3);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80069038  zz_0069038_ ====

undefined4 zz_0069038_(int param_1)

{
  undefined4 uVar1;
  
  if ((*(uint *)(param_1 + 0x5e0) & 2) == 0) {
    if ((*(uint *)(param_1 + 0x5d4) & 1) == 0) {
      uVar1 = 0;
    }
    else if ((*(uint *)(param_1 + 0x5b4) & 0x100) == 0) {
      uVar1 = 0;
    }
    else {
      *(undefined1 *)(param_1 + 0x57c) = 0;
      uVar1 = zz_006a750_(param_1,4);
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 800690a0  FUN_800690a0 ====

undefined4 FUN_800690a0(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if ((*(byte *)(param_1 + 0x57a) & 0x40) == 0) {
    uVar1 = 0;
  }
  else if ((*(uint *)(param_1 + 0x5d4) & 1) == 0) {
    uVar1 = 0;
  }
  else if ((*(uint *)(param_1 + 0x5b4) & 0x100) == 0) {
    uVar1 = 0;
  }
  else {
    iVar2 = zz_006a750_(param_1,5);
    if (iVar2 == 0) {
      uVar1 = 0;
    }
    else {
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xff0000;
      zz_005c080_(param_1);
      uVar1 = 1;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x2000;
    }
  }
  return uVar1;
}



// ==== 80069140  FUN_80069140 ====

undefined4 FUN_80069140(int param_1)

{
  undefined4 uVar1;
  
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    uVar1 = 0;
  }
  else if (*(char *)(param_1 + 0x7cd) == '\x01') {
    if (*(char *)(param_1 + 0x588) == '\0') {
      uVar1 = 0;
    }
    else if ((*(short *)(param_1 + 0x736) < 1) || ((*(uint *)(param_1 + 0x5b4) & 0x100) == 0)) {
      if (*(char *)(param_1 + 0x661) == '\x06') {
        uVar1 = zz_006a750_(param_1,0);
      }
      else {
        uVar1 = zz_006a750_(param_1,6);
      }
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 800691d8  FUN_800691d8 ====

undefined4 FUN_800691d8(int param_1)

{
  if (*(char *)(param_1 + 0x4a0) != '\x02') {
    zz_00677b0_(param_1);
  }
  return 0;
}



// ==== 80069210  zz_0069210_ ====

undefined4 zz_0069210_(int param_1)

{
  undefined4 uVar1;
  
  if ((*(uint *)(param_1 + 0x5e0) & 2) == 0) {
    if ((*(uint *)(param_1 + 0x5d4) & 2) == 0) {
      uVar1 = 0;
    }
    else if (*(char *)(param_1 + 0x588) == '\0') {
      uVar1 = 0;
    }
    else {
      if (*(char *)(param_1 + 0x7cd) == '\0') {
        if ((int)(uint)*(byte *)(*(int *)(param_1 + 0x4ac) + 0x9f) <=
            (int)*(char *)(param_1 + 0x747)) {
          return 0;
        }
      }
      else if ((*(char *)(param_1 + 0x7cd) == '\x01') && (*(short *)(param_1 + 0x736) < 1)) {
        return 0;
      }
      uVar1 = zz_006a750_(param_1,8);
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 800692bc  FUN_800692bc ====

undefined4 FUN_800692bc(int param_1)

{
  undefined4 uVar1;
  
  if ((*(uint *)(param_1 + 0x5e0) & 2) == 0) {
    if ((*(uint *)(param_1 + 0x5d4) & 2) == 0) {
      uVar1 = 0;
    }
    else {
      if (*(char *)(param_1 + 0x7cd) == '\0') {
        if ((int)(uint)*(byte *)(*(int *)(param_1 + 0x4ac) + 0x9f) <=
            (int)*(char *)(param_1 + 0x747)) {
          return 0;
        }
      }
      else if ((*(char *)(param_1 + 0x7cd) == '\x01') && (*(short *)(param_1 + 0x736) < 1)) {
        return 0;
      }
      uVar1 = zz_006a750_(param_1,8);
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80069354  FUN_80069354 ====

undefined4 FUN_80069354(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if ((*(uint *)(param_1 + 0x5e0) & 1) == 0) {
    if ((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) {
      uVar1 = 0;
    }
    else {
      if (*(char *)(param_1 + 0x661) == '\x06') {
        iVar2 = zz_006a750_(param_1,0x25);
        if (iVar2 == 0) {
          return 0;
        }
      }
      else {
        iVar2 = zz_006a750_(param_1,0xc);
        if (iVar2 == 0) {
          return 0;
        }
      }
      uVar1 = 1;
      *(byte *)(param_1 + 0x58f) = (byte)(*(ushort *)(param_1 + 0x5d8) >> 4) & 0xf;
      *(ushort *)(param_1 + 0x5d8) = *(ushort *)(param_1 + 0x5d8) & 0xff0f;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 800693fc  FUN_800693fc ====

undefined4 FUN_800693fc(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x661) == '\x02') {
    uVar1 = 0;
  }
  else if (*(char *)(param_1 + 0x661) == '\x05') {
    uVar1 = 0;
  }
  else {
    uVar2 = zz_00694c0_(param_1);
    if (uVar2 == 0) {
      uVar1 = 0;
    }
    else if ((*(uint *)(param_1 + 0x5e0) & 1) == 0) {
      if ((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) {
        uVar1 = 0;
      }
      else {
        iVar3 = zz_006a750_(param_1,0xf);
        if (iVar3 == 0) {
          uVar1 = 0;
        }
        else {
          uVar1 = 1;
          *(byte *)(param_1 + 0x58f) = (byte)(*(ushort *)(param_1 + 0x5d8) >> 4) & 0xf;
          *(ushort *)(param_1 + 0x5d8) = *(ushort *)(param_1 + 0x5d8) & 0xff0f;
        }
      }
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}



// ==== 800694c0  zz_00694c0_ ====

uint zz_00694c0_(int param_1)

{
  if (*(char *)(param_1 + 0x7cd) == '\0') {
    return 1;
  }
  return (uint)(-(int)*(short *)(param_1 + 0x736) & ~(int)*(short *)(param_1 + 0x736)) >> 0x1f;
}



// ==== 800694e8  FUN_800694e8 ====

undefined4 FUN_800694e8(int param_1)

{
  undefined4 uVar1;
  
  if (((*(uint *)(param_1 + 0x5b4) & 0xf0000) == 0) && (*(char *)(param_1 + 0x588) != '\0')) {
    uVar1 = zz_006a750_(param_1,0x11);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 8006952c  FUN_8006952c ====

undefined4 FUN_8006952c(int param_1)

{
  undefined4 uVar1;
  
  if (*(char *)(param_1 + 0x661) == '\x02') {
    if ((*(uint *)(param_1 + 0x5e0) & 2) == 0) {
      if ((*(uint *)(param_1 + 0x5b4) & 0x100) == 0) {
        uVar1 = 0;
      }
      else {
        uVar1 = zz_006a750_(param_1,0x12);
      }
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 8006958c  FUN_8006958c ====

undefined4 FUN_8006958c(int param_1)

{
  undefined4 uVar1;
  
  if ((*(uint *)(param_1 + 0x5b4) & 0x100) == 0) {
    uVar1 = zz_006a750_(param_1,6);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 800695c4  FUN_800695c4 ====

undefined4 FUN_800695c4(int param_1)

{
  undefined4 uVar1;
  
  if (*(char *)(param_1 + 0x661) == '\x02') {
    if ((*(uint *)(param_1 + 0x5e0) & 2) == 0) {
      if ((*(uint *)(param_1 + 0x5b4) & 0xf0000) == 0) {
        uVar1 = 0;
      }
      else {
        uVar1 = zz_006a750_(param_1,0x13);
      }
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80069624  FUN_80069624 ====

undefined4 FUN_80069624(int param_1)

{
  undefined4 uVar1;
  
  if ((*(uint *)(param_1 + 0x5b4) & 0xf0000) == 0) {
    uVar1 = zz_006a750_(param_1,0x15);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



