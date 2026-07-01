// ==== 801113a0  FUN_801113a0 ====

void FUN_801113a0(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  double dVar5;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  if (*(int *)(param_1 + 0xcc) != 0) {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x764) / FLOAT_80439634;
  }
  zz_006ed8c_((double)FLOAT_80439620,param_1);
  FUN_80067310((double)FLOAT_80439624,param_1,*(short *)(param_1 + 0x5ae));
  fVar3 = FLOAT_8043961c;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  dVar4 = DOUBLE_80439688;
  if (fVar2 <= fVar3) {
    dVar5 = (double)FLOAT_80439618;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x44) * dVar4);
    *(float *)(param_1 + 0x4c) = (float)((double)*(float *)(param_1 + 0x4c) * dVar4);
    *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x48) * dVar4);
    *(float *)(param_1 + 0x50) = (float)((double)*(float *)(param_1 + 0x50) * dVar4);
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 801114b0  FUN_801114b0 ====

void FUN_801114b0(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  fVar1 = FLOAT_8043961c;
  if (*(float *)(param_1 + 0x48) < FLOAT_8043961c) {
    *(float *)(param_1 + 0x48) = FLOAT_8043961c;
    *(float *)(param_1 + 0x50) = fVar1;
  }
  FUN_80067310((double)FLOAT_80439624,param_1,*(short *)(param_1 + 0x5ae));
  fVar1 = FLOAT_80439690;
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x48) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  return;
}



// ==== 80111540  FUN_80111540 ====

void FUN_80111540(int param_1)

{
  char cVar1;
  int iVar2;
  double dVar3;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x44) * DOUBLE_80439658);
    *(undefined1 *)(param_1 + 0x541) = 0xff;
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  FUN_80067310((double)FLOAT_80439624,param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  if ((iVar2 != 0) && (*(char *)(param_1 + 0x1cee) != '\0')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_0066530_(param_1,0x2c);
    cVar1 = *(char *)(param_1 + 0x6ea);
    dVar3 = (double)FLOAT_80439618;
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    *(float *)(param_1 + 0x80c) = FLOAT_8043961c;
  }
  return;
}



// ==== 80111630  FUN_80111630 ====

void FUN_80111630(int param_1)

{
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  zz_004cd24_(param_1,0xf);
  if (((*(byte *)(param_1 + 0x746) & *(byte *)(param_1 + 0x745)) != 0) &&
     (*(char *)(param_1 + 0x1cf0) < '\0')) {
    zz_006a3d0_(param_1,'\x01',0,0);
    return;
  }
  zz_006ed8c_((double)FLOAT_80439620,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 801116fc  FUN_801116fc ====

void FUN_801116fc(int param_1)

{
  zz_01c956c_(param_1);
  return;
}



// ==== 8011174c  FUN_8011174c ====

void FUN_8011174c(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80326be4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8011179c  FUN_8011179c ====

void FUN_8011179c(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_80439610;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = 0x18;
  if (*(short *)(param_1 + 1000) == 0x80c) {
    *(undefined1 *)(param_1 + 0x6ea) = 0x19;
  }
  uVar3 = FUN_800668cc((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80439678,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_80439618;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 801118cc  FUN_801118cc ====

void FUN_801118cc(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_80439678,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_8043961c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_80439634;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 80111998  FUN_80111998 ====

void FUN_80111998(int param_1)

{
  double dVar1;
  
  gnt4_PSQUATScale_bl((double)FLOAT_80439678,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    if (*(short *)(param_1 + 1000) == 0x80c) {
      *(float *)(param_1 + 0x558) = FLOAT_80439698;
      *(undefined1 *)(param_1 + 0x6f7) = 0x38;
      zz_01005ec_(param_1,1);
    }
    dVar1 = zz_0045238_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_80439650 * dVar1);
    dVar1 = zz_0045204_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_80439650 * -dVar1);
  }
  return;
}



// ==== 80111a88  FUN_80111a88 ====

void FUN_80111a88(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x18da));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_80439650 * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x18da));
  dVar5 = (double)FLOAT_80439624;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_80439650 * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  iVar3 = zz_00677b0_(param_1);
  fVar2 = FLOAT_8043961c;
  if ((iVar3 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80439624 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(short *)(param_1 + 1000) == 0x80c) {
    *(undefined1 *)(param_1 + 0x6f7) = 0x38;
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar1 <= fVar2) goto LAB_80111b8c;
  }
  if (*(char *)(param_1 + 0x1cee) == '\0') {
    return;
  }
LAB_80111b8c:
  *(undefined1 *)(param_1 + 0x6f7) = 0;
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a5a4_(param_1);
  return;
}



// ==== 80111bc0  FUN_80111bc0 ====

void FUN_80111bc0(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80326bf4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80111c1c  FUN_80111c1c ====

void FUN_80111c1c(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar2 = FLOAT_8043961c;
  fVar1 = FLOAT_80439610;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = 0xe;
  *(undefined1 *)(param_1 + 0x6eb) = 0;
  *(float *)(param_1 + 0x50) = fVar2;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80439678,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_80439618,param_1,0xf,3,(int)*(char *)(param_1 + 0x6ea),0xffffffff,
              0xffffffff);
  return;
}



// ==== 80111d7c  FUN_80111d7c ====

void FUN_80111d7c(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80439678,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  fVar2 = FLOAT_8043961c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    fVar2 = FLOAT_80439634;
    fVar1 = FLOAT_8043961c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar3 = FLOAT_80439650;
    *(float *)(param_1 + 0x558) = fVar2;
    *(float *)(param_1 + 0x38) = fVar1;
    *(float *)(param_1 + 0x40) = fVar3;
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 80111e54  FUN_80111e54 ====

void FUN_80111e54(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x38) =
       FLOAT_8043969c * *(float *)(param_1 + 0x1dc8) + *(float *)(param_1 + 0x38);
  if (*(float *)(param_1 + 0x40) < *(float *)(param_1 + 0x38)) {
    *(float *)(param_1 + 0x38) = *(float *)(param_1 + 0x40);
  }
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x38) * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x54e));
  dVar5 = (double)FLOAT_80439624;
  *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x38) * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043961c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_800668cc((double)FLOAT_8043963c,param_1), 0 < (int)uVar3)) {
    dVar4 = DOUBLE_804396a0;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x44) * dVar4);
    *(float *)(param_1 + 0x4c) = (float)((double)*(float *)(param_1 + 0x4c) * dVar4);
    *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x48) * dVar4);
    *(float *)(param_1 + 0x50) = (float)((double)*(float *)(param_1 + 0x50) * dVar4);
  }
  return;
}



// ==== 80111f9c  FUN_80111f9c ====

void FUN_80111f9c(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  fVar1 = FLOAT_8043961c;
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(undefined1 *)(param_1 + 0x745) = 1;
    *(float *)(param_1 + 0x50) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
    *(undefined2 *)(param_1 + 0x80) = 0;
    *(undefined2 *)(param_1 + 0x7e) = 0;
    *(undefined2 *)(param_1 + 0x7c) = 0;
  }
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d144_(param_1,0xc0);
    zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  }
  if ((*(char *)(param_1 + 0x1cf0) < '\0') &&
     ((*(byte *)(param_1 + 0x746) & *(byte *)(param_1 + 0x745)) != 0)) {
    dVar3 = (double)FLOAT_80439618;
    *(undefined1 *)(param_1 + 0x746) = 0;
    *(undefined1 *)(param_1 + 0x745) = 0;
    *(char *)(param_1 + 0x6eb) = *(char *)(param_1 + 0x6eb) + '\x01';
    *(byte *)(param_1 + 0x6eb) = *(byte *)(param_1 + 0x6eb) & 1;
    zz_004beb8_(dVar3,param_1,0xf,3,
                (int)*(char *)(param_1 + 0x6ea) + (int)*(char *)(param_1 + 0x6eb),0xffffffff,
                0xffffffff);
    return;
  }
  if ('\0' < *(char *)(param_1 + 0x1d0f)) {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    dVar3 = zz_0045238_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_80439650 * dVar3);
    dVar3 = zz_0045204_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_80439650 * -dVar3);
    zz_0092dcc_(param_1,0);
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  zz_006ed8c_((double)FLOAT_80439678,param_1);
  FUN_80067310((double)FLOAT_80439624,param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  if ((iVar2 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80439624 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 801121c0  FUN_801121c0 ====

void FUN_801121c0(int param_1)

{
  (*(code *)(&PTR_FUN_80326c04)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801121fc  FUN_801121fc ====

void FUN_801121fc(int param_1)

{
  double dVar1;
  float fVar2;
  
  fVar2 = FLOAT_804396a8;
  dVar1 = DOUBLE_80439628;
  *(byte *)(param_1 + 0x597) = *(byte *)(param_1 + 0x597) | 4;
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) - dVar1
                           ) * fVar2);
  (*(code *)(&PTR_FUN_80434530)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80112278  FUN_80112278 ====

void FUN_80112278(int param_1)

{
  char cVar1;
  double dVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 1;
  }
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar2 = (double)FLOAT_80439618;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar2,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  zz_011230c_(param_1);
  return;
}



// ==== 8011230c  zz_011230c_ ====

void zz_011230c_(int param_1)

{
  float fVar1;
  double dVar2;
  
  gnt4_PSQUATScale_bl((double)FLOAT_80439678,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    if (0 < *(short *)(param_1 + 0x144)) goto LAB_801123c4;
    *(undefined2 *)(param_1 + 0x144) = 0x4b0;
    apply_actor_param_tier_delta_127(param_1,4);
    zz_00f036c_(param_1,0xa5);
    *(undefined1 *)(param_1 + 0x146) = 0x1e;
    zz_00107a0_(param_1,0xf);
  }
  if (*(char *)(param_1 + 0x1cee) == '\0') {
    return;
  }
  *(undefined2 *)(param_1 + 0x144) = 0x4b0;
  *(undefined1 *)(param_1 + 0x146) = 0;
LAB_801123c4:
  fVar1 = FLOAT_8043961c;
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_1 + 0x3c);
  *(float *)(param_1 + 0x3c) = fVar1;
  dVar2 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  *(float *)(param_1 + 0x44) = (float)dVar2;
  *(float *)(param_1 + 0x4c) = FLOAT_8043961c;
  *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_006a474_(param_1);
  }
  else {
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 8011243c  zz_011243c_ ====

void zz_011243c_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0x18,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x16;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_801126c4;
    *(code **)(puVar1 + 0x10c) = FUN_80112990;
    *(int *)(puVar1 + 0x8c) = param_1;
    *(undefined4 *)(puVar1 + 0x90) = *(undefined4 *)(param_1 + 0x90);
    *(undefined2 *)(puVar1 + 0x94) = *(undefined2 *)(param_1 + 0x94);
    puVar1[0x96] = *(undefined1 *)(param_1 + 0x96);
    puVar1[0x97] = *(undefined1 *)(param_1 + 0x97);
    puVar1[0x88] = *(undefined1 *)(param_1 + 0x88);
    *(undefined4 *)(puVar1 + 200) = *(undefined4 *)(param_1 + 200);
    *(undefined4 *)(puVar1 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
    *(undefined4 *)(puVar1 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
    *(undefined4 *)(puVar1 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
    *(undefined4 *)(puVar1 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
    puVar1[0xd0] = *(undefined1 *)(param_1 + 0xd0);
  }
  return;
}



// ==== 80112534  FUN_80112534 ====

undefined4 FUN_80112534(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if ((FLOAT_804396b0 == *(float *)(param_1 + 0x80c)) ||
     (FLOAT_804396b4 <= *(float *)(param_1 + 0x80c))) {
    *(float *)(param_1 + 0x80c) = FLOAT_804396b0;
    uVar1 = zz_011243c_(param_1,0);
  }
  *(float *)(param_1 + 0x80c) = *(float *)(param_1 + 0x80c) + *(float *)(param_1 + 0x768);
  return uVar1;
}



// ==== 801125a4  FUN_801125a4 ====

undefined4 FUN_801125a4(int param_1)

{
  undefined4 uVar1;
  double dVar2;
  double dVar3;
  
  uVar1 = 0;
  if ((FLOAT_804396b0 != *(float *)(param_1 + 0x80c)) &&
     (*(float *)(param_1 + 0x80c) < FLOAT_804396b8)) {
    dVar2 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x800));
    if ((double)FLOAT_804396b0 < dVar2) {
      dVar3 = 1.0 / SQRT(dVar2);
      dVar3 = DOUBLE_804396c0 * dVar3 * -(dVar2 * dVar3 * dVar3 - DOUBLE_804396c8);
      dVar3 = DOUBLE_804396c0 * dVar3 * -(dVar2 * dVar3 * dVar3 - DOUBLE_804396c8);
      dVar2 = (double)(float)(dVar2 * DOUBLE_804396c0 * dVar3 *
                                      -(dVar2 * dVar3 * dVar3 - DOUBLE_804396c8));
    }
    if (dVar2 < (double)(FLOAT_804396d0 * *(float *)(param_1 + 0xb4))) goto LAB_80112694;
  }
  *(float *)(param_1 + 0x80c) = FLOAT_804396b0;
  *(float *)(param_1 + 0x800) = *(float *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x804) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x808) = *(undefined4 *)(param_1 + 0x28);
  uVar1 = zz_011243c_(param_1,2);
LAB_80112694:
  *(float *)(param_1 + 0x80c) = *(float *)(param_1 + 0x80c) + *(float *)(param_1 + 0x768);
  return uVar1;
}



// ==== 801126c4  FUN_801126c4 ====

void FUN_801126c4(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_80327428)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 80112750  FUN_80112750 ====

void FUN_80112750(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 extraout_r4;
  int iVar4;
  int iVar5;
  double dVar6;
  undefined8 uVar7;
  float local_18 [2];
  
  iVar5 = *(int *)(param_9 + 0x8c);
  iVar4 = (int)*(char *)(param_9 + 0x11);
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x13) = 0;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(undefined2 *)(param_9 + 0x1e) = *(undefined2 *)(&DAT_803273fa + iVar4 * 0xc);
  if (*(char *)(param_9 + 0x19) == '\0') {
    uVar2 = *(undefined4 *)(iVar5 + 0x24);
    *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(iVar5 + 0x20);
    *(undefined4 *)(param_9 + 0x24) = uVar2;
    *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(iVar5 + 0x28);
  }
  dVar6 = FUN_8003d6e4((double)*(float *)(iVar5 + 0x668),iVar5,(float *)(param_9 + 0x20));
  *(float *)(param_9 + 0x24) = (float)dVar6;
  dVar6 = (double)*(float *)(iVar5 + 0x24);
  fVar1 = (float)(dVar6 - (double)*(float *)(param_9 + 0x24));
  if (fVar1 < FLOAT_804396b0) {
    fVar1 = -fVar1;
  }
  if (FLOAT_804396d4 <= fVar1) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined2 *)(param_9 + 0x74) = 0;
    *(undefined2 *)(param_9 + 0x70) = 0;
    uVar3 = zz_00055fc_();
    *(short *)(param_9 + 0x72) = (short)(uVar3 << 8);
    *(code **)(param_9 + 0x100) = FUN_801129ec;
    zz_0089100_(param_9,1,1);
    zz_0018f88_((int *)(param_9 + 0x144),(int)(&PTR_DAT_803273fc)[iVar4 * 3],
                (float *)(param_9 + 0x58));
    gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0xb4),(float *)(param_9 + 0x58),
                        (float *)(param_9 + 0x58));
    uVar7 = zz_0019338_((int *)(param_9 + 0x14c),(int)(&PTR_DAT_80327400)[iVar4 * 3],local_18);
    iVar5 = zz_0006f78_(*(int *)(param_9 + 0x90));
    iVar4 = (int)*(short *)(&DAT_803273f8 + iVar4 * 0xc);
    zz_0006fb4_(uVar7,dVar6,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                *(int *)(param_9 + 0xe0),iVar4,param_12,param_13,param_14,param_15,param_16);
    FUN_80112ac8((double)local_18[0],dVar6,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                 extraout_r4,iVar4,param_12,param_13,param_14,param_15,param_16);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  }
  return;
}



