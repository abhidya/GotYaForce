// ==== 801043ac  zz_01043ac_ ====

bool zz_01043ac_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x13] = param_2;
    puVar1[0x11] = 0;
    puVar1[0x10] = 0x4f;
    *(code **)(puVar1 + 0xc) = zz_01044c4_;
    *(code **)(puVar1 + 0x10c) = zz_0104978_;
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
    zz_00f036c_(param_1,7);
  }
  return puVar1 != (undefined1 *)0x0;
}



// ==== 801044c4  zz_01044c4_ ====

void zz_01044c4_(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_zz_010455c__8032170c)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8010455c  zz_010455c_ ====

void zz_010455c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  int iVar6;
  undefined *puVar7;
  int iVar8;
  undefined8 uVar9;
  
  puVar7 = &DAT_803216f0;
  puVar5 = &DAT_803216c0;
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar8 = *(int *)(param_9 + 0x90);
  iVar6 = (int)*(char *)(param_9 + 0x13);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  iVar3 = (uint)*(byte *)(param_9 + 0x11) * 0x1c;
  *(undefined1 *)(param_9 + 0x98) = 5;
  iVar2 = iVar6 * 0x18;
  *(code **)(param_9 + 0x100) = zz_0048288_;
  iVar1 = iVar2;
  iVar4 = iVar3;
  zz_0089100_(param_9,0,1);
  *(undefined4 *)(param_9 + 0x9c) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_803216c2 + iVar2) * 0x30 + 0x8d8);
  *(undefined4 *)(param_9 + 0xa0) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_803216c2 + iVar2) * 0x30 + 0x8e8);
  *(undefined4 *)(param_9 + 0xa4) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_803216c2 + iVar2) * 0x30 + 0x8f8);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar8 + *(short *)(&DAT_803216c2 + iVar2) * 0x30 + 0x8d4),
             (float *)(iVar2 + -0x7fcde93c),(float *)(param_9 + 0x20));
  *(undefined4 *)(param_9 + 0x38) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_803216c2 + iVar2) * 0x30 + 0x8dc);
  *(undefined4 *)(param_9 + 0x3c) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_803216c2 + iVar2) * 0x30 + 0x8ec);
  *(undefined4 *)(param_9 + 0x40) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_803216c2 + iVar2) * 0x30 + 0x8fc);
  uVar9 = gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80321700 + iVar3),(float *)(param_9 + 0x38),
                              (float *)(param_9 + 0x38));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_80321700 + iVar3);
  *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_803216f2 + iVar3);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_803216f4 + iVar3);
  *(undefined2 *)(param_9 + 0x1c4) = *(undefined2 *)(&DAT_803216f6 + iVar3);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined4 *)(param_9 + 0x144) = *(undefined4 *)(&DAT_80321704 + iVar3);
  if ((*(byte *)(param_9 + 0xd0) & 4) == 0) {
    *(undefined4 *)(param_9 + 200) = 0;
  }
  iVar8 = zz_0006f98_(iVar8);
  zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar8 + 0x600),
              *(int *)(param_9 + 0xe0),(int)*(short *)(&DAT_803216c0 + iVar2),iVar1,iVar4,puVar5,
              iVar6,puVar7);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  iVar1 = zz_008ac80_(param_9,(int)*(short *)(&DAT_803216f0 + iVar3));
  if (iVar1 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    *(undefined1 *)(param_9 + 0xa8) = 1;
    zz_00c74ec_(param_9,0x50);
  }
  return;
}



// ==== 80104758  zz_0104758_ ====

void zz_0104758_(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (uint)*(byte *)(param_1 + 0x11) * 0x1c;
  if (*(char *)(param_1 + 0x1d9) == '\0') {
    iVar2 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar2 == 0) {
      if (*(short *)(param_1 + 0x1c6) < 1) {
        zz_0104910_(param_1);
        FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
      }
      else {
        *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
        *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
        *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
        if (*(short *)(param_1 + 0x1c) < 1) {
          zz_0104910_(param_1);
          FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
        }
        else {
          if (*(float *)(param_1 + 0x44) < *(float *)(param_1 + 0x144)) {
            *(float *)(param_1 + 0x44) =
                 *(float *)(param_1 + 0x44) + *(float *)(&DAT_80321708 + iVar1);
          }
          else {
            *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x144);
          }
          gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
          gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                              (float *)(param_1 + 0x38));
          FUN_80083874((double)*(float *)(&DAT_803216fc + iVar1),param_1);
          FUN_80083ad4((double)*(float *)(&DAT_803216f8 + iVar1),param_1,
                       (char)*(undefined2 *)(&DAT_803216f4 + iVar1));
          *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
          zz_00833ec_(param_1);
          zz_0083610_(param_1,(float *)(param_1 + 0x144));
          iVar1 = zz_0083714_(param_1);
          if (iVar1 == 0) {
            iVar1 = zz_0084170_(param_1);
            if (iVar1 != 0) {
              zz_0104910_(param_1);
              zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x20),9);
            }
          }
          else {
            zz_0104910_(param_1);
          }
        }
      }
    }
    else {
      zz_0104910_(param_1);
    }
  }
  else {
    zz_0104910_(param_1);
    zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x2a0),9);
  }
  return;
}



// ==== 80104910  zz_0104910_ ====

void zz_0104910_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 2;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 8010494c  zz_010494c_ ====

void zz_010494c_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 80104958  zz_0104958_ ====

void zz_0104958_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80104978  zz_0104978_ ====

void zz_0104978_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 801049d4  zz_01049d4_ ====

void zz_01049d4_(int param_1)

{
  undefined1 *puVar1;
  int *piVar2;
  
  if ((*(short *)(param_1 + 1000) == 0xb03) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    *(code **)(puVar1 + 0xc) = zz_0104ae4_;
    *(code **)(puVar1 + 0x10c) = zz_0104e98_;
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
    piVar2 = zz_0006dc8_(0xf0);
    *(int **)(puVar1 + 0xdc) = piVar2;
    if (piVar2 == (int *)0x0) {
      puVar1[0x18] = 2;
    }
  }
  return;
}



// ==== 80104ae4  zz_0104ae4_ ====

void zz_0104ae4_(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_zz_0104b38__80321744)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80104b38  zz_0104b38_ ====

void zz_0104b38_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  undefined4 extraout_r4;
  undefined4 uVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  double dVar6;
  undefined8 uVar7;
  int local_18 [4];
  
  iVar5 = *(int *)(param_9 + 0x90);
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  *(code **)(param_9 + 0x100) = zz_0104ce8_;
  zz_0089100_(param_9,(int)*(char *)(iVar5 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_804393f0;
  dVar6 = (double)FLOAT_804393f0;
  *(undefined1 *)(param_9 + 0x84) = 0x41;
  fVar2 = FLOAT_804393f4;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  *(undefined1 *)(param_9 + 0x89) = 7;
  *(float *)(param_9 + 100) = fVar2;
  *(float *)(param_9 + 0x68) = fVar2;
  *(float *)(param_9 + 0x6c) = fVar2;
  iVar5 = zz_0006f98_(iVar5);
  uVar7 = zz_0007030_(dVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),9,iVar5 + 0xc28,in_r7,in_r8,
                      in_r9,in_r10);
  iVar4 = iVar5 + 0xc28;
  uVar3 = 9;
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),9,iVar4,in_r7,in_r8,in_r9,
                      in_r10);
  zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,uVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  uVar7 = zz_0007cac_((double)FLOAT_804393f8,*(int *)(param_9 + 0xe4));
  local_18[0] = 0;
  zz_0009b38_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(*(int *)(param_9 + 0xe0) + 0xc),*(int *)(*(int *)(param_9 + 0xdc) + 0xc),
              local_18,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0104f20_(param_9,(float *)(param_9 + 0x144));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0104c58_(param_9);
  return;
}



// ==== 80104c58  zz_0104c58_ ====

void zz_0104c58_(int param_1)

{
  zz_0104f8c_(param_1,(float *)(param_1 + 0x144));
  return;
}



// ==== 80104c7c  zz_0104c7c_ ====

void zz_0104c7c_(int param_1)

{
  *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  if (*(int **)(param_1 + 0xdc) != (int *)0x0) {
    zz_0197ad8_(*(int **)(param_1 + 0xdc));
    *(undefined4 *)(param_1 + 0xdc) = 0;
  }
  return;
}



// ==== 80104cc8  zz_0104cc8_ ====

void zz_0104cc8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80104ce8  zz_0104ce8_ ====

/* WARNING: Removing unreachable block (ram,0x80104e78) */
/* WARNING: Removing unreachable block (ram,0x80104cf8) */

void zz_0104ce8_(int param_1)

{
  float *pfVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  float local_24;
  
  FUN_80047aa4(param_1);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x150),(float *)(param_1 + 0x144),&local_2c);
  local_38 = *(float *)(param_1 + 0x118);
  local_34 = *(undefined4 *)(param_1 + 0x128);
  local_30 = *(undefined4 *)(param_1 + 0x138);
  zz_006ebb4_(&local_38,&local_38);
  dVar3 = gnt4_PSQUATDotProduct_bl(&local_2c,&local_38);
  gnt4_PSQUATScale_bl(dVar3,&local_38,&local_38);
  gnt4_PSVECSubtract_bl(&local_2c,&local_38,&local_2c);
  zz_006ec1c_(&local_2c,&local_2c);
  local_38 = *(float *)(param_1 + 0x11c);
  local_34 = *(undefined4 *)(param_1 + 300);
  local_30 = *(undefined4 *)(param_1 + 0x13c);
  zz_006ec1c_(&local_38,&local_38);
  dVar4 = gnt4_PSQUATDotProduct_bl(&local_2c,&local_38);
  dVar3 = (double)FLOAT_804393f0;
  if ((dVar4 <= dVar3) && (dVar3 = dVar4, dVar4 < (double)FLOAT_804393fc)) {
    dVar3 = (double)FLOAT_804393fc;
  }
  dVar3 = (double)gnt4_acos_bl(dVar3);
  local_38 = *(float *)(param_1 + 0x114);
  local_34 = *(undefined4 *)(param_1 + 0x124);
  dVar4 = (double)(FLOAT_80439400 * (float)dVar3);
  local_30 = *(undefined4 *)(param_1 + 0x134);
  zz_006ec1c_(&local_38,&local_38);
  dVar3 = gnt4_PSQUATDotProduct_bl(&local_2c,&local_38);
  if (dVar3 < (double)FLOAT_804393f4) {
    dVar4 = -dVar4;
  }
  iVar2 = 0;
  pfVar1 = (float *)(*(int *)(*(int *)(param_1 + 0xdc) + 0xc) + 0x60);
  do {
    local_2c = pfVar1[3];
    local_28 = pfVar1[7];
    local_24 = pfVar1[0xb];
    gnt4_PSMTXRotRad_bl(dVar4,pfVar1,0x79);
    iVar2 = iVar2 + 1;
    pfVar1[3] = local_2c;
    pfVar1[7] = local_28;
    pfVar1[0xb] = local_24;
    pfVar1 = pfVar1 + 0xc;
  } while (iVar2 < 3);
  return;
}



// ==== 80104e98  zz_0104e98_ ====

