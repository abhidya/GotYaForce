// ==== 80227764  gnt4-GXSetLineWidth-bl ====

void gnt4_GXSetLineWidth_bl(uint param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  *(uint *)(DAT_8043cb00 + 0x7c) = param_1 & 0xff | *(uint *)(DAT_8043cb00 + 0x7c) & 0xffffff00;
  *(uint *)(iVar1 + 0x7c) = (param_2 & 7) << 0x10 | *(uint *)(iVar1 + 0x7c) & 0xfff8ffff;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(iVar1 + 0x7c);
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}



// ==== 802277a4  gnt4-GXSetPointSize-bl ====

void gnt4_GXSetPointSize_bl(uint param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  *(uint *)(DAT_8043cb00 + 0x7c) =
       (param_1 & 0xff) << 8 | *(uint *)(DAT_8043cb00 + 0x7c) & 0xffff00ff;
  *(uint *)(iVar1 + 0x7c) = (param_2 & 7) << 0x13 | *(uint *)(iVar1 + 0x7c) & 0xffc7ffff;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(iVar1 + 0x7c);
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}



// ==== 802277e4  gnt4-GXEnableTexOffsets-bl ====

void gnt4_GXEnableTexOffsets_bl(int param_1,uint param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_8043cb00;
  iVar2 = DAT_8043cb00 + param_1 * 4;
  *(uint *)(iVar2 + 0xb8) = (param_2 & 1) << 0x12 | *(uint *)(iVar2 + 0xb8) & 0xfffbffff;
  *(uint *)(iVar2 + 0xb8) = (param_3 & 1) << 0x13 | *(uint *)(iVar2 + 0xb8) & 0xfff7ffff;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(iVar2 + 0xb8);
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}



// ==== 8022782c  gnt4-GXSetCullMode-bl ====

void gnt4_GXSetCullMode_bl(uint param_1)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  if (param_1 == 2) {
    param_1 = 1;
  }
  else if (((int)param_1 < 2) && (0 < (int)param_1)) {
    param_1 = 2;
  }
  *(uint *)(DAT_8043cb00 + 0x204) =
       (param_1 & 3) << 0xe | *(uint *)(DAT_8043cb00 + 0x204) & 0xffff3fff;
  *(uint *)(iVar1 + 0x5ac) = *(uint *)(iVar1 + 0x5ac) | 4;
  return;
}



// ==== 80227870  gnt4-GXSetCoPlanar-bl ====

void gnt4_GXSetCoPlanar_bl(uint param_1)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  *(uint *)(DAT_8043cb00 + 0x204) =
       (param_1 & 1) << 0x13 | *(uint *)(DAT_8043cb00 + 0x204) & 0xfff7ffff;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = 0xfe080000;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(iVar1 + 0x204);
  return;
}



// ==== 802278a4  gnt4-__GXSetGenMode-bl ====

void gnt4___GXSetGenMode_bl(void)

{
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(DAT_8043cb00 + 0x204);
  *(undefined2 *)(DAT_8043cb00 + 2) = 0;
  return;
}



// ==== 802278c8  zz_02278c8_ ====

void zz_02278c8_(uint *param_1,uint *param_2,ushort param_3,uint param_4)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = (param_4 & 0x7fff) * 2;
  if (param_1 != param_2) {
    uVar3 = param_1[1];
    *param_2 = *param_1;
    param_2[1] = uVar3;
    uVar3 = param_1[3];
    param_2[2] = param_1[2];
    param_2[3] = uVar3;
    uVar3 = param_1[5];
    param_2[4] = param_1[4];
    param_2[5] = uVar3;
    uVar3 = param_1[7];
    param_2[6] = param_1[6];
    param_2[7] = uVar3;
    uVar3 = param_1[9];
    param_2[8] = param_1[8];
    param_2[9] = uVar3;
    uVar3 = param_1[0xb];
    param_2[10] = param_1[10];
    param_2[0xb] = uVar3;
    uVar3 = param_1[0xd];
    param_2[0xc] = param_1[0xc];
    param_2[0xd] = uVar3;
    param_2[0xe] = param_1[0xe];
  }
  *(ushort *)(param_2 + 1) = *(short *)(param_1 + 1) + param_3 * -2;
  *(ushort *)((int)param_2 + 6) =
       *(ushort *)((int)param_1 + 6) -
       (short)((iVar2 * (uint)*(ushort *)((int)param_1 + 6)) / (uint)*(ushort *)(param_1 + 2));
  sVar1 = (short)iVar2;
  if ((param_1[5] == 0) && ((*param_1 & 2) != 2)) {
    *(short *)(param_2 + 2) = *(short *)(param_1 + 2) - (short)param_4;
  }
  else {
    *(short *)(param_2 + 2) = *(short *)(param_1 + 2) - sVar1;
  }
  *(ushort *)((int)param_2 + 0xe) = *(short *)((int)param_1 + 0xe) + param_3 * -2;
  *(short *)(param_2 + 4) = *(short *)(param_1 + 4) - sVar1;
  *(ushort *)((int)param_2 + 10) = *(short *)((int)param_1 + 10) + param_3;
  *(short *)(param_2 + 3) = *(short *)(param_1 + 3) + (short)param_4;
  return;
}



// ==== 802279e8  gnt4-GXSetDispCopySrc-bl ====

void gnt4_GXSetDispCopySrc_bl(uint param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  *(undefined4 *)(DAT_8043cb00 + 0x1e0) = 0;
  *(uint *)(iVar1 + 0x1e0) = param_1 & 0x3ff | *(uint *)(iVar1 + 0x1e0) & 0xfffffc00;
  *(uint *)(iVar1 + 0x1e0) = (param_2 & 0x3ff) << 10 | *(uint *)(iVar1 + 0x1e0) & 0xfff003ff;
  *(uint *)(iVar1 + 0x1e0) = *(uint *)(iVar1 + 0x1e0) & 0xffffff | 0x49000000;
  *(undefined4 *)(iVar1 + 0x1e4) = 0;
  *(uint *)(iVar1 + 0x1e4) = (param_3 & 0xffff) - 1 & 0x3ff | *(uint *)(iVar1 + 0x1e4) & 0xfffffc00;
  *(uint *)(iVar1 + 0x1e4) =
       ((param_4 & 0xffff) - 1) * 0x400 & 0xffc00 | *(uint *)(iVar1 + 0x1e4) & 0xfff003ff;
  *(uint *)(iVar1 + 0x1e4) = *(uint *)(iVar1 + 0x1e4) & 0xffffff | 0x4a000000;
  return;
}



// ==== 80227a64  gnt4-GXSetTexCopySrc-bl ====

void gnt4_GXSetTexCopySrc_bl(uint param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  *(undefined4 *)(DAT_8043cb00 + 0x1f0) = 0;
  *(uint *)(iVar1 + 0x1f0) = param_1 & 0x3ff | *(uint *)(iVar1 + 0x1f0) & 0xfffffc00;
  *(uint *)(iVar1 + 0x1f0) = (param_2 & 0x3ff) << 10 | *(uint *)(iVar1 + 0x1f0) & 0xfff003ff;
  *(uint *)(iVar1 + 0x1f0) = *(uint *)(iVar1 + 0x1f0) & 0xffffff | 0x49000000;
  *(undefined4 *)(iVar1 + 500) = 0;
  *(uint *)(iVar1 + 500) = (param_3 & 0xffff) - 1 & 0x3ff | *(uint *)(iVar1 + 500) & 0xfffffc00;
  *(uint *)(iVar1 + 500) =
       ((param_4 & 0xffff) - 1) * 0x400 & 0xffc00 | *(uint *)(iVar1 + 500) & 0xfff003ff;
  *(uint *)(iVar1 + 500) = *(uint *)(iVar1 + 500) & 0xffffff | 0x4a000000;
  return;
}



// ==== 80227ae0  gnt4-GXSetDispCopyDst-bl ====

void gnt4_GXSetDispCopyDst_bl(uint param_1)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  *(undefined4 *)(DAT_8043cb00 + 0x1e8) = 0;
  *(uint *)(iVar1 + 0x1e8) =
       (int)((param_1 & 0x7fff) << 1) >> 5 & 0x3ffU | *(uint *)(iVar1 + 0x1e8) & 0xfffffc00;
  *(uint *)(iVar1 + 0x1e8) = *(uint *)(iVar1 + 0x1e8) & 0xffffff | 0x4d000000;
  return;
}



// ==== 80227b14  gnt4-GXSetTexCopyDst-bl ====

void gnt4_GXSetTexCopyDst_bl(ushort param_1,ushort param_2,uint param_3,uint param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int local_14;
  int iStack_10;
  int local_c;
  
  uVar3 = param_3 & 0xf;
  *(undefined1 *)(DAT_8043cb00 + 0x200) = 0;
  if (param_3 == 0x13) {
    uVar3 = 0xb;
  }
  if ((param_3 == 0x26) || ((((int)param_3 < 0x26 && ((int)param_3 < 4)) && (-1 < (int)param_3)))) {
    *(uint *)(DAT_8043cb00 + 0x1fc) = *(uint *)(DAT_8043cb00 + 0x1fc) & 0xfffe7fff | 0x18000;
  }
  else {
    *(uint *)(DAT_8043cb00 + 0x1fc) = *(uint *)(DAT_8043cb00 + 0x1fc) & 0xfffe7fff | 0x10000;
  }
  iVar1 = DAT_8043cb00;
  uVar2 = countLeadingZeros((param_3 & 0x10) - 0x10);
  *(char *)(DAT_8043cb00 + 0x200) = (char)(uVar2 >> 5);
  *(uint *)(iVar1 + 0x1fc) = uVar3 & 8 | *(uint *)(iVar1 + 0x1fc) & 0xfffffff7;
  gnt4___GetImageTileCount_bl(param_3,param_1,param_2,&local_c,&iStack_10,&local_14);
  iVar1 = DAT_8043cb00;
  *(undefined4 *)(DAT_8043cb00 + 0x1f8) = 0;
  *(uint *)(iVar1 + 0x1f8) = local_c * local_14 & 0x3ffU | *(uint *)(iVar1 + 0x1f8) & 0xfffffc00;
  *(uint *)(iVar1 + 0x1f8) = *(uint *)(iVar1 + 0x1f8) & 0xffffff | 0x4d000000;
  *(uint *)(iVar1 + 0x1fc) = (param_4 & 1) << 9 | *(uint *)(iVar1 + 0x1fc) & 0xfffffdff;
  *(uint *)(iVar1 + 0x1fc) = (uVar3 & 7) << 4 | *(uint *)(iVar1 + 0x1fc) & 0xffffff8f;
  return;
}



// ==== 80227c44  gnt4-GXSetDispCopyFrame2Field-bl ====

void gnt4_GXSetDispCopyFrame2Field_bl(uint param_1)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  *(uint *)(DAT_8043cb00 + 0x1ec) =
       (param_1 & 3) << 0xc | *(uint *)(DAT_8043cb00 + 0x1ec) & 0xffffcfff;
  *(uint *)(iVar1 + 0x1fc) = *(uint *)(iVar1 + 0x1fc) & 0xffffcfff;
  return;
}



// ==== 80227c68  gnt4-GXSetCopyClamp-bl ====

void gnt4_GXSetCopyClamp_bl(uint param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  iVar1 = DAT_8043cb00;
  uVar3 = countLeadingZeros((param_1 & 1) - 1);
  *(uint *)(DAT_8043cb00 + 0x1ec) = uVar3 >> 5 & 1 | *(uint *)(DAT_8043cb00 + 0x1ec) & 0xfffffffe;
  uVar2 = countLeadingZeros((param_1 & 2) - 2);
  *(uint *)(iVar1 + 0x1ec) = (uVar2 >> 5 & 1) << 1 | *(uint *)(iVar1 + 0x1ec) & 0xfffffffd;
  *(uint *)(iVar1 + 0x1fc) = uVar3 >> 5 & 1 | *(uint *)(iVar1 + 0x1fc) & 0xfffffffe;
  *(uint *)(iVar1 + 0x1fc) = (uVar2 >> 5 & 1) << 1 | *(uint *)(iVar1 + 0x1fc) & 0xfffffffd;
  return;
}



// ==== 80227cc0  gnt4-GXSetDispCopyYScale-bl ====

uint gnt4_GXSetDispCopyYScale_bl(double param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  
  uVar2 = gnt4___cvt_fp2unsigned_bl((double)(float)((double)FLOAT_8043cb28 / param_1));
  iVar1 = DAT_8043cb00;
  uVar2 = uVar2 & 0x1ff;
  iVar5 = -uVar2 + 0x100;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar2 | 0x4e000000;
  *(undefined2 *)(DAT_8043cb00 + 2) = 0;
  *(uint *)(iVar1 + 0x1ec) =
       (iVar5 - ((uint)(iVar5 == 0) + -uVar2 + 0xff)) * 0x400 & 0x400 |
       *(uint *)(iVar1 + 0x1ec) & 0xfffffbff;
  uVar3 = (*(uint *)(iVar1 + 0x1e4) >> 2 & 0x3ff00) / uVar2;
  uVar6 = (*(uint *)(iVar1 + 0x1e4) >> 10 & 0x3ff) + 1;
  uVar4 = uVar3 + 1;
  if ((0x80 < uVar2) && (uVar2 < 0x100)) {
    for (; (uVar2 & 1) == 0; uVar2 = uVar2 >> 1) {
    }
    if (uVar6 == (uVar6 / uVar2) * uVar2) {
      uVar4 = uVar3 + 2;
    }
  }
  if (0x400 < uVar4) {
    uVar4 = 0x400;
  }
  return uVar4;
}



// ==== 80227d8c  gnt4-GXSetCopyClear-bl ====

void gnt4_GXSetCopyClear_bl(undefined1 *param_1,uint param_2)

{
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = CONCAT11(param_1[3],*param_1) | 0x4f000000;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(ushort *)(param_1 + 1) | 0x50000000;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = param_2 & 0xffffff | 0x51000000;
  *(undefined2 *)(DAT_8043cb00 + 2) = 0;
  return;
}



// ==== 80227e04  gnt4-GXSetCopyFilter-bl ====

void gnt4_GXSetCopyFilter_bl(char param_1,byte *param_2,char param_3,byte *param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  if (param_1 == '\0') {
    uVar1 = 0x1666666;
    uVar2 = 0x2666666;
    uVar3 = 0x3666666;
    uVar4 = 0x4666666;
  }
  else {
    uVar1 = (param_2[5] & 0xf) << 0x14 |
            (param_2[4] & 0xf) << 0x10 |
            (param_2[3] & 0xf) << 0xc |
            (param_2[2] & 0xf) << 8 | (param_2[1] & 0xf) << 4 | *param_2 & 0xf | 0x1000000;
    uVar2 = (param_2[0xb] & 0xf) << 0x14 |
            (param_2[10] & 0xf) << 0x10 |
            (param_2[9] & 0xf) << 0xc |
            (param_2[8] & 0xf) << 8 | (param_2[7] & 0xf) << 4 | param_2[6] & 0xf | 0x2000000;
    uVar3 = (param_2[0x11] & 0xf) << 0x14 |
            (param_2[0x10] & 0xf) << 0x10 |
            (param_2[0xf] & 0xf) << 0xc |
            (param_2[0xe] & 0xf) << 8 | (param_2[0xd] & 0xf) << 4 | param_2[0xc] & 0xf | 0x3000000;
    uVar4 = (param_2[0x17] & 0xf) << 0x14 |
            (param_2[0x16] & 0xf) << 0x10 |
            (param_2[0x15] & 0xf) << 0xc |
            (param_2[0x14] & 0xf) << 8 | (param_2[0x13] & 0xf) << 4 | param_2[0x12] & 0xf |
            0x4000000;
  }
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar1;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar2;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar3;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar4;
  if (param_3 == '\0') {
    uVar1 = 0x54000015;
    uVar2 = 0x53595000;
  }
  else {
    uVar2 = (param_4[3] & 0x3f) << 0x12 |
            (param_4[2] & 0x3f) << 0xc | (param_4[1] & 0x3f) << 6 | *param_4 & 0x3f | 0x53000000;
    uVar1 = (param_4[6] & 0x3f) << 0xc | (param_4[5] & 0x3f) << 6 | param_4[4] & 0x3f | 0x54000000;
  }
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar2;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar1;
  *(undefined2 *)(DAT_8043cb00 + 2) = 0;
  return;
}



// ==== 8022800c  gnt4-GXSetDispCopyGamma-bl ====

void gnt4_GXSetDispCopyGamma_bl(uint param_1)

{
  *(uint *)(DAT_8043cb00 + 0x1ec) =
       (param_1 & 3) << 7 | *(uint *)(DAT_8043cb00 + 0x1ec) & 0xfffffe7f;
  return;
}



// ==== 80228020  gnt4-GXCopyDisp-bl ====

void gnt4_GXCopyDisp_bl(uint param_1,uint param_2)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = DAT_8043cb00;
  if ((param_2 & 0xff) != 0) {
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(uint *)(DAT_8043cb00 + 0x1d8) & 0xfffffff0 | 0xf;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(uint *)(DAT_8043cb00 + 0x1d0) & 0xfffffffc;
  }
  bVar1 = false;
  if ((param_2 & 0xff) == 0) {
    if ((*(uint *)(DAT_8043cb00 + 0x1dc) & 7) != 3) goto LAB_802280b8;
  }
  if ((*(uint *)(DAT_8043cb00 + 0x1dc) >> 6 & 1) == 1) {
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(uint *)(DAT_8043cb00 + 0x1dc) & 0xffffffbf;
    bVar1 = true;
  }
LAB_802280b8:
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(DAT_8043cb00 + 0x1e0);
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(DAT_8043cb00 + 0x1e4);
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(DAT_8043cb00 + 0x1e8);
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = param_1 >> 5 & 0x1fffff | 0x4b000000;
  *(uint *)(DAT_8043cb00 + 0x1ec) =
       (param_2 & 1) << 0xb | *(uint *)(DAT_8043cb00 + 0x1ec) & 0xfffff7ff;
  *(uint *)(iVar2 + 0x1ec) = *(uint *)(iVar2 + 0x1ec) & 0xffffbfff | 0x4000;
  *(uint *)(iVar2 + 0x1ec) = *(uint *)(iVar2 + 0x1ec) & 0xffffff | 0x52000000;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(iVar2 + 0x1ec);
  if ((param_2 & 0xff) != 0) {
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(undefined4 *)(iVar2 + 0x1d8);
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(undefined4 *)(iVar2 + 0x1d0);
  }
  if (bVar1) {
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(undefined4 *)(DAT_8043cb00 + 0x1dc);
  }
  *(undefined2 *)(DAT_8043cb00 + 2) = 0;
  return;
}



// ==== 80228188  gnt4-GXCopyTex-bl ====

void gnt4_GXCopyTex_bl(uint param_1,uint param_2)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = DAT_8043cb00;
  if ((param_2 & 0xff) != 0) {
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(uint *)(DAT_8043cb00 + 0x1d8) & 0xfffffff0 | 0xf;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(uint *)(DAT_8043cb00 + 0x1d0) & 0xfffffffc;
  }
  bVar1 = false;
  uVar3 = *(uint *)(DAT_8043cb00 + 0x1dc);
  if (*(char *)(DAT_8043cb00 + 0x200) != '\0') {
    if ((uVar3 & 7) != 3) {
      uVar3 = uVar3 & 0xfffffff8 | 3;
      bVar1 = true;
    }
  }
  if ((param_2 & 0xff) == 0) {
    if ((uVar3 & 7) != 3) goto LAB_8022822c;
  }
  if ((uVar3 >> 6 & 1) == 1) {
    uVar3 = uVar3 & 0xffffffbf;
    bVar1 = true;
  }
LAB_8022822c:
  if (bVar1) {
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = uVar3;
  }
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(DAT_8043cb00 + 0x1f0);
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(DAT_8043cb00 + 500);
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(DAT_8043cb00 + 0x1f8);
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = param_1 >> 5 & 0x1fffff | 0x4b000000;
  *(uint *)(DAT_8043cb00 + 0x1fc) =
       (param_2 & 1) << 0xb | *(uint *)(DAT_8043cb00 + 0x1fc) & 0xfffff7ff;
  *(uint *)(iVar2 + 0x1fc) = *(uint *)(iVar2 + 0x1fc) & 0xffffbfff;
  *(uint *)(iVar2 + 0x1fc) = *(uint *)(iVar2 + 0x1fc) & 0xffffff | 0x52000000;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(iVar2 + 0x1fc);
  if ((param_2 & 0xff) != 0) {
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(undefined4 *)(iVar2 + 0x1d8);
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(undefined4 *)(iVar2 + 0x1d0);
  }
  if (bVar1) {
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(undefined4 *)(DAT_8043cb00 + 0x1dc);
  }
  *(undefined2 *)(DAT_8043cb00 + 2) = 0;
  return;
}



// ==== 80228314  gnt4-GXClearBoundingBox-bl ====

void gnt4_GXClearBoundingBox_bl(void)

{
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = 0x550003ff;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = 0x560003ff;
  *(undefined2 *)(DAT_8043cb00 + 2) = 0;
  return;
}



// ==== 8022834c  gnt4-GXInitLightAttn-bl ====

void gnt4_GXInitLightAttn_bl
               (double param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,int param_7)

{
  *(float *)(param_7 + 0x10) = (float)param_1;
  *(float *)(param_7 + 0x14) = (float)param_2;
  *(float *)(param_7 + 0x18) = (float)param_3;
  *(float *)(param_7 + 0x1c) = (float)param_4;
  *(float *)(param_7 + 0x20) = (float)param_5;
  *(float *)(param_7 + 0x24) = (float)param_6;
  return;
}