// ==== 801128c8  FUN_801128c8 ====

void FUN_801128c8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  int iVar2;
  float *pfVar3;
  float local_18 [4];
  
  sVar1 = *(short *)(param_9 + 0x1c) + 1;
  *(short *)(param_9 + 0x1c) = sVar1;
  if (*(short *)(param_9 + 0x1e) <= sVar1) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  zz_0018fd8_((int *)(param_9 + 0x144),(int)*(short *)(param_9 + 0x1c),(float *)(param_9 + 0x58));
  gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0xb4),(float *)(param_9 + 0x58),
                      (float *)(param_9 + 0x58));
  iVar2 = (int)*(short *)(param_9 + 0x1c);
  pfVar3 = local_18;
  zz_0019370_((int *)(param_9 + 0x14c),iVar2,pfVar3);
  FUN_80112ac8((double)local_18[0],param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
               iVar2,pfVar3,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8011295c  FUN_8011295c ====

void FUN_8011295c(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 80112970  FUN_80112970 ====

void FUN_80112970(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80112990  FUN_80112990 ====

void FUN_80112990(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  if (*(char *)(param_9 + 0x13) == '\0') {
    zz_00097b4_(*(int *)(param_9 + 0xe0),1);
  }
  else {
    zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  }
  return;
}



// ==== 801129ec  FUN_801129ec ====

void FUN_801129ec(int param_1)

{
  bool bVar1;
  int iVar2;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  iVar2 = *(int *)(param_1 + 0x8c);
  if (*(char *)(param_1 + 0x11) == '\x03') {
    local_18 = *(undefined4 *)(iVar2 + 0x968);
    local_14 = *(undefined4 *)(iVar2 + 0x978);
    local_10 = *(undefined4 *)(iVar2 + 0x988);
    bVar1 = zz_0045ef4_((float *)(param_1 + 0x114),3,&local_18,&DAT_802b0cc0);
    if (bVar1) {
      zz_0045ef4_((float *)(param_1 + 0x114),2,&local_18,&DAT_802b0ca8);
    }
    *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  }
  else {
    gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),(double)*(float *)(param_1 + 0x24),
                       (double)*(float *)(param_1 + 0x28),(float *)(param_1 + 0x114));
  }
  zz_00457d4_('y',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x72));
  zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),(float *)(param_1 + 0x58));
  return;
}



// ==== 80112ac8  FUN_80112ac8 ====

/* WARNING: Removing unreachable block (ram,0x80112b28) */
/* WARNING: Removing unreachable block (ram,0x80112ad8) */

void FUN_80112ac8(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  if (((double)FLOAT_804396d8 != param_1) && (*(char *)(param_9 + 0x13) == '\0')) {
    *(undefined1 *)(param_9 + 0x13) = 1;
    zz_0007c54_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),param_10,param_11,param_12,param_13,param_14,param_15,
                param_16);
  }
  if (*(char *)(param_9 + 0x13) != '\0') {
    zz_0007cac_(param_1,*(int *)(param_9 + 0xe0));
  }
  return;
}



// ==== 80112c64  FUN_80112c64 ====

void FUN_80112c64(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x402) {
    zz_010dde0_(param_1,0);
    zz_010dde0_(param_1,1);
  }
  else if (sVar1 == 0x407) {
    zz_01a4d9c_(param_1);
  }
  else if (sVar1 == 0x408) {
    zz_010dde0_(param_1,2);
    zz_010dde0_(param_1,3);
  }
  *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x148) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(param_1 + 0x28);
  *(undefined1 *)(param_1 + 0x150) = 0;
  zz_00c74ec_(param_1,0xc);
  return;
}



// ==== 80112d08  FUN_80112d08 ====

void FUN_80112d08(int param_1)

{
  int iVar1;
  
  if (*(short *)(param_1 + 1000) == 0x407) {
    if (*(char *)(param_1 + 0x150) == '\0') {
      if (*(short *)(param_1 + 0x784) < 1) {
        zz_006de10_(param_1,2);
      }
    }
    else if ((*(char *)(param_1 + 0x150) == '\x01') &&
            (iVar1 = zz_006dbe0_(param_1,2,1,0), iVar1 != 0)) {
      *(undefined1 *)(param_1 + 0x150) = 0;
    }
    if (*(short *)(param_1 + 0x79e) <= *(short *)(param_1 + 0x784)) {
      *(float *)(param_1 + 0x788) = FLOAT_804396e0;
    }
  }
  return;
}



// ==== 80112da8  FUN_80112da8 ====

void FUN_80112da8(int param_1)

{
  int iVar1;
  
  if (*(short *)(param_1 + 1000) == 0x407) {
    if (((*(uint *)(param_1 + 0x5e0) & 0x2000000) != 0) &&
       ((*(uint *)(param_1 + 0x5e0) & 0x80000000) == 0)) {
      iVar1 = zz_006dbe0_(param_1,2,1,1);
      if ((iVar1 != 0) && (*(char *)(param_1 + 0x150) == '\0')) {
        *(undefined1 *)(param_1 + 0x150) = 1;
        FUN_801b8b6c(param_1,0x80);
      }
    }
  }
  return;
}



// ==== 80112e28  FUN_80112e28 ====

void FUN_80112e28(int param_1)

{
  uint uVar1;
  
  if (((*(short *)(param_1 + 1000) == 0x407) && (*(char *)(param_1 + 0x150) == '\x02')) &&
     (uVar1 = zz_006ab9c_(param_1), uVar1 != 0)) {
    zz_006a3d0_(param_1,'\x05',0,0);
  }
  return;
}



// ==== 80112e90  FUN_80112e90 ====

void FUN_80112e90(int param_1)