void zz_0104e98_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  uint uVar1;
  int iVar2;
  int local_18 [4];
  
  if ((*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') &&
     (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) != '\x04')) {
    iVar2 = *(int *)(param_9 + 0xe0);
    uVar1 = 1;
  }
  else {
    iVar2 = *(int *)(param_9 + 0xe4);
    uVar1 = 0x44;
  }
  local_18[0] = 0;
  zz_0009a14_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar2 + 0xc),
              (float *)(param_9 + 0x114),*(int *)(*(int *)(param_9 + 0xdc) + 0xc),local_18,in_r7,
              in_r8,in_r9,in_r10);
  zz_00097b4_(iVar2,uVar1);
  return;
}



// ==== 80104f20  zz_0104f20_ ====

void zz_0104f20_(int param_1,float *param_2)

{
  gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x114),(float *)&DAT_80321720,param_2);
  gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x114),(float *)&DAT_8032172c,param_2 + 3);
  return;
}



// ==== 80104f8c  zz_0104f8c_ ====

void zz_0104f8c_(int param_1,float *param_2)

{
  int iVar1;
  double dVar2;
  double dVar3;
  float afStack_28 [3];
  float local_1c;
  float local_18;
  float local_14;
  
  iVar1 = *(int *)(param_1 + 0x90);
  gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x114),(float *)&DAT_80321720,param_2);
  gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x114),(float *)&DAT_80321738,&local_1c);
  gnt4_PSVECSubtract_bl(&local_1c,param_2 + 3,afStack_28);
  dVar3 = gnt4_PSVECMag_bl(afStack_28);
  dVar2 = (double)(FLOAT_80439404 * *(float *)(iVar1 + 0xb4));
  if (dVar3 <= dVar2) {
    gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x114),(float *)&DAT_8032172c,&local_1c);
    gnt4_PSVECSubtract_bl(&local_1c,param_2 + 3,&local_1c);
    dVar2 = gnt4_PSVECMag_bl(&local_1c);
    gnt4_PSQUATScale_bl((double)((float)(dVar2 * dVar2) / FLOAT_80439408),&local_1c,param_2 + 9);
    gnt4_PSVECAdd_bl(param_2 + 6,param_2 + 9,param_2 + 6);
    gnt4_PSVECAdd_bl(param_2 + 6,param_2 + 3,param_2 + 3);
    gnt4_PSQUATScale_bl((double)FLOAT_8043940c,param_2 + 6,param_2 + 6);
  }
  else {
    gnt4_PSQUATScale_bl((double)(float)(dVar2 / dVar3),afStack_28,afStack_28);
    gnt4_PSVECAdd_bl(&local_1c,afStack_28,param_2 + 3);
  }
  gnt4_PSVECSubtract_bl(param_2 + 3,param_2,&local_1c);
  if (local_14 * local_14 + local_1c * local_1c + local_18 * local_18 <= FLOAT_804393f4) {
    local_1c = FLOAT_804393f4;
    local_18 = FLOAT_804393f4;
    local_14 = FLOAT_804393f0;
  }
  gnt4_PSVECNormalize_bl(&local_1c,&local_1c);
  gnt4_PSQUATScale_bl((double)(FLOAT_80439410 * *(float *)(iVar1 + 0xb4)),&local_1c,&local_1c);
  gnt4_PSVECAdd_bl(&local_1c,param_2,param_2 + 3);
  return;
}



// ==== 80105144  zz_0105144_ ====

void zz_0105144_(int param_1)

{
  *(undefined **)(param_1 + 0x4b4) = PTR_zz_01052c8__80321f38;
  *(undefined **)(param_1 + 0x4b8) = PTR_zz_0105240__80321f3c;
  *(undefined **)(param_1 + 0x4bc) = PTR_zz_010528c__80321f40;
  *(undefined **)(param_1 + 0x4c0) = PTR_zz_0105290__80321f44;
  *(undefined **)(param_1 + 0x4c4) = PTR_zz_01052b8__80321f48;
  *(undefined **)(param_1 + 0x4c8) = PTR_zz_01052bc__80321f4c;
  *(undefined **)(param_1 + 0x4cc) = PTR_zz_01052c0__80321f50;
  *(undefined **)(param_1 + 0x4d0) = PTR_zz_01052c4__80321f54;
  *(undefined4 *)(param_1 + 0x4d4) = DAT_80321f58;
  *(undefined4 *)(param_1 + 0x4d8) = DAT_80321f5c;
  *(undefined4 *)(param_1 + 0x4dc) = DAT_80321f60;
  *(undefined4 *)(param_1 + 0x4e0) = DAT_80321f64;
  *(undefined **)(param_1 + 0x4e4) = PTR_FUN_80321f68;
  *(undefined **)(param_1 + 0x4e8) = PTR_DAT_80321f6c;
  *(undefined **)(param_1 + 0x4ec) = PTR_PTR_80321f70;
  *(undefined **)(param_1 + 0x4f0) = PTR_DAT_80321f74;
  *(undefined4 *)(param_1 + 0x4ac) = *(undefined4 *)(&DAT_803c4d94 + *(char *)(param_1 + 999) * 4);
  *(undefined **)(param_1 + 0x4b0) = &DAT_80321c88;
  *(undefined **)(param_1 + 0x1d80) = &DAT_80321920;
  *(undefined **)(param_1 + 0x1d84) = &DAT_802bcfa8;
  *(undefined **)(param_1 + 0x1d88) = &DAT_80321760;
  *(undefined **)(param_1 + 0x1d8c) = &DAT_802bbd94;
  *(undefined **)(param_1 + 0x27c) = &DAT_80321ef0;
  return;
}



// ==== 80105240  zz_0105240_ ====

void zz_0105240_(int param_1)

{
  zz_004f1c4_(param_1);
  zz_0106494_(param_1);
  zz_00c74ec_(param_1,0x30);
  zz_00c74ec_(param_1,0x31);
  return;
}



// ==== 8010528c  zz_010528c_ ====

void zz_010528c_(void)

{
  return;
}



// ==== 80105290  zz_0105290_ ====

void zz_0105290_(int param_1)

{
  zz_006d520_(param_1,(float *)&DAT_80321f78);
  return;
}



// ==== 801052b8  zz_01052b8_ ====

void zz_01052b8_(void)

{
  return;
}



// ==== 801052bc  zz_01052bc_ ====

void zz_01052bc_(void)

{
  return;
}



// ==== 801052c0  zz_01052c0_ ====

void zz_01052c0_(void)

{
  return;
}



// ==== 801052c4  zz_01052c4_ ====

void zz_01052c4_(void)

{
  return;
}



// ==== 801052c8  zz_01052c8_ ====

void zz_01052c8_(int param_1)

{
  (*(code *)(&PTR_zz_0105304__80321fa8)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80105304  zz_0105304_ ====

void zz_0105304_(int param_1)

{
  (**(code **)(&DAT_804344a8 + *(char *)(param_1 + 0x581) * 4))();
  return;
}



// ==== 8010533c  zz_010533c_ ====

void zz_010533c_(int param_1)

{
  (*(code *)(&PTR_zz_0105378__80321fb4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80105378  zz_0105378_ ====

void zz_0105378_(int param_1)

{
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x548) = 10;
  return;
}



// ==== 80105390  zz_0105390_ ====

void zz_0105390_(int param_1)

{
  *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -1;
  zz_0106270_(param_1);
  if (*(short *)(param_1 + 0x548) < 1) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x144) = 0;
    *(undefined2 *)(param_1 + 0x146) = 0;
    *(undefined2 *)(param_1 + 0x148) = 0;
    *(undefined2 *)(param_1 + 0x14a) = 0;
  }
  return;
}



// ==== 801053f4  zz_01053f4_ ====

void zz_01053f4_(int param_1)

{
  int iVar1;
  
  zz_0106270_(param_1);
  iVar1 = zz_0106398_(param_1);
  if (iVar1 != 0) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x548) = 0x1e;
  }
  return;
}



// ==== 80105444  zz_0105444_ ====

void zz_0105444_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  *(short *)(param_9 + 0x548) = *(short *)(param_9 + 0x548) + -1;
  if (*(short *)(param_9 + 0x548) < 1) {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 80105494  zz_0105494_ ====

void zz_0105494_(int param_1)

{
  (*(code *)(&PTR_zz_01054d0__80321fc4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801054d0  zz_01054d0_ ====

void zz_01054d0_(int param_1)

{
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x548) = 10;
  return;
}



// ==== 801054e8  zz_01054e8_ ====

void zz_01054e8_(int param_1)

{
  *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -1;
  zz_0106270_(param_1);
  if (*(short *)(param_1 + 0x548) < 1) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x144) = 0;
    *(undefined2 *)(param_1 + 0x146) = 0;
    *(undefined2 *)(param_1 + 0x148) = 0;
    *(undefined2 *)(param_1 + 0x14a) = 0;
  }
  return;
}



// ==== 8010554c  zz_010554c_ ====

void zz_010554c_(int param_1)

{
  int iVar1;
  
  zz_0106270_(param_1);
  iVar1 = zz_0106398_(param_1);
  if (iVar1 != 0) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x548) = 0x1e;
  }
  return;
}



// ==== 8010559c  zz_010559c_ ====

void zz_010559c_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  *(short *)(param_9 + 0x548) = *(short *)(param_9 + 0x548) + -1;
  if (*(short *)(param_9 + 0x548) < 1) {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 801055ec  zz_01055ec_ ====

void zz_01055ec_(int param_1)

{
  (**(code **)(&DAT_804344b0 + *(char *)(param_1 + 0x581) * 4))();
  return;
}



// ==== 80105624  zz_0105624_ ====

void zz_0105624_(int param_1)

{
  float fVar1;
  undefined2 uVar2;
  
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_01056e4__80321fd4)[*(char *)(param_1 + 0x540)])(param_1);
  if (*(char *)(param_1 + 0x542) == '\0') {
    fVar1 = FLOAT_80439418 * *(float *)(param_1 + 0x1dc8);
    uVar2 = (undefined2)
            (int)(FLOAT_8043941c * fVar1 +
                 (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1910) ^ 0x80000000)
                        - DOUBLE_80439428) * (FLOAT_80439420 - fVar1));
    *(undefined2 *)(param_1 + 0x1910) = uVar2;
    *(undefined2 *)(param_1 + 0x190a) = uVar2;
  }
  return;
}



// ==== 801056e4  zz_01056e4_ ====

void zz_01056e4_(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar1 = FLOAT_80439430;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x694) = fVar1 + *(float *)(param_1 + 0x1dc8);
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if (0 < (int)uVar3) {
    uVar3 = FUN_80066838((double)(*(float *)(param_1 + 0x770) * FLOAT_80439434),param_1);
    if (uVar3 == 0) goto LAB_80105784;
  }
  *(undefined1 *)(param_1 + 0x541) = 1;
  *(undefined4 *)(param_1 + 0xcc) = 0;
  *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
LAB_80105784:
  fVar2 = FLOAT_8043943c;
  fVar1 = FLOAT_80439438;
  *(float *)(param_1 + 0x50) = FLOAT_80439438;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x558) = fVar2;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    dVar4 = (double)FLOAT_80439440;
    *(undefined1 *)(param_1 + 0x543) = 0;
    zz_004beb8_(dVar4,param_1,0xf,3,0,0xffffffff,0xffffffff);
  }
  else {
    dVar4 = (double)FLOAT_80439440;
    *(undefined1 *)(param_1 + 0x543) = 1;
    zz_004beb8_(dVar4,param_1,0xf,3,1,0xffffffff,0xffffffff);
  }
  zz_006d144_(param_1,0xc0);
  return;
}



// ==== 80105818  zz_0105818_ ====