// ==== 80228368  gnt4-GXInitLightSpot-bl ====

void gnt4_GXInitLightSpot_bl(double param_1,int param_2,undefined4 param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  if ((param_1 <= (double)FLOAT_8043cb30) || ((double)FLOAT_8043cb34 < param_1)) {
    param_3 = 0;
  }
  fVar3 = gnt4_cosf((float)((double)FLOAT_8043cb38 * param_1) / FLOAT_8043cb3c);
  fVar2 = FLOAT_8043cb30;
  switch(param_3) {
  default:
    fVar1 = FLOAT_8043cb30;
    fVar3 = FLOAT_8043cb48;
    break;
  case 1:
    fVar3 = FLOAT_8043cb40 * fVar3;
    fVar1 = FLOAT_8043cb44;
    break;
  case 2:
    fVar1 = FLOAT_8043cb48 / (FLOAT_8043cb48 - fVar3);
    fVar3 = -fVar3 * fVar1;
    break;
  case 3:
    fVar2 = FLOAT_8043cb48 / (FLOAT_8043cb48 - fVar3);
    fVar1 = -fVar3 * fVar2;
    fVar3 = FLOAT_8043cb30;
    break;
  case 4:
    fVar2 = FLOAT_8043cb48 / ((FLOAT_8043cb48 - fVar3) * (FLOAT_8043cb48 - fVar3));
    fVar3 = fVar2 * fVar3 * (fVar3 - FLOAT_8043cb4c);
    fVar1 = FLOAT_8043cb4c * fVar2;
    fVar2 = -fVar2;
    break;
  case 5:
    fVar1 = FLOAT_8043cb48 / ((FLOAT_8043cb48 - fVar3) * (FLOAT_8043cb48 - fVar3));
    fVar2 = FLOAT_8043cb50 * fVar1;
    fVar1 = FLOAT_8043cb54 * (FLOAT_8043cb48 + fVar3) * fVar1;
    fVar3 = fVar2 * fVar3;
    break;
  case 6:
    fVar2 = FLOAT_8043cb48 / ((FLOAT_8043cb48 - fVar3) * (FLOAT_8043cb48 - fVar3));
    fVar1 = FLOAT_8043cb54 * fVar3 * fVar2;
    fVar3 = FLOAT_8043cb48 - fVar2 * FLOAT_8043cb4c * fVar3 * fVar3;
    fVar2 = FLOAT_8043cb58 * fVar2;
  }
  *(float *)(param_2 + 0x10) = fVar3;
  *(float *)(param_2 + 0x14) = fVar1;
  *(float *)(param_2 + 0x18) = fVar2;
  return;
}



// ==== 802284f8  gnt4-GXInitLightDistAttn-bl ====

void gnt4_GXInitLightDistAttn_bl(double param_1,double param_2,int param_3,int param_4)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  if (param_1 < (double)FLOAT_8043cb30) {
    param_4 = 0;
  }
  if ((param_2 <= (double)FLOAT_8043cb30) || ((double)FLOAT_8043cb48 <= param_2)) {
    param_4 = 0;
  }
  if (param_4 == 2) {
    dVar3 = (double)(FLOAT_8043cb5c * (float)((double)FLOAT_8043cb48 - param_2));
    fVar1 = (float)(dVar3 / (double)(float)(param_1 * (double)(float)(param_2 * param_1)));
    fVar2 = (float)(dVar3 / (double)(float)(param_2 * param_1));
  }
  else {
    fVar1 = FLOAT_8043cb30;
    fVar2 = FLOAT_8043cb30;
    if (param_4 < 2) {
      if ((param_4 != 0) && (-1 < param_4)) {
        fVar2 = (float)((double)FLOAT_8043cb48 - param_2) / (float)(param_2 * param_1);
      }
    }
    else if (param_4 < 4) {
      fVar1 = (float)((double)FLOAT_8043cb48 - param_2) /
              (float)(param_1 * (double)(float)(param_2 * param_1));
    }
  }
  *(float *)(param_3 + 0x1c) = FLOAT_8043cb48;
  *(float *)(param_3 + 0x20) = fVar2;
  *(float *)(param_3 + 0x24) = fVar1;
  return;
}



// ==== 802285c8  gnt4-GXInitLightPos-bl ====

void gnt4_GXInitLightPos_bl(double param_1,double param_2,double param_3,int param_4)

{
  *(float *)(param_4 + 0x28) = (float)param_1;
  *(float *)(param_4 + 0x2c) = (float)param_2;
  *(float *)(param_4 + 0x30) = (float)param_3;
  return;
}



// ==== 802285d8  gnt4-GXInitLightDir-bl ====

void gnt4_GXInitLightDir_bl(double param_1,double param_2,double param_3,int param_4)

{
  *(float *)(param_4 + 0x34) = (float)-param_1;
  *(float *)(param_4 + 0x38) = (float)-param_2;
  *(float *)(param_4 + 0x3c) = (float)-param_3;
  return;
}



// ==== 802285f4  gnt4-GXInitLightColor-bl ====

void gnt4_GXInitLightColor_bl(int param_1,undefined4 *param_2)

{
  *(undefined4 *)(param_1 + 0xc) = *param_2;
  return;
}



// ==== 80228600  gnt4-GXLoadLightObjImm-bl ====

/* WARNING: Removing unreachable block (ram,0x80228668) */
/* WARNING: Removing unreachable block (ram,0x80228664) */
/* WARNING: Removing unreachable block (ram,0x80228660) */
/* WARNING: Removing unreachable block (ram,0x8022865c) */
/* WARNING: Removing unreachable block (ram,0x80228658) */
/* WARNING: Removing unreachable block (ram,0x80228654) */
/* WARNING: Removing unreachable block (ram,0x80228640) */
/* WARNING: Removing unreachable block (ram,0x8022863c) */
/* WARNING: Removing unreachable block (ram,0x80228638) */
/* WARNING: Removing unreachable block (ram,0x80228634) */
/* WARNING: Removing unreachable block (ram,0x80228630) */
/* WARNING: Removing unreachable block (ram,0x8022862c) */

void gnt4_GXLoadLightObjImm_bl(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = countLeadingZeros(param_2);
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = ((0x1f - iVar1) * 0x10 & 0x70U) + 0x600 | 0xf0000;
  DAT_cc008000 = 0;
  DAT_cc008000 = 0;
  DAT_cc008000 = 0;
  DAT_cc008000 = *(undefined4 *)(param_1 + 0xc);
  DAT_cc008000 = *(undefined4 *)(param_1 + 0x10);
  DAT_cc008004 = *(undefined4 *)(param_1 + 0x14);
  DAT_cc008000 = *(undefined4 *)(param_1 + 0x18);
  DAT_cc008004 = *(undefined4 *)(param_1 + 0x1c);
  DAT_cc008000 = *(undefined4 *)(param_1 + 0x20);
  DAT_cc008004 = *(undefined4 *)(param_1 + 0x24);
  DAT_cc008000 = *(undefined4 *)(param_1 + 0x28);
  DAT_cc008004 = *(undefined4 *)(param_1 + 0x2c);
  DAT_cc008000 = *(undefined4 *)(param_1 + 0x30);
  DAT_cc008004 = *(undefined4 *)(param_1 + 0x34);
  DAT_cc008000 = *(undefined4 *)(param_1 + 0x38);
  DAT_cc008004 = *(undefined4 *)(param_1 + 0x3c);
  *(undefined2 *)(DAT_8043cb00 + 2) = 1;
  return;
}



// ==== 8022867c  gnt4-GXSetChanAmbColor-bl ====

void gnt4_GXSetChanAmbColor_bl(int param_1,uint *param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  
  if (param_1 == 3) {
    gnt4___GXSetChanAmbColor_bl
              (DAT_8043cb00,param_2,1,param_4,
               (uint)(byte)*param_2 | *(uint *)(DAT_8043cb00 + 0xac) & 0xffffff00);
    return;
  }
  if (2 < param_1) {
    if (param_1 == 5) {
      gnt4___GXSetChanAmbColor_bl(5,param_2,1,param_4,*param_2);
      return;
    }
    if (4 < param_1) {
      return;
    }
    gnt4___GXSetChanAmbColor_bl(param_1,param_2,0,param_4,*param_2);
    return;
  }
  if (param_1 == 1) {
    gnt4___GXSetChanAmbColor_bl
              (*(uint *)(DAT_8043cb00 + 0xac),param_2,1,param_4,
               *(uint *)(DAT_8043cb00 + 0xac) & 0xff | *param_2 & 0xffffff00);
    return;
  }
  if (param_1 < 1) {
    if (param_1 < 0) {
      return;
    }
    gnt4___GXSetChanAmbColor_bl
              (*(uint *)(DAT_8043cb00 + 0xa8),param_2,0,param_4,
               *(uint *)(DAT_8043cb00 + 0xa8) & 0xff | *param_2 & 0xffffff00);
    return;
  }
  uVar1 = (uint)(byte)*param_2 | *(uint *)(DAT_8043cb00 + 0xa8) & 0xffffff00;
  gnt4___GXSetChanAmbColor_bl(uVar1,param_2,0,param_4,uVar1);
  return;
}



// ==== 80228738  gnt4-__GXSetChanAmbColor-bl ====

void gnt4___GXSetChanAmbColor_bl
               (undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,
               undefined4 param_5)

{
  int iVar1;
  
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = param_3 + 0x100a;
  iVar1 = DAT_8043cb00 + param_3 * 4;
  DAT_cc008000 = param_5;
  *(undefined2 *)(DAT_8043cb00 + 2) = 1;
  *(undefined4 *)(iVar1 + 0xa8) = param_5;
  return;
}



// ==== 8022876c  gnt4-GXSetChanMatColor-bl ====

void gnt4_GXSetChanMatColor_bl(int param_1,uint *param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  
  if (param_1 == 3) {
    gnt4___GXSetChanMatColor_bl
              (DAT_8043cb00,param_2,1,param_4,
               (uint)(byte)*param_2 | *(uint *)(DAT_8043cb00 + 0xb4) & 0xffffff00);
    return;
  }
  if (2 < param_1) {
    if (param_1 == 5) {
      gnt4___GXSetChanMatColor_bl(5,param_2,1,param_4,*param_2);
      return;
    }
    if (4 < param_1) {
      return;
    }
    gnt4___GXSetChanMatColor_bl(param_1,param_2,0,param_4,*param_2);
    return;
  }
  if (param_1 == 1) {
    gnt4___GXSetChanMatColor_bl
              (*(uint *)(DAT_8043cb00 + 0xb4),param_2,1,param_4,
               *(uint *)(DAT_8043cb00 + 0xb4) & 0xff | *param_2 & 0xffffff00);
    return;
  }
  if (param_1 < 1) {
    if (param_1 < 0) {
      return;
    }
    gnt4___GXSetChanMatColor_bl
              (*(uint *)(DAT_8043cb00 + 0xb0),param_2,0,param_4,
               *(uint *)(DAT_8043cb00 + 0xb0) & 0xff | *param_2 & 0xffffff00);
    return;
  }
  uVar1 = (uint)(byte)*param_2 | *(uint *)(DAT_8043cb00 + 0xb0) & 0xffffff00;
  gnt4___GXSetChanMatColor_bl(uVar1,param_2,0,param_4,uVar1);
  return;
}



// ==== 80228828  gnt4-__GXSetChanMatColor-bl ====

void gnt4___GXSetChanMatColor_bl
               (undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,
               undefined4 param_5)

{
  int iVar1;
  
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = param_3 + 0x100c;
  iVar1 = DAT_8043cb00 + param_3 * 4;
  DAT_cc008000 = param_5;
  *(undefined2 *)(DAT_8043cb00 + 2) = 1;
  *(undefined4 *)(iVar1 + 0xb0) = param_5;
  return;
}



// ==== 8022885c  gnt4-GXSetNumChans-bl ====

void gnt4_GXSetNumChans_bl(uint param_1)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  *(uint *)(DAT_8043cb00 + 0x204) =
       (param_1 & 7) << 4 | *(uint *)(DAT_8043cb00 + 0x204) & 0xffffff8f;
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = 0x1009;
  DAT_cc008000 = param_1 & 0xff;
  *(uint *)(iVar1 + 0x5ac) = *(uint *)(iVar1 + 0x5ac) | 4;
  return;
}



// ==== 80228898  gnt4-GXSetChanCtrl-bl ====

void gnt4_GXSetChanCtrl_bl
               (uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6,
               int param_7)

{
  int iVar1;
  uint uVar2;
  
  if (param_7 == 0) {
    param_6 = 0;
  }
  iVar1 = -param_7 + 2;
  DAT_cc008000._0_1_ = 0x10;
  uVar2 = (param_5 & 0xf0) << 7 |
          (param_5 & 0xf) << 2 |
          (uint)(param_7 != 0) * 0x400 |
          (iVar1 - ((uint)(iVar1 == 0) + -param_7 + 1)) * 0x200 & 0x200 |
          (param_6 & 3) << 7 | (param_3 & 1) << 6 | param_4 & 1 | (param_2 & 1) << 1;
  DAT_cc008000 = (param_1 & 3) + 0x100e;
  DAT_cc008000 = uVar2;
  if (param_1 == 4) {
    DAT_cc008000._0_1_ = 0x10;
    DAT_cc008000 = 0x1010;
    DAT_cc008000 = uVar2;
  }
  else if (param_1 == 5) {
    DAT_cc008000._0_1_ = 0x10;
    DAT_cc008000 = 0x1011;
    DAT_cc008000 = uVar2;
  }
  *(undefined2 *)(DAT_8043cb00 + 2) = 1;
  return;
}



// ==== 80228950  gnt4-GXGetTexBufferSize-bl ====

int gnt4_GXGetTexBufferSize_bl(uint param_1,uint param_2,int param_3,char param_4,uint param_5)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  
  switch(param_3) {
  case 0:
  case 8:
  case 0xe:
  case 0x20:
  case 0x30:
    iVar3 = 3;
    iVar5 = 3;
    break;
  case 1:
  case 2:
  case 9:
  case 0x11:
  case 0x22:
  case 0x27:
  case 0x28:
  case 0x29:
  case 0x2a:
  case 0x39:
  case 0x3a:
    iVar3 = 3;
    iVar5 = 2;
    break;
  case 3:
  case 4:
  case 5:
  case 6:
  case 10:
  case 0x13:
  case 0x16:
  case 0x23:
  case 0x2b:
  case 0x2c:
  case 0x3c:
    iVar3 = 2;
    iVar5 = 2;
    break;
  default:
    iVar5 = 0;
    iVar3 = 0;
  }
  if ((param_3 == 6) || (param_3 == 0x16)) {
    iVar4 = 0x40;
  }
  else {
    iVar4 = 0x20;
  }
  if (param_4 == '\x01') {
    iVar6 = 0;
    for (uVar7 = param_5 & 0xff; uVar7 != 0; uVar7 = uVar7 - 1) {
      uVar1 = param_1 & 0xffff;
      uVar2 = param_2 & 0xffff;
      iVar6 = iVar6 + iVar4 * ((int)(uVar1 + (1 << iVar3) + -1) >> iVar3) *
                              ((int)(uVar2 + (1 << iVar5) + -1) >> iVar5);
      if ((uVar1 == 1) && (uVar2 == 1)) {
        return iVar6;
      }
      if ((param_1 & 0xffff) < 2) {
        param_1 = 1;
      }
      else {
        param_1 = (int)uVar1 >> 1;
      }
      if ((param_2 & 0xffff) < 2) {
        param_2 = 1;
      }
      else {
        param_2 = (int)uVar2 >> 1;
      }
    }
  }
  else {
    iVar6 = iVar4 * ((int)((param_1 & 0xffff) + (1 << iVar3) + -1) >> iVar3) *
                    ((int)((param_2 & 0xffff) + (1 << iVar5) + -1) >> iVar5);
  }
  return iVar6;
}



// ==== 80228aac  gnt4-__GetImageTileCount-bl ====

void gnt4___GetImageTileCount_bl
               (int param_1,ushort param_2,ushort param_3,int *param_4,int *param_5,
               undefined4 *param_6)

{
  bool bVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  uVar4 = (uint)param_3;
  uVar3 = (uint)param_2;
  switch(param_1) {
  case 0:
  case 8:
  case 0xe:
  case 0x20:
  case 0x30:
    iVar5 = 3;
    iVar6 = 3;
    break;
  case 1:
  case 2:
  case 9:
  case 0x11:
  case 0x22:
  case 0x27:
  case 0x28:
  case 0x29:
  case 0x2a:
  case 0x39:
  case 0x3a:
    iVar5 = 3;
    iVar6 = 2;
    break;
  case 3:
  case 4:
  case 5:
  case 6:
  case 10:
  case 0x13:
  case 0x16:
  case 0x23:
  case 0x2b:
  case 0x2c:
  case 0x3c:
    iVar5 = 2;
    iVar6 = 2;
    break;
  default:
    iVar6 = 0;
    iVar5 = 0;
  }
  if (param_2 == 0) {
    uVar3 = 1;
  }
  if (param_3 == 0) {
    uVar4 = 1;
  }
  bVar1 = true;
  *param_4 = (int)(uVar3 + (1 << iVar5) + -1) >> iVar5;
  *param_5 = (int)(uVar4 + (1 << iVar6) + -1) >> iVar6;
  if ((param_1 != 6) && (param_1 != 0x16)) {
    bVar1 = false;
  }
  if (bVar1) {
    uVar2 = 2;
  }
  else {
    uVar2 = 1;
  }
  *param_6 = uVar2;
  return;
}



// ==== 80228b74  gnt4-GXInitTexObj-bl ====

void gnt4_GXInitTexObj_bl
               (uint *param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6,
               uint param_7,char param_8)

{
  int iVar1;
  int iVar2;
  
  gnt4_memset(param_1,0,0x20);
  *param_1 = param_6 & 3 | *param_1 & 0xfffffffc;
  *param_1 = (param_7 & 3) << 2 | *param_1 & 0xfffffff3;
  *param_1 = *param_1 & 0xffffffef | 0x10;
  if (param_8 == '\0') {
    *param_1 = *param_1 & 0xffffff1f | 0x80;
  }
  else {
    *(byte *)((int)param_1 + 0x1f) = *(byte *)((int)param_1 + 0x1f) | 1;
    if (param_5 - 8 < 3) {
      *param_1 = *param_1 & 0xffffff1f | 0xa0;
    }
    else {
      *param_1 = *param_1 & 0xffffff1f | 0xc0;
    }
    if ((param_4 & 0xffff) < (param_3 & 0xffff)) {
      iVar1 = countLeadingZeros(param_3 & 0xffff);
    }
    else {
      iVar1 = countLeadingZeros(param_4 & 0xffff);
    }
    param_1[1] = ((int)(FLOAT_8043cb60 *
                       (float)((double)CONCAT44(0x43300000,0x1f - iVar1) - DOUBLE_8043cb68)) & 0xffU
                 ) << 8 | param_1[1] & 0xffff00ff;
  }
  param_1[5] = param_5;
  param_1[2] = (param_3 & 0xffff) - 1 & 0x3ff | param_1[2] & 0xfffffc00;
  param_1[2] = ((param_4 & 0xffff) - 1) * 0x400 & 0xffc00 | param_1[2] & 0xfff003ff;
  param_1[2] = (param_5 & 0xf) << 0x14 | param_1[2] & 0xff0fffff;
  param_1[3] = param_2 >> 5 & 0x1fffff | param_1[3] & 0xffe00000;
  switch(param_5 & 0xf) {
  case 0:
  case 8:
    *(undefined1 *)((int)param_1 + 0x1e) = 1;
    iVar1 = 3;
    iVar2 = 3;
    break;
  case 1:
  case 2:
  case 9:
    *(undefined1 *)((int)param_1 + 0x1e) = 2;
    iVar1 = 3;
    iVar2 = 2;
    break;
  case 3:
  case 4:
  case 5:
  case 10:
    *(undefined1 *)((int)param_1 + 0x1e) = 2;
    iVar1 = 2;
    iVar2 = 2;
    break;
  case 6:
    *(undefined1 *)((int)param_1 + 0x1e) = 3;
    iVar1 = 2;
    iVar2 = 2;
    break;
  default:
    *(undefined1 *)((int)param_1 + 0x1e) = 2;
    iVar1 = 2;
    iVar2 = 2;
    break;
  case 0xe:
    *(undefined1 *)((int)param_1 + 0x1e) = 0;
    iVar1 = 3;
    iVar2 = 3;
  }
  *(ushort *)(param_1 + 7) =
       (short)((int)((param_3 & 0xffff) + (1 << iVar1) + -1) >> iVar1) *
       (short)((int)((param_4 & 0xffff) + (1 << iVar2) + -1) >> iVar2) & 0x7fff;
  *(byte *)((int)param_1 + 0x1f) = *(byte *)((int)param_1 + 0x1f) | 2;
  return;
}



// ==== 80228dc0  gnt4-GXInitTexObjCI-bl ====

void gnt4_GXInitTexObjCI_bl
               (uint *param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6,
               uint param_7,char param_8,uint param_9)

{
  gnt4_GXInitTexObj_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  *(byte *)((int)param_1 + 0x1f) = *(byte *)((int)param_1 + 0x1f) & 0xfd;
  param_1[6] = param_9;
  return;
}



// ==== 80228e08  gnt4-GXInitTexObjLOD-bl ====

void gnt4_GXInitTexObjLOD_bl
               (double param_1,double param_2,double param_3,uint *param_4,int param_5,int param_6,
               uint param_7,char param_8,uint param_9)