{
  (*(code *)(&PTR_FUN_80327f38)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80112ecc  FUN_80112ecc ====

void FUN_80112ecc(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x402) {
    zz_0112f00_(param_1);
  }
  else {
    zz_0112fe8_(param_1);
  }
  return;
}



// ==== 80112f00  zz_0112f00_ ====

void zz_0112f00_(int param_1)

{
  zz_00f1e30_(param_1,&DAT_80327f48);
  return;
}



// ==== 80112f28  FUN_80112f28 ====

void FUN_80112f28(int param_1)

{
  int iVar1;
  
  iVar1 = zz_006dbe0_(param_1,0,1,1);
  if (iVar1 != 0) {
    zz_00c3be0_(param_1,0xc);
    zz_00c3be0_(param_1,0xd);
  }
  return;
}



// ==== 80112f80  FUN_80112f80 ====

undefined4 FUN_80112f80(int param_1)

{
  int iVar1;
  
  if (((*(char *)(param_1 + 0x1cef) < '\0') && (iVar1 = zz_006dbe0_(param_1,0,1,0), iVar1 != 0)) &&
     ((*(uint *)(param_1 + 0x5bc) & 0x200) != 0)) {
    return 0x8444;
  }
  return 0;
}



// ==== 80112fe8  zz_0112fe8_ ====

void zz_0112fe8_(int param_1)

{
  zz_00f1e30_(param_1,&DAT_80327f5c);
  return;
}



// ==== 80113010  FUN_80113010 ====

void FUN_80113010(int param_1)

{
  int iVar1;
  
  *(float *)(param_1 + 0x558) = FLOAT_804396e4;
  *(char *)(param_1 + 0x6ef) = *(char *)(param_1 + 0x6ef) + -1;
  iVar1 = zz_006dbe0_(param_1,0,1,1);
  if (iVar1 != 0) {
    if (*(short *)(param_1 + 1000) == 0x408) {
      zz_0082824_(param_1,0x47);
      zz_0082824_(param_1,0x48);
    }
    else if (*(short *)(param_1 + 1000) == 0x407) {
      zz_0082824_(param_1,0x78);
      zz_0082824_(param_1,0x79);
    }
  }
  return;
}



// ==== 801130ac  FUN_801130ac ====

undefined4 FUN_801130ac(int param_1)

{
  int iVar1;
  
  if (*(float *)(param_1 + 0x558) <= FLOAT_804396e0) {
    iVar1 = zz_006dbe0_(param_1,0,1,0);
    if ((iVar1 != 0) && ('\0' < *(char *)(param_1 + 0x6ef))) {
      return 0x8444;
    }
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  return 0;
}



// ==== 80113128  FUN_80113128 ====

void FUN_80113128(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_804396f0;
  fVar1 = FLOAT_804396e8;
  *(short *)(param_1 + 0x18e0) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e0) ^ 0x80000000) -
                           DOUBLE_804396f0) * FLOAT_804396e8);
  *(short *)(param_1 + 0x18e2) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e2) ^ 0x80000000) - dVar2
                           ) * fVar1);
  (*(code *)(&PTR_FUN_80327f70)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801131c8  FUN_801131c8 ====

void FUN_801131c8(int param_1)

{
  zz_00f2374_(param_1);
  return;
}



// ==== 801131ec  FUN_801131ec ====

void FUN_801131ec(int param_1)

{
  zz_00f2c3c_(param_1);
  return;
}



// ==== 80113210  FUN_80113210 ====

void FUN_80113210(int param_1)

{
  zz_00f33f4_(param_1);
  return;
}



// ==== 80113234  FUN_80113234 ====

void FUN_80113234(int param_1)

{
  zz_00f3738_(param_1);
  return;
}



// ==== 80113258  FUN_80113258 ====

void FUN_80113258(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_804396f0;
  fVar1 = FLOAT_804396e8;
  *(short *)(param_1 + 0x18e0) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e0) ^ 0x80000000) -
                           DOUBLE_804396f0) * FLOAT_804396e8);
  *(short *)(param_1 + 0x18e2) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e2) ^ 0x80000000) - dVar2
                           ) * fVar1);
  (*(code *)(&PTR_FUN_80327f84)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801132f8  FUN_801132f8 ====

void FUN_801132f8(int param_1)

{
  (*(code *)(&PTR_FUN_80327f98)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80113334  FUN_80113334 ====

void FUN_80113334(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  fVar2 = FLOAT_804396e0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x50) = fVar2;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804396f8,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 1;
  }
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_804396fc;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 8011340c  FUN_8011340c ====

void FUN_8011340c(int param_1)

{
  short sVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  zz_004cd24_(param_1,0xf);
  if (*(short *)(param_1 + 1000) == 0x407) {
    zz_006d144_(param_1,0xc0);
  }
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    iVar4 = zz_006dbe0_(param_1,2,1,1);
    if (iVar4 == 0) {
      zz_00f036c_(param_1,0x24);
    }
    else {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x402) {
        zz_01138c0_(param_1,0,0);
      }
      else if (sVar1 == 0x407) {
        if (*(char *)(param_1 + 0x150) == '\0') {
          *(undefined1 *)(param_1 + 0x150) = 1;
          FUN_801b8b6c(param_1,0);
        }
      }
      else if (sVar1 == 0x408) {
        zz_01138c0_(param_1,1,1);
      }
    }
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  FUN_80067310((double)FLOAT_80439700,param_1,*(short *)(param_1 + 0x5ae));
  gnt4_PSQUATScale_bl((double)FLOAT_804396f8,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  iVar4 = zz_00677b0_(param_1);
  fVar3 = FLOAT_80439704;
  fVar2 = FLOAT_804396e0;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    if (iVar4 == 0) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(float *)(param_1 + 0x558) = fVar3;
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    }
    else {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(float *)(param_1 + 0x44) = fVar2;
      zz_006a474_(param_1);
    }
  }
  return;
}



// ==== 8011359c  FUN_8011359c ====

void FUN_8011359c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_80439700,param_1,*(short *)(param_1 + 0x5ae));
  gnt4_PSQUATScale_bl((double)FLOAT_804396f8,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  iVar3 = zz_00677b0_(param_1);
  fVar2 = FLOAT_804396e0;
  if (iVar3 == 0) {
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar1 <= fVar2) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_804396e4 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 8011367c  FUN_8011367c ====

void FUN_8011367c(int param_1)

{
  *(short *)(param_1 + 0x18e0) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e0) ^ 0x80000000) -
                           DOUBLE_804396f0) * FLOAT_804396e8);
  zz_01136d4_(param_1);
  return;
}



// ==== 801136d4  zz_01136d4_ ====

void zz_01136d4_(int param_1)