void zz_0105818_(int param_1)

{
  short sVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_80439438;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x768);
  if ((fVar2 < *(float *)(param_1 + 0x558)) && (iVar3 = zz_006d144_(param_1,0xc0), iVar3 == 0)) {
    return;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(char *)(param_1 + 0x541) == '\0') {
    *(float *)(param_1 + 0x558) = FLOAT_8043943c;
  }
  else {
    *(float *)(param_1 + 0x558) = FLOAT_80439444;
  }
  *(undefined1 *)(param_1 + 0x709) = 4;
  fVar2 = FLOAT_8043944c;
  if (*(char *)(param_1 + 0x543) == '\0') {
    *(float *)(param_1 + 0x44) = FLOAT_80439448;
    *(float *)(param_1 + 0x4c) = fVar2;
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
    zz_00b2190_(param_1,0);
  }
  else {
    FUN_8006cc90((double)FLOAT_80439450,param_1,1,0,(short *)&DAT_804344b4);
    sVar1 = *(short *)(param_1 + 0x18da);
    dVar4 = zz_0045238_(sVar1);
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_80439448 * dVar4);
    dVar4 = zz_0045204_(sVar1);
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_80439448 * -dVar4);
    dVar4 = zz_0045238_(sVar1);
    *(float *)(param_1 + 0x4c) = (float)((double)FLOAT_8043944c * dVar4);
    dVar4 = zz_0045204_(sVar1);
    dVar5 = (double)FLOAT_80439420;
    *(float *)(param_1 + 0x50) = (float)((double)FLOAT_8043944c * -dVar4);
    zz_0067458_(dVar5,param_1,*(short *)(param_1 + 0x5ae));
    iVar3 = zz_00677b0_(param_1);
    if (iVar3 != 0) {
      *(short *)(param_1 + 0x18da) =
           (short)(int)((float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                               DOUBLE_80439428) *
                       (FLOAT_80439458 * (FLOAT_80439420 - *(float *)(param_1 + 0x1dc8)) +
                       FLOAT_80439454));
      zz_00b2190_(param_1,0);
    }
  }
  *(float *)(param_1 + 0x80c) = FLOAT_80439438;
  return;
}



// ==== 801059e8  zz_01059e8_ ====

void zz_01059e8_(int param_1)

{
  short sVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_80439438;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x768);
  if (fVar2 < *(float *)(param_1 + 0x558)) {
    uVar3 = FUN_80066838((double)FLOAT_8043945c,param_1);
    if ((int)uVar3 < 1) goto LAB_80105a68;
  }
  fVar2 = FLOAT_80439460;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined2 *)(param_1 + 0x548) = DAT_804344bc;
  zz_00f036c_(param_1,0xa7);
LAB_80105a68:
  if (*(char *)(param_1 + 0x543) == '\0') {
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
    zz_00b22f4_(param_1);
  }
  else {
    FUN_8006cc90((double)FLOAT_80439450,param_1,1,0,(short *)&DAT_804344b4);
    sVar1 = *(short *)(param_1 + 0x18da);
    dVar5 = zz_0045238_(sVar1);
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_80439448 * dVar5);
    dVar5 = zz_0045204_(sVar1);
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_80439448 * -dVar5);
    dVar5 = zz_0045238_(sVar1);
    *(float *)(param_1 + 0x4c) = (float)((double)FLOAT_8043944c * dVar5);
    dVar5 = zz_0045204_(sVar1);
    dVar6 = (double)FLOAT_80439420;
    *(float *)(param_1 + 0x50) = (float)((double)FLOAT_8043944c * -dVar5);
    zz_0067458_(dVar6,param_1,*(short *)(param_1 + 0x5ae));
    iVar4 = zz_00677b0_(param_1);
    if (iVar4 != 0) {
      *(short *)(param_1 + 0x18da) =
           (short)(int)((float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                               DOUBLE_80439428) *
                       (FLOAT_80439458 * (FLOAT_80439420 - *(float *)(param_1 + 0x1dc8)) +
                       FLOAT_80439454));
      zz_00b22f4_(param_1);
    }
  }
  return;
}



// ==== 80105b8c  zz_0105b8c_ ====

void zz_0105b8c_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  zz_004cd24_(param_1,0xf);
  iVar3 = zz_006de44_(param_1,0xf0f00);
  if (iVar3 != 0) {
    if (0 < *(short *)(param_1 + 0x548)) {
      *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) + FLOAT_80439464;
      *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -1;
    }
  }
  if (*(char *)(param_1 + 0x543) == '\0') {
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
    zz_00b22f4_(param_1);
  }
  else {
    zz_0067458_((double)FLOAT_80439420,param_1,*(short *)(param_1 + 0x5ae));
    iVar3 = zz_00677b0_(param_1);
    if (iVar3 != 0) {
      *(short *)(param_1 + 0x18da) =
           (short)(int)((float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                               DOUBLE_80439428) *
                       (FLOAT_80439458 * (FLOAT_80439420 - *(float *)(param_1 + 0x1dc8)) +
                       FLOAT_80439454));
      zz_00b22f4_(param_1);
    }
  }
  fVar2 = FLOAT_80439438;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x768);
  fVar1 = FLOAT_80439430;
  if (*(float *)(param_1 + 0x558) <= fVar2) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x542) = 1;
    *(float *)(param_1 + 0x558) = fVar1;
    if (*(char *)(param_1 + 0x543) == '\0') {
      dVar4 = (double)FLOAT_80439440;
      *(float *)(param_1 + 0x4c) = -(*(float *)(param_1 + 0x44) / FLOAT_80439468);
      zz_004beb8_(dVar4,param_1,0xf,0,0,10,1);
    }
    else {
      *(float *)(param_1 + 0x4c) = fVar2;
      dVar4 = (double)FLOAT_80439440;
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
      zz_004beb8_(dVar4,param_1,0xf,0,0,10,1);
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
    }
    *(undefined1 *)(param_1 + 0x709) = 0;
  }
  return;
}



// ==== 80105d5c  zz_0105d5c_ ====

void zz_0105d5c_(int param_1)

{
  float fVar1;
  undefined2 uVar2;
  int iVar3;
  uint uVar4;
  double dVar5;
  undefined8 local_20;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x543) == '\0') {
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
    zz_00b22f4_(param_1);
  }
  else {
    dVar5 = (double)FLOAT_80439420;
    *(float *)(param_1 + 0x44) =
         *(float *)(param_1 + 0x44) *
         (FLOAT_80439470 * (float)(dVar5 - (double)*(float *)(param_1 + 0x1dc8)) + FLOAT_8043946c);
    zz_0067458_(dVar5,param_1,*(short *)(param_1 + 0x5ae));
    iVar3 = zz_00677b0_(param_1);
    if (iVar3 != 0) {
      *(short *)(param_1 + 0x18da) =
           (short)(int)((float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                               DOUBLE_80439428) *
                       (FLOAT_80439458 * (FLOAT_80439420 - *(float *)(param_1 + 0x1dc8)) +
                       FLOAT_80439454));
      zz_00b22f4_(param_1);
      *(undefined1 *)(param_1 + 0x709) = 1;
    }
  }
  fVar1 = FLOAT_80439438;
  uVar4 = (int)*(short *)(param_1 + 0x1910) ^ 0x80000000;
  local_20 = (double)CONCAT44(0x43300000,uVar4);
  uVar2 = (undefined2)
          (int)((float)(local_20 - DOUBLE_80439428) -
               (float)((double)CONCAT44(0x43300000,uVar4) - DOUBLE_80439428) /
               *(float *)(param_1 + 0x558));
  *(undefined2 *)(param_1 + 0x1910) = uVar2;
  *(undefined2 *)(param_1 + 0x190a) = uVar2;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x768);
  if (*(float *)(param_1 + 0x558) <= fVar1) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x1910) = 0;
    *(undefined2 *)(param_1 + 0x190a) = 0;
    *(undefined4 *)(param_1 + 0x694) = *(undefined4 *)(param_1 + 0x1dc8);
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(undefined1 *)(param_1 + 0x709) = 0;
    if (*(char *)(param_1 + 0x543) == '\0') {
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
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 80105f30  zz_0105f30_ ====

void zz_0105f30_(int param_1)

{
  (*(code *)(&PTR_zz_0105f68__804344c0)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80105f68  zz_0105f68_ ====

void zz_0105f68_(int param_1)

{
  (*(code *)(&PTR_zz_0105fa4__80321fe8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80105fa4  zz_0105fa4_ ====

void zz_0105fa4_(int param_1)

{
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x548) = 10;
  return;
}



// ==== 80105fbc  zz_0105fbc_ ====

void zz_0105fbc_(int param_1)

{
  bool bVar1;
  
  *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -1;
  if ((*(short *)(param_1 + 0x548) < 1) || (bVar1 = zz_01062cc_(param_1), bVar1)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x144) = 0;
    *(undefined2 *)(param_1 + 0x146) = 0;
    *(undefined2 *)(param_1 + 0x148) = 0;
    *(undefined2 *)(param_1 + 0x14a) = 0;
  }
  return;
}



// ==== 80106028  zz_0106028_ ====

void zz_0106028_(int param_1)

{
  int iVar1;
  
  zz_01062cc_(param_1);
  iVar1 = zz_006dbe0_(param_1,2,1,1);
  if (iVar1 != 0) {
    zz_00c3be0_(param_1,8);
    zz_00c3be0_(param_1,9);
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x548) = 0x1e;
  return;
}



// ==== 8010609c  zz_010609c_ ====

void zz_010609c_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  *(short *)(param_9 + 0x548) = *(short *)(param_9 + 0x548) + -1;
  if (*(short *)(param_9 + 0x548) < 1) {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 801060ec  zz_01060ec_ ====

void zz_01060ec_(int param_1)

{
  (*(code *)(&PTR_zz_0106128__80321ff8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80106128  zz_0106128_ ====

void zz_0106128_(int param_1)

{
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x548) = 10;
  return;
}



// ==== 80106140  zz_0106140_ ====

void zz_0106140_(int param_1)

{
  bool bVar1;
  
  *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -1;
  if ((*(short *)(param_1 + 0x548) < 1) || (bVar1 = zz_01062cc_(param_1), bVar1)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x144) = 0;
    *(undefined2 *)(param_1 + 0x146) = 0;
    *(undefined2 *)(param_1 + 0x148) = 0;
    *(undefined2 *)(param_1 + 0x14a) = 0;
  }
  return;
}



// ==== 801061ac  zz_01061ac_ ====

void zz_01061ac_(int param_1)

{
  int iVar1;
  
  zz_01062cc_(param_1);
  iVar1 = zz_006dbe0_(param_1,2,1,1);
  if (iVar1 != 0) {
    zz_00c3be0_(param_1,8);
    zz_00c3be0_(param_1,9);
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x548) = 0x1e;
  return;
}



// ==== 80106220  zz_0106220_ ====

void zz_0106220_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  *(short *)(param_9 + 0x548) = *(short *)(param_9 + 0x548) + -1;
  if (*(short *)(param_9 + 0x548) < 1) {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 80106270  zz_0106270_ ====

uint zz_0106270_(int param_1)

{
  uint uVar1;
  short local_8 [4];
  
  local_8[0] = 0x7fff;
  local_8[1] = 0x8000;
  local_8[2] = 0xffff;
  local_8[3] = 0;
  uVar1 = FUN_8006cc90((double)FLOAT_80439434,param_1,2,1,local_8);
  return (-uVar1 | uVar1) >> 0x1f;
}



// ==== 801062cc  zz_01062cc_ ====

bool zz_01062cc_(int param_1)

{
  int iVar1;
  char cVar2;
  short local_18 [8];
  
  zz_0106270_(param_1);
  local_18[0] = 0;
  local_18[1] = 0;
  local_18[2] = 0xe000;
  local_18[3] = 0x2000;
  iVar1 = FUN_8006cc90((double)FLOAT_80439434,param_1,9,2,local_18);
  cVar2 = iVar1 != 0;
  local_18[0] = 0;
  local_18[1] = 0;
  local_18[2] = 0xe000;
  local_18[3] = 0x2000;
  iVar1 = FUN_8006cc90((double)FLOAT_80439434,param_1,10,2,local_18);
  if (iVar1 != 0) {
    cVar2 = cVar2 + '\x01';
  }
  return cVar2 == '\x02';
}



// ==== 80106398  zz_0106398_ ====

undefined4 zz_0106398_(int param_1)

{
  int iVar1;
  
  if ((*(uint *)(param_1 + 0x5b4) & 0x200) != 0) {
    *(undefined2 *)(param_1 + 0x144) = 1;
  }
  if (*(short *)(param_1 + 0x146) == 0) {
    *(undefined2 *)(param_1 + 0x146) = 5;
    *(short *)(param_1 + 0x148) = *(short *)(param_1 + 0x148) + 1;
    iVar1 = zz_006dbe0_(param_1,0,1,1);
    if (iVar1 == 0) {
      return 1;
    }
    zz_0082824_(param_1,(int)*(short *)(param_1 + 0x14a) + 0x15);
    *(short *)(param_1 + 0x14a) = *(short *)(param_1 + 0x14a) + 1;
    if (2 < *(short *)(param_1 + 0x14a)) {
      *(undefined2 *)(param_1 + 0x14a) = 0;
    }
    if (*(short *)(param_1 + 0x144) == 0) {
      if (2 < *(short *)(param_1 + 0x148)) {
        return 1;
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x144) = 0;
      if (4 < *(short *)(param_1 + 0x148)) {
        return 1;
      }
    }
  }
  else {
    *(short *)(param_1 + 0x146) = *(short *)(param_1 + 0x146) + -1;
  }
  return 0;
}



// ==== 80106494  zz_0106494_ ====

bool zz_0106494_(int param_1)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0,0,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x13] = 0;
    puVar1[0x11] = 0;
    *(code **)(puVar1 + 0xc) = zz_010659c_;
    *(code **)(puVar1 + 0x10c) = zz_0106814_;
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
  return puVar1 != (undefined1 *)0x0;
}



// ==== 8010659c  zz_010659c_ ====

void zz_010659c_(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_zz_01065f0__80322020)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801065f0  zz_01065f0_ ====

void zz_01065f0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 extraout_r4;
  int iVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  undefined8 uVar6;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar5 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar6 = zz_0089100_(param_9,(int)*(char *)(iVar5 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x5f;
  fVar1 = FLOAT_80439478;
  iVar3 = *(char *)(param_9 + 0x13) * 0x18;
  uVar2 = *(undefined4 *)(&DAT_80322010 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_8032200c + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80322014 + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_80322018 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_8032201c + iVar3);
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_8032200a + iVar3);
  *(undefined2 *)(param_9 + 0x80) = 0;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_80322008 + iVar3),iVar5 + 0xc28,in_r7,in_r8,in_r9,in_r10)
  ;
  iVar4 = iVar5 + 0xc28;
  iVar3 = (int)*(short *)(&DAT_80322008 + iVar3);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043947c,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0106724_(param_9);
  return;
}



// ==== 80106724  zz_0106724_ ====

void zz_0106724_(int param_1)

{
  undefined8 local_18;
  undefined8 local_10;
  
  if ((*(uint *)(*(int *)(param_1 + 0x90) + 0x5e0) & 0x20000000) == 0) {
    if (*(char *)(*(int *)(param_1 + 0x90) + 0x6e8) == '\0') {
      local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x80)) ^ 0x80000000);
      *(short *)(param_1 + 0x80) =
           (short)(int)((FLOAT_80439484 * (float)(local_18 - DOUBLE_80439498) + FLOAT_80439480) /
                       FLOAT_80439488);
    }
    else {
      local_10 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x80)) ^ 0x80000000);
      *(short *)(param_1 + 0x80) =
           (short)(int)((FLOAT_80439490 * (float)(local_10 - DOUBLE_80439498) + FLOAT_8043948c) /
                       FLOAT_80439494);
    }
    *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + *(short *)(param_1 + 0x80);
  }
  return;
}