{
  double dVar1;
  double dVar2;
  double dVar3;
  
  dVar1 = (double)FLOAT_8043cb70;
  if ((dVar1 <= param_3) && (dVar1 = param_3, (double)FLOAT_8043cb74 <= param_3)) {
    dVar1 = (double)FLOAT_8043cb78;
  }
  *param_4 = ((int)((double)FLOAT_8043cb7c * dVar1) & 0xffU) << 9 | *param_4 & 0xfffe01ff;
  *param_4 = (uint)(param_6 == 1) << 4 | *param_4 & 0xffffffef;
  *param_4 = ((byte)(&DAT_80435db8)[param_5] & 7) << 5 | *param_4 & 0xffffff1f;
  *param_4 = (uint)(param_8 == '\0') << 8 | *param_4 & 0xfffffeff;
  *param_4 = *param_4 & 0xfffdffff;
  *param_4 = *param_4 & 0xfffbffff;
  *param_4 = (param_9 & 3) << 0x13 | *param_4 & 0xffe7ffff;
  *param_4 = (param_7 & 1) << 0x15 | *param_4 & 0xffdfffff;
  dVar1 = (double)FLOAT_8043cb80;
  if ((dVar1 <= param_1) && (dVar1 = param_1, (double)FLOAT_8043cb84 < param_1)) {
    dVar1 = (double)FLOAT_8043cb84;
  }
  dVar2 = (double)FLOAT_8043cb80;
  if ((dVar2 <= param_2) && (dVar2 = param_2, (double)FLOAT_8043cb84 < param_2)) {
    dVar2 = (double)FLOAT_8043cb84;
  }
  dVar3 = (double)FLOAT_8043cb60;
  param_4[1] = (int)((double)FLOAT_8043cb60 * dVar1) & 0xffU | param_4[1] & 0xffffff00;
  param_4[1] = ((int)(dVar3 * dVar2) & 0xffU) << 8 | param_4[1] & 0xffff00ff;
  return;
}



// ==== 80228f6c  gnt4-GXGetTexObjFmt-bl ====

undefined4 gnt4_GXGetTexObjFmt_bl(int param_1)

{
  return *(undefined4 *)(param_1 + 0x14);
}



// ==== 80228f74  gnt4-GXGetTexObjMipMap-bl ====

uint gnt4_GXGetTexObjMipMap_bl(int param_1)

{
  uint uVar1;
  
  uVar1 = countLeadingZeros((*(byte *)(param_1 + 0x1f) & 1) - 1);
  return uVar1 >> 5 & 0xff;
}



// ==== 80228f8c  gnt4-GXLoadTexObjPreLoaded-bl ====

void gnt4_GXLoadTexObjPreLoaded_bl(uint *param_1,uint *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  *param_1 = (uint)(byte)(&DAT_80435d80)[param_3] << 0x18 | *param_1 & 0xffffff;
  param_1[1] = (uint)(byte)(&DAT_80435d88)[param_3] << 0x18 | param_1[1] & 0xffffff;
  param_1[2] = (uint)(byte)(&DAT_80435d90)[param_3] << 0x18 | param_1[2] & 0xffffff;
  *param_2 = (uint)(byte)(&DAT_80435d98)[param_3] << 0x18 | *param_2 & 0xffffff;
  param_2[1] = (uint)(byte)(&DAT_80435da0)[param_3] << 0x18 | param_2[1] & 0xffffff;
  param_1[3] = (uint)(byte)(&DAT_80435da8)[param_3] << 0x18 | param_1[3] & 0xffffff;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *param_1;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = param_1[1];
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = param_1[2];
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *param_2;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = param_2[1];
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = param_1[3];
  if ((*(byte *)((int)param_1 + 0x1f) & 2) == 0) {
    iVar1 = (**(code **)(DAT_8043cb00 + 0x4cc))(param_1[6]);
    *(uint *)(iVar1 + 4) =
         (uint)(byte)(&DAT_80435db0)[param_3] << 0x18 | *(uint *)(iVar1 + 4) & 0xffffff;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(undefined4 *)(iVar1 + 4);
  }
  iVar1 = DAT_8043cb00;
  iVar2 = DAT_8043cb00 + param_3 * 4;
  *(uint *)(iVar2 + 0x514) = param_1[2];
  *(uint *)(iVar2 + 0x534) = *param_1;
  *(uint *)(iVar1 + 0x5ac) = *(uint *)(iVar1 + 0x5ac) | 1;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}



// ==== 80229108  gnt4-GXLoadTexObj-bl ====

void gnt4_GXLoadTexObj_bl(uint *param_1,int param_2)

{
  uint *puVar1;
  
  puVar1 = (uint *)(**(code **)(DAT_8043cb00 + 0x4c8))();
  gnt4_GXLoadTexObjPreLoaded_bl(param_1,puVar1,param_2);
  return;
}



// ==== 8022915c  gnt4-GXInitTlutObj-bl ====

void gnt4_GXInitTlutObj_bl(uint *param_1,uint param_2,uint param_3,undefined2 param_4)

{
  *param_1 = 0;
  *param_1 = (param_3 & 3) << 10 | *param_1 & 0xfffff3ff;
  param_1[1] = param_2 >> 5 & 0x1fffff | param_1[1] & 0xffe00000;
  param_1[1] = param_1[1] & 0xffffff | 0x64000000;
  *(undefined2 *)(param_1 + 2) = param_4;
  return;
}



// ==== 80229194  gnt4-GXLoadTlut-bl ====

void gnt4_GXLoadTlut_bl(uint *param_1,undefined4 param_2)

{
  uint uVar1;
  uint *puVar2;
  
  puVar2 = (uint *)(**(code **)(DAT_8043cb00 + 0x4cc))(param_2);
  gnt4___GXFlushTextureState_bl();
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = param_1[1];
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *puVar2;
  gnt4___GXFlushTextureState_bl();
  *param_1 = *puVar2 & 0x3ff | *param_1 & 0xfffffc00;
  uVar1 = param_1[1];
  puVar2[1] = *param_1;
  puVar2[2] = uVar1;
  puVar2[3] = param_1[2];
  return;
}



// ==== 8022922c  gnt4-GXInitTexCacheRegion-bl ====

void gnt4_GXInitTexCacheRegion_bl
               (uint *param_1,undefined1 param_2,uint param_3,int param_4,uint param_5,int param_6,
               uint param_7)

{
  if (param_4 == 1) {
    param_7 = 4;
  }
  else if (param_4 < 1) {
    if (-1 < param_4) {
      param_7 = 3;
    }
  }
  else if (param_4 < 3) {
    param_7 = 5;
  }
  *param_1 = 0;
  *param_1 = param_3 >> 5 & 0x7fff | *param_1 & 0xffff8000;
  *param_1 = (param_7 & 7) << 0xf | *param_1 & 0xfffc7fff;
  *param_1 = (param_7 & 7) << 0x12 | *param_1 & 0xffe3ffff;
  *param_1 = *param_1 & 0xffdfffff;
  if (param_6 == 2) {
    param_7 = 5;
  }
  else if (param_6 < 2) {
    if (param_6 == 0) {
      param_7 = 3;
    }
    else if (-1 < param_6) {
      param_7 = 4;
    }
  }
  else if (param_6 < 4) {
    param_7 = 0;
  }
  param_1[1] = 0;
  param_1[1] = param_5 >> 5 & 0x7fff | param_1[1] & 0xffff8000;
  param_1[1] = (param_7 & 7) << 0xf | param_1[1] & 0xfffc7fff;
  param_1[1] = (param_7 & 7) << 0x12 | param_1[1] & 0xffe3ffff;
  *(undefined1 *)(param_1 + 3) = param_2;
  *(undefined1 *)((int)param_1 + 0xd) = 1;
  return;
}



// ==== 80229320  gnt4-GXInitTlutRegion-bl ====

void gnt4_GXInitTlutRegion_bl(uint *param_1,int param_2,uint param_3)

{
  *param_1 = 0;
  *param_1 = param_2 - 0x80000U >> 9 & 0x3ff | *param_1 & 0xfffffc00;
  *param_1 = (param_3 & 0x7ff) << 10 | *param_1 & 0xffe003ff;
  *param_1 = *param_1 & 0xffffff | 0x65000000;
  return;
}



// ==== 80229358  gnt4-GXInvalidateTexAll-bl ====

void gnt4_GXInvalidateTexAll_bl(void)

{
  gnt4___GXFlushTextureState_bl();
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = 0x66001000;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = 0x66001100;
  gnt4___GXFlushTextureState_bl();
  return;
}



// ==== 802293a0  gnt4-GXSetTexRegionCallback-bl ====

undefined4 gnt4_GXSetTexRegionCallback_bl(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(DAT_8043cb00 + 0x4c8);
  *(undefined4 *)(DAT_8043cb00 + 0x4c8) = param_1;
  return uVar1;
}



// ==== 802293b4  gnt4-GXSetTlutRegionCallback-bl ====

undefined4 gnt4_GXSetTlutRegionCallback_bl(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(DAT_8043cb00 + 0x4cc);
  *(undefined4 *)(DAT_8043cb00 + 0x4cc) = param_1;
  return uVar1;
}



// ==== 802293c8  gnt4-__SetSURegs-bl ====

void gnt4___SetSURegs_bl(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  iVar1 = DAT_8043cb00;
  iVar2 = DAT_8043cb00 + param_1 * 4;
  uVar3 = *(uint *)(iVar2 + 0x514);
  iVar4 = DAT_8043cb00 + param_2 * 4;
  *(uint *)(iVar4 + 0xb8) = uVar3 & 0x3ff | *(uint *)(iVar4 + 0xb8) & 0xffff0000;
  *(uint *)(iVar4 + 0xd8) = uVar3 >> 10 & 0x3ff | *(uint *)(iVar4 + 0xd8) & 0xffff0000;
  uVar5 = *(uint *)(iVar2 + 0x534);
  uVar3 = countLeadingZeros(1 - (uVar5 & 3));
  *(uint *)(iVar4 + 0xb8) = (uVar3 >> 5 & 1) << 0x10 | *(uint *)(iVar4 + 0xb8) & 0xfffeffff;
  uVar3 = countLeadingZeros(1 - (uVar5 >> 2 & 3));
  *(uint *)(iVar4 + 0xd8) = (uVar3 >> 5 & 1) << 0x10 | *(uint *)(iVar4 + 0xd8) & 0xfffeffff;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(iVar4 + 0xb8);
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(iVar4 + 0xd8);
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}



// ==== 80229468  gnt4-__GXSetSUTexRegs-bl ====

void gnt4___GXSetSUTexRegs_bl(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  int iVar5;
  uint unaff_r28;
  uint unaff_r29;
  uint uVar6;
  
  if (*(int *)(DAT_8043cb00 + 0x594) != 0xff) {
    uVar3 = *(uint *)(DAT_8043cb00 + 0x204);
    for (uVar6 = 0; uVar6 < (uVar3 >> 0x10 & 7); uVar6 = uVar6 + 1) {
      if (uVar6 == 2) {
        unaff_r29 = *(uint *)(DAT_8043cb00 + 0x120) >> 0xc & 7;
        unaff_r28 = *(uint *)(DAT_8043cb00 + 0x120) >> 0xf & 7;
      }
      else if ((int)uVar6 < 2) {
        if (uVar6 == 0) {
          unaff_r29 = *(uint *)(DAT_8043cb00 + 0x120) & 7;
          unaff_r28 = *(uint *)(DAT_8043cb00 + 0x120) >> 3 & 7;
        }
        else if (-1 < (int)uVar6) {
          unaff_r29 = *(uint *)(DAT_8043cb00 + 0x120) >> 6 & 7;
          unaff_r28 = *(uint *)(DAT_8043cb00 + 0x120) >> 9 & 7;
        }
      }
      else if ((int)uVar6 < 4) {
        unaff_r29 = *(uint *)(DAT_8043cb00 + 0x120) >> 0x12 & 7;
        unaff_r28 = *(uint *)(DAT_8043cb00 + 0x120) >> 0x15 & 7;
      }
      if ((*(uint *)(DAT_8043cb00 + 0x594) & 1 << unaff_r28) == 0) {
        gnt4___SetSURegs_bl(unaff_r29,unaff_r28);
      }
    }
    iVar5 = 0;
    for (uVar6 = 0; uVar6 < (uVar3 >> 10 & 0xf) + 1; uVar6 = uVar6 + 1) {
      puVar4 = (uint *)(DAT_8043cb00 + (uVar6 & 0x7ffffffe) * 2 + 0x100);
      uVar2 = *(uint *)(DAT_8043cb00 + iVar5 + 0x554) & 0xfffffeff;
      if ((uVar6 & 1) == 0) {
        uVar1 = *puVar4 >> 3;
      }
      else {
        uVar1 = *puVar4 >> 0xf;
      }
      if (((uVar2 != 0xff) && ((*(uint *)(DAT_8043cb00 + 0x594) & 1 << (uVar1 & 7)) == 0)) &&
         ((*(uint *)(DAT_8043cb00 + 0x598) & 1 << uVar6) != 0)) {
        gnt4___SetSURegs_bl(uVar2,uVar1 & 7);
      }
      iVar5 = iVar5 + 4;
    }
  }
  return;
}



// ==== 802295e4  gnt4-__GXSetTmemConfig-bl ====

void gnt4___GXSetTmemConfig_bl(int param_1)

{
  if (param_1 == 1) {
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x8c0d8000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x900dc000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x8d0d8800;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x910dc800;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x8e0d9000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x920dd000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x8f0d9800;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x930dd800;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0xac0da000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0xb00de000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0xad0da800;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0xb10de800;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0xae0db000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0xb20df000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0xaf0db800;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0xb30df800;
  }
  else if ((param_1 < 1) || (2 < param_1)) {
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x8c0d8000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x900dc000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x8d0d8400;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x910dc400;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x8e0d8800;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x920dc800;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x8f0d8c00;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x930dcc00;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0xac0d9000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0xb00dd000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0xad0d9400;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0xb10dd400;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0xae0d9800;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0xb20dd800;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0xaf0d9c00;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0xb30ddc00;
  }
  else {
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x8c0d8000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x900dc000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x8d0d8800;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x910dc800;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x8e0d9000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x920dd000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x8f0d9800;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x930dd800;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0xac0da000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0xb00dc400;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0xad0da800;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0xb10dcc00;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0xae0db000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0xb20dd400;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0xaf0db800;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0xb30ddc00;
  }
  return;
}



// ==== 80229938  gnt4-GXSetTevIndirect-bl ====

void gnt4_GXSetTevIndirect_bl
               (int param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6,
               uint param_7,uint param_8,byte param_9,uint param_10)

{
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = (param_1 + 0x10) * 0x1000000 |
                 (param_8 & 1) << 0x14 |
                 (param_9 & 1) << 0x13 |
                 (param_7 & 7) << 0x10 |
                 (param_6 & 7) << 0xd |
                 (param_5 & 0xf) << 9 |
                 (param_10 & 3) << 7 | (param_4 & 7) << 4 | (param_3 & 3) << 2 | param_2 & 3;
  *(undefined2 *)(DAT_8043cb00 + 2) = 0;
  return;
}



// ==== 802299a4  gnt4-GXSetIndTexCoordScale-bl ====

void gnt4_GXSetIndTexCoordScale_bl(int param_1,uint param_2,uint param_3)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  if (param_1 == 2) {
    *(uint *)(DAT_8043cb00 + 300) = param_2 & 0xf | *(uint *)(DAT_8043cb00 + 300) & 0xfffffff0;
    *(uint *)(iVar1 + 300) = (param_3 & 0xf) << 4 | *(uint *)(iVar1 + 300) & 0xffffff0f;
    *(uint *)(iVar1 + 300) = *(uint *)(iVar1 + 300) & 0xffffff | 0x26000000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(undefined4 *)(iVar1 + 300);
  }
  else if (param_1 < 2) {
    if (param_1 == 0) {
      *(uint *)(DAT_8043cb00 + 0x128) = param_2 & 0xf | *(uint *)(DAT_8043cb00 + 0x128) & 0xfffffff0
      ;
      *(uint *)(iVar1 + 0x128) = (param_3 & 0xf) << 4 | *(uint *)(iVar1 + 0x128) & 0xffffff0f;
      *(uint *)(iVar1 + 0x128) = *(uint *)(iVar1 + 0x128) & 0xffffff | 0x25000000;
      DAT_cc008000._0_1_ = 0x61;
      DAT_cc008000 = *(undefined4 *)(iVar1 + 0x128);
    }
    else if (-1 < param_1) {
      *(uint *)(DAT_8043cb00 + 0x128) =
           (param_2 & 0xf) << 8 | *(uint *)(DAT_8043cb00 + 0x128) & 0xfffff0ff;
      *(uint *)(iVar1 + 0x128) = (param_3 & 0xf) << 0xc | *(uint *)(iVar1 + 0x128) & 0xffff0fff;
      *(uint *)(iVar1 + 0x128) = *(uint *)(iVar1 + 0x128) & 0xffffff | 0x25000000;
      DAT_cc008000._0_1_ = 0x61;
      DAT_cc008000 = *(undefined4 *)(iVar1 + 0x128);
    }
  }
  else if (param_1 < 4) {
    *(uint *)(DAT_8043cb00 + 300) =
         (param_2 & 0xf) << 8 | *(uint *)(DAT_8043cb00 + 300) & 0xfffff0ff;
    *(uint *)(iVar1 + 300) = (param_3 & 0xf) << 0xc | *(uint *)(iVar1 + 300) & 0xffff0fff;
    *(uint *)(iVar1 + 300) = *(uint *)(iVar1 + 300) & 0xffffff | 0x26000000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(undefined4 *)(iVar1 + 300);
  }
  *(undefined2 *)(DAT_8043cb00 + 2) = 0;
  return;
}



// ==== 80229ae8  gnt4-GXSetNumIndStages-bl ====

void gnt4_GXSetNumIndStages_bl(uint param_1)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  *(uint *)(DAT_8043cb00 + 0x204) =
       (param_1 & 7) << 0x10 | *(uint *)(DAT_8043cb00 + 0x204) & 0xfff8ffff;
  *(uint *)(iVar1 + 0x5ac) = *(uint *)(iVar1 + 0x5ac) | 6;
  return;
}



// ==== 80229b0c  gnt4-GXSetTevDirect-bl ====

void gnt4_GXSetTevDirect_bl(int param_1)

{
  gnt4_GXSetTevIndirect_bl(param_1,0,0,0,0,0,0,0,0,0);
  return;
}



// ==== 80229b54  gnt4-__GXUpdateBPMask-bl ====

void gnt4___GXUpdateBPMask_bl(void)

{
  return;
}



// ==== 80229b58  gnt4-__GXSetIndirectMask-bl ====

void gnt4___GXSetIndirectMask_bl(uint param_1)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  *(uint *)(DAT_8043cb00 + 0x124) = param_1 & 0xff | *(uint *)(DAT_8043cb00 + 0x124) & 0xffffff00;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(iVar1 + 0x124);
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}



// ==== 80229b88  gnt4-__GXFlushTextureState-bl ====

void gnt4___GXFlushTextureState_bl(void)

{
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(DAT_8043cb00 + 0x124);
  *(undefined2 *)(DAT_8043cb00 + 2) = 0;
  return;
}



// ==== 80229bac  gnt4-GXSetTevOp-bl ====

void gnt4_GXSetTevOp_bl(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint *puVar3;
  int iVar4;
  uint *puVar5;
  
  iVar1 = DAT_8043cb00;
  if (param_1 == 0) {
    puVar3 = (uint *)(&DAT_803aad30 + param_2 * 4);
    puVar5 = (uint *)(&DAT_803aad58 + param_2 * 4);
  }
  else {
    puVar3 = (uint *)(&DAT_803aad44 + param_2 * 4);
    puVar5 = (uint *)(&DAT_803aad6c + param_2 * 4);
  }
  iVar4 = DAT_8043cb00 + param_1 * 4;
  DAT_cc008000._0_1_ = 0x61;
  uVar2 = *puVar3 & 0xffffff | *(uint *)(iVar4 + 0x130) & 0xff000000;
  DAT_cc008000 = uVar2;
  *(uint *)(iVar4 + 0x130) = uVar2;
  DAT_cc008000._0_1_ = 0x61;
  uVar2 = *puVar5 & 0xfffff0 | *(uint *)(iVar4 + 0x170) & 0xff00000f;
  DAT_cc008000 = uVar2;
  *(uint *)(iVar4 + 0x170) = uVar2;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}



// ==== 80229c38  gnt4-GXSetTevColorIn-bl ====

void gnt4_GXSetTevColorIn_bl(int param_1,uint param_2,uint param_3,uint param_4,uint param_5)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar1 = DAT_8043cb00;
  iVar3 = DAT_8043cb00 + param_1 * 4;
  DAT_cc008000._0_1_ = 0x61;
  uVar2 = param_5 & 0xf |
          (param_4 & 0xf) << 4 |
          (param_3 & 0xf) << 8 | (param_2 & 0xf) << 0xc | *(uint *)(iVar3 + 0x130) & 0xffff0000;
  DAT_cc008000 = uVar2;
  *(uint *)(iVar3 + 0x130) = uVar2;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}



// ==== 80229c7c  gnt4-GXSetTevAlphaIn-bl ====

void gnt4_GXSetTevAlphaIn_bl(int param_1,uint param_2,uint param_3,uint param_4,uint param_5)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar1 = DAT_8043cb00;
  iVar3 = DAT_8043cb00 + param_1 * 4;
  DAT_cc008000._0_1_ = 0x61;
  uVar2 = (param_5 & 7) << 4 |
          (param_4 & 7) << 7 |
          (param_3 & 7) << 10 | (param_2 & 7) << 0xd | *(uint *)(iVar3 + 0x170) & 0xffff000f;
  DAT_cc008000 = uVar2;
  *(uint *)(iVar3 + 0x170) = uVar2;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}