{
  (*(code *)(&PTR_FUN_80434538)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8011370c  FUN_8011370c ====

void FUN_8011370c(int param_1)

{
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_01137e8_(param_1);
  *(undefined1 *)(param_1 + 0x543) = 1;
  if (*(char *)(param_1 + 0x5db) == '\x01') {
    *(undefined1 *)(param_1 + 0x543) = 0xf;
  }
  zz_004beb8_((double)FLOAT_804396fc,param_1,(int)*(char *)(param_1 + 0x543),4,2,0xffffffff,
              0xffffffff);
  return;
}



// ==== 80113784  FUN_80113784 ====

void FUN_80113784(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_004cd24_(param_9,1);
  zz_01137e8_(param_9);
  if (*(char *)(param_9 + 0x1cee) != '\0') {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 801137e8  zz_01137e8_ ====

undefined4 zz_01137e8_(int param_1)

{
  short sVar1;
  short sVar2;
  int iVar3;
  short sVar5;
  undefined4 uVar4;
  float local_28 [2];
  float local_20;
  
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x144),(float *)(param_1 + 0x20),local_28);
  iVar3 = FUN_800452a0((double)local_28[0],(double)local_20);
  sVar5 = (short)iVar3 - *(short *)(param_1 + 0x72);
  sVar1 = sVar5 - *(short *)(param_1 + 0x18e2);
  iVar3 = (int)sVar1;
  sVar2 = (short)(int)((float)((double)CONCAT44(0x43300000,
                                                (int)*(short *)(*(int *)(param_1 + 0x4ac) + 0xae) ^
                                                0x80000000) - DOUBLE_804396f0) *
                      *(float *)(param_1 + 0x1dc8));
  if (iVar3 < 0) {
    iVar3 = -iVar3;
  }
  if (sVar2 < iVar3) {
    if (sVar1 < 0) {
      sVar2 = -sVar2;
    }
    uVar4 = 0;
    *(short *)(param_1 + 0x18e2) = *(short *)(param_1 + 0x18e2) + sVar2;
  }
  else {
    *(short *)(param_1 + 0x18e2) = sVar5;
    uVar4 = 1;
  }
  return uVar4;
}



// ==== 801138c0  zz_01138c0_ ====

bool zz_01138c0_(int param_1,undefined1 param_2,undefined1 param_3)

{
  bool bVar2;
  undefined1 *puVar1;
  
  if ((*(short *)(param_1 + 1000) == 0x402) || (*(short *)(param_1 + 1000) == 0x408)) {
    puVar1 = zz_0088aa0_(param_1,3,0x20,0,1);
    if (puVar1 == (undefined1 *)0x0) {
      zz_006de10_(param_1,2);
    }
    else {
      *puVar1 = 1;
      puVar1[0x11] = param_2;
      puVar1[0x13] = param_3;
      puVar1[0x10] = 0x27;
      *(code **)(puVar1 + 0xc) = FUN_80113a04;
      *(code **)(puVar1 + 0x10c) = FUN_80114340;
      *(int *)(puVar1 + 0x8c) = param_1;
      *(undefined4 *)(puVar1 + 0x90) = *(undefined4 *)(param_1 + 0x90);
      *(undefined2 *)(puVar1 + 0x94) = *(undefined2 *)(param_1 + 0x94);
      puVar1[0x96] = *(undefined1 *)(param_1 + 0x96);
      puVar1[0x97] = *(undefined1 *)(param_1 + 0x97);
      puVar1[0x88] = *(undefined1 *)(param_1 + 0x88);
      *(undefined4 *)(puVar1 + 200) = *(undefined4 *)(param_1 + 200);
      *(undefined4 *)(puVar1 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
      *(undefined4 *)(puVar1 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
      *(undefined4 *)(puVar1 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(puVar1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(puVar1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(puVar1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(puVar1 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
      *(undefined4 *)(puVar1 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
      puVar1[0xd0] = *(undefined1 *)(param_1 + 0xd0);
    }
    bVar2 = puVar1 != (undefined1 *)0x0;
  }
  else {
    bVar2 = false;
  }
  return bVar2;
}



// ==== 80113a04  FUN_80113a04 ====

void FUN_80113a04(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x90);
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(iVar1 + 0x18) || (*(short *)(iVar1 + 1000) != *(short *)(param_1 + 0x94)))
     )) {
    zz_006de10_(iVar1,2);
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_803284c8)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80113aa4  FUN_80113aa4 ====

void FUN_80113aa4(int param_1)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined *puVar6;
  int iVar7;
  undefined *puVar8;
  uint uVar9;
  int iVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  puVar8 = &DAT_803284a8;
  puVar6 = &DAT_80328478;
  *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  uVar9 = (uint)*(byte *)(param_1 + 0x11);
  iVar10 = *(int *)(param_1 + 0x90);
  iVar7 = *(char *)(param_1 + 0x13) * 0x18;
  *(undefined1 *)(param_1 + 0x84) = 0x1e;
  iVar5 = uVar9 * 0x10;
  *(code **)(param_1 + 0x100) = FUN_800480f4;
  iVar4 = iVar7;
  zz_0089100_(param_1,0,1);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar10 + *(short *)(&DAT_8032847a + iVar7) * 0x30 + 0x8d4),
             (float *)(iVar7 + -0x7fcd7b84),(float *)(param_1 + 0x20));
  *(undefined4 *)(param_1 + 0x38) =
       *(undefined4 *)(iVar10 + *(short *)(&DAT_8032847a + iVar7) * 0x30 + 0x8dc);
  *(undefined4 *)(param_1 + 0x3c) =
       *(undefined4 *)(iVar10 + *(short *)(&DAT_8032847a + iVar7) * 0x30 + 0x8ec);
  *(undefined4 *)(param_1 + 0x40) =
       *(undefined4 *)(iVar10 + *(short *)(&DAT_8032847a + iVar7) * 0x30 + 0x8fc);
  gnt4_PSQUATScale_bl((double)*(float *)(&DAT_803284ac + iVar5),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(&DAT_803284ac + iVar5);
  *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(&DAT_803284b0 + iVar5);
  *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(&DAT_803284b4 + iVar5);
  *(undefined2 *)(param_1 + 0x1c4) = *(undefined2 *)(&DAT_803284aa + iVar5);
  *(undefined2 *)(param_1 + 0x1c6) = *(undefined2 *)(param_1 + 0x1c4);
  *(undefined2 *)(param_1 + 0x1c8) = *(undefined2 *)(param_1 + 0x1c4);
  *(undefined2 *)(param_1 + 0x70) = 0;
  *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(iVar10 + 0x72);
  uVar2 = zz_00055fc_();
  if ((uVar2 & 1) == 0) {
    *(undefined2 *)(param_1 + 0x1c) = 1;
    *(undefined2 *)(param_1 + 0x74) = 0xc000;
  }
  else {
    *(undefined2 *)(param_1 + 0x1c) = 0;
    *(undefined2 *)(param_1 + 0x74) = 0x4000;
  }
  dVar12 = (double)FLOAT_80439708;
  *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(param_1 + 0xb4);
  fVar1 = FLOAT_80439710;
  dVar11 = (double)FLOAT_8043970c;
  dVar13 = (double)*(float *)(param_1 + 0x144);
  *(float *)(param_1 + 0x144) = (float)(dVar13 * dVar12);
  dVar12 = (double)*(float *)(param_1 + 0xb4);
  *(float *)(param_1 + 0xb4) = (float)(dVar12 * dVar11);
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(param_1 + 0xb4);
  dVar11 = (double)*(float *)(param_1 + 0xb4);
  *(float *)(param_1 + 0xc4) = *(float *)(param_1 + 0xb4);
  *(float *)(param_1 + 0x204) = fVar1;
  *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 1;
  *(undefined4 *)(*(int *)(param_1 + 0xe0) + 0x18) = 0xff;
  *(undefined4 *)(*(int *)(param_1 + 0xe0) + 0x1c) = 0xffffffff;
  iVar3 = zz_0006f98_(iVar10);
  zz_0007030_(dVar11,dVar12,dVar13,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar3 + 0x600),
              *(int *)(param_1 + 0xe0),(int)*(short *)(&DAT_80328478 + iVar7),
              *(int *)(param_1 + 0xe0) + 0x18,puVar6,iVar4,puVar8,uVar9);
  *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + '1';
  iVar4 = zz_008ac80_(param_1,(int)(char)(&DAT_803284a8)[iVar5]);
  if ((iVar4 == 0) || (iVar5 = zz_008ac80_(param_1,(int)(char)(&DAT_803284a9)[iVar5]), iVar5 == 0))
  {
    zz_006de10_(iVar10,2);
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  else {
    zz_00f036c_(param_1,0xf3);
  }
  return;
}



// ==== 80113d20  FUN_80113d20 ====

/* WARNING: Removing unreachable block (ram,0x801142ac) */
/* WARNING: Removing unreachable block (ram,0x801142a4) */
/* WARNING: Removing unreachable block (ram,0x80113d38) */
/* WARNING: Removing unreachable block (ram,0x80113d30) */

void FUN_80113d20(int param_1)

{
  float fVar1;
  char cVar2;
  bool bVar3;
  float fVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  double in_f31;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float afStack_5c [3];
  float afStack_50 [7];
  
  if (*(char *)(param_1 + 0x1da) == '\0') {
    *(undefined4 *)(*(int *)(param_1 + 0xe0) + 0x18) = 0xff;
  }
  else {
    *(undefined4 *)(*(int *)(param_1 + 0xe0) + 0x18) = 0xc0c0c0ff;
  }
  if (*(float *)(param_1 + 0x20) <= *(float *)(DAT_8043625c + 0x38)) {
    if (*(float *)(param_1 + 0x20) < *(float *)(DAT_8043625c + 0x3c)) {
      *(float *)(param_1 + 0x20) = *(float *)(DAT_8043625c + 0x3c);
    }
  }
  else {
    *(float *)(param_1 + 0x20) = *(float *)(DAT_8043625c + 0x38);
  }
  if (*(float *)(param_1 + 0x28) <= *(float *)(DAT_8043625c + 0x40)) {
    if (*(float *)(param_1 + 0x28) < *(float *)(DAT_8043625c + 0x44)) {
      *(float *)(param_1 + 0x28) = *(float *)(DAT_8043625c + 0x44);
    }
  }
  else {
    *(float *)(param_1 + 0x28) = *(float *)(DAT_8043625c + 0x40);
  }
  iVar5 = zz_0083244_((float *)(param_1 + 0x20));
  if (iVar5 == 0) {
    if (*(short *)(param_1 + 0x1c6) < 1) {
      zz_01142c8_(param_1);
      FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
    }
    else {
      if (*(short *)(param_1 + 0x1c) == 0) {
        *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + -0x400;
        if (*(short *)(param_1 + 0x74) < 1) {
          *(undefined2 *)(param_1 + 0x74) = 0;
        }
      }
      else {
        *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + 0x400;
        if (-1 < *(short *)(param_1 + 0x74)) {
          *(undefined2 *)(param_1 + 0x74) = 0;
        }
      }
      if (*(float *)(param_1 + 0xb4) < *(float *)(param_1 + 0x144)) {
        *(float *)(param_1 + 0xb4) = *(float *)(param_1 + 0xb4) * FLOAT_80439714;
      }
      else {
        *(float *)(param_1 + 0xb4) = *(float *)(param_1 + 0x144);
      }
      *(undefined2 *)(param_1 + 0x272) = 0;
      dVar6 = zz_003f320_((double)*(float *)(param_1 + 0x24),(float *)(param_1 + 0x20));
      dVar7 = FUN_8003d964((double)(FLOAT_80439718 * *(float *)(param_1 + 0xb4)),param_1,
                           (float *)(param_1 + 0x20));
      fVar1 = FLOAT_8043971c * *(float *)(param_1 + 0x144);
      if (((float)(dVar6 - dVar7) <= fVar1) &&
         (*(float *)(param_1 + 0xb4) =
               *(float *)(param_1 + 0x144) * ((float)(dVar6 - dVar7) / fVar1),
         PTR_DAT_80433934[0x1c] == '\x03')) {
        *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 0x20;
      }
      bVar3 = false;
      if ((((*(byte *)(param_1 + 0x274) & 1) != 0) && (dVar7 <= (double)FLOAT_80439720)) &&
         (*(char *)(param_1 + 0x1db) == '\0')) {
        local_74 = *(float *)(param_1 + 0x20);
        local_6c = *(float *)(param_1 + 0x28);
        local_70 = FLOAT_80439720;
        local_64 = FLOAT_80439720;
        local_60 = (float)((double)FLOAT_80439720 * (double)*(float *)(param_1 + 0x144) +
                          (double)local_6c);
        local_68 = local_74;
        iVar5 = zz_003f044_(&local_74,&local_68,afStack_5c);
        if (iVar5 != 0) {
          local_68 = local_74;
          local_64 = local_70;
          local_60 = -(FLOAT_80439720 * *(float *)(param_1 + 0x144) - local_6c);
          iVar5 = zz_003f044_(&local_74,&local_68,afStack_50);
          if (iVar5 != 0) {
            in_f31 = gnt4_PSVECSquareDistance_bl(afStack_5c,afStack_50);
            if ((double)FLOAT_80439724 < in_f31) {
              dVar6 = 1.0 / SQRT(in_f31);
              dVar6 = DOUBLE_80439728 * dVar6 * -(in_f31 * dVar6 * dVar6 - DOUBLE_80439730);
              dVar6 = DOUBLE_80439728 * dVar6 * -(in_f31 * dVar6 * dVar6 - DOUBLE_80439730);
              in_f31 = (double)(float)(in_f31 * DOUBLE_80439728 * dVar6 *
                                                -(in_f31 * dVar6 * dVar6 - DOUBLE_80439730));
            }
            bVar3 = true;
          }
        }
        if ((bVar3) && ((float)(in_f31 / (double)FLOAT_80439718) <= *(float *)(param_1 + 0xb4))) {
          *(float *)(param_1 + 0xb4) = (float)(in_f31 / (double)FLOAT_80439718);
          *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(param_1 + 0xb4);
        }
      }
      *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(param_1 + 0xc4) = *(undefined4 *)(param_1 + 0xb4);
      fVar4 = FLOAT_80439740;
      fVar1 = FLOAT_80439738;
      cVar2 = *(char *)(param_1 + 0x19);
      if (cVar2 == '\x01') {
        *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 1;
        *(float *)(param_1 + 0x204) = fVar4;
        if (*(char *)(param_1 + 0x1db) == '\0') {
          dVar6 = FUN_8003d964((double)(FLOAT_80439718 * *(float *)(param_1 + 0xb4)),param_1,
                               (float *)(param_1 + 0x20));
          fVar1 = (float)((double)FLOAT_8043973c * (double)*(float *)(param_1 + 0xb4) + dVar6);
          if (*(float *)(param_1 + 0x24) < fVar1) {
            *(float *)(param_1 + 0x24) = fVar1;
          }
          else if (FLOAT_80439744 < *(float *)(param_1 + 0x24) - fVar1) {
            *(undefined1 *)(param_1 + 0x19) = 0;
          }
          else {
            *(float *)(param_1 + 0x24) = fVar1;
          }
        }
        else {
          *(undefined1 *)(param_1 + 0x19) = 2;
        }
      }
      else if (cVar2 < '\x01') {
        if (-1 < cVar2) {
          *(float *)(param_1 + 0x204) = FLOAT_80439710;
          *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x20) + *(float *)(param_1 + 0x38);
          *(float *)(param_1 + 0x28) = *(float *)(param_1 + 0x28) + *(float *)(param_1 + 0x40);
          *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x48);
          *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) + *(float *)(param_1 + 0x50);
          if (fVar1 < *(float *)(param_1 + 0x48)) {
            *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 1;
          }
          if (*(float *)(param_1 + 0x48) <= FLOAT_80439724) {
            dVar6 = FUN_8003d964((double)(FLOAT_80439718 * *(float *)(param_1 + 0xb4)),param_1,
                                 (float *)(param_1 + 0x20));
            fVar1 = (float)((double)FLOAT_8043973c * (double)*(float *)(param_1 + 0xb4) + dVar6);
            if (*(float *)(param_1 + 0x24) <= fVar1) {
              *(float *)(param_1 + 0x24) = fVar1;
              fVar1 = FLOAT_80439724;
              *(undefined1 *)(param_1 + 0x19) = 1;
              *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 1;
              *(float *)(param_1 + 0x38) = fVar1;
              *(float *)(param_1 + 0x3c) = fVar1;
              *(float *)(param_1 + 0x40) = fVar1;
              *(float *)(param_1 + 0x48) = fVar1;
              zz_00f036c_(param_1,0xe2);
              *(float *)(param_1 + 0x204) = FLOAT_80439740;
            }
            fVar1 = FLOAT_80439724;
            if (*(char *)(param_1 + 0x1db) != '\0') {
              *(undefined1 *)(param_1 + 0x19) = 2;
              *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 1;
              *(float *)(param_1 + 0x38) = fVar1;
              *(float *)(param_1 + 0x3c) = fVar1;
              *(float *)(param_1 + 0x40) = fVar1;
              *(float *)(param_1 + 0x48) = fVar1;
              zz_00f036c_(param_1,0xe2);
              *(float *)(param_1 + 0x204) = FLOAT_80439740;
            }
          }
        }
      }
      else if (cVar2 < '\x03') {
        *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 1;
        *(float *)(param_1 + 0x204) = fVar4;
        if (*(char *)(param_1 + 0x1db) == '\0') {
          *(undefined1 *)(param_1 + 0x19) = 0;
        }
      }
    }
  }
  else {
    zz_01142c8_(param_1);
  }
  return;
}



// ==== 801142c8  zz_01142c8_ ====

void zz_01142c8_(int param_1)

{
  zz_006de10_(*(int *)(param_1 + 0x90),2);
  *(undefined1 *)(param_1 + 0x18) = 2;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 80114314  FUN_80114314 ====

void FUN_80114314(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 80114320  FUN_80114320 ====

void FUN_80114320(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80114340  FUN_80114340 ====

void FUN_80114340(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_9 + 0x90);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  uVar1 = 1;
  if (*(char *)(iVar2 + 0x3ec) == '\x04') {
    uVar1 = 0x44;
  }
  zz_00097b4_(*(int *)(param_9 + 0xe0),uVar1);
  return;
}



// ==== 8011439c  FUN_8011439c ====

void FUN_8011439c(int param_1)

{
  undefined1 *puVar1;
  
  if ((*(short *)(param_1 + 1000) == 0x301) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,4), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_80114490;
    *(code **)(puVar1 + 0x10c) = FUN_80114690;
    *(int *)(puVar1 + 0x8c) = param_1;
    *(undefined4 *)(puVar1 + 0x90) = *(undefined4 *)(param_1 + 0x90);
    *(undefined2 *)(puVar1 + 0x94) = *(undefined2 *)(param_1 + 0x94);
    puVar1[0x96] = *(undefined1 *)(param_1 + 0x96);
    puVar1[0x97] = *(undefined1 *)(param_1 + 0x97);
    puVar1[0x88] = *(undefined1 *)(param_1 + 0x88);
    *(undefined4 *)(puVar1 + 200) = *(undefined4 *)(param_1 + 200);
    *(undefined4 *)(puVar1 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
    *(undefined4 *)(puVar1 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
    *(undefined4 *)(puVar1 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
    *(undefined4 *)(puVar1 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
    puVar1[0xd0] = *(undefined1 *)(param_1 + 0xd0);
  }
  return;
}



// ==== 80114490  FUN_80114490 ====

void FUN_80114490(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_803284fc)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801144e4  FUN_801144e4 ====

void FUN_801144e4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  undefined8 uVar5;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar4 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar5 = zz_0089100_(param_9,(int)*(char *)(iVar4 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x41;
  fVar1 = FLOAT_80439748;
  *(undefined1 *)(param_9 + 0x13) = 2;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar4 = zz_0006f98_(iVar4);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe0),9,iVar4 + 0xc28,in_r7,in_r8,
                      in_r9,in_r10);
  iVar3 = iVar4 + 0xc28;
  uVar2 = 9;
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe4),9,iVar3,in_r7,in_r8,in_r9,
                      in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,uVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  uVar5 = zz_0007cac_((double)FLOAT_8043974c,*(int *)(param_9 + 0xe4));
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe8),0xb,iVar4 + 0xc28,in_r7,in_r8
                      ,in_r9,in_r10);
  iVar3 = iVar4 + 0xc28;
  uVar2 = 0xb;
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xec),0xb,iVar3,in_r7,in_r8,in_r9,
                      in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xec)
              ,extraout_r4_00,uVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043974c,*(int *)(param_9 + 0xec));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0114604_(param_9);
  return;
}