// ==== 801067e8  zz_01067e8_ ====

void zz_01067e8_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 801067f4  zz_01067f4_ ====

void zz_01067f4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80106814  zz_0106814_ ====

void zz_0106814_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  if (*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') {
    iVar1 = *(int *)(param_9 + 0xe0);
    if (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) == '\x04') {
      uVar2 = 0x44;
    }
    else {
      uVar2 = 1;
    }
  }
  else {
    iVar1 = *(int *)(param_9 + 0xe4);
    uVar2 = 0x44;
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar1,uVar2);
  return;
}



// ==== 80106894  zz_0106894_ ====

void zz_0106894_(int param_1)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0,0,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = zz_0106984_;
    *(code **)(puVar1 + 0x10c) = zz_0106b34_;
    puVar1[0x11] = 0;
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



// ==== 80106984  zz_0106984_ ====

void zz_0106984_(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_zz_01069d8__80322048)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801069d8  zz_01069d8_ ====

void zz_01069d8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 extraout_r4;
  int iVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar6;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar6 = zz_0089100_(param_9,(int)*(char *)(param_9 + 0x96) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x43;
  fVar1 = FLOAT_804394a0;
  iVar4 = *(char *)(param_9 + 0x11) * 0x18;
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_80322032 + iVar4);
  uVar2 = *(undefined4 *)(&DAT_80322038 + iVar4);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80322034 + iVar4);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_8032203c + iVar4);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_80322040 + iVar4);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_80322044 + iVar4);
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar3 = zz_0006f98_(param_9);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_80322030 + iVar4),iVar3 + 0xc28,in_r7,in_r8,in_r9,in_r10)
  ;
  iVar5 = iVar3 + 0xc28;
  iVar4 = (int)*(short *)(&DAT_80322030 + iVar4);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe4),iVar4,iVar5,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar4,iVar5,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_804394a4,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0106b00_();
  return;
}



// ==== 80106b00  zz_0106b00_ ====

void zz_0106b00_(void)

{
  return;
}



// ==== 80106b04  zz_0106b04_ ====

void zz_0106b04_(int param_1)

{
  *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  return;
}



// ==== 80106b14  zz_0106b14_ ====

void zz_0106b14_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80106b34  zz_0106b34_ ====

void zz_0106b34_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)(param_9 + 0x90);
  if (*(char *)(iVar1 + 0x146) == '\0') {
    if ((*(char *)(iVar1 + 0xae) == '\0') && (*(char *)(iVar1 + 0x3ec) != '\x04')) {
      iVar1 = *(int *)(param_9 + 0xe0);
      uVar2 = 1;
    }
    else {
      iVar1 = *(int *)(param_9 + 0xe4);
      uVar2 = 0x44;
    }
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
                (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(iVar1,uVar2);
  }
  return;
}



// ==== 80106bb8  zz_0106bb8_ ====

void zz_0106bb8_(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  piVar2 = zz_0006dc8_(0xc0);
  *(int **)(param_1 + 0xdc) = piVar2;
  puVar3 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar3 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar3 = *(undefined4 *)(param_1 + 0x20);
    puVar3[1] = uVar1;
    puVar3[2] = *(undefined4 *)(param_1 + 0x28);
    zz_00e3758_(param_1,-0x7fcdd2a8,3,puVar3 + 3,(float *)(puVar3 + 0x12));
    zz_00e3758_(param_1,-0x7fcdd218,2,puVar3 + 0xc,(float *)(puVar3 + 0x1b));
  }
  return;
}



// ==== 80106c54  zz_0106c54_ ====

void zz_0106c54_(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  puVar2 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar2 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar2 = *(undefined4 *)(param_1 + 0x20);
    puVar2[1] = uVar1;
    puVar2[2] = *(undefined4 *)(param_1 + 0x28);
    if ((*(uint *)(param_1 + 0x5e0) & 0x20001000) == 0) {
      zz_00e38a4_(param_1,(float *)&DAT_80322d58,3,(float *)(puVar2 + 3),(float *)(puVar2 + 0x12));
      zz_00e38a4_(param_1,(float *)&DAT_80322de8,2,(float *)(puVar2 + 0xc),(float *)(puVar2 + 0x1b))
      ;
    }
    else {
      FUN_800e4f9c(param_1,-0x7fcdd2a8,3,(float *)(puVar2 + 3),(float *)(puVar2 + 0x21));
      FUN_800e4f9c(param_1,-0x7fcdd218,2,(float *)(puVar2 + 0xc),(float *)(puVar2 + 0x2a));
    }
  }
  return;
}



// ==== 80106d2c  zz_0106d2c_ ====

void zz_0106d2c_(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}



// ==== 80106d64  zz_0106d64_ ====

void zz_0106d64_(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcdd2a8,3,pfVar2 + 3,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcdd218,2,pfVar2 + 0xc,afStack_18);
    zz_00e5184_(param_1,-0x7fcdd2a8,3,pfVar2 + 3,pfVar2 + 0x21);
    zz_00e5184_(param_1,-0x7fcdd218,2,pfVar2 + 0xc,pfVar2 + 0x2a);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}



// ==== 80106e3c  zz_0106e3c_ ====

void zz_0106e3c_(int param_1)

{
  *(undefined **)(param_1 + 0x4b4) = PTR_FUN_80322e48;
  *(undefined **)(param_1 + 0x4b8) = PTR_zz_0106f38__80322e4c;
  *(undefined **)(param_1 + 0x4bc) = PTR_zz_0106f94__80322e50;
  *(undefined **)(param_1 + 0x4c0) = PTR_zz_0107134__80322e54;
  *(undefined **)(param_1 + 0x4c4) = PTR_LAB_80322e58;
  *(undefined **)(param_1 + 0x4c8) = PTR_LAB_80322e5c;
  *(undefined **)(param_1 + 0x4cc) = PTR_LAB_80322e60;
  *(undefined **)(param_1 + 0x4d0) = PTR_FUN_80322e64;
  *(undefined **)(param_1 + 0x4d4) = PTR_FUN_80322e68;
  *(undefined **)(param_1 + 0x4d8) = PTR_FUN_80322e6c;
  *(undefined4 *)(param_1 + 0x4dc) = DAT_80322e70;
  *(undefined **)(param_1 + 0x4e0) = PTR_FUN_80322e74;
  *(undefined **)(param_1 + 0x4e4) = PTR_FUN_80322e78;
  *(undefined **)(param_1 + 0x4e8) = PTR_DAT_80322e7c;
  *(undefined **)(param_1 + 0x4ec) = PTR_PTR_80322e80;
  *(undefined **)(param_1 + 0x4f0) = PTR_DAT_80322e84;
  *(undefined4 *)(param_1 + 0x4ac) = *(undefined4 *)(&DAT_803c4d94 + *(char *)(param_1 + 999) * 4);
  *(undefined **)(param_1 + 0x4b0) = &DAT_80322f40;
  *(undefined **)(param_1 + 0x1d80) = &DAT_80322060;
  *(undefined **)(param_1 + 0x1d84) = &DAT_802bc080;
  *(undefined **)(param_1 + 0x1d88) = &DAT_803228a0;
  *(undefined **)(param_1 + 0x1d8c) = &DAT_802bae60;
  *(undefined **)(param_1 + 0x27c) = &DAT_80323208;
  return;
}