// ==== 80229cc0  gnt4-GXSetTevColorOp-bl ====

void gnt4_GXSetTevColorOp_bl
               (int param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  iVar1 = DAT_8043cb00;
  uVar2 = *(uint *)(DAT_8043cb00 + param_1 * 4 + 0x130);
  uVar3 = (param_2 & 1) << 0x12;
  if ((int)param_2 < 2) {
    uVar3 = (param_3 & 3) << 0x10 | (param_4 & 3) << 0x14 | uVar3 | uVar2 & 0xffc8ffff;
  }
  else {
    uVar3 = (param_2 & 6) << 0x13 | uVar3 | uVar2 & 0xffc8ffff | 0x30000;
  }
  DAT_cc008000._0_1_ = 0x61;
  uVar3 = (param_6 & 3) << 0x16 | (param_5 & 1) << 0x13 | uVar3 & 0xff37ffff;
  DAT_cc008000 = uVar3;
  *(uint *)(DAT_8043cb00 + param_1 * 4 + 0x130) = uVar3;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}



// ==== 80229d28  gnt4-GXSetTevAlphaOp-bl ====

void gnt4_GXSetTevAlphaOp_bl
               (int param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  iVar1 = DAT_8043cb00;
  uVar2 = *(uint *)(DAT_8043cb00 + param_1 * 4 + 0x170);
  uVar3 = (param_2 & 1) << 0x12;
  if ((int)param_2 < 2) {
    uVar3 = (param_3 & 3) << 0x10 | (param_4 & 3) << 0x14 | uVar3 | uVar2 & 0xffc8ffff;
  }
  else {
    uVar3 = (param_2 & 6) << 0x13 | uVar3 | uVar2 & 0xffc8ffff | 0x30000;
  }
  DAT_cc008000._0_1_ = 0x61;
  uVar3 = (param_6 & 3) << 0x16 | (param_5 & 1) << 0x13 | uVar3 & 0xff37ffff;
  DAT_cc008000 = uVar3;
  *(uint *)(DAT_8043cb00 + param_1 * 4 + 0x170) = uVar3;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}



// ==== 80229d90  gnt4-GXSetTevColor-bl ====

void gnt4_GXSetTevColor_bl(int param_1,byte *param_2)

{
  uint uVar1;
  
  uVar1 = (param_1 * 2 + 0xe1) * 0x1000000 | (uint)param_2[1] << 0xc | (uint)param_2[2];
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = (param_1 * 2 + 0xe0) * 0x1000000 | (uint)param_2[3] << 0xc | (uint)*param_2;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar1;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar1;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar1;
  *(undefined2 *)(DAT_8043cb00 + 2) = 0;
  return;
}



// ==== 80229e0c  gnt4-GXSetTevColorS10-bl ====

void gnt4_GXSetTevColorS10_bl(int param_1,short *param_2)

{
  uint uVar1;
  
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = (param_1 * 2 + 0xe0) * 0x1000000 |
                 ((int)param_2[3] & 0x7ffU) << 0xc | (int)*param_2 & 0x7ffU;
  DAT_cc008000._0_1_ = 0x61;
  uVar1 = (param_1 * 2 + 0xe1) * 0x1000000 |
          ((int)param_2[1] & 0x7ffU) << 0xc | (int)param_2[2] & 0x7ffU;
  DAT_cc008000 = uVar1;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar1;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar1;
  *(undefined2 *)(DAT_8043cb00 + 2) = 0;
  return;
}



// ==== 80229e88  gnt4-GXSetTevKColor-bl ====

void gnt4_GXSetTevKColor_bl(int param_1,byte *param_2)

{
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = (param_1 * 2 + 0xe0) * 0x1000000 |
                 (uint)param_2[3] << 0xc | (uint)*param_2 | 0x800000;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = (param_1 * 2 + 0xe1) * 0x1000000 |
                 (uint)param_2[1] << 0xc | (uint)param_2[2] | 0x800000;
  *(undefined2 *)(DAT_8043cb00 + 2) = 0;
  return;
}



// ==== 80229efc  gnt4-GXSetTevKColorSel-bl ====

void gnt4_GXSetTevKColorSel_bl(uint param_1,uint param_2)

{
  uint *puVar1;
  
  puVar1 = (uint *)(DAT_8043cb00 + ((int)param_1 >> 1) * 4 + 0x1b0);
  if ((param_1 & 1) == 0) {
    *puVar1 = (param_2 & 0x1f) << 4 | *puVar1 & 0xfffffe0f;
  }
  else {
    *puVar1 = (param_2 & 0x1f) << 0xe | *puVar1 & 0xfff83fff;
  }
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *puVar1;
  *(undefined2 *)(DAT_8043cb00 + 2) = 0;
  return;
}



// ==== 80229f58  gnt4-GXSetTevKAlphaSel-bl ====

void gnt4_GXSetTevKAlphaSel_bl(uint param_1,uint param_2)

{
  uint *puVar1;
  
  puVar1 = (uint *)(DAT_8043cb00 + ((int)param_1 >> 1) * 4 + 0x1b0);
  if ((param_1 & 1) == 0) {
    *puVar1 = (param_2 & 0x1f) << 9 | *puVar1 & 0xffffc1ff;
  }
  else {
    *puVar1 = (param_2 & 0x1f) << 0x13 | *puVar1 & 0xff07ffff;
  }
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *puVar1;
  *(undefined2 *)(DAT_8043cb00 + 2) = 0;
  return;
}



// ==== 80229fb4  gnt4-GXSetTevSwapMode-bl ====

void gnt4_GXSetTevSwapMode_bl(int param_1,uint param_2,uint param_3)

{
  int iVar1;
  uint *puVar2;
  
  iVar1 = DAT_8043cb00;
  puVar2 = (uint *)(DAT_8043cb00 + param_1 * 4 + 0x170);
  *puVar2 = param_2 & 3 | *puVar2 & 0xfffffffc;
  *puVar2 = (param_3 & 3) << 2 | *puVar2 & 0xfffffff3;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *puVar2;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}



// ==== 80229ffc  gnt4-GXSetTevSwapModeTable-bl ====

void gnt4_GXSetTevSwapModeTable_bl(int param_1,uint param_2,uint param_3,uint param_4,uint param_5)

{
  int iVar1;
  uint *puVar2;
  uint *puVar3;
  
  iVar1 = DAT_8043cb00;
  puVar3 = (uint *)(DAT_8043cb00 + param_1 * 8 + 0x1b0);
  *puVar3 = param_2 & 3 | *puVar3 & 0xfffffffc;
  *puVar3 = (param_3 & 3) << 2 | *puVar3 & 0xfffffff3;
  puVar2 = (uint *)(iVar1 + (param_1 * 2 + 1) * 4 + 0x1b0);
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *puVar3;
  *puVar2 = param_4 & 3 | *puVar2 & 0xfffffffc;
  *puVar2 = (param_5 & 3) << 2 | *puVar2 & 0xfffffff3;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *puVar2;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}



// ==== 8022a07c  gnt4-GXSetAlphaCompare-bl ====

void gnt4_GXSetAlphaCompare_bl(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5)

{
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = (param_3 & 3) << 0x16 |
                 (param_4 & 7) << 0x13 |
                 (param_1 & 7) << 0x10 | (param_5 & 0xff) << 8 | param_2 & 0xff | 0xf3000000;
  *(undefined2 *)(DAT_8043cb00 + 2) = 0;
  return;
}



// ==== 8022a0c0  gnt4-GXSetZTexture-bl ====

void gnt4_GXSetZTexture_bl(uint param_1,int param_2,uint param_3)

{
  uint uVar1;
  
  if (param_2 == 0x13) {
    uVar1 = 1;
  }
  else {
    if (param_2 < 0x13) {
      if (param_2 == 0x11) {
        uVar1 = 0;
        goto LAB_8022a114;
      }
    }
    else if (param_2 == 0x16) {
      uVar1 = 2;
      goto LAB_8022a114;
    }
    uVar1 = 2;
  }
LAB_8022a114:
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = param_3 & 0xffffff | 0xf4000000;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = (param_1 & 3) << 2 | uVar1 | 0xf5000000;
  *(undefined2 *)(DAT_8043cb00 + 2) = 0;
  return;
}



// ==== 8022a14c  gnt4-GXSetTevOrder-bl ====

void gnt4_GXSetTevOrder_bl(uint param_1,uint param_2,uint param_3,int param_4)

{
  int iVar1;
  uint *puVar2;
  uint uVar3;
  
  iVar1 = DAT_8043cb00;
  uVar3 = param_3 & 0xfffffeff;
  *(uint *)(DAT_8043cb00 + param_1 * 4 + 0x554) = param_3;
  puVar2 = (uint *)(iVar1 + (((int)param_1 >> 1) + (uint)((int)param_1 < 0 && (param_1 & 1) != 0)) *
                            4 + 0x100);
  if (7 < uVar3) {
    uVar3 = 0;
  }
  if ((int)param_2 < 8) {
    *(uint *)(DAT_8043cb00 + 0x598) = *(uint *)(DAT_8043cb00 + 0x598) | 1 << param_1;
  }
  else {
    param_2 = 0;
    *(uint *)(DAT_8043cb00 + 0x598) = *(uint *)(DAT_8043cb00 + 0x598) & ~(1 << param_1);
  }
  if ((param_1 & 1) == 0) {
    *puVar2 = uVar3 & 7 | *puVar2 & 0xfffffff8;
    *puVar2 = (param_2 & 7) << 3 | *puVar2 & 0xffffffc7;
    if (param_4 == 0xff) {
      uVar3 = 7;
    }
    else {
      uVar3 = *(uint *)(&DAT_803aad80 + param_4 * 4);
    }
    *puVar2 = (uVar3 & 7) << 7 | *puVar2 & 0xfffffc7f;
    iVar1 = 0;
    if ((param_3 != 0xff) && ((param_3 & 0x100) == 0)) {
      iVar1 = 1;
    }
    *puVar2 = iVar1 << 6 | *puVar2 & 0xffffffbf;
  }
  else {
    *puVar2 = (uVar3 & 7) << 0xc | *puVar2 & 0xffff8fff;
    *puVar2 = (param_2 & 7) << 0xf | *puVar2 & 0xfffc7fff;
    if (param_4 == 0xff) {
      uVar3 = 7;
    }
    else {
      uVar3 = *(uint *)(&DAT_803aad80 + param_4 * 4);
    }
    *puVar2 = (uVar3 & 7) << 0x13 | *puVar2 & 0xffc7ffff;
    iVar1 = 0;
    if ((param_3 != 0xff) && ((param_3 & 0x100) == 0)) {
      iVar1 = 1;
    }
    *puVar2 = iVar1 << 0x12 | *puVar2 & 0xfffbffff;
  }
  iVar1 = DAT_8043cb00;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *puVar2;
  *(undefined2 *)(DAT_8043cb00 + 2) = 0;
  *(uint *)(iVar1 + 0x5ac) = *(uint *)(iVar1 + 0x5ac) | 1;
  return;
}



// ==== 8022a2e8  gnt4-GXSetNumTevStages-bl ====

void gnt4_GXSetNumTevStages_bl(uint param_1)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  *(uint *)(DAT_8043cb00 + 0x204) =
       ((param_1 & 0xff) - 1) * 0x400 & 0x3c00 | *(uint *)(DAT_8043cb00 + 0x204) & 0xffffc3ff;
  *(uint *)(iVar1 + 0x5ac) = *(uint *)(iVar1 + 0x5ac) | 4;
  return;
}



// ==== 8022a310  gnt4-GXSetFog-bl ====

void gnt4_GXSetFog_bl(double param_1,double param_2,double param_3,double param_4,uint param_5,
                     uint3 *param_6)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  undefined4 local_40;
  undefined4 local_3c;
  
  uVar4 = 0;
  uVar5 = param_5 >> 3 & 1;
  uVar3 = 0;
  if (uVar5 == 0) {
    if ((param_4 == param_3) || (param_2 == param_1)) {
      dVar6 = (double)FLOAT_8043cb88;
      dVar8 = dVar6;
      fVar1 = FLOAT_8043cb90;
    }
    else {
      fVar1 = (float)(param_4 / (double)(float)(param_4 - param_3));
      dVar8 = (double)(float)(param_1 / (double)(float)(param_2 - param_1));
      dVar6 = (double)((float)(param_4 * param_3) /
                      (float)((double)(float)(param_4 - param_3) *
                             (double)(float)(param_2 - param_1)));
    }
    iVar2 = 0;
    while (dVar7 = (double)fVar1, DOUBLE_8043cb98 < dVar7) {
      iVar2 = iVar2 + 1;
      fVar1 = (float)(dVar7 * (double)FLOAT_8043cb90);
    }
    for (; ((double)FLOAT_8043cb88 < dVar7 && (dVar7 < DOUBLE_8043cba8));
        dVar7 = (double)(float)(dVar7 * (double)FLOAT_8043cba0)) {
      iVar2 = iVar2 + -1;
    }
    local_3c = (float)(dVar6 / (double)(float)((double)CONCAT44(0x43300000,
                                                                1 << iVar2 + 1U ^ 0x80000000) -
                                              DOUBLE_8043cbb8));
    uVar4 = gnt4___cvt_fp2unsigned_bl((double)(float)((double)FLOAT_8043cbb0 * dVar7));
    local_40 = (float)dVar8;
    uVar4 = uVar4 & 0xffffff | 0xef000000;
    uVar3 = iVar2 + 1U & 0x1f | 0xf0000000;
  }
  else if ((param_4 == param_3) || (param_2 == param_1)) {
    local_3c = FLOAT_8043cb88;
    local_40 = FLOAT_8043cb88;
  }
  else {
    local_40 = FLOAT_8043cb8c / (float)(param_2 - param_1);
    local_3c = local_40 * (float)(param_4 - param_3);
    local_40 = local_40 * (float)(param_1 - param_3);
  }
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = (uint)local_3c >> 0xc & 0x80000 |
                 (uint)local_3c >> 0xc & 0x7f800 | (uint)local_3c >> 0xc & 0x7ff | 0xee000000;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar4;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar3;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = (param_5 & 7) << 0x15 |
                 uVar5 << 0x14 |
                 (uint)local_40 >> 0xc & 0x80000 |
                 (uint)local_40 >> 0xc & 0x7f800 | (uint)local_40 >> 0xc & 0x7ff | 0xf1000000;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *param_6 | 0xf2000000;
  *(undefined2 *)(DAT_8043cb00 + 2) = 0;
  return;
}



// ==== 8022a534  gnt4-GXInitFogAdjTable-bl ====

void gnt4_GXInitFogAdjTable_bl(ushort *param_1,uint param_2,float *param_3)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  
  if (DOUBLE_8043cbc0 == (double)param_3[0xf]) {
    fVar1 = param_3[0xb] / (param_3[10] - FLOAT_8043cb8c);
    dVar7 = (double)(fVar1 / *param_3);
  }
  else {
    dVar7 = (double)(FLOAT_8043cb8c / *param_3);
    fVar1 = (float)((double)FLOAT_8043cbc8 * dVar7);
  }
  dVar9 = (double)(fVar1 * fVar1);
  dVar11 = (double)FLOAT_8043cb8c;
  dVar12 = (double)FLOAT_8043cb88;
  uVar3 = 0;
  dVar6 = (double)FLOAT_8043cbd8;
  dVar8 = (double)(FLOAT_8043cba0 /
                  (float)((double)CONCAT44(0x43300000,param_2 & 0xffff) - DOUBLE_8043cbe0));
  dVar10 = DOUBLE_8043cbe0;
  dVar13 = DOUBLE_8043cba8;
  dVar14 = DOUBLE_8043cbd0;
  do {
    fVar1 = (float)((double)(float)((double)(float)((double)CONCAT44(0x43300000,(uVar3 + 1) * 0x20)
                                                   - dVar10) * dVar8) * dVar7);
    dVar5 = (double)(float)(dVar11 + (double)(float)((double)(fVar1 * fVar1) / dVar9));
    if (dVar12 < dVar5) {
      dVar4 = 1.0 / SQRT(dVar5);
      dVar4 = dVar13 * dVar4 * (dVar14 - dVar5 * dVar4 * dVar4);
      dVar4 = dVar13 * dVar4 * (dVar14 - dVar5 * dVar4 * dVar4);
      dVar5 = (double)(float)(dVar5 * dVar13 * dVar4 * (dVar14 - dVar5 * dVar4 * dVar4));
    }
    iVar2 = gnt4___cvt_fp2unsigned_bl((double)(float)(dVar6 * dVar5));
    uVar3 = uVar3 + 1;
    *param_1 = (ushort)iVar2 & 0xfff;
    param_1 = param_1 + 1;
  } while (uVar3 < 10);
  return;
}



// ==== 8022a6e4  gnt4-GXSetFogRangeAdj-bl ====

void gnt4_GXSetFogRangeAdj_bl(uint param_1,uint param_2,ushort *param_3)

{
  if ((param_1 & 0xff) != 0) {
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = (param_3[1] & 0xfff) << 0xc | *param_3 & 0xfff | 0xe9000000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = (param_3[3] & 0xfff) << 0xc | param_3[2] & 0xfff | 0xea000000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = (param_3[5] & 0xfff) << 0xc | param_3[4] & 0xfff | 0xeb000000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = (param_3[7] & 0xfff) << 0xc | param_3[6] & 0xfff | 0xec000000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = (param_3[9] & 0xfff) << 0xc | param_3[8] & 0xfff | 0xed000000;
  }
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = (param_1 & 1) << 10 | (param_2 & 0xffff) + 0x156 & 0x3ff | 0xe8000000;
  *(undefined2 *)(DAT_8043cb00 + 2) = 0;
  return;
}



// ==== 8022a808  gnt4-GXSetBlendMode-bl ====

void gnt4_GXSetBlendMode_bl(uint param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  iVar1 = DAT_8043cb00;
  uVar3 = countLeadingZeros(3 - param_1);
  uVar2 = countLeadingZeros(2 - param_1);
  DAT_cc008000._0_1_ = 0x61;
  uVar2 = (param_3 & 7) << 5 |
          (param_2 & 7) << 8 |
          (param_4 & 0xf) << 0xc |
          uVar2 >> 4 & 2 |
          param_1 & 1 | (uVar3 & 0x20) << 6 | *(uint *)(DAT_8043cb00 + 0x1d0) & 0xffff001c;
  DAT_cc008000 = uVar2;
  *(uint *)(DAT_8043cb00 + 0x1d0) = uVar2;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}



// ==== 8022a85c  gnt4-GXSetColorUpdate-bl ====

void gnt4_GXSetColorUpdate_bl(uint param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = DAT_8043cb00;
  uVar2 = (param_1 & 1) << 3 | *(uint *)(DAT_8043cb00 + 0x1d0) & 0xfffffff7;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar2;
  *(uint *)(DAT_8043cb00 + 0x1d0) = uVar2;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}



// ==== 8022a888  gnt4-GXSetAlphaUpdate-bl ====

void gnt4_GXSetAlphaUpdate_bl(uint param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = DAT_8043cb00;
  uVar2 = (param_1 & 1) << 4 | *(uint *)(DAT_8043cb00 + 0x1d0) & 0xffffffef;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar2;
  *(uint *)(DAT_8043cb00 + 0x1d0) = uVar2;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}



// ==== 8022a8b4  gnt4-GXSetZMode-bl ====

void gnt4_GXSetZMode_bl(uint param_1,uint param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = DAT_8043cb00;
  DAT_cc008000._0_1_ = 0x61;
  uVar2 = (param_3 & 1) << 4 |
          (param_2 & 7) << 1 | param_1 & 1 | *(uint *)(DAT_8043cb00 + 0x1d8) & 0xffffffe0;
  DAT_cc008000 = uVar2;
  *(uint *)(DAT_8043cb00 + 0x1d8) = uVar2;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}



// ==== 8022a8e8  gnt4-GXSetZCompLoc-bl ====

void gnt4_GXSetZCompLoc_bl(uint param_1)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  *(uint *)(DAT_8043cb00 + 0x1dc) =
       (param_1 & 1) << 6 | *(uint *)(DAT_8043cb00 + 0x1dc) & 0xffffffbf;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(iVar1 + 0x1dc);
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}



// ==== 8022a91c  gnt4-GXSetPixelFmt-bl ====

void gnt4_GXSetPixelFmt_bl(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = DAT_8043cb00;
  uVar3 = *(uint *)(DAT_8043cb00 + 0x1dc);
  *(uint *)(DAT_8043cb00 + 0x1dc) = *(uint *)(&DAT_803aada8 + param_1 * 4) & 7 | uVar3 & 0xfffffff8;
  *(uint *)(iVar1 + 0x1dc) = (param_2 & 7) << 3 | *(uint *)(iVar1 + 0x1dc) & 0xffffffc7;
  iVar2 = DAT_8043cb00;
  if (uVar3 != *(uint *)(iVar1 + 0x1dc)) {
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(uint *)(iVar1 + 0x1dc);
    *(uint *)(DAT_8043cb00 + 0x204) =
         (uint)(param_1 == 2) << 9 | *(uint *)(DAT_8043cb00 + 0x204) & 0xfffffdff;
    *(uint *)(iVar2 + 0x5ac) = *(uint *)(iVar2 + 0x5ac) | 4;
  }
  iVar1 = DAT_8043cb00;
  if (*(uint *)(&DAT_803aada8 + param_1 * 4) == 4) {
    *(uint *)(DAT_8043cb00 + 0x1d4) =
         (param_1 + -4) * 0x200 & 0x600U | *(uint *)(DAT_8043cb00 + 0x1d4) & 0xfffff9ff;
    *(uint *)(iVar1 + 0x1d4) = *(uint *)(iVar1 + 0x1d4) & 0xffffff | 0x42000000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(undefined4 *)(iVar1 + 0x1d4);
  }
  *(undefined2 *)(DAT_8043cb00 + 2) = 0;
  return;
}