// ==== 80114604  zz_0114604_ ====

void zz_0114604_(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  cVar1 = *(char *)(*(int *)(param_1 + 0x90) + 0x6e8);
  if (-1 < cVar1) {
    *(char *)(param_1 + 0x13) = cVar1;
  }
  iVar3 = *(char *)(param_1 + 0x13) * 0xc;
  uVar2 = *(undefined4 *)(&DAT_803284dc + iVar3);
  *(undefined4 *)(param_1 + 100) = *(undefined4 *)(&DAT_803284d8 + iVar3);
  *(undefined4 *)(param_1 + 0x68) = uVar2;
  *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(&DAT_803284e0 + iVar3);
  *(undefined *)(param_1 + 0x89) = (&DAT_80434540)[*(char *)(param_1 + 0x13)];
  return;
}



// ==== 80114670  FUN_80114670 ====

void FUN_80114670(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80114690  FUN_80114690 ====

void FUN_80114690(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar2;
  int iVar3;
  
  iVar1 = *(int *)(param_9 + 0x90);
  iVar2 = (int)(char)((undefined *)(int)*(char *)(param_9 + 0x13))[-0x7fbcbabc];
  if ((*(char *)(iVar1 + 0xae) != '\0') || (*(char *)(iVar1 + 0x3ec) == '\x04')) {
    iVar2 = iVar2 + 1;
  }
  iVar3 = *(int *)(param_9 + iVar2 * 4 + 0xe0);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
              (float *)(param_9 + 0x114),(undefined *)(int)*(char *)(param_9 + 0x13),iVar1,in_r7,
              in_r8,in_r9,in_r10);
  zz_00097b4_(iVar3,(int)(char)(&DAT_80434548)[iVar2]);
  return;
}



// ==== 8011471c  zz_011471c_ ====

void zz_011471c_(int param_1,float *param_2)

{
  float fVar1;
  
  fVar1 = FLOAT_80439750;
  param_2[5] = FLOAT_80439750;
  param_2[4] = fVar1;
  param_2[3] = fVar1;
  param_2[2] = fVar1;
  param_2[1] = fVar1;
  *param_2 = fVar1;
  *(float *)(param_1 + 0x16d8) = fVar1;
  *(float *)(param_1 + 0x16d4) = fVar1;
  *(float *)(param_1 + 0x16d0) = fVar1;
  *(float *)(param_1 + 0x16e4) = fVar1;
  *(float *)(param_1 + 0x16e0) = fVar1;
  *(float *)(param_1 + 0x16dc) = fVar1;
  return;
}



// ==== 80114754  zz_0114754_ ====

void zz_0114754_(int param_1,float *param_2)

{
  float fVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  
  if (*(char *)(param_1 + 0x6e9) != 0) {
    iVar2 = (*(char *)(param_1 + 0x6e9) + -1) * 0x10;
    param_2[4] = *(float *)(&DAT_80329248 + iVar2);
    param_2[2] = *(float *)(&DAT_8032924c + iVar2);
    param_2[5] = *(float *)(&DAT_80329250 + iVar2);
    param_2[3] = *(float *)(&DAT_80329254 + iVar2);
    *(undefined1 *)(param_1 + 0x6e9) = 0;
  }
  dVar4 = DOUBLE_80439760;
  dVar3 = DOUBLE_80439758;
  *param_2 = (float)(DOUBLE_80439758 * (double)(float)((double)param_2[2] - (double)*param_2) +
                    (double)*param_2);
  if (dVar4 * (double)param_2[2] <= (double)*param_2) {
    param_2[2] = param_2[4];
  }
  param_2[1] = (float)(dVar3 * (double)(float)((double)param_2[3] - (double)param_2[1]) +
                      (double)param_2[1]);
  if (dVar4 * (double)param_2[3] <= (double)param_2[1]) {
    param_2[3] = param_2[5];
  }
  fVar1 = *param_2;
  *(float *)(param_1 + 0x16e4) = fVar1;
  *(float *)(param_1 + 0x16e0) = fVar1;
  *(float *)(param_1 + 0x16dc) = fVar1;
  fVar1 = param_2[1];
  *(float *)(param_1 + 0x16d8) = fVar1;
  *(float *)(param_1 + 0x16d4) = fVar1;
  *(float *)(param_1 + 0x16d0) = fVar1;
  return;
}



// ==== 80114934  FUN_80114934 ====

void FUN_80114934(int param_1)

{
  short sVar1;
  
  zz_011471c_(param_1,(float *)(param_1 + 0x144));
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x805) {
    zz_013874c_(param_1,0);
  }
  else if (sVar1 == 0x80d) {
    zz_013874c_(param_1,2);
  }
  else if (sVar1 == 0x80e) {
    zz_013874c_(param_1,1);
  }
  *(undefined1 *)(param_1 + 0x6f4) = 0;
  return;
}



// ==== 801149d0  FUN_801149d0 ====

void FUN_801149d0(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  zz_0114754_(param_1,(float *)(param_1 + 0x144));
  *(float *)(param_1 + 0x1dc0) = FLOAT_80439768;
  fVar2 = FLOAT_80439770;
  fVar1 = FLOAT_80439750;
  if (*(char *)(param_1 + 0x18) == '\x01') {
    if ((*(char *)(param_1 + 0x19) == '\x02') && ((*(uint *)(param_1 + 0x5e0) & 0x20001000) == 0)) {
      if ((*(char *)(param_1 + 0x5db) == '\x01') || ((*(uint *)(param_1 + 0x5e0) & 0x10) != 0)) {
        *(float *)(param_1 + 0x15c) = *(float *)(param_1 + 0x15c) + FLOAT_8043976c;
        if (fVar2 < *(float *)(param_1 + 0x15c)) {
          *(float *)(param_1 + 0x15c) = fVar2;
        }
        *(short *)(param_1 + 0x160) = *(short *)(param_1 + 0x160) + 0x180;
      }
      else {
        *(float *)(param_1 + 0x15c) = *(float *)(param_1 + 0x15c) - FLOAT_8043976c;
        if (*(float *)(param_1 + 0x15c) < fVar1) {
          *(float *)(param_1 + 0x15c) = fVar1;
        }
      }
      dVar3 = zz_0045204_(*(short *)(param_1 + 0x160));
      *(float *)(param_1 + 0x1dc0) =
           *(float *)(param_1 + 0x15c) * (float)((double)FLOAT_80439774 * dVar3) + FLOAT_80439768;
    }
  }
  return;
}



// ==== 80114ad4  FUN_80114ad4 ====

void FUN_80114ad4(int param_1)