// ==== 80106f38  zz_0106f38_ ====

void zz_0106f38_(int param_1)

{
  *(undefined1 *)(param_1 + 0x6e8) = 2;
  zz_0106894_(param_1);
  FUN_8011439c(param_1);
  *(undefined1 *)(param_1 + 0x146) = 0;
  *(undefined1 *)(param_1 + 0x147) = 0;
  zz_0106bb8_(param_1);
  zz_00c74ec_(param_1,5);
  return;
}



// ==== 80106f94  zz_0106f94_ ====

uint zz_0106f94_(int param_1)

{
  byte bVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  
  zz_010a4ac_(param_1);
  bVar1 = *(byte *)(param_1 + 0x147);
  uVar3 = (uint)bVar1;
  if (bVar1 != 0) {
    *(byte *)(param_1 + 0x147) = bVar1 - 1;
  }
  if ((*(uint *)(param_1 + 0x5bc) & 0x400) != 0) {
    cVar2 = *(char *)(param_1 + 0x146);
    if (cVar2 == '\x01') {
      if (*(char *)(param_1 + 0x147) == '\0') {
        if (*(float *)(param_1 + 0x694) <= FLOAT_804394ac) {
          *(undefined1 *)(param_1 + 0x147) = 0xf;
          iVar4 = zz_006dbe0_(param_1,2,1,1);
          if (iVar4 == 0) {
            uVar3 = zz_0011cc4_((int)*(char *)(param_1 + 0x3e4),2);
          }
          else {
            *(char *)(param_1 + 0x148) = *(char *)(param_1 + 0x148) + '\x01';
            uVar3 = zz_00f0214_(param_1,4,3);
            if ('\x06' < *(char *)(param_1 + 0x148)) {
              *(undefined1 *)(param_1 + 0x148) = 7;
            }
          }
          *(float *)(param_1 + 0x694) = FLOAT_804394a8 + *(float *)(param_1 + 0x1dc8);
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x146) = 2;
      }
    }
    else if (((cVar2 < '\x01') && (-1 < cVar2)) && (*(char *)(param_1 + 0x147) == '\0')) {
      *(undefined1 *)(param_1 + 0x147) = 0xf;
      iVar4 = zz_006dbe0_(param_1,2,1,1);
      if (iVar4 == 0) {
        uVar3 = zz_0011cc4_((int)*(char *)(param_1 + 0x3e4),2);
      }
      else {
        *(undefined1 *)(param_1 + 0x146) = 1;
        *(undefined1 *)(param_1 + 0x148) = 1;
        bVar5 = zz_01073f8_(param_1);
        uVar3 = (uint)bVar5;
      }
      *(float *)(param_1 + 0x694) = FLOAT_804394a8 + *(float *)(param_1 + 0x1dc8);
    }
  }
  if (*(char *)(param_1 + 0x146) != '\0') {
    uVar3 = zz_00f0104_(param_1,4,3);
  }
  return uVar3;
}



// ==== 80106f9c  zz_0106f9c_ ====

uint zz_0106f9c_(int param_1)

{
  byte bVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  
  zz_010a4ac_(param_1);
  bVar1 = *(byte *)(param_1 + 0x147);
  uVar3 = (uint)bVar1;
  if (bVar1 != 0) {
    *(byte *)(param_1 + 0x147) = bVar1 - 1;
  }
  if ((*(uint *)(param_1 + 0x5bc) & 0x400) != 0) {
    cVar2 = *(char *)(param_1 + 0x146);
    if (cVar2 == '\x01') {
      if (*(char *)(param_1 + 0x147) == '\0') {
        if (*(float *)(param_1 + 0x694) <= FLOAT_804394ac) {
          *(undefined1 *)(param_1 + 0x147) = 0xf;
          iVar4 = zz_006dbe0_(param_1,2,1,1);
          if (iVar4 == 0) {
            uVar3 = zz_0011cc4_((int)*(char *)(param_1 + 0x3e4),2);
          }
          else {
            *(char *)(param_1 + 0x148) = *(char *)(param_1 + 0x148) + '\x01';
            uVar3 = zz_00f0214_(param_1,4,3);
            if ('\x06' < *(char *)(param_1 + 0x148)) {
              *(undefined1 *)(param_1 + 0x148) = 7;
            }
          }
          *(float *)(param_1 + 0x694) = FLOAT_804394a8 + *(float *)(param_1 + 0x1dc8);
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x146) = 2;
      }
    }
    else if (((cVar2 < '\x01') && (-1 < cVar2)) && (*(char *)(param_1 + 0x147) == '\0')) {
      *(undefined1 *)(param_1 + 0x147) = 0xf;
      iVar4 = zz_006dbe0_(param_1,2,1,1);
      if (iVar4 == 0) {
        uVar3 = zz_0011cc4_((int)*(char *)(param_1 + 0x3e4),2);
      }
      else {
        *(undefined1 *)(param_1 + 0x146) = 1;
        *(undefined1 *)(param_1 + 0x148) = 1;
        bVar5 = zz_01073f8_(param_1);
        uVar3 = (uint)bVar5;
      }
      *(float *)(param_1 + 0x694) = FLOAT_804394a8 + *(float *)(param_1 + 0x1dc8);
    }
  }
  if (*(char *)(param_1 + 0x146) != '\0') {
    uVar3 = zz_00f0104_(param_1,4,3);
  }
  return uVar3;
}



// ==== 80106fec  zz_0106fec_ ====

void zz_0106fec_(void)

{
  int unaff_r31;
  
  if (*(char *)(unaff_r31 + 0x146) != '\0') {
    zz_00f0104_(unaff_r31,4,3);
  }
  return;
}



// ==== 80107134  zz_0107134_ ====

void zz_0107134_(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x6e9);
  if (cVar1 == '\x02') {
    *(undefined1 *)(param_1 + 0xaf) = 0xff;
  }
  else if ((cVar1 < '\x02') && ('\0' < cVar1)) {
    *(undefined1 *)(param_1 + 0xaf) = 1;
    zz_001ab6c_(param_1,0x1c);
    *(undefined1 *)(param_1 + 0x6e9) = 0;
  }
  return;
}



// ==== 801071a0  FUN_801071a0 ====

void FUN_801071a0(int param_1)

{
  zz_0106c54_(param_1);
  return;
}



// ==== 801071cc  FUN_801071cc ====

void FUN_801071cc(int param_1)

{
  zz_0106d2c_(param_1);
  return;
}



// ==== 801071ec  FUN_801071ec ====

void FUN_801071ec(int param_1)

{
  zz_0106d64_(param_1);
  return;
}



// ==== 8010720c  FUN_8010720c ====

void FUN_8010720c(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_804344c8)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 80107278  FUN_80107278 ====

void FUN_80107278(int param_1)

{
  (*(code *)(&PTR_FUN_80322e88)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801072b4  FUN_801072b4 ====

void FUN_801072b4(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_80322e98)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801072fc  FUN_801072fc ====

void FUN_801072fc(int param_1)

{
  zz_010b2f4_(param_1);
  return;
}



// ==== 80107320  FUN_80107320 ====

void FUN_80107320(int param_1)

{
  zz_010b7ac_(param_1);
  return;
}



// ==== 80107344  FUN_80107344 ====

void FUN_80107344(int param_1)

{
  zz_010bd10_(param_1);
  return;
}



// ==== 80107368  FUN_80107368 ====

void FUN_80107368(int param_1)

{
  zz_010c220_(param_1);
  return;
}



// ==== 8010738c  FUN_8010738c ====

void FUN_8010738c(int param_1)

{
  zz_010c590_(param_1);
  return;
}



// ==== 801073b0  FUN_801073b0 ====

void FUN_801073b0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  double dVar1;
  
  zz_006a474_(param_9);
  dVar1 = (double)FLOAT_804394b0;
  *(float *)(param_9 + 0x694) = (float)(dVar1 + (double)*(float *)(param_9 + 0x1dc8));
  zz_006a668_(dVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,5,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801073f8  zz_01073f8_ ====

bool zz_01073f8_(int param_1)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 == (undefined1 *)0x0) {
    *(undefined1 *)(param_1 + 0x146) = 0;
    *(undefined2 *)(param_1 + 0x784) = *(undefined2 *)(param_1 + 0x79e);
    *(undefined2 *)(param_1 + 0x786) = *(undefined2 *)(param_1 + 0x79e);
  }
  else {
    *puVar1 = 1;
    puVar1[0x13] = 0;
    puVar1[0x11] = 0;
    puVar1[0x10] = 0x22;
    *(code **)(puVar1 + 0xc) = FUN_80107510;
    *(code **)(puVar1 + 0x10c) = FUN_80107e1c;
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
  return puVar1 != (undefined1 *)0x0;
}



// ==== 80107510  FUN_80107510 ====

void FUN_80107510(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x90);
  iVar1 = zz_00840b8_(param_1);
  if (iVar1 != 0) {
    *(undefined1 *)(iVar2 + 0x146) = 0;
    zz_006de10_(iVar2,2);
  }
  (*(code *)(&PTR_FUN_80323310)[*(char *)(param_1 + 0x18)])(param_1);
  *(undefined1 *)(param_1 + 0x22d) = *(undefined1 *)(iVar2 + 0x148);
  return;
}



// ==== 80107590  FUN_80107590 ====

void FUN_80107590(int param_1)

{
  float fVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  uVar3 = 0x80320000;
  iVar6 = *(int *)(param_1 + 0x90);
  *(undefined1 *)(param_1 + 0x18) = 1;
  iVar4 = *(char *)(param_1 + 0x13) * 0x18;
  *(code **)(param_1 + 0x100) = FUN_80047aa4;
  iVar5 = iVar4;
  zz_0089100_(param_1,0,1);
  *(undefined1 *)(param_1 + 0x84) = 0x1e;
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar6 + *(short *)(&DAT_803232fa + iVar4) * 0x30 + 0x8d4),
             (float *)(iVar4 + -0x7fcdcd04),(float *)(param_1 + 0x20));
  dVar7 = FUN_8003db9c((float *)(param_1 + 0x20));
  dVar8 = (double)FLOAT_804394b8;
  dVar9 = (double)*(float *)(param_1 + 0x24);
  fVar1 = (float)(dVar8 * (double)*(float *)(iVar6 + 0xb4) + dVar7);
  if (dVar9 < (double)fVar1) {
    *(float *)(param_1 + 0x24) = fVar1;
  }
  zz_008458c_((float *)(param_1 + 0x20));
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(iVar6 + 0x70);
  *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(iVar6 + 0x74);
  iVar2 = zz_0006f98_(iVar6);
  zz_0006fb4_(dVar7,dVar8,dVar9,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar2 + 0x600),
              *(int *)(param_1 + 0xe0),(int)*(short *)(&DAT_803232f8 + iVar4),uVar3,iVar5,in_r8,
              in_r9,in_r10);
  *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + '1';
  *(undefined1 *)(param_1 + 0x86) = 0;
  *(undefined1 *)(param_1 + 0x224) = 0;
  *(undefined1 *)(param_1 + 0x225) = 0;
  *(undefined1 *)(param_1 + 0x226) = 0;
  *(undefined1 *)(param_1 + 0x227) = 0;
  *(undefined1 *)(param_1 + 0x228) = 0;
  *(undefined1 *)(param_1 + 0x229) = 0;
  *(undefined1 *)(param_1 + 0x22a) = 0;
  *(undefined1 *)(param_1 + 0x22b) = 0;
  *(undefined4 *)(param_1 + 0x1c4) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x1c8) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x1cc) = *(undefined4 *)(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0x1d0) = *(undefined4 *)(param_1 + 0x1c4);
  *(undefined4 *)(param_1 + 0x1d4) = *(undefined4 *)(param_1 + 0x1c8);
  *(undefined4 *)(param_1 + 0x1d8) = *(undefined4 *)(param_1 + 0x1cc);
  *(undefined1 *)(param_1 + 0x224) = 1;
  *(undefined1 *)(param_1 + 0x225) = 1;
  *(undefined1 *)(param_1 + 0x22c) = 1;
  zz_00a2bf8_(iVar6,param_1,(undefined4 *)(param_1 + 0x1c4),(undefined4 *)(param_1 + 0x1d0),3,0);
  *(undefined4 *)(param_1 + 0x230) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x234) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x238) = *(undefined4 *)(param_1 + 0x28);
  zz_0117ed4_(param_1,param_1 + 0x230,0);
  return;
}