// ==== 8022a9f0  gnt4-GXSetDither-bl ====

void gnt4_GXSetDither_bl(uint param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = DAT_8043cb00;
  uVar2 = (param_1 & 1) << 2 | *(uint *)(DAT_8043cb00 + 0x1d0) & 0xfffffffb;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar2;
  *(uint *)(DAT_8043cb00 + 0x1d0) = uVar2;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}



// ==== 8022aa1c  gnt4-GXSetDstAlpha-bl ====

void gnt4_GXSetDstAlpha_bl(uint param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = DAT_8043cb00;
  DAT_cc008000._0_1_ = 0x61;
  uVar2 = (param_1 & 1) << 8 | param_2 & 0xff | *(uint *)(DAT_8043cb00 + 0x1d4) & 0xfffffe00;
  DAT_cc008000 = uVar2;
  *(uint *)(DAT_8043cb00 + 0x1d4) = uVar2;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}



// ==== 8022aa58  gnt4-GXSetFieldMask-bl ====

void gnt4_GXSetFieldMask_bl(uint param_1,uint param_2)

{
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = (param_1 & 1) << 1 | param_2 & 1 | 0x44000000;
  *(undefined2 *)(DAT_8043cb00 + 2) = 0;
  return;
}



// ==== 8022aa90  gnt4-GXSetFieldMode-bl ====

void gnt4_GXSetFieldMode_bl(uint param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  *(uint *)(DAT_8043cb00 + 0x7c) =
       (param_2 & 1) << 0x16 | *(uint *)(DAT_8043cb00 + 0x7c) & 0xffbfffff;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(iVar1 + 0x7c);
  gnt4___GXFlushTextureState_bl();
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = param_1 & 0xff | 0x68000000;
  gnt4___GXFlushTextureState_bl();
  return;
}



// ==== 8022ab08  zz_022ab08_ ====

void zz_022ab08_(char param_1,float *param_2,float *param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  char cVar10;
  double dVar11;
  double dVar12;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  
  if (param_1 == '\0') {
    gnt4_GXBegin_bl(0x90,3,3);
    DAT_cc008000 = *param_2;
    DAT_cc008000 = param_2[1];
    DAT_cc008000 = param_2[2];
    DAT_cc008000 = *param_2;
    DAT_cc008000 = param_2[1];
    DAT_cc008000 = param_2[2];
    DAT_cc008000 = *param_3;
    DAT_cc008000 = param_3[1];
    DAT_cc008000 = param_3[2];
    DAT_cc008000 = *param_3;
    DAT_cc008000 = param_3[1];
    DAT_cc008000 = param_3[2];
    DAT_cc008000 = *param_4;
    DAT_cc008000 = param_4[1];
    DAT_cc008000 = param_4[2];
    DAT_cc008000 = *param_4;
    DAT_cc008000 = param_4[1];
    DAT_cc008000 = param_4[2];
  }
  else {
    fVar1 = *param_2 + *param_3;
    fVar2 = *param_3 + *param_4;
    fVar3 = *param_4 + *param_2;
    fVar4 = param_2[1] + param_3[1];
    fVar5 = param_3[1] + param_4[1];
    fVar6 = param_4[1] + param_2[1];
    fVar7 = param_2[2] + param_3[2];
    fVar8 = param_3[2] + param_4[2];
    fVar9 = param_4[2] + param_2[2];
    dVar12 = (double)(fVar7 * fVar7 + fVar1 * fVar1 + fVar4 * fVar4);
    if ((double)FLOAT_8043cbe8 < dVar12) {
      dVar11 = 1.0 / SQRT(dVar12);
      dVar11 = DOUBLE_8043cbf0 * dVar11 * (DOUBLE_8043cbf8 - dVar12 * dVar11 * dVar11);
      dVar11 = DOUBLE_8043cbf0 * dVar11 * (DOUBLE_8043cbf8 - dVar12 * dVar11 * dVar11);
      dVar12 = (double)(float)(dVar12 * DOUBLE_8043cbf0 * dVar11 *
                                        (DOUBLE_8043cbf8 - dVar12 * dVar11 * dVar11));
    }
    local_1c = (float)((double)fVar1 / dVar12);
    local_18 = (float)((double)fVar4 / dVar12);
    local_14 = (float)((double)fVar7 / dVar12);
    dVar12 = (double)(fVar8 * fVar8 + fVar2 * fVar2 + fVar5 * fVar5);
    if ((double)FLOAT_8043cbe8 < dVar12) {
      dVar11 = 1.0 / SQRT(dVar12);
      dVar11 = DOUBLE_8043cbf0 * dVar11 * (DOUBLE_8043cbf8 - dVar12 * dVar11 * dVar11);
      dVar11 = DOUBLE_8043cbf0 * dVar11 * (DOUBLE_8043cbf8 - dVar12 * dVar11 * dVar11);
      dVar12 = (double)(float)(dVar12 * DOUBLE_8043cbf0 * dVar11 *
                                        (DOUBLE_8043cbf8 - dVar12 * dVar11 * dVar11));
    }
    local_28 = (float)((double)fVar2 / dVar12);
    local_24 = (float)((double)fVar5 / dVar12);
    local_20 = (float)((double)fVar8 / dVar12);
    dVar12 = (double)(fVar9 * fVar9 + fVar3 * fVar3 + fVar6 * fVar6);
    if ((double)FLOAT_8043cbe8 < dVar12) {
      dVar11 = 1.0 / SQRT(dVar12);
      dVar11 = DOUBLE_8043cbf0 * dVar11 * (DOUBLE_8043cbf8 - dVar12 * dVar11 * dVar11);
      dVar11 = DOUBLE_8043cbf0 * dVar11 * (DOUBLE_8043cbf8 - dVar12 * dVar11 * dVar11);
      dVar12 = (double)(float)(dVar12 * DOUBLE_8043cbf0 * dVar11 *
                                        (DOUBLE_8043cbf8 - dVar12 * dVar11 * dVar11));
    }
    cVar10 = param_1 + -1;
    local_34 = (float)((double)fVar3 / dVar12);
    local_30 = (float)((double)fVar6 / dVar12);
    local_2c = (float)((double)fVar9 / dVar12);
    zz_022ab08_(cVar10,param_2,&local_1c,&local_34);
    zz_022ab08_(cVar10,param_3,&local_28,&local_1c);
    zz_022ab08_(cVar10,param_4,&local_34,&local_28);
    zz_022ab08_(cVar10,&local_1c,&local_28,&local_34);
  }
  return;
}



// ==== 8022aebc  zz_022aebc_ ====

void zz_022aebc_(uint param_1)