{
  (*(code *)(&PTR_FUN_803292c8)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80114b10  FUN_80114b10 ====

void FUN_80114b10(int param_1)

{
  *(short *)(param_1 + 0x18dc) = *(short *)(param_1 + 0x18dc) >> 1;
  (*(code *)(&PTR_FUN_803292d4)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80114b58  FUN_80114b58 ====

void FUN_80114b58(int param_1)

{
  (*(code *)(&PTR_FUN_803292e8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80114b94  FUN_80114b94 ====

void FUN_80114b94(int param_1)

{
  float fVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_01151e0_(param_1);
  fVar1 = FLOAT_80439750;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff4f;
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80439778,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  zz_004beb8_((double)FLOAT_8043977c,param_1,0xf,2,(int)*(char *)(param_1 + 0x6ee),0xffffffff,
              0xffffffff);
  return;
}



// ==== 80114c78  FUN_80114c78 ====

void FUN_80114c78(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_80439778,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e1ac_(param_1,0xc1,1);
  fVar2 = FLOAT_80439750;
  fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x560) = fVar1;
  if ((fVar2 < fVar1) && (iVar3 = zz_006d144_(param_1,0xc1), iVar3 == 0)) {
    return;
  }
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_0115210_(param_1);
  }
  return;
}



// ==== 80114d48  FUN_80114d48 ====

void FUN_80114d48(int param_1)

{
  int iVar1;
  int iVar2;
  double dVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_80439780,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  iVar1 = zz_00679d0_(param_1);
  if (*(float *)(param_1 + 0x55c) <= FLOAT_80439750) {
    zz_004cd24_(param_1,0xf);
  }
  else {
    *(float *)(param_1 + 0x55c) = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8);
  }
  if (*(float *)(param_1 + 0x558) <= FLOAT_80439750) {
    if ((*(uint *)(param_1 + 0x5b4) & 0x200) != 0) {
      iVar2 = zz_006dbe0_(param_1,0,1,0);
      if ((iVar2 != 0) && ('\0' < *(char *)(param_1 + 0x6ef))) {
        zz_006bf80_(param_1);
        dVar3 = (double)FLOAT_8043977c;
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
        zz_004beb8_(dVar3,param_1,0xf,2,1,0xffffffff,0xffffffff);
        return;
      }
      goto LAB_80114e6c;
    }
    *(float *)(param_1 + 0x55c) = FLOAT_80439750;
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  if ((((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) && ((*(uint *)(param_1 + 0x5d4) & 1) == 0)) &&
     (*(char *)(param_1 + 0x1cee) == '\0')) {
    return;
  }
LAB_80114e6c:
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  if (iVar1 == 0) {
    zz_006a5a4_(param_1);
  }
  else {
    zz_006a474_(param_1);
  }
  return;
}



// ==== 80114eb4  FUN_80114eb4 ====

void FUN_80114eb4(int param_1)

{
  (*(code *)(&PTR_FUN_803292f4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80114ef0  FUN_80114ef0 ====

void FUN_80114ef0(int param_1)

{
  int iVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_01151e0_(param_1);
  iVar1 = 2;
  if ((*(uint *)(param_1 + 0x5e0) & 0x80) != 0) {
    if (*(char *)(param_1 + 0x5db) != '\x11') {
      zz_006a3d0_(param_1,'\0',3,0);
      return;
    }
    iVar1 = 6;
  }
  zz_004beb8_((double)FLOAT_8043977c,param_1,1,2,iVar1 + *(char *)(param_1 + 0x6ee),0xffffffff,
              0xffffffff);
  return;
}



// ==== 80114f88  FUN_80114f88 ====

void FUN_80114f88(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_006dee8_(param_1,1);
  zz_004cd24_(param_1,1);
  fVar2 = FLOAT_80439750;
  if (iVar3 < 0) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a3d0_(param_1,'\0',0,2);
    }
    else {
      zz_006a3d0_(param_1,'\0',3,2);
    }
  }
  else {
    if ((iVar3 < 1) &&
       (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
       *(float *)(param_1 + 0x560) = fVar1, fVar2 < fVar1)) {
      return;
    }
    if (*(char *)(param_1 + 0x1cef) != '\0') {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      zz_0115210_(param_1);
    }
  }
  return;
}



// ==== 8011505c  FUN_8011505c ====

void FUN_8011505c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  double dVar2;
  
  if (*(float *)(param_9 + 0x55c) <= FLOAT_80439750) {
    zz_004cd24_(param_9,1);
  }
  else {
    *(float *)(param_9 + 0x55c) = *(float *)(param_9 + 0x55c) - *(float *)(param_9 + 0x1dc8);
  }
  dVar2 = (double)*(float *)(param_9 + 0x558);
  if (dVar2 <= (double)FLOAT_80439750) {
    if ((*(uint *)(param_9 + 0x5b4) & 0x200) != 0) {
      param_11 = 1;
      param_12 = 0;
      iVar1 = zz_006dbe0_(param_9,0,1,0);
      if ((iVar1 != 0) && ('\0' < *(char *)(param_9 + 0x6ef))) {
        zz_006bf80_(param_9);
        *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
        if (((*(uint *)(param_9 + 0x5e0) & 0x80) != 0) && (*(char *)(param_9 + 0x5db) == '\x11')) {
          dVar2 = (double)FLOAT_8043977c;
          *(undefined1 *)(param_9 + 0x581) = 4;
          zz_004beb8_(dVar2,param_9,1,2,7,0xffffffff,0xffffffff);
          return;
        }
        if ((*(uint *)(param_9 + 0x5e0) & 0x10) != 0) {
          dVar2 = (double)FLOAT_8043977c;
          *(undefined1 *)(param_9 + 0x581) = 1;
          zz_004beb8_(dVar2,param_9,1,2,3,0xffffffff,0xffffffff);
          return;
        }
        zz_006a3d0_(param_9,'\0',0,2);
        return;
      }
      goto LAB_801151ac;
    }
    *(float *)(param_9 + 0x55c) = FLOAT_80439750;
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar2 - (double)*(float *)(param_9 + 0x1dc8));
  }
  if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_9 + 0x1cee) == '\0')) {
    return;
  }
LAB_801151ac:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801151e0  zz_01151e0_ ====

void zz_01151e0_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_80439784;
  *(float *)(param_1 + 0x560) = FLOAT_80439768;
  fVar1 = FLOAT_80439750;
  *(float *)(param_1 + 0x558) = fVar2;
  *(float *)(param_1 + 0x55c) = fVar1;
  if (*(char *)(param_1 + 0x6ee) != '\0') {
    return;
  }
  *(undefined1 *)(param_1 + 0x6ef) = 3;
  return;
}



// ==== 80115210  zz_0115210_ ====

void zz_0115210_(int param_1)

{
  short sVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  fVar3 = FLOAT_80439784;
  *(float *)(param_1 + 0x560) = FLOAT_80439768;
  fVar2 = FLOAT_80439750;
  *(float *)(param_1 + 0x558) = fVar3;
  *(float *)(param_1 + 0x55c) = fVar2;
  *(undefined1 *)(param_1 + 0x6ee) = 1;
  if ('\0' < *(char *)(param_1 + 0x6ef)) {
    iVar4 = zz_006dbe0_(param_1,0,1,1);
    if (iVar4 != 0) {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x805) {
        zz_013fb50_(param_1,0);
        zz_013fb50_(param_1,1);
      }
      else if (sVar1 == 0x80d) {
        zz_013fb50_(param_1,4);
        zz_013fb50_(param_1,5);
      }
      else if (sVar1 == 0x80e) {
        zz_013fb50_(param_1,2);
        zz_013fb50_(param_1,3);
      }
      *(char *)(param_1 + 0x6ef) = *(char *)(param_1 + 0x6ef) + -1;
    }
    if (*(short *)(param_1 + 0x774) < 1) {
      *(undefined1 *)(param_1 + 0x6ef) = 0;
    }
  }
  return;
}



// ==== 80115308  FUN_80115308 ====

void FUN_80115308(int param_1)

{
  if ((*(char *)(param_1 + 0x581) != '\x03') && (*(char *)(param_1 + 0x581) != '\x04')) {
    *(short *)(param_1 + 0x18dc) = *(short *)(param_1 + 0x18dc) >> 1;
    *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  }
  (*(code *)(&PTR_FUN_80329300)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80115374  FUN_80115374 ====

void FUN_80115374(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80329314)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801153c4  FUN_801153c4 ====

void FUN_801153c4(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  double dVar5;
  
  fVar3 = FLOAT_80439788;
  fVar2 = FLOAT_80439750;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar3;
  *(float *)(param_1 + 0x55c) = fVar2;
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = 1;
  *(float *)(param_1 + 0x44) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  uVar4 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar4 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar5 = (double)FLOAT_8043977c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 801154ac  FUN_801154ac ====

void FUN_801154ac(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_80439750;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) &&
     (fVar1 = FLOAT_8043978c, *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01',
     fVar1 < *(float *)(param_1 + 0x764))) {
    zz_00b2190_(param_1,0);
  }
  return;
}



// ==== 80115544  FUN_80115544 ====

void FUN_80115544(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  fVar2 = FLOAT_8043978c;
  if ((*(char *)(param_1 + 0x1cef) < '\0') && (*(char *)(param_1 + 0x746) != '\0')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x746) = 0;
    if (fVar2 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
    cVar1 = *(char *)(param_1 + 0x6ea);
    dVar3 = (double)FLOAT_8043977c;
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  }
  else {
    zz_0115600_(param_1);
  }
  return;
}



// ==== 80115600  zz_0115600_ ====

void zz_0115600_(int param_1)

{
  float fVar1;
  float fVar2;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  if (*(char *)(param_1 + 0x1d0f) != '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(float *)(param_1 + 0x55c) = FLOAT_80439790;
    fVar2 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) &&
       (fVar1 = (float)(DOUBLE_80439798 * (double)*(float *)(param_1 + 0x764)), fVar2 < fVar1)) {
      fVar2 = fVar1;
    }
    *(float *)(param_1 + 0x44) = fVar2 / FLOAT_80439768;
  }
  if (FLOAT_80439750 < *(float *)(param_1 + 0x55c)) {
    *(short *)(param_1 + 0x54a) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x54a) ^ 0x80000000) -
                             DOUBLE_804397a8) - *(float *)(param_1 + 0x1dc8));
  }
  else if (*(float *)(param_1 + 0x764) < FLOAT_8043978c) {
    zz_006ed8c_((double)FLOAT_804397a0,param_1);
  }
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_804397a4;
  }
  zz_006ed8c_((double)FLOAT_80439780,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 80115790  FUN_80115790 ====

void FUN_80115790(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80329328)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801157e0  FUN_801157e0 ====

void FUN_801157e0(int param_1)

{
  char cVar1;
  uint uVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x5ae);
  *(undefined1 *)(param_1 + 0x6ea) = 7;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  *(float *)(param_1 + 0x558) = FLOAT_80439788;
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_80439778,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043977c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 801158d0  FUN_801158d0 ====

void FUN_801158d0(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_80439750;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  else {
    zz_006ed8c_((double)FLOAT_80439778,param_1);
    zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  }
  return;
}



// ==== 80115968  FUN_80115968 ====

void FUN_80115968(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_80439778,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  fVar1 = FLOAT_80439768;
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar3 = FLOAT_804397b0;
    fVar2 = FLOAT_80439750;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x760))) {
      fVar1 = *(float *)(param_1 + 0x760);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_80439768;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x760)) {
      zz_00b2190_(param_1,0);
    }
    *(float *)(param_1 + 0x80c) = FLOAT_80439750;
  }
  return;
}



// ==== 80115a60  FUN_80115a60 ====

void FUN_80115a60(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  fVar2 = FLOAT_80439750;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < fVar1) {
    uVar3 = FUN_80066838((double)FLOAT_8043978c,param_1);
    if ((uVar3 == 0) && (*(char *)(param_1 + 0x1d9) == '\0')) goto LAB_80115ae8;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0xff;
LAB_80115ae8:
  zz_00b22f4_(param_1);
  return;
}



// ==== 80115b04  FUN_80115b04 ====

void FUN_80115b04(int param_1)

{
  zz_006ed8c_((double)FLOAT_80439780,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 80115b7c  FUN_80115b7c ====

void FUN_80115b7c(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8032933c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80115bcc  FUN_80115bcc ====

void FUN_80115bcc(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_80439788;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = 5;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80439780,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_8043977c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 80115ce4  FUN_80115ce4 ====

void FUN_80115ce4(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80439780,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_80439750;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 80115d98  FUN_80115d98 ====

void FUN_80115d98(int param_1)

{
  int iVar1;
  double dVar2;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d144_(param_1,0xc0);
    zz_006e1ac_(param_1,0xc0,1);
    dVar2 = zz_0045238_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_804397b4 * dVar2);
    dVar2 = zz_0045204_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_804397b4 * -dVar2);
  }
  zz_006ed8c_((double)FLOAT_804397b8,param_1);
  FUN_80067310((double)FLOAT_80439770,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    if (iVar1 == 0) {
      if (*(char *)(param_1 + 0x746) == '\0') {
        dVar2 = (double)FLOAT_8043977c;
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
        zz_004beb8_(dVar2,param_1,0xf,0,0xd,0x14,1);
      }
      else {
        dVar2 = (double)FLOAT_8043977c;
        *(undefined1 *)(param_1 + 0x746) = 0;
        zz_004beb8_(dVar2,param_1,0xf,3,(int)*(char *)(param_1 + 0x6ea),0xffffffff,0xffffffff);
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a750_(param_1,7);
      *(float *)(param_1 + 0x694) = FLOAT_804397bc + *(float *)(param_1 + 0x1dc8);
    }
  }
  return;
}



// ==== 80115f14  FUN_80115f14 ====

void FUN_80115f14(int param_1)

{
  int iVar1;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_804397a8) * FLOAT_804397b8);
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_804397b8,param_1);
  FUN_80067310((double)FLOAT_80439770,param_1,*(short *)(param_1 + 0x5ac));
  iVar1 = zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if (iVar1 == 0) {
      zz_006a5a4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
  }
  return;
}



// ==== 80115fdc  FUN_80115fdc ====

void FUN_80115fdc(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8032934c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8011602c  FUN_8011602c ====

void FUN_8011602c(int param_1)

{
  uint uVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 8;
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(float *)(param_1 + 0x558) = FLOAT_80439788;
  zz_006d144_(param_1,0xc0);
  zz_004beb8_((double)FLOAT_8043977c,param_1,0xf,3,(int)*(char *)(param_1 + 0x6ea),0xffffffff,
              0xffffffff);
  return;
}



// ==== 801160f4  FUN_801160f4 ====

void FUN_801160f4(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  fVar2 = FLOAT_80439750;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_804397c0;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar1 = FLOAT_80439750;
    dVar4 = (double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (dVar4 < (double)*(float *)(param_1 + 0x764))) {
      dVar4 = (double)*(float *)(param_1 + 0x764);
    }
    *(float *)(param_1 + 0x44) = (float)((DOUBLE_804397c8 * dVar4) / DOUBLE_804397d0);
    *(float *)(param_1 + 0x4c) = fVar1;
    zz_00b2190_(param_1,0);
    *(float *)(param_1 + 0x80c) = FLOAT_80439750;
  }
  return;
}