// ==== 80107734  FUN_80107734 ====

void FUN_80107734(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  cVar1 = *(char *)(param_1 + 0x19);
  iVar4 = *(int *)(param_1 + 0x90);
  if (cVar1 == '\x01') {
    FUN_80107978(param_1);
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    FUN_801077e4(param_1);
  }
  iVar3 = param_1 + *(char *)(param_1 + 0x22c) * 0xc;
  uVar2 = *(undefined4 *)(iVar3 + 0x1c8);
  *(undefined4 *)(param_1 + 0x230) = *(undefined4 *)(iVar3 + 0x1c4);
  *(undefined4 *)(param_1 + 0x234) = uVar2;
  *(undefined4 *)(param_1 + 0x238) = *(undefined4 *)(iVar3 + 0x1cc);
  *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(iVar4 + 0xb4);
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(param_1 + 0xb4);
  return;
}



// ==== 801077e4  FUN_801077e4 ====

void FUN_801077e4(int param_1)

{
  float fVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  double dVar6;
  
  iVar5 = *(int *)(param_1 + 0x90);
  iVar4 = *(char *)(param_1 + 0x13) * 0x18;
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar5 + *(short *)(&DAT_803232fa + iVar4) * 0x30 + 0x8d4),
             (float *)(iVar4 + -0x7fcdcd04),
             (float *)(param_1 + *(char *)(param_1 + 0x22c) * 0xc + 0x1c4));
  if (*(char *)(iVar5 + 0x146) == '\x02') {
    *(undefined1 *)(param_1 + 0x19) = 1;
    *(undefined1 *)(param_1 + 0x22e) = 0;
  }
  else if (*(char *)(param_1 + 0x22d) != *(char *)(iVar5 + 0x148)) {
    dVar6 = FUN_8003db9c((float *)(param_1 + *(char *)(param_1 + 0x22c) * 0xc + 0x1c4));
    fVar1 = (float)((double)FLOAT_804394b8 * (double)*(float *)(iVar5 + 0xb4) + dVar6);
    iVar3 = param_1 + *(char *)(param_1 + 0x22c) * 0xc;
    if (*(float *)(iVar3 + 0x1c8) < fVar1) {
      *(float *)(iVar3 + 0x1c8) = fVar1;
    }
    cVar2 = *(char *)(param_1 + 0x22c);
    zz_00a2bf8_(iVar5,param_1,(undefined4 *)(param_1 + cVar2 * 0xc + 0x1c4),
                (undefined4 *)(param_1 + (cVar2 + 1) * 0xc + 0x1c4),3,cVar2);
    *(char *)(param_1 + 0x22c) = *(char *)(param_1 + 0x22c) + '\x01';
    *(undefined1 *)(param_1 + *(char *)(param_1 + 0x22c) + 0x224) = 1;
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar5 + *(short *)(&DAT_803232fa + iVar4) * 0x30 + 0x8d4),
               (float *)(iVar4 + -0x7fcdcd04),
               (float *)(param_1 + *(char *)(param_1 + 0x22c) * 0xc + 0x1c4));
    zz_008458c_((float *)(param_1 + *(char *)(param_1 + 0x22c) * 0xc + 0x1c4));
  }
  return;
}



// ==== 80107978  FUN_80107978 ====

/* WARNING: Removing unreachable block (ram,0x80107dcc) */
/* WARNING: Removing unreachable block (ram,0x80107988) */

void FUN_80107978(int param_1)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  float fStack_34;
  float local_30;
  
  iVar7 = *(int *)(param_1 + 0x90);
  iVar5 = *(char *)(param_1 + 0x13) * 0x18;
  dVar8 = gnt4_PSVECSquareDistance_bl((float *)(iVar7 + 0x2c),(float *)(iVar7 + 0x5e8));
  if ((double)FLOAT_804394bc < dVar8) {
    dVar9 = 1.0 / SQRT(dVar8);
    dVar9 = DOUBLE_804394c0 * dVar9 * -(dVar8 * dVar9 * dVar9 - DOUBLE_804394c8);
    dVar9 = DOUBLE_804394c0 * dVar9 * -(dVar8 * dVar9 * dVar9 - DOUBLE_804394c8);
    dVar8 = (double)(float)(dVar8 * DOUBLE_804394c0 * dVar9 *
                                    -(dVar8 * dVar9 * dVar9 - DOUBLE_804394c8));
  }
  if ((double)(FLOAT_804394d0 * *(float *)(iVar7 + 0xb4)) < dVar8) {
    *(undefined1 *)(param_1 + 0x22e) = 0;
  }
  else {
    *(char *)(param_1 + 0x22e) = *(char *)(param_1 + 0x22e) + '\x01';
  }
  if ((((*(char *)(iVar7 + 0x146) == '\x03') || ((*(uint *)(iVar7 + 0x5e0) & 0x1000) != 0)) ||
      (*(char *)(iVar7 + 0x18) != '\x01')) ||
     ((*(char *)(iVar7 + 0x6cb) != '\0' || (',' < *(char *)(param_1 + 0x22e))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(iVar7 + 0x146) = 0;
    *(undefined2 *)(iVar7 + 0x784) = *(undefined2 *)(iVar7 + 0x79e);
    *(undefined2 *)(iVar7 + 0x786) = *(undefined2 *)(iVar7 + 0x79e);
  }
  else {
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar7 + *(short *)(&DAT_803232fa + iVar5) * 0x30 + 0x8d4),
               (float *)(iVar5 + -0x7fcdcd04),
               (float *)(param_1 + *(char *)(param_1 + 0x22c) * 0xc + 0x1c4));
    gnt4_PSVECSubtract_bl
              ((float *)(param_1 + (*(char *)(param_1 + 0x22c) + -1) * 0xc + 0x1c4),
               (float *)(param_1 + *(char *)(param_1 + 0x22c) * 0xc + 0x1c4),&fStack_34);
    dVar8 = gnt4_PSVECMag_bl(&fStack_34);
    if (dVar8 <= (double)(FLOAT_804394d4 * *(float *)(param_1 + 0xb4))) {
      zz_006de10_(iVar7,2);
      if (*(char *)(param_1 + 0x22c) == 1) {
        *(undefined1 *)(param_1 + 0x18) = 2;
        *(undefined1 *)(iVar7 + 0x146) = 0;
        zz_00f036c_(iVar7,0xc3);
        return;
      }
      *(undefined1 *)(param_1 + *(char *)(param_1 + 0x22c) + 0x224) = 0;
      *(char *)(param_1 + 0x22c) = *(char *)(param_1 + 0x22c) + -1;
      *(char *)(iVar7 + 0x148) = *(char *)(iVar7 + 0x148) + -1;
      zz_00f0214_(iVar7,4,3);
    }
    gnt4_PSVECNormalize_bl(&fStack_34,&fStack_34);
    fVar1 = FLOAT_804394bc;
    if (*(char *)(iVar7 + 0x87) == '\0') {
      fVar1 = FLOAT_804394d4 * *(float *)(param_1 + 0xb4);
      iVar4 = param_1 + *(char *)(param_1 + 0x22c) * 0xc;
      fVar2 = *(float *)(iVar4 + 0x1bc) - *(float *)(iVar4 + 0x1c8);
      if (((fVar1 <= fVar2) || (fVar2 <= -fVar1)) && (FLOAT_804394d8 <= local_30)) {
        *(float *)(iVar7 + 0x48) = FLOAT_804394bc;
        *(byte *)(iVar7 + 0x732) = *(byte *)(iVar7 + 0x732) | 0x10;
      }
    }
    else if ((FLOAT_804394bc < local_30) &&
            (*(byte *)(iVar7 + 0x732) = *(byte *)(iVar7 + 0x732) | 0x10,
            *(float *)(iVar7 + 0x48) <= fVar1)) {
      *(float *)(iVar7 + 0x48) = fVar1;
    }
    dVar9 = (double)(FLOAT_804394d4 * *(float *)(param_1 + 0xb4));
    if ((double)(float)((double)FLOAT_804394dc * dVar9) < dVar8) {
      dVar8 = (double)(FLOAT_804394e0 * *(float *)(param_1 + 0xb4));
      if (*(char *)(iVar7 + 0x70c) != '\0') {
        dVar8 = (double)(float)(dVar8 * (double)*(float *)(iVar7 + 0x768));
      }
      gnt4_PSQUATScale_bl(dVar8,&fStack_34,&fStack_34);
    }
    else {
      gnt4_PSQUATScale_bl(dVar9,&fStack_34,&fStack_34);
    }
    zz_0084498_(iVar7,&fStack_34);
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar7 + *(short *)(&DAT_803232fa + iVar5) * 0x30 + 0x8d4),
               (float *)(iVar5 + -0x7fcdcd04),
               (float *)(param_1 + *(char *)(param_1 + 0x22c) * 0xc + 0x1c4));
    puVar6 = (undefined4 *)(param_1 + 0x1c4);
    iVar5 = 0;
    iVar7 = 2;
    do {
      if (*(char *)(param_1 + 0x22c) < iVar5) {
        iVar4 = param_1 + *(char *)(param_1 + 0x22c) * 0xc;
        uVar3 = *(undefined4 *)(iVar4 + 0x1c8);
        *puVar6 = *(undefined4 *)(iVar4 + 0x1c4);
        puVar6[1] = uVar3;
        puVar6[2] = *(undefined4 *)(iVar4 + 0x1cc);
      }
      if ((int)*(char *)(param_1 + 0x22c) < iVar5 + 1) {
        iVar4 = param_1 + *(char *)(param_1 + 0x22c) * 0xc;
        uVar3 = *(undefined4 *)(iVar4 + 0x1c8);
        puVar6[3] = *(undefined4 *)(iVar4 + 0x1c4);
        puVar6[4] = uVar3;
        puVar6[5] = *(undefined4 *)(iVar4 + 0x1cc);
      }
      if ((int)*(char *)(param_1 + 0x22c) < iVar5 + 2) {
        iVar4 = param_1 + *(char *)(param_1 + 0x22c) * 0xc;
        uVar3 = *(undefined4 *)(iVar4 + 0x1c8);
        puVar6[6] = *(undefined4 *)(iVar4 + 0x1c4);
        puVar6[7] = uVar3;
        puVar6[8] = *(undefined4 *)(iVar4 + 0x1cc);
      }
      if ((int)*(char *)(param_1 + 0x22c) < iVar5 + 3) {
        iVar4 = param_1 + *(char *)(param_1 + 0x22c) * 0xc;
        uVar3 = *(undefined4 *)(iVar4 + 0x1c8);
        puVar6[9] = *(undefined4 *)(iVar4 + 0x1c4);
        puVar6[10] = uVar3;
        puVar6[0xb] = *(undefined4 *)(iVar4 + 0x1cc);
      }
      puVar6 = puVar6 + 0xc;
      iVar5 = iVar5 + 4;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
  }
  return;
}