{
  float *pfVar1;
  float fVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  float *pfVar6;
  float *pfVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  float *pfVar11;
  float *pfVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  float fVar19;
  float local_384 [100];
  float local_1f4 [101];
  undefined4 local_60;
  uint uStack_5c;
  undefined4 local_58;
  uint uStack_54;
  
  dVar18 = -(double)FLOAT_8043cc00;
  zz_022611c_(-0x7fc0a6b0);
  zz_02269dc_(3,(int *)&DAT_803f5a28);
  gnt4_GXClearVtxDesc_bl();
  gnt4_GXSetVtxDesc_bl(9,1);
  gnt4_GXSetVtxDesc_bl(10,1);
  gnt4_GXSetVtxAttrFmt_bl(3,9,1,4,0);
  gnt4_GXSetVtxAttrFmt_bl(3,10,0,4,0);
  pfVar12 = local_1f4;
  dVar14 = (double)FLOAT_8043cc04;
  pfVar11 = local_384;
  dVar15 = (double)FLOAT_8043cc08;
  uVar4 = param_1 & 0xff;
  pfVar6 = pfVar11;
  pfVar7 = pfVar12;
  dVar16 = DOUBLE_8043cc10;
  dVar17 = DOUBLE_8043cc18;
  for (uVar9 = 0; (int)uVar9 <= (int)uVar4; uVar9 = uVar9 + 1) {
    uStack_54 = uVar9 ^ 0x80000000;
    local_58 = 0x43300000;
    local_60 = 0x43300000;
    fVar19 = (float)(dVar14 * (double)(float)(dVar15 * (double)(float)((double)CONCAT44(0x43300000,
                                                                                        uStack_54) -
                                                                      dVar16))) /
             (float)((double)CONCAT44(0x43300000,uVar4) - dVar17);
    dVar13 = (double)fVar19;
    uStack_5c = uVar4;
    fVar19 = gnt4_cosf(fVar19);
    *pfVar7 = fVar19;
    fVar19 = gnt4_sinf((float)dVar13);
    *pfVar6 = fVar19;
    pfVar7 = pfVar7 + 1;
    pfVar6 = pfVar6 + 1;
  }
  uVar10 = uVar4 + 1;
  gnt4_GXBegin_bl(0x98,3,(short)uVar10 * 2);
  uVar9 = uVar10 >> 2;
  pfVar6 = pfVar12;
  pfVar7 = pfVar11;
  if (uVar9 != 0) {
    do {
      fVar19 = *pfVar6;
      DAT_cc008000 = fVar19;
      fVar2 = *pfVar7;
      DAT_cc008000 = fVar2;
      DAT_cc008000 = (float)dVar18;
      DAT_cc008000 = fVar19;
      DAT_cc008000 = fVar2;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = fVar19;
      DAT_cc008000 = fVar2;
      DAT_cc008000 = FLOAT_8043cc00;
      DAT_cc008000 = fVar19;
      DAT_cc008000 = fVar2;
      DAT_cc008000 = FLOAT_8043cbe8;
      fVar19 = pfVar6[1];
      DAT_cc008000 = fVar19;
      fVar2 = pfVar7[1];
      DAT_cc008000 = fVar2;
      DAT_cc008000 = (float)dVar18;
      DAT_cc008000 = fVar19;
      DAT_cc008000 = fVar2;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = fVar19;
      DAT_cc008000 = fVar2;
      DAT_cc008000 = FLOAT_8043cc00;
      DAT_cc008000 = fVar19;
      DAT_cc008000 = fVar2;
      DAT_cc008000 = FLOAT_8043cbe8;
      fVar19 = pfVar6[2];
      DAT_cc008000 = fVar19;
      fVar2 = pfVar7[2];
      DAT_cc008000 = fVar2;
      DAT_cc008000 = (float)dVar18;
      DAT_cc008000 = fVar19;
      DAT_cc008000 = fVar2;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = fVar19;
      DAT_cc008000 = fVar2;
      DAT_cc008000 = FLOAT_8043cc00;
      DAT_cc008000 = fVar19;
      DAT_cc008000 = fVar2;
      DAT_cc008000 = FLOAT_8043cbe8;
      fVar19 = pfVar6[3];
      pfVar6 = pfVar6 + 4;
      DAT_cc008000 = fVar19;
      fVar2 = pfVar7[3];
      DAT_cc008000 = fVar2;
      pfVar7 = pfVar7 + 4;
      DAT_cc008000 = (float)dVar18;
      DAT_cc008000 = fVar19;
      DAT_cc008000 = fVar2;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = fVar19;
      DAT_cc008000 = fVar2;
      DAT_cc008000 = FLOAT_8043cc00;
      DAT_cc008000 = fVar19;
      DAT_cc008000 = fVar2;
      DAT_cc008000 = FLOAT_8043cbe8;
      uVar9 = uVar9 - 1;
    } while (uVar9 != 0);
    uVar10 = uVar10 & 3;
    if (uVar10 == 0) goto LAB_8022b15c;
  }
  do {
    fVar19 = *pfVar6;
    DAT_cc008000 = fVar19;
    fVar2 = *pfVar7;
    DAT_cc008000 = fVar2;
    DAT_cc008000 = (float)dVar18;
    DAT_cc008000 = fVar19;
    DAT_cc008000 = fVar2;
    DAT_cc008000 = FLOAT_8043cbe8;
    DAT_cc008000 = fVar19;
    DAT_cc008000 = fVar2;
    DAT_cc008000 = FLOAT_8043cc00;
    DAT_cc008000 = fVar19;
    DAT_cc008000 = fVar2;
    DAT_cc008000 = FLOAT_8043cbe8;
    uVar10 = uVar10 - 1;
    pfVar6 = pfVar6 + 1;
    pfVar7 = pfVar7 + 1;
  } while (uVar10 != 0);
LAB_8022b15c:
  sVar3 = (short)uVar4 + 2;
  gnt4_GXBegin_bl(0xa0,3,sVar3);
  DAT_cc008000 = FLOAT_8043cbe8;
  iVar8 = 0;
  DAT_cc008000 = FLOAT_8043cbe8;
  DAT_cc008000 = FLOAT_8043cc00;
  DAT_cc008000 = FLOAT_8043cbe8;
  DAT_cc008000 = FLOAT_8043cbe8;
  DAT_cc008000 = FLOAT_8043cc00;
  if ((8 < uVar4 + 1) &&
     (uVar9 = uVar4 >> 3, pfVar6 = pfVar12, pfVar7 = pfVar11, -1 < (int)(uVar4 - 8))) {
    do {
      iVar8 = iVar8 + 8;
      DAT_cc008000 = *pfVar6;
      DAT_cc008000 = -*pfVar7;
      DAT_cc008000 = FLOAT_8043cc00;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cc00;
      DAT_cc008000 = pfVar6[1];
      DAT_cc008000 = -pfVar7[1];
      DAT_cc008000 = FLOAT_8043cc00;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cc00;
      DAT_cc008000 = pfVar6[2];
      DAT_cc008000 = -pfVar7[2];
      DAT_cc008000 = FLOAT_8043cc00;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cc00;
      DAT_cc008000 = pfVar6[3];
      DAT_cc008000 = -pfVar7[3];
      DAT_cc008000 = FLOAT_8043cc00;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cc00;
      DAT_cc008000 = pfVar6[4];
      DAT_cc008000 = -pfVar7[4];
      DAT_cc008000 = FLOAT_8043cc00;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cc00;
      DAT_cc008000 = pfVar6[5];
      DAT_cc008000 = -pfVar7[5];
      DAT_cc008000 = FLOAT_8043cc00;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cc00;
      DAT_cc008000 = pfVar6[6];
      DAT_cc008000 = -pfVar7[6];
      DAT_cc008000 = FLOAT_8043cc00;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cc00;
      pfVar1 = pfVar6 + 7;
      pfVar6 = pfVar6 + 8;
      DAT_cc008000 = *pfVar1;
      pfVar1 = pfVar7 + 7;
      pfVar7 = pfVar7 + 8;
      DAT_cc008000 = -*pfVar1;
      DAT_cc008000 = FLOAT_8043cc00;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cc00;
      uVar9 = uVar9 - 1;
    } while (uVar9 != 0);
  }
  pfVar6 = local_1f4 + iVar8;
  pfVar7 = local_384 + iVar8;
  iVar5 = (uVar4 + 1) - iVar8;
  if (iVar8 <= (int)uVar4) {
    do {
      fVar19 = *pfVar6;
      pfVar6 = pfVar6 + 1;
      DAT_cc008000 = fVar19;
      fVar19 = *pfVar7;
      pfVar7 = pfVar7 + 1;
      DAT_cc008000 = -fVar19;
      DAT_cc008000 = FLOAT_8043cc00;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cc00;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  gnt4_GXBegin_bl(0xa0,3,sVar3);
  DAT_cc008000 = FLOAT_8043cbe8;
  iVar8 = 0;
  DAT_cc008000 = FLOAT_8043cbe8;
  DAT_cc008000 = (float)dVar18;
  DAT_cc008000 = FLOAT_8043cbe8;
  DAT_cc008000 = FLOAT_8043cbe8;
  DAT_cc008000 = FLOAT_8043cc0c;
  if ((8 < uVar4 + 1) && (uVar9 = uVar4 >> 3, -1 < (int)(uVar4 - 8))) {
    do {
      iVar8 = iVar8 + 8;
      DAT_cc008000 = *pfVar12;
      DAT_cc008000 = *pfVar11;
      DAT_cc008000 = (float)dVar18;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cc0c;
      DAT_cc008000 = pfVar12[1];
      DAT_cc008000 = pfVar11[1];
      DAT_cc008000 = (float)dVar18;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cc0c;
      DAT_cc008000 = pfVar12[2];
      DAT_cc008000 = pfVar11[2];
      DAT_cc008000 = (float)dVar18;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cc0c;
      DAT_cc008000 = pfVar12[3];
      DAT_cc008000 = pfVar11[3];
      DAT_cc008000 = (float)dVar18;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cc0c;
      DAT_cc008000 = pfVar12[4];
      DAT_cc008000 = pfVar11[4];
      DAT_cc008000 = (float)dVar18;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cc0c;
      DAT_cc008000 = pfVar12[5];
      DAT_cc008000 = pfVar11[5];
      DAT_cc008000 = (float)dVar18;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cc0c;
      DAT_cc008000 = pfVar12[6];
      DAT_cc008000 = pfVar11[6];
      DAT_cc008000 = (float)dVar18;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cc0c;
      pfVar6 = pfVar12 + 7;
      pfVar12 = pfVar12 + 8;
      DAT_cc008000 = *pfVar6;
      pfVar6 = pfVar11 + 7;
      pfVar11 = pfVar11 + 8;
      DAT_cc008000 = *pfVar6;
      DAT_cc008000 = (float)dVar18;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cc0c;
      uVar9 = uVar9 - 1;
    } while (uVar9 != 0);
  }
  pfVar6 = local_1f4 + iVar8;
  pfVar7 = local_384 + iVar8;
  iVar5 = (uVar4 + 1) - iVar8;
  if (iVar8 <= (int)uVar4) {
    do {
      fVar19 = *pfVar6;
      pfVar6 = pfVar6 + 1;
      DAT_cc008000 = fVar19;
      fVar19 = *pfVar7;
      pfVar7 = pfVar7 + 1;
      DAT_cc008000 = fVar19;
      DAT_cc008000 = (float)dVar18;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cbe8;
      DAT_cc008000 = FLOAT_8043cc0c;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  zz_0225b00_((int *)&DAT_803f5950);
  gnt4_GXSetVtxAttrFmtv_bl(3,(int *)&DAT_803f5a28);
  return;
}



// ==== 8022b588  zz_022b588_ ====

void zz_022b588_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10)

{
  float in_stack_00000008;
  
  DAT_cc008000 = FLOAT_8043cc20 * (float)(param_7 + (double)(float)(param_1 + param_4));
  DAT_cc008000 = FLOAT_8043cc20 * (float)(param_8 + (double)(float)(param_2 + param_5));
  DAT_cc008000 = FLOAT_8043cc20 * (in_stack_00000008 + (float)(param_3 + param_6));
  DAT_cc008000 = (float)param_1;
  DAT_cc008000 = (float)param_2;
  DAT_cc008000 = (float)param_3;
  if (param_9 != 0) {
    DAT_cc008000 = (float)param_4;
    DAT_cc008000 = (float)param_5;
    DAT_cc008000 = (float)param_6;
    DAT_cc008000 = (float)param_7;
    DAT_cc008000 = (float)param_8;
    DAT_cc008000 = in_stack_00000008;
  }
  if (param_10 != 0) {
    DAT_cc008000._0_1_ = 1;
    DAT_cc008000._0_1_ = 1;
  }
  DAT_cc008000 = FLOAT_8043cc20 * (float)(param_7 + (double)(float)(param_1 - param_4));
  DAT_cc008000 = FLOAT_8043cc20 * (float)(param_8 + (double)(float)(param_2 - param_5));
  DAT_cc008000 = FLOAT_8043cc20 * (in_stack_00000008 + (float)(param_3 - param_6));
  DAT_cc008000 = (float)param_1;
  DAT_cc008000 = (float)param_2;
  DAT_cc008000 = (float)param_3;
  if (param_9 != 0) {
    DAT_cc008000 = (float)param_4;
    DAT_cc008000 = (float)param_5;
    DAT_cc008000 = (float)param_6;
    DAT_cc008000 = (float)param_7;
    DAT_cc008000 = (float)param_8;
    DAT_cc008000 = in_stack_00000008;
  }
  if (param_10 != 0) {
    DAT_cc008000._0_1_ = 0;
    DAT_cc008000._0_1_ = 1;
  }
  DAT_cc008000 = FLOAT_8043cc20 * (float)((double)(float)(param_1 - param_4) - param_7);
  DAT_cc008000 = FLOAT_8043cc20 * (float)((double)(float)(param_2 - param_5) - param_8);
  DAT_cc008000 = FLOAT_8043cc20 * ((float)(param_3 - param_6) - in_stack_00000008);
  DAT_cc008000 = (float)param_1;
  DAT_cc008000 = (float)param_2;
  DAT_cc008000 = (float)param_3;
  if (param_9 != 0) {
    DAT_cc008000 = (float)param_4;
    DAT_cc008000 = (float)param_5;
    DAT_cc008000 = (float)param_6;
    DAT_cc008000 = (float)param_7;
    DAT_cc008000 = (float)param_8;
    DAT_cc008000 = in_stack_00000008;
  }
  if (param_10 != 0) {
    DAT_cc008000._0_1_ = 0;
    DAT_cc008000._0_1_ = 0;
  }
  DAT_cc008000 = FLOAT_8043cc20 * (float)((double)(float)(param_1 + param_4) - param_7);
  DAT_cc008000 = FLOAT_8043cc20 * (float)((double)(float)(param_2 + param_5) - param_8);
  DAT_cc008000 = FLOAT_8043cc20 * ((float)(param_3 + param_6) - in_stack_00000008);
  DAT_cc008000 = (float)param_1;
  DAT_cc008000 = (float)param_2;
  DAT_cc008000 = (float)param_3;
  if (param_9 != 0) {
    DAT_cc008000 = (float)param_4;
    DAT_cc008000 = (float)param_5;
    DAT_cc008000 = (float)param_6;
    DAT_cc008000 = (float)param_7;
    DAT_cc008000 = (float)param_8;
    DAT_cc008000 = in_stack_00000008;
  }
  if (param_10 != 0) {
    DAT_cc008000._0_1_ = 1;
    DAT_cc008000._0_1_ = 0;
  }
  return;
}



// ==== 8022b7a0  zz_022b7a0_ ====

void zz_022b7a0_(void)

{
  double dVar1;
  uint local_10;
  uint local_c [2];
  
  zz_0225f68_(0x19,local_c);
  zz_0225f68_(0xd,&local_10);
  zz_022611c_(-0x7fc0a6b0);
  zz_02269dc_(3,(int *)&DAT_803f5a28);
  gnt4_GXClearVtxDesc_bl();
  gnt4_GXSetVtxDesc_bl(9,1);
  gnt4_GXSetVtxDesc_bl(10,1);
  gnt4_GXSetVtxAttrFmt_bl(3,9,1,4,0);
  gnt4_GXSetVtxAttrFmt_bl(3,10,0,4,0);
  if (local_c[0] != 0) {
    gnt4_GXSetVtxDesc_bl(0x19,1);
    gnt4_GXSetVtxAttrFmt_bl(3,0x19,1,4,0);
  }
  if (local_10 != 0) {
    gnt4_GXSetVtxDesc_bl(0xd,1);
    gnt4_GXSetVtxAttrFmt_bl(3,0xd,1,1,0);
  }
  gnt4_GXBegin_bl(0x80,3,0x18);
  dVar1 = (double)FLOAT_8043cbe8;
  zz_022b588_((double)FLOAT_8043cc0c,dVar1,dVar1,dVar1,dVar1,(double)FLOAT_8043cc0c,dVar1,
              (double)FLOAT_8043cc00,local_c[0],local_10);
  dVar1 = (double)FLOAT_8043cbe8;
  zz_022b588_((double)FLOAT_8043cc00,dVar1,dVar1,dVar1,(double)FLOAT_8043cc00,dVar1,dVar1,dVar1,
              local_c[0],local_10);
  dVar1 = (double)FLOAT_8043cbe8;
  zz_022b588_(dVar1,(double)FLOAT_8043cc0c,dVar1,(double)FLOAT_8043cc0c,dVar1,dVar1,dVar1,dVar1,
              local_c[0],local_10);
  dVar1 = (double)FLOAT_8043cbe8;
  zz_022b588_(dVar1,(double)FLOAT_8043cc00,dVar1,dVar1,dVar1,(double)FLOAT_8043cc00,
              (double)FLOAT_8043cc0c,dVar1,local_c[0],local_10);
  dVar1 = (double)FLOAT_8043cbe8;
  zz_022b588_(dVar1,dVar1,(double)FLOAT_8043cc0c,dVar1,(double)FLOAT_8043cc0c,dVar1,
              (double)FLOAT_8043cc00,dVar1,local_c[0],local_10);
  dVar1 = (double)FLOAT_8043cbe8;
  zz_022b588_(dVar1,dVar1,(double)FLOAT_8043cc00,(double)FLOAT_8043cc00,dVar1,dVar1,dVar1,
              (double)FLOAT_8043cc0c,local_c[0],local_10);
  zz_0225b00_((int *)&DAT_803f5950);
  gnt4_GXSetVtxAttrFmtv_bl(3,(int *)&DAT_803f5a28);
  return;
}



// ==== 8022b9f0  zz_022b9f0_ ====

void zz_022b9f0_(char param_1)

{
  int iVar1;
  uint uVar2;
  
  zz_022611c_(-0x7fc0a6b0);
  zz_02269dc_(3,(int *)&DAT_803f5a28);
  gnt4_GXClearVtxDesc_bl();
  gnt4_GXSetVtxDesc_bl(9,1);
  gnt4_GXSetVtxDesc_bl(10,1);
  gnt4_GXSetVtxAttrFmt_bl(3,9,1,4,0);
  gnt4_GXSetVtxAttrFmt_bl(3,10,0,4,0);
  uVar2 = 0x13;
  do {
    iVar1 = (uVar2 & 0xff) * 3;
    zz_022ab08_(param_1,(float *)((uint)*(byte *)(iVar1 + -0x7fc54f68) * 0xc + -0x7fc54ff8),
                (float *)((uint)*(byte *)(iVar1 + -0x7fc54f67) * 0xc + -0x7fc54ff8),
                (float *)((uint)*(byte *)(iVar1 + -0x7fc54f66) * 0xc + -0x7fc54ff8));
    uVar2 = uVar2 - 1;
  } while (-1 < (int)uVar2);
  zz_0225b00_((int *)&DAT_803f5950);
  gnt4_GXSetVtxAttrFmtv_bl(3,(int *)&DAT_803f5a28);
  return;
}



// ==== 8022bb04  gnt4-GXCallDisplayList-bl ====

void gnt4_GXCallDisplayList_bl(undefined4 param_1,undefined4 param_2)

{
  if (DAT_8043cb00[0x16b] != 0) {
    gnt4___GXSetDirtyState_bl();
  }
  if (*DAT_8043cb00 == 0) {
    gnt4___GXSendFlushPrim_bl();
  }
  DAT_cc008000._0_1_ = 0x40;
  DAT_cc008000 = param_1;
  DAT_cc008000 = param_2;
  return;
}



// ==== 8022bb74  gnt4-GXProject-bl ====

void gnt4_GXProject_bl(double param_1,double param_2,double param_3,float *param_4,float *param_5,
                      float *param_6,float *param_7,float *param_8,float *param_9)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  fVar6 = FLOAT_8043cc30;
  fVar1 = param_4[3] +
          (float)((double)param_4[2] * param_3) +
          (float)((double)*param_4 * param_1) + (float)((double)param_4[1] * param_2);
  fVar2 = param_4[7] +
          (float)((double)param_4[6] * param_3) +
          (float)((double)param_4[4] * param_1) + (float)((double)param_4[5] * param_2);
  fVar3 = param_4[0xb] +
          (float)((double)param_4[10] * param_3) +
          (float)((double)param_4[8] * param_1) + (float)((double)param_4[9] * param_2);
  if (FLOAT_8043cc28 == *param_5) {
    fVar5 = fVar1 * param_5[1] + fVar3 * param_5[2];
    fVar4 = param_5[6] + fVar3 * param_5[5];
    fVar2 = fVar2 * param_5[3] + fVar3 * param_5[4];
    fVar1 = FLOAT_8043cc2c / -fVar3;
  }
  else {
    fVar5 = param_5[2] + fVar1 * param_5[1];
    fVar2 = param_5[4] + fVar2 * param_5[3];
    fVar4 = param_5[6] + fVar3 * param_5[5];
    fVar1 = FLOAT_8043cc2c;
  }
  *param_7 = param_6[2] * FLOAT_8043cc30 + *param_6 + fVar1 * fVar5 * param_6[2] * FLOAT_8043cc30;
  *param_8 = param_6[3] * fVar6 + param_6[1] + fVar1 * -fVar2 * param_6[3] * fVar6;
  *param_9 = param_6[5] + fVar1 * fVar4 * (param_6[5] - param_6[4]);
  return;
}



// ==== 8022bce8  gnt4-GXSetProjection-bl ====

/* WARNING: Removing unreachable block (ram,0x8022bd74) */
/* WARNING: Removing unreachable block (ram,0x8022bd70) */
/* WARNING: Removing unreachable block (ram,0x8022bd6c) */
/* WARNING: Removing unreachable block (ram,0x8022bd68) */
/* WARNING: Removing unreachable block (ram,0x8022bd64) */
/* WARNING: Removing unreachable block (ram,0x8022bd60) */

void gnt4_GXSetProjection_bl(undefined4 *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  *(int *)(DAT_8043cb00 + 0x4d8) = param_2;
  *(undefined4 *)(iVar1 + 0x4dc) = *param_1;
  *(undefined4 *)(iVar1 + 0x4e4) = param_1[5];
  *(undefined4 *)(iVar1 + 0x4ec) = param_1[10];
  *(undefined4 *)(iVar1 + 0x4f0) = param_1[0xb];
  if (param_2 == 1) {
    *(undefined4 *)(iVar1 + 0x4e0) = param_1[3];
    *(undefined4 *)(iVar1 + 0x4e8) = param_1[7];
  }
  else {
    *(undefined4 *)(iVar1 + 0x4e0) = param_1[2];
    *(undefined4 *)(iVar1 + 0x4e8) = param_1[6];
  }
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = 0x61020;
  DAT_cc008000 = *(undefined4 *)(DAT_8043cb00 + 0x4dc);
  DAT_cc008004 = *(undefined4 *)(DAT_8043cb00 + 0x4e0);
  DAT_cc008000 = *(undefined4 *)(DAT_8043cb00 + 0x4e4);
  DAT_cc008004 = *(undefined4 *)(DAT_8043cb00 + 0x4e8);
  DAT_cc008000 = *(undefined4 *)(DAT_8043cb00 + 0x4ec);
  DAT_cc008004 = *(undefined4 *)(DAT_8043cb00 + 0x4f0);
  DAT_cc008000 = *(undefined4 *)(DAT_8043cb00 + 0x4d8);
  *(undefined2 *)(DAT_8043cb00 + 2) = 1;
  return;
}



// ==== 8022bd8c  gnt4-GXSetProjectionv-bl ====

/* WARNING: Removing unreachable block (ram,0x8022be00) */
/* WARNING: Removing unreachable block (ram,0x8022bdfc) */
/* WARNING: Removing unreachable block (ram,0x8022bdf8) */
/* WARNING: Removing unreachable block (ram,0x8022bdf4) */
/* WARNING: Removing unreachable block (ram,0x8022bdf0) */
/* WARNING: Removing unreachable block (ram,0x8022bdec) */
/* WARNING: Removing unreachable block (ram,0x8022bdcc) */
/* WARNING: Removing unreachable block (ram,0x8022bdc8) */
/* WARNING: Removing unreachable block (ram,0x8022bdc4) */
/* WARNING: Removing unreachable block (ram,0x8022bdc0) */
/* WARNING: Removing unreachable block (ram,0x8022bdbc) */
/* WARNING: Removing unreachable block (ram,0x8022bdb8) */

void gnt4_GXSetProjectionv_bl(float *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  
  iVar6 = DAT_8043cb00;
  *(uint *)(DAT_8043cb00 + 0x4d8) = (uint)(FLOAT_8043cc28 != *param_1);
  fVar3 = param_1[2];
  fVar1 = param_1[3];
  fVar4 = param_1[4];
  fVar2 = param_1[5];
  fVar5 = param_1[6];
  *(float *)(iVar6 + 0x4dc) = param_1[1];
  *(float *)(iVar6 + 0x4e0) = fVar3;
  *(float *)(iVar6 + 0x4e4) = fVar1;
  *(float *)(iVar6 + 0x4e8) = fVar4;
  *(float *)(iVar6 + 0x4ec) = fVar2;
  *(float *)(iVar6 + 0x4f0) = fVar5;
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = 0x61020;
  DAT_cc008000 = *(float *)(iVar6 + 0x4dc);
  DAT_cc008004 = *(undefined4 *)(iVar6 + 0x4e0);
  DAT_cc008000 = *(undefined4 *)(iVar6 + 0x4e4);
  DAT_cc008004 = *(undefined4 *)(iVar6 + 0x4e8);
  DAT_cc008000 = *(undefined4 *)(iVar6 + 0x4ec);
  DAT_cc008004 = *(undefined4 *)(iVar6 + 0x4f0);
  DAT_cc008000 = *(undefined4 *)(iVar6 + 0x4d8);
  *(undefined2 *)(iVar6 + 2) = 1;
  return;
}



// ==== 8022be18  gnt4-GXGetProjectionv-bl ====

/* WARNING: Removing unreachable block (ram,0x8022be58) */
/* WARNING: Removing unreachable block (ram,0x8022be54) */
/* WARNING: Removing unreachable block (ram,0x8022be50) */
/* WARNING: Removing unreachable block (ram,0x8022be4c) */
/* WARNING: Removing unreachable block (ram,0x8022be48) */
/* WARNING: Removing unreachable block (ram,0x8022be44) */

void gnt4_GXGetProjectionv_bl(float *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar1 = FLOAT_8043cc28;
  if (*(int *)(DAT_8043cb00 + 0x4d8) != 0) {
    fVar1 = FLOAT_8043cc2c;
  }
  *param_1 = fVar1;
  fVar3 = *(float *)(DAT_8043cb00 + 0x4e0);
  fVar1 = *(float *)(DAT_8043cb00 + 0x4e4);
  fVar4 = *(float *)(DAT_8043cb00 + 0x4e8);
  fVar2 = *(float *)(DAT_8043cb00 + 0x4ec);
  fVar5 = *(float *)(DAT_8043cb00 + 0x4f0);
  param_1[1] = *(float *)(DAT_8043cb00 + 0x4dc);
  param_1[2] = fVar3;
  param_1[3] = fVar1;
  param_1[4] = fVar4;
  param_1[5] = fVar2;
  param_1[6] = fVar5;
  return;
}



// ==== 8022be60  gnt4-GXLoadPosMtxImm-bl ====

/* WARNING: Removing unreachable block (ram,0x8022bea8) */
/* WARNING: Removing unreachable block (ram,0x8022bea4) */
/* WARNING: Removing unreachable block (ram,0x8022bea0) */
/* WARNING: Removing unreachable block (ram,0x8022be9c) */
/* WARNING: Removing unreachable block (ram,0x8022be98) */
/* WARNING: Removing unreachable block (ram,0x8022be94) */
/* WARNING: Removing unreachable block (ram,0x8022be90) */
/* WARNING: Removing unreachable block (ram,0x8022be8c) */
/* WARNING: Removing unreachable block (ram,0x8022be88) */
/* WARNING: Removing unreachable block (ram,0x8022be84) */
/* WARNING: Removing unreachable block (ram,0x8022be80) */
/* WARNING: Removing unreachable block (ram,0x8022be7c) */

void gnt4_GXLoadPosMtxImm_bl(float *param_1,int param_2)

{
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = param_2 << 2 | 0xb0000;
  DAT_cc008000 = *param_1;
  DAT_cc008004 = param_1[1];
  DAT_cc008000 = param_1[2];
  DAT_cc008004 = param_1[3];
  DAT_cc008000 = param_1[4];
  DAT_cc008004 = param_1[5];
  DAT_cc008000 = param_1[6];
  DAT_cc008004 = param_1[7];
  DAT_cc008000 = param_1[8];
  DAT_cc008004 = param_1[9];
  DAT_cc008000 = param_1[10];
  DAT_cc008004 = param_1[0xb];
  return;
}



// ==== 8022beb0  gnt4-GXLoadNrmMtxImm-bl ====

/* WARNING: Removing unreachable block (ram,0x8022bef4) */
/* WARNING: Removing unreachable block (ram,0x8022beec) */
/* WARNING: Removing unreachable block (ram,0x8022bee4) */
/* WARNING: Removing unreachable block (ram,0x8022bedc) */
/* WARNING: Removing unreachable block (ram,0x8022bed4) */
/* WARNING: Removing unreachable block (ram,0x8022becc) */

void gnt4_GXLoadNrmMtxImm_bl(float *param_1,int param_2)

{
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = param_2 * 3 + 0x400U | 0x80000;
  DAT_cc008000 = *param_1;
  DAT_cc008004 = param_1[1];
  DAT_cc008000 = param_1[2];
  DAT_cc008000 = param_1[4];
  DAT_cc008004 = param_1[5];
  DAT_cc008000 = param_1[6];
  DAT_cc008000 = param_1[8];
  DAT_cc008004 = param_1[9];
  DAT_cc008000 = param_1[10];
  return;
}



// ==== 8022bf00  gnt4-GXSetCurrentMtx-bl ====

void gnt4_GXSetCurrentMtx_bl(uint param_1)

{
  *(uint *)(DAT_8043cb00 + 0x80) = param_1 & 0x3f | *(uint *)(DAT_8043cb00 + 0x80) & 0xffffffc0;
  gnt4___GXSetMatrixIndex_bl(0);
  return;
}



// ==== 8022bf34  gnt4-GXLoadTexMtxImm-bl ====

/* WARNING: Removing unreachable block (ram,0x8022bfe0) */
/* WARNING: Removing unreachable block (ram,0x8022bfdc) */
/* WARNING: Removing unreachable block (ram,0x8022bfd8) */
/* WARNING: Removing unreachable block (ram,0x8022bfd4) */
/* WARNING: Removing unreachable block (ram,0x8022bfd0) */
/* WARNING: Removing unreachable block (ram,0x8022bfcc) */
/* WARNING: Removing unreachable block (ram,0x8022bfc8) */
/* WARNING: Removing unreachable block (ram,0x8022bfc4) */
/* WARNING: Removing unreachable block (ram,0x8022bfb8) */
/* WARNING: Removing unreachable block (ram,0x8022bfb4) */
/* WARNING: Removing unreachable block (ram,0x8022bfb0) */
/* WARNING: Removing unreachable block (ram,0x8022bfac) */
/* WARNING: Removing unreachable block (ram,0x8022bfa8) */
/* WARNING: Removing unreachable block (ram,0x8022bfa4) */
/* WARNING: Removing unreachable block (ram,0x8022bfa0) */
/* WARNING: Removing unreachable block (ram,0x8022bf9c) */
/* WARNING: Removing unreachable block (ram,0x8022bf98) */
/* WARNING: Removing unreachable block (ram,0x8022bf94) */
/* WARNING: Removing unreachable block (ram,0x8022bf90) */
/* WARNING: Removing unreachable block (ram,0x8022bf8c) */

void gnt4_GXLoadTexMtxImm_bl(float *param_1,uint param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  
  if (param_2 < 0x40) {
    uVar2 = param_2 << 2;
  }
  else {
    uVar2 = (param_2 - 0x40) * 4 + 0x500;
  }
  if (param_3 == 1) {
    iVar1 = 8;
  }
  else {
    iVar1 = 0xc;
  }
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = uVar2 | (iVar1 + -1) * 0x10000;
  if (param_3 != 0) {
    DAT_cc008000 = *param_1;
    DAT_cc008004 = param_1[1];
    DAT_cc008000 = param_1[2];
    DAT_cc008004 = param_1[3];
    DAT_cc008000 = param_1[4];
    DAT_cc008004 = param_1[5];
    DAT_cc008000 = param_1[6];
    DAT_cc008004 = param_1[7];
    return;
  }
  DAT_cc008000 = *param_1;
  DAT_cc008004 = param_1[1];
  DAT_cc008000 = param_1[2];
  DAT_cc008004 = param_1[3];
  DAT_cc008000 = param_1[4];
  DAT_cc008004 = param_1[5];
  DAT_cc008000 = param_1[6];
  DAT_cc008004 = param_1[7];
  DAT_cc008000 = param_1[8];
  DAT_cc008004 = param_1[9];
  DAT_cc008000 = param_1[10];
  DAT_cc008004 = param_1[0xb];
  return;
}



// ==== 8022bfe8  gnt4-__GXSetViewport-bl ====

void gnt4___GXSetViewport_bl(void)

{
  float fVar1;
  float fVar2;
  
  fVar1 = *(float *)(DAT_8043cb00 + 0x4fc) * FLOAT_8043cc30;
  fVar2 = *(float *)(DAT_8043cb00 + 0x508) * *(float *)(DAT_8043cb00 + 0x510);
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = 0x5101a;
  DAT_cc008000 = fVar1;
  DAT_cc008000 = -*(float *)(DAT_8043cb00 + 0x500) * FLOAT_8043cc30;
  DAT_cc008000 = fVar2 - *(float *)(DAT_8043cb00 + 0x504) * *(float *)(DAT_8043cb00 + 0x510);
  DAT_cc008000 = FLOAT_8043cc34 + *(float *)(DAT_8043cb00 + 0x4f4) + fVar1;
  DAT_cc008000 = FLOAT_8043cc34 +
                 *(float *)(DAT_8043cb00 + 0x4f8) +
                 *(float *)(DAT_8043cb00 + 0x500) * FLOAT_8043cc30;
  DAT_cc008000 = fVar2 + *(float *)(DAT_8043cb00 + 0x50c);
  return;
}



// ==== 8022c078  gnt4-GXSetViewportJitter-bl ====

void gnt4_GXSetViewportJitter_bl
               (double param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,int param_7)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  if (param_7 == 0) {
    param_2 = (double)(float)(param_2 - (double)FLOAT_8043cc30);
  }
  *(float *)(DAT_8043cb00 + 0x4f4) = (float)param_1;
  *(float *)(iVar1 + 0x4f8) = (float)param_2;
  *(float *)(iVar1 + 0x4fc) = (float)param_3;
  *(float *)(iVar1 + 0x500) = (float)param_4;
  *(float *)(iVar1 + 0x504) = (float)param_5;
  *(float *)(iVar1 + 0x508) = (float)param_6;
  gnt4___GXSetViewport_bl();
  *(undefined2 *)(DAT_8043cb00 + 2) = 1;
  return;
}



// ==== 8022c0d0  gnt4-GXSetViewport-bl ====

void gnt4_GXSetViewport_bl
               (double param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  *(float *)(DAT_8043cb00 + 0x4f4) = (float)param_1;
  *(float *)(iVar1 + 0x4f8) = (float)param_2;
  *(float *)(iVar1 + 0x4fc) = (float)param_3;
  *(float *)(iVar1 + 0x500) = (float)param_4;
  *(float *)(iVar1 + 0x504) = (float)param_5;
  *(float *)(iVar1 + 0x508) = (float)param_6;
  gnt4___GXSetViewport_bl();
  *(undefined2 *)(DAT_8043cb00 + 2) = 1;
  return;
}



// ==== 8022c118  gnt4-GXGetViewportv-bl ====

/* WARNING: Removing unreachable block (ram,0x8022c134) */
/* WARNING: Removing unreachable block (ram,0x8022c130) */
/* WARNING: Removing unreachable block (ram,0x8022c12c) */
/* WARNING: Removing unreachable block (ram,0x8022c128) */
/* WARNING: Removing unreachable block (ram,0x8022c124) */
/* WARNING: Removing unreachable block (ram,0x8022c120) */

void gnt4_GXGetViewportv_bl(float *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar3 = *(float *)(DAT_8043cb00 + 0x4f8);
  fVar1 = *(float *)(DAT_8043cb00 + 0x4fc);
  fVar4 = *(float *)(DAT_8043cb00 + 0x500);
  fVar2 = *(float *)(DAT_8043cb00 + 0x504);
  fVar5 = *(float *)(DAT_8043cb00 + 0x508);
  *param_1 = *(float *)(DAT_8043cb00 + 0x4f4);
  param_1[1] = fVar3;
  param_1[2] = fVar1;
  param_1[3] = fVar4;
  param_1[4] = fVar2;
  param_1[5] = fVar5;
  return;
}



// ==== 8022c13c  gnt4-GXSetScissor-bl ====

void gnt4_GXSetScissor_bl(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  *(uint *)(DAT_8043cb00 + 0xf8) =
       param_2 + 0x156U & 0x7ff | *(uint *)(DAT_8043cb00 + 0xf8) & 0xfffff800;
  *(uint *)(iVar1 + 0xf8) =
       (param_1 + 0x156) * 0x1000 & 0x7ff000U | *(uint *)(iVar1 + 0xf8) & 0xff800fff;
  *(uint *)(iVar1 + 0xfc) =
       param_2 + 0x156U + param_4 + -1 & 0x7ff | *(uint *)(iVar1 + 0xfc) & 0xfffff800;
  *(uint *)(iVar1 + 0xfc) =
       (param_1 + 0x156 + param_3 + -1) * 0x1000 & 0x7ff000U | *(uint *)(iVar1 + 0xfc) & 0xff800fff;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(iVar1 + 0xf8);
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(iVar1 + 0xfc);
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}



// ==== 8022c1b4  gnt4-GXSetScissorBoxOffset-bl ====

void gnt4_GXSetScissorBoxOffset_bl(int param_1,int param_2)

{
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = (param_2 + 0x156) * 0x200 & 0xffc00U | param_1 + 0x156U >> 1 & 0x3ff | 0x59000000;
  *(undefined2 *)(DAT_8043cb00 + 2) = 0;
  return;
}



// ==== 8022c1f4  gnt4-GXSetClipMode-bl ====

void gnt4_GXSetClipMode_bl(undefined4 param_1)

{
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = 0x1005;
  DAT_cc008000 = param_1;
  *(undefined2 *)(DAT_8043cb00 + 2) = 1;
  return;
}



// ==== 8022c21c  gnt4-__GXSetMatrixIndex-bl ====

void gnt4___GXSetMatrixIndex_bl(int param_1)

{
  if (param_1 < 5) {
    DAT_cc008000._0_1_ = 8;
    DAT_cc008000._0_1_ = 0x30;
    DAT_cc008000 = *(undefined4 *)(DAT_8043cb00 + 0x80);
    DAT_cc008000._0_1_ = 0x10;
    DAT_cc008000 = 0x1018;
    DAT_cc008000 = *(undefined4 *)(DAT_8043cb00 + 0x80);
  }
  else {
    DAT_cc008000._0_1_ = 8;
    DAT_cc008000._0_1_ = 0x40;
    DAT_cc008000 = *(undefined4 *)(DAT_8043cb00 + 0x84);
    DAT_cc008000._0_1_ = 0x10;
    DAT_cc008000 = 0x1019;
    DAT_cc008000 = *(undefined4 *)(DAT_8043cb00 + 0x84);
  }
  *(undefined2 *)(DAT_8043cb00 + 2) = 1;
  return;
}



// ==== 8022c2a0  gnt4-GXSetGPMetric-bl ====

void gnt4_GXSetGPMetric_bl(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_8043cb00;
  iVar2 = *(int *)(DAT_8043cb00 + 0x59c);
  if (iVar2 == 0x22) {
LAB_8022c2d8:
    DAT_cc008000._0_1_ = 0x10;
    DAT_cc008000 = 0x1006;
    DAT_cc008000 = 0;
  }
  else if (iVar2 < 0x22) {
    if (iVar2 < 0xb) {
      if (-1 < iVar2) goto LAB_8022c2d8;
    }
    else if (iVar2 < 0x1b) {
      DAT_cc008000._0_1_ = 0x61;
      DAT_cc008000 = 0x23000000;
    }
    else {
      DAT_cc008000._0_1_ = 0x61;
      DAT_cc008000 = 0x24000000;
    }
  }
  iVar2 = *(int *)(DAT_8043cb00 + 0x5a0);
  if (iVar2 != 0x15) {
    if (0x14 < iVar2) goto LAB_8022c3b0;
    if (8 < iVar2) {
      if (iVar2 < 0x11) {
        *(uint *)(DAT_8043cb00 + 0x5a4) = *(uint *)(DAT_8043cb00 + 0x5a4) & 0xffffff0f;
        DAT_cc008000._0_1_ = 8;
        DAT_cc008000._0_1_ = 0x20;
        DAT_cc008000 = *(undefined4 *)(iVar1 + 0x5a4);
      }
      else {
        *(undefined2 *)(DAT_804367e4 + 6) = 0;
      }
      goto LAB_8022c3b0;
    }
    if (iVar2 < 0) goto LAB_8022c3b0;
  }
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = 0x67000000;
LAB_8022c3b0:
  iVar1 = DAT_8043cb00;
  *(undefined4 *)(DAT_8043cb00 + 0x59c) = param_1;
  iVar2 = DAT_8043cb00;
  switch(*(undefined4 *)(iVar1 + 0x59c)) {
  case 0:
    DAT_cc008000._0_1_ = 0x10;
    DAT_cc008000 = 0x1006;
    DAT_cc008000 = 0x273;
    break;
  case 1:
    DAT_cc008000._0_1_ = 0x10;
    DAT_cc008000 = 0x1006;
    DAT_cc008000 = 0x14a;
    break;
  case 2:
    DAT_cc008000._0_1_ = 0x10;
    DAT_cc008000 = 0x1006;
    DAT_cc008000 = 0x16b;
    break;
  case 3:
    DAT_cc008000._0_1_ = 0x10;
    DAT_cc008000 = 0x1006;
    DAT_cc008000 = 0x84;
    break;
  case 4:
    DAT_cc008000._0_1_ = 0x10;
    DAT_cc008000 = 0x1006;
    DAT_cc008000 = 0xc6;
    break;
  case 5:
    DAT_cc008000._0_1_ = 0x10;
    DAT_cc008000 = 0x1006;
    DAT_cc008000 = 0x210;
    break;
  case 6:
    DAT_cc008000._0_1_ = 0x10;
    DAT_cc008000 = 0x1006;
    DAT_cc008000 = 0x252;
    break;
  case 7:
    DAT_cc008000._0_1_ = 0x10;
    DAT_cc008000 = 0x1006;
    DAT_cc008000 = 0x231;
    break;
  case 8:
    DAT_cc008000._0_1_ = 0x10;
    DAT_cc008000 = 0x1006;
    DAT_cc008000 = 0x1ad;
    break;
  case 9:
    DAT_cc008000._0_1_ = 0x10;
    DAT_cc008000 = 0x1006;
    DAT_cc008000 = 0x1ce;
    break;
  case 10:
    DAT_cc008000._0_1_ = 0x10;
    DAT_cc008000 = 0x1006;
    DAT_cc008000 = 0x153;
    break;
  case 0xb:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x2300ae7f;
    break;
  case 0xc:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x23008e7f;
    break;
  case 0xd:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x23009e7f;
    break;
  case 0xe:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x23001e7f;
    break;
  case 0xf:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x2300ac3f;
    break;
  case 0x10:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x2300ac7f;
    break;
  case 0x11:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x2300acbf;
    break;
  case 0x12:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x2300acff;
    break;
  case 0x13:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x2300ad3f;
    break;
  case 0x14:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x2300ad7f;
    break;
  case 0x15:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x2300adbf;
    break;
  case 0x16:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x2300adff;
    break;
  case 0x17:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x2300ae3f;
    break;
  case 0x18:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x2300a27f;
    break;
  case 0x19:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x2300a67f;
    break;
  case 0x1a:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x2300aa7f;
    break;
  case 0x1b:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x2402c0c6;
    break;
  case 0x1c:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x2402c16b;
    break;
  case 0x1d:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x2402c0e7;
    break;
  case 0x1e:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x2402c108;
    break;
  case 0x1f:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x2402c129;
    break;
  case 0x20:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x2402c14a;
    break;
  case 0x21:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x2402c1ad;
    break;
  case 0x22:
    DAT_cc008000._0_1_ = 0x10;
    DAT_cc008000 = 0x1006;
    DAT_cc008000 = 0x21;
  }
  *(undefined4 *)(DAT_8043cb00 + 0x5a0) = param_2;
  switch(*(undefined4 *)(iVar2 + 0x5a0)) {
  case 0:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x67000042;
    break;
  case 1:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x67000084;
    break;
  case 2:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x67000063;
    break;
  case 3:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x67000129;
    break;
  case 4:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x6700014b;
    break;
  case 5:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x6700018d;
    break;
  case 6:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x670001cf;
    break;
  case 7:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x67000211;
    break;
  case 8:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x67000252;
    break;
  case 9:
    *(uint *)(iVar2 + 0x5a4) = *(uint *)(iVar2 + 0x5a4) & 0xffffff0f | 0x20;
    DAT_cc008000._0_1_ = 8;
    DAT_cc008000._0_1_ = 0x20;
    DAT_cc008000 = *(undefined4 *)(iVar2 + 0x5a4);
    break;
  case 10:
    *(uint *)(iVar2 + 0x5a4) = *(uint *)(iVar2 + 0x5a4) & 0xffffff0f | 0x30;
    DAT_cc008000._0_1_ = 8;
    DAT_cc008000._0_1_ = 0x20;
    DAT_cc008000 = *(undefined4 *)(iVar2 + 0x5a4);
    break;
  case 0xb:
    *(uint *)(iVar2 + 0x5a4) = *(uint *)(iVar2 + 0x5a4) & 0xffffff0f | 0x40;
    DAT_cc008000._0_1_ = 8;
    DAT_cc008000._0_1_ = 0x20;
    DAT_cc008000 = *(undefined4 *)(iVar2 + 0x5a4);
    break;
  case 0xc:
    *(uint *)(iVar2 + 0x5a4) = *(uint *)(iVar2 + 0x5a4) & 0xffffff0f | 0x50;
    DAT_cc008000._0_1_ = 8;
    DAT_cc008000._0_1_ = 0x20;
    DAT_cc008000 = *(undefined4 *)(iVar2 + 0x5a4);
    break;
  case 0xd:
    *(uint *)(iVar2 + 0x5a4) = *(uint *)(iVar2 + 0x5a4) & 0xffffff0f | 0x60;
    DAT_cc008000._0_1_ = 8;
    DAT_cc008000._0_1_ = 0x20;
    DAT_cc008000 = *(undefined4 *)(iVar2 + 0x5a4);
    break;
  case 0xe:
    *(uint *)(iVar2 + 0x5a4) = *(uint *)(iVar2 + 0x5a4) & 0xffffff0f | 0x70;
    DAT_cc008000._0_1_ = 8;
    DAT_cc008000._0_1_ = 0x20;
    DAT_cc008000 = *(undefined4 *)(iVar2 + 0x5a4);
    break;
  case 0xf:
    *(uint *)(iVar2 + 0x5a4) = *(uint *)(iVar2 + 0x5a4) & 0xffffff0f | 0x90;
    DAT_cc008000._0_1_ = 8;
    DAT_cc008000._0_1_ = 0x20;
    DAT_cc008000 = *(undefined4 *)(iVar2 + 0x5a4);
    break;
  case 0x10:
    *(uint *)(iVar2 + 0x5a4) = *(uint *)(iVar2 + 0x5a4) & 0xffffff0f | 0x80;
    DAT_cc008000._0_1_ = 8;
    DAT_cc008000._0_1_ = 0x20;
    DAT_cc008000 = *(undefined4 *)(iVar2 + 0x5a4);
    break;
  case 0x11:
    *(undefined2 *)(DAT_804367e4 + 6) = 2;
    break;
  case 0x12:
    *(undefined2 *)(DAT_804367e4 + 6) = 3;
    break;
  case 0x13:
    *(undefined2 *)(DAT_804367e4 + 6) = 4;
    break;
  case 0x14:
    *(undefined2 *)(DAT_804367e4 + 6) = 5;
    break;
  case 0x15:
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = 0x67000021;
  }
  *(undefined2 *)(DAT_8043cb00 + 2) = 0;
  return;
}



// ==== 8022cae8  gnt4-GXClearGPMetric-bl ====

void gnt4_GXClearGPMetric_bl(void)

{
  *(undefined2 *)(DAT_804367e4 + 4) = 4;
  return;
}



// ==== 8022caf8  cPoseAccumulator::GetNodeMatrix( ====

int cPoseAccumulator__GetNodeMatrix_(int param_1,int param_2)

{
  return *(int *)(param_1 + 8) + param_2 * 8;
}



// ==== 8022cb08  TRKNubMainLoop ====

void TRKNubMainLoop(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                   undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                   undefined4 param_9,undefined4 param_10,undefined4 *param_11,undefined4 param_12,
                   undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  undefined *puVar4;
  char *pcVar5;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  int local_18 [2];
  int local_10;
  
  bVar2 = false;
  bVar1 = false;
  while (!bVar2) {
    iVar3 = TRKGetNextEvent((int)local_18);
    if (iVar3 == 0) {
      pcVar5 = (char *)0x0;
      if ((bVar1) && (pcVar5 = DAT_80436840, *DAT_80436840 == '\0')) {
        iVar3 = zz_022f96c_();
        if (iVar3 == 0) {
          TRKTargetContinue(0,param_10,param_11,param_12,param_13,param_14,param_15,param_16);
        }
        bVar1 = false;
      }
      else {
        bVar1 = true;
        param_1 = TRKGetInput(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,pcVar5
                              ,param_10,param_11,param_12,param_13,param_14,param_15,param_16);
        param_10 = extraout_r4_00;
      }
    }
    else {
      bVar1 = false;
      if (local_18[0] == 2) {
        puVar4 = TRKGetBuffer(local_10);
        TRKDispatchMessage(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           (int)puVar4,param_10,param_11,param_12,param_13,param_14,param_15,
                           param_16);
      }
      else if (local_18[0] < 2) {
        if ((local_18[0] != 0) && (-1 < local_18[0])) {
          bVar2 = true;
        }
      }
      else if (local_18[0] == 5) {
        TRKTargetSupportRequest
                  (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,param_10,
                   param_11,param_12,param_13,param_14,param_15,param_16);
      }
      else if (local_18[0] < 5) {
        TRKTargetInterrupt(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,local_18,
                           param_10,param_11,param_12,param_13,param_14,param_15,param_16);
      }
      param_1 = zz_022cc00_((int)local_18);
      param_10 = extraout_r4;
    }
  }
  return;
}



// ==== 8022cc00  zz_022cc00_ ====

void zz_022cc00_(int param_1)

{
  TRKReleaseBuffer(*(int *)(param_1 + 8));
  return;
}



// ==== 8022cc24  TRKConstructEvent ====

void TRKConstructEvent(undefined4 *param_1,undefined4 param_2)

{
  *param_1 = param_2;
  param_1[1] = 0;
  param_1[2] = 0xffffffff;
  return;
}



// ==== 8022cc3c  TRKPostEvent ====

undefined4 TRKPostEvent(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  zz_022f408_();
  if (DAT_803f5bdc == 2) {
    uVar2 = 0x100;
  }
  else {
    iVar1 = DAT_803f5be0 + DAT_803f5bdc >> 0x1f;
    iVar1 = ((DAT_803f5be0 + DAT_803f5bdc & 1U ^ -iVar1) + iVar1) * 0xc;
    TRK_memcpy(iVar1 + -0x7fc0a41c,param_1,0xc);
    *(uint *)(&DAT_803f5be8 + iVar1) = DAT_803f5bfc;
    DAT_803f5bfc = DAT_803f5bfc + 1;
    if (DAT_803f5bfc < 0x100) {
      DAT_803f5bfc = 0x100;
    }
    DAT_803f5bdc = DAT_803f5bdc + 1;
  }
  zz_022f400_();
  return uVar2;
}



// ==== 8022cd1c  TRKGetNextEvent ====

undefined4 TRKGetNextEvent(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  zz_022f408_();
  if (0 < DAT_803f5bdc) {
    TRK_memcpy(param_1,DAT_803f5be0 * 0xc + -0x7fc0a41c,0xc);
    DAT_803f5be0 = DAT_803f5be0 + 1;
    DAT_803f5bdc = DAT_803f5bdc + -1;
    if (DAT_803f5be0 == 2) {
      DAT_803f5be0 = 0;
    }
    uVar1 = 1;
  }
  zz_022f400_();
  return uVar1;
}



// ==== 8022cdd0  TRKInitializeEventQueue ====

undefined4 TRKInitializeEventQueue(void)

{
  zz_022f410_();
  zz_022f408_();
  DAT_803f5bdc = 0;
  DAT_803f5be0 = 0;
  DAT_803f5bfc = 0x100;
  zz_022f400_();
  return 0;
}



// ==== 8022ce28  TRKNubWelcome ====

void TRKNubWelcome(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                  undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                  undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                  undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  TRK_board_display(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    s_MetroTRK_for_GAMECUBE_v2_0_802b44c0,param_10,param_11,param_12,param_13,
                    param_14,param_15,param_16);
  return;
}



// ==== 8022ce50  zz_022ce50_ ====

undefined4 zz_022ce50_(void)

{
  zz_022d840_();
  return 0;
}



// ==== 8022ce74  TRKInitializeNub ====

/* WARNING: Removing unreachable block (ram,0x8022ced0) */
/* WARNING: Removing unreachable block (ram,0x8022cee4) */
/* WARNING: Removing unreachable block (ram,0x8022cedc) */

int TRKInitializeNub(void)

{
  int iVar1;
  int iVar2;
  
  DAT_803f5c00 = 1;
  zz_02327c8_();
  zz_022daf8_();
  iVar1 = TRKInitializeEventQueue();
  if (iVar1 == 0) {
    iVar1 = TRKInitializeMessageBuffers();
  }
  if (iVar1 == 0) {
    iVar1 = zz_022dcf4_();
  }
  InitializeProgramEndTrap();
  if (iVar1 == 0) {
    iVar1 = TRKInitializeSerialHandler();
  }
  if (iVar1 == 0) {
    iVar1 = TRKInitializeTarget();
  }
  if (iVar1 == 0) {
    iVar2 = TRKInitializeIntDrivenUART();
    zz_022f934_(DAT_80436840);
    if (iVar2 != 0) {
      iVar1 = iVar2;
    }
  }
  return iVar1;
}



// ==== 8022cfc0  TRKMessageSend ====

undefined4 TRKMessageSend(void)

{
  zz_0231858_();
  zz_02327c8_();
  return 0;
}



// ==== 8022d004  TRKReadBuffer_ui32 ====

void TRKReadBuffer_ui32(int param_1,undefined1 *param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined1 *puVar4;
  int iVar5;
  undefined1 auStack_28 [8];
  
  iVar2 = 0;
  for (iVar5 = 0; (iVar2 == 0 && (iVar5 < param_3)); iVar5 = iVar5 + 1) {
    puVar4 = param_2;
    if (DAT_803f5c00 == 0) {
      puVar4 = auStack_28;
    }
    iVar2 = 0;
    uVar1 = *(int *)(param_1 + 8) - *(int *)(param_1 + 0xc);
    uVar3 = 4;
    if (uVar1 < 4) {
      iVar2 = 0x302;
      uVar3 = uVar1;
    }
    TRK_memcpy((int)puVar4,param_1 + *(int *)(param_1 + 0xc) + 0x10,uVar3);
    *(uint *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + uVar3;
    if ((DAT_803f5c00 == 0) && (iVar2 == 0)) {
      *param_2 = puVar4[3];
      param_2[1] = puVar4[2];
      param_2[2] = puVar4[1];
      param_2[3] = *puVar4;
    }
    param_2 = param_2 + 4;
  }
  return;
}



// ==== 8022d0f4  TRKReadBuffer_ui8 ====

void TRKReadBuffer_ui8(int param_1,int param_2,int param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  iVar2 = 0;
  for (iVar4 = 0; (iVar2 == 0 && (iVar4 < param_3)); iVar4 = iVar4 + 1) {
    iVar3 = *(int *)(param_1 + 0xc);
    iVar2 = 0;
    bVar1 = *(int *)(param_1 + 8) == iVar3;
    if (bVar1) {
      iVar2 = 0x302;
    }
    uVar5 = (uint)!bVar1;
    TRK_memcpy(param_2 + iVar4,param_1 + iVar3 + 0x10,uVar5);
    *(uint *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + uVar5;
  }
  return;
}



// ==== 8022d18c  TRKReadBuffer1_ui64 ====

int TRKReadBuffer1_ui64(int param_1,undefined1 *param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 auStack_28 [20];
  
  puVar4 = param_2;
  if (DAT_803f5c00 == 0) {
    puVar4 = auStack_28;
  }
  iVar3 = 0;
  uVar1 = *(int *)(param_1 + 8) - *(int *)(param_1 + 0xc);
  uVar2 = 8;
  if (uVar1 < 8) {
    iVar3 = 0x302;
    uVar2 = uVar1;
  }
  TRK_memcpy((int)puVar4,param_1 + *(int *)(param_1 + 0xc) + 0x10,uVar2);
  *(uint *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + uVar2;
  if ((DAT_803f5c00 == 0) && (iVar3 == 0)) {
    *param_2 = puVar4[7];
    param_2[1] = puVar4[6];
    param_2[2] = puVar4[5];
    param_2[3] = puVar4[4];
    param_2[4] = puVar4[3];
    param_2[5] = puVar4[2];
    param_2[6] = puVar4[1];
    param_2[7] = *puVar4;
  }
  return iVar3;
}



// ==== 8022d274  TRKAppendBuffer_ui32 ====

void TRKAppendBuffer_ui32(int param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined4 local_28;
  undefined1 local_24;
  undefined1 local_23;
  undefined1 local_22;
  undefined1 local_21;
  
  iVar1 = 0;
  for (iVar6 = 0; (iVar1 == 0 && (iVar6 < param_3)); iVar6 = iVar6 + 1) {
    uVar2 = *param_2;
    local_28 = uVar2;
    uVar2 = local_28;
    if (DAT_803f5c00 == 0) {
      local_28._3_1_ = (undefined1)uVar2;
      puVar3 = (undefined4 *)&local_24;
      local_28._2_1_ = (undefined1)((uint)uVar2 >> 8);
      local_28._1_1_ = (undefined1)((uint)uVar2 >> 0x10);
      local_28._0_1_ = (undefined1)((uint)uVar2 >> 0x18);
      local_24 = (undefined1)local_28;
      local_23 = local_28._2_1_;
      local_22 = local_28._1_1_;
      local_21 = local_28._0_1_;
    }
    else {
      puVar3 = &local_28;
    }
    iVar4 = *(int *)(param_1 + 0xc);
    iVar1 = 0;
    uVar5 = 4;
    if (0x880U - iVar4 < 4) {
      iVar1 = 0x301;
      uVar5 = 0x880U - iVar4;
    }
    if (uVar5 == 1) {
      *(undefined1 *)(param_1 + iVar4 + 0x10) = *(undefined1 *)puVar3;
    }
    else {
      local_28 = uVar2;
      TRK_memcpy(param_1 + iVar4 + 0x10,(int)puVar3,uVar5);
    }
    param_2 = param_2 + 1;
    *(uint *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + uVar5;
    *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_1 + 0xc);
  }
  return;
}



// ==== 8022d370  TRKAppendBuffer_ui8 ====

int TRKAppendBuffer_ui8(int param_1,undefined1 *param_2,int param_3)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  iVar2 = 0;
  for (iVar4 = 0; (iVar2 == 0 && (iVar4 < param_3)); iVar4 = iVar4 + 1) {
    uVar3 = *(uint *)(param_1 + 0xc);
    uVar1 = *param_2;
    if (uVar3 < 0x880) {
      *(uint *)(param_1 + 0xc) = uVar3 + 1;
      iVar2 = 0;
      *(undefined1 *)(param_1 + uVar3 + 0x10) = uVar1;
      *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
    }
    else {
      iVar2 = 0x301;
    }
    param_2 = param_2 + 1;
  }
  return iVar2;
}



// ==== 8022d3d8  TRKAppendBuffer1_ui64 ====

undefined4
TRKAppendBuffer1_ui64(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined4 local_28;
  undefined4 local_24;
  undefined1 local_20;
  undefined1 local_1f;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  
  local_28 = param_3;
  uVar1 = local_28;
  local_24 = param_4;
  uVar2 = local_24;
  if (DAT_803f5c00 == 0) {
    local_24._3_1_ = (undefined1)param_4;
    puVar4 = (undefined4 *)&local_20;
    local_24._2_1_ = (undefined1)((uint)param_4 >> 8);
    local_24._1_1_ = (undefined1)((uint)param_4 >> 0x10);
    local_24._0_1_ = (undefined1)((uint)param_4 >> 0x18);
    local_28._3_1_ = (undefined1)param_3;
    local_28._2_1_ = (undefined1)((uint)param_3 >> 8);
    local_28._1_1_ = (undefined1)((uint)param_3 >> 0x10);
    local_28._0_1_ = (undefined1)((uint)param_3 >> 0x18);
    local_20 = (undefined1)local_24;
    local_1f = local_24._2_1_;
    local_1e = local_24._1_1_;
    local_1d = local_24._0_1_;
    local_1c = (undefined1)local_28;
    local_1b = local_28._2_1_;
    local_1a = local_28._1_1_;
    local_19 = local_28._0_1_;
  }
  else {
    puVar4 = &local_28;
  }
  iVar3 = *(int *)(param_1 + 0xc);
  uVar6 = 0;
  uVar5 = 8;
  if (0x880U - iVar3 < 8) {
    uVar6 = 0x301;
    uVar5 = 0x880U - iVar3;
  }
  if (uVar5 == 1) {
    *(undefined1 *)(param_1 + iVar3 + 0x10) = *(undefined1 *)puVar4;
  }
  else {
    local_28 = uVar1;
    local_24 = uVar2;
    TRK_memcpy(param_1 + iVar3 + 0x10,(int)puVar4,uVar5);
  }
  *(uint *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + uVar5;
  *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_1 + 0xc);
  return uVar6;
}



// ==== 8022d4d4  TRKReadBuffer ====

undefined4 TRKReadBuffer(int param_1,int param_2,uint param_3)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  if (param_3 == 0) {
    uVar2 = 0;
  }
  else {
    uVar1 = *(int *)(param_1 + 8) - *(int *)(param_1 + 0xc);
    if (uVar1 < param_3) {
      uVar2 = 0x302;
      param_3 = uVar1;
    }
    TRK_memcpy(param_2,param_1 + *(int *)(param_1 + 0xc) + 0x10,param_3);
    *(uint *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + param_3;
  }
  return uVar2;
}



// ==== 8022d560  TRKAppendBuffer ====

undefined4 TRKAppendBuffer(int param_1,undefined1 *param_2,uint param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  if (param_3 == 0) {
    uVar2 = 0;
  }
  else {
    iVar1 = *(int *)(param_1 + 0xc);
    if (0x880U - iVar1 < param_3) {
      uVar2 = 0x301;
      param_3 = 0x880U - iVar1;
    }
    if (param_3 == 1) {
      *(undefined1 *)(param_1 + iVar1 + 0x10) = *param_2;
    }
    else {
      TRK_memcpy(param_1 + iVar1 + 0x10,(int)param_2,param_3);
    }
    *(uint *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + param_3;
    *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_1 + 0xc);
  }
  return uVar2;
}



// ==== 8022d604  TRKSetBufferPosition ====

undefined4 TRKSetBufferPosition(int param_1,uint param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_2 < 0x881) {
    *(uint *)(param_1 + 0xc) = param_2;
    if (*(uint *)(param_1 + 8) < param_2) {
      *(uint *)(param_1 + 8) = param_2;
    }
  }
  else {
    uVar1 = 0x301;
  }
  return uVar1;
}



// ==== 8022d634  TRKResetBuffer ====

void TRKResetBuffer(int param_1,int param_2)

{
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  if (param_2 == 0) {
    TRK_memset(param_1 + 0x10,0,0x880);
  }
  return;
}



// ==== 8022d674  TRKReleaseBuffer ====

void TRKReleaseBuffer(int param_1)

{
  if (((param_1 != -1) && (-1 < param_1)) && (param_1 < 3)) {
    zz_022f408_();
    (&DAT_803f5c0c)[param_1 * 0x224] = 0;
    zz_022f400_();
  }
  return;
}



// ==== 8022d6d8  TRKGetBuffer ====

undefined * TRKGetBuffer(int param_1)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)0x0;
  if ((-1 < param_1) && (param_1 < 3)) {
    puVar1 = &DAT_803f5c08 + param_1 * 0x890;
  }
  return puVar1;
}