// ==== 801161e0  FUN_801161e0 ====

void FUN_801161e0(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_80439780,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (-1 < *(char *)(param_1 + 0x1cef)) {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_80439750;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < fVar1) {
    uVar3 = FUN_80066838((double)FLOAT_804397d8,param_1);
    if (((int)uVar3 < 1) && (*(char *)(param_1 + 0x1d9) == '\0')) goto LAB_80116280;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0xff;
LAB_80116280:
  zz_00b22f4_(param_1);
  return;
}



// ==== 8011629c  FUN_8011629c ====

void FUN_8011629c(int param_1)

{
  double dVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_804397b8,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    dVar1 = (double)FLOAT_8043977c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar1,param_1,0xf,0x82,4,0xffffffff,0);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 80116324  FUN_80116324 ====

void FUN_80116324(int param_1)

{
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 8011637c  FUN_8011637c ====

void FUN_8011637c(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80329360)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801163d8  FUN_801163d8 ====

void FUN_801163d8(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_80439788;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = 9;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80439780,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_8043977c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 801164f0  FUN_801164f0 ====

void FUN_801164f0(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80439780,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_80439750;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_804397dc;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    *(undefined2 *)(param_1 + 0x54a) = 0x78;
  }
  return;
}



// ==== 801165b4  FUN_801165b4 ====

void FUN_801165b4(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  
  uVar3 = zz_006de44_(param_1,0xf0f00);
  dVar4 = DOUBLE_804397a8;
  if (uVar3 != 0) {
    if ((int)*(short *)(param_1 + 0x54a) < (int)uVar3) {
      uVar3 = (int)*(short *)(param_1 + 0x54a);
    }
    *(short *)(param_1 + 0x54a) = *(short *)(param_1 + 0x54a) - (short)uVar3;
    *(float *)(param_1 + 0x558) =
         *(float *)(param_1 + 0x558) +
         (float)((double)CONCAT44(0x43300000,uVar3 ^ 0x80000000) - dVar4);
  }
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d144_(param_1,0xc0);
    zz_006e1ac_(param_1,0xc0,1);
  }
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x18da));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_804397b4 * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x18da));
  dVar5 = (double)FLOAT_80439770;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_804397b4 * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_80439750;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar1 <= fVar2) {
    dVar4 = (double)FLOAT_8043977c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    zz_004beb8_(dVar4,param_1,0xf,0,0xc,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80116704  FUN_80116704 ====

void FUN_80116704(int param_1)

{
  int iVar1;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_804397a8) * FLOAT_804397b8);
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_804397b8,param_1);
  FUN_80067310((double)FLOAT_80439770,param_1,*(short *)(param_1 + 0x5ac));
  iVar1 = zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if (iVar1 == 0) {
      zz_006a5a4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
  }
  return;
}



// ==== 801167cc  FUN_801167cc ====

void FUN_801167cc(int param_1)

{
  (*(code *)(&PTR_FUN_80329370)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80116808  FUN_80116808 ====

void FUN_80116808(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80434550)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80116854  FUN_80116854 ====

void FUN_80116854(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x54a) = *(undefined2 *)(param_1 + 0x5ae);
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  fVar3 = FLOAT_80439780;
  fVar2 = FLOAT_80439750;
  if (*(char *)(param_1 + 0x581) == '\0') {
    *(float *)(param_1 + 0x4c) = FLOAT_80439750;
    *(float *)(param_1 + 0x44) = fVar2;
  }
  else {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80439780;
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar3;
  }
  fVar2 = FLOAT_80439750;
  dVar4 = (double)FLOAT_80439770;
  *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * FLOAT_80439780;
  *(float *)(param_1 + 0x50) = fVar2;
  FUN_80067310(dVar4,param_1,*(short *)(param_1 + 0x54a));
  zz_00679d0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_8043977c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 80116944  FUN_80116944 ====

void FUN_80116944(int param_1)

{
  short sVar1;
  float fVar2;
  int iVar3;
  
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    iVar3 = zz_006dbe0_(param_1,2,1,1);
    if (iVar3 != 0) {
      if (*(char *)(param_1 + 0x6f4) == '\0') {
        sVar1 = *(short *)(param_1 + 1000);
        if (sVar1 == 0x805) {
          zz_01213bc_(param_1,0);
        }
        else if (sVar1 == 0x80d) {
          zz_01213bc_(param_1,2);
        }
        else if (sVar1 == 0x80e) {
          zz_01213bc_(param_1,1);
        }
      }
      else if (*(char *)(param_1 + 0x6f4) == '\x01') {
        *(undefined1 *)(param_1 + 0x6f4) = 2;
      }
    }
  }
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  zz_006ed8c_((double)FLOAT_80439780,param_1);
  FUN_80067310((double)FLOAT_80439770,param_1,*(short *)(param_1 + 0x54a));
  zz_00679d0_(param_1);
  fVar2 = FLOAT_80439750;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x44) = fVar2;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x54a);
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a474_(param_1);
    }
    else {
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 80116bc8  FUN_80116bc8 ====

void FUN_80116bc8(int param_1)

{
  float fVar1;
  
  zz_00c627c_(param_1,0,0);
  fVar1 = FLOAT_804397e0;
  *(undefined2 *)(param_1 + 0x6f6) = 0;
  *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x140);
  *(undefined4 *)(param_1 + 0x148) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x144);
  *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x148);
  *(float *)(param_1 + 0x150) = fVar1;
  return;
}



// ==== 80116c30  FUN_80116c30 ====

void FUN_80116c30(int param_1)

{
  float fVar1;
  float fVar2;
  
  *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 1;
  *(undefined1 *)(param_1 + 0x748) = 2;
  if (*(short *)(param_1 + 0x6f6) < 1) {
    fVar1 = FLOAT_804397e8 * *(float *)(param_1 + 0x150);
    fVar2 = *(float *)(param_1 + 0x144);
    if (*(float *)(param_1 + 0x144) < fVar1) {
      fVar2 = fVar1;
    }
    *(float *)(param_1 + 0x874) = fVar2;
    *(float *)(param_1 + 0x85c) = fVar2;
    *(float *)(param_1 + 0x858) = fVar2;
    fVar2 = *(float *)(param_1 + 0x148);
    if (*(float *)(param_1 + 0x148) < fVar1) {
      fVar2 = fVar1;
    }
    *(float *)(param_1 + 0x878) = fVar2;
    fVar2 = *(float *)(param_1 + 0x14c);
    if (*(float *)(param_1 + 0x14c) < fVar1) {
      fVar2 = fVar1;
    }
    *(float *)(param_1 + 0x87c) = fVar2;
  }
  else {
    fVar1 = FLOAT_804397e0 +
            (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x6f6) ^ 0x80000000) -
                   DOUBLE_804397f0) / FLOAT_804397e4;
    fVar2 = *(float *)(param_1 + 0x144) * fVar1;
    *(float *)(param_1 + 0x874) = fVar2;
    *(float *)(param_1 + 0x85c) = fVar2;
    *(float *)(param_1 + 0x858) = fVar2;
    *(float *)(param_1 + 0x878) = *(float *)(param_1 + 0x148) * fVar1;
    *(float *)(param_1 + 0x87c) = *(float *)(param_1 + 0x14c) * fVar1;
  }
  if (*(short *)(param_1 + 0x6f6) < 1) {
    *(undefined4 *)(param_1 + 0x16cc) = *(undefined4 *)(param_1 + 0x150);
  }
  else {
    *(float *)(param_1 + 0x16cc) = FLOAT_804397ec;
  }
  return;
}



// ==== 80116d28  FUN_80116d28 ====

void FUN_80116d28(int param_1)

{
  if (0 < *(short *)(param_1 + 0x6f6)) {
    zz_00f0104_(param_1,0x1a,3);
    *(short *)(param_1 + 0x6f6) = *(short *)(param_1 + 0x6f6) + -1;
    if ((*(short *)(param_1 + 0x6f6) == 0) && ((*(uint *)(param_1 + 0x5e0) & 3) != 0)) {
      *(undefined2 *)(param_1 + 0x6f6) = 1;
    }
  }
  return;
}



// ==== 80116dac  FUN_80116dac ====

void FUN_80116dac(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_8032a188)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 80116dec  FUN_80116dec ====

void FUN_80116dec(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  zz_001ab6c_(param_1,0x14);
  return;
}



// ==== 80116e18  FUN_80116e18 ====

void FUN_80116e18(int param_1)

{
  if (0 < *(short *)(param_1 + 0x6f6)) {
    zz_00f0214_(param_1,0x1a,3);
  }
  return;
}



// ==== 80116e58  FUN_80116e58 ====

void FUN_80116e58(int param_1)

{
  int iVar1;
  
  iVar1 = zz_006dbe0_(param_1,0,1,1);
  if (iVar1 != 0) {
    zz_0082824_(param_1,0x25);
  }
  return;
}



// ==== 80116ed0  FUN_80116ed0 ====

void FUN_80116ed0(int param_1)