// ==== 80107dfc  FUN_80107dfc ====

void FUN_80107dfc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80107e1c  FUN_80107e1c ====

void FUN_80107e1c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  
  uVar1 = 1;
  if (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) == '\x04') {
    uVar1 = 0x44;
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),uVar1);
  return;
}



// ==== 80107f9c  FUN_80107f9c ====

void FUN_80107f9c(int param_1)

{
  short sVar1;
  
  *(undefined1 *)(param_1 + 0x6e8) = 2;
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x306) {
    zz_013358c_(param_1,1);
    zz_00c74ec_(param_1,6);
  }
  else if ((sVar1 < 0x306) && (sVar1 == 0x302)) {
    zz_013358c_(param_1,0);
    zz_00c74ec_(param_1,6);
  }
  return;
}



// ==== 80108014  FUN_80108014 ====

void FUN_80108014(int param_1)

{
  zz_010a4ac_(param_1);
  return;
}



// ==== 80108034  FUN_80108034 ====

void FUN_80108034(int param_1)

{
  if (*(char *)(param_1 + 0x146) != '\0') {
    zz_00f0104_(param_1,10,3);
  }
  return;
}



// ==== 80108078  FUN_80108078 ====

void FUN_80108078(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_804344d0)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 801080e4  FUN_801080e4 ====

void FUN_801080e4(int param_1)

{
  (*(code *)(&PTR_FUN_803240f8)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80108120  FUN_80108120 ====

void FUN_80108120(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_80324108)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80108168  FUN_80108168 ====

void FUN_80108168(int param_1)

{
  zz_010b2f4_(param_1);
  return;
}



// ==== 8010818c  FUN_8010818c ====

void FUN_8010818c(int param_1)

{
  zz_010b7ac_(param_1);
  return;
}



// ==== 801081b0  FUN_801081b0 ====

void FUN_801081b0(int param_1)

{
  zz_010bd10_(param_1);
  return;
}



// ==== 801081d4  FUN_801081d4 ====

void FUN_801081d4(int param_1)

{
  zz_010c220_(param_1);
  return;
}



// ==== 801081f8  FUN_801081f8 ====

void FUN_801081f8(int param_1)

{
  zz_010c590_(param_1);
  return;
}



// ==== 8010821c  FUN_8010821c ====

void FUN_8010821c(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x306) {
    FUN_80108508(param_1);
  }
  else {
    FUN_80108250(param_1);
  }
  return;
}



// ==== 80108250  FUN_80108250 ====

void FUN_80108250(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_804344d8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80108294  FUN_80108294 ====

void FUN_80108294(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_804394e8;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 1;
  }
  zz_004beb8_((double)FLOAT_804394ec,param_1,0xf,4,(int)*(char *)(param_1 + 0x6ea),0xffffffff,
              0xffffffff);
  FUN_80108344(param_1);
  return;
}



// ==== 80108344  FUN_80108344 ====

void FUN_80108344(int param_1)

{
  char cVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_804394f0,param_1,*(short *)(param_1 + 0x5ae));
  gnt4_PSQUATScale_bl((double)FLOAT_804394f4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  iVar2 = zz_00677b0_(param_1);
  if (((iVar2 == 0) || ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0)) ||
     (-1 < *(char *)(param_1 + 0x1cef))) {
    if ('\0' < *(char *)(param_1 + 0x1cef)) {
      *(undefined1 *)(param_1 + 0x1cef) = 0;
      cVar1 = *(char *)(param_1 + 0x146);
      if (cVar1 == '\x01') {
        iVar2 = zz_006dbe0_(param_1,2,1,1);
        if (iVar2 != 0) {
          *(undefined1 *)(param_1 + 0x146) = 2;
          FUN_800061a8(param_1,0x11);
        }
      }
      else if (((cVar1 < '\x01') && (-1 < cVar1)) &&
              (iVar2 = zz_006dbe0_(param_1,2,1,1), iVar2 != 0)) {
        FUN_800a6108(param_1,0);
        FUN_800061a8(param_1,0x11);
      }
    }
    if (*(char *)(param_1 + 0x1d0f) < '\0') {
      *(undefined1 *)(param_1 + 0x1d0f) = 0;
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    }
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
        zz_006a474_(param_1);
      }
      else {
        zz_006a5a4_(param_1);
      }
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_804394f8 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80108508  FUN_80108508 ====

void FUN_80108508(int param_1)

{
  zz_010c9d8_(param_1);
  return;
}



// ==== 80108530  FUN_80108530 ====

undefined4 FUN_80108530(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = zz_006dbe0_(param_1,2,1,1);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    zz_016cc24_(param_1,0xf);
    uVar2 = 0x8444;
  }
  return uVar2;
}



// ==== 8010858c  FUN_8010858c ====

void FUN_8010858c(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  piVar2 = zz_0006dc8_(0xd4);
  *(int **)(param_1 + 0xdc) = piVar2;
  puVar3 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar3 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar3 = *(undefined4 *)(param_1 + 0x20);
    puVar3[1] = uVar1;
    puVar3[2] = *(undefined4 *)(param_1 + 0x28);
    zz_00e48cc_(param_1,-0x7fcdae50,5,puVar3 + 3,(float *)(puVar3 + 0x12));
  }
  return;
}



// ==== 80108604  FUN_80108604 ====

void FUN_80108604(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  puVar2 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar2 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar2 = *(undefined4 *)(param_1 + 0x20);
    puVar2[1] = uVar1;
    puVar2[2] = *(undefined4 *)(param_1 + 0x28);
    if ((*(uint *)(param_1 + 0x5e0) & 0x20001000) == 0) {
      FUN_800e4a18((double)FLOAT_80439500,param_1,(float *)&DAT_803251b0,5,(float *)(puVar2 + 3),
                   (float *)(puVar2 + 0x12),(float *)(puVar2 + 0x30));
    }
    else {
      FUN_800e4f9c(param_1,-0x7fcdae50,5,(float *)(puVar2 + 3),(float *)(puVar2 + 0x21));
    }
  }
  return;
}



// ==== 80108698  FUN_80108698 ====

void FUN_80108698(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}



// ==== 801086d0  FUN_801086d0 ====

void FUN_801086d0(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcdae50,5,pfVar2 + 3,afStack_18);
    zz_00e5184_(param_1,-0x7fcdae50,5,pfVar2 + 3,pfVar2 + 0x21);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}



// ==== 80108770  FUN_80108770 ====

void FUN_80108770(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  piVar2 = zz_0006dc8_(0xd4);
  *(int **)(param_1 + 0xdc) = piVar2;
  puVar3 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar3 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar3 = *(undefined4 *)(param_1 + 0x20);
    puVar3[1] = uVar1;
    puVar3[2] = *(undefined4 *)(param_1 + 0x28);
    zz_00e48cc_(param_1,-0x7fcdad60,5,puVar3 + 3,(float *)(puVar3 + 0x12));
  }
  return;
}



// ==== 801087e8  FUN_801087e8 ====

void FUN_801087e8(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  puVar2 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar2 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar2 = *(undefined4 *)(param_1 + 0x20);
    puVar2[1] = uVar1;
    puVar2[2] = *(undefined4 *)(param_1 + 0x28);
    if ((*(uint *)(param_1 + 0x5e0) & 0x20001000) == 0) {
      FUN_800e4a18((double)FLOAT_80439504,param_1,(float *)&DAT_803252a0,5,(float *)(puVar2 + 3),
                   (float *)(puVar2 + 0x12),(float *)(puVar2 + 0x30));
    }
    else {
      FUN_800e4f9c(param_1,-0x7fcdad60,5,(float *)(puVar2 + 3),(float *)(puVar2 + 0x21));
    }
  }
  return;
}



// ==== 8010887c  FUN_8010887c ====

void FUN_8010887c(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}



// ==== 801088b4  FUN_801088b4 ====

void FUN_801088b4(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcdad60,5,pfVar2 + 3,afStack_18);
    zz_00e5184_(param_1,-0x7fcdad60,5,pfVar2 + 3,pfVar2 + 0x21);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}



// ==== 80108a74  FUN_80108a74 ====

/* WARNING: Removing unreachable block (ram,0x80108d20) */
/* WARNING: Removing unreachable block (ram,0x80108a84) */

void FUN_80108a74(int param_1,short *param_2)

{
  float fVar1;
  short sVar2;
  int iVar3;
  short sVar5;
  int iVar4;
  double dVar6;
  double dVar7;
  float local_58;
  float local_54;
  undefined4 local_50;
  float local_4c;
  float local_48;
  undefined4 local_44;
  undefined4 local_40;
  uint uStack_3c;
  longlong local_38;
  undefined4 local_30;
  uint uStack_2c;
  longlong local_28;
  
  iVar3 = zz_0066580_(param_1);
  dVar6 = DOUBLE_80439510;
  fVar1 = FLOAT_80439508;
  uStack_3c = (int)*param_2 ^ 0x80000000;
  local_40 = 0x43300000;
  sVar5 = (short)iVar3 - *(short *)(param_1 + 0x72);
  local_30 = 0x43300000;
  iVar3 = (int)((float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80439510) * FLOAT_80439508);
  local_38 = (longlong)iVar3;
  *param_2 = (short)iVar3;
  uStack_2c = (int)param_2[1] ^ 0x80000000;
  iVar3 = (int)((float)((double)CONCAT44(0x43300000,uStack_2c) - dVar6) * fVar1);
  local_28 = (longlong)iVar3;
  param_2[1] = (short)iVar3;
  if ((*(byte *)(param_1 + 0x6e9) & 1) != 0) {
    sVar2 = sVar5;
    if (0x4000 < sVar5) {
      sVar2 = 0;
    }
    if (sVar2 < -0x4000) {
      sVar2 = 0;
    }
    if (0x2000 < sVar2) {
      sVar2 = 0x2000;
    }
    if (sVar2 < -0x2000) {
      sVar2 = -0x2000;
    }
    sVar2 = sVar2 - *param_2;
    if (sVar2 < 1) {
      if (sVar2 < -0x200) {
        sVar2 = -0x200;
      }
    }
    else if (0x200 < sVar2) {
      sVar2 = 0x200;
    }
    *param_2 = *param_2 + sVar2;
  }
  if ((((*(byte *)(param_1 + 0x6e9) & 0xe) != 0) && (sVar5 < 0x4000)) && (-0x4000 < sVar5)) {
    local_4c = *(float *)(param_1 + 0xb18);
    dVar6 = (double)*(float *)(param_1 + 0xb28);
    local_44 = *(undefined4 *)(param_1 + 0xb38);
    local_48 = FLOAT_8043950c;
    dVar7 = gnt4_PSVECMag_bl(&local_4c);
    iVar3 = FUN_800452a0(dVar6,dVar7);
    local_58 = *(float *)(param_1 + 0xb20);
    local_54 = *(float *)(param_1 + 0xb30);
    local_50 = *(undefined4 *)(param_1 + 0xb40);
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x50c),&local_58,&local_58);
    dVar7 = (double)local_54;
    local_54 = FLOAT_8043950c;
    dVar6 = gnt4_PSVECMag_bl(&local_58);
    iVar4 = FUN_800452a0(dVar7,dVar6);
    if ((*(byte *)(param_1 + 0x6e9) & 4) == 0) {
      if ((*(byte *)(param_1 + 0x6e9) & 8) == 0) {
        sVar5 = 0;
      }
      else {
        sVar5 = 0x1000;
      }
    }
    else {
      sVar5 = -0x1000;
    }
    sVar5 = sVar5 + ((short)iVar3 - (short)iVar4);
    if (sVar5 < 1) {
      if (sVar5 < -0x200) {
        sVar5 = -0x200;
      }
    }
    else if (0x200 < sVar5) {
      sVar5 = 0x200;
    }
    param_2[1] = param_2[1] + sVar5;
    if (0x4000 < param_2[1]) {
      param_2[1] = 0x4000;
    }
    if (param_2[1] < -0x4000) {
      param_2[1] = -0x4000;
    }
  }
  *(short *)(param_1 + 0x190a) = param_2[1] >> 2;
  *(short *)(param_1 + 0x1910) = param_2[1] >> 2;
  *(short *)(param_1 + 0x1916) = param_2[1] >> 2;
  *(short *)(param_1 + 0x191c) = param_2[1];
  *(short *)(param_1 + 0x1920) = -(*param_2 >> 1);
  *(short *)(param_1 + 0x190c) = *param_2 >> 3;
  *(short *)(param_1 + 0x1912) = *param_2 >> 3;
  *(short *)(param_1 + 0x1918) = *param_2 >> 3;
  return;
}