// ==== 8022d704  TRKGetFreeBuffer ====

int TRKGetFreeBuffer(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                    undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                    int *param_9,undefined4 *param_10,undefined4 param_11,undefined4 param_12,
                    undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  
  iVar3 = 0x300;
  *param_10 = 0;
  puVar1 = param_10;
  for (iVar2 = 0; iVar2 < 3; iVar2 = iVar2 + 1) {
    puVar4 = (undefined4 *)0x0;
    if ((-1 < iVar2) && (iVar2 < 3)) {
      puVar1 = (undefined4 *)(iVar2 * 0x890);
      puVar4 = puVar1 + -0x1ff028fe;
    }
    zz_022f408_();
    if (puVar4[1] == 0) {
      puVar4[2] = 0;
      iVar3 = 0;
      puVar4[3] = 0;
      puVar4[1] = 1;
      *param_10 = puVar4;
      *param_9 = iVar2;
      iVar2 = 3;
    }
    zz_022f400_();
  }
  if (iVar3 == 0x300) {
    usr_puts_serial(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    s_ERROR___No_buffer_available_802b4518,puVar1,param_11,param_12,param_13,
                    param_14,param_15,param_16);
  }
  return iVar3;
}



// ==== 8022d7cc  TRKInitializeMessageBuffers ====