{
  (*(code *)(&PTR_FUN_8032a1a4)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80116f0c  FUN_80116f0c ====

void FUN_80116f0c(int param_1)

{
  (*(code *)(&PTR_FUN_8032a1b0)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80116f48  FUN_80116f48 ====

void FUN_80116f48(int param_1)

{
  zz_0148d74_(param_1);
  return;
}



// ==== 80116fa4  FUN_80116fa4 ====

void FUN_80116fa4(int param_1)

{
  zz_0149178_(param_1);
  return;
}



// ==== 80117008  FUN_80117008 ====

void FUN_80117008(int param_1)

{
  zz_0148d74_(param_1);
  return;
}



// ==== 80117064  FUN_80117064 ====

void FUN_80117064(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8032a1c4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801170b4  FUN_801170b4 ====

void FUN_801170b4(int param_1)

{
  char cVar1;
  uint uVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(float *)(param_1 + 0x558) = FLOAT_80439818;
  *(undefined1 *)(param_1 + 0x6ea) = 5;
  if (0 < *(short *)(param_1 + 0x6f6)) {
    *(undefined1 *)(param_1 + 0x6ea) = 0xb;
  }
  zz_006d144_(param_1,0xc0);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043981c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 80117198  FUN_80117198 ====

void FUN_80117198(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_804397ec;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_80439820;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    if (0 < *(short *)(param_1 + 0x6f6)) {
      *(float *)(param_1 + 0x558) = FLOAT_804397ec;
    }
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (*(float *)(param_1 + 0x760) < fVar1)) {
      fVar1 = *(float *)(param_1 + 0x760);
    }
    fVar1 = fVar1 / FLOAT_80439820;
    *(float *)(param_1 + 0x4c) = FLOAT_804397ec;
    *(float *)(param_1 + 0x44) = fVar1;
    fVar1 = *(float *)(*(int *)(param_1 + 0x4b0) + 0x54);
    if (fVar1 < *(float *)(param_1 + 0x44)) {
      *(float *)(param_1 + 0x44) = fVar1;
    }
    if (FLOAT_80439824 < *(float *)(param_1 + 0x760)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}



// ==== 801172c4  FUN_801172c4 ====

void FUN_801172c4(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_80439814,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_804397ec;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_80439824,param_1), uVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 80117358  FUN_80117358 ====

void FUN_80117358(int param_1)

{
  float fVar1;
  float fVar2;
  
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_80439814,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_80439828;
  fVar1 = FLOAT_80439818;
  if (*(char *)(param_1 + 0x1cf0) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    *(float *)(param_1 + 0x48) = fVar2;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  return;
}



// ==== 801173e0  FUN_801173e0 ====

void FUN_801173e0(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_804397ec;
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(float *)(param_1 + 0x4c) = FLOAT_804397ec;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  zz_006ed8c_((double)FLOAT_80439814,param_1);
  FUN_80067310((double)FLOAT_804397e0,param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 8011746c  FUN_8011746c ====

void FUN_8011746c(int param_1)

{
  (*(code *)(&PTR_FUN_8032a1d8)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801174a8  FUN_801174a8 ====

void FUN_801174a8(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8032a1ec)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801174f8  FUN_801174f8 ====

void FUN_801174f8(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if (0 < *(short *)(param_1 + 0x6f6)) {
    *(undefined2 *)(param_1 + 0x6f6) = 300;
  }
  zz_006d144_(param_1,0xc1);
  fVar2 = FLOAT_804397ec;
  *(float *)(param_1 + 0x4c) = FLOAT_804397ec;
  *(float *)(param_1 + 0x44) = fVar2;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80439814,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043981c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 801175c4  FUN_801175c4 ====

void FUN_801175c4(int param_1)

{
  char cVar1;
  int iVar2;
  double dVar3;
  
  if (0 < *(short *)(param_1 + 0x6f6)) {
    *(undefined2 *)(param_1 + 0x6f6) = 300;
  }
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d144_(param_1,0xc1);
  }
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    if (*(short *)(param_1 + 0x6f6) < 1) {
      *(undefined2 *)(param_1 + 0x6f6) = 300;
      zz_0182680_(param_1,0,param_1 + 0x6f6);
    }
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80439814,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  iVar2 = zz_00679d0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    if (iVar2 == 0) {
      *(char *)(param_1 + 0x6ea) = *(char *)(param_1 + 0x6ea) + '\x01';
    }
    cVar1 = *(char *)(param_1 + 0x6ea);
    dVar3 = (double)FLOAT_8043981c;
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 801176e8  FUN_801176e8 ====

void FUN_801176e8(int param_1)

{
  int iVar1;
  
  if (0 < *(short *)(param_1 + 0x6f6)) {
    *(undefined2 *)(param_1 + 0x6f6) = 300;
  }
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_804397e0,param_1,*(short *)(param_1 + 0x5ae));
  gnt4_PSQUATScale_bl((double)FLOAT_80439814,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  iVar1 = zz_00679d0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a474_(param_1);
    }
    else if (iVar1 == 0) {
      zz_006a5a4_(param_1);
    }
    else {
      zz_006a750_(param_1,7);
    }
    *(float *)(param_1 + 0x694) = FLOAT_8043982c + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 801177d0  FUN_801177d0 ====

void FUN_801177d0(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  int *piVar2;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x83] = 0x10;
    puVar1[0x10] = 0x1f;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_80117938;
    *(code **)(puVar1 + 0x10c) = FUN_80117eac;
    *(int *)(puVar1 + 0x8c) = param_1;
    *(undefined4 *)(puVar1 + 0x90) = *(undefined4 *)(param_1 + 0x90);
    *(undefined2 *)(puVar1 + 0x94) = *(undefined2 *)(param_1 + 0x94);
    puVar1[0x96] = *(undefined1 *)(param_1 + 0x96);
    puVar1[0x97] = *(undefined1 *)(param_1 + 0x97);
    puVar1[0x88] = *(undefined1 *)(param_1 + 0x88);
    *(undefined4 *)(puVar1 + 200) = *(undefined4 *)(param_1 + 200);
    *(undefined4 *)(puVar1 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
    *(undefined4 *)(puVar1 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
    *(undefined4 *)(puVar1 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
    *(undefined4 *)(puVar1 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
    puVar1[0xd0] = *(undefined1 *)(param_1 + 0xd0);
    gnt4_PSMTXMultVec_bl
              ((float *)(param_1 +
                        (char)(&DAT_8032a672)[(uint)(byte)puVar1[0x11] * 0x30] * 0x30 + 0x8d4),
               (float *)((uint)(byte)puVar1[0x11] * 0x30 + -0x7fcd598c),(float *)(puVar1 + 0x20));
    zz_0083d60_((int)puVar1,param_1,0);
    piVar2 = zz_0006dc8_(0x90);
    *(int **)(puVar1 + 0xdc) = piVar2;
    if (piVar2 == (int *)0x0) {
      puVar1[0x18] = 2;
    }
  }
  return;
}



// ==== 80117938  FUN_80117938 ====

void FUN_80117938(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_8032a730)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801179d0  FUN_801179d0 ====

void FUN_801179d0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  int iVar6;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar7;
  int local_18 [4];
  
  puVar4 = &DAT_8032a670;
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar5 = (uint)*(byte *)(param_9 + 0x11) * 0x30;
  *(code **)(param_9 + 0x100) = FUN_80117da4;
  iVar6 = iVar5;
  zz_0089100_(param_9,1,1);
  *(undefined1 *)(param_9 + 0x98) = 5;
  fVar1 = FLOAT_80439830;
  *(undefined1 *)(param_9 + 0x84) = 0x10;
  fVar2 = FLOAT_80439834;
  *(float *)(param_9 + 0xa4) = fVar1;
  *(float *)(param_9 + 0x9c) = fVar1;
  *(float *)(param_9 + 0xa0) = fVar2;
  uVar7 = zz_0048288_(param_9);
  *(float *)(param_9 + 0x144) = FLOAT_80439838;
  *(undefined2 *)(param_9 + 0x1c) = 600;
  iVar3 = zz_008ac80_(param_9,(int)(char)(&DAT_8032a673)[iVar5]);
  if (iVar3 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    iVar3 = zz_0006f78_(param_9);
    uVar7 = zz_0006fb4_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                        *(int *)(param_9 + 0xe0),(uint)*(ushort *)(&DAT_8032a670 + iVar5),puVar4,
                        iVar6,in_r8,in_r9,in_r10);
    local_18[0] = 0;
    zz_0009b38_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(*(int *)(param_9 + 0xe0) + 0xc),*(int *)(*(int *)(param_9 + 0xdc) + 0xc),
                local_18,puVar4,iVar6,in_r8,in_r9,in_r10);
    gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(&DAT_8032a680 + iVar5),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_8032a680 + iVar5);
    *(char *)(param_9 + 0x1cb) = (char)*(undefined4 *)(&DAT_8032a684 + iVar5);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    *(undefined2 *)(param_9 + 0x72) = 0;
    zz_0117b20_(param_9);
    zz_00f036c_(param_9,0xde);
  }
  return;
}



// ==== 80117b20  zz_0117b20_ ====

void zz_0117b20_(int param_1)

{
  float fVar1;
  int iVar2;
  undefined4 auStack_28 [3];
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
  *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  *(byte *)(param_1 + 0x12) =
       (char)*(undefined4 *)(PTR_DAT_80433934 + 0xb0) + *(char *)(param_1 + 0x11) & 3;
  if (*(char *)(param_1 + 0x11) == '\0') {
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + -0x1000;
  }
  else {
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + 0x1000;
  }
  if (*(short *)(param_1 + 0x1c) < 1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x20),10);
  }
  else {
    iVar2 = zz_0083244_((float *)(param_1 + 0x20));
    fVar1 = FLOAT_80439834;
    if (iVar2 == 0) {
      iVar2 = (uint)*(byte *)(param_1 + 0x11) * 0x30;
      *(float *)(param_1 + 0x144) = (float)((double)*(float *)(param_1 + 0x144) + DOUBLE_80439840);
      if (fVar1 < *(float *)(param_1 + 0x144)) {
        *(float *)(param_1 + 0x144) = fVar1;
      }
      if (*(char *)(param_1 + 0x1d9) == '\0') {
        FUN_80083874((double)*(float *)(&DAT_8032a68c + iVar2),param_1);
        FUN_80083ad4((double)*(float *)(&DAT_8032a688 + iVar2),param_1,
                     (char)*(undefined4 *)(&DAT_8032a684 + iVar2));
        zz_00833ec_(param_1);
        zz_0083524_(param_1);
        iVar2 = zz_0083714_(param_1);
        if (iVar2 == 0) {
          iVar2 = zz_003ecb8_((float *)(param_1 + 0x20),(float *)(param_1 + 0x2c),&local_1c,
                              auStack_28);
          if (iVar2 != 0) {
            *(float *)(param_1 + 0x20) = local_1c;
            *(undefined4 *)(param_1 + 0x24) = local_18;
            *(undefined4 *)(param_1 + 0x28) = local_14;
            FUN_8001b9ac((double)*(float *)(param_1 + 0xb4),&local_1c,auStack_28);
            *(undefined1 *)(param_1 + 0x18) = 2;
            zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x20),10);
          }
        }
        else {
          *(undefined1 *)(param_1 + 0x18) = 2;
          zz_008aff0_(param_1);
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x18) = 2;
        zz_008aff0_(param_1);
        zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x20),10);
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x18) = 2;
      zz_008aff0_(param_1);
    }
  }
  return;
}



// ==== 80117d28  FUN_80117d28 ====

void FUN_80117d28(int param_1)

{
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  zz_0089444_(param_1);
  if (*(int **)(param_1 + 0xdc) != (int *)0x0) {
    zz_0197ad8_(*(int **)(param_1 + 0xdc));
    *(undefined4 *)(param_1 + 0xdc) = 0;
  }
  return;
}



// ==== 80117d84  FUN_80117d84 ====

void FUN_80117d84(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80117da4  FUN_80117da4 ====

/* WARNING: Removing unreachable block (ram,0x80117e90) */
/* WARNING: Removing unreachable block (ram,0x80117e88) */
/* WARNING: Removing unreachable block (ram,0x80117e80) */
/* WARNING: Removing unreachable block (ram,0x80117dc4) */
/* WARNING: Removing unreachable block (ram,0x80117dbc) */
/* WARNING: Removing unreachable block (ram,0x80117db4) */

void FUN_80117da4(int param_1)

{
  float *pfVar1;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar2;
  uint uVar3;
  double dVar4;
  undefined8 uVar5;
  double dVar6;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  double dVar7;
  double dVar8;
  double dVar9;
  int local_88;
  float afStack_84 [16];
  
  zz_0048288_(param_1);
  dVar4 = (double)*(float *)(param_1 + 0x144);
  dVar6 = dVar4;
  gnt4_PSMTXScale_bl(dVar4,dVar4,dVar4,afStack_84);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_84,(float *)(param_1 + 0x114));
  iVar2 = 0;
  uVar3 = (uint)*(char *)(param_1 + 0x12);
  pfVar1 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  do {
    dVar9 = (double)pfVar1[0xf];
    dVar8 = (double)pfVar1[0x13];
    dVar7 = (double)pfVar1[0x17];
    uVar5 = gnt4_PSMTXRotRad_bl((double)*(float *)(&DAT_8032a660 + uVar3 * 4),pfVar1 + 0xc,0x7a);
    pfVar1[0xf] = (float)dVar9;
    iVar2 = iVar2 + 1;
    pfVar1[0x13] = (float)dVar8;
    uVar3 = uVar3 + 2 & 3;
    pfVar1[0x17] = (float)dVar7;
    pfVar1 = pfVar1 + 0xc;
  } while (iVar2 < 2);
  local_88 = 0;
  zz_0009a14_(uVar5,dVar4,dVar6,in_f4,in_f5,in_f6,in_f7,in_f8,
              *(int *)(*(int *)(param_1 + 0xe0) + 0xc),(float *)(param_1 + 0x114),
              *(int *)(*(int *)(param_1 + 0xdc) + 0xc),&local_88,in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 80117eac  FUN_80117eac ====

void FUN_80117eac(int param_1)

{
  zz_00097b4_(*(int *)(param_1 + 0xe0),0x45);
  return;
}