// ==== 80108d44  FUN_80108d44 ====

void FUN_80108d44(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x504) {
    FUN_8010858c(param_1);
  }
  else if (*(short *)(param_1 + 1000) == 0x510) {
    FUN_80108770(param_1);
  }
  return;
}



// ==== 80108d84  FUN_80108d84 ====

void FUN_80108d84(int param_1)

{
  zz_0046698_(param_1);
  FUN_80108a74(param_1,(short *)(param_1 + 0x144));
  if ('\0' < *(char *)(param_1 + 0x6f7)) {
    *(char *)(param_1 + 0x6f7) = *(char *)(param_1 + 0x6f7) + -1;
  }
  if ((*(uint *)(param_1 + 0x5e0) & 1) == 0) {
    *(short *)(param_1 + 0x1dfc) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1dfc) ^ 0x80000000) -
                             DOUBLE_80439510) * FLOAT_80439518);
  }
  if ((*(uint *)(param_1 + 0x5e0) & 3) != 0) {
    *(undefined1 *)(param_1 + 0x7de) = 1;
  }
  return;
}



// ==== 80108e28  FUN_80108e28 ====

void FUN_80108e28(int param_1)

{
  FUN_80108a74(param_1,(short *)(param_1 + 0x144));
  if (*(short *)(param_1 + 1000) == 0x504) {
    FUN_80108604(param_1);
  }
  else if (*(short *)(param_1 + 1000) == 0x510) {
    FUN_801087e8(param_1);
  }
  return;
}



// ==== 80108e94  FUN_80108e94 ====

void FUN_80108e94(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x504) {
    FUN_80108698(param_1);
  }
  else if (*(short *)(param_1 + 1000) == 0x510) {
    FUN_8010887c(param_1);
  }
  return;
}



// ==== 80108ed0  FUN_80108ed0 ====

void FUN_80108ed0(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x504) {
    FUN_801086d0(param_1);
  }
  else if (*(short *)(param_1 + 1000) == 0x510) {
    FUN_801088b4(param_1);
  }
  return;
}



// ==== 80108f0c  FUN_80108f0c ====

void FUN_80108f0c(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_804344e0)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 80108f48  FUN_80108f48 ====

void FUN_80108f48(int param_1)

{
  undefined1 uVar1;
  
  uVar1 = 0x17;
  if (*(char *)(param_1 + 0x1b44) != '\0') {
    uVar1 = 0x1a;
  }
  zz_01ef2b4_(param_1,2,uVar1);
  return;
}



// ==== 80108f80  FUN_80108f80 ====

void FUN_80108f80(int param_1)

{
  (*(code *)(&PTR_FUN_803253d0)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80108fbc  FUN_80108fbc ====

void FUN_80108fbc(int param_1)

{
  (*(code *)(&PTR_FUN_803253e0)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80108ff8  FUN_80108ff8 ====

void FUN_80108ff8(int param_1)

{
  zz_00665cc_(param_1);
  (*(code *)(&PTR_FUN_803253ec)[*(char *)(param_1 + 0x540)])(param_1);
  return;
}



// ==== 80109048  FUN_80109048 ====

void FUN_80109048(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  fVar2 = FLOAT_8043951c;
  fVar1 = FLOAT_8043950c;
  dVar3 = (double)FLOAT_80439520;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar2;
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  *(undefined2 *)(param_1 + 0x1dfc) = 0;
  zz_004beb8_(dVar3,param_1,0xf,0,0x2a,10,2);
  return;
}



// ==== 801090bc  FUN_801090bc ====

void FUN_801090bc(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  
  zz_004cd24_(param_1,0xf);
  iVar3 = FUN_8006e0ac(param_1,0x2000);
  fVar2 = FLOAT_8043950c;
  fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x560) = fVar1;
  if (((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc1), iVar4 != 0)) || (-1 < iVar3)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    if (*(short *)(param_1 + 0x1dfc) < 0) {
      *(undefined1 *)(param_1 + 0x6ec) = 1;
    }
    else {
      *(undefined1 *)(param_1 + 0x6ec) = 0;
    }
    zz_004beb8_((double)FLOAT_80439520,param_1,0xf,2,(int)*(char *)(param_1 + 0x6ec),0xffffffff,1);
  }
  return;
}



// ==== 80109190  FUN_80109190 ====

void FUN_80109190(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    iVar1 = zz_006dbe0_(param_1,0,1,1);
    if (iVar1 != 0) {
      FUN_80109710(param_1,param_1 + 0x144);
    }
  }
  FUN_801097ac(param_1,param_1 + 0x144);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 80109230  FUN_80109230 ====

void FUN_80109230(int param_1)

{
  zz_00665cc_(param_1);
  (*(code *)(&PTR_FUN_803253f8)[*(char *)(param_1 + 0x540)])(param_1);
  gnt4_PSQUATScale_bl((double)FLOAT_80439524,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  return;
}



// ==== 801092a8  FUN_801092a8 ====

void FUN_801092a8(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_8043951c;
  fVar1 = FLOAT_8043950c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar2;
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  *(undefined2 *)(param_1 + 0x1dfc) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\x0f')) {
    zz_004beb8_((double)FLOAT_80439520,param_1,0xf,0,0xf,10,2);
  }
  return;
}



// ==== 80109354  FUN_80109354 ====

void FUN_80109354(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  
  zz_004cd24_(param_1,0xf);
  iVar3 = FUN_8006e0ac(param_1,0x2000);
  fVar2 = FLOAT_8043950c;
  fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x560) = fVar1;
  if (((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0x81), iVar4 != 0)) || (-1 < iVar3)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    if (*(short *)(param_1 + 0x1dfc) < 0) {
      *(undefined1 *)(param_1 + 0x6ec) = 3;
    }
    else {
      *(undefined1 *)(param_1 + 0x6ec) = 2;
    }
    zz_004beb8_((double)FLOAT_80439520,param_1,3,2,(int)*(char *)(param_1 + 0x6ec),0xffffffff,1);
  }
  return;
}



// ==== 80109428  FUN_80109428 ====

void FUN_80109428(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    iVar1 = zz_006dbe0_(param_1,0,1,1);
    if (iVar1 != 0) {
      FUN_80109710(param_1,param_1 + 0x144);
    }
  }
  FUN_801097ac(param_1,param_1 + 0x144);
  if (*(char *)(param_1 + 0x1cf0) != '\0') {
    iVar1 = FUN_8006e0ac(param_1,0x2000);
    if (iVar1 < 0) {
      zz_006d144_(param_1,0xc1);
    }
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 801094f4  FUN_801094f4 ====

void FUN_801094f4(int param_1)

{
  zz_00665cc_(param_1);
  (*(code *)(&PTR_FUN_804344e8)[*(char *)(param_1 + 0x540)])(param_1);
  FUN_80067310((double)FLOAT_80439528,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  return;
}



// ==== 80109558  FUN_80109558 ====

void FUN_80109558(int param_1)

{
  if (*(char *)(param_1 + 0x5dd) == '\x11') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x1dfc) = 0;
    FUN_8006e0ac(param_1,0x4000);
    if (*(short *)(param_1 + 0x1dfc) < 0) {
      *(undefined1 *)(param_1 + 0x6ec) = 5;
    }
    else {
      *(undefined1 *)(param_1 + 0x6ec) = 4;
    }
    zz_004beb8_((double)FLOAT_80439520,param_1,1,2,(int)*(char *)(param_1 + 0x6ec),0xffffffff,1);
    if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\v')) {
      zz_004beb8_((double)FLOAT_80439520,param_1,6,0,0xb,10,2);
    }
  }
  else {
    zz_006a3d0_(param_1,'\0',3,0);
  }
  return;
}



// ==== 80109638  FUN_80109638 ====

void FUN_80109638(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x542) == '\0') {
    FUN_8006e0ac(param_1,0x4000);
  }
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    iVar1 = zz_006dbe0_(param_1,0,1,1);
    if (iVar1 != 0) {
      FUN_80109710(param_1,param_1 + 0x144);
    }
  }
  FUN_801097ac(param_1,param_1 + 0x144);
  zz_0066ac0_(param_1,0);
  zz_0066e40_(param_1,2);
  *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 80109710  FUN_80109710 ====

void FUN_80109710(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  undefined1 uVar5;
  
  fVar3 = FLOAT_80439534;
  fVar2 = FLOAT_80439530;
  fVar1 = FLOAT_8043952c;
  *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(float *)(param_1 + 0x55c) = fVar2;
  *(float *)(param_2 + 0x2c) = fVar3 * *(float *)(param_1 + 0x764);
  if ((*(byte *)(param_1 + 0xd0) & 4) == 0) {
    *(undefined4 *)(param_2 + 0x2c) = *(undefined4 *)(param_1 + 0x814);
  }
  uVar5 = 5;
  uVar4 = *(undefined4 *)(param_1 + 0x528);
  *(undefined4 *)(param_2 + 8) = *(undefined4 *)(param_1 + 0x524);
  *(undefined4 *)(param_2 + 0xc) = uVar4;
  *(undefined4 *)(param_2 + 0x10) = *(undefined4 *)(param_1 + 0x52c);
  if (*(short *)(param_1 + 1000) == 0x510) {
    uVar5 = 6;
  }
  zz_01deb68_(param_1,uVar5,param_2 + 0x14,param_2 + 0x20,param_1 + 0x6f7);
  return;
}