undefined4 TRKInitializeMessageBuffers(void)

{
  int iVar1;
  undefined *puVar2;
  
  puVar2 = &DAT_803f5c08;
  iVar1 = 0;
  do {
    zz_022f410_();
    zz_022f408_();
    *(undefined4 *)(puVar2 + 4) = 0;
    zz_022f400_();
    iVar1 = iVar1 + 1;
    puVar2 = puVar2 + 0x890;
  } while (iVar1 < 3);
  return 0;
}



// ==== 8022d840  zz_022d840_ ====

undefined4 zz_022d840_(void)

{
  return 0;
}



// ==== 8022d848  TRKInitializeSerialHandler ====

undefined4 TRKInitializeSerialHandler(void)

{
  DAT_803f75b8 = 0xffffffff;
  DAT_803f75c0 = 0;
  DAT_803f75c4 = 0;
  zz_02327c8_();
  zz_02327c8_();
  zz_02327c8_();
  zz_02327c8_();
  zz_02327c8_();
  zz_02327c8_();
  return 0;
}



// ==== 8022d90c  TRKProcessInput ====

void TRKProcessInput(undefined4 param_1)

{
  undefined4 auStack_18 [2];
  undefined4 local_10;
  
  TRKConstructEvent(auStack_18,2);
  DAT_803f75b8 = 0xffffffff;
  local_10 = param_1;
  TRKPostEvent((int)auStack_18);
  return;
}



// ==== 8022d95c  TRKGetInput ====

void TRKGetInput(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 auStack_18 [2];
  int local_10;
  
  local_10 = TRKTestForPacket(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              param_9,param_10,param_11,param_12,param_13,param_14,param_15,param_16
                             );
  if (local_10 != -1) {
    TRKGetBuffer(local_10);
    TRKConstructEvent(auStack_18,2);
    DAT_803f75b8 = 0xffffffff;
    TRKPostEvent((int)auStack_18);
  }
  return;
}



// ==== 8022d9bc  TRKTestForPacket ====

int TRKTestForPacket(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                    undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                    undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                    undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  undefined8 extraout_f1;
  int local_8d8;
  int local_8d4;
  int local_8d0 [16];
  undefined1 auStack_890 [2184];
  
  iVar1 = zz_02318d0_();
  if (iVar1 < 1) {
    iVar1 = -1;
  }
  else {
    iVar1 = TRKGetFreeBuffer(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &local_8d4,&local_8d8,param_11,param_12,param_13,param_14,param_15,
                             param_16);
    zz_02327c8_();
    TRKSetBufferPosition(local_8d8,0);
    iVar2 = TRKWriteUARTN();
    if (iVar2 == 0) {
      TRKAppendBuffer_ui8(local_8d8,(undefined1 *)local_8d0,0x40);
      iVar1 = local_8d4;
      if (0 < local_8d0[0] + -0x40) {
        zz_02327c8_();
        iVar2 = TRKWriteUARTN();
        if (iVar2 == 0) {
          TRKAppendBuffer_ui8(local_8d8,auStack_890,local_8d0[0]);
        }
        else {
          zz_02327c8_();
          TRKReleaseBuffer(local_8d4);
          iVar1 = -1;
        }
      }
    }
    else {
      zz_02327c8_();
      TRKReleaseBuffer(iVar1);
      iVar1 = -1;
    }
    zz_02327c8_();
  }
  return iVar1;
}



// ==== 8022daf8  zz_022daf8_ ====

void zz_022daf8_(void)

{
  return;
}



// ==== 8022dafc  usr_puts_serial ====

void usr_puts_serial(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                    undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                    char *param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                    undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 extraout_r4;
  undefined8 uVar3;
  char local_18 [12];
  
  while( true ) {
    cVar1 = *param_9;
    param_9 = param_9 + 1;
    if (cVar1 == '\0') break;
    uVar2 = zz_022ec14_();
    local_18[1] = 0;
    local_18[0] = cVar1;
    uVar3 = zz_022ec08_(0);
    gnt4_OSReport_bl(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,local_18,
                     extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
    zz_022ec08_(uVar2);
  }
  return;
}



// ==== 8022db84  TRKDispatchMessage ====

undefined4
TRKDispatchMessage(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                  undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                  int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                  undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  uint uVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  
  uVar2 = 0x500;
  TRKSetBufferPosition(param_9,0);
  uVar1 = (uint)*(byte *)(param_9 + 0x14);
  uVar3 = zz_02327c8_();
  switch(*(undefined1 *)(param_9 + 0x14)) {
  case 1:
    uVar2 = TRKDoConnect();
    break;
  case 2:
    uVar2 = TRKDoDisconnect();
    break;
  case 3:
    uVar2 = zz_022ead4_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    break;
  case 4:
    uVar2 = zz_022ea74_();
    break;
  case 5:
    uVar2 = zz_022ea6c_();
    break;
  case 7:
    uVar2 = TRKDoOverride();
    break;
  case 0x10:
    uVar2 = zz_022e880_(param_9);
    break;
  case 0x11:
    uVar2 = zz_022e68c_(param_9);
    break;
  case 0x12:
    uVar2 = TRKDoReadRegisters(param_9);
    break;
  case 0x13:
    uVar2 = TRKDoWriteRegisters(param_9);
    break;
  case 0x17:
    uVar2 = TRKDoSetOption(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                           extraout_r4,uVar1,param_12,param_13,param_14,param_15,param_16);
    break;
  case 0x18:
    uVar2 = TRKDoContinue();
    break;
  case 0x19:
    uVar2 = TRKDoStep(param_9);
    break;
  case 0x1a:
    uVar2 = TRKDoStop();
  }
  zz_02327c8_();
  return uVar2;
}



// ==== 8022dcf4  zz_022dcf4_ ====

undefined4 zz_022dcf4_(void)

{
  return 0;
}



// ==== 8022dcfc  TRKDoSetOption ====

undefined4
TRKDoSetOption(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
              undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
              int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
              undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  undefined4 extraout_r4;
  undefined8 uVar2;
  undefined4 local_48;
  undefined1 local_44;
  undefined1 local_40;
  
  cVar1 = *(char *)(param_9 + 0x1c);
  if (*(char *)(param_9 + 0x18) == '\x01') {
    uVar2 = usr_puts_serial(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            s_MetroTRK_Option___SerialIO___802b4708,0x802b0000,param_11,param_12,
                            param_13,param_14,param_15,param_16);
    if (cVar1 == '\0') {
      usr_puts_serial(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      s_Disable_802b4730,extraout_r4,param_11,param_12,param_13,param_14,param_15,
                      param_16);
    }
    else {
      usr_puts_serial(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      s_Enable_802b4728,extraout_r4,param_11,param_12,param_13,param_14,param_15,
                      param_16);
    }
    SetUseSerialIO(cVar1);
  }
  gnt4_memset(&local_48,0,0x40);
  local_44 = 0x80;
  local_48 = 0x40;
  local_40 = 0;
  zz_0231858_();
  return 0;
}



// ==== 8022dda4  TRKDoStop ====

undefined4 TRKDoStop(void)

{
  int iVar1;
  undefined1 uVar2;
  undefined4 local_48;
  undefined1 local_44;
  undefined1 local_40;
  
  iVar1 = TRKTargetStop();
  if (iVar1 == 0x704) {
    uVar2 = 0x21;
    goto LAB_8022de04;
  }
  if (iVar1 < 0x704) {
    if (iVar1 == 0) {
      uVar2 = 0;
      goto LAB_8022de04;
    }
  }
  else {
    if (iVar1 == 0x706) {
      uVar2 = 0x20;
      goto LAB_8022de04;
    }
    if (iVar1 < 0x706) {
      uVar2 = 0x22;
      goto LAB_8022de04;
    }
  }
  uVar2 = 1;
LAB_8022de04:
  gnt4_memset(&local_48,0,0x40);
  local_44 = 0x80;
  local_48 = 0x40;
  local_40 = uVar2;
  zz_0231858_();
  return 0;
}



// ==== 8022de4c  TRKDoStep ====

/* WARNING: Removing unreachable block (ram,0x8022e018) */
/* WARNING: Removing unreachable block (ram,0x8022de94) */

undefined4 TRKDoStep(int param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint unaff_r30;
  uint uVar6;
  undefined4 local_158;
  undefined1 local_154;
  undefined1 local_150;
  undefined4 local_118;
  undefined1 local_114;
  undefined1 local_110;
  undefined4 local_d8;
  undefined1 local_d4;
  undefined1 local_d0;
  undefined4 local_98;
  undefined1 local_94;
  undefined1 local_90;
  undefined4 local_58;
  undefined1 local_54;
  undefined1 local_50;
  
  TRKSetBufferPosition(param_1,0);
  uVar6 = (uint)*(byte *)(param_1 + 0x18);
  uVar5 = *(uint *)(param_1 + 0x20);
  uVar4 = *(uint *)(param_1 + 0x24);
  if (uVar6 == 0x10) {
LAB_8022dea4:
    unaff_r30 = (uint)*(byte *)(param_1 + 0x1c);
    if (unaff_r30 == 0) {
      gnt4_memset(&local_58,0,0x40);
      local_54 = 0x80;
      local_58 = 0x40;
      local_50 = 0x11;
      zz_0231858_();
      return 0;
    }
  }
  else {
    if (uVar6 < 0x10) {
      if (uVar6 != 1) {
        if (uVar6 != 0) goto LAB_8022df3c;
        goto LAB_8022dea4;
      }
    }
    else if (0x11 < uVar6) {
LAB_8022df3c:
      gnt4_memset(&local_d8,0,0x40);
      local_d4 = 0x80;
      local_d8 = 0x40;
      local_d0 = 0x12;
      zz_0231858_();
      return 0;
    }
    uVar1 = zz_022fb7c_();
    if ((uVar1 < uVar5) || (uVar4 < uVar1)) {
      gnt4_memset(&local_98,0,0x40);
      local_94 = 0x80;
      local_98 = 0x40;
      local_90 = 0x11;
      zz_0231858_();
      return 0;
    }
  }
  iVar2 = zz_022f96c_();
  if (iVar2 == 0) {
    gnt4_memset(&local_118,0,0x40);
    local_114 = 0x80;
    local_118 = 0x40;
    local_110 = 0x16;
    zz_0231858_();
    return 0;
  }
  gnt4_memset(&local_158,0,0x40);
  local_154 = 0x80;
  local_158 = 0x40;
  local_150 = 0;
  zz_0231858_();
  if (uVar6 == 0x10) {
LAB_8022e028:
    uVar4 = countLeadingZeros(0x10 - uVar6);
    uVar3 = TRKTargetSingleStep(unaff_r30,uVar4 >> 5);
  }
  else {
    if (uVar6 < 0x10) {
      if (uVar6 != 1) {
        if (uVar6 != 0) {
          return 0;
        }
        goto LAB_8022e028;
      }
    }
    else if (0x11 < uVar6) {
      return 0;
    }
    uVar6 = countLeadingZeros(0x11 - uVar6);
    uVar3 = TRKTargetStepOutOfRange(uVar5,uVar4,uVar6 >> 5);
  }
  return uVar3;
}



// ==== 8022e06c  TRKDoContinue ====

undefined4 TRKDoContinue(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined4 local_88;
  undefined1 local_84;
  undefined1 local_80;
  undefined4 local_48;
  undefined1 local_44;
  undefined1 local_40;
  
  zz_02327c8_();
  iVar1 = zz_022f96c_();
  if (iVar1 == 0) {
    gnt4_memset(&local_48,0,0x40);
    local_44 = 0x80;
    local_48 = 0x40;
    local_40 = 0x16;
    zz_0231858_();
    uVar2 = 0;
  }
  else {
    gnt4_memset(&local_88,0,0x40);
    uVar3 = 0x40;
    local_84 = 0x80;
    uVar2 = 0x40;
    local_88 = 0x40;
    local_80 = 0;
    iVar1 = zz_0231858_();
    uVar2 = TRKTargetContinue(iVar1,uVar2,uVar3,in_r6,in_r7,in_r8,in_r9,in_r10);
  }
  return uVar2;
}



