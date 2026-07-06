// ==== 802358d8  gnt4-tolower ====

int gnt4_tolower(int __c)

{
  if (__c == -1) {
    return -1;
  }
  return (uint)(byte)(&DAT_803ab670)[__c & 0xff];
}



// ==== 802358fc  __fwrite ====

/* WARNING: Type propagation algorithm not settling */

uint __fwrite(char *param_1,uint param_2,int param_3,__FILE *param_4)

{
  bool bVar1;
  bool bVar2;
  ushort uVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  char *local_28 [3];
  
  iVar4 = fwide(param_4,0);
  if (iVar4 == 0) {
    fwide(param_4,-1);
  }
  pcVar7 = (char *)(param_2 * param_3);
  if (((pcVar7 == (char *)0x0) || (*(char *)((int)&param_4->_IO_read_end + 2) != '\0')) ||
     (uVar3 = *(ushort *)&param_4->_IO_read_ptr >> 6 & 7, uVar3 == 0)) {
    return 0;
  }
  if (uVar3 == 2) {
    __sinit_AILoader_cpp();
  }
  bVar2 = true;
  bVar1 = false;
  if (((*(byte *)((int)&param_4->_IO_read_ptr + 1) >> 3 & 1) == 0) ||
     ((*(byte *)&param_4->_IO_read_ptr >> 1 & 3) == 2)) {
    bVar1 = true;
  }
  if ((!bVar1) && ((*(byte *)&param_4->_IO_read_ptr >> 1 & 3) != 1)) {
    bVar2 = false;
  }
  if ((*(byte *)&param_4->_IO_read_end >> 5 == 0) &&
     ((*(byte *)&param_4->_IO_read_ptr >> 3 & 2) != 0)) {
    if (((*(byte *)&param_4->_IO_read_ptr >> 3 & 4) != 0) &&
       (iVar4 = fseek(param_4,0,2), iVar4 != 0)) {
      return 0;
    }
    *(byte *)&param_4->_IO_read_end = *(byte *)&param_4->_IO_read_end & 0x1f | 0x20;
    zz_0235898_((int)param_4);
  }
  if (*(byte *)&param_4->_IO_read_end >> 5 != 1) {
    *(undefined1 *)((int)&param_4->_IO_read_end + 2) = 1;
    param_4->_IO_backup_base = (char *)0x0;
    return 0;
  }
  pcVar6 = (char *)0x0;
  if (pcVar7 != (char *)0x0) {
    if ((param_4->_IO_save_base != param_4->_IO_buf_base) || (bVar2)) {
      param_4->_IO_backup_base =
           param_4->_IO_buf_end + -((int)param_4->_IO_save_base - (int)param_4->_IO_buf_base);
      while( true ) {
        pcVar5 = (char *)0x0;
        local_28[0] = param_4->_IO_backup_base;
        if (pcVar7 < param_4->_IO_backup_base) {
          local_28[0] = pcVar7;
        }
        if ((((*(byte *)&param_4->_IO_read_ptr >> 1 & 3) == 1) && (local_28[0] != (char *)0x0)) &&
           (pcVar5 = __memrchr((int)param_1,'\n',(int)local_28[0]), pcVar5 != (char *)0x0)) {
          local_28[0] = pcVar5 + (1 - (int)param_1);
        }
        if (local_28[0] != (char *)0x0) {
          gnt4_memcpy(param_4->_IO_save_base,param_1,(size_t)local_28[0]);
          param_1 = param_1 + (int)local_28[0];
          pcVar6 = pcVar6 + (int)local_28[0];
          pcVar7 = pcVar7 + -(int)local_28[0];
          param_4->_IO_save_base = param_4->_IO_save_base + (int)local_28[0];
          param_4->_IO_backup_base = param_4->_IO_backup_base + -(int)local_28[0];
        }
        if ((((param_4->_IO_backup_base == (char *)0x0) || (pcVar5 != (char *)0x0)) ||
            ((*(byte *)&param_4->_IO_read_ptr >> 1 & 3) == 0)) &&
           (iVar4 = __flush_buffer(&param_4->_flags,(undefined4 *)0x0), iVar4 != 0)) break;
        if ((pcVar7 == (char *)0x0) || (!bVar2)) goto LAB_80235b64;
      }
      *(undefined1 *)((int)&param_4->_IO_read_end + 2) = 1;
      pcVar7 = (char *)0x0;
      param_4->_IO_backup_base = (char *)0x0;
    }
  }
LAB_80235b64:
  if ((pcVar7 != (char *)0x0) && (!bVar2)) {
    pcVar5 = param_4->_IO_buf_base;
    pcVar8 = param_4->_IO_buf_end;
    param_4->_IO_buf_base = param_1;
    param_4->_IO_buf_end = pcVar7;
    param_4->_IO_save_base = param_1 + (int)pcVar7;
    iVar4 = __flush_buffer(&param_4->_flags,local_28);
    if (iVar4 != 0) {
      *(undefined1 *)((int)&param_4->_IO_read_end + 2) = 1;
      param_4->_IO_backup_base = (char *)0x0;
    }
    param_4->_IO_buf_base = pcVar5;
    pcVar6 = pcVar6 + (int)local_28[0];
    param_4->_IO_buf_end = pcVar8;
    zz_0235898_((int)param_4);
    param_4->_IO_backup_base = (char *)0x0;
  }
  if ((*(byte *)&param_4->_IO_read_ptr >> 1 & 3) != 2) {
    param_4->_IO_backup_base = (char *)0x0;
  }
  return (uint)(pcVar6 + (param_2 - 1)) / param_2;
}



// ==== 80235c08  fwrite ====

size_t fwrite(void *__ptr,size_t __size,size_t __n,FILE *__s)

{
  uint uVar1;
  
  zz_02358d0_();
  uVar1 = __fwrite(__ptr,__size,__n,__s);
  zz_02358cc_();
  return uVar1;
}



// ==== 80235c84  fflush ====

int fflush(FILE *__stream)

{
  int iVar1;
  char *pcVar2;
  
  if (__stream == (FILE *)0x0) {
    iVar1 = __flush_all();
  }
  else if ((*(char *)((int)&__stream->_IO_read_end + 2) == '\0') &&
          ((*(ushort *)&__stream->_IO_read_ptr >> 6 & 7) != 0)) {
    if ((*(byte *)&__stream->_IO_read_ptr >> 3 & 7) == 1) {
      iVar1 = 0;
    }
    else {
      if (2 < *(byte *)&__stream->_IO_read_end >> 5) {
        *(byte *)&__stream->_IO_read_end = *(byte *)&__stream->_IO_read_end & 0x1f | 0x40;
      }
      if (*(byte *)&__stream->_IO_read_end >> 5 == 2) {
        __stream->_IO_backup_base = (char *)0x0;
      }
      if (*(byte *)&__stream->_IO_read_end >> 5 == 1) {
        if ((*(ushort *)&__stream->_IO_read_ptr >> 6 & 7) == 1) {
          pcVar2 = (char *)zz_0236220_((int)__stream);
        }
        else {
          pcVar2 = (char *)0x0;
        }
        iVar1 = __flush_buffer(&__stream->_flags,(undefined4 *)0x0);
        if (iVar1 == 0) {
          iVar1 = 0;
          *(byte *)&__stream->_IO_read_end = *(byte *)&__stream->_IO_read_end & 0x1f;
          __stream->_IO_write_end = pcVar2;
          __stream->_IO_backup_base = (char *)0x0;
        }
        else {
          *(undefined1 *)((int)&__stream->_IO_read_end + 2) = 1;
          iVar1 = -1;
          __stream->_IO_backup_base = (char *)0x0;
        }
      }
      else {
        iVar1 = 0;
        *(byte *)&__stream->_IO_read_end = *(byte *)&__stream->_IO_read_end & 0x1f;
      }
    }
  }
  else {
    iVar1 = -1;
  }
  return iVar1;
}



// ==== 80235dbc  fclose ====

int fclose(FILE *__stream)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  
  if (__stream == (FILE *)0x0) {
    iVar2 = -1;
  }
  else {
    uVar1 = *(ushort *)&__stream->_IO_read_ptr >> 6 & 7;
    if (uVar1 == 0) {
      iVar2 = 0;
    }
    else {
      if (__stream == (FILE *)0x0) {
        iVar2 = __flush_all();
      }
      else if ((*(char *)((int)&__stream->_IO_read_end + 2) == '\0') && (uVar1 != 0)) {
        if ((*(byte *)&__stream->_IO_read_ptr >> 3 & 7) == 1) {
          iVar2 = 0;
        }
        else {
          if (2 < *(byte *)&__stream->_IO_read_end >> 5) {
            *(byte *)&__stream->_IO_read_end = *(byte *)&__stream->_IO_read_end & 0x1f | 0x40;
          }
          if (*(byte *)&__stream->_IO_read_end >> 5 == 2) {
            __stream->_IO_backup_base = (char *)0x0;
          }
          if (*(byte *)&__stream->_IO_read_end >> 5 == 1) {
            if ((*(ushort *)&__stream->_IO_read_ptr >> 6 & 7) == 1) {
              pcVar5 = (char *)zz_0236220_((int)__stream);
            }
            else {
              pcVar5 = (char *)0x0;
            }
            iVar2 = __flush_buffer(&__stream->_flags,(undefined4 *)0x0);
            if (iVar2 == 0) {
              iVar2 = 0;
              *(byte *)&__stream->_IO_read_end = *(byte *)&__stream->_IO_read_end & 0x1f;
              __stream->_IO_write_end = pcVar5;
              __stream->_IO_backup_base = (char *)0x0;
            }
            else {
              *(undefined1 *)((int)&__stream->_IO_read_end + 2) = 1;
              iVar2 = -1;
              __stream->_IO_backup_base = (char *)0x0;
            }
          }
          else {
            iVar2 = 0;
            *(byte *)&__stream->_IO_read_end = *(byte *)&__stream->_IO_read_end & 0x1f;
          }
        }
      }
      else {
        iVar2 = -1;
      }
      iVar3 = (**(code **)&__stream->_cur_column)(__stream->_flags);
      *(ushort *)&__stream->_IO_read_ptr = *(ushort *)&__stream->_IO_read_ptr & 0xfe3f;
      __stream->_flags = 0;
      if ((*(byte *)&__stream->_IO_read_end >> 4 & 1) != 0) {
        free(__stream->_IO_buf_base);
      }
      uVar4 = 0;
      if ((iVar2 != 0) || (iVar3 != 0)) {
        uVar4 = 1;
      }
      iVar2 = (int)(-uVar4 | uVar4) >> 0x1f;
    }
  }
  return iVar2;
}



// ==== 80235f78  fseek ====

int fseek(FILE *__stream,long __off,int __whence)

{
  int iVar1;
  
  zz_02358d0_();
  iVar1 = zz_0235fe4_(&__stream->_flags,__off,__whence);
  zz_02358cc_();
  return iVar1;
}



// ==== 80235fe4  zz_0235fe4_ ====

undefined4 zz_0235fe4_(undefined4 *param_1,uint param_2,int param_3)

{
  uint uVar1;
  ushort uVar2;
  int iVar3;
  uint local_18 [4];
  
  if (((*(ushort *)(param_1 + 1) >> 6 & 7) != 1) || (*(char *)((int)param_1 + 10) != '\0')) {
    DAT_80436878 = 0x28;
    return 0xffffffff;
  }
  local_18[0] = param_2;
  if ((*(byte *)(param_1 + 2) >> 5 == 1) &&
     (iVar3 = __flush_buffer(param_1,(undefined4 *)0x0), iVar3 != 0)) {
    *(undefined1 *)((int)param_1 + 10) = 1;
    param_1[10] = 0;
    DAT_80436878 = 0x28;
    return 0xffffffff;
  }
  if (param_3 == 1) {
    param_3 = 0;
    uVar2 = *(ushort *)(param_1 + 1) >> 6 & 7;
    if (((uVar2 == 1) || (uVar2 == 2)) && (*(char *)((int)param_1 + 10) == '\0')) {
      uVar1 = (uint)(*(byte *)(param_1 + 2) >> 5);
      if (uVar1 == 0) {
        iVar3 = param_1[6];
      }
      else {
        iVar3 = param_1[0xd] + (param_1[9] - param_1[7]);
        if (2 < uVar1) {
          iVar3 = iVar3 - (uVar1 - 2);
        }
      }
    }
    else {
      iVar3 = -1;
      DAT_80436878 = 0x28;
    }
    local_18[0] = local_18[0] + iVar3;
  }
  if (((param_3 == 2) || ((*(byte *)(param_1 + 1) >> 3 & 7) == 3)) ||
     ((*(byte *)(param_1 + 2) >> 5 != 2 && (*(byte *)(param_1 + 2) >> 5 != 3)))) {
    *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) & 0x1f;
  }
  else if ((local_18[0] < (uint)param_1[6]) && ((uint)param_1[0xd] <= local_18[0])) {
    param_1[9] = param_1[7] + (local_18[0] - param_1[0xd]);
    param_1[10] = param_1[6] - local_18[0];
    *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) & 0x1f | 0x40;
  }
  else {
    *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) & 0x1f;
  }
  if (*(byte *)(param_1 + 2) >> 5 == 0) {
    if (((code *)param_1[0xe] != (code *)0x0) &&
       (iVar3 = (*(code *)param_1[0xe])(*param_1,local_18,param_3,param_1[0x12]), iVar3 != 0)) {
      *(undefined1 *)((int)param_1 + 10) = 1;
      param_1[10] = 0;
      DAT_80436878 = 0x28;
      return 0xffffffff;
    }
    *(undefined1 *)((int)param_1 + 9) = 0;
    param_1[6] = local_18[0];
    param_1[10] = 0;
  }
  return 0;
}



// ==== 80236220  zz_0236220_ ====

int zz_0236220_(int param_1)

{
  uint uVar1;
  ushort uVar2;
  int iVar3;
  
  zz_02358d0_();
  uVar2 = *(ushort *)(param_1 + 4) >> 6 & 7;
  if ((uVar2 == 1) || (uVar2 == 2)) {
    if (*(char *)(param_1 + 10) == '\0') {
      uVar1 = (uint)(*(byte *)(param_1 + 8) >> 5);
      if (uVar1 == 0) {
        iVar3 = *(int *)(param_1 + 0x18);
      }
      else {
        iVar3 = *(int *)(param_1 + 0x34) + (*(int *)(param_1 + 0x24) - *(int *)(param_1 + 0x1c));
        if (2 < uVar1) {
          iVar3 = iVar3 - (uVar1 - 2);
        }
      }
      goto LAB_802362a8;
    }
  }
  iVar3 = -1;
  DAT_80436878 = 0x28;
LAB_802362a8:
  zz_02358cc_();
  return iVar3;
}



// ==== 802362c8  wcstombs ====

size_t wcstombs(char *__s,wchar_t *__pwcs,size_t __n)

{
  wchar_t wVar1;
  byte bVar2;
  byte *pbVar3;
  uint uVar4;
  uint uVar5;
  size_t sVar6;
  undefined4 local_28;
  byte local_24 [16];
  
  sVar6 = 0;
  if ((__s == (char *)0x0) || (__pwcs == (wchar_t *)0x0)) {
    sVar6 = 0;
  }
  else {
    for (; sVar6 <= __n; sVar6 = sVar6 + uVar5) {
      wVar1 = *__pwcs;
      uVar4 = (uint)(ushort)wVar1;
      if (uVar4 == 0) {
        __s[sVar6] = '\0';
        return sVar6;
      }
      __pwcs = __pwcs + 1;
      local_28 = DAT_8043cc40;
      if (uVar4 < 0x80) {
        uVar5 = 1;
      }
      else if (uVar4 < 0x800) {
        uVar5 = 2;
      }
      else {
        uVar5 = 3;
      }
      pbVar3 = local_24 + uVar5;
      if (uVar5 == 2) {
LAB_80236380:
        bVar2 = (byte)uVar4;
        uVar4 = uVar4 >> 6;
        pbVar3 = pbVar3 + -1;
        *pbVar3 = bVar2 & 0x3f | 0x80;
LAB_80236390:
        pbVar3[-1] = (byte)uVar4 | local_24[uVar5 - 4];
      }
      else if (uVar5 < 2) {
        if (uVar5 != 0) goto LAB_80236390;
      }
      else if (uVar5 < 4) {
        uVar4 = (uint)((ushort)wVar1 >> 6);
        pbVar3 = local_24 + (uVar5 - 1);
        *pbVar3 = (byte)wVar1 & 0x3f | 0x80;
        goto LAB_80236380;
      }
      if (__n < sVar6 + uVar5) {
        return sVar6;
      }
      zz_0238cbc_((int)(__s + sVar6),(int)local_24,uVar5);
    }
  }
  return sVar6;
}



// ==== 802363e0  gnt4-memcmp ====

int gnt4_memcmp(void *__s1,void *__s2,size_t __n)

{
  int iVar1;
  byte *pbVar2;
  byte *pbVar3;
  
  pbVar2 = (byte *)((int)__s1 + -1);
  pbVar3 = (byte *)((int)__s2 + -1);
  iVar1 = __n + 1;
  do {
    iVar1 = iVar1 + -1;
    if (iVar1 == 0) {
      return 0;
    }
    pbVar2 = pbVar2 + 1;
    pbVar3 = pbVar3 + 1;
  } while (*pbVar2 == *pbVar3);
  if (*pbVar3 <= *pbVar2) {
    return 1;
  }
  return -1;
}



// ==== 8023642c  __memrchr ====

char * __memrchr(int param_1,char param_2,int param_3)

{
  char *pcVar1;
  int iVar2;
  
  pcVar1 = (char *)(param_1 + param_3);
  iVar2 = param_3 + 1;
  do {
    iVar2 = iVar2 + -1;
    if (iVar2 == 0) {
      return (char *)0x0;
    }
    pcVar1 = pcVar1 + -1;
  } while (*pcVar1 != param_2);
  return pcVar1;
}



// ==== 80236458  zz_0236458_ ====

char * zz_0236458_(int param_1,char param_2,int param_3)

{
  char *pcVar1;
  int iVar2;
  
  pcVar1 = (char *)(param_1 + -1);
  iVar2 = param_3 + 1;
  do {
    iVar2 = iVar2 + -1;
    if (iVar2 == 0) {
      return (char *)0x0;
    }
    pcVar1 = pcVar1 + 1;
  } while (*pcVar1 != param_2);
  return pcVar1;
}



// ==== 80236484  gnt4-memmove-bl ====

uint gnt4_memmove_bl(uint param_1,uint param_2,uint param_3)

{
  int iVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  
  iVar1 = countLeadingZeros(param_1 ^ param_2);
  iVar1 = param_1 << iVar1;
  if (param_3 < 0x20) {
    if (iVar1 < 0) {
      puVar2 = (undefined1 *)(param_2 + param_3);
      puVar3 = (undefined1 *)(param_1 + param_3);
      iVar1 = param_3 + 1;
      while (iVar1 = iVar1 + -1, iVar1 != 0) {
        puVar2 = puVar2 + -1;
        puVar3 = puVar3 + -1;
        *puVar3 = *puVar2;
      }
    }
    else {
      puVar2 = (undefined1 *)(param_2 - 1);
      puVar3 = (undefined1 *)(param_1 - 1);
      iVar1 = param_3 + 1;
      while (iVar1 = iVar1 + -1, iVar1 != 0) {
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
        *puVar3 = *puVar2;
      }
    }
  }
  else if (((param_1 ^ param_2) & 3) == 0) {
    if (iVar1 < 0) {
      gnt4___copy_longs_rev_aligned(param_1,param_2,param_3);
    }
    else {
      gnt4___copy_longs_aligned(param_1,param_2,param_3);
    }
  }
  else if (iVar1 < 0) {
    gnt4___copy_longs_rev_unaligned(param_1,param_2,param_3);
  }
  else {
    gnt4___copy_longs_unaligned(param_1,param_2,param_3);
  }
  return param_1;
}



// ==== 80236550  gnt4-__copy_longs_rev_unaligned ====

void gnt4___copy_longs_rev_unaligned(int param_1,int param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined1 *puVar6;
  uint *puVar7;
  uint *puVar8;
  uint *puVar9;
  uint *puVar10;
  
  puVar9 = (uint *)(param_1 + param_3);
  puVar6 = (undefined1 *)(param_2 + param_3);
  uVar2 = (uint)puVar9 & 3;
  if (uVar2 != 0) {
    param_3 = param_3 - uVar2;
    do {
      puVar6 = puVar6 + -1;
      uVar2 = uVar2 - 1;
      puVar9 = (uint *)((int)puVar9 + -1);
      *(undefined1 *)puVar9 = *puVar6;
    } while (uVar2 != 0);
  }
  iVar4 = ((uint)puVar6 & 3) * 8;
  iVar5 = ((uint)puVar6 & 3) * -8 + 0x20;
  uVar2 = param_3 >> 3;
  uVar3 = *(uint *)(puVar6 + -((uint)puVar6 & 3));
  puVar8 = (uint *)(puVar6 + -((uint)puVar6 & 3));
  do {
    puVar10 = puVar9;
    puVar7 = puVar8;
    uVar1 = puVar7[-1];
    uVar2 = uVar2 - 1;
    puVar10[-1] = uVar1 << iVar4 | uVar3 >> iVar5;
    puVar8 = puVar7 + -2;
    uVar3 = *puVar8;
    puVar9 = puVar10 + -2;
    *puVar9 = uVar3 << iVar4 | uVar1 >> iVar5;
  } while (uVar2 != 0);
  if ((param_3 & 4) != 0) {
    puVar8 = puVar7 + -3;
    puVar9 = puVar10 + -3;
    *puVar9 = *puVar8 << iVar4 | uVar3 >> iVar5;
  }
  uVar2 = param_3 & 3;
  if (uVar2 == 0) {
    return;
  }
  puVar6 = (undefined1 *)((int)puVar8 + ((uint)puVar6 & 3));
  do {
    puVar6 = puVar6 + -1;
    uVar2 = uVar2 - 1;
    puVar9 = (uint *)((int)puVar9 + -1);
    *(undefined1 *)puVar9 = *puVar6;
  } while (uVar2 != 0);
  return;
}



// ==== 802365fc  gnt4-__copy_longs_unaligned ====

void gnt4___copy_longs_unaligned(int param_1,int param_2,uint param_3)

{
  uint uVar1;
  undefined1 *puVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  uint *puVar7;
  undefined1 *puVar8;
  uint *puVar9;
  uint *puVar10;
  uint uVar11;
  int iVar12;
  
  puVar8 = (undefined1 *)(param_2 + -1);
  uVar5 = -param_1 & 3;
  puVar2 = (undefined1 *)(param_1 + -1);
  if (uVar5 != 0) {
    param_3 = param_3 - uVar5;
    do {
      puVar8 = puVar8 + 1;
      uVar5 = uVar5 - 1;
      puVar2 = puVar2 + 1;
      *puVar2 = *puVar8;
    } while (uVar5 != 0);
  }
  uVar1 = (uint)(puVar8 + 1) & 3;
  uVar5 = param_3 >> 3;
  uVar11 = (int)(puVar8 + 1) * 8 & 0x18;
  uVar4 = *(uint *)(puVar8 + (1 - uVar1));
  iVar12 = 0x20 - uVar11;
  puVar7 = (uint *)(puVar2 + -3);
  puVar10 = (uint *)(puVar8 + (1 - uVar1));
  do {
    puVar9 = puVar10;
    puVar6 = puVar7;
    uVar3 = puVar9[1];
    uVar5 = uVar5 - 1;
    puVar6[1] = uVar4 << uVar11 | uVar3 >> iVar12;
    puVar10 = puVar9 + 2;
    uVar4 = *puVar10;
    puVar7 = puVar6 + 2;
    *puVar7 = uVar3 << uVar11 | uVar4 >> iVar12;
  } while (uVar5 != 0);
  if ((param_3 & 4) != 0) {
    puVar10 = puVar9 + 3;
    puVar7 = puVar6 + 3;
    *puVar7 = uVar4 << uVar11 | *puVar10 >> iVar12;
  }
  uVar5 = param_3 & 3;
  puVar8 = (undefined1 *)((int)puVar7 + 3);
  if (uVar5 == 0) {
    return;
  }
  puVar2 = (undefined1 *)((int)puVar10 + (3 - (4 - uVar1)));
  do {
    puVar2 = puVar2 + 1;
    uVar5 = uVar5 - 1;
    puVar8 = puVar8 + 1;
    *puVar8 = *puVar2;
  } while (uVar5 != 0);
  return;
}



// ==== 802366bc  gnt4-__copy_longs_rev_aligned ====

void gnt4___copy_longs_rev_aligned(int param_1,int param_2,uint param_3)

{
  undefined4 uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  puVar5 = (undefined4 *)(param_1 + param_3);
  puVar4 = (undefined4 *)(param_2 + param_3);
  uVar2 = (uint)puVar5 & 3;
  if (uVar2 != 0) {
    param_3 = param_3 - uVar2;
    do {
      puVar4 = (undefined4 *)((int)puVar4 + -1);
      uVar2 = uVar2 - 1;
      puVar5 = (undefined4 *)((int)puVar5 + -1);
      *(undefined1 *)puVar5 = *(undefined1 *)puVar4;
    } while (uVar2 != 0);
  }
  for (uVar2 = param_3 >> 5; uVar2 != 0; uVar2 = uVar2 - 1) {
    uVar1 = puVar4[-2];
    puVar5[-1] = puVar4[-1];
    uVar3 = puVar4[-3];
    puVar5[-2] = uVar1;
    uVar1 = puVar4[-4];
    puVar5[-3] = uVar3;
    uVar3 = puVar4[-5];
    puVar5[-4] = uVar1;
    uVar1 = puVar4[-6];
    puVar5[-5] = uVar3;
    uVar3 = puVar4[-7];
    puVar5[-6] = uVar1;
    puVar4 = puVar4 + -8;
    uVar1 = *puVar4;
    puVar5[-7] = uVar3;
    puVar5 = puVar5 + -8;
    *puVar5 = uVar1;
  }
  for (uVar2 = param_3 >> 2 & 7; uVar2 != 0; uVar2 = uVar2 - 1) {
    puVar4 = puVar4 + -1;
    puVar5 = puVar5 + -1;
    *puVar5 = *puVar4;
  }
  uVar2 = param_3 & 3;
  if (uVar2 != 0) {
    do {
      puVar4 = (undefined4 *)((int)puVar4 + -1);
      uVar2 = uVar2 - 1;
      puVar5 = (undefined4 *)((int)puVar5 + -1);
      *(undefined1 *)puVar5 = *(undefined1 *)puVar4;
    } while (uVar2 != 0);
    return;
  }
  return;
}



// ==== 80236764  gnt4-__copy_longs_aligned ====

void gnt4___copy_longs_aligned(int param_1,int param_2,uint param_3)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined4 *puVar7;
  
  puVar4 = (undefined1 *)(param_2 + -1);
  uVar6 = -param_1 & 3;
  puVar2 = (undefined1 *)(param_1 + -1);
  if (uVar6 != 0) {
    param_3 = param_3 - uVar6;
    do {
      puVar4 = puVar4 + 1;
      uVar6 = uVar6 - 1;
      puVar2 = puVar2 + 1;
      *puVar2 = *puVar4;
    } while (uVar6 != 0);
  }
  puVar7 = (undefined4 *)(puVar4 + -3);
  puVar5 = (undefined4 *)(puVar2 + -3);
  for (uVar6 = param_3 >> 5; uVar6 != 0; uVar6 = uVar6 - 1) {
    uVar1 = puVar7[2];
    puVar5[1] = puVar7[1];
    uVar3 = puVar7[3];
    puVar5[2] = uVar1;
    uVar1 = puVar7[4];
    puVar5[3] = uVar3;
    uVar3 = puVar7[5];
    puVar5[4] = uVar1;
    uVar1 = puVar7[6];
    puVar5[5] = uVar3;
    uVar3 = puVar7[7];
    puVar5[6] = uVar1;
    puVar7 = puVar7 + 8;
    uVar1 = *puVar7;
    puVar5[7] = uVar3;
    puVar5 = puVar5 + 8;
    *puVar5 = uVar1;
  }
  for (uVar6 = param_3 >> 2 & 7; uVar6 != 0; uVar6 = uVar6 - 1) {
    puVar7 = puVar7 + 1;
    puVar5 = puVar5 + 1;
    *puVar5 = *puVar7;
  }
  uVar6 = param_3 & 3;
  puVar4 = (undefined1 *)((int)puVar7 + 3);
  puVar2 = (undefined1 *)((int)puVar5 + 3);
  if (uVar6 != 0) {
    do {
      puVar4 = puVar4 + 1;
      uVar6 = uVar6 - 1;
      puVar2 = puVar2 + 1;
      *puVar2 = *puVar4;
    } while (uVar6 != 0);
    return;
  }
  return;
}



// ==== 80236820  __sinit_AILoader_cpp ====

void __sinit_AILoader_cpp(void)

{
  DAT_80436868 = FUN_802337d8;
  return;
}



// ==== 80236830  sprintf ====

int sprintf(char *__s,char *__format,...)

{
  int iVar1;
  int iVar2;
  undefined4 in_r5;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  byte in_cr1;
  undefined8 in_f1;
  undefined8 in_f2;
  undefined8 in_f3;
  undefined8 in_f4;
  undefined8 in_f5;
  undefined8 in_f6;
  undefined8 in_f7;
  undefined8 in_f8;
  char *local_98;
  char *local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined8 local_78;
  undefined8 local_70;
  undefined8 local_68;
  undefined8 local_60;
  undefined8 local_58;
  undefined8 local_50;
  undefined8 local_48;
  undefined8 local_40;
  char *local_38;
  undefined4 local_34;
  undefined4 local_30;
  char local_2c [4];
  undefined1 *local_28;
  char **local_24;
  
  if ((bool)(in_cr1 >> 1 & 1)) {
    local_78 = in_f1;
    local_70 = in_f2;
    local_68 = in_f3;
    local_60 = in_f4;
    local_58 = in_f5;
    local_50 = in_f6;
    local_48 = in_f7;
    local_40 = in_f8;
  }
  local_28 = &stack0x00000008;
  local_24 = &local_98;
  local_2c[0] = '\x02';
  local_2c[1] = '\0';
  local_2c[2] = '\0';
  local_2c[3] = '\0';
  local_34 = 0xffffffff;
  local_30 = 0;
  local_98 = __s;
  local_94 = __format;
  local_90 = in_r5;
  local_8c = in_r6;
  local_88 = in_r7;
  local_84 = in_r8;
  local_80 = in_r9;
  local_7c = in_r10;
  local_38 = __s;
  iVar1 = __pformatter(zz_0236a20_,&local_38,__format,local_2c);
  if (__s != (char *)0x0) {
    iVar2 = -2;
    if (iVar1 != -1) {
      iVar2 = iVar1;
    }
    __s[iVar2] = '\0';
  }
  return iVar1;
}



// ==== 80236910  zz_0236910_ ====

void zz_0236910_(int param_1,char *param_2,char *param_3)

{
  int iVar1;
  int iVar2;
  int local_18 [5];
  
  local_18[1] = 0xffffffff;
  local_18[2] = 0;
  local_18[0] = param_1;
  iVar1 = __pformatter(zz_0236a20_,local_18,param_2,param_3);
  if (param_1 != 0) {
    iVar2 = -2;
    if (iVar1 != -1) {
      iVar2 = iVar1;
    }
    *(undefined1 *)(param_1 + iVar2) = 0;
  }
  return;
}



// ==== 80236988  gnt4-vprintf ====

int gnt4_vprintf(char *__format,__gnuc_va_list __arg)

{
  int iVar1;
  
  iVar1 = fwide((__FILE *)&DAT_803ab358,-1);
  if (iVar1 < 0) {
    zz_02358d0_();
    iVar1 = __pformatter(FUN_80236a8c,&DAT_803ab358,__format,__arg);
    zz_02358cc_();
  }
  else {
    iVar1 = -1;
  }
  return iVar1;
}



// ==== 80236a20  zz_0236a20_ ====

undefined4 zz_0236a20_(int *param_1,void *param_2,size_t param_3)

{
  int iVar1;
  size_t __n;
  
  iVar1 = param_1[2];
  __n = param_1[1] - iVar1;
  if (iVar1 + param_3 <= (uint)param_1[1]) {
    __n = param_3;
  }
  gnt4_memcpy((void *)(*param_1 + iVar1),param_2,__n);
  param_1[2] = param_1[2] + __n;
  return 1;
}



// ==== 80236a8c  FUN_80236a8c ====

FILE * FUN_80236a8c(FILE *param_1,void *param_2,size_t param_3)

{
  size_t sVar1;
  
  sVar1 = fwrite(param_2,1,param_3,param_1);
  if (param_3 != sVar1) {
    param_1 = (FILE *)0x0;
  }
  return param_1;
}



// ==== 80236ae4  __pformatter ====

/* WARNING: Type propagation algorithm not settling */

int __pformatter(undefined *param_1,undefined4 param_2,char *param_3,char *param_4)

{
  byte bVar1;
  char *pcVar2;
  size_t sVar3;
  int iVar4;
  uint *puVar5;
  double *pdVar6;
  char *pcVar7;
  int *piVar8;
  wchar_t *__pwcs;
  byte *__s;
  uint unaff_r22;
  uint unaff_r23;
  char *pcVar9;
  char *pcVar10;
  int iVar11;
  uint unaff_r28;
  double dVar12;
  undefined1 local_2b8;
  char local_2b7 [3];
  uint local_2b4;
  undefined4 local_2b0;
  int local_2ac;
  char *local_2a8;
  uint local_2a4;
  undefined4 local_2a0;
  int local_29c;
  char *local_298;
  uint local_294;
  undefined4 local_290;
  int local_28c;
  char *local_288;
  uint local_284;
  undefined4 local_280;
  int local_27c;
  char *local_278;
  uint local_274;
  undefined4 local_270;
  int local_26c;
  char *local_268;
  uint local_264;
  undefined4 local_260;
  int local_25c;
  char *local_258;
  undefined4 local_254;
  undefined4 local_250;
  int local_24c;
  char *local_248;
  byte local_244 [511];
  char acStack_45 [17];
  
  pcVar9 = acStack_45 + 1;
  iVar11 = 0;
  local_2b7[0] = ' ';
LAB_80237234:
  if (*param_3 == '\0') {
    return iVar11;
  }
  pcVar2 = zz_0238aac_((int)param_3,'%');
  if (pcVar2 == (char *)0x0) {
    sVar3 = strlen(param_3);
    if (sVar3 == 0) {
      return iVar11 + sVar3;
    }
    iVar4 = (*(code *)param_1)(param_2,param_3);
    if (iVar4 != 0) {
      return iVar11 + sVar3;
    }
    return -1;
  }
  iVar11 = iVar11 + ((int)pcVar2 - (int)param_3);
  if (((int)pcVar2 - (int)param_3 != 0) && (iVar4 = (*(code *)param_1)(param_2,param_3), iVar4 == 0)
     ) {
    return -1;
  }
  param_3 = parse_format((int)pcVar2,param_4,&local_254);
  if (local_250._1_1_ == 0x68) goto LAB_802370b4;
  if (local_250._1_1_ < 0x68) {
    if (local_250._1_1_ == 0x58) goto LAB_80236d70;
    if (local_250._1_1_ < 0x58) {
      if (local_250._1_1_ == 0x41) {
LAB_80236ed8:
        if (local_250._0_1_ == '\x05') {
          pdVar6 = (double *)__va_arg(param_4,3);
          dVar12 = *pdVar6;
        }
        else {
          pdVar6 = (double *)__va_arg(param_4,3);
          dVar12 = *pdVar6;
        }
        local_2b4 = local_254;
        local_2b0 = local_250;
        local_2ac = local_24c;
        local_2a8 = local_248;
        __s = (byte *)double2hex(dVar12,(int)pcVar9,(int)&local_2b4);
        if (__s == (byte *)0x0) goto LAB_802370b4;
        pcVar2 = acStack_45 + -(int)__s;
      }
      else {
        if (0x40 < local_250._1_1_) {
          if ((0x47 < local_250._1_1_) || (local_250._1_1_ < 0x45)) goto LAB_802370b4;
          goto LAB_80236e6c;
        }
        if (local_250._1_1_ != 0x25) goto LAB_802370b4;
        __s = local_244;
        local_244[0] = 0x25;
        pcVar2 = (char *)0x1;
      }
    }
    else if (local_250._1_1_ == 99) {
      __s = local_244;
      piVar8 = __va_arg(param_4,1);
      local_244[0] = (byte)*piVar8;
      pcVar2 = (char *)0x1;
    }
    else {
      if (local_250._1_1_ < 99) {
        if (local_250._1_1_ != 0x61) goto LAB_802370b4;
        goto LAB_80236ed8;
      }
      if (local_250._1_1_ < 0x65) goto LAB_80236c74;
LAB_80236e6c:
      if (local_250._0_1_ == '\x05') {
        pdVar6 = (double *)__va_arg(param_4,3);
        dVar12 = *pdVar6;
      }
      else {
        pdVar6 = (double *)__va_arg(param_4,3);
        dVar12 = *pdVar6;
      }
      local_2a4 = local_254;
      local_2a0 = local_250;
      local_29c = local_24c;
      local_298 = local_248;
      __s = float2str(dVar12,(int)pcVar9,(int)&local_2a4);
      if (__s == (byte *)0x0) goto LAB_802370b4;
      pcVar2 = acStack_45 + -(int)__s;
    }
  }
  else {
    if (local_250._1_1_ == 0x74) goto LAB_802370b4;
    if (local_250._1_1_ < 0x74) {
      if (local_250._1_1_ != 0x6f) {
        if (local_250._1_1_ < 0x6f) {
          if (local_250._1_1_ < 0x6e) {
            if (0x69 < local_250._1_1_) goto LAB_802370b4;
LAB_80236c74:
            if (local_250._0_1_ == '\x03') {
              puVar5 = (uint *)__va_arg(param_4,1);
              unaff_r28 = *puVar5;
            }
            else if (local_250._0_1_ == '\x04') {
              puVar5 = (uint *)__va_arg(param_4,2);
              unaff_r22 = *puVar5;
              unaff_r23 = puVar5[1];
            }
            else {
              puVar5 = (uint *)__va_arg(param_4,1);
              unaff_r28 = *puVar5;
            }
            if (local_250._0_1_ == '\x02') {
              unaff_r28 = (uint)(short)unaff_r28;
            }
            if (local_250._0_1_ == '\x01') {
              unaff_r28 = (uint)(char)unaff_r28;
            }
            if (local_250._0_1_ == '\x04') {
              local_264 = local_254;
              local_260 = local_250;
              local_25c = local_24c;
              local_258 = local_248;
              __s = (byte *)longlong2str(unaff_r22,unaff_r23,(int)pcVar9,(char *)&local_264);
            }
            else {
              local_274 = local_254;
              local_270 = local_250;
              local_26c = local_24c;
              local_268 = local_248;
              __s = (byte *)long2str(unaff_r28,(int)pcVar9,(char *)&local_274);
            }
            if (__s == (byte *)0x0) goto LAB_802370b4;
            pcVar2 = acStack_45 + -(int)__s;
            goto LAB_802370f4;
          }
          piVar8 = __va_arg(param_4,1);
          piVar8 = (int *)*piVar8;
          if (local_250._0_1_ == 2) {
            *(short *)piVar8 = (short)iVar11;
          }
          else if (local_250._0_1_ < 2) {
            if (local_250._0_1_ == 0) {
              *piVar8 = iVar11;
            }
          }
          else if (local_250._0_1_ == 4) {
            piVar8[1] = iVar11;
            *piVar8 = iVar11 >> 0x1f;
          }
          else if (local_250._0_1_ < 4) {
            *piVar8 = iVar11;
          }
          goto LAB_80237234;
        }
        if (local_250._1_1_ < 0x73) goto LAB_802370b4;
        if (local_250._0_1_ == '\x06') {
          piVar8 = __va_arg(param_4,1);
          __pwcs = (wchar_t *)*piVar8;
          if (__pwcs == (wchar_t *)0x0) {
            __pwcs = (wchar_t *)&DAT_80435dc0;
          }
          sVar3 = wcstombs((char *)local_244,__pwcs,0x200);
          if ((int)sVar3 < 0) goto LAB_802370b4;
          __s = local_244;
        }
        else {
          piVar8 = __va_arg(param_4,1);
          __s = (byte *)*piVar8;
        }
        pcVar10 = local_248;
        if (__s == (byte *)0x0) {
          __s = &DAT_802b4e90;
        }
        if ((char)local_254 == '\0') {
          if (local_254._2_1_ == '\0') {
            pcVar2 = (char *)strlen((char *)__s);
          }
          else {
            pcVar7 = zz_0236458_((int)__s,'\0',(int)local_248);
            pcVar2 = pcVar10;
            if (pcVar7 != (char *)0x0) {
              pcVar2 = pcVar7 + -(int)__s;
            }
          }
        }
        else {
          pcVar2 = (char *)(uint)*__s;
          __s = __s + 1;
          if ((local_254._2_1_ != '\0') && ((int)local_248 < (int)pcVar2)) {
            pcVar2 = pcVar10;
          }
        }
        goto LAB_802370f4;
      }
    }
    else if ((local_250._1_1_ != 0x78) && ((0x77 < local_250._1_1_ || (0x75 < local_250._1_1_))))
    goto LAB_802370b4;
LAB_80236d70:
    if (local_250._0_1_ == '\x03') {
      puVar5 = (uint *)__va_arg(param_4,1);
      unaff_r28 = *puVar5;
    }
    else if (local_250._0_1_ == '\x04') {
      puVar5 = (uint *)__va_arg(param_4,2);
      unaff_r22 = *puVar5;
      unaff_r23 = puVar5[1];
    }
    else {
      puVar5 = (uint *)__va_arg(param_4,1);
      unaff_r28 = *puVar5;
    }
    if (local_250._0_1_ == '\x02') {
      unaff_r28 = unaff_r28 & 0xffff;
    }
    if (local_250._0_1_ == '\x01') {
      unaff_r28 = unaff_r28 & 0xff;
    }
    if (local_250._0_1_ == '\x04') {
      local_284 = local_254;
      local_280 = local_250;
      local_27c = local_24c;
      local_278 = local_248;
      __s = (byte *)longlong2str(unaff_r22,unaff_r23,(int)pcVar9,(char *)&local_284);
    }
    else {
      local_294 = local_254;
      local_290 = local_250;
      local_28c = local_24c;
      local_288 = local_248;
      __s = (byte *)long2str(unaff_r28,(int)pcVar9,(char *)&local_294);
    }
    if (__s == (byte *)0x0) {
LAB_802370b4:
      sVar3 = strlen(pcVar2);
      if (sVar3 == 0) {
        return iVar11 + sVar3;
      }
      iVar4 = (*(code *)param_1)(param_2,pcVar2);
      if (iVar4 != 0) {
        return iVar11 + sVar3;
      }
      return -1;
    }
    pcVar2 = acStack_45 + -(int)__s;
  }
LAB_802370f4:
  pcVar10 = pcVar2;
  if (local_254._0_1_ != '\0') {
    local_2b7[0] = ' ';
    if (local_254._0_1_ == '\x02') {
      local_2b7[0] = '0';
    }
    bVar1 = *__s;
    if ((((bVar1 == 0x2b) || (bVar1 == 0x2d)) || (bVar1 == 0x20)) && (local_2b7[0] == '0')) {
      iVar4 = (*(code *)param_1)(param_2,__s,1);
      if (iVar4 == 0) {
        return -1;
      }
      __s = __s + 1;
      pcVar10 = pcVar2 + -1;
    }
    for (; (int)pcVar2 < local_24c; pcVar2 = pcVar2 + 1) {
      iVar4 = (*(code *)param_1)(param_2,local_2b7,1);
      if (iVar4 == 0) {
        return -1;
      }
    }
  }
  if ((pcVar10 != (char *)0x0) && (iVar4 = (*(code *)param_1)(param_2,__s,pcVar10), iVar4 == 0)) {
    return -1;
  }
  if (local_254._0_1_ == '\0') {
    for (; (int)pcVar2 < local_24c; pcVar2 = pcVar2 + 1) {
      local_2b8 = 0x20;
      iVar4 = (*(code *)param_1)(param_2,&local_2b8,1);
      if (iVar4 == 0) {
        return -1;
      }
    }
  }
  iVar11 = iVar11 + (int)pcVar2;
  goto LAB_80237234;
}



// ==== 80237258  float2str ====

byte * float2str(double param_1,int param_2,int param_3)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  byte *pbVar6;
  int iVar7;
  byte bVar8;
  byte *pbVar9;
  uint uVar10;
  undefined1 local_48 [2];
  undefined2 local_46;
  char local_44 [2];
  short local_42;
  byte local_40;
  byte local_3f [39];
  
  if (0x1fd < *(int *)(param_3 + 0xc)) {
    return (byte *)0x0;
  }
  local_48[0] = 0;
  local_46 = 0x20;
  __num2dec(param_1,(int)local_48,local_44);
  pbVar9 = local_3f + local_40;
  while ((1 < local_40 && (pbVar9 = pbVar9 + -1, *pbVar9 == 0x30))) {
    local_40 = local_40 - 1;
    local_42 = local_42 + 1;
  }
  if (local_3f[0] == 0x49) {
    if (DOUBLE_8043cc48 <= param_1) {
      pbVar9 = (byte *)(param_2 + -4);
      if (((&DAT_803ab570)[*(byte *)(param_3 + 5)] & 0x80) != 0) {
        strcpy((char *)pbVar9,&DAT_802b4e9b);
        return pbVar9;
      }
      strcpy((char *)pbVar9,&DAT_802b4e9f);
      return pbVar9;
    }
    pbVar9 = (byte *)(param_2 + -5);
    if (((&DAT_803ab570)[*(byte *)(param_3 + 5)] & 0x80) != 0) {
      strcpy((char *)pbVar9,&DAT_802b4e91);
      return pbVar9;
    }
    strcpy((char *)pbVar9,&DAT_802b4e96);
    return pbVar9;
  }
  if (local_3f[0] < 0x49) {
    if (local_3f[0] == 0x30) {
      local_42 = 0;
    }
  }
  else if (local_3f[0] == 0x4e) {
    if (local_44[0] == '\0') {
      pbVar9 = (byte *)(param_2 + -4);
      if (((&DAT_803ab570)[*(byte *)(param_3 + 5)] & 0x80) != 0) {
        strcpy((char *)pbVar9,&DAT_802b4ead);
        return pbVar9;
      }
      strcpy((char *)pbVar9,&DAT_802b4eb1);
      return pbVar9;
    }
    pbVar9 = (byte *)(param_2 + -5);
    if (((&DAT_803ab570)[*(byte *)(param_3 + 5)] & 0x80) != 0) {
      strcpy((char *)pbVar9,&DAT_802b4ea3);
      return pbVar9;
    }
    strcpy((char *)pbVar9,&DAT_802b4ea8);
    return pbVar9;
  }
  pbVar9 = (byte *)(param_2 + -1);
  bVar8 = *(byte *)(param_3 + 5);
  local_42 = (ushort)local_40 + local_42 + -1;
  *(undefined1 *)(param_2 + -1) = 0;
  if (bVar8 == 0x65) goto LAB_80237594;
  if (bVar8 < 0x65) {
    if (bVar8 != 0x46) {
      if (bVar8 < 0x46) {
        if (bVar8 < 0x45) {
          return pbVar9;
        }
        goto LAB_80237594;
      }
      if (0x47 < bVar8) {
        return pbVar9;
      }
LAB_802374dc:
      if (*(int *)(param_3 + 0xc) < (int)(uint)local_40) {
        round_decimal((int)local_44,*(int *)(param_3 + 0xc));
      }
      iVar5 = (int)local_42;
      if ((iVar5 < -4) || (*(int *)(param_3 + 0xc) <= iVar5)) {
        if (*(char *)(param_3 + 3) == '\0') {
          *(uint *)(param_3 + 0xc) = local_40 - 1;
        }
        else {
          *(int *)(param_3 + 0xc) = *(int *)(param_3 + 0xc) + -1;
        }
        if (*(char *)(param_3 + 5) == 'g') {
          *(undefined1 *)(param_3 + 5) = 0x65;
        }
        else {
          *(undefined1 *)(param_3 + 5) = 0x45;
        }
LAB_80237594:
        iVar5 = *(int *)(param_3 + 0xc) + 1;
        if (iVar5 < (int)(uint)local_40) {
          round_decimal((int)local_44,iVar5);
        }
        iVar5 = (int)local_42;
        bVar8 = 0x2b;
        if (iVar5 < 0) {
          iVar5 = -iVar5;
          bVar8 = 0x2d;
        }
        for (iVar7 = 0; (iVar5 != 0 || (iVar7 < 2)); iVar7 = iVar7 + 1) {
          iVar3 = iVar5 / 10 + (iVar5 >> 0x1f);
          cVar2 = (char)iVar5;
          iVar5 = iVar3 - (iVar3 >> 0x1f);
          pbVar9[-1] = cVar2 + ((char)iVar3 - (char)(iVar3 >> 0x1f)) * -10 + 0x30;
          pbVar9 = pbVar9 + -1;
        }
        bVar1 = *(byte *)(param_3 + 5);
        pbVar9[-1] = bVar8;
        iVar5 = *(int *)(param_3 + 0xc);
        pbVar9 = pbVar9 + -2;
        *pbVar9 = bVar1;
        if (0x1fd < iVar5 + (param_2 - (int)pbVar9)) {
          return (byte *)0x0;
        }
        if ((int)(uint)local_40 < iVar5 + 1) {
          iVar5 = (iVar5 + 2) - (uint)local_40;
          while (iVar5 = iVar5 + -1, iVar5 != 0) {
            pbVar9 = pbVar9 + -1;
            *pbVar9 = 0x30;
          }
        }
        uVar4 = (uint)local_40;
        pbVar6 = local_3f + uVar4;
        while (uVar4 = uVar4 - 1, uVar4 != 0) {
          pbVar6 = pbVar6 + -1;
          pbVar9 = pbVar9 + -1;
          *pbVar9 = *pbVar6;
        }
        if ((*(int *)(param_3 + 0xc) != 0) || (*(char *)(param_3 + 3) != '\0')) {
          pbVar9 = pbVar9 + -1;
          *pbVar9 = 0x2e;
        }
        pbVar9[-1] = local_3f[0];
        if (local_44[0] != '\0') {
          pbVar9[-2] = 0x2d;
          return pbVar9 + -2;
        }
        if (*(char *)(param_3 + 1) == '\x01') {
          pbVar9[-2] = 0x2b;
          return pbVar9 + -2;
        }
        if (*(char *)(param_3 + 1) != '\x02') {
          return pbVar9 + -1;
        }
        pbVar9[-2] = 0x20;
        return pbVar9 + -2;
      }
      if (*(char *)(param_3 + 3) == '\0') {
        iVar5 = (uint)local_40 - (iVar5 + 1);
        *(int *)(param_3 + 0xc) = iVar5;
        if (iVar5 < 0) {
          *(undefined4 *)(param_3 + 0xc) = 0;
        }
      }
      else {
        *(int *)(param_3 + 0xc) = *(int *)(param_3 + 0xc) - (iVar5 + 1);
      }
    }
  }
  else {
    if (bVar8 == 0x67) goto LAB_802374dc;
    if (0x66 < bVar8) {
      return pbVar9;
    }
  }
  iVar5 = ((uint)local_40 - (int)local_42) + -1;
  if (iVar5 < 0) {
    iVar5 = 0;
  }
  if (*(int *)(param_3 + 0xc) < iVar5) {
    round_decimal((int)local_44,(uint)local_40 - (iVar5 - *(int *)(param_3 + 0xc)));
    iVar5 = ((uint)local_40 - (int)local_42) + -1;
    if (iVar5 < 0) {
      iVar5 = 0;
    }
  }
  iVar7 = local_42 + 1;
  if (iVar7 < 0) {
    iVar7 = 0;
  }
  if (0x1fd < iVar7 + iVar5) {
    return (byte *)0x0;
  }
  uVar4 = *(int *)(param_3 + 0xc) - iVar5;
  pbVar6 = local_3f + local_40;
  if (0 < (int)uVar4) {
    uVar10 = uVar4 >> 3;
    if (uVar10 != 0) {
      do {
        pbVar9[-1] = 0x30;
        pbVar9[-2] = 0x30;
        pbVar9[-3] = 0x30;
        pbVar9[-4] = 0x30;
        pbVar9[-5] = 0x30;
        pbVar9[-6] = 0x30;
        pbVar9[-7] = 0x30;
        pbVar9 = pbVar9 + -8;
        *pbVar9 = 0x30;
        uVar10 = uVar10 - 1;
      } while (uVar10 != 0);
      uVar4 = uVar4 & 7;
      if (uVar4 == 0) goto LAB_802377c4;
    }
    do {
      pbVar9 = pbVar9 + -1;
      *pbVar9 = 0x30;
      uVar4 = uVar4 - 1;
    } while (uVar4 != 0);
  }
LAB_802377c4:
  for (iVar3 = 0; (iVar3 < iVar5 && (iVar3 < (int)(uint)local_40)); iVar3 = iVar3 + 1) {
    pbVar6 = pbVar6 + -1;
    pbVar9 = pbVar9 + -1;
    *pbVar9 = *pbVar6;
  }
  uVar4 = iVar5 - iVar3;
  if (iVar3 < iVar5) {
    uVar10 = uVar4 >> 3;
    if (uVar10 != 0) {
      do {
        pbVar9[-1] = 0x30;
        pbVar9[-2] = 0x30;
        pbVar9[-3] = 0x30;
        pbVar9[-4] = 0x30;
        pbVar9[-5] = 0x30;
        pbVar9[-6] = 0x30;
        pbVar9[-7] = 0x30;
        pbVar9 = pbVar9 + -8;
        *pbVar9 = 0x30;
        uVar10 = uVar10 - 1;
      } while (uVar10 != 0);
      uVar4 = uVar4 & 7;
      if (uVar4 == 0) goto LAB_80237840;
    }
    do {
      pbVar9 = pbVar9 + -1;
      *pbVar9 = 0x30;
      uVar4 = uVar4 - 1;
    } while (uVar4 != 0);
  }
LAB_80237840:
  if ((*(int *)(param_3 + 0xc) != 0) || (*(char *)(param_3 + 3) != '\0')) {
    pbVar9 = pbVar9 + -1;
    *pbVar9 = 0x2e;
  }
  if (iVar7 == 0) {
    pbVar9 = pbVar9 + -1;
    *pbVar9 = 0x30;
  }
  else {
    for (iVar5 = 0; iVar5 < (int)(iVar7 - (uint)local_40); iVar5 = iVar5 + 1) {
      pbVar9 = pbVar9 + -1;
      *pbVar9 = 0x30;
    }
    uVar4 = iVar7 - iVar5;
    if (iVar5 < iVar7) {
      uVar10 = uVar4 >> 3;
      if (uVar10 != 0) {
        do {
          pbVar9[-1] = pbVar6[-1];
          pbVar9[-2] = pbVar6[-2];
          pbVar9[-3] = pbVar6[-3];
          pbVar9[-4] = pbVar6[-4];
          pbVar9[-5] = pbVar6[-5];
          pbVar9[-6] = pbVar6[-6];
          pbVar9[-7] = pbVar6[-7];
          pbVar6 = pbVar6 + -8;
          pbVar9 = pbVar9 + -8;
          *pbVar9 = *pbVar6;
          uVar10 = uVar10 - 1;
        } while (uVar10 != 0);
        uVar4 = uVar4 & 7;
        if (uVar4 == 0) goto LAB_8023790c;
      }
      do {
        pbVar6 = pbVar6 + -1;
        pbVar9 = pbVar9 + -1;
        *pbVar9 = *pbVar6;
        uVar4 = uVar4 - 1;
      } while (uVar4 != 0);
    }
  }
LAB_8023790c:
  if (local_44[0] == '\0') {
    if (*(char *)(param_3 + 1) == '\x01') {
      pbVar9 = pbVar9 + -1;
      *pbVar9 = 0x2b;
    }
    else if (*(char *)(param_3 + 1) == '\x02') {
      pbVar9 = pbVar9 + -1;
      *pbVar9 = 0x20;
    }
  }
  else {
    pbVar9 = pbVar9 + -1;
    *pbVar9 = 0x2d;
  }
  return pbVar9;
}



// ==== 80237974  round_decimal ====

void round_decimal(int param_1,int param_2)

{
  char cVar1;
  char cVar2;
  char *pcVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  
  if (-1 < param_2) {
    if ((int)(uint)*(byte *)(param_1 + 4) <= param_2) {
      return;
    }
    iVar4 = param_1 + param_2;
    pcVar6 = (char *)(iVar4 + 5);
    uVar5 = (uint)(char)(*(char *)(iVar4 + 5) + -0x30);
    if (uVar5 == 5) {
      pcVar3 = (char *)(param_1 + (uint)*(byte *)(param_1 + 4) + 5);
      do {
        pcVar3 = pcVar3 + -1;
        if (pcVar3 <= pcVar6) break;
      } while (*pcVar3 == '0');
      if (pcVar3 == pcVar6) {
        uVar5 = *(byte *)(iVar4 + 4) & 1;
      }
      else {
        uVar5 = 1;
      }
    }
    else {
      uVar5 = ((int)(uVar5 ^ 5) >> 1) - ((uVar5 ^ 5) & uVar5) >> 0x1f;
    }
    for (; param_2 != 0; param_2 = param_2 + -1) {
      pcVar6 = pcVar6 + -1;
      cVar1 = *pcVar6 + (char)uVar5;
      cVar2 = cVar1 + -0x30;
      uVar5 = (int)cVar2 ^ 9;
      uVar5 = -((int)(((int)uVar5 >> 1) - (uVar5 & (int)cVar2)) >> 0x1f);
      if ((uVar5 == 0) && (cVar2 != '\0')) {
        *pcVar6 = cVar1;
        break;
      }
    }
    if (uVar5 != 0) {
      *(short *)(param_1 + 2) = *(short *)(param_1 + 2) + 1;
      *(undefined1 *)(param_1 + 4) = 1;
      *(undefined1 *)(param_1 + 5) = 0x31;
      return;
    }
    if (param_2 != 0) {
      *(char *)(param_1 + 4) = (char)param_2;
      return;
    }
  }
  *(undefined2 *)(param_1 + 2) = 0;
  *(undefined1 *)(param_1 + 4) = 1;
  *(undefined1 *)(param_1 + 5) = 0x30;
  return;
}



// ==== 80237aa0  double2hex ====

char * double2hex(double param_1,int param_2,int param_3)

{
  char cVar1;
  char *__dest;
  char *pcVar2;
  byte bVar3;
  uint uVar4;
  uint uVar5;
  undefined8 local_78;
  undefined1 local_70 [2];
  undefined2 local_6e;
  double local_68;
  char local_60 [4];
  uint local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  char acStack_40 [5];
  char local_3b;
  
  if (*(int *)(param_3 + 0xc) < 0x1fe) {
    local_70[0] = 0;
    local_6e = 0x20;
    local_78 = param_1;
    local_68 = param_1;
    __num2dec(param_1,(int)local_70,acStack_40);
    if (local_3b == 'I') {
      if (((int)local_68._0_2_ & 0x8000U) == 0) {
        __dest = (char *)(param_2 + -4);
        if (*(char *)(param_3 + 5) == 'A') {
          strcpy(__dest,&DAT_802b4e9b);
        }
        else {
          strcpy(__dest,&DAT_802b4e9f);
        }
      }
      else {
        __dest = (char *)(param_2 + -5);
        if (*(char *)(param_3 + 5) == 'A') {
          strcpy(__dest,&DAT_802b4e91);
        }
        else {
          strcpy(__dest,&DAT_802b4e96);
        }
      }
    }
    else if (local_3b == 'N') {
      if (((ulonglong)local_78 & 0x8000000000000000) == 0) {
        __dest = (char *)(param_2 + -4);
        if (*(char *)(param_3 + 5) == 'A') {
          strcpy(__dest,&DAT_802b4ead);
        }
        else {
          strcpy(__dest,&DAT_802b4eb1);
        }
      }
      else {
        __dest = (char *)(param_2 + -5);
        if (*(char *)(param_3 + 5) == 'A') {
          strcpy(__dest,&DAT_802b4ea3);
        }
        else {
          strcpy(__dest,&DAT_802b4ea8);
        }
      }
    }
    else {
      local_50 = 0x1010000;
      local_4c = (uint)CONCAT12(100,local_4c._2_2_);
      local_48 = 0;
      local_44 = 1;
      local_60[0] = '\x01';
      local_60[1] = '\x01';
      local_60[2] = '\0';
      local_60[3] = '\0';
      local_5c = local_4c;
      local_58 = 0;
      local_54 = 1;
      pcVar2 = long2str((int)(short)((ushort)((uint)(int)local_68._0_2_ >> 4) & 0x7ff) - 0x3ff,
                        param_2,local_60);
      if (*(char *)(param_3 + 5) == 'a') {
        pcVar2[-1] = 'p';
      }
      else {
        pcVar2[-1] = 'P';
      }
      pcVar2 = pcVar2 + -1;
      uVar4 = *(uint *)(param_3 + 0xc);
      uVar5 = uVar4;
      if (0 < (int)uVar4) {
        do {
          bVar3 = (byte)local_70[(int)uVar4 / 2 + -7] >> 4;
          if ((uVar4 & 1 ^ -((int)uVar4 >> 0x1f)) != -((int)uVar4 >> 0x1f)) {
            bVar3 = local_70[(int)uVar4 / 2 + -7];
          }
          bVar3 = bVar3 & 0xf;
          if (bVar3 < 10) {
            cVar1 = bVar3 + 0x30;
          }
          else if (*(char *)(param_3 + 5) == 'a') {
            cVar1 = bVar3 + 0x57;
          }
          else {
            cVar1 = bVar3 + 0x37;
          }
          pcVar2 = pcVar2 + -1;
          *pcVar2 = cVar1;
          uVar4 = uVar4 - 1;
          uVar5 = uVar5 - 1;
        } while (uVar5 != 0);
      }
      if ((*(int *)(param_3 + 0xc) != 0) || (*(char *)(param_3 + 3) != '\0')) {
        pcVar2 = pcVar2 + -1;
        *pcVar2 = '.';
      }
      cVar1 = *(char *)(param_3 + 5);
      pcVar2[-1] = '1';
      if (cVar1 == 'a') {
        pcVar2[-2] = 'x';
      }
      else {
        pcVar2[-2] = 'X';
      }
      __dest = pcVar2 + -3;
      *__dest = '0';
      if (((int)local_68._0_2_ & 0x8000U) == 0) {
        if (*(char *)(param_3 + 1) == '\x01') {
          __dest = pcVar2 + -4;
          *__dest = '+';
        }
        else if (*(char *)(param_3 + 1) == '\x02') {
          __dest = pcVar2 + -4;
          *__dest = ' ';
        }
      }
      else {
        __dest = pcVar2 + -4;
        *__dest = '-';
      }
    }
  }
  else {
    __dest = (char *)0x0;
  }
  return __dest;
}



// ==== 80237dd8  longlong2str ====

char * longlong2str(uint param_1,int param_2,int param_3,char *param_4)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  uint unaff_r28;
  int unaff_r29;
  uint uVar8;
  undefined8 uVar9;
  longlong lVar10;
  
  pcVar6 = (char *)(param_3 + -1);
  bVar1 = false;
  iVar5 = 0;
  *(undefined1 *)(param_3 + -1) = 0;
  if ((param_2 == 0 && param_1 == 0) && (*(int *)(param_4 + 0xc) == 0)) {
    if (param_4[3] == '\0') {
      return pcVar6;
    }
    if (param_4[5] != 'o') {
      return pcVar6;
    }
  }
  lVar10 = CONCAT44(param_1,param_2);
  switch(param_4[5]) {
  case 'X':
  case 'x':
    unaff_r28 = 0x10;
    param_4[1] = '\0';
    unaff_r29 = 0;
    lVar10 = CONCAT44(param_1,param_2);
    break;
  case 'd':
  case 'i':
    unaff_r28 = 10;
    unaff_r29 = 0;
    lVar10 = CONCAT44(param_1,param_2);
    if ((param_1 ^ 0x80000000) < 0x80000000) {
      bVar1 = true;
      lVar10 = CONCAT44(-((param_2 != 0) + param_1),-param_2);
    }
    break;
  case 'o':
    unaff_r28 = 8;
    param_4[1] = '\0';
    unaff_r29 = 0;
    lVar10 = CONCAT44(param_1,param_2);
    break;
  case 'u':
    unaff_r28 = 10;
    param_4[1] = '\0';
    unaff_r29 = 0;
    lVar10 = CONCAT44(param_1,param_2);
  }
  do {
    pcVar7 = pcVar6;
    iVar3 = iVar5;
    uVar4 = (uint)((ulonglong)lVar10 >> 0x20);
    uVar9 = __mod2u(uVar4,(uint)lVar10,unaff_r29,unaff_r28);
    lVar10 = zz_0232b0c_(uVar4,(uint)lVar10,unaff_r29,unaff_r28);
    cVar2 = (char)uVar9;
    if ((int)uVar9 < 10) {
      cVar2 = cVar2 + '0';
    }
    else if (param_4[5] == 'x') {
      cVar2 = cVar2 + 'W';
    }
    else {
      cVar2 = cVar2 + '7';
    }
    pcVar6 = pcVar7 + -1;
    *pcVar6 = cVar2;
    iVar5 = iVar3 + 1;
  } while (lVar10 != 0);
  if (((unaff_r28 == 8 && unaff_r29 == 0) && (param_4[3] != '\0')) && (*pcVar6 != '0')) {
    iVar5 = iVar3 + 2;
    pcVar6 = pcVar7 + -2;
    *pcVar6 = '0';
  }
  if (*param_4 == '\x02') {
    *(undefined4 *)(param_4 + 0xc) = *(undefined4 *)(param_4 + 8);
    if ((bVar1) || (param_4[1] != '\0')) {
      *(int *)(param_4 + 0xc) = *(int *)(param_4 + 0xc) + -1;
    }
    if ((unaff_r28 == 0x10 && unaff_r29 == 0) && (param_4[3] != '\0')) {
      *(int *)(param_4 + 0xc) = *(int *)(param_4 + 0xc) + -2;
    }
  }
  iVar3 = *(int *)(param_4 + 0xc);
  if (0x1fd < iVar3 + (param_3 - (int)pcVar6)) {
    return (char *)0x0;
  }
  uVar4 = iVar3 - iVar5;
  if (iVar5 < iVar3) {
    uVar8 = uVar4 >> 3;
    if (uVar8 != 0) {
      do {
        builtin_strncpy(pcVar6 + -8,"00000000",8);
        pcVar6 = pcVar6 + -8;
        uVar8 = uVar8 - 1;
      } while (uVar8 != 0);
      uVar4 = uVar4 & 7;
      if (uVar4 == 0) goto LAB_80238064;
    }
    do {
      pcVar6 = pcVar6 + -1;
      *pcVar6 = '0';
      uVar4 = uVar4 - 1;
    } while (uVar4 != 0);
  }
LAB_80238064:
  if ((unaff_r28 == 0x10 && unaff_r29 == 0) && (param_4[3] != '\0')) {
    pcVar6[-1] = param_4[5];
    pcVar6 = pcVar6 + -2;
    *pcVar6 = '0';
  }
  if (bVar1) {
    pcVar6 = pcVar6 + -1;
    *pcVar6 = '-';
  }
  else if (param_4[1] == '\x01') {
    pcVar6 = pcVar6 + -1;
    *pcVar6 = '+';
  }
  else if (param_4[1] == '\x02') {
    pcVar6 = pcVar6 + -1;
    *pcVar6 = ' ';
  }
  return pcVar6;
}



// ==== 802380ec  long2str ====

char * long2str(uint param_1,int param_2,char *param_3)

{
  char cVar1;
  bool bVar2;
  uint in_r0;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  char cVar8;
  uint uVar9;
  
  *(undefined1 *)(param_2 + -1) = 0;
  bVar2 = false;
  if (((param_1 == 0) && (*(int *)(param_3 + 0xc) == 0)) &&
     ((param_3[3] == '\0' || (param_3[5] != 'o')))) {
    return (char *)(param_2 + -1);
  }
  switch(param_3[5]) {
  case 'X':
  case 'x':
    in_r0 = 0x10;
    param_3[1] = '\0';
    break;
  case 'd':
  case 'i':
    in_r0 = 10;
    if ((int)param_1 < 0) {
      param_1 = -param_1;
      bVar2 = true;
    }
    break;
  case 'o':
    in_r0 = 8;
    param_3[1] = '\0';
    break;
  case 'u':
    in_r0 = 10;
    param_3[1] = '\0';
  }
  cVar1 = param_3[5];
  pcVar5 = (char *)(param_2 + -1);
  iVar7 = 0;
  do {
    iVar6 = iVar7;
    pcVar4 = pcVar5;
    iVar7 = param_1 - (param_1 / in_r0) * in_r0;
    param_1 = param_1 / in_r0;
    cVar8 = (char)iVar7;
    if (iVar7 < 10) {
      cVar8 = cVar8 + '0';
    }
    else if (cVar1 == 'x') {
      cVar8 = cVar8 + 'W';
    }
    else {
      cVar8 = cVar8 + '7';
    }
    pcVar4[-1] = cVar8;
    pcVar5 = pcVar4 + -1;
    iVar7 = iVar6 + 1;
  } while (param_1 != 0);
  if (((in_r0 == 8) && (param_3[3] != '\0')) && (*pcVar5 != '0')) {
    iVar7 = iVar6 + 2;
    pcVar5 = pcVar4 + -2;
    *pcVar5 = '0';
  }
  if (*param_3 == '\x02') {
    *(undefined4 *)(param_3 + 0xc) = *(undefined4 *)(param_3 + 8);
    if ((bVar2) || (param_3[1] != '\0')) {
      *(int *)(param_3 + 0xc) = *(int *)(param_3 + 0xc) + -1;
    }
    if ((in_r0 == 0x10) && (param_3[3] != '\0')) {
      *(int *)(param_3 + 0xc) = *(int *)(param_3 + 0xc) + -2;
    }
  }
  iVar6 = *(int *)(param_3 + 0xc);
  if (0x1fd < iVar6 + (param_2 - (int)pcVar5)) {
    return (char *)0x0;
  }
  uVar3 = iVar6 - iVar7;
  if (iVar7 < iVar6) {
    uVar9 = uVar3 >> 3;
    if (uVar9 != 0) {
      do {
        builtin_strncpy(pcVar5 + -8,"00000000",8);
        pcVar5 = pcVar5 + -8;
        uVar9 = uVar9 - 1;
      } while (uVar9 != 0);
      uVar3 = uVar3 & 7;
      if (uVar3 == 0) goto LAB_802382dc;
    }
    do {
      pcVar5 = pcVar5 + -1;
      *pcVar5 = '0';
      uVar3 = uVar3 - 1;
    } while (uVar3 != 0);
  }
LAB_802382dc:
  if ((in_r0 == 0x10) && (param_3[3] != '\0')) {
    pcVar5[-1] = param_3[5];
    pcVar5 = pcVar5 + -2;
    *pcVar5 = '0';
  }
  if (bVar2) {
    pcVar5 = pcVar5 + -1;
    *pcVar5 = '-';
  }
  else if (param_3[1] == '\x01') {
    pcVar5 = pcVar5 + -1;
    *pcVar5 = '+';
  }
  else if (param_3[1] == '\x02') {
    pcVar5 = pcVar5 + -1;
    *pcVar5 = ' ';
  }
  return pcVar5;
}



// ==== 80238344  parse_format ====

char * parse_format(int param_1,char *param_2,uint *param_3)

{
  bool bVar1;
  undefined2 uVar2;
  uint uVar3;
  uint3 uVar4;
  uint *puVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  undefined4 local_28;
  undefined4 local_24;
  uint local_20;
  uint local_1c;
  
  uVar4 = local_24._1_3_;
  uVar6 = (uint)*(char *)(param_1 + 1);
  pcVar7 = (char *)(param_1 + 1);
  local_28 = 0x1000000;
  local_24 = (uint)local_24._1_3_;
  uVar3 = local_24;
  local_20 = 0;
  local_1c = 0;
  local_24._2_2_ = (undefined2)uVar4;
  if (uVar6 == 0x25) {
    local_24._1_3_ = CONCAT12(*(char *)(param_1 + 1),local_24._2_2_);
    local_24 = (uint)local_24._1_3_;
    *param_3 = 0x1000000;
    param_3[1] = local_24;
    param_3[2] = 0;
    param_3[3] = 0;
    return (char *)(param_1 + 2);
  }
  while( true ) {
    bVar1 = true;
    uVar2 = local_28._2_2_;
    switch(uVar6) {
    case 0x20:
      if (local_28._1_1_ != '\x01') {
        local_28._1_3_ = CONCAT12(2,uVar2);
      }
      break;
    default:
      bVar1 = false;
      break;
    case 0x23:
      local_28 = CONCAT31(local_28._0_3_,1);
      break;
    case 0x2b:
      local_28._1_3_ = CONCAT12(1,uVar2);
      break;
    case 0x2d:
      local_28 = local_28 & 0xffffff;
      break;
    case 0x30:
      if (local_28._0_1_ != '\0') {
        local_28 = CONCAT13(2,local_28._1_3_);
      }
    }
    if (!bVar1) break;
    pcVar7 = pcVar7 + 1;
    uVar6 = (uint)*pcVar7;
  }
  if (uVar6 == 0x2a) {
    puVar5 = (uint *)__va_arg(param_2,1);
    local_20 = *puVar5;
    if ((int)local_20 < 0) {
      local_20 = -local_20;
      local_28 = local_28 & 0xffffff;
    }
    pcVar7 = pcVar7 + 1;
    uVar6 = (uint)*pcVar7;
  }
  else {
    while (((&DAT_803ab570)[uVar6 & 0xff] & 0x10) != 0) {
      pcVar7 = pcVar7 + 1;
      local_20 = (uVar6 + local_20 * 10) - 0x30;
      uVar6 = (uint)*pcVar7;
    }
  }
  if (0x1fd < (int)local_20) {
    local_24._1_3_ = CONCAT12(0xff,local_24._2_2_);
    local_24 = (uint)local_24._1_3_;
    *param_3 = local_28;
    param_3[1] = local_24;
    param_3[2] = local_20;
    param_3[3] = 0;
    return pcVar7 + 1;
  }
  pcVar8 = pcVar7;
  if (uVar6 == 0x2e) {
    pcVar8 = pcVar7 + 1;
    local_28._2_2_ = CONCAT11(1,(byte)local_28);
    uVar6 = (uint)*pcVar8;
    if (uVar6 == 0x2a) {
      puVar5 = (uint *)__va_arg(param_2,1);
      local_1c = *puVar5;
      if ((int)local_1c < 0) {
        local_28 = CONCAT22(local_28._0_2_,(ushort)(byte)local_28);
      }
      pcVar8 = pcVar7 + 2;
      uVar6 = (uint)*pcVar8;
    }
    else {
      while (((&DAT_803ab570)[uVar6 & 0xff] & 0x10) != 0) {
        pcVar8 = pcVar8 + 1;
        local_1c = (uVar6 + local_1c * 10) - 0x30;
        uVar6 = (uint)*pcVar8;
      }
    }
  }
  bVar1 = true;
  if (uVar6 == 0x68) {
    local_24 = CONCAT13(2,uVar4);
    if (pcVar8[1] == 'h') {
      local_24 = CONCAT13(1,uVar4);
      pcVar8 = pcVar8 + 1;
      uVar6 = 0x68;
    }
  }
  else {
    if ((int)uVar6 < 0x68) {
      if (uVar6 == 0x4c) {
        local_24 = CONCAT13(5,uVar4);
        goto LAB_80238618;
      }
    }
    else if (uVar6 == 0x6c) {
      local_24 = CONCAT13(3,uVar4);
      if (pcVar8[1] == 'l') {
        local_24 = CONCAT13(4,uVar4);
        pcVar8 = pcVar8 + 1;
        uVar6 = 0x6c;
      }
      goto LAB_80238618;
    }
    bVar1 = false;
    local_24 = uVar3;
  }
LAB_80238618:
  if (bVar1) {
    pcVar8 = pcVar8 + 1;
    uVar6 = (uint)*pcVar8;
  }
  local_24._1_3_ = CONCAT12((char)uVar6,local_24._2_2_);
  switch(uVar6) {
  case 0x41:
  case 0x61:
    if (local_28._2_1_ == '\0') {
      local_1c = 0xd;
    }
    if (((local_24._0_1_ == '\x02') || (local_24._0_1_ == '\x04')) || (local_24._0_1_ == '\x01')) {
      local_24._1_3_ = CONCAT12(0xff,local_24._2_2_);
    }
    break;
  default:
    local_24._1_3_ = CONCAT12(0xff,local_24._2_2_);
    break;
  case 0x46:
  case 0x66:
    if ((local_24._0_1_ == '\x02') || (local_24._0_1_ == '\x04')) {
      local_24._1_3_ = CONCAT12(0xff,local_24._2_2_);
    }
    else if (local_28._2_1_ == '\0') {
      local_1c = 6;
    }
    break;
  case 0x47:
  case 0x67:
    if (local_1c == 0) {
      local_1c = 1;
    }
  case 0x45:
  case 0x65:
    if (((local_24._0_1_ == '\x02') || (local_24._0_1_ == '\x04')) || (local_24._0_1_ == '\x01')) {
      local_24._1_3_ = CONCAT12(0xff,local_24._2_2_);
    }
    else if (local_28._2_1_ == '\0') {
      local_1c = 6;
    }
    break;
  case 0x58:
  case 100:
  case 0x69:
  case 0x6f:
  case 0x75:
  case 0x78:
    if (local_24._0_1_ == '\x05') {
      local_24._1_3_ = CONCAT12(0xff,local_24._2_2_);
      local_24 = CONCAT13(5,local_24._1_3_);
    }
    else if (local_28._2_1_ == '\0') {
      local_1c = 1;
    }
    else if (local_28._0_1_ == '\x02') {
      local_28 = CONCAT13(1,local_28._1_3_);
    }
    break;
  case 99:
    if (local_24._0_1_ == '\x03') {
      local_24 = CONCAT13(6,local_24._1_3_);
    }
    else if ((local_28._2_1_ != '\0') || (local_24._0_1_ != '\0')) {
      local_24._1_3_ = CONCAT12(0xff,local_24._2_2_);
    }
    break;
  case 0x6e:
    if (local_24._0_1_ == '\x05') {
      local_24._1_3_ = CONCAT12(0xff,local_24._2_2_);
      local_24 = CONCAT13(5,local_24._1_3_);
    }
    break;
  case 0x70:
    local_24._1_3_ = CONCAT12(0x78,local_24._2_2_);
    local_28 = CONCAT31(local_28._0_3_,1);
    local_24 = CONCAT13(3,local_24._1_3_);
    local_1c = 8;
    break;
  case 0x73:
    if (local_24._0_1_ == '\x03') {
      local_24 = CONCAT13(6,local_24._1_3_);
    }
    else if (local_24._0_1_ != '\0') {
      local_24._1_3_ = CONCAT12(0xff,local_24._2_2_);
    }
  }
  *param_3 = local_28;
  param_3[1] = local_24;
  param_3[2] = local_20;
  param_3[3] = local_1c;
  return pcVar8 + 1;
}



// ==== 80238848  qsort ====

void qsort(void *__base,size_t __nmemb,size_t __size,__compar_fn_t __compar)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  void *pvVar5;
  void *pvVar6;
  void *pvVar7;
  void *pvVar8;
  uint uVar9;
  uint uVar10;
  
  if (__nmemb < 2) {
    return;
  }
  uVar10 = (__nmemb >> 1) + 1;
  pvVar8 = (void *)((int)__base + __size * (__nmemb >> 1));
  pvVar7 = (void *)((int)__base + __size * (__nmemb - 1));
  do {
    if (uVar10 < 2) {
      iVar2 = (int)pvVar7 + -1;
      iVar3 = (int)pvVar8 + -1;
      iVar4 = __size + 1;
      while (iVar4 = iVar4 + -1, iVar4 != 0) {
        uVar1 = *(undefined1 *)(iVar3 + 1);
        *(undefined1 *)(iVar3 + 1) = *(undefined1 *)(iVar2 + 1);
        iVar3 = iVar3 + 1;
        *(undefined1 *)(iVar2 + 1) = uVar1;
        iVar2 = iVar2 + 1;
      }
      __nmemb = __nmemb - 1;
      if (__nmemb == 1) {
        return;
      }
      pvVar7 = (void *)((int)pvVar7 - __size);
    }
    else {
      pvVar8 = (void *)((int)pvVar8 - __size);
      uVar10 = uVar10 - 1;
    }
    pvVar6 = (void *)((int)__base + __size * (uVar10 - 1));
    uVar9 = uVar10;
    while (uVar9 << 1 <= __nmemb) {
      uVar9 = uVar9 * 2;
      pvVar5 = (void *)((int)__base + __size * (uVar9 - 1));
      if (uVar9 < __nmemb) {
        iVar2 = (*__compar)(pvVar5,(void *)((int)pvVar5 + __size));
        if (iVar2 < 0) {
          uVar9 = uVar9 + 1;
          pvVar5 = (void *)((int)pvVar5 + __size);
        }
      }
      iVar2 = (*__compar)(pvVar6,pvVar5);
      if (-1 < iVar2) break;
      iVar2 = (int)pvVar5 + -1;
      iVar3 = (int)pvVar6 + -1;
      iVar4 = __size + 1;
      while (iVar4 = iVar4 + -1, pvVar6 = pvVar5, iVar4 != 0) {
        uVar1 = *(undefined1 *)(iVar3 + 1);
        *(undefined1 *)(iVar3 + 1) = *(undefined1 *)(iVar2 + 1);
        iVar3 = iVar3 + 1;
        *(undefined1 *)(iVar2 + 1) = uVar1;
        iVar2 = iVar2 + 1;
      }
    }
  } while( true );
}



// ==== 80238a44  strstr ====

char * strstr(char *__haystack,char *__needle)

{
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  
  if (__needle == (char *)0x0) {
    return __haystack;
  }
  pcVar1 = __haystack + -1;
  if (*__needle == '\0') {
    return __haystack;
  }
  do {
    do {
      pcVar2 = pcVar1;
      pcVar1 = pcVar2 + 1;
      if (*pcVar1 == '\0') {
        return (char *)0x0;
      }
    } while (*pcVar1 != *__needle);
    pcVar3 = __needle + -1;
    do {
      pcVar2 = pcVar2 + 1;
      pcVar3 = pcVar3 + 1;
      if (*pcVar2 != *pcVar3) break;
    } while (*pcVar2 != '\0');
    if (*pcVar3 == '\0') {
      return pcVar1;
    }
  } while( true );
}



// ==== 80238aac  zz_0238aac_ ====

char * zz_0238aac_(int param_1,char param_2)

{
  char *pcVar1;
  
  pcVar1 = (char *)(param_1 + -1);
  while( true ) {
    pcVar1 = pcVar1 + 1;
    if (*pcVar1 == '\0') break;
    if (*pcVar1 == param_2) {
      return pcVar1;
    }
  }
  if (param_2 == '\0') {
    return pcVar1;
  }
  return (char *)0x0;
}



// ==== 80238adc  gnt4-strncmp ====

int gnt4_strncmp(char *__s1,char *__s2,size_t __n)

{
  uint uVar1;
  byte *pbVar2;
  byte *pbVar3;
  int iVar4;
  
  pbVar2 = (byte *)(__s1 + -1);
  pbVar3 = (byte *)(__s2 + -1);
  iVar4 = __n + 1;
  while( true ) {
    iVar4 = iVar4 + -1;
    if (iVar4 == 0) {
      return 0;
    }
    pbVar2 = pbVar2 + 1;
    uVar1 = (uint)*pbVar2;
    pbVar3 = pbVar3 + 1;
    if (uVar1 != *pbVar3) break;
    if (uVar1 == 0) {
      return 0;
    }
  }
  return uVar1 - *pbVar3;
}



// ==== 80238b1c  gnt4-strcmp ====

int gnt4_strcmp(char *__s1,char *__s2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = (uint)(byte)*__s1;
  if (uVar3 - (byte)*__s2 != 0) {
    return uVar3 - (byte)*__s2;
  }
  uVar4 = (uint)__s1 & 3;
  if (((uint)__s2 & 3) == uVar4) {
    if (uVar4 != 0) {
      if (uVar3 == 0) {
        return 0;
      }
      for (iVar1 = 3 - uVar4; iVar1 != 0; iVar1 = iVar1 + -1) {
        __s1 = __s1 + 1;
        __s2 = __s2 + 1;
        iVar2 = (uint)(byte)*__s1 - (uint)(byte)*__s2;
        if (iVar2 != 0) {
          return iVar2;
        }
        if ((byte)*__s1 == 0) {
          return 0;
        }
      }
      __s1 = __s1 + 1;
      __s2 = __s2 + 1;
    }
    uVar4 = *(uint *)__s2;
    uVar3 = *(uint *)__s1;
    while ((uVar3 + 0xfefefeff & 0x80808080) == 0) {
      if (uVar3 != uVar4) {
        if (uVar4 < uVar3) {
          return 1;
        }
        return -1;
      }
      __s1 = (char *)((int)__s1 + 4);
      __s2 = (char *)((int)__s2 + 4);
      uVar4 = *(uint *)__s2;
      uVar3 = *(uint *)__s1;
    }
    uVar3 = (uint)(byte)*__s1;
    if (uVar3 - (byte)*__s2 != 0) {
      return uVar3 - (byte)*__s2;
    }
  }
  if (uVar3 == 0) {
    return 0;
  }
  do {
    __s1 = (char *)((int)__s1 + 1);
    __s2 = (char *)((int)__s2 + 1);
    iVar1 = (uint)(byte)*__s1 - (uint)(byte)*__s2;
    if (iVar1 != 0) {
      return iVar1;
    }
  } while ((byte)*__s1 != 0);
  return 0;
}



// ==== 80238c44  zz_0238c44_ ====

void zz_0238c44_(int param_1,int param_2,int param_3)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  
  pcVar2 = (char *)(param_2 + -1);
  pcVar5 = (char *)(param_1 + -1);
  do {
    pcVar4 = pcVar5;
    pcVar5 = pcVar4 + 1;
  } while (*pcVar5 != '\0');
  iVar3 = param_3 + 1;
  do {
    pcVar5 = pcVar4;
    iVar3 = iVar3 + -1;
    if (iVar3 == 0) break;
    pcVar2 = pcVar2 + 1;
    cVar1 = *pcVar2;
    pcVar4 = pcVar5 + 1;
    *pcVar4 = cVar1;
  } while (cVar1 != '\0');
  pcVar5[1] = '\0';
  return;
}



// ==== 80238c90  zz_0238c90_ ====

void zz_0238c90_(int param_1,int param_2)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  
  pcVar3 = (char *)(param_2 + -1);
  pcVar2 = (char *)(param_1 + -1);
  do {
    pcVar4 = pcVar2;
    pcVar2 = pcVar4 + 1;
  } while (pcVar4[1] != '\0');
  do {
    pcVar3 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar4 = pcVar4 + 1;
    *pcVar4 = cVar1;
  } while (cVar1 != '\0');
  return;
}



// ==== 80238cbc  zz_0238cbc_ ====

void zz_0238cbc_(int param_1,int param_2,int param_3)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  char *pcVar4;
  
  pcVar2 = (char *)(param_2 + -1);
  pcVar4 = (char *)(param_1 + -1);
  iVar3 = param_3 + 1;
  do {
    iVar3 = iVar3 + -1;
    if (iVar3 == 0) {
      return;
    }
    pcVar2 = pcVar2 + 1;
    cVar1 = *pcVar2;
    pcVar4 = pcVar4 + 1;
    *pcVar4 = cVar1;
  } while (cVar1 != '\0');
  while (iVar3 = iVar3 + -1, iVar3 != 0) {
    pcVar4 = pcVar4 + 1;
    *pcVar4 = '\0';
  }
  return;
}



// ==== 80238d00  strcpy ====

char * strcpy(char *__dest,char *__src)

{
  char *pcVar1;
  char cVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  
  uVar3 = (uint)__src & 3;
  piVar6 = (int *)__dest;
  if (((uint)__dest & 3) == uVar3) {
    if (uVar3 != 0) {
      cVar2 = *__src;
      *__dest = cVar2;
      if (cVar2 == '\0') {
        return __dest;
      }
      pcVar1 = __dest;
      for (iVar5 = 3 - uVar3; iVar5 != 0; iVar5 = iVar5 + -1) {
        __src = __src + 1;
        cVar2 = *__src;
        pcVar1 = pcVar1 + 1;
        *pcVar1 = cVar2;
        if (cVar2 == '\0') {
          return __dest;
        }
      }
      piVar6 = (int *)(pcVar1 + 1);
      __src = __src + 1;
    }
    iVar5 = *(int *)__src;
    if ((iVar5 + 0xfefefeffU & 0x80808080) == 0) {
      piVar4 = piVar6 + -1;
      do {
        piVar6 = piVar4;
        piVar4 = piVar6 + 1;
        *piVar4 = iVar5;
        __src = (char *)((int)__src + 4);
        iVar5 = *(int *)__src;
      } while ((iVar5 + 0xfefefeffU & 0x80808080) == 0);
      piVar6 = piVar6 + 2;
    }
  }
  cVar2 = *__src;
  *(char *)piVar6 = cVar2;
  if (cVar2 != '\0') {
    do {
      __src = (char *)((int)__src + 1);
      cVar2 = *__src;
      piVar6 = (int *)((int)piVar6 + 1);
      *(char *)piVar6 = cVar2;
    } while (cVar2 != '\0');
    return __dest;
  }
  return __dest;
}



// ==== 80238db8  strlen ====

size_t strlen(char *__s)

{
  size_t sVar1;
  char *pcVar2;
  
  pcVar2 = __s + -1;
  sVar1 = 0xffffffff;
  do {
    pcVar2 = pcVar2 + 1;
    sVar1 = sVar1 + 1;
  } while (*pcVar2 != '\0');
  return sVar1;
}



// ==== 80238dd4  atoi ====

int atoi(char *__nptr)

{
  uint uVar1;
  int iStack_18;
  uint local_14;
  int local_10;
  char *local_c;
  undefined4 local_8;
  
  local_8 = 0;
  local_c = __nptr;
  uVar1 = __strtoul(10,0x7fffffff,&LAB_802389b4,&local_c,&iStack_18,&local_14,&local_10);
  if (((local_10 == 0) && ((local_14 != 0 || (uVar1 < 0x80000000)))) &&
     ((local_14 == 0 || (uVar1 < 0x80000001)))) {
    if (local_14 != 0) {
      uVar1 = -uVar1;
    }
  }
  else {
    DAT_80436878 = 0x22;
    uVar1 = 0x7fffffff - ((int)(-local_14 | local_14) >> 0x1f);
  }
  return uVar1;
}



// ==== 80238e94  zz_0238e94_ ====

uint zz_0238e94_(int param_1,int *param_2,uint param_3)

{
  uint uVar1;
  int local_28;
  int local_24;
  int local_20;
  int local_1c [5];
  
  local_1c[1] = 0;
  local_1c[0] = param_1;
  uVar1 = __strtoul(param_3,0x7fffffff,&LAB_802389b4,local_1c,&local_20,&local_24,&local_28);
  if (param_2 != (int *)0x0) {
    *param_2 = param_1 + local_20;
  }
  if (local_28 == 0) {
    if (local_24 != 0) {
      uVar1 = -uVar1;
    }
  }
  else {
    uVar1 = 0xffffffff;
    DAT_80436878 = 0x22;
  }
  return uVar1;
}



// ==== 80238f40  __strtoul ====

uint __strtoul(uint param_1,uint param_2,undefined *param_3,undefined4 param_4,int *param_5,
              undefined4 *param_6,undefined4 *param_7)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  
  uVar6 = 1;
  iVar9 = 0;
  iVar5 = 0;
  uVar8 = 0;
  uVar7 = 0;
  *param_7 = 0;
  *param_6 = 0;
  if (((((int)param_1 < 0) || (param_1 == 1)) || (0x24 < (int)param_1)) || ((int)param_2 < 1)) {
    uVar6 = 0x40;
    uVar2 = param_2;
  }
  else {
    iVar9 = 1;
    uVar2 = (*(code *)param_3)(param_4,0,0);
  }
  if (param_1 != 0) {
    uVar7 = 0xffffffff / param_1;
  }
  do {
    if ((((int)param_2 < iVar9) || (uVar2 == 0xffffffff)) || ((uVar6 & 0x60) != 0)) {
      if ((uVar6 & 0x34) == 0) {
        uVar8 = 0;
        *param_5 = 0;
      }
      else {
        *param_5 = iVar9 + iVar5 + -1;
      }
      (*(code *)param_3)(param_4,uVar2,1);
      return uVar8;
    }
    switch(uVar6) {
    case 1:
      if (((&DAT_803ab570)[uVar2 & 0xff] & 6) == 0) {
        if (uVar2 == 0x2b) {
          iVar9 = iVar9 + 1;
          uVar2 = (*(code *)param_3)(param_4,0,0);
        }
        else if (uVar2 == 0x2d) {
          iVar9 = iVar9 + 1;
          uVar2 = (*(code *)param_3)(param_4,0,0);
          *param_6 = 1;
        }
        uVar6 = 2;
      }
      else {
        uVar2 = (*(code *)param_3)(param_4,0,0);
        iVar5 = iVar5 + 1;
      }
      break;
    case 2:
      if (((param_1 == 0) || (param_1 == 0x10)) && (uVar2 == 0x30)) {
        uVar6 = 4;
        iVar9 = iVar9 + 1;
        uVar2 = (*(code *)param_3)(param_4,0,0);
      }
      else {
        uVar6 = 8;
      }
      break;
    case 4:
      if ((uVar2 == 0x58) || (uVar2 == 0x78)) {
        param_1 = 0x10;
        uVar6 = 8;
        iVar9 = iVar9 + 1;
        uVar2 = (*(code *)param_3)(param_4,0,0);
      }
      else {
        if (param_1 == 0) {
          param_1 = 8;
        }
        uVar6 = 0x10;
      }
      break;
    case 8:
    case 0x10:
      if (param_1 == 0) {
        param_1 = 10;
      }
      if (uVar7 == 0) {
        uVar7 = 0xffffffff / param_1;
      }
      uVar4 = uVar2 & 0xff;
      if (((&DAT_803ab570)[uVar4] & 0x10) == 0) {
        if (((&DAT_803ab570)[uVar4] & 0xc0) != 0) {
          if (uVar2 == 0xffffffff) {
            uVar3 = 0xffffffff;
          }
          else {
            uVar3 = (uint)(byte)(&DAT_803ab770)[uVar4];
          }
          if ((int)(uVar3 - 0x37) < (int)param_1) {
            if (uVar2 == 0xffffffff) {
              uVar4 = 0xffffffff;
            }
            else {
              uVar4 = (uint)(byte)(&DAT_803ab770)[uVar4];
            }
            uVar4 = uVar4 - 0x37;
            goto LAB_80239200;
          }
        }
        if (uVar6 == 0x10) {
          uVar6 = 0x20;
        }
        else {
          uVar6 = 0x40;
        }
      }
      else {
        uVar4 = uVar2 - 0x30;
        if ((int)uVar4 < (int)param_1) {
LAB_80239200:
          if (uVar7 < uVar8) {
            *param_7 = 1;
          }
          if (-(uVar8 * param_1) - 1 < uVar4) {
            *param_7 = 1;
          }
          uVar8 = uVar8 * param_1 + uVar4;
          uVar6 = 0x10;
          iVar9 = iVar9 + 1;
          uVar2 = (*(code *)param_3)(param_4,0,0);
        }
        else {
          bVar1 = uVar6 == 0x10;
          uVar6 = 0x40;
          if (bVar1) {
            uVar6 = 0x20;
          }
        }
      }
    }
  } while( true );
}



// ==== 802392b8  FUN_802392b8 ====

undefined4 FUN_802392b8(undefined4 param_1,byte *param_2,uint *param_3)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = gnt4_OSGetConsoleType_bl();
  if ((uVar1 & 0x20000000) == 0) {
    iVar2 = 0;
    if ((DAT_80436880 == 0) && (iVar2 = zz_020921c_(), iVar2 == 0)) {
      DAT_80436880 = 1;
    }
    if (iVar2 != 0) {
      return 1;
    }
    iVar2 = zz_020928c_(param_2,*param_3);
    if (iVar2 != 0) {
      *param_3 = 0;
      return 1;
    }
  }
  zz_0231d10_(param_1,param_2,param_3);
  return 0;
}



// ==== 80239388  fwide ====

/* WARNING: Removing unreachable block (ram,0x802393c0) */

int fwide(__FILE *__fp,int __mode)

{
  byte bVar1;
  byte bVar2;
  
  if ((__fp == (__FILE *)0x0) || ((*(ushort *)&__fp->_IO_read_ptr >> 6 & 7) == 0)) {
    return 0;
  }
  bVar1 = *(byte *)((int)&__fp->_IO_read_ptr + 1);
  bVar2 = bVar1 >> 4 & 3;
  if (bVar2 == 1) {
    return -1;
  }
  if (bVar2 != 0) {
    if (bVar2 < 3) {
      return 1;
    }
    return (int)__fp;
  }
  if (__mode < 1) {
    if (__mode < 0) {
      *(byte *)((int)&__fp->_IO_read_ptr + 1) = bVar1 & 0xcf | 0x10;
    }
  }
  else {
    *(byte *)((int)&__fp->_IO_read_ptr + 1) = bVar1 & 0xcf | 0x20;
  }
  return __mode;
}



// ==== 80239410  gnt4-__ieee754_acos ====

double gnt4___ieee754_acos(double param_1)

{
  double dVar1;
  double dVar2;
  uint local_18;
  int iStack_14;
  double local_10;
  
  local_18 = (uint)((ulonglong)param_1 >> 0x20);
  local_18 = local_18 & 0x7fffffff;
  if (local_18 < 0x3ff00000) {
    if (local_18 < 0x3fe00000) {
      dVar1 = DOUBLE_8043cc60;
      if (0x3c600000 < local_18) {
        dVar1 = param_1 * param_1;
        dVar1 = DOUBLE_8043cc60 -
                (param_1 -
                -(param_1 * ((dVar1 * (dVar1 * (dVar1 * (dVar1 * (dVar1 * (DOUBLE_8043cc98 * dVar1 +
                                                                          DOUBLE_8043cc90) +
                                                                 DOUBLE_8043cc88) + DOUBLE_8043cc80)
                                               + DOUBLE_8043cc78) + DOUBLE_8043cc70)) /
                            (dVar1 * (dVar1 * (dVar1 * (DOUBLE_8043ccc0 * dVar1 + DOUBLE_8043ccb8) +
                                              DOUBLE_8043ccb0) + DOUBLE_8043cca8) + DOUBLE_8043cca0)
                            ) - DOUBLE_8043cc68));
      }
    }
    else if ((longlong)param_1 < 0) {
      dVar1 = DOUBLE_8043ccc8 * (DOUBLE_8043cca0 + param_1);
      if (dVar1 <= DOUBLE_8043cc50) {
        dVar2 = DOUBLE_8043cc50;
        if (DOUBLE_8043cc50 != dVar1) {
          if (dVar1 == DOUBLE_8043cc50) {
            dVar2 = (double)DAT_80435dcc;
          }
          else {
            dVar2 = (double)DAT_80435dc8;
          }
        }
      }
      else {
        dVar2 = 1.0 / SQRT(dVar1);
        dVar2 = DOUBLE_8043ccc8 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043ccd0);
        dVar2 = DOUBLE_8043ccc8 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043ccd0);
        dVar2 = DOUBLE_8043ccc8 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043ccd0);
        dVar2 = dVar1 * DOUBLE_8043ccc8 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043ccd0);
      }
      dVar1 = -(DOUBLE_8043ccd8 *
                (dVar2 + (((dVar1 * (dVar1 * (dVar1 * (dVar1 * (dVar1 * (DOUBLE_8043cc98 * dVar1 +
                                                                        DOUBLE_8043cc90) +
                                                               DOUBLE_8043cc88) + DOUBLE_8043cc80) +
                                             DOUBLE_8043cc78) + DOUBLE_8043cc70)) /
                          (dVar1 * (dVar1 * (dVar1 * (DOUBLE_8043ccc0 * dVar1 + DOUBLE_8043ccb8) +
                                            DOUBLE_8043ccb0) + DOUBLE_8043cca8) + DOUBLE_8043cca0))
                          * dVar2 - DOUBLE_8043cc68)) - DOUBLE_8043cc58);
    }
    else {
      dVar1 = DOUBLE_8043ccc8 * (DOUBLE_8043cca0 - param_1);
      if (dVar1 <= DOUBLE_8043cc50) {
        dVar2 = DOUBLE_8043cc50;
        if (DOUBLE_8043cc50 != dVar1) {
          if (dVar1 == DOUBLE_8043cc50) {
            dVar2 = (double)DAT_80435dcc;
          }
          else {
            dVar2 = (double)DAT_80435dc8;
          }
        }
      }
      else {
        dVar2 = 1.0 / SQRT(dVar1);
        dVar2 = DOUBLE_8043ccc8 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043ccd0);
        dVar2 = DOUBLE_8043ccc8 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043ccd0);
        dVar2 = DOUBLE_8043ccc8 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043ccd0);
        dVar2 = dVar1 * DOUBLE_8043ccc8 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043ccd0);
      }
      local_10 = (double)((ulonglong)dVar2 & 0xffffffff00000000);
      dVar1 = DOUBLE_8043ccd8 *
              (local_10 +
              ((dVar1 * (dVar1 * (dVar1 * (dVar1 * (dVar1 * (DOUBLE_8043cc98 * dVar1 +
                                                            DOUBLE_8043cc90) + DOUBLE_8043cc88) +
                                          DOUBLE_8043cc80) + DOUBLE_8043cc78) + DOUBLE_8043cc70)) /
              (dVar1 * (dVar1 * (dVar1 * (DOUBLE_8043ccc0 * dVar1 + DOUBLE_8043ccb8) +
                                DOUBLE_8043ccb0) + DOUBLE_8043cca8) + DOUBLE_8043cca0)) * dVar2 +
              -(local_10 * local_10 - dVar1) / (dVar2 + local_10));
    }
  }
  else {
    iStack_14 = SUB84(param_1,0);
    if (local_18 == 0x3ff00000 && iStack_14 == 0) {
      dVar1 = DOUBLE_8043cc58;
      if (0xffffffff < (longlong)param_1) {
        dVar1 = DOUBLE_8043cc50;
      }
    }
    else {
      dVar1 = (double)DAT_80435dc8;
    }
  }
  return dVar1;
}



// ==== 80239720  gnt4-__ieee754_asin ====

double gnt4___ieee754_asin(double param_1,double param_2)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  uint local_18;
  int iStack_14;
  double local_10;
  
  local_18 = (uint)((ulonglong)param_1 >> 0x20);
  local_18 = local_18 & 0x7fffffff;
  if (local_18 < 0x3ff00000) {
    if (local_18 < 0x3fe00000) {
      if (local_18 < 0x3e400000) {
        if (DOUBLE_8043ccf8 < DOUBLE_8043ccf0 + param_1) {
          return param_1;
        }
      }
      else {
        param_2 = param_1 * param_1;
      }
      dVar1 = param_1 * ((param_2 *
                         (param_2 * (param_2 * (param_2 * (param_2 * (DOUBLE_8043cd28 * param_2 +
                                                                     DOUBLE_8043cd20) +
                                                          DOUBLE_8043cd18) + DOUBLE_8043cd10) +
                                    DOUBLE_8043cd08) + DOUBLE_8043cd00)) /
                        (param_2 * (param_2 * (param_2 * (DOUBLE_8043cd48 * param_2 +
                                                         DOUBLE_8043cd40) + DOUBLE_8043cd38) +
                                   DOUBLE_8043cd30) + DOUBLE_8043ccf8)) + param_1;
    }
    else {
      dVar1 = DOUBLE_8043cd50 * (DOUBLE_8043ccf8 - ABS(param_1));
      dVar4 = dVar1 * (dVar1 * (dVar1 * (DOUBLE_8043cd48 * dVar1 + DOUBLE_8043cd40) +
                               DOUBLE_8043cd38) + DOUBLE_8043cd30) + DOUBLE_8043ccf8;
      dVar3 = dVar1 * (dVar1 * (dVar1 * (dVar1 * (dVar1 * (DOUBLE_8043cd28 * dVar1 + DOUBLE_8043cd20
                                                          ) + DOUBLE_8043cd18) + DOUBLE_8043cd10) +
                               DOUBLE_8043cd08) + DOUBLE_8043cd00);
      if (dVar1 <= DOUBLE_8043cd58) {
        dVar2 = DOUBLE_8043cd58;
        if (DOUBLE_8043cd58 != dVar1) {
          if (dVar1 == DOUBLE_8043cd58) {
            dVar2 = (double)DAT_80435dcc;
          }
          else {
            dVar2 = (double)DAT_80435dc8;
          }
        }
      }
      else {
        dVar2 = 1.0 / SQRT(dVar1);
        dVar2 = DOUBLE_8043cd50 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043cd60);
        dVar2 = DOUBLE_8043cd50 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043cd60);
        dVar2 = DOUBLE_8043cd50 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043cd60);
        dVar2 = dVar1 * DOUBLE_8043cd50 * dVar2 * -(dVar1 * dVar2 * dVar2 - DOUBLE_8043cd60);
      }
      if (local_18 < 0x3fef3333) {
        local_10 = (double)((ulonglong)dVar2 & 0xffffffff00000000);
        dVar1 = DOUBLE_8043cd70 -
                ((DOUBLE_8043cd68 * dVar2 * (dVar3 / dVar4) -
                 -(DOUBLE_8043cd68 * (-(local_10 * local_10 - dVar1) / (dVar2 + local_10)) -
                  DOUBLE_8043cce8)) - -(DOUBLE_8043cd68 * local_10 - DOUBLE_8043cd70));
      }
      else {
        dVar1 = DOUBLE_8043cce0 -
                (DOUBLE_8043cd68 * (dVar2 * (dVar3 / dVar4) + dVar2) - DOUBLE_8043cce8);
      }
      if ((longlong)param_1 < 0x100000000) {
        dVar1 = -dVar1;
      }
    }
  }
  else {
    iStack_14 = SUB84(param_1,0);
    if (local_18 == 0x3ff00000 && iStack_14 == 0) {
      dVar1 = DOUBLE_8043cce0 * param_1 + DOUBLE_8043cce8 * param_1;
    }
    else {
      dVar1 = (double)DAT_80435dc8;
    }
  }
  return dVar1;
}



// ==== 80239984  gnt4-__ieee754_atan2 ====

/* WARNING: Removing unreachable block (ram,0x80239af0) */
/* WARNING: Removing unreachable block (ram,0x80239aa8) */
/* WARNING: Removing unreachable block (ram,0x80239ba8) */
/* WARNING: Removing unreachable block (ram,0x80239a34) */

double gnt4___ieee754_atan2(double param_1,double param_2)

{
  uint uVar1;
  uint uVar2;
  double dVar3;
  int iVar4;
  uint uVar5;
  uint local_28;
  uint uStack_24;
  uint local_20;
  uint uStack_1c;
  double local_18;
  
  uStack_1c = SUB84(param_2,0);
  local_20 = (uint)((ulonglong)param_2 >> 0x20);
  uVar1 = local_20 & 0x7fffffff;
  local_28 = (uint)((ulonglong)param_1 >> 0x20);
  uStack_24 = SUB84(param_1,0);
  uVar2 = local_28 & 0x7fffffff;
  if (((uVar1 | (uStack_1c | -uStack_1c) >> 0x1f) < 0x7ff00001) &&
     ((uVar2 | (uStack_24 | -uStack_24) >> 0x1f) < 0x7ff00001)) {
    if (param_2 == 1.0) {
      local_18 = gnt4_atan(param_1);
    }
    else {
      uVar5 = local_28 >> 0x1f | local_20 >> 0x1e & 2;
      if ((((ulonglong)param_1 & 0x7fffffff00000000) != 0 || uStack_24 != 0) ||
         (((local_18 = DOUBLE_8043cd78, uVar5 != 2 && (local_18 = param_1, 1 < uVar5)) &&
          (local_18 = DOUBLE_8043cd80, 3 < uVar5)))) {
        local_18 = DOUBLE_8043cd90;
        if (((ulonglong)param_2 & 0x7fffffff00000000) == 0 && uStack_1c == 0) {
          if ((longlong)param_1 < 0) {
            local_18 = DOUBLE_8043cd88;
          }
        }
        else {
          if (uVar1 == 0x7ff00000) {
            if (uVar2 == 0x7ff00000) {
              if (uVar5 == 2) {
                return DOUBLE_8043cda8;
              }
              dVar3 = DOUBLE_8043cdb0;
              if (uVar5 < 2) {
                if (uVar5 == 0) {
                  return DOUBLE_8043cd98;
                }
                return DOUBLE_8043cda0;
              }
            }
            else {
              if (uVar5 == 2) {
                return DOUBLE_8043cd78;
              }
              dVar3 = DOUBLE_8043cd80;
              if (uVar5 < 2) {
                if (uVar5 == 0) {
                  return DOUBLE_8043cdb8;
                }
                return DOUBLE_8043cdc0;
              }
            }
            if (uVar5 < 4) {
              return dVar3;
            }
          }
          if (uVar2 == 0x7ff00000) {
            if ((longlong)param_1 < 0) {
              local_18 = DOUBLE_8043cd88;
            }
          }
          else {
            iVar4 = (int)(uVar2 - uVar1) >> 0x14;
            if (iVar4 < 0x3d) {
              if (((longlong)param_2 < 0) && (iVar4 < -0x3c)) {
                local_18 = DOUBLE_8043cdb8;
              }
              else {
                local_18 = gnt4_atan(ABS(param_1 / param_2));
              }
            }
            else {
            }
            if (uVar5 == 1) {
              local_18 = -local_18;
            }
            else if (uVar5 != 0) {
              if (uVar5 < 3) {
                local_18 = DOUBLE_8043cd78 - (local_18 - DOUBLE_8043cdc8);
              }
              else {
                local_18 = (local_18 - DOUBLE_8043cdc8) - DOUBLE_8043cd78;
              }
            }
          }
        }
      }
    }
  }
  else {
    local_18 = param_2 + param_1;
  }
  return local_18;
}



// ==== 80239c14  gnt4-__ieee754_exp ====

double gnt4___ieee754_exp(double param_1)

{
  uint uVar1;
  int iVar2;
  uint in_r6;
  double dVar3;
  double in_f7;
  double in_f8;
  undefined8 local_28;
  undefined8 local_20;
  
  local_28._0_4_ = (uint)((ulonglong)param_1 >> 0x20);
  uVar1 = local_28._0_4_ & 0x7fffffff;
  iVar2 = (int)local_28._0_4_ >> 0x1f;
  if (0x40862e41 < uVar1) {
    if (0x7fefffff < uVar1) {
      local_28._4_4_ = SUB84(param_1,0);
      if (((ulonglong)param_1 & 0xfffff00000000) != 0 || local_28._4_4_ != 0) {
        return param_1 + param_1;
      }
      if ((longlong)param_1 < 0) {
        return DOUBLE_8043cdd0;
      }
      return param_1;
    }
    if (DOUBLE_8043cdd8 < param_1) {
      return DOUBLE_8043cde0;
    }
    if (param_1 < DOUBLE_8043cde8) {
      return DOUBLE_8043cdd0;
    }
  }
  if (uVar1 < 0x3fd62e43) {
    local_28 = param_1;
    if (uVar1 < 0x3e300000) {
      if (DOUBLE_8043ce00 < DOUBLE_8043cdf8 + param_1) {
        return DOUBLE_8043ce00 + param_1;
      }
    }
    else {
      in_r6 = 0;
    }
  }
  else {
    if (uVar1 < 0x3ff0a2b2) {
      in_r6 = iVar2 * 2 + 1;
      in_f8 = (&DAT_802b4ed8)[-iVar2];
      in_f7 = param_1 - (&DAT_802b4ec8)[-iVar2];
    }
    else {
      in_r6 = (uint)(DOUBLE_8043cdf0 * param_1 + *(double *)(&DAT_802b4eb8 + iVar2 * -8));
      dVar3 = (double)CONCAT44(0x43300000,in_r6 ^ 0x80000000) - DOUBLE_8043ce40;
      in_f7 = -(dVar3 * DAT_802b4ec8 - param_1);
      in_f8 = dVar3 * DAT_802b4ed8;
    }
    local_28 = in_f7 - in_f8;
  }
  dVar3 = local_28 * local_28;
  dVar3 = -(dVar3 * (dVar3 * (dVar3 * (dVar3 * (DOUBLE_8043ce28 * dVar3 + DOUBLE_8043ce20) +
                                      DOUBLE_8043ce18) + DOUBLE_8043ce10) + DOUBLE_8043ce08) -
           local_28);
  if (in_r6 == 0) {
    local_20 = DOUBLE_8043ce00 - ((local_28 * dVar3) / (dVar3 - DOUBLE_8043ce30) - local_28);
  }
  else {
    dVar3 = DOUBLE_8043ce00 - ((in_f8 - (local_28 * dVar3) / (DOUBLE_8043ce30 - dVar3)) - in_f7);
    local_20._4_4_ = SUB84(dVar3,0);
    local_20._0_4_ = (int)((ulonglong)dVar3 >> 0x20);
    if ((int)in_r6 < -0x3fd) {
      local_20 = (double)CONCAT44(local_20._0_4_ + (in_r6 + 1000) * 0x100000,local_20._4_4_);
      local_20 = DOUBLE_8043ce38 * local_20;
    }
    else {
      local_20 = (double)CONCAT44(local_20._0_4_ + in_r6 * 0x100000,local_20._4_4_);
    }
  }
  return local_20;
}



// ==== 80239e38  gnt4-__ieee754_fmod ====

double gnt4___ieee754_fmod(double param_1,double param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  undefined8 local_18;
  uint local_10;
  uint uStack_c;
  
  local_10 = (uint)((ulonglong)param_2 >> 0x20);
  local_18._0_4_ = (uint)((ulonglong)param_1 >> 0x20);
  uStack_c = SUB84(param_2,0);
  uVar7 = local_10 & 0x7fffffff;
  uVar1 = local_18._0_4_ & 0x80000000;
  local_18._4_4_ = SUB84(param_1,0);
  uVar4 = local_18._0_4_ ^ uVar1;
  if (((((ulonglong)param_2 & 0x7fffffff00000000) == 0 && uStack_c == 0) ||
      (0x7fefffff < (int)uVar4)) || (0x7ff00000 < (uVar7 | (uStack_c | -uStack_c) >> 0x1f))) {
    return (param_1 * param_2) / (param_1 * param_2);
  }
  if ((int)uVar4 <= (int)uVar7) {
    if ((int)uVar4 < (int)uVar7) {
      return param_1;
    }
    if (local_18._4_4_ < uStack_c) {
      return param_1;
    }
    if (local_18._4_4_ == uStack_c) {
      return *(double *)(&DAT_802b4ee8 + (uVar1 >> 0x1c));
    }
  }
  if ((int)uVar4 < 0x100000) {
    if (uVar4 == 0) {
      iVar8 = -0x413;
      for (uVar6 = local_18._4_4_; 0 < (int)uVar6; uVar6 = uVar6 << 1) {
        iVar8 = iVar8 + -1;
      }
    }
    else {
      iVar8 = -0x3fe;
      for (iVar2 = local_18._0_4_ << 0xb; 0 < iVar2; iVar2 = iVar2 << 1) {
        iVar8 = iVar8 + -1;
      }
    }
  }
  else {
    iVar8 = ((int)uVar4 >> 0x14) + -0x3ff;
  }
  if (uVar7 < 0x100000) {
    if (((ulonglong)param_2 & 0x7fffffff00000000) == 0) {
      iVar2 = -0x413;
      for (uVar6 = uStack_c; 0 < (int)uVar6; uVar6 = uVar6 << 1) {
        iVar2 = iVar2 + -1;
      }
    }
    else {
      iVar2 = -0x3fe;
      for (iVar5 = local_10 << 0xb; 0 < iVar5; iVar5 = iVar5 << 1) {
        iVar2 = iVar2 + -1;
      }
    }
  }
  else {
    iVar2 = ((int)uVar7 >> 0x14) + -0x3ff;
  }
  if (iVar8 < -0x3fe) {
    iVar5 = -iVar8 + -0x3fe;
    if (iVar5 < 0x20) {
      uVar6 = local_18._4_4_ >> 0x20 - iVar5;
      local_18._4_4_ = local_18._4_4_ << iVar5;
      uVar6 = uVar4 << iVar5 | uVar6;
    }
    else {
      uVar6 = local_18._4_4_ << -iVar8 + -0x41e;
      local_18._4_4_ = 0;
    }
  }
  else {
    uVar6 = uVar4 & 0xfffff | 0x100000;
  }
  if (iVar2 < -0x3fe) {
    iVar5 = -iVar2 + -0x3fe;
    if (iVar5 < 0x20) {
      uVar4 = uStack_c >> 0x20 - iVar5;
      uStack_c = uStack_c << iVar5;
      uVar4 = uVar7 << iVar5 | uVar4;
    }
    else {
      uVar4 = uStack_c << -iVar2 + -0x41e;
      uStack_c = 0;
    }
  }
  else {
    uVar4 = local_10 & 0xfffff | 0x100000;
  }
  iVar8 = iVar8 - iVar2;
  do {
    if (iVar8 == 0) {
      uVar4 = uVar6 - uVar4;
      if (local_18._4_4_ < uStack_c) {
        uVar4 = uVar4 - 1;
      }
      if (-1 < (int)uVar4) {
        local_18._4_4_ = local_18._4_4_ - uStack_c;
        uVar6 = uVar4;
      }
      if (uVar6 == 0 && local_18._4_4_ == 0) {
        local_18 = *(double *)(&DAT_802b4ee8 + (uVar1 >> 0x1c));
      }
      else {
        for (; (int)uVar6 < 0x100000; uVar6 = uVar6 * 2 - iVar8) {
          iVar8 = (int)local_18._4_4_ >> 0x1f;
          local_18._4_4_ = local_18._4_4_ * 2;
          iVar2 = iVar2 + -1;
        }
        if (iVar2 < -0x3fe) {
          uVar7 = -iVar2 - 0x3fe;
          if ((int)uVar7 < 0x15) {
            uVar3 = local_18._4_4_ >> uVar7 | uVar6 << 0x20 - uVar7;
            uVar4 = (int)uVar6 >> (uVar7 & 0x3f);
          }
          else {
            uVar4 = uVar1;
            if ((int)uVar7 < 0x20) {
              uVar3 = uVar6 << 0x20 - uVar7 | local_18._4_4_ >> uVar7;
            }
            else {
              uVar3 = (int)uVar6 >> (-iVar2 - 0x41eU & 0x3f);
            }
          }
          local_18 = (double)CONCAT44(uVar4 | uVar1,uVar3);
        }
        else {
          local_18 = (double)CONCAT44(uVar6 - 0x100000 | (iVar2 + 0x3ff) * 0x100000 | uVar1,
                                      local_18._4_4_);
        }
      }
      return local_18;
    }
    iVar5 = uVar6 - uVar4;
    uVar7 = local_18._4_4_ - uStack_c;
    if (local_18._4_4_ < uStack_c) {
      iVar5 = iVar5 + -1;
    }
    if (iVar5 < 0) {
      uVar6 = uVar6 * 2 - ((int)local_18._4_4_ >> 0x1f);
      uVar7 = local_18._4_4_;
    }
    else {
      if (iVar5 == 0 && uVar7 == 0) {
        return *(double *)(&DAT_802b4ee8 + (uVar1 >> 0x1c));
      }
      uVar6 = iVar5 * 2 - ((int)uVar7 >> 0x1f);
    }
    local_18._4_4_ = uVar7 * 2;
    iVar8 = iVar8 + -1;
  } while( true );
}



// ==== 8023a174  gnt4-__ieee754_log ====

double gnt4___ieee754_log(double param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  undefined8 local_18;
  
  iVar2 = 0;
  local_18._0_4_ = (uint)((ulonglong)param_1 >> 0x20);
  local_18._4_4_ = SUB84(param_1,0);
  uVar3 = local_18._0_4_;
  dVar4 = param_1;
  if ((longlong)param_1 < 0x10000000000000) {
    if (((ulonglong)param_1 & 0x7fffffff00000000) == 0 && local_18._4_4_ == 0) {
      return DOUBLE_8043ce48 / DOUBLE_80436888;
    }
    if ((longlong)param_1 < 0) {
      DAT_80436878 = 0x21;
      return (param_1 - param_1) / DOUBLE_80436888;
    }
    iVar2 = -0x36;
    local_18._0_4_ = (uint)((ulonglong)(param_1 * DOUBLE_8043ce50) >> 0x20);
    uVar3 = local_18._0_4_;
    dVar4 = param_1 * DOUBLE_8043ce50;
  }
  local_18 = dVar4;
  if ((int)uVar3 < 0x7ff00000) {
    uVar1 = uVar3 & 0xfffff;
    local_18 = (double)CONCAT44(uVar1 | uVar1 + 0x95f64 & 0x100000 ^ 0x3ff00000,local_18._4_4_);
    uVar3 = ((int)uVar3 >> 0x14) + iVar2 + -0x3ff + (uVar1 + 0x95f64 >> 0x14);
    local_18 = local_18 - DOUBLE_8043ce58;
    if ((uVar1 + 2 & 0xfffff) < 3) {
      if (local_18 == DOUBLE_80436888) {
        dVar4 = DOUBLE_80436888;
        if (uVar3 != 0) {
          dVar4 = (double)CONCAT44(0x43300000,uVar3 ^ 0x80000000) - DOUBLE_8043cec0;
          dVar4 = DOUBLE_8043ce60 * dVar4 + DOUBLE_8043ce68 * dVar4;
        }
      }
      else {
        dVar4 = -(DOUBLE_8043ce78 * local_18 - DOUBLE_8043ce70) * local_18 * local_18;
        if (uVar3 == 0) {
          dVar4 = local_18 - dVar4;
        }
        else {
          dVar5 = (double)CONCAT44(0x43300000,uVar3 ^ 0x80000000) - DOUBLE_8043cec0;
          dVar4 = DOUBLE_8043ce60 * dVar5 - (-(DOUBLE_8043ce68 * dVar5 - dVar4) - local_18);
        }
      }
    }
    else {
      dVar4 = local_18 / (DOUBLE_8043ce80 + local_18);
      dVar5 = dVar4 * dVar4;
      dVar7 = dVar5 * dVar5;
      dVar6 = (double)CONCAT44(0x43300000,uVar3 ^ 0x80000000) - DOUBLE_8043cec0;
      dVar5 = dVar5 * (dVar7 * (dVar7 * (DOUBLE_8043cea0 * dVar7 + DOUBLE_8043ce98) +
                               DOUBLE_8043ce90) + DOUBLE_8043ce88) +
              dVar7 * (dVar7 * (DOUBLE_8043ceb8 * dVar7 + DOUBLE_8043ceb0) + DOUBLE_8043cea8);
      if ((int)(uVar1 - 0x6147a | 0x6b851 - uVar1) < 1) {
        if (uVar3 == 0) {
          dVar4 = -(dVar4 * (local_18 - dVar5) - local_18);
        }
        else {
          dVar4 = DOUBLE_8043ce60 * dVar6 -
                  ((dVar4 * (local_18 - dVar5) - DOUBLE_8043ce68 * dVar6) - local_18);
        }
      }
      else {
        dVar7 = DOUBLE_8043ce70 * local_18 * local_18;
        if (uVar3 == 0) {
          dVar4 = local_18 - -(dVar4 * (dVar7 + dVar5) - dVar7);
        }
        else {
          dVar4 = DOUBLE_8043ce60 * dVar6 -
                  ((dVar7 - (dVar4 * (dVar7 + dVar5) + DOUBLE_8043ce68 * dVar6)) - local_18);
        }
      }
    }
  }
  else {
    dVar4 = local_18 + local_18;
  }
  return dVar4;
}



// ==== 8023a3f0  gnt4-__ieee754_pow ====

/* WARNING: Removing unreachable block (ram,0x8023ac8c) */
/* WARNING: Removing unreachable block (ram,0x8023ac84) */
/* WARNING: Removing unreachable block (ram,0x8023ac7c) */
/* WARNING: Removing unreachable block (ram,0x8023ac74) */
/* WARNING: Removing unreachable block (ram,0x8023ac6c) */
/* WARNING: Removing unreachable block (ram,0x8023a420) */
/* WARNING: Removing unreachable block (ram,0x8023a418) */
/* WARNING: Removing unreachable block (ram,0x8023a410) */
/* WARNING: Removing unreachable block (ram,0x8023a408) */
/* WARNING: Removing unreachable block (ram,0x8023a400) */

double gnt4___ieee754_pow(double param_1,double param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  uint local_a8;
  int iStack_a4;
  uint local_a0;
  uint uStack_9c;
  undefined8 local_98;
  double local_90;
  undefined8 local_88;
  double local_80;
  double local_78;
  double local_70;
  double local_68;
  undefined8 local_60;
  
  local_a0 = (uint)((ulonglong)param_2 >> 0x20);
  uStack_9c = SUB84(param_2,0);
  uVar3 = local_a0 & 0x7fffffff;
  local_a8 = (uint)((ulonglong)param_1 >> 0x20);
  iStack_a4 = SUB84(param_1,0);
  local_a8 = local_a8 & 0x7fffffff;
  local_60 = DOUBLE_8043cec8;
  if (((ulonglong)param_2 & 0x7fffffff00000000) != 0 || uStack_9c != 0) {
    if (((local_a8 < 0x7ff00001) &&
        (((local_a8 != 0x7ff00000 || (iStack_a4 == 0)) && (uVar3 < 0x7ff00001)))) &&
       ((uVar3 != 0x7ff00000 || (uStack_9c == 0)))) {
      iVar2 = 0;
      if ((longlong)param_1 < 0) {
        if (uVar3 < 0x43400000) {
          if (0x3fefffff < uVar3) {
            iVar5 = ((int)uVar3 >> 0x14) + -0x3ff;
            if (iVar5 < 0x15) {
              if ((uStack_9c == 0) &&
                 (uVar4 = (int)uVar3 >> (0x14U - iVar5 & 0x3f), uVar3 == uVar4 << 0x14U - iVar5)) {
                iVar2 = 2 - (uVar4 & 1);
              }
            }
            else {
              uVar4 = uStack_9c >> 0x34 - iVar5;
              if (uStack_9c == uVar4 << 0x34 - iVar5) {
                iVar2 = 2 - (uVar4 & 1);
              }
            }
          }
        }
        else {
          iVar2 = 2;
        }
      }
      if (uStack_9c == 0) {
        if (uVar3 == 0x7ff00000) {
          if (local_a8 == 0x3ff00000 && iStack_a4 == 0) {
            return param_2 - param_2;
          }
          if (0x3fefffff < local_a8) {
            if ((longlong)param_2 < 0) {
              return DOUBLE_8043ced0;
            }
            return param_2;
          }
          if (-1 < (longlong)param_2) {
            return DOUBLE_8043ced0;
          }
          return -param_2;
        }
        if (uVar3 == 0x3ff00000) {
          if (-1 < (longlong)param_2) {
            return param_1;
          }
          return DOUBLE_8043cec8 / param_1;
        }
        if (local_a0 == 0x40000000) {
          return param_1 * param_1;
        }
        if ((local_a0 == 0x3fe00000) && (-1 < (longlong)param_1)) {
          if (DOUBLE_8043ced0 < param_1) {
            dVar8 = 1.0 / SQRT(param_1);
            dVar8 = DOUBLE_8043ced8 * dVar8 * -(param_1 * dVar8 * dVar8 - DOUBLE_8043cee0);
            dVar8 = DOUBLE_8043ced8 * dVar8 * -(param_1 * dVar8 * dVar8 - DOUBLE_8043cee0);
            dVar8 = DOUBLE_8043ced8 * dVar8 * -(param_1 * dVar8 * dVar8 - DOUBLE_8043cee0);
            return param_1 * DOUBLE_8043ced8 * dVar8 * -(param_1 * dVar8 * dVar8 - DOUBLE_8043cee0);
          }
          if (DOUBLE_8043ced0 == param_1) {
            return DOUBLE_8043ced0;
          }
          if (param_1 != DOUBLE_8043ced0) {
            return (double)DAT_80435dc8;
          }
          return (double)DAT_80435dcc;
        }
      }
      local_60 = ABS(param_1);
      if ((iStack_a4 == 0) &&
         (((local_a8 == 0x7ff00000 || (((ulonglong)param_1 & 0x7fffffff00000000) == 0)) ||
          (local_a8 == 0x3ff00000)))) {
        if ((longlong)param_2 < 0) {
          local_60 = DOUBLE_8043cec8 / local_60;
        }
        if ((longlong)param_1 < 0) {
          if (local_a8 == 0x3ff00000 && iVar2 == 0) {
            local_60 = (local_60 - local_60) / (local_60 - local_60);
          }
          else if (iVar2 == 1) {
            local_60 = -local_60;
          }
        }
      }
      else if ((longlong)param_1 < 0 && iVar2 == 0) {
        DAT_80436878 = 0x21;
        local_60 = (double)DAT_80435dc8;
      }
      else {
        local_98._4_4_ = SUB84(DOUBLE_8043ced0,0);
        uVar1 = local_98._4_4_;
        if (uVar3 < 0x41e00001) {
          iVar5 = 0;
          local_68 = local_60;
          if (local_a8 < 0x100000) {
            iVar5 = -0x35;
            local_68._0_4_ = (uint)((ulonglong)(local_60 * DOUBLE_8043cf18) >> 0x20);
            local_a8 = local_68._0_4_;
            local_68 = local_60 * DOUBLE_8043cf18;
          }
          uVar3 = local_a8 & 0xfffff;
          uVar4 = uVar3 | 0x3ff00000;
          iVar5 = ((int)local_a8 >> 0x14) + iVar5;
          uVar6 = iVar5 - 0x3ff;
          if (uVar3 < 0x3988f) {
            iVar7 = 0;
          }
          else if (uVar3 < 0xbb67a) {
            iVar7 = 1;
          }
          else {
            uVar4 = uVar4 - 0x100000;
            iVar7 = 0;
            uVar6 = iVar5 - 0x3fe;
          }
          local_68 = (double)CONCAT44(uVar4,local_68._4_4_);
          dVar9 = (double)(&DAT_802b4ef8)[iVar7];
          dVar10 = DOUBLE_8043cec8 / (local_68 + dVar9);
          dVar8 = (local_68 - dVar9) * dVar10;
          local_98 = (double)CONCAT44(((int)uVar4 >> 1 | 0x20000000U) + 0x80000 + iVar7 * 0x40000,
                                      local_98._4_4_);
          dVar11 = dVar8 * dVar8;
          local_90 = (double)((ulonglong)dVar8 & 0xffffffff00000000);
          dVar10 = dVar10 * -(local_90 * (local_68 - (local_98 - dVar9)) -
                             -(local_90 * local_98 - (local_68 - dVar9)));
          dVar9 = (double)CONCAT44(0x43300000,uVar6 ^ 0x80000000) - DOUBLE_8043cfd0;
          dVar11 = dVar10 * (local_90 + dVar8) +
                   dVar11 * dVar11 *
                   (dVar11 * (dVar11 * (dVar11 * (dVar11 * (DOUBLE_8043cf48 * dVar11 +
                                                           DOUBLE_8043cf40) + DOUBLE_8043cf38) +
                                       DOUBLE_8043cf30) + DOUBLE_8043cf28) + DOUBLE_8043cf20);
          local_98 = (double)((ulonglong)(DOUBLE_8043cee0 + local_90 * local_90 + dVar11) &
                             0xffffffff00000000);
          dVar8 = dVar10 * local_98 +
                  (dVar11 - ((local_98 - DOUBLE_8043cee0) - local_90 * local_90)) * dVar8;
          local_70 = (double)((ulonglong)(local_90 * local_98 + dVar8) & 0xffffffff00000000);
          dVar8 = (double)(&DAT_802b4f18)[iVar7] +
                  DOUBLE_8043cf58 * local_70 +
                  DOUBLE_8043cf60 * (dVar8 - (local_70 - local_90 * local_98));
          local_80 = (double)((ulonglong)
                              (dVar9 + DOUBLE_8043cf50 * local_70 + dVar8 +
                                       (double)(&DAT_802b4f08)[iVar7]) & 0xffffffff00000000);
          dVar8 = dVar8 - (((local_80 - dVar9) - (double)(&DAT_802b4f08)[iVar7]) -
                          DOUBLE_8043cf50 * local_70);
        }
        else {
          if (0x43f00000 < uVar3) {
            if (local_a8 < 0x3ff00000) {
              if (-1 < (longlong)param_2) {
                return DOUBLE_8043ced0;
              }
              return DOUBLE_8043cee8;
            }
            if (0x3fefffff < local_a8) {
              if ((longlong)param_2 < 0x100000000) {
                return DOUBLE_8043ced0;
              }
              return DOUBLE_8043cee8;
            }
          }
          if (local_a8 < 0x3fefffff) {
            if (-1 < (longlong)param_2) {
              return DOUBLE_8043ced0;
            }
            return DOUBLE_8043cee8;
          }
          if (0x3ff00000 < local_a8) {
            if ((longlong)param_2 < 0x100000000) {
              return DOUBLE_8043ced0;
            }
            return DOUBLE_8043cee8;
          }
          dVar9 = param_1 - DOUBLE_8043cec8;
          dVar8 = DOUBLE_8043cf08 * dVar9 -
                  DOUBLE_8043cf10 *
                  dVar9 * dVar9 *
                  -(dVar9 * -(DOUBLE_8043cef8 * dVar9 - DOUBLE_8043cef0) - DOUBLE_8043ced8);
          local_80 = (double)((ulonglong)(DOUBLE_8043cf00 * dVar9 + dVar8) & 0xffffffff00000000);
          dVar8 = dVar8 - (local_80 - DOUBLE_8043cf00 * dVar9);
        }
        dVar9 = DOUBLE_8043cec8;
        if ((longlong)param_1 < 0 && iVar2 == 1) {
          dVar9 = DOUBLE_8043cf68;
        }
        local_78 = (double)((ulonglong)param_2 & 0xffffffff00000000);
        local_70 = local_78 * local_80;
        dVar11 = local_80 * (param_2 - local_78) + param_2 * dVar8;
        dVar8 = dVar11 + local_70;
        local_60._0_4_ = (uint)((ulonglong)dVar8 >> 0x20);
        if ((longlong)dVar8 < 0x4090000000000000) {
          if (0x4090cbff < (local_60._0_4_ & 0x7fffffff)) {
            if (dVar8 != -1075.0) {
              return DOUBLE_8043cf80 * DOUBLE_8043cf80 * dVar9;
            }
            if (dVar11 <= -1075.0 - local_70) {
              return DOUBLE_8043cf80 * DOUBLE_8043cf80 * dVar9;
            }
          }
        }
        else {
          if (dVar8 != 1024.0) {
            return DOUBLE_8043cf70 * DOUBLE_8043cf70 * dVar9;
          }
          if (1024.0 - local_70 < DOUBLE_8043cf78 + dVar11) {
            return DOUBLE_8043cf70 * DOUBLE_8043cf70 * dVar9;
          }
        }
        iVar2 = 0;
        if (0x3fe00000 < (local_60._0_4_ & 0x7fffffff)) {
          local_60._0_4_ =
               local_60._0_4_ + (0x100000 >> ((local_60._0_4_ >> 0x14 & 0x7ff) - 0x3fe & 0x3f));
          uVar3 = ((int)(local_60._0_4_ & 0x7fffffff) >> 0x14) - 0x3ff;
          local_88 = (double)CONCAT44(local_60._0_4_ & ~(0xfffff >> (uVar3 & 0x3f)),uVar1);
          iVar2 = (int)(local_60._0_4_ & 0xfffff | 0x100000) >> (0x14 - uVar3 & 0x3f);
          if ((longlong)dVar8 < 0) {
            iVar2 = -iVar2;
          }
          local_70 = local_70 - local_88;
        }
        local_88 = (double)((ulonglong)(dVar11 + local_70) & 0xffffffff00000000);
        dVar11 = DOUBLE_8043cf90 * (dVar11 - (local_88 - local_70)) + DOUBLE_8043cf98 * local_88;
        dVar10 = DOUBLE_8043cf88 * local_88 + dVar11;
        dVar8 = dVar10 * dVar10;
        dVar11 = dVar11 - (dVar10 - DOUBLE_8043cf88 * local_88);
        dVar8 = dVar10 - dVar8 * (dVar8 * (dVar8 * (dVar8 * (DOUBLE_8043cfc0 * dVar8 +
                                                            DOUBLE_8043cfb8) + DOUBLE_8043cfb0) +
                                          DOUBLE_8043cfa8) + DOUBLE_8043cfa0);
        dVar8 = DOUBLE_8043cec8 -
                (((dVar10 * dVar8) / (dVar8 - DOUBLE_8043cfc8) - (dVar10 * dVar11 + dVar11)) -
                dVar10);
        local_60._0_4_ = (uint)((ulonglong)dVar8 >> 0x20);
        if ((int)(local_60._0_4_ + iVar2 * 0x100000) >> 0x14 < 1) {
          local_60 = ldexp(dVar8,iVar2);
        }
        else {
          local_60 = (double)CONCAT44(local_60._0_4_ + iVar2 * 0x100000,SUB84(dVar8,0));
        }
        local_60 = dVar9 * local_60;
      }
    }
    else {
      local_60 = param_1 + param_2;
    }
  }
  return local_60;
}



// ==== 8023aca4  gnt4-__ieee754_rem_pio2-bl ====

/* WARNING: Type propagation algorithm not settling */

int gnt4___ieee754_rem_pio2_bl(double param_1,double *param_2)

{
  int iVar1;
  int iVar2;
  double *pdVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  uint local_58;
  double local_48;
  double local_40;
  double local_38 [3];
  longlong local_20;
  undefined4 local_18;
  uint uStack_14;
  
  dVar5 = DOUBLE_8043cff8;
  dVar7 = DOUBLE_8043cfe8;
  local_58 = (uint)((ulonglong)param_1 >> 0x20);
  local_58 = local_58 & 0x7fffffff;
  if (local_58 < 0x3fe921fc) {
    *param_2 = param_1;
    iVar1 = 0;
    param_2[1] = DOUBLE_8043cfd8;
  }
  else if (local_58 < 0x4002d97c) {
    if ((longlong)param_1 < 0x100000000) {
      dVar6 = DOUBLE_8043cfe0 + param_1;
      if (local_58 == 0x3ff921fb) {
        dVar6 = dVar6 + DOUBLE_8043cff0;
        *param_2 = DOUBLE_8043cff8 + dVar6;
        param_2[1] = dVar5 + (dVar6 - *param_2);
      }
      else {
        *param_2 = DOUBLE_8043cfe8 + dVar6;
        param_2[1] = dVar7 + (dVar6 - *param_2);
      }
      iVar1 = -1;
    }
    else {
      dVar6 = param_1 - DOUBLE_8043cfe0;
      if (local_58 == 0x3ff921fb) {
        dVar6 = dVar6 - DOUBLE_8043cff0;
        *param_2 = dVar6 - DOUBLE_8043cff8;
        param_2[1] = (dVar6 - *param_2) - dVar5;
      }
      else {
        *param_2 = dVar6 - DOUBLE_8043cfe8;
        param_2[1] = (dVar6 - *param_2) - dVar7;
      }
      iVar1 = 1;
    }
  }
  else {
    iVar2 = (int)local_58 >> 0x14;
    if (local_58 < 0x413921fc) {
      iVar1 = (int)(DOUBLE_8043d008 * ABS(param_1) + DOUBLE_8043d000);
      local_38[2] = (double)(CONCAT44(0x43300000,iVar1) ^ 0x80000000);
      local_38[2] = local_38[2] - DOUBLE_8043d028;
      dVar7 = -(DOUBLE_8043cfe0 * local_38[2] - ABS(param_1));
      dVar5 = DOUBLE_8043cfe8 * local_38[2];
      if ((iVar1 < 0x20) && (local_58 != *(uint *)(&DAT_802b502c + iVar1 * 4))) {
        *param_2 = dVar7 - dVar5;
      }
      else {
        *param_2 = dVar7 - dVar5;
        if (0x10 < (int)(iVar2 - (*(uint *)param_2 >> 0x14 & 0x7ff))) {
          dVar6 = dVar7 - DOUBLE_8043cff0 * local_38[2];
          dVar5 = DOUBLE_8043cff8 * local_38[2] - ((dVar7 - dVar6) - DOUBLE_8043cff0 * local_38[2]);
          *param_2 = dVar6 - dVar5;
          dVar7 = dVar6;
          if (0x31 < (int)(iVar2 - (*(uint *)param_2 >> 0x14 & 0x7ff))) {
            dVar7 = dVar6 - DOUBLE_8043d010 * local_38[2];
            dVar5 = DOUBLE_8043d018 * local_38[2] -
                    ((dVar6 - dVar7) - DOUBLE_8043d010 * local_38[2]);
            *param_2 = dVar7 - dVar5;
          }
        }
      }
      param_2[1] = (dVar7 - *param_2) - dVar5;
      if ((longlong)param_1 < 0) {
        iVar1 = -iVar1;
        *param_2 = -*param_2;
        param_2[1] = -param_2[1];
      }
    }
    else if (local_58 < 0x7ff00000) {
      iVar4 = 3;
      dVar7 = (double)CONCAT44(local_58 + (iVar2 + -0x416) * -0x100000,SUB84(param_1,0));
      local_18 = 0x43300000;
      iVar1 = (int)dVar7;
      local_38[2] = (double)(longlong)iVar1;
      local_38[1] = (double)(CONCAT44(0x43300000,iVar1) ^ 0x80000000);
      local_48 = local_38[1] - DOUBLE_8043d028;
      dVar7 = DOUBLE_8043d020 * (dVar7 - local_48);
      uStack_14 = (uint)dVar7;
      local_20 = (longlong)(int)uStack_14;
      uStack_14 = uStack_14 ^ 0x80000000;
      local_40 = (double)CONCAT44(0x43300000,uStack_14) - DOUBLE_8043d028;
      local_38[0] = DOUBLE_8043d020 * (dVar7 - local_40);
      for (pdVar3 = local_38 + 1; DOUBLE_8043cfd8 == pdVar3[0xffffffff];
          pdVar3 = pdVar3 + 0xffffffff) {
        iVar4 = iVar4 + -1;
      }
      iVar1 = gnt4___kernel_rem_pio2(&local_48,param_2,iVar2 + -0x416,iVar4,2,-0x7fd4b0d8);
      if ((longlong)param_1 < 0) {
        iVar1 = -iVar1;
        *param_2 = -*param_2;
        param_2[1] = -param_2[1];
      }
    }
    else {
      iVar1 = 0;
      param_2[1] = param_1 - param_1;
      *param_2 = param_1 - param_1;
    }
  }
  return iVar1;
}



// ==== 8023b044  gnt4-__kernel_cos ====

double gnt4___kernel_cos(double param_1,double param_2)

{
  double dVar1;
  double dVar2;
  undefined4 local_18;
  undefined8 local_10;
  
  local_18 = (uint)((ulonglong)param_1 >> 0x20);
  local_18 = local_18 & 0x7fffffff;
  if ((0x3e3fffff < local_18) || (dVar1 = DOUBLE_8043d030, (int)param_1 != 0)) {
    dVar2 = param_1 * param_1;
    dVar1 = dVar2 * (dVar2 * (dVar2 * (dVar2 * (dVar2 * (DOUBLE_8043d060 * dVar2 + DOUBLE_8043d058)
                                               + DOUBLE_8043d050) + DOUBLE_8043d048) +
                             DOUBLE_8043d040) + DOUBLE_8043d038);
    if (local_18 < 0x3fd33333) {
      dVar1 = DOUBLE_8043d030 - (DOUBLE_8043d068 * dVar2 - (dVar2 * dVar1 - param_1 * param_2));
    }
    else {
      if (local_18 < 0x3fe90001) {
        local_10 = (double)((ulonglong)(local_18 - 0x200000) << 0x20);
      }
      else {
        local_10 = DOUBLE_8043d070;
      }
      dVar1 = (DOUBLE_8043d030 - local_10) -
              ((DOUBLE_8043d068 * dVar2 - local_10) - (dVar2 * dVar1 - param_1 * param_2));
    }
  }
  return dVar1;
}



// ==== 8023b138  gnt4-__kernel_rem_pio2 ====

void gnt4___kernel_rem_pio2
               (undefined4 param_1,undefined4 param_2,int param_3,int param_4,int param_5,
               int param_6)

{
  double *pdVar1;
  double *pdVar2;
  double *pdVar3;
  double *pdVar4;
  double *pdVar5;
  double *pdVar6;
  double *pdVar7;
  uint *puVar8;
  uint *puVar9;
  uint *puVar10;
  uint *puVar11;
  uint *puVar12;
  uint *puVar13;
  uint *puVar14;
  bool bVar15;
  int iVar16;
  int iVar17;
  uint uVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  uint uVar23;
  uint *puVar24;
  double *pdVar25;
  undefined4 *puVar26;
  uint *puVar27;
  double *pdVar28;
  double *pdVar29;
  double *pdVar30;
  int iVar31;
  int iVar32;
  int iVar33;
  int iVar34;
  int iVar35;
  int iVar36;
  int iVar37;
  int __exponent;
  uint uVar38;
  int iVar39;
  uint uVar40;
  uint uVar41;
  uint uVar42;
  double dVar43;
  double dVar44;
  double dVar45;
  double dVar46;
  double dVar47;
  double dVar48;
  double dVar49;
  double dVar50;
  double dVar51;
  double dVar52;
  undefined8 uVar53;
  uint auStack_2cc [21];
  double local_278 [20];
  double local_1d8 [20];
  double local_138 [20];
  double local_98;
  undefined4 local_90;
  uint uStack_8c;
  double local_88;
  undefined8 local_80;
  
  uVar53 = zz_0232a10_();
  pdVar29 = (double *)((ulonglong)uVar53 >> 0x20);
  pdVar25 = (double *)uVar53;
  uVar38 = *(uint *)(&DAT_802b50b0 + param_5 * 4);
  iVar16 = (param_3 + -3) / 0x18 + (param_3 + -3 >> 0x1f);
  iVar39 = param_4 + -1;
  iVar16 = iVar16 - (iVar16 >> 0x1f);
  if (iVar16 < 0) {
    iVar16 = 0;
  }
  iVar31 = iVar16 - iVar39;
  __exponent = param_3 + (iVar16 + 1) * -0x18;
  iVar17 = iVar39 + uVar38 + 1;
  puVar26 = (undefined4 *)(param_6 + iVar31 * 4);
  pdVar30 = local_138;
  if (-1 < (int)(iVar39 + uVar38)) {
    do {
      dVar46 = DOUBLE_8043d078;
      if (-1 < iVar31) {
        local_98 = (double)(CONCAT44(0x43300000,*puVar26) ^ 0x80000000);
        dVar46 = local_98 - DOUBLE_8043d0b0;
      }
      *pdVar30 = dVar46;
      pdVar30 = pdVar30 + 1;
      puVar26 = puVar26 + 1;
      iVar31 = iVar31 + 1;
      iVar17 = iVar17 + -1;
    } while (iVar17 != 0);
  }
  pdVar30 = local_278;
  for (iVar17 = 0; iVar17 <= (int)uVar38; iVar17 = iVar17 + 1) {
    iVar31 = 0;
    dVar46 = DOUBLE_8043d078;
    if (-1 < iVar39) {
      if (8 < param_4) {
        uVar40 = param_4 - 1U >> 3;
        iVar32 = iVar39 + iVar17;
        pdVar28 = pdVar29;
        if (-1 < param_4 + -9) {
          do {
            iVar33 = iVar32 - iVar31;
            iVar35 = iVar31 + 1;
            dVar47 = *pdVar28;
            iVar19 = iVar31 + 2;
            iVar20 = iVar31 + 3;
            pdVar1 = pdVar28 + 1;
            pdVar2 = pdVar28 + 2;
            iVar21 = iVar31 + 4;
            pdVar3 = pdVar28 + 3;
            iVar22 = iVar31 + 5;
            pdVar4 = pdVar28 + 4;
            iVar36 = iVar31 + 6;
            pdVar5 = pdVar28 + 5;
            iVar34 = iVar31 + 7;
            pdVar6 = pdVar28 + 6;
            iVar31 = iVar31 + 8;
            pdVar7 = pdVar28 + 7;
            pdVar28 = pdVar28 + 8;
            dVar46 = *pdVar7 * local_138[iVar32 - iVar34] +
                     *pdVar6 * local_138[iVar32 - iVar36] +
                     *pdVar5 * local_138[iVar32 - iVar22] +
                     *pdVar4 * local_138[iVar32 - iVar21] +
                     *pdVar3 * local_138[iVar32 - iVar20] +
                     *pdVar2 * local_138[iVar32 - iVar19] +
                     *pdVar1 * local_138[iVar32 - iVar35] + dVar47 * local_138[iVar33] + dVar46;
            uVar40 = uVar40 - 1;
          } while (uVar40 != 0);
        }
      }
      iVar32 = param_4 - iVar31;
      pdVar28 = pdVar29 + iVar31;
      if (iVar31 <= iVar39) {
        do {
          iVar33 = (iVar39 + iVar17) - iVar31;
          dVar47 = *pdVar28;
          pdVar28 = pdVar28 + 1;
          iVar31 = iVar31 + 1;
          dVar46 = dVar47 * local_138[iVar33] + dVar46;
          iVar32 = iVar32 + -1;
        } while (iVar32 != 0);
      }
    }
    *pdVar30 = dVar46;
    pdVar30 = pdVar30 + 1;
  }
  puVar24 = auStack_2cc + 1;
  uVar40 = uVar38;
  dVar46 = DOUBLE_8043d080;
  dVar47 = DOUBLE_8043d0b0;
  dVar51 = DOUBLE_8043d088;
  dVar49 = DOUBLE_8043d098;
  dVar50 = DOUBLE_8043d090;
  dVar52 = DOUBLE_8043d078;
  do {
    pdVar30 = local_278 + uVar40;
    dVar44 = *pdVar30;
    if (0 < (int)uVar40) {
      uVar41 = uVar40 >> 1;
      puVar27 = puVar24;
      uVar23 = uVar40;
      if (uVar41 != 0) {
        do {
          local_90 = 0x43300000;
          local_98 = (double)(longlong)(int)(dVar46 * dVar44);
          uStack_8c = (int)(dVar46 * dVar44) ^ 0x80000000;
          dVar48 = (double)CONCAT44(0x43300000,uStack_8c) - dVar47;
          local_90 = 0x43300000;
          dVar45 = dVar48 + pdVar30[-1];
          pdVar30 = pdVar30 + -2;
          dVar43 = *pdVar30;
          uVar23 = (uint)(dVar46 * dVar45);
          *puVar27 = (int)-(dVar51 * dVar48 - dVar44);
          local_98 = (double)(longlong)(int)uVar23;
          uStack_8c = uVar23 ^ 0x80000000;
          dVar48 = (double)(CONCAT44(local_90,uVar23) ^ 0x80000000) - dVar47;
          dVar44 = dVar48 + dVar43;
          uVar23 = (uint)-(dVar51 * dVar48 - dVar45);
          local_88 = (double)(longlong)(int)uVar23;
          puVar27[1] = uVar23;
          puVar27 = puVar27 + 2;
          uVar41 = uVar41 - 1;
        } while (uVar41 != 0);
        uVar23 = uVar40 & 1;
        if (uVar23 == 0) goto LAB_8023b4ac;
      }
      do {
        local_90 = 0x43300000;
        pdVar30 = pdVar30 + -1;
        local_98 = (double)(longlong)(int)(dVar46 * dVar44);
        uStack_8c = (int)(dVar46 * dVar44) ^ 0x80000000;
        dVar45 = (double)CONCAT44(0x43300000,uStack_8c) - dVar47;
        dVar43 = dVar51 * dVar45 - dVar44;
        dVar44 = dVar45 + *pdVar30;
        uVar41 = (uint)-dVar43;
        local_88 = (double)(longlong)(int)uVar41;
        *puVar27 = uVar41;
        uVar23 = uVar23 - 1;
        puVar27 = puVar27 + 1;
      } while (uVar23 != 0);
    }
LAB_8023b4ac:
    dVar44 = ldexp(dVar44,__exponent);
    dVar43 = floor(dVar49 * dVar44);
    dVar44 = -(dVar50 * dVar43 - dVar44);
    local_90 = 0x43300000;
    iVar17 = 0;
    uStack_8c = (uint)dVar44;
    local_88 = (double)(longlong)(int)uStack_8c;
    uStack_8c = uStack_8c ^ 0x80000000;
    dVar44 = dVar44 - ((double)CONCAT44(0x43300000,uStack_8c) - dVar47);
    if (__exponent < 1) {
      if (__exponent == 0) {
        iVar17 = (int)auStack_2cc[uVar40] >> 0x17;
      }
      else if (DOUBLE_8043d0a0 <= dVar44) {
        iVar17 = 2;
      }
    }
    else {
      auStack_2cc[uVar40] =
           auStack_2cc[uVar40] -
           (((int)auStack_2cc[uVar40] >> (0x18U - __exponent & 0x3f)) << 0x18U - __exponent);
      iVar17 = (int)auStack_2cc[uVar40] >> (0x17U - __exponent & 0x3f);
    }
    if (0 < iVar17) {
      bVar15 = false;
      puVar27 = puVar24;
      uVar41 = uVar40;
      if (0 < (int)uVar40) {
        do {
          uVar23 = *puVar27;
          if (bVar15) {
            *puVar27 = 0xffffff - uVar23;
          }
          else if (uVar23 != 0) {
            bVar15 = true;
            *puVar27 = 0x1000000 - uVar23;
          }
          puVar27 = puVar27 + 1;
          uVar41 = uVar41 - 1;
        } while (uVar41 != 0);
      }
      if (0 < __exponent) {
        if (__exponent == 2) {
          auStack_2cc[uVar40] = auStack_2cc[uVar40] & 0x3fffff;
        }
        else if ((__exponent < 2) && (0 < __exponent)) {
          auStack_2cc[uVar40] = auStack_2cc[uVar40] & 0x7fffff;
        }
      }
      if ((iVar17 == 2) && (dVar44 = DOUBLE_8043d0a8 - dVar44, bVar15)) {
        dVar43 = ldexp(DOUBLE_8043d0a8,__exponent);
        dVar44 = dVar44 - dVar43;
      }
    }
    if (dVar52 != dVar44) break;
    uVar23 = 0;
    puVar27 = auStack_2cc + uVar40;
    uVar41 = uVar40 - uVar38;
    if ((int)uVar38 <= (int)(uVar40 - 1)) {
      uVar42 = uVar41 >> 3;
      if (uVar42 != 0) {
        do {
          uVar18 = *puVar27;
          puVar8 = puVar27 + -1;
          puVar9 = puVar27 + -2;
          puVar10 = puVar27 + -3;
          puVar11 = puVar27 + -4;
          puVar12 = puVar27 + -5;
          puVar13 = puVar27 + -6;
          puVar14 = puVar27 + -7;
          puVar27 = puVar27 + -8;
          uVar23 = uVar23 | uVar18 | *puVar8 | *puVar9 | *puVar10 | *puVar11 | *puVar12 | *puVar13 |
                   *puVar14;
          uVar42 = uVar42 - 1;
        } while (uVar42 != 0);
        uVar41 = uVar41 & 7;
        if (uVar41 == 0) goto LAB_8023b6c4;
      }
      do {
        uVar42 = *puVar27;
        puVar27 = puVar27 + -1;
        uVar23 = uVar23 | uVar42;
        uVar41 = uVar41 - 1;
      } while (uVar41 != 0);
    }
LAB_8023b6c4:
    if (uVar23 != 0) break;
    for (iVar17 = 1; puVar24[uVar38 - iVar17] == 0; iVar17 = iVar17 + 1) {
    }
    iVar31 = uVar40 + 1;
    pdVar30 = local_278 + iVar31;
    for (; iVar31 <= (int)(uVar40 + iVar17); iVar31 = iVar31 + 1) {
      iVar32 = iVar39 + iVar31;
      iVar33 = 0;
      local_88 = (double)(CONCAT44(0x43300000,*(undefined4 *)(param_6 + (iVar16 + iVar31) * 4)) ^
                         0x80000000);
      local_138[iVar32] = local_88 - dVar47;
      dVar44 = DOUBLE_8043d078;
      if (-1 < iVar39) {
        if (8 < param_4) {
          uVar41 = param_4 - 1U >> 3;
          pdVar28 = pdVar29;
          if (-1 < param_4 + -9) {
            do {
              iVar34 = iVar32 - iVar33;
              iVar19 = iVar33 + 1;
              dVar43 = *pdVar28;
              iVar35 = iVar33 + 2;
              pdVar1 = pdVar28 + 4;
              iVar36 = iVar33 + 3;
              pdVar2 = pdVar28 + 1;
              iVar20 = iVar33 + 4;
              pdVar3 = pdVar28 + 2;
              iVar21 = iVar33 + 5;
              pdVar4 = pdVar28 + 6;
              pdVar5 = pdVar28 + 3;
              iVar37 = iVar33 + 6;
              pdVar6 = pdVar28 + 5;
              iVar22 = iVar33 + 7;
              pdVar7 = pdVar28 + 7;
              pdVar28 = pdVar28 + 8;
              iVar33 = iVar33 + 8;
              dVar44 = *pdVar7 * local_138[iVar32 - iVar22] +
                       *pdVar4 * local_138[iVar32 - iVar37] +
                       *pdVar6 * local_138[iVar32 - iVar21] +
                       *pdVar1 * local_138[iVar32 - iVar20] +
                       *pdVar5 * local_138[iVar32 - iVar36] +
                       *pdVar3 * local_138[iVar32 - iVar35] +
                       *pdVar2 * local_138[iVar32 - iVar19] + dVar43 * local_138[iVar34] + dVar44;
              uVar41 = uVar41 - 1;
            } while (uVar41 != 0);
          }
        }
        iVar19 = param_4 - iVar33;
        pdVar28 = pdVar29 + iVar33;
        if (iVar33 <= iVar39) {
          do {
            iVar20 = iVar32 - iVar33;
            dVar43 = *pdVar28;
            pdVar28 = pdVar28 + 1;
            iVar33 = iVar33 + 1;
            dVar44 = dVar43 * local_138[iVar20] + dVar44;
            iVar19 = iVar19 + -1;
          } while (iVar19 != 0);
        }
      }
      *pdVar30 = dVar44;
      pdVar30 = pdVar30 + 1;
    }
    uVar40 = uVar40 + iVar17;
  } while( true );
  if (DOUBLE_8043d078 == dVar44) {
    for (puVar24 = auStack_2cc + uVar40; uVar40 = uVar40 - 1, __exponent = __exponent + -0x18,
        *puVar24 == 0; puVar24 = puVar24 + -1) {
    }
  }
  else {
    dVar46 = ldexp(dVar44,-__exponent);
    if (dVar46 < DOUBLE_8043d088) {
      local_80 = (double)(longlong)(int)dVar46;
      auStack_2cc[uVar40 + 1] = (int)dVar46;
    }
    else {
      local_90 = 0x43300000;
      __exponent = __exponent + 0x18;
      local_88 = (double)(longlong)(int)(DOUBLE_8043d080 * dVar46);
      uStack_8c = (int)(DOUBLE_8043d080 * dVar46) ^ 0x80000000;
      dVar47 = (double)CONCAT44(0x43300000,uStack_8c) - DOUBLE_8043d0b0;
      uVar41 = (uint)dVar47;
      local_80 = (double)(longlong)(int)uVar41;
      uVar23 = (uint)-(DOUBLE_8043d088 * dVar47 - dVar46);
      local_98 = (double)(longlong)(int)uVar23;
      auStack_2cc[uVar40 + 1] = uVar23;
      auStack_2cc[uVar40 + 2] = uVar41;
      uVar40 = uVar40 + 1;
    }
  }
  dVar46 = ldexp(DOUBLE_8043d0a8,__exponent);
  puVar24 = auStack_2cc + uVar40 + 1;
  pdVar29 = local_278 + uVar40;
  uVar41 = uVar40 + 1;
  if (-1 < (int)uVar40) {
    uVar23 = uVar41 >> 2;
    if (uVar23 != 0) {
      do {
        local_80 = (double)CONCAT44(0x43300000,local_80._4_4_);
        local_80 = (double)CONCAT44(0x43300000,*puVar24 ^ 0x80000000);
        dVar47 = local_80;
        puVar27 = puVar24 + -2;
        local_80 = (double)CONCAT44(0x43300000,puVar24[-1] ^ 0x80000000);
        uVar42 = puVar24[-3];
        local_80 = (double)CONCAT44(0x43300000,puVar24[-1] ^ 0x80000000);
        puVar24 = puVar24 + -4;
        dVar49 = local_80 - DOUBLE_8043d0b0;
        local_80 = (double)CONCAT44(0x43300000,*puVar27 ^ 0x80000000);
        dVar51 = local_80;
        *pdVar29 = dVar46 * (dVar47 - DOUBLE_8043d0b0);
        dVar47 = dVar46 * DOUBLE_8043d080 * DOUBLE_8043d080;
        local_80 = (double)CONCAT44(0x43300000,uVar42 ^ 0x80000000);
        pdVar29[-1] = dVar46 * DOUBLE_8043d080 * dVar49;
        dVar49 = dVar47 * DOUBLE_8043d080;
        dVar50 = local_80 - DOUBLE_8043d0b0;
        pdVar29[-2] = dVar47 * (dVar51 - DOUBLE_8043d0b0);
        dVar46 = dVar49 * DOUBLE_8043d080;
        pdVar29[-3] = dVar49 * dVar50;
        pdVar29 = pdVar29 + -4;
        uVar23 = uVar23 - 1;
      } while (uVar23 != 0);
      uVar41 = uVar41 & 3;
      if (uVar41 == 0) goto LAB_8023ba90;
    }
    do {
      uVar23 = *puVar24;
      puVar24 = puVar24 + -1;
      local_80 = (double)(CONCAT44(0x43300000,uVar23) ^ 0x80000000);
      dVar47 = dVar46 * (local_80 - DOUBLE_8043d0b0);
      dVar46 = dVar46 * DOUBLE_8043d080;
      *pdVar29 = dVar47;
      pdVar29 = pdVar29 + -1;
      uVar41 = uVar41 - 1;
    } while (uVar41 != 0);
  }
LAB_8023ba90:
  iVar16 = uVar40 + 1;
  uVar41 = uVar40;
  if (-1 < (int)uVar40) {
    do {
      iVar39 = uVar40 - uVar41;
      pdVar29 = (double *)&DAT_802b50c0;
      dVar46 = DOUBLE_8043d078;
      for (iVar31 = 0; (iVar31 <= (int)uVar38 && (iVar31 <= iVar39)); iVar31 = iVar31 + 1) {
        dVar47 = *pdVar29;
        pdVar29 = pdVar29 + 1;
        dVar46 = dVar47 * local_278[uVar41 + iVar31] + dVar46;
      }
      uVar41 = uVar41 - 1;
      local_1d8[iVar39] = dVar46;
      iVar16 = iVar16 + -1;
    } while (iVar16 != 0);
  }
  if (param_5 != 3) {
    if (2 < param_5) goto LAB_8023bf6c;
    if (param_5 != 0) {
      if (param_5 < 0) goto LAB_8023bf6c;
      pdVar29 = local_1d8 + uVar40;
      uVar38 = uVar40 + 1;
      dVar46 = DOUBLE_8043d078;
      if (-1 < (int)uVar40) {
        uVar41 = uVar38 >> 3;
        if (uVar41 != 0) {
          do {
            dVar47 = *pdVar29;
            pdVar30 = pdVar29 + -1;
            pdVar28 = pdVar29 + -2;
            pdVar1 = pdVar29 + -3;
            pdVar2 = pdVar29 + -4;
            pdVar3 = pdVar29 + -5;
            pdVar4 = pdVar29 + -6;
            pdVar5 = pdVar29 + -7;
            pdVar29 = pdVar29 + -8;
            dVar46 = dVar46 + dVar47 + *pdVar30 + *pdVar28 + *pdVar1 + *pdVar2 + *pdVar3 + *pdVar4 +
                     *pdVar5;
            uVar41 = uVar41 - 1;
          } while (uVar41 != 0);
          uVar38 = uVar38 & 7;
          if (uVar38 == 0) goto LAB_8023bc48;
        }
        do {
          dVar47 = *pdVar29;
          pdVar29 = pdVar29 + -1;
          dVar46 = dVar46 + dVar47;
          uVar38 = uVar38 - 1;
        } while (uVar38 != 0);
      }
LAB_8023bc48:
      dVar47 = dVar46;
      if (iVar17 != 0) {
        dVar47 = -dVar46;
      }
      *pdVar25 = dVar47;
      iVar16 = 1;
      local_1d8[0] = local_1d8[0] - dVar46;
      if (0 < (int)uVar40) {
        if (8 < (int)uVar40) {
          pdVar29 = local_1d8 + 1;
          uVar38 = uVar40 - 1 >> 3;
          if (0 < (int)(uVar40 - 8)) {
            do {
              dVar46 = *pdVar29;
              iVar16 = iVar16 + 8;
              pdVar30 = pdVar29 + 1;
              pdVar28 = pdVar29 + 2;
              pdVar1 = pdVar29 + 3;
              pdVar2 = pdVar29 + 4;
              pdVar3 = pdVar29 + 5;
              pdVar4 = pdVar29 + 6;
              pdVar5 = pdVar29 + 7;
              pdVar29 = pdVar29 + 8;
              local_1d8[0] = local_1d8[0] + dVar46 + *pdVar30 + *pdVar28 + *pdVar1 + *pdVar2 +
                             *pdVar3 + *pdVar4 + *pdVar5;
              uVar38 = uVar38 - 1;
            } while (uVar38 != 0);
          }
        }
        iVar39 = (uVar40 + 1) - iVar16;
        pdVar29 = local_1d8 + iVar16;
        if (iVar16 <= (int)uVar40) {
          do {
            dVar46 = *pdVar29;
            pdVar29 = pdVar29 + 1;
            local_1d8[0] = local_1d8[0] + dVar46;
            iVar39 = iVar39 + -1;
          } while (iVar39 != 0);
        }
      }
      if (iVar17 != 0) {
        local_1d8[0] = -local_1d8[0];
      }
      pdVar25[1] = local_1d8[0];
      goto LAB_8023bf6c;
    }
    pdVar29 = local_1d8 + uVar40;
    uVar38 = uVar40 + 1;
    dVar46 = DOUBLE_8043d078;
    if (-1 < (int)uVar40) {
      uVar40 = uVar38 >> 3;
      if (uVar40 != 0) {
        do {
          dVar47 = *pdVar29;
          pdVar30 = pdVar29 + -1;
          pdVar28 = pdVar29 + -2;
          pdVar1 = pdVar29 + -3;
          pdVar2 = pdVar29 + -4;
          pdVar3 = pdVar29 + -5;
          pdVar4 = pdVar29 + -6;
          pdVar5 = pdVar29 + -7;
          pdVar29 = pdVar29 + -8;
          dVar46 = dVar46 + dVar47 + *pdVar30 + *pdVar28 + *pdVar1 + *pdVar2 + *pdVar3 + *pdVar4 +
                   *pdVar5;
          uVar40 = uVar40 - 1;
        } while (uVar40 != 0);
        uVar38 = uVar38 & 7;
        if (uVar38 == 0) goto LAB_8023bba8;
      }
      do {
        dVar47 = *pdVar29;
        pdVar29 = pdVar29 + -1;
        dVar46 = dVar46 + dVar47;
        uVar38 = uVar38 - 1;
      } while (uVar38 != 0);
    }
LAB_8023bba8:
    if (iVar17 != 0) {
      dVar46 = -dVar46;
    }
    *pdVar25 = dVar46;
    goto LAB_8023bf6c;
  }
  pdVar29 = local_1d8 + uVar40;
  if (0 < (int)uVar40) {
    uVar38 = uVar40 >> 2;
    pdVar30 = pdVar29;
    uVar41 = uVar40;
    if (uVar38 != 0) {
      do {
        dVar46 = pdVar30[-1] + *pdVar30;
        *pdVar30 = *pdVar30 + (pdVar30[-1] - dVar46);
        pdVar30[-1] = dVar46;
        dVar46 = pdVar30[-2] + pdVar30[-1];
        pdVar30[-1] = pdVar30[-1] + (pdVar30[-2] - dVar46);
        pdVar30[-2] = dVar46;
        dVar46 = pdVar30[-3] + pdVar30[-2];
        pdVar30[-2] = pdVar30[-2] + (pdVar30[-3] - dVar46);
        pdVar30[-3] = dVar46;
        dVar46 = pdVar30[-4] + pdVar30[-3];
        pdVar30[-3] = pdVar30[-3] + (pdVar30[-4] - dVar46);
        pdVar30 = pdVar30 + -4;
        *pdVar30 = dVar46;
        uVar38 = uVar38 - 1;
      } while (uVar38 != 0);
      uVar41 = uVar40 & 3;
      if (uVar41 == 0) goto LAB_8023bdf0;
    }
    do {
      dVar46 = pdVar30[-1] + *pdVar30;
      *pdVar30 = *pdVar30 + (pdVar30[-1] - dVar46);
      pdVar30[-1] = dVar46;
      uVar41 = uVar41 - 1;
      pdVar30 = pdVar30 + -1;
    } while (uVar41 != 0);
  }
LAB_8023bdf0:
  uVar38 = uVar40 - 1;
  if (1 < (int)uVar40) {
    uVar41 = uVar38 >> 2;
    pdVar30 = pdVar29;
    if (uVar41 != 0) {
      do {
        dVar46 = pdVar30[-1] + *pdVar30;
        *pdVar30 = *pdVar30 + (pdVar30[-1] - dVar46);
        pdVar30[-1] = dVar46;
        dVar46 = pdVar30[-2] + pdVar30[-1];
        pdVar30[-1] = pdVar30[-1] + (pdVar30[-2] - dVar46);
        pdVar30[-2] = dVar46;
        dVar46 = pdVar30[-3] + pdVar30[-2];
        pdVar30[-2] = pdVar30[-2] + (pdVar30[-3] - dVar46);
        pdVar30[-3] = dVar46;
        dVar46 = pdVar30[-4] + pdVar30[-3];
        pdVar30[-3] = pdVar30[-3] + (pdVar30[-4] - dVar46);
        pdVar30 = pdVar30 + -4;
        *pdVar30 = dVar46;
        uVar41 = uVar41 - 1;
      } while (uVar41 != 0);
      uVar38 = uVar38 & 3;
      if (uVar38 == 0) goto LAB_8023beac;
    }
    do {
      dVar46 = pdVar30[-1] + *pdVar30;
      *pdVar30 = *pdVar30 + (pdVar30[-1] - dVar46);
      pdVar30[-1] = dVar46;
      uVar38 = uVar38 - 1;
      pdVar30 = pdVar30 + -1;
    } while (uVar38 != 0);
  }
LAB_8023beac:
  uVar38 = uVar40 - 1;
  dVar46 = DOUBLE_8043d078;
  if (1 < (int)uVar40) {
    uVar40 = uVar38 >> 3;
    if (uVar40 != 0) {
      do {
        dVar47 = *pdVar29;
        pdVar30 = pdVar29 + -1;
        pdVar28 = pdVar29 + -2;
        pdVar1 = pdVar29 + -3;
        pdVar2 = pdVar29 + -4;
        pdVar3 = pdVar29 + -5;
        pdVar4 = pdVar29 + -6;
        pdVar5 = pdVar29 + -7;
        pdVar29 = pdVar29 + -8;
        dVar46 = dVar46 + dVar47 + *pdVar30 + *pdVar28 + *pdVar1 + *pdVar2 + *pdVar3 + *pdVar4 +
                 *pdVar5;
        uVar40 = uVar40 - 1;
      } while (uVar40 != 0);
      uVar38 = uVar38 & 7;
      if (uVar38 == 0) goto LAB_8023bf2c;
    }
    do {
      dVar47 = *pdVar29;
      pdVar29 = pdVar29 + -1;
      dVar46 = dVar46 + dVar47;
      uVar38 = uVar38 - 1;
    } while (uVar38 != 0);
  }
LAB_8023bf2c:
  if (iVar17 == 0) {
    *pdVar25 = local_1d8[0];
    pdVar25[1] = local_1d8[1];
    pdVar25[2] = dVar46;
  }
  else {
    *pdVar25 = -local_1d8[0];
    pdVar25[1] = -local_1d8[1];
    pdVar25[2] = -dVar46;
  }
LAB_8023bf6c:
  zz_0232a54_();
  return;
}



// ==== 8023bf8c  gnt4-__kernel_sin ====

double gnt4___kernel_sin(double param_1,double param_2,int param_3)

{
  double dVar1;
  double dVar2;
  double dVar3;
  undefined4 local_18;
  
  local_18 = (uint)((ulonglong)param_1 >> 0x20);
  if ((0x3e3fffff < (local_18 & 0x7fffffff)) || ((int)param_1 != 0)) {
    dVar3 = param_1 * param_1;
    dVar2 = dVar3 * param_1;
    dVar1 = dVar3 * (dVar3 * (dVar3 * (DOUBLE_8043d0d8 * dVar3 + DOUBLE_8043d0d0) + DOUBLE_8043d0c8)
                    + DOUBLE_8043d0c0) + DOUBLE_8043d0b8;
    if (param_3 == 0) {
      param_1 = dVar2 * (dVar3 * dVar1 + DOUBLE_8043d0e0) + param_1;
    }
    else {
      param_1 = param_1 - -(DOUBLE_8043d0e0 * dVar2 -
                           (dVar3 * (DOUBLE_8043d0e8 * param_2 - dVar2 * dVar1) - param_2));
    }
  }
  return param_1;
}



// ==== 8023c02c  gnt4-__kernel_tan ====

/* WARNING: Removing unreachable block (ram,0x8023c230) */
/* WARNING: Removing unreachable block (ram,0x8023c034) */

double gnt4___kernel_tan(double param_1,double param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  double dVar3;
  double dVar4;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  undefined8 local_20;
  
  local_38._0_4_ = (uint)((ulonglong)param_1 >> 0x20);
  uVar2 = local_38._0_4_;
  uVar1 = local_38._0_4_ & 0x7fffffff;
  if ((uVar1 < 0x3e300000) && ((int)param_1 == 0)) {
    local_38._4_4_ = SUB84(param_1,0);
    if (param_3 == 0xffffffff &&
        (((ulonglong)param_1 & 0x7fffffff00000000) == 0 && local_38._4_4_ == 0)) {
      param_1 = DOUBLE_8043d0f0 / ABS(param_1);
    }
    else if (param_3 != 1) {
      param_1 = DOUBLE_8043d0f8 / param_1;
    }
  }
  else {
    local_38 = param_1;
    if (0x3fe59427 < uVar1) {
      if ((longlong)param_1 < 0) {
        param_2 = -param_2;
        local_38 = -param_1;
      }
      local_38 = (DOUBLE_8043d100 - local_38) + (DOUBLE_8043d108 - param_2);
      param_2 = DOUBLE_8043d110;
    }
    dVar3 = local_38 * local_38;
    dVar4 = dVar3 * dVar3;
    dVar3 = DAT_802b5100 * dVar3 * local_38 +
            dVar3 * (dVar3 * local_38 *
                     (dVar4 * (dVar4 * (dVar4 * (dVar4 * (dVar4 * DAT_802b5158 + DAT_802b5148) +
                                                DAT_802b5138) + DAT_802b5128) + DAT_802b5118) +
                      DAT_802b5108 +
                     dVar3 * (dVar4 * (dVar4 * (dVar4 * (dVar4 * (dVar4 * DAT_802b5160 +
                                                                 DAT_802b5150) + DAT_802b5140) +
                                               DAT_802b5130) + DAT_802b5120) + DAT_802b5110)) +
                    param_2) + param_2;
    param_1 = local_38 + dVar3;
    if (uVar1 < 0x3fe59428) {
      if (param_3 != 1) {
        local_28 = (double)((ulonglong)param_1 & 0xffffffff00000000);
        local_30 = (double)((ulonglong)(DOUBLE_8043d0f8 / param_1) & 0xffffffff00000000);
        param_1 = (DOUBLE_8043d0f8 / param_1) *
                  (local_30 * (dVar3 - (local_28 - local_38)) +
                  local_30 * local_28 + DOUBLE_8043d0f0) + local_30;
      }
    }
    else {
      local_20 = (double)CONCAT44(0x43300000,param_3 ^ 0x80000000);
      param_1 = ((double)CONCAT44(0x43300000,1 - (uVar2 >> 0x1e & 2) ^ 0x80000000) - DOUBLE_8043d120
                ) * -(DOUBLE_8043d118 *
                      (local_38 -
                      ((param_1 * param_1) / (param_1 + (local_20 - DOUBLE_8043d120)) - dVar3)) -
                     (local_20 - DOUBLE_8043d120));
    }
  }
  return param_1;
}



// ==== 8023c240  gnt4-atan ====

double gnt4_atan(double __x)

{
  uint uVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  undefined8 local_8;
  
  local_8._0_4_ = (uint)((ulonglong)__x >> 0x20);
  uVar1 = local_8._0_4_ & 0x7fffffff;
  if (uVar1 < 0x44100000) {
    if (uVar1 < 0x3fdc0000) {
      if ((uVar1 < 0x3e200000) && (DOUBLE_8043d130 < DOUBLE_8043d128 + __x)) {
        return __x;
      }
      iVar2 = -1;
      local_8 = __x;
    }
    else {
      local_8 = ABS(__x);
      if (uVar1 < 0x3ff30000) {
        if (uVar1 < 0x3fe60000) {
          iVar2 = 0;
          local_8 = (DOUBLE_8043d138 * local_8 - DOUBLE_8043d130) / (DOUBLE_8043d138 + local_8);
        }
        else {
          iVar2 = 1;
          local_8 = (local_8 - DOUBLE_8043d130) / (DOUBLE_8043d130 + local_8);
        }
      }
      else if (uVar1 < 0x40038000) {
        iVar2 = 2;
        local_8 = (local_8 - DOUBLE_8043d140) / (DOUBLE_8043d140 * local_8 + DOUBLE_8043d130);
      }
      else {
        iVar2 = 3;
        local_8 = DOUBLE_8043d148 / local_8;
      }
    }
    dVar3 = local_8 * local_8;
    dVar5 = dVar3 * dVar3;
    dVar4 = dVar5 * (dVar5 * (dVar5 * (dVar5 * (dVar5 * DAT_802b51f0 + DAT_802b51e0) + DAT_802b51d0)
                             + DAT_802b51c0) + DAT_802b51b0);
    dVar3 = dVar3 * (dVar5 * (dVar5 * (dVar5 * (dVar5 * (dVar5 * DAT_802b51f8 + DAT_802b51e8) +
                                               DAT_802b51d8) + DAT_802b51c8) + DAT_802b51b8) +
                    DAT_802b51a8);
    if (iVar2 < 0) {
      dVar3 = -(local_8 * (dVar3 + dVar4) - local_8);
    }
    else {
      dVar3 = *(double *)(&DAT_802b5168 + iVar2 * 8) -
              ((local_8 * (dVar3 + dVar4) - *(double *)(&DAT_802b5188 + iVar2 * 8)) - local_8);
      if ((longlong)__x < 0) {
        dVar3 = -dVar3;
      }
    }
  }
  else if ((uVar1 < 0x7ff00001) &&
          ((uVar1 != 0x7ff00000 || (local_8._4_4_ = SUB84(__x,0), local_8._4_4_ == 0)))) {
    if ((longlong)__x < 0x100000000) {
      dVar3 = -DAT_802b5180 - DAT_802b51a0;
    }
    else {
      dVar3 = DAT_802b5180 + DAT_802b51a0;
    }
  }
  else {
    dVar3 = __x + __x;
  }
  return dVar3;
}



// ==== 8023c458  copysign ====

double copysign(double __x,double __y)

{
  undefined8 local_18;
  undefined4 local_10;
  
  local_18._0_4_ = (uint)((ulonglong)__x >> 0x20);
  local_10 = (uint)((ulonglong)__y >> 0x20);
  local_18 = (double)CONCAT44(local_18._0_4_ & 0x7fffffff | local_10 & 0x80000000,SUB84(__x,0));
  return local_18;
}



// ==== 8023c480  gnt4-cos-bl ====

/* WARNING: Removing unreachable block (ram,0x8023c4e8) */

double gnt4_cos_bl(double param_1)

{
  uint uVar1;
  double dVar2;
  uint local_18;
  double local_10;
  double local_8;
  
  local_18 = (uint)((ulonglong)param_1 >> 0x20);
  if ((local_18 & 0x7fffffff) < 0x3fe921fc) {
    dVar2 = gnt4___kernel_cos(param_1,DOUBLE_8043d150);
  }
  else if ((local_18 & 0x7fffffff) < 0x7ff00000) {
    uVar1 = gnt4___ieee754_rem_pio2_bl(param_1,&local_10);
    uVar1 = uVar1 & 3;
    if (uVar1 == 1) {
      dVar2 = gnt4___kernel_sin(local_10,local_8,1);
      dVar2 = -dVar2;
    }
    else if (uVar1 == 0) {
      dVar2 = gnt4___kernel_cos(local_10,local_8);
    }
    else if (uVar1 < 3) {
      dVar2 = gnt4___kernel_cos(local_10,local_8);
      dVar2 = -dVar2;
    }
    else {
      dVar2 = gnt4___kernel_sin(local_10,local_8,1);
    }
  }
  else {
    dVar2 = param_1 - param_1;
  }
  return dVar2;
}



// ==== 8023c554  floor ====

double floor(double __x)

{
  uint uVar1;
  uint uVar2;
  uint local_8;
  uint uStack_4;
  
  local_8 = (uint)((ulonglong)__x >> 0x20);
  uStack_4 = SUB84(__x,0);
  uVar1 = local_8 >> 0x14 & 0x7ff;
  uVar2 = uVar1 - 0x3ff;
  if ((int)uVar2 < 0x14) {
    if ((int)uVar2 < 0) {
      if (DOUBLE_8043d160 < DOUBLE_8043d158 + __x) {
        if ((longlong)__x < 0) {
          if (((ulonglong)__x & 0x7fffffff00000000) != 0 || uStack_4 != 0) {
            __x = -1.0;
          }
        }
        else {
          __x = 0.0;
        }
      }
    }
    else {
      uVar1 = 0xfffff >> (uVar2 & 0x3f);
      if ((uStack_4 != 0 || (local_8 & uVar1) != 0) && (DOUBLE_8043d160 < DOUBLE_8043d158 + __x)) {
        if ((longlong)__x < 0) {
          local_8 = local_8 + (0x100000 >> (uVar2 & 0x3f));
        }
        __x = (double)((ulonglong)(local_8 & ~uVar1) << 0x20);
      }
    }
  }
  else if ((int)uVar2 < 0x34) {
    uVar1 = 0xffffffff >> uVar1 - 0x413;
    if (((uStack_4 & uVar1) != 0) && (DOUBLE_8043d160 < DOUBLE_8043d158 + __x)) {
      if ((longlong)__x < 0) {
        if (uVar2 == 0x14) {
          __x = (double)CONCAT44(local_8 + 1,uStack_4);
        }
        else {
          uVar2 = uStack_4 + (1 << 0x34 - uVar2);
          if (uVar2 < uStack_4) {
            local_8 = local_8 + 1;
          }
          __x = (double)CONCAT44(local_8,uVar2);
        }
      }
      __x = (double)CONCAT44((int)((ulonglong)__x >> 0x20),SUB84(__x,0) & ~uVar1);
    }
  }
  else if (uVar2 == 0x400) {
    __x = __x + __x;
  }
  return __x;
}



// ==== 8023c69c  frexp ====

double frexp(double __x,int *__exponent)

{
  double dVar1;
  uint uVar2;
  uint uVar3;
  undefined8 local_8;
  
  local_8._0_4_ = (uint)((ulonglong)__x >> 0x20);
  *__exponent = 0;
  dVar1 = DOUBLE_8043d168;
  uVar2 = local_8._0_4_ & 0x7fffffff;
  local_8._4_4_ = SUB84(__x,0);
  if ((uVar2 < 0x7ff00000) && (((ulonglong)__x & 0x7fffffff00000000) != 0 || local_8._4_4_ != 0)) {
    uVar3 = local_8._0_4_;
    local_8 = __x;
    if (uVar2 < 0x100000) {
      *__exponent = -0x36;
      local_8._0_4_ = (uint)((ulonglong)(__x * dVar1) >> 0x20);
      uVar2 = local_8._0_4_ & 0x7fffffff;
      uVar3 = local_8._0_4_;
      local_8 = __x * dVar1;
    }
    local_8 = (double)(CONCAT44(uVar3,local_8._4_4_) & 0x800fffffffffffff | 0x3fe0000000000000);
    *__exponent = ((int)uVar2 >> 0x14) + *__exponent + -0x3fe;
    __x = local_8;
  }
  return __x;
}



// ==== 8023c728  ldexp ====

double ldexp(double __x,int __exponent)

{
  uint uVar1;
  int iVar2;
  double dVar3;
  double local_18;
  uint local_10;
  int iStack_c;
  
  local_10 = (uint)((ulonglong)__x >> 0x20);
  iStack_c = SUB84(__x,0);
  if ((local_10 & 0x7ff00000) == 0x7ff00000) {
    if ((((ulonglong)__x & 0xfffff00000000) == 0) && (iStack_c == 0)) {
      uVar1 = 2;
    }
    else {
      uVar1 = 1;
    }
  }
  else if (((local_10 & 0x7ff00000) < 0x7ff00000) && (((ulonglong)__x & 0x7ff0000000000000) == 0)) {
    if ((((ulonglong)__x & 0xfffff00000000) == 0) && (iStack_c == 0)) {
      uVar1 = 3;
    }
    else {
      uVar1 = 5;
    }
  }
  else {
    uVar1 = 4;
  }
  if (uVar1 < 3) {
    return __x;
  }
  if (DOUBLE_8043d170 == __x) {
    return __x;
  }
  uVar1 = local_10 >> 0x14 & 0x7ff;
  local_18 = __x;
  if (uVar1 == 0) {
    if (iStack_c == 0 && ((ulonglong)__x & 0x7fffffff00000000) == 0) {
      return __x;
    }
    dVar3 = __x * DOUBLE_8043d178;
    local_18._0_4_ = (uint)((ulonglong)dVar3 >> 0x20);
    uVar1 = (local_18._0_4_ >> 0x14 & 0x7ff) - 0x36;
    local_10 = local_18._0_4_;
    local_18 = dVar3;
    if (__exponent < -50000) {
      return DOUBLE_8043d180 * dVar3;
    }
  }
  if (uVar1 == 0x7ff) {
    local_18 = local_18 + local_18;
  }
  else {
    iVar2 = uVar1 + __exponent;
    if (iVar2 < 0x7ff) {
      if (iVar2 < 1) {
        if (iVar2 < -0x35) {
          if (__exponent < 0xc351) {
            local_18 = copysign(DOUBLE_8043d180,local_18);
            local_18 = DOUBLE_8043d180 * local_18;
          }
          else {
            local_18 = copysign(DOUBLE_8043d188,local_18);
            local_18 = DOUBLE_8043d188 * local_18;
          }
        }
        else {
          local_18 = (double)CONCAT44(local_10 & 0x800fffff | (iVar2 + 0x36) * 0x100000,
                                      local_18._4_4_);
          local_18 = DOUBLE_8043d190 * local_18;
        }
      }
      else {
        local_18 = (double)CONCAT44(local_10 & 0x800fffff | iVar2 * 0x100000,local_18._4_4_);
      }
    }
    else {
      local_18 = copysign(DOUBLE_8043d188,local_18);
      local_18 = DOUBLE_8043d188 * local_18;
    }
  }
  return local_18;
}



// ==== 8023c8ec  modf ====

double modf(double __x,double *__iptr)

{
  uint uVar1;
  uint uVar2;
  undefined8 local_8;
  
  local_8._0_4_ = (uint)((ulonglong)__x >> 0x20);
  local_8._4_4_ = SUB84(__x,0);
  uVar1 = local_8._0_4_ >> 0x14 & 0x7ff;
  uVar2 = uVar1 - 0x3ff;
  if ((int)uVar2 < 0x14) {
    if ((int)uVar2 < 0) {
      *(uint *)__iptr = local_8._0_4_ & 0x80000000;
      *(undefined4 *)((int)__iptr + 4) = 0;
    }
    else {
      uVar1 = 0xfffff >> (uVar2 & 0x3f);
      if (local_8._4_4_ == 0 && (local_8._0_4_ & uVar1) == 0) {
        local_8 = (double)((ulonglong)(local_8._0_4_ & 0x80000000) << 0x20);
        *__iptr = __x;
        __x = local_8;
      }
      else {
        *(uint *)__iptr = local_8._0_4_ & ~uVar1;
        *(undefined4 *)((int)__iptr + 4) = 0;
        __x = __x - *__iptr;
      }
    }
  }
  else if ((int)uVar2 < 0x34) {
    uVar1 = 0xffffffff >> uVar1 - 0x413;
    if ((local_8._4_4_ & uVar1) == 0) {
      local_8 = (double)((ulonglong)(local_8._0_4_ & 0x80000000) << 0x20);
      *__iptr = __x;
      __x = local_8;
    }
    else {
      *(uint *)__iptr = local_8._0_4_;
      *(uint *)((int)__iptr + 4) = local_8._4_4_ & ~uVar1;
      __x = __x - *__iptr;
    }
  }
  else {
    local_8 = (double)((ulonglong)(local_8._0_4_ & 0x80000000) << 0x20);
    *__iptr = __x;
    __x = local_8;
  }
  return __x;
}



// ==== 8023c9e8  gnt4-sin-bl ====

/* WARNING: Removing unreachable block (ram,0x8023ca54) */

double gnt4_sin_bl(double param_1)

{
  uint uVar1;
  double dVar2;
  uint local_18;
  double local_10;
  double local_8;
  
  local_18 = (uint)((ulonglong)param_1 >> 0x20);
  if ((local_18 & 0x7fffffff) < 0x3fe921fc) {
    dVar2 = gnt4___kernel_sin(param_1,DOUBLE_8043d198,0);
  }
  else if ((local_18 & 0x7fffffff) < 0x7ff00000) {
    uVar1 = gnt4___ieee754_rem_pio2_bl(param_1,&local_10);
    uVar1 = uVar1 & 3;
    if (uVar1 == 1) {
      dVar2 = gnt4___kernel_cos(local_10,local_8);
    }
    else if (uVar1 == 0) {
      dVar2 = gnt4___kernel_sin(local_10,local_8,1);
    }
    else if (uVar1 < 3) {
      dVar2 = gnt4___kernel_sin(local_10,local_8,1);
      dVar2 = -dVar2;
    }
    else {
      dVar2 = gnt4___kernel_cos(local_10,local_8);
      dVar2 = -dVar2;
    }
  }
  else {
    dVar2 = param_1 - param_1;
  }
  return dVar2;
}



// ==== 8023cac0  gnt4-tan-bl ====

double gnt4_tan_bl(double param_1)

{
  uint uVar1;
  double dVar2;
  uint local_18;
  double local_10;
  double local_8;
  
  local_18 = (uint)((ulonglong)param_1 >> 0x20);
  if ((local_18 & 0x7fffffff) < 0x3fe921fc) {
    dVar2 = gnt4___kernel_tan(param_1,DOUBLE_8043d1a0,1);
  }
  else if ((local_18 & 0x7fffffff) < 0x7ff00000) {
    uVar1 = gnt4___ieee754_rem_pio2_bl(param_1,&local_10);
    dVar2 = gnt4___kernel_tan(local_10,local_8,(uVar1 & 1) * -2 + 1);
  }
  else {
    dVar2 = param_1 - param_1;
  }
  return dVar2;
}



// ==== 8023cb38  gnt4-acos-bl ====

void gnt4_acos_bl(double param_1)

{
  gnt4___ieee754_acos(param_1);
  return;
}



// ==== 8023cb58  gnt4-asin-bl ====

void gnt4_asin_bl(double param_1,double param_2)

{
  gnt4___ieee754_asin(param_1,param_2);
  return;
}



// ==== 8023cb78  gnt4-atan2-bl ====

void gnt4_atan2_bl(double param_1,double param_2)

{
  gnt4___ieee754_atan2(param_1,param_2);
  return;
}



// ==== 8023cb98  gnt4-exp-bl ====

void gnt4_exp_bl(double param_1)

{
  gnt4___ieee754_exp(param_1);
  return;
}



// ==== 8023cbb8  gnt4-fmod-bl ====

void gnt4_fmod_bl(double param_1,double param_2)

{
  gnt4___ieee754_fmod(param_1,param_2);
  return;
}



// ==== 8023cbd8  gnt4-log-bl ====

void gnt4_log_bl(double param_1)

{
  gnt4___ieee754_log(param_1);
  return;
}



// ==== 8023cbf8  gnt4-pow-bl ====

void gnt4_pow_bl(double param_1,double param_2)

{
  gnt4___ieee754_pow(param_1,param_2);
  return;
}



// ==== 8023cc18  zz_023cc18_ ====

double zz_023cc18_(double param_1)

{
  return ABS(param_1);
}



// ==== 8023cc20  gnt4-tanf ====

float gnt4_tanf(float __x)

{
  double dVar1;
  
  dVar1 = gnt4_tan_bl((double)__x);
  return (float)dVar1;
}



// ==== 8023cc44  gnt4-sinf ====

float gnt4_sinf(float __x)

{
  double dVar1;
  
  dVar1 = gnt4_sin_bl((double)__x);
  return (float)dVar1;
}



// ==== 8023cc68  gnt4-cosf ====

float gnt4_cosf(float __x)

{
  double dVar1;
  
  dVar1 = gnt4_cos_bl((double)__x);
  return (float)dVar1;
}



// ==== 8023cc8c  tanf ====

float tanf(float __x)

{
  double dVar1;
  
  dVar1 = (double)gnt4_acos_bl((double)__x);
  return (float)dVar1;
}



// ==== 8023ccb0  zz_023ccb0_ ====

void zz_023ccb0_(void)

{
  return;
}



// ==== 8023ccb4  zz_023ccb4_ ====

void zz_023ccb4_(void)

{
  return;
}



// ==== 8023ccb8  zz_023ccb8_ ====

undefined4 zz_023ccb8_(void)

{
  return 0;
}



// ==== 8023ccc0  zz_023ccc0_ ====

undefined4 zz_023ccc0_(void)

{
  return 0;
}



// ==== 8023ccc8  zz_023ccc8_ ====

undefined4 zz_023ccc8_(void)

{
  return 0;
}



// ==== 8023ccd0  zz_023ccd0_ ====

void zz_023ccd0_(void)

{
  return;
}



// ==== 8023ccd4  zz_023ccd4_ ====

void zz_023ccd4_(void)

{
  return;
}



// ==== 8023ccd8  zz_023ccd8_ ====

undefined4 zz_023ccd8_(void)

{
  return 1;
}



// ==== 8023cce0  zz_023cce0_ ====

undefined4 zz_023cce0_(void)

{
  return 0;
}



// ==== 8023cce8  zz_023cce8_ ====

void zz_023cce8_(void)

{
  return;
}



// ==== 8023ccec  zz_023ccec_ ====

void zz_023ccec_(void)

{
  return;
}



// ==== 8023ccf0  DBWrite ====

undefined4 DBWrite(undefined4 *param_1,uint param_2)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  byte local_3c [8];
  uint local_34 [2];
  byte local_2c [8];
  uint local_24;
  
  gnt4_OSDisableInterrupts_bl();
  do {
    uVar3 = DAT_cc006828;
    DAT_cc006828 = uVar3 & 0x405 | 0xc0;
    local_2c[4] = 0x40;
    local_2c[5] = 0;
    local_2c[6] = 0;
    local_2c[7] = 0;
    uVar2 = DBGEXIImm(local_2c + 4,2,1);
    countLeadingZeros(uVar2);
    do {
      uVar3 = DAT_cc006834;
    } while ((uVar3 & 1) != 0);
    DBGEXIImm((byte *)&local_24,4,0);
    do {
      uVar3 = DAT_cc006834;
    } while ((uVar3 & 1) != 0);
    uVar3 = DAT_cc006828;
    DAT_cc006828 = uVar3 & 0x405;
  } while ((local_24 & 2) != 0);
  DAT_80435dd0 = DAT_80435dd0 + 1;
  if ((DAT_80435dd0 & 1) == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = 0x1000;
  }
  do {
    uVar4 = DBGWrite(uVar3 | 0x1c000,param_1,param_2 + 3 & 0xfffffffc);
  } while (uVar4 == 0);
  do {
    uVar3 = DAT_cc006828;
    DAT_cc006828 = uVar3 & 0x405 | 0xc0;
    local_2c[0] = 0x40;
    local_2c[1] = 0;
    local_2c[2] = 0;
    local_2c[3] = 0;
    uVar2 = DBGEXIImm(local_2c,2,1);
    countLeadingZeros(uVar2);
    do {
      uVar3 = DAT_cc006834;
    } while ((uVar3 & 1) != 0);
    DBGEXIImm((byte *)&local_24,4,0);
    do {
      uVar3 = DAT_cc006834;
    } while ((uVar3 & 1) != 0);
    uVar3 = DAT_cc006828;
    DAT_cc006828 = uVar3 & 0x405;
  } while ((local_24 & 2) != 0);
  uVar3 = (uint)DAT_80435dd0;
  do {
    uVar4 = DAT_cc006828;
    DAT_cc006828 = uVar4 & 0x405 | 0xc0;
    local_34[0] = uVar3 << 0x10 | 0x1f000000 | param_2 & 0x1fffffff | 0xc0000000;
    uVar2 = DBGEXIImm((byte *)local_34,4,1);
    uVar4 = countLeadingZeros(uVar2);
    do {
      uVar1 = DAT_cc006834;
    } while ((uVar1 & 1) != 0);
    uVar1 = DAT_cc006828;
    DAT_cc006828 = uVar1 & 0x405;
  } while (uVar4 >> 5 != 0);
  do {
    uVar3 = DAT_cc006828;
    DAT_cc006828 = uVar3 & 0x405 | 0xc0;
    local_3c[0] = 0x40;
    local_3c[1] = 0;
    local_3c[2] = 0;
    local_3c[3] = 0;
    uVar2 = DBGEXIImm(local_3c,2,1);
    uVar3 = countLeadingZeros(uVar2);
    do {
      uVar4 = DAT_cc006834;
    } while ((uVar4 & 1) != 0);
    uVar2 = DBGEXIImm((byte *)&local_24,4,0);
    uVar4 = countLeadingZeros(uVar2);
    do {
      uVar1 = DAT_cc006834;
    } while ((uVar1 & 1) != 0);
    uVar1 = DAT_cc006828;
    DAT_cc006828 = uVar1 & 0x405;
  } while ((uVar3 >> 5 != 0 || uVar4 >> 5 != 0) || ((local_24 & 2) != 0));
  gnt4_OSRestoreInterrupts_bl();
  return 0;
}



// ==== 8023cf50  DBRead ====

undefined4 DBRead(undefined4 *param_1,int param_2)

{
  int iVar1;
  
  gnt4_OSDisableInterrupts_bl();
  if ((DAT_80436898 & 0x10000) == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = 0x1000;
  }
  DBGRead(iVar1 + 0x1e000,param_1,param_2 + 3U & 0xfffffffc);
  DAT_8043689c = 0;
  DAT_804368a4 = 0;
  gnt4_OSRestoreInterrupts_bl();
  return 0;
}



// ==== 8023cfdc  DBQueryData ====

uint DBQueryData(void)

{
  uint uVar1;
  uint local_10 [3];
  
  DAT_804368a4 = 0;
  if (DAT_8043689c == 0) {
    gnt4_OSDisableInterrupts_bl();
    zz_023d1c0_((byte *)local_10);
    uVar1 = local_10[0];
    if ((local_10[0] & 1) != 0) {
      DBGReadStatus((byte *)local_10);
      uVar1 = local_10[0] & 0x1fffffff;
      if ((local_10[0] & 0x1f000000) == 0x1f000000) {
        DAT_8043689c = local_10[0] & 0x7fff;
        DAT_804368a4 = 1;
        DAT_80436898 = uVar1;
      }
    }
    local_10[0] = uVar1;
    gnt4_OSRestoreInterrupts_bl();
  }
  return DAT_8043689c;
}



// ==== 8023d078  DBInitInterrupts ====

void DBInitInterrupts(void)

{
  gnt4___OSMaskInterrupts_bl(0x18000);
  gnt4___OSMaskInterrupts_bl(0x40);
  DAT_80436894 = FUN_8023d184;
  gnt4___OSSetInterruptHandler_bl(0x19,FUN_8023d144);
  gnt4___OSUnmaskInterrupts_bl(0x40);
  return;
}



// ==== 8023d0cc  DBInitComm ====

void DBInitComm(undefined4 *param_1,undefined4 param_2)

{
  gnt4_OSDisableInterrupts_bl();
  DAT_804368a0 = &DAT_804368a4;
  *param_1 = &DAT_804368a4;
  DAT_80436890 = param_2;
  gnt4___OSMaskInterrupts_bl(0x18000);
  DAT_cc006828 = 0;
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 8023d144  FUN_8023d144 ====

void FUN_8023d144(short param_1)

{
  DAT_cc003000 = 0x1000;
  if (DAT_80436894 != (code *)0x0) {
    (*DAT_80436894)((int)param_1);
  }
  return;
}



// ==== 8023d184  FUN_8023d184 ====

void FUN_8023d184(void)

{
  DAT_804368a4 = 1;
  if (DAT_80436890 != (code *)0x0) {
    (*DAT_80436890)(0);
  }
  return;
}



// ==== 8023d1c0  zz_023d1c0_ ====

uint zz_023d1c0_(byte *param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  byte local_20 [12];
  
  uVar2 = DAT_cc006828;
  DAT_cc006828 = uVar2 & 0x405 | 0xc0;
  local_20[0] = 0x40;
  local_20[1] = 0;
  local_20[2] = 0;
  local_20[3] = 0;
  uVar4 = DBGEXIImm(local_20,2,1);
  uVar2 = countLeadingZeros(uVar4);
  do {
    uVar3 = DAT_cc006834;
  } while ((uVar3 & 1) != 0);
  uVar4 = DBGEXIImm(param_1,4,0);
  uVar3 = countLeadingZeros(uVar4);
  do {
    uVar1 = DAT_cc006834;
  } while ((uVar1 & 1) != 0);
  uVar1 = DAT_cc006828;
  uVar2 = countLeadingZeros((uVar2 | uVar3) >> 5);
  DAT_cc006828 = uVar1 & 0x405;
  return uVar2 >> 5;
}



// ==== 8023d26c  DBGWrite ====

uint DBGWrite(uint param_1,undefined4 *param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 local_20;
  uint local_1c;
  
  local_1c = (param_1 & 0x1fffc) << 8 | 0xa0000000;
  uVar1 = DAT_cc006828;
  DAT_cc006828 = uVar1 & 0x405 | 0xc0;
  uVar3 = DBGEXIImm((byte *)&local_1c,4,1);
  uVar1 = countLeadingZeros(uVar3);
  uVar1 = uVar1 >> 5;
  do {
    uVar2 = DAT_cc006834;
  } while ((uVar2 & 1) != 0);
  while (param_3 != 0) {
    local_20 = *param_2;
    param_2 = param_2 + 1;
    uVar3 = DBGEXIImm((byte *)&local_20,4,1);
    uVar2 = countLeadingZeros(uVar3);
    uVar1 = uVar1 | uVar2 >> 5;
    do {
      uVar2 = DAT_cc006834;
    } while ((uVar2 & 1) != 0);
    param_3 = param_3 + -4;
    if (param_3 < 0) {
      param_3 = 0;
    }
  }
  uVar2 = DAT_cc006828;
  uVar1 = countLeadingZeros(uVar1);
  DAT_cc006828 = uVar2 & 0x405;
  return uVar1 >> 5;
}



// ==== 8023d348  DBGRead ====

uint DBGRead(uint param_1,undefined4 *param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 local_20;
  uint local_1c;
  
  local_1c = (param_1 & 0x1fffc) << 8 | 0x20000000;
  uVar1 = DAT_cc006828;
  DAT_cc006828 = uVar1 & 0x405 | 0xc0;
  uVar3 = DBGEXIImm((byte *)&local_1c,4,1);
  uVar1 = countLeadingZeros(uVar3);
  uVar1 = uVar1 >> 5;
  do {
    uVar2 = DAT_cc006834;
  } while ((uVar2 & 1) != 0);
  while (param_3 != 0) {
    uVar3 = DBGEXIImm((byte *)&local_20,4,0);
    uVar2 = countLeadingZeros(uVar3);
    uVar1 = uVar1 | uVar2 >> 5;
    do {
      uVar2 = DAT_cc006834;
    } while ((uVar2 & 1) != 0);
    param_3 = param_3 + -4;
    *param_2 = local_20;
    param_2 = param_2 + 1;
    if (param_3 < 0) {
      param_3 = 0;
    }
  }
  uVar2 = DAT_cc006828;
  uVar1 = countLeadingZeros(uVar1);
  DAT_cc006828 = uVar2 & 0x405;
  return uVar1 >> 5;
}



// ==== 8023d424  DBGReadStatus ====

uint DBGReadStatus(byte *param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  byte local_20 [12];
  
  uVar2 = DAT_cc006828;
  DAT_cc006828 = uVar2 & 0x405 | 0xc0;
  local_20[0] = 0x60;
  local_20[1] = 0;
  local_20[2] = 0;
  local_20[3] = 0;
  uVar4 = DBGEXIImm(local_20,2,1);
  uVar2 = countLeadingZeros(uVar4);
  do {
    uVar3 = DAT_cc006834;
  } while ((uVar3 & 1) != 0);
  uVar4 = DBGEXIImm(param_1,4,0);
  uVar3 = countLeadingZeros(uVar4);
  do {
    uVar1 = DAT_cc006834;
  } while ((uVar1 & 1) != 0);
  uVar1 = DAT_cc006828;
  uVar2 = countLeadingZeros((uVar2 | uVar3) >> 5);
  DAT_cc006828 = uVar1 & 0x405;
  return uVar2 >> 5;
}



// ==== 8023d4d0  DBGEXIImm ====

undefined4 DBGEXIImm(byte *param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  byte *pbVar4;
  uint uVar5;
  
  if (param_3 != 0) {
    iVar2 = 0;
    uVar3 = 0;
    if (0 < param_2) {
      if ((8 < param_2) && (uVar5 = param_2 - 1U >> 3, pbVar4 = param_1, 0 < param_2 + -8)) {
        do {
          uVar3 = uVar3 | (uint)*pbVar4 << (3 - iVar2) * 8 |
                  (uint)pbVar4[1] << (3 - (iVar2 + 1)) * 8 |
                  (uint)pbVar4[2] << (3 - (iVar2 + 2)) * 8 | (uint)pbVar4[3] << iVar2 * -8 |
                  (uint)pbVar4[4] << (3 - (iVar2 + 4)) * 8 |
                  (uint)pbVar4[5] << (3 - (iVar2 + 5)) * 8 |
                  (uint)pbVar4[6] << (3 - (iVar2 + 6)) * 8 |
                  (uint)pbVar4[7] << (3 - (iVar2 + 7)) * 8;
          pbVar4 = pbVar4 + 8;
          iVar2 = iVar2 + 8;
          uVar5 = uVar5 - 1;
        } while (uVar5 != 0);
      }
      pbVar4 = param_1 + iVar2;
      iVar1 = param_2 - iVar2;
      if (iVar2 < param_2) {
        do {
          uVar3 = uVar3 | (uint)*pbVar4 << (3 - iVar2) * 8;
          pbVar4 = pbVar4 + 1;
          iVar2 = iVar2 + 1;
          iVar1 = iVar1 + -1;
        } while (iVar1 != 0);
      }
    }
    DAT_cc006838 = uVar3;
  }
  DAT_cc006834 = param_3 << 2 | 1U | (param_2 + -1) * 0x10;
  do {
    uVar3 = DAT_cc006834;
  } while ((uVar3 & 1) != 0);
  if (param_3 == 0) {
    iVar2 = 0;
    uVar3 = DAT_cc006838;
    if (0 < param_2) {
      if ((8 < param_2) && (uVar5 = param_2 - 1U >> 3, 0 < param_2 + -8)) {
        do {
          *param_1 = (byte)(uVar3 >> (3 - iVar2) * 8);
          param_1[1] = (byte)(uVar3 >> (3 - (iVar2 + 1)) * 8);
          param_1[2] = (byte)(uVar3 >> (3 - (iVar2 + 2)) * 8);
          param_1[3] = (byte)(uVar3 >> iVar2 * -8);
          param_1[4] = (byte)(uVar3 >> (3 - (iVar2 + 4)) * 8);
          param_1[5] = (byte)(uVar3 >> (3 - (iVar2 + 5)) * 8);
          param_1[6] = (byte)(uVar3 >> (3 - (iVar2 + 6)) * 8);
          param_1[7] = (byte)(uVar3 >> (3 - (iVar2 + 7)) * 8);
          param_1 = param_1 + 8;
          iVar2 = iVar2 + 8;
          uVar5 = uVar5 - 1;
        } while (uVar5 != 0);
      }
      iVar1 = param_2 - iVar2;
      if (iVar2 < param_2) {
        do {
          *param_1 = (byte)(uVar3 >> (3 - iVar2) * 8);
          param_1 = param_1 + 1;
          iVar2 = iVar2 + 1;
          iVar1 = iVar1 + -1;
        } while (iVar1 != 0);
      }
    }
  }
  return 1;
}



// ==== 8023d768  gnt4-HSD_DObjSetCurrent-bl ====

void gnt4_HSD_DObjSetCurrent_bl(undefined4 param_1)

{
  DAT_804368ac = param_1;
  return;
}



// ==== 8023d770  gnt4-HSD_DObjSetFlags-bl ====

void gnt4_HSD_DObjSetFlags_bl(int param_1,uint param_2)

{
  if (param_1 == 0) {
    return;
  }
  *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) | param_2;
  return;
}



// ==== 8023d788  gnt4-HSD_DObjClearFlags-bl ====

void gnt4_HSD_DObjClearFlags_bl(int param_1,uint param_2)

{
  if (param_1 == 0) {
    return;
  }
  *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) & ~param_2;
  return;
}



// ==== 8023d7a0  zz_023d7a0_ ====

void zz_023d7a0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,uint param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint extraout_r4;
  uint uVar1;
  undefined8 uVar2;
  
  if (param_9 != 0) {
    uVar1 = param_10;
    for (; param_9 != 0; param_9 = *(int *)(param_9 + 4)) {
      if (param_9 != 0) {
        if ((param_10 & 2) != 0) {
          param_1 = gnt4_HSD_AObjRemove(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                        param_8,*(undefined4 **)(param_9 + 0x10),uVar1,param_11,
                                        param_12,param_13,param_14,param_15,param_16);
          *(undefined4 *)(param_9 + 0x10) = 0;
        }
        uVar2 = zz_024a4e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            *(int *)(param_9 + 0xc),param_10,param_11,param_12,param_13,param_14,
                            param_15,param_16);
        param_1 = zz_02422dc_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              *(int *)(param_9 + 8),param_10,param_11,param_12,param_13,param_14,
                              param_15,param_16);
        uVar1 = extraout_r4;
      }
    }
  }
  return;
}



// ==== 8023d838  gnt4-HSD_DObjAddAnimAll-bl ====

void gnt4_HSD_DObjAddAnimAll_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 *param_10,
               undefined4 *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined8 uVar3;
  
  puVar2 = param_11;
  if (param_9 != 0) {
    while (param_9 != 0) {
      if (param_9 != 0) {
        if (puVar2 == (undefined4 *)0x0) {
          puVar1 = (undefined4 *)0x0;
        }
        else {
          puVar1 = (undefined4 *)puVar2[1];
        }
        uVar3 = gnt4_HSD_PObjRemoveAnimAll_bl
                          (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           *(int *)(param_9 + 0xc),puVar1,param_11,param_12,param_13,param_14,
                           param_15,param_16);
        param_1 = gnt4_HSD_MObjAddAnim_bl
                            (uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             *(int *)(param_9 + 8),(int)param_10,param_11,param_12,param_13,param_14
                             ,param_15,param_16);
      }
      param_9 = *(int *)(param_9 + 4);
      if (param_10 == (undefined4 *)0x0) {
        param_10 = (undefined4 *)0x0;
      }
      else {
        param_10 = (undefined4 *)*param_10;
      }
      if (puVar2 == (undefined4 *)0x0) {
        puVar2 = (undefined4 *)0x0;
      }
      else {
        puVar2 = (undefined4 *)*puVar2;
      }
    }
  }
  return;
}



// ==== 8023d8e8  gnt4-HSD_DObjReqAnimAllByFlags-bl ====

void gnt4_HSD_DObjReqAnimAllByFlags_bl(double param_1,int param_2,uint param_3)

{
  if (param_2 != 0) {
    for (; param_2 != 0; param_2 = *(int *)(param_2 + 4)) {
      if (param_2 != 0) {
        gnt4_HSD_PObjReqAnimAllByFlags_bl(param_1,*(int *)(param_2 + 0xc),param_3);
        gnt4_HSD_MObjReqAnimByFlags_bl(param_1,*(int *)(param_2 + 8),param_3);
      }
    }
  }
  return;
}



// ==== 8023d968  gnt4-HSD_DObjAnimAll-bl ====

void gnt4_HSD_DObjAnimAll_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int *param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar1;
  undefined8 uVar2;
  
  if (param_9 != (int *)0x0) {
    for (; param_9 != (int *)0x0; param_9 = (int *)param_9[1]) {
      if (param_9 != (int *)0x0) {
        pfVar1 = *(float **)(*param_9 + 0x44);
        uVar2 = gnt4_HSD_AObjInterpretAnim
                          (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           (uint *)param_9[4],(uint)param_9,pfVar1,param_12,param_13,param_14,
                           param_15,param_16);
        uVar2 = gnt4_HSD_PObjAnimAll_bl
                          (uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           (int *)param_9[3],extraout_r4,pfVar1,param_12,param_13,param_14,param_15,
                           param_16);
        param_1 = gnt4_HSD_MObjAnim_bl
                            (uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             (int *)param_9[2],extraout_r4_00,pfVar1,param_12,param_13,param_14,
                             param_15,param_16);
      }
    }
  }
  return;
}



// ==== 8023d9d4  gnt4-DObjLoad-bl ====

undefined4
gnt4_DObjLoad_bl(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  double dVar5;
  
  iVar3 = param_10;
  piVar2 = gnt4_HSD_DObjLoadDesc_bl
                     (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int **)(param_10 + 4),param_10,param_11,param_12,param_13,param_14,param_15,
                      param_16);
  *(int **)(param_9 + 4) = piVar2;
  piVar2 = gnt4_HSD_MObjLoadDesc_bl
                     (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int **)(param_10 + 8),iVar3,param_11,param_12,param_13,param_14,param_15,
                      param_16);
  *(int **)(param_9 + 8) = piVar2;
  piVar2 = gnt4_HSD_PObjLoadDesc_bl
                     (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int **)(param_10 + 0xc),iVar3,param_11,param_12,param_13,param_14,param_15,
                      param_16);
  *(int **)(param_9 + 0xc) = piVar2;
  if (*(int *)(param_9 + 8) != 0) {
    uVar4 = *(uint *)(*(int *)(param_9 + 8) + 4);
    uVar1 = uVar4 & 0x60000000;
    if (uVar1 == 0x40000000) {
      if (param_9 != 0) {
        *(uint *)(param_9 + 0x14) = *(uint *)(param_9 + 0x14) & 0xfffffff1 | 8;
      }
    }
    else {
      if (uVar1 < 0x40000000) {
        if (uVar1 == 0) {
          if (param_9 == 0) {
            return 0;
          }
          *(uint *)(param_9 + 0x14) = *(uint *)(param_9 + 0x14) & 0xfffffff1 | 2;
          return 0;
        }
      }
      else if (uVar1 == 0x60000000) {
        if (param_9 == 0) {
          return 0;
        }
        *(uint *)(param_9 + 0x14) = *(uint *)(param_9 + 0x14) & 0xfffffff1 | 4;
        return 0;
      }
      dVar5 = (double)gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                       param_8,s_mobj_has_unexpected_blending_fla_803abb30,uVar4,
                                       param_11,param_12,param_13,param_14,param_15,param_16);
      gnt4_HSD_Panic_bl(dVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435dd8,
                        0x13f,&DAT_80435de0,param_12,param_13,param_14,param_15,param_16);
    }
  }
  return 0;
}



// ==== 8023dae4  gnt4-HSD_DObjLoadDesc-bl ====

int * gnt4_HSD_DObjLoadDesc_bl
                (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int *param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 *puVar1;
  int *piVar2;
  
  if (param_9 != (int *)0x0) {
    if ((*param_9 == 0) ||
       (puVar1 = (undefined4 *)
                 gnt4_hsdSearchClassInfo_bl
                           (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*param_9
                            ,param_10,param_11,param_12,param_13,param_14,param_15,param_16),
       puVar1 == (undefined4 *)0x0)) {
      piVar2 = gnt4_HSD_DObjAlloc_bl
                         (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    }
    else {
      piVar2 = gnt4_hsdNew_bl(puVar1);
      if (piVar2 == (int *)0x0) {
        gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         &DAT_80435dd8,0x181,&DAT_80435de4,param_12,param_13,param_14,param_15,
                         param_16);
      }
    }
    (**(code **)(*piVar2 + 0x40))(piVar2,param_9);
    return piVar2;
  }
  return (int *)0x0;
}



// ==== 8023db7c  gnt4-HSD_DObjRemoveAll-bl ====

void gnt4_HSD_DObjRemoveAll_bl(int *param_1)

{
  int *piVar1;
  
  while (piVar1 = param_1, piVar1 != (int *)0x0) {
    param_1 = (int *)piVar1[1];
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 0x30))(piVar1);
      (**(code **)(*piVar1 + 0x34))(piVar1);
    }
  }
  return;
}



// ==== 8023dbf0  gnt4-HSD_DObjAlloc-bl ====

int * gnt4_HSD_DObjAlloc_bl
                (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  int *piVar1;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined **ppuVar2;
  
  ppuVar2 = DAT_804368a8;
  if (DAT_804368a8 == (undefined **)0x0) {
    ppuVar2 = &PTR_gnt4_DObjInfoInit_bl_803abae8;
  }
  piVar1 = gnt4_hsdNew_bl(ppuVar2);
  if (piVar1 == (int *)0x0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435dd8,
                     0x214,&DAT_80435de4,in_r6,in_r7,in_r8,in_r9,in_r10);
  }
  return piVar1;
}



// ==== 8023dc4c  gnt4-HSD_DObjResolveRefsAll-bl ====

void gnt4_HSD_DObjResolveRefsAll_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,int param_10)

{
  for (; (param_9 != 0 && (param_10 != 0)); param_10 = *(int *)(param_10 + 4)) {
    if ((param_9 != 0) && (param_10 != 0)) {
      param_1 = gnt4_HSD_PObjResolveRefsAll_bl
                          (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    }
    param_9 = *(int *)(param_9 + 4);
  }
  return;
}



// ==== 8023dcb8  gnt4-HSD_DObjDisp-bl ====

void gnt4_HSD_DObjDisp_bl(undefined4 param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  int iVar1;
  int *piVar2;
  undefined8 uVar3;
  
  uVar3 = gnt4__savegpr_26_bl();
  iVar1 = (int)((ulonglong)uVar3 >> 0x20);
  gnt4_HSD_MObjSetCurrent_bl(*(undefined4 *)(iVar1 + 8));
  if ((param_4 & 0x4000000) == 0) {
    (**(code **)(**(int **)(iVar1 + 8) + 0x3c))(*(int **)(iVar1 + 8),param_4);
  }
  for (piVar2 = *(int **)(iVar1 + 0xc); piVar2 != (int *)0x0; piVar2 = (int *)piVar2[1]) {
    (**(code **)(*piVar2 + 0x3c))(piVar2,(int)uVar3,param_3,param_4);
  }
  if ((param_4 & 0x4000000) == 0) {
    (**(code **)(**(int **)(iVar1 + 8) + 0x50))(*(int **)(iVar1 + 8),param_4);
  }
  gnt4_HSD_MObjSetCurrent_bl(0);
  gnt4__restgpr_26_bl();
  return;
}



// ==== 8023dd78  gnt4-DObjRelease-bl ====

void gnt4_DObjRelease_bl(undefined8 param_1,double param_2,double param_3,double param_4,
                        double param_5,double param_6,double param_7,double param_8,int param_9,
                        undefined4 param_10,undefined4 param_11,undefined4 param_12,
                        undefined4 param_13,undefined4 param_14,undefined4 param_15,
                        undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined8 uVar1;
  
  gnt4_HSD_MObjRemove_bl(*(int **)(param_9 + 8));
  uVar1 = gnt4_HSD_PObjRemoveAll_bl(*(int **)(param_9 + 0xc));
  gnt4_HSD_AObjRemove(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(undefined4 **)(param_9 + 0x10),extraout_r4,param_11,param_12,param_13,
                      param_14,param_15,param_16);
  (**(code **)(DAT_803abafc + 0x30))(param_9);
  return;
}



// ==== 8023ddd4  gnt4-DObjAmnesia-bl ====

void gnt4_DObjAmnesia_bl(int param_1)

{
  if (param_1 == DAT_804368a8) {
    DAT_804368a8 = 0;
  }
  (**(code **)(DAT_803abafc + 0x38))();
  return;
}



// ==== 8023de1c  gnt4-DObjInfoInit-bl ====

void gnt4_DObjInfoInit_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  undefined4 in_r9;
  undefined4 in_r10;
  
  gnt4_hsdInitClassInfo_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fc54518,
             &PTR_gnt4__hsdClassInfoInit_bl_803ad6b0,s_sysdolphin_base_library_803abbe4,
             s_hsd_dobj_803abbfc,0x48,0x18,in_r9,in_r10);
  DAT_803abb18 = gnt4_DObjRelease_bl;
  DAT_803abb20 = gnt4_DObjAmnesia_bl;
  DAT_803abb24 = gnt4_HSD_DObjDisp_bl;
  DAT_803abb28 = gnt4_DObjLoad_bl;
  return;
}



// ==== 8023de9c  zz_023de9c_ ====

void zz_023de9c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  
  if (param_9 != 0) {
    for (; param_9 != 0; param_9 = *(int *)(param_9 + 8)) {
      if (param_9 != 0) {
        param_1 = gnt4_HSD_AObjRemove(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                      param_8,*(undefined4 **)(param_9 + 100),param_10,param_11,
                                      param_12,param_13,param_14,param_15,param_16);
        *(undefined4 *)(param_9 + 100) = 0;
        param_10 = extraout_r4;
      }
    }
  }
  return;
}



// ==== 8023defc  gnt4-HSD_TObjAddAnim-bl ====

void gnt4_HSD_TObjAddAnim_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  uint *puVar1;
  undefined4 *puVar2;
  int *piVar3;
  undefined4 *puVar4;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  int iVar10;
  undefined8 extraout_f1;
  undefined8 uVar11;
  undefined8 extraout_f1_00;
  undefined8 uVar12;
  
  uVar12 = gnt4__savegpr_27_bl();
  puVar4 = (undefined4 *)uVar12;
  uVar11 = extraout_f1;
  if ((int)((ulonglong)uVar12 >> 0x20) != 0) {
    while( true ) {
      iVar10 = (int)((ulonglong)uVar12 >> 0x20);
      uVar5 = (undefined4)uVar12;
      if (iVar10 == 0) break;
      if (iVar10 != 0) {
        for (puVar9 = puVar4; puVar9 != (undefined4 *)0x0; puVar9 = (undefined4 *)*puVar9) {
          if (puVar9[1] == (uint)*(ushort *)(iVar10 + 0x4a)) goto LAB_8023df58;
        }
        puVar9 = (undefined4 *)0x0;
LAB_8023df58:
        if (puVar9 != (undefined4 *)0x0) {
          if (*(undefined4 **)(iVar10 + 100) != (undefined4 *)0x0) {
            uVar11 = gnt4_HSD_AObjRemove(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,
                                         param_8,*(undefined4 **)(iVar10 + 100),uVar5,param_11,
                                         param_12,param_13,param_14,param_15,param_16);
            uVar5 = extraout_r4;
          }
          puVar1 = gnt4_HSD_AObjLoadDesc
                             (uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              (uint *)puVar9[2],uVar5,param_11,param_12,param_13,param_14,param_15,
                              param_16);
          *(uint **)(iVar10 + 100) = puVar1;
          *(undefined4 *)(iVar10 + 0x68) = puVar9[3];
          if (*(int *)(iVar10 + 0x6c) != 0) {
            iVar7 = 0;
            while( true ) {
              puVar2 = *(undefined4 **)(*(int *)(iVar10 + 0x6c) + iVar7);
              if (puVar2 == (undefined4 *)0x0) break;
              uVar11 = gnt4_HSD_TlutFree_bl
                                 (uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  puVar2,*(int *)(iVar10 + 0x6c),param_11,param_12,param_13,param_14
                                  ,param_15,param_16);
              iVar7 = iVar7 + 4;
            }
            uVar11 = gnt4_HSD_Free_bl();
            uVar5 = extraout_r4_00;
          }
          if (*(ushort *)((int)puVar9 + 0x16) == 0) {
            *(undefined4 *)(iVar10 + 0x6c) = 0;
          }
          else {
            uVar12 = gnt4_HSD_Alloc_bl((*(ushort *)((int)puVar9 + 0x16) + 1) * 4);
            iVar7 = (int)uVar12;
            *(int *)(iVar10 + 0x6c) = (int)((ulonglong)uVar12 >> 0x20);
            iVar8 = 0;
            uVar11 = extraout_f1_00;
            for (iVar6 = 0; iVar6 < (int)(uint)*(ushort *)((int)puVar9 + 0x16); iVar6 = iVar6 + 1) {
              piVar3 = gnt4_HSD_TlutLoadDesc_bl
                                 (uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  *(void **)(puVar9[4] + iVar8),iVar7,param_11,param_12,param_13,
                                  param_14,param_15,param_16);
              iVar7 = *(int *)(iVar10 + 0x6c);
              *(int **)(iVar7 + iVar8) = piVar3;
              iVar8 = iVar8 + 4;
            }
            uVar5 = 0;
            *(undefined4 *)(*(int *)(iVar10 + 0x6c) + iVar6 * 4) = 0;
          }
          *(undefined1 *)(iVar10 + 0x70) = 0xff;
        }
      }
      uVar12 = CONCAT44(*(undefined4 *)(iVar10 + 8),uVar5);
    }
  }
  gnt4__restgpr_27_bl();
  return;
}



// ==== 8023e050  gnt4-HSD_TObjReqAnimAllByFlags-bl ====

void gnt4_HSD_TObjReqAnimAllByFlags_bl(double param_1,int param_2,uint param_3)

{
  if (param_2 != 0) {
    for (; param_2 != 0; param_2 = *(int *)(param_2 + 8)) {
      if ((param_2 != 0) && ((param_3 & 0x10) != 0)) {
        gnt4_HSD_AObjReqAnim(param_1,*(uint **)(param_2 + 100));
      }
    }
  }
  return;
}



// ==== 8023e0c4  gnt4-TObjUpdateFunc-bl ====

void gnt4_TObjUpdateFunc_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
               float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (param_9 == 0) {
    return;
  }
  switch(param_10) {
  case 1:
    if (*(int *)(param_9 + 0x68) == 0) {
      gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435df0
                       ,0x116,s_tobj_>imagetbl_803abc54,param_12,param_13,param_14,param_15,param_16
                      );
    }
    iVar3 = *(int *)(*(int *)(param_9 + 0x68) + (int)*param_11 * 4);
    if (iVar3 != 0) {
      *(int *)(param_9 + 0x58) = iVar3;
    }
    break;
  case 2:
    *(float *)(param_9 + 0x34) = *param_11;
    goto LAB_8023e1fc;
  case 3:
    *(float *)(param_9 + 0x38) = *param_11;
    goto LAB_8023e1fc;
  case 4:
    *(float *)(param_9 + 0x28) = *param_11;
    goto LAB_8023e1fc;
  case 5:
    *(float *)(param_9 + 0x2c) = *param_11;
    goto LAB_8023e1fc;
  case 6:
    *(float *)(param_9 + 0x18) = *param_11;
    goto LAB_8023e1fc;
  case 7:
    *(float *)(param_9 + 0x1c) = *param_11;
    goto LAB_8023e1fc;
  case 8:
    *(float *)(param_9 + 0x20) = *param_11;
LAB_8023e1fc:
    *(uint *)(param_9 + 0x4c) = *(uint *)(param_9 + 0x4c) | 0x80000000;
    break;
  case 9:
    fVar1 = *param_11;
    fVar2 = FLOAT_8043d1a8;
    if ((FLOAT_8043d1a8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ac <= fVar1)) {
      fVar2 = FLOAT_8043d1ac;
    }
    *(float *)(param_9 + 0x50) = fVar2;
    break;
  case 10:
    if (*(int *)(param_9 + 0x6c) != 0) {
      *(char *)(param_9 + 0x70) = (char)(int)*param_11;
    }
    break;
  case 0xb:
    if (*(int *)(param_9 + 0x60) != 0) {
      *(float *)(*(int *)(param_9 + 0x60) + 4) = *param_11;
    }
    break;
  case 0xc:
    if (*(int *)(param_9 + 0xa8) != 0) {
      fVar1 = *param_11;
      fVar2 = FLOAT_8043d1a8;
      if ((FLOAT_8043d1a8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ac <= fVar1)) {
        fVar2 = FLOAT_8043d1ac;
      }
      *(char *)(*(int *)(param_9 + 0xa8) + 0x10) = (char)(int)(FLOAT_8043d1b0 * fVar2);
    }
    break;
  case 0xd:
    if (*(int *)(param_9 + 0xa8) != 0) {
      fVar1 = *param_11;
      fVar2 = FLOAT_8043d1a8;
      if ((FLOAT_8043d1a8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ac <= fVar1)) {
        fVar2 = FLOAT_8043d1ac;
      }
      *(char *)(*(int *)(param_9 + 0xa8) + 0x11) = (char)(int)(FLOAT_8043d1b0 * fVar2);
    }
    break;
  case 0xe:
    if (*(int *)(param_9 + 0xa8) != 0) {
      fVar1 = *param_11;
      fVar2 = FLOAT_8043d1a8;
      if ((FLOAT_8043d1a8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ac <= fVar1)) {
        fVar2 = FLOAT_8043d1ac;
      }
      *(char *)(*(int *)(param_9 + 0xa8) + 0x12) = (char)(int)(FLOAT_8043d1b0 * fVar2);
    }
    break;
  case 0xf:
    if (*(int *)(param_9 + 0xa8) != 0) {
      fVar1 = *param_11;
      fVar2 = FLOAT_8043d1a8;
      if ((FLOAT_8043d1a8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ac <= fVar1)) {
        fVar2 = FLOAT_8043d1ac;
      }
      *(char *)(*(int *)(param_9 + 0xa8) + 0x13) = (char)(int)(FLOAT_8043d1b0 * fVar2);
    }
    break;
  case 0x10:
    if (*(int *)(param_9 + 0xa8) != 0) {
      fVar1 = *param_11;
      fVar2 = FLOAT_8043d1a8;
      if ((FLOAT_8043d1a8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ac <= fVar1)) {
        fVar2 = FLOAT_8043d1ac;
      }
      *(char *)(*(int *)(param_9 + 0xa8) + 0x14) = (char)(int)(FLOAT_8043d1b0 * fVar2);
    }
    break;
  case 0x11:
    if (*(int *)(param_9 + 0xa8) != 0) {
      fVar1 = *param_11;
      fVar2 = FLOAT_8043d1a8;
      if ((FLOAT_8043d1a8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ac <= fVar1)) {
        fVar2 = FLOAT_8043d1ac;
      }
      *(char *)(*(int *)(param_9 + 0xa8) + 0x15) = (char)(int)(FLOAT_8043d1b0 * fVar2);
    }
    break;
  case 0x12:
    if (*(int *)(param_9 + 0xa8) != 0) {
      fVar1 = *param_11;
      fVar2 = FLOAT_8043d1a8;
      if ((FLOAT_8043d1a8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ac <= fVar1)) {
        fVar2 = FLOAT_8043d1ac;
      }
      *(char *)(*(int *)(param_9 + 0xa8) + 0x16) = (char)(int)(FLOAT_8043d1b0 * fVar2);
    }
    break;
  case 0x13:
    if (*(int *)(param_9 + 0xa8) != 0) {
      fVar1 = *param_11;
      fVar2 = FLOAT_8043d1a8;
      if ((FLOAT_8043d1a8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ac <= fVar1)) {
        fVar2 = FLOAT_8043d1ac;
      }
      *(char *)(*(int *)(param_9 + 0xa8) + 0x17) = (char)(int)(FLOAT_8043d1b0 * fVar2);
    }
    break;
  case 0x14:
    if (*(int *)(param_9 + 0xa8) != 0) {
      fVar1 = *param_11;
      fVar2 = FLOAT_8043d1a8;
      if ((FLOAT_8043d1a8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ac <= fVar1)) {
        fVar2 = FLOAT_8043d1ac;
      }
      *(char *)(*(int *)(param_9 + 0xa8) + 0x18) = (char)(int)(FLOAT_8043d1b0 * fVar2);
    }
    break;
  case 0x15:
    if (*(int *)(param_9 + 0xa8) != 0) {
      fVar1 = *param_11;
      fVar2 = FLOAT_8043d1a8;
      if ((FLOAT_8043d1a8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ac <= fVar1)) {
        fVar2 = FLOAT_8043d1ac;
      }
      *(char *)(*(int *)(param_9 + 0xa8) + 0x19) = (char)(int)(FLOAT_8043d1b0 * fVar2);
    }
    break;
  case 0x16:
    if (*(int *)(param_9 + 0xa8) != 0) {
      fVar1 = *param_11;
      fVar2 = FLOAT_8043d1a8;
      if ((FLOAT_8043d1a8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ac <= fVar1)) {
        fVar2 = FLOAT_8043d1ac;
      }
      *(char *)(*(int *)(param_9 + 0xa8) + 0x1a) = (char)(int)(FLOAT_8043d1b0 * fVar2);
    }
    break;
  case 0x17:
    if (*(int *)(param_9 + 0xa8) != 0) {
      fVar1 = *param_11;
      fVar2 = FLOAT_8043d1a8;
      if ((FLOAT_8043d1a8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ac <= fVar1)) {
        fVar2 = FLOAT_8043d1ac;
      }
      *(char *)(*(int *)(param_9 + 0xa8) + 0x1b) = (char)(int)(FLOAT_8043d1b0 * fVar2);
    }
    break;
  case 0x18:
    fVar1 = *param_11;
    fVar2 = FLOAT_8043d1a8;
    if ((FLOAT_8043d1a8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ac <= fVar1)) {
      fVar2 = FLOAT_8043d1ac;
    }
    *(float *)(param_9 + 0x50) = fVar2;
  }
  return;
}



// ==== 8023e690  gnt4-HSD_TObjAnimAll-bl ====

void gnt4_HSD_TObjAnimAll_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int *param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  if (param_9 != (int *)0x0) {
    for (; param_9 != (int *)0x0; param_9 = (int *)param_9[2]) {
      if (param_9 != (int *)0x0) {
        param_1 = gnt4_HSD_AObjInterpretAnim
                            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             (uint *)param_9[0x19],(uint)param_9,*(float **)(*param_9 + 0x48),
                             param_12,param_13,param_14,param_15,param_16);
      }
    }
  }
  return;
}



// ==== 8023e6ec  gnt4-TObjLoad-bl ====

undefined4
gnt4_TObjLoad_bl(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = param_10;
  piVar2 = gnt4_HSD_TObjLoadDesc_bl
                     (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int **)(param_10 + 4),param_10,param_11,param_12,param_13,param_14,param_15,
                      param_16);
  *(int **)(param_9 + 8) = piVar2;
  *(short *)(param_9 + 0x4a) = (short)*(undefined4 *)(param_10 + 8);
  *(undefined4 *)(param_9 + 0x10) = *(undefined4 *)(param_10 + 0xc);
  *(undefined4 *)(param_9 + 0x14) = 0x3c;
  *(undefined4 *)(param_9 + 0x18) = *(undefined4 *)(param_10 + 0x10);
  *(undefined4 *)(param_9 + 0x1c) = *(undefined4 *)(param_10 + 0x14);
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_10 + 0x18);
  uVar1 = *(undefined4 *)(param_10 + 0x20);
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_10 + 0x1c);
  *(undefined4 *)(param_9 + 0x2c) = uVar1;
  *(undefined4 *)(param_9 + 0x30) = *(undefined4 *)(param_10 + 0x24);
  uVar1 = *(undefined4 *)(param_10 + 0x2c);
  *(undefined4 *)(param_9 + 0x34) = *(undefined4 *)(param_10 + 0x28);
  *(undefined4 *)(param_9 + 0x38) = uVar1;
  *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(param_10 + 0x30);
  *(undefined4 *)(param_9 + 0x40) = *(undefined4 *)(param_10 + 0x34);
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(param_10 + 0x38);
  *(undefined1 *)(param_9 + 0x48) = *(undefined1 *)(param_10 + 0x3c);
  *(undefined1 *)(param_9 + 0x49) = *(undefined1 *)(param_10 + 0x3d);
  *(undefined4 *)(param_9 + 0x4c) = *(undefined4 *)(param_10 + 0x40);
  *(undefined4 *)(param_9 + 0x50) = *(undefined4 *)(param_10 + 0x44);
  *(undefined4 *)(param_9 + 0x54) = *(undefined4 *)(param_10 + 0x48);
  *(undefined4 *)(param_9 + 0x58) = *(undefined4 *)(param_10 + 0x4c);
  piVar2 = gnt4_HSD_TlutLoadDesc_bl
                     (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(void **)(param_10 + 0x50),iVar3,param_11,param_12,param_13,param_14,param_15
                      ,param_16);
  *(int **)(param_9 + 0x5c) = piVar2;
  uVar1 = *(undefined4 *)(param_10 + 0x54);
  *(undefined4 *)(param_9 + 0x60) = uVar1;
  *(undefined4 *)(param_9 + 100) = 0;
  *(uint *)(param_9 + 0x4c) = *(uint *)(param_9 + 0x4c) | 0x80000000;
  *(undefined1 *)(param_9 + 0x70) = 0xff;
  piVar2 = gnt4_HSD_TObjTevLoadDesc_bl
                     (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(void **)(param_10 + 0x58),uVar1,param_11,param_12,param_13,param_14,param_15
                      ,param_16);
  *(int **)(param_9 + 0xa8) = piVar2;
  gnt4__HSD_NeedCacheInvalidate_bl(2);
  return 0;
}



// ==== 8023e814  gnt4-HSD_TObjLoadDesc-bl ====

int * gnt4_HSD_TObjLoadDesc_bl
                (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int *param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 *puVar1;
  int *piVar2;
  
  if (param_9 != (int *)0x0) {
    if ((*param_9 == 0) ||
       (puVar1 = (undefined4 *)
                 gnt4_hsdSearchClassInfo_bl
                           (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*param_9
                            ,param_10,param_11,param_12,param_13,param_14,param_15,param_16),
       puVar1 == (undefined4 *)0x0)) {
      piVar2 = gnt4_HSD_TObjAlloc_bl
                         (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    }
    else {
      piVar2 = gnt4_hsdNew_bl(puVar1);
      if (piVar2 == (int *)0x0) {
        gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         &DAT_80435df0,0x1ed,&DAT_80435df8,param_12,param_13,param_14,param_15,
                         param_16);
      }
    }
    (**(code **)(*piVar2 + 0x40))(piVar2,param_9);
    return piVar2;
  }
  return (int *)0x0;
}



// ==== 8023e8ac  gnt4-HSD_TlutLoadDesc-bl ====

int * gnt4_HSD_TlutLoadDesc_bl
                (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,void *param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int *__dest;
  
  if (param_9 == (void *)0x0) {
    __dest = (int *)0x0;
  }
  else {
    __dest = gnt4_HSD_TlutAlloc_bl
                       (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                        param_10,param_11,param_12,param_13,param_14,param_15,param_16);
    gnt4_memcpy(__dest,param_9,0x10);
  }
  return __dest;
}



// ==== 8023e8f8  gnt4-HSD_TObjTevLoadDesc-bl ====

int * gnt4_HSD_TObjTevLoadDesc_bl
                (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,void *param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int *__dest;
  
  if (param_9 == (void *)0x0) {
    __dest = (int *)0x0;
  }
  else {
    __dest = gnt4_HSD_TObjTevAlloc_bl
                       (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                        param_10,param_11,param_12,param_13,param_14,param_15,param_16);
    gnt4_memcpy(__dest,param_9,0x20);
  }
  return __dest;
}



// ==== 8023e944  gnt4-_HSD_TObjGetCurrentByType-bl ====

int gnt4__HSD_TObjGetCurrentByType_bl(int param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = DAT_804368b4;
  if (param_1 != 0) {
    iVar1 = *(int *)(param_1 + 8);
  }
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    if ((*(uint *)(iVar1 + 0x4c) & 0xf) == param_2) break;
    iVar1 = *(int *)(iVar1 + 8);
  }
  return iVar1;
}



// ==== 8023e980  gnt4-HSD_TexMapID2PTTexMtx-bl ====

undefined4
gnt4_HSD_TexMapID2PTTexMtx_bl
          (double param_1,double param_2,double param_3,double param_4,double param_5,double param_6
          ,double param_7,double param_8,undefined4 param_9,undefined4 param_10,undefined4 param_11,
          undefined4 param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
          undefined4 param_16)

{
  undefined4 uVar1;
  
  switch(param_9) {
  case 0:
    uVar1 = 0x40;
    break;
  case 1:
    uVar1 = 0x43;
    break;
  case 2:
    uVar1 = 0x46;
    break;
  case 3:
    uVar1 = 0x49;
    break;
  case 4:
    uVar1 = 0x4c;
    break;
  case 5:
    uVar1 = 0x4f;
    break;
  case 6:
    uVar1 = 0x52;
    break;
  case 7:
    uVar1 = 0x55;
    break;
  default:
    gnt4_HSD_Panic_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435df0,
                      600,s_unexpected_texmap_id__803abcc8,param_12,param_13,param_14,param_15,
                      param_16);
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 8023ea14  gnt4-MakeTextureMtx-bl ====

/* WARNING: Removing unreachable block (ram,0x8023ebcc) */
/* WARNING: Removing unreachable block (ram,0x8023ebc4) */
/* WARNING: Removing unreachable block (ram,0x8023ebbc) */
/* WARNING: Removing unreachable block (ram,0x8023ea34) */
/* WARNING: Removing unreachable block (ram,0x8023ea2c) */
/* WARNING: Removing unreachable block (ram,0x8023ea24) */

void gnt4_MakeTextureMtx_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  bool bVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  float local_98;
  undefined4 local_94;
  float local_90;
  float afStack_88 [12];
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  uint uStack_4c;
  undefined4 local_48;
  uint uStack_44;
  
  bVar2 = false;
  if ((*(char *)(param_9 + 0x48) != '\0') && (*(char *)(param_9 + 0x49) != '\0')) {
    bVar2 = true;
  }
  if (!bVar2) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435df0,
                     0x267,s_tobj_>repeat_s____tobj_>repeat_t_803abd00,param_12,param_13,param_14,
                     param_15,param_16);
  }
  fVar1 = FLOAT_8043d1a8;
  if (FLOAT_8043d1b4 <= ABS(*(float *)(param_9 + 0x28))) {
    uStack_54 = (uint)*(byte *)(param_9 + 0x48);
    local_58 = 0x43300000;
    fVar1 = (float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_8043d1b8) /
            *(float *)(param_9 + 0x28);
  }
  dVar5 = (double)fVar1;
  fVar1 = FLOAT_8043d1a8;
  if (FLOAT_8043d1b4 <= ABS(*(float *)(param_9 + 0x2c))) {
    uStack_4c = (uint)*(byte *)(param_9 + 0x49);
    local_50 = 0x43300000;
    fVar1 = (float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_8043d1b8) /
            *(float *)(param_9 + 0x2c);
  }
  dVar4 = (double)fVar1;
  dVar3 = (double)*(float *)(param_9 + 0x30);
  local_98 = *(float *)(param_9 + 0x18);
  local_94 = *(undefined4 *)(param_9 + 0x1c);
  local_90 = -*(float *)(param_9 + 0x20);
  fVar1 = FLOAT_8043d1a8;
  if (*(int *)(param_9 + 0x44) == 2) {
    uStack_44 = (uint)*(byte *)(param_9 + 0x49);
    local_48 = 0x43300000;
    fVar1 = FLOAT_8043d1ac /
            ((float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_8043d1b8) /
            *(float *)(param_9 + 0x2c));
  }
  gnt4_PSMTXTrans_bl(-(double)*(float *)(param_9 + 0x34),
                     -(double)(*(float *)(param_9 + 0x38) + fVar1),
                     (double)*(float *)(param_9 + 0x3c),(float *)(param_9 + 0x74));
  gnt4_HSD_MkRotationMtx_bl(afStack_88,&local_98);
  gnt4_PSMTXConcat_bl(afStack_88,(float *)(param_9 + 0x74),(float *)(param_9 + 0x74));
  gnt4_PSMTXScale_bl(dVar5,dVar4,dVar3,afStack_88);
  gnt4_PSMTXConcat_bl(afStack_88,(float *)(param_9 + 0x74),(float *)(param_9 + 0x74));
  return;
}



// ==== 8023ebe8  gnt4-TObjSetupMtx-bl ====

void gnt4_TObjSetupMtx_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int *param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  uint uVar6;
  uint extraout_r4;
  float local_b8;
  float local_b4;
  float local_b0;
  float afStack_ac [2];
  float local_a4;
  float afStack_a0 [12];
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  
  uVar6 = param_9[0x13];
  if ((uVar6 & 0xf) != 4) {
    if ((uVar6 & 0x80000000) != 0) {
      param_1 = (**(code **)(*param_9 + 0x3c))();
      param_9[0x13] = param_9[0x13] & 0x7fffffff;
      uVar6 = extraout_r4;
    }
    uVar2 = param_9[0x13] & 0xf;
    if (uVar2 == 2) {
      iVar4 = gnt4_HSD_LObjGetCurrentByType_bl(1);
      if (iVar4 == 0) {
        gnt4_GXLoadTexMtxImm_bl((float *)&DAT_803abd24,param_9[5],0);
      }
      else {
        iVar3 = gnt4_HSD_CObjGetCurrent();
        if (iVar3 == 0) {
          param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                     ,&DAT_80435df0,0x2c2,&DAT_80435e00,param_12,param_13,param_14,
                                     param_15,param_16);
        }
        gnt4_HSD_LObjGetLightVector_bl
                  (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,afStack_ac)
        ;
        gnt4_PSMTXMultVecSR_bl((float *)(iVar3 + 0x54),afStack_ac,afStack_ac);
        local_a4 = local_a4 + FLOAT_8043d1c8;
        gnt4_PSVECNormalize_bl(afStack_ac,&local_b8);
        local_b8 = (float)((double)local_b8 * DOUBLE_8043d1d0);
        local_b4 = (float)((double)local_b4 * DOUBLE_8043d1d0);
        local_b0 = (float)((double)local_b0 * DOUBLE_8043d1d0);
        fVar1 = (float)param_9[0x1d];
        local_70 = fVar1 * local_b8;
        local_6c = fVar1 * local_b4;
        local_68 = fVar1 * local_b0;
        local_64 = FLOAT_8043d1c0 * fVar1 + (float)param_9[0x20];
        fVar1 = (float)param_9[0x21];
        local_60 = fVar1 * local_b8;
        local_5c = fVar1 * local_b4;
        local_58 = fVar1 * local_b0;
        local_54 = FLOAT_8043d1c0 * fVar1 + (float)param_9[0x24];
        local_48 = FLOAT_8043d1a8;
        local_4c = FLOAT_8043d1a8;
        local_50 = FLOAT_8043d1a8;
        local_44 = FLOAT_8043d1ac;
        gnt4_GXLoadTexMtxImm_bl(&local_70,param_9[5],0);
      }
    }
    else {
      if (uVar2 < 2) {
        if (uVar2 != 0) {
          local_40 = FLOAT_8043d1c0 * (float)param_9[0x1d];
          local_3c = FLOAT_8043d1c4 * (float)param_9[0x1e];
          local_38 = FLOAT_8043d1a8;
          local_34 = (float)param_9[0x20] +
                     (float)param_9[0x1f] +
                     FLOAT_8043d1c0 * (float)param_9[0x1d] + FLOAT_8043d1c0 * (float)param_9[0x1e];
          local_30 = FLOAT_8043d1c0 * (float)param_9[0x21];
          local_2c = FLOAT_8043d1c4 * (float)param_9[0x22];
          local_28 = FLOAT_8043d1a8;
          local_24 = (float)param_9[0x24] +
                     (float)param_9[0x23] +
                     FLOAT_8043d1c0 * (float)param_9[0x21] + FLOAT_8043d1c0 * (float)param_9[0x22];
          local_20 = FLOAT_8043d1c0 * (float)param_9[0x25];
          local_1c = FLOAT_8043d1c4 * (float)param_9[0x26];
          local_18 = FLOAT_8043d1a8;
          local_14 = (float)param_9[0x28] +
                     (float)param_9[0x27] +
                     FLOAT_8043d1c0 * (float)param_9[0x25] + FLOAT_8043d1c0 * (float)param_9[0x26];
          gnt4_GXLoadTexMtxImm_bl(&local_40,param_9[5],0);
          return;
        }
      }
      else if (uVar2 < 4) {
        iVar4 = gnt4_HSD_CObjGetCurrent();
        pfVar5 = (float *)gnt4_HSD_CObjGetInvViewingMtxPtrDirect_bl
                                    (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                     ,iVar4,uVar6,param_11,param_12,param_13,param_14,param_15,
                                     param_16);
        gnt4_PSMTXConcat_bl((float *)(param_9 + 0x1d),pfVar5,afStack_a0);
        gnt4_GXLoadTexMtxImm_bl(afStack_a0,param_9[5],0);
        return;
      }
      if ((param_9[0x13] & 0x1000000U) == 0) {
        gnt4_GXLoadTexMtxImm_bl((float *)(param_9 + 0x1d),param_9[5],0);
      }
      else {
        gnt4_GXLoadTexMtxImm_bl((float *)(param_9 + 0x1d),param_9[5],1);
      }
    }
  }
  return;
}



// ==== 8023eed0  gnt4-HSD_TObjSetupTextureCoordGen-bl ====

/* WARNING: Removing unreachable block (ram,0x8023f100) */

void gnt4_HSD_TObjSetupTextureCoordGen_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 in_r9;
  undefined4 in_r10;
  uint uVar6;
  undefined8 uVar7;
  
  for (; param_9 != 0; param_9 = *(int *)(param_9 + 8)) {
    if (*(int *)(param_9 + 0xc) != 0xff) {
      uVar1 = *(uint *)(param_9 + 0x4c);
      if ((uVar1 & 0x1000000) == 0) {
        uVar1 = uVar1 & 0xf;
        if (uVar1 == 4) {
          gnt4_GXSetTexCoordGen2_bl
                    (*(int *)(param_9 + 0xa4),10,*(int *)(param_9 + 0x10),0x3c,0,0x7d);
        }
        else if (uVar1 == 3) {
          gnt4_GXSetTexCoordGen2_bl(*(int *)(param_9 + 0xa4),0,0,0,0,*(int *)(param_9 + 0x14));
        }
        else if ((uVar1 < 3) && (uVar1 != 0)) {
          gnt4_GXSetTexCoordGen2_bl(*(int *)(param_9 + 0xa4),0,1,0x1e,1,*(int *)(param_9 + 0x14));
        }
        else {
          gnt4_GXSetTexCoordGen2_bl
                    (*(int *)(param_9 + 0xa4),1,*(int *)(param_9 + 0x10),0x3c,0,
                     *(int *)(param_9 + 0x14));
        }
      }
      else {
        uVar2 = uVar1 & 0xf;
        if (uVar2 == 3) {
          iVar5 = *(int *)(param_9 + 0x14);
          iVar3 = 0;
          uVar1 = 0;
          uVar4 = 0;
          uVar7 = gnt4_GXSetTexCoordGen2_bl(*(int *)(param_9 + 0xa4),0,0,0,0,iVar5);
        }
        else if ((uVar2 < 3) && (uVar2 != 0)) {
          iVar5 = *(int *)(param_9 + 0x14);
          iVar3 = 1;
          uVar1 = 0x1e;
          uVar4 = 1;
          uVar7 = gnt4_GXSetTexCoordGen2_bl(*(int *)(param_9 + 0xa4),0,1,0x1e,1,iVar5);
        }
        else if ((uVar1 & 0x1000000) == 0) {
          iVar3 = *(int *)(param_9 + 0x10);
          uVar1 = 0x3c;
          iVar5 = *(int *)(param_9 + 0x14);
          uVar4 = 0;
          uVar7 = gnt4_GXSetTexCoordGen2_bl(*(int *)(param_9 + 0xa4),1,iVar3,0x3c,0,iVar5);
        }
        else {
          iVar3 = *(int *)(param_9 + 0x10);
          uVar4 = 0;
          uVar1 = *(uint *)(param_9 + 0x14);
          iVar5 = 0x7d;
          uVar7 = gnt4_GXSetTexCoordGen2_bl(*(int *)(param_9 + 0xa4),1,iVar3,uVar1,0,0x7d);
        }
        uVar2 = gnt4_HSD_LObjGetLightMaskDiffuse_bl();
        uVar6 = 0;
        if ((((((uVar2 & 1) == 0) && (uVar6 = 1, (uVar2 & 2) == 0)) && (uVar6 = 2, (uVar2 & 4) == 0)
             ) && ((uVar6 = 3, (uVar2 & 8) == 0 && (uVar6 = 4, (uVar2 & 0x10) == 0)))) &&
           ((uVar6 = 5, (uVar2 & 0x20) == 0 &&
            ((uVar6 = 6, (uVar2 & 0x40) == 0 && (uVar6 = 7, (uVar2 & 0x80) == 0)))))) {
          uVar6 = 8;
        }
        if (7 < uVar6) {
          uVar6 = 0;
        }
        iVar3 = gnt4_HSD_TexCoordID2TexGenSrc_bl
                          (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           *(undefined4 *)(param_9 + 0xa4),1,iVar3,uVar1,uVar4,iVar5,in_r9,in_r10);
        gnt4_GXSetTexCoordGen2_bl
                  (*(int *)(param_9 + 0xa4) + 1,(&DAT_803abd54)[uVar6],iVar3,0x3c,0,0x7d);
      }
    }
  }
  return;
}



// ==== 8023f160  gnt4-HSD_TObjSetupVolatileTev-bl ====

void gnt4_HSD_TObjSetupVolatileTev_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  int iVar2;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  undefined8 extraout_f1_01;
  undefined8 uVar3;
  
  uVar1 = 0x803b0000;
  iVar2 = param_9;
  do {
    uVar3 = CONCAT44(param_9,uVar1);
    if (iVar2 == 0) {
      return;
    }
    if (*(int *)(iVar2 + 0xc) != 0xff) {
      if ((*(uint *)(iVar2 + 0x4c) & 0x1000000) != 0) {
        DAT_803abdf0 = gnt4_HSD_StateAssignTev_bl
                                 (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  param_9,uVar1,param_11,param_12,param_13,param_14,param_15,
                                  param_16);
        DAT_803abdf4 = *(undefined4 *)(iVar2 + 0xa4);
        DAT_803abdf8 = *(undefined4 *)(iVar2 + 0xc);
        DAT_803abe00 = 0;
        DAT_803abe24 = 0;
        DAT_803abe1c = 0;
        uVar3 = gnt4_HSD_SetupTevStage_bl(-0x7fc54218);
        DAT_803abdf0 = gnt4_HSD_StateAssignTev_bl
                                 (extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,
                                  param_8,(int)((ulonglong)uVar3 >> 0x20),(int)uVar3,param_11,
                                  param_12,param_13,param_14,param_15,param_16);
        DAT_803abdf4 = *(int *)(iVar2 + 0xa4) + 1;
        DAT_803abe00 = 1;
        DAT_803abe24 = 1;
        DAT_803abe1c = 1;
        uVar3 = gnt4_HSD_SetupTevStage_bl(-0x7fc54218);
        param_1 = extraout_f1_00;
      }
      if ((*(uint *)(iVar2 + 0x4c) & 0x100) != 0) {
        uVar3 = CONCAT44(0x803b0000,(int)uVar3);
        while( true ) {
          if ((iVar2 == 0) || ((*(uint *)(iVar2 + 0x4c) & 0xf) != 3)) break;
          DAT_803abd7c = gnt4_HSD_StateAssignTev_bl
                                   (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    (int)((ulonglong)uVar3 >> 0x20),(int)uVar3,param_11,param_12,
                                    param_13,param_14,param_15,param_16);
          DAT_803abd80 = *(undefined4 *)(iVar2 + 0xa4);
          DAT_803abd84 = *(undefined4 *)(iVar2 + 0xc);
          uVar3 = gnt4_HSD_SetupTevStage_bl(-0x7fc5428c);
          iVar2 = *(int *)(iVar2 + 8);
          param_1 = extraout_f1_01;
        }
        return;
      }
    }
    param_9 = (int)((ulonglong)uVar3 >> 0x20);
    uVar1 = (undefined4)uVar3;
    iVar2 = *(int *)(iVar2 + 8);
  } while( true );
}



// ==== 8023f280  gnt4-MakeColorGenTExp-bl ====

void gnt4_MakeColorGenTExp_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               undefined4 *param_11,undefined4 *param_12,int *param_13,undefined4 param_14,
               undefined4 *param_15,undefined4 param_16)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  bool bVar8;
  int iVar9;
  int *piVar10;
  int *piVar11;
  int extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 extraout_r4_04;
  undefined4 extraout_r4_05;
  undefined4 uVar12;
  undefined4 extraout_r4_06;
  undefined4 extraout_r4_07;
  undefined4 extraout_r4_08;
  undefined4 extraout_r4_09;
  byte *pbVar13;
  char *pcVar14;
  int *piVar15;
  int *piVar16;
  char *unaff_r14;
  undefined4 *puVar17;
  undefined4 **ppuVar18;
  int **ppiVar19;
  char **ppcVar20;
  undefined4 *unaff_r23;
  undefined4 *unaff_r24;
  undefined4 *unaff_r25;
  undefined4 *unaff_r26;
  char *unaff_r27;
  char *unaff_r28;
  char *unaff_r29;
  char *unaff_r30;
  byte *pbVar21;
  undefined8 uVar22;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  undefined8 extraout_f1_01;
  undefined8 extraout_f1_02;
  undefined8 extraout_f1_03;
  undefined8 extraout_f1_04;
  undefined8 extraout_f1_05;
  undefined8 extraout_f1_06;
  undefined8 extraout_f1_07;
  undefined4 *local_98 [4];
  undefined4 local_88 [4];
  char *local_78;
  int *local_74;
  undefined4 *local_70;
  undefined4 *local_6c;
  int *local_68 [4];
  int local_58;
  int local_54;
  
  uVar22 = gnt4___save_gpr();
  pbVar21 = *(byte **)(extraout_r4 + 0xa8);
  local_54 = 0;
  bVar2 = false;
  pbVar13 = pbVar21 + 8;
  bVar3 = false;
  local_58 = 0;
  bVar4 = false;
  bVar5 = false;
  bVar6 = false;
  bVar7 = false;
  bVar8 = false;
  iVar9 = 0;
  do {
    piVar15 = (int *)(*pbVar13 - 0x80);
    piVar16 = piVar15;
    if (piVar15 < (int *)0x9) {
      piVar16 = (int *)((int)piVar15 * 4);
      switch(piVar15) {
      case (int *)0x0:
        bVar2 = true;
        break;
      case (int *)0x1:
        bVar3 = true;
        break;
      case (int *)0x2:
        bVar4 = true;
        break;
      case (int *)0x3:
        bVar5 = true;
        break;
      case (int *)0x4:
        bVar6 = true;
        break;
      case (int *)0x5:
        local_54 = 1;
        break;
      case (int *)0x6:
        bVar7 = true;
        break;
      case (int *)0x7:
        local_58 = 1;
        break;
      case (int *)0x8:
        bVar8 = true;
      }
    }
    iVar9 = iVar9 + 1;
    pbVar13 = pbVar13 + 1;
  } while (iVar9 < 4);
  pbVar13 = pbVar21 + 0xc;
  pcVar14 = (char *)0x0;
  iVar9 = 2;
  do {
    bVar1 = *pbVar13;
    if (bVar1 == 0x43) {
      bVar6 = true;
    }
    else if (bVar1 < 0x43) {
      if (bVar1 == 0x41) {
        bVar4 = true;
      }
      else if (bVar1 < 0x41) {
        if (0x3f < bVar1) {
          bVar3 = true;
        }
      }
      else {
        bVar5 = true;
      }
    }
    else if (bVar1 == 0x45) {
      bVar8 = true;
    }
    else if (bVar1 < 0x45) {
      bVar7 = true;
    }
    bVar1 = pbVar13[1];
    if (bVar1 == 0x43) {
      bVar6 = true;
    }
    else if (bVar1 < 0x43) {
      if (bVar1 == 0x41) {
        bVar4 = true;
      }
      else if (bVar1 < 0x41) {
        if (0x3f < bVar1) {
          bVar3 = true;
        }
      }
      else {
        bVar5 = true;
      }
    }
    else if (bVar1 == 0x45) {
      bVar8 = true;
    }
    else if (bVar1 < 0x45) {
      bVar7 = true;
    }
    pcVar14 = pcVar14 + 1;
    pbVar13 = pbVar13 + 2;
    iVar9 = iVar9 + -1;
  } while (iVar9 != 0);
  piVar15 = param_13;
  if (bVar2) {
    pcVar14 = (char *)0x0;
    piVar16 = param_13;
    uVar22 = gnt4_HSD_TExpCnst_bl
                       (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        pbVar21 + 0x10,1,(char *)0x0,param_13,param_13,param_14,param_15,param_16);
    unaff_r14 = (char *)((ulonglong)uVar22 >> 0x20);
    pbVar13 = (byte *)uVar22;
    uVar22 = extraout_f1;
  }
  if (bVar3) {
    pcVar14 = (char *)0x0;
    piVar16 = param_13;
    uVar22 = gnt4_HSD_TExpCnst_bl
                       (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(extraout_r4 + 0xa8) + 0x10,6,(char *)0x0,param_13,piVar15,param_14,
                        param_15,param_16);
    unaff_r30 = (char *)((ulonglong)uVar22 >> 0x20);
    pbVar13 = (byte *)uVar22;
    uVar22 = extraout_f1_00;
  }
  if (bVar4) {
    pcVar14 = (char *)0x0;
    piVar16 = param_13;
    uVar22 = gnt4_HSD_TExpCnst_bl
                       (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(extraout_r4 + 0xa8) + 0x11,6,(char *)0x0,param_13,piVar15,param_14,
                        param_15,param_16);
    unaff_r29 = (char *)((ulonglong)uVar22 >> 0x20);
    pbVar13 = (byte *)uVar22;
    uVar22 = extraout_f1_01;
  }
  if (bVar5) {
    pcVar14 = (char *)0x0;
    piVar16 = param_13;
    uVar22 = gnt4_HSD_TExpCnst_bl
                       (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(extraout_r4 + 0xa8) + 0x12,6,(char *)0x0,param_13,piVar15,param_14,
                        param_15,param_16);
    unaff_r28 = (char *)((ulonglong)uVar22 >> 0x20);
    pbVar13 = (byte *)uVar22;
    uVar22 = extraout_f1_02;
  }
  if (bVar6) {
    pcVar14 = (char *)0x0;
    piVar16 = param_13;
    uVar22 = gnt4_HSD_TExpCnst_bl
                       (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(extraout_r4 + 0xa8) + 0x13,6,(char *)0x0,param_13,piVar15,param_14,
                        param_15,param_16);
    unaff_r27 = (char *)((ulonglong)uVar22 >> 0x20);
    pbVar13 = (byte *)uVar22;
    uVar22 = extraout_f1_03;
  }
  if (local_54 != 0) {
    pcVar14 = (char *)0x0;
    piVar16 = param_13;
    uVar22 = gnt4_HSD_TExpCnst_bl
                       (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(extraout_r4 + 0xa8) + 0x14,1,(char *)0x0,param_13,piVar15,param_14,
                        param_15,param_16);
    unaff_r26 = (undefined4 *)((ulonglong)uVar22 >> 0x20);
    pbVar13 = (byte *)uVar22;
    uVar22 = extraout_f1_04;
  }
  if (bVar7) {
    pcVar14 = (char *)0x0;
    piVar16 = param_13;
    uVar22 = gnt4_HSD_TExpCnst_bl
                       (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(extraout_r4 + 0xa8) + 0x17,6,(char *)0x0,param_13,piVar15,param_14,
                        param_15,param_16);
    unaff_r25 = (undefined4 *)((ulonglong)uVar22 >> 0x20);
    pbVar13 = (byte *)uVar22;
    uVar22 = extraout_f1_05;
  }
  if (local_58 != 0) {
    pcVar14 = (char *)0x0;
    piVar16 = param_13;
    uVar22 = gnt4_HSD_TExpCnst_bl
                       (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(extraout_r4 + 0xa8) + 0x18,1,(char *)0x0,param_13,piVar15,param_14,
                        param_15,param_16);
    unaff_r24 = (undefined4 *)((ulonglong)uVar22 >> 0x20);
    pbVar13 = (byte *)uVar22;
    uVar22 = extraout_f1_06;
  }
  if (bVar8) {
    pcVar14 = (char *)0x0;
    piVar16 = param_13;
    uVar22 = gnt4_HSD_TExpCnst_bl
                       (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(extraout_r4 + 0xa8) + 0x1b,6,(char *)0x0,param_13,piVar15,param_14,
                        param_15,param_16);
    unaff_r23 = (undefined4 *)((ulonglong)uVar22 >> 0x20);
    pbVar13 = (byte *)uVar22;
    uVar22 = extraout_f1_07;
  }
  piVar10 = gnt4_HSD_TExpTev_bl(uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                param_13,pbVar13,pcVar14,piVar16,piVar15,param_14,param_15,param_16)
  ;
  pcVar14 = (char *)0xff;
  uVar22 = gnt4_HSD_TExpOrder_bl
                     (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar10,
                      extraout_r4,0xff,piVar16,piVar15,param_14,param_15,param_16);
  uVar12 = extraout_r4_00;
  if ((*(uint *)(pbVar21 + 0x1c) & 0x40000000) != 0) {
    ppiVar19 = local_68;
    ppcVar20 = &local_78;
    pbVar13 = pbVar21 + 8;
    iVar9 = 0;
    do {
      bVar1 = *pbVar13;
      if (bVar1 == 0x80) {
        *ppcVar20 = unaff_r14;
        *ppiVar19 = (int *)0x1;
      }
      else if (bVar1 < 0x80) {
        if (bVar1 == 0xc) {
          *ppiVar19 = (int *)0x8;
          *ppcVar20 = (char *)0x0;
        }
        else if (bVar1 < 0xc) {
          if (bVar1 == 9) {
            *ppiVar19 = (int *)0x5;
            *ppcVar20 = (char *)0xffffffff;
          }
          else if ((bVar1 < 9) && (7 < bVar1)) {
            *ppiVar19 = (int *)0x1;
            *ppcVar20 = (char *)0xffffffff;
          }
          else {
LAB_8023f89c:
            pcVar14 = &DAT_80435e08;
            uVar22 = gnt4___assert_bl(uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                      ,&DAT_80435df0,0x4c1,&DAT_80435e08,piVar16,piVar15,param_14,
                                      param_15,param_16);
            uVar12 = extraout_r4_05;
          }
        }
        else if (bVar1 == 0xf) {
          *ppiVar19 = (int *)0x7;
          *ppcVar20 = (char *)0x0;
        }
        else {
          if ((0xe < bVar1) || (0xd < bVar1)) goto LAB_8023f89c;
          *ppiVar19 = (int *)0xc;
          *ppcVar20 = (char *)0x0;
        }
      }
      else if (bVar1 == 0x85) {
        piVar11 = gnt4_HSD_TExpTev_bl(uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                      ,param_13,uVar12,pcVar14,piVar16,piVar15,param_14,param_15,
                                      param_16);
        uVar22 = gnt4_HSD_TExpOrder_bl
                           (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar11,0
                            ,0xff,piVar16,piVar15,param_14,param_15,param_16);
        uVar22 = gnt4_HSD_TExpColorOp_bl
                           (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar11,0
                            ,0,0,1,param_14,param_15,param_16);
        pcVar14 = (char *)0x0;
        piVar16 = (int *)0x7;
        piVar15 = (int *)0x0;
        param_14 = 7;
        param_15 = (undefined4 *)0x0;
        param_16 = 1;
        uVar22 = gnt4_HSD_TExpColorIn_bl
                           (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar11,7
                            ,(undefined4 *)0x0,7,(undefined4 *)0x0,7,(undefined4 *)0x0,1,unaff_r26);
        *ppcVar20 = (char *)piVar11;
        *ppiVar19 = (int *)0x1;
        uVar12 = extraout_r4_01;
      }
      else if (bVar1 < 0x85) {
        if (bVar1 == 0x83) {
          *ppcVar20 = unaff_r28;
          *ppiVar19 = (int *)0x6;
        }
        else if (bVar1 < 0x83) {
          if (bVar1 < 0x82) {
            *ppcVar20 = unaff_r30;
            *ppiVar19 = (int *)0x6;
          }
          else {
            *ppcVar20 = unaff_r29;
            *ppiVar19 = (int *)0x6;
          }
        }
        else {
          *ppcVar20 = unaff_r27;
          *ppiVar19 = (int *)0x6;
        }
      }
      else if (bVar1 == 0x88) {
        piVar11 = gnt4_HSD_TExpTev_bl(uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                      ,param_13,uVar12,pcVar14,piVar16,piVar15,param_14,param_15,
                                      param_16);
        uVar22 = gnt4_HSD_TExpOrder_bl
                           (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar11,0
                            ,0xff,piVar16,piVar15,param_14,param_15,param_16);
        uVar22 = gnt4_HSD_TExpColorOp_bl
                           (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar11,0
                            ,0,0,1,param_14,param_15,param_16);
        pcVar14 = (char *)0x0;
        piVar16 = (int *)0x7;
        piVar15 = (int *)0x0;
        param_14 = 7;
        param_15 = (undefined4 *)0x0;
        param_16 = 6;
        uVar22 = gnt4_HSD_TExpColorIn_bl
                           (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar11,7
                            ,(undefined4 *)0x0,7,(undefined4 *)0x0,7,(undefined4 *)0x0,6,unaff_r23);
        *ppcVar20 = (char *)piVar11;
        *ppiVar19 = (int *)0x1;
        uVar12 = extraout_r4_04;
      }
      else {
        if (0x87 < bVar1) goto LAB_8023f89c;
        if (bVar1 < 0x87) {
          piVar11 = gnt4_HSD_TExpTev_bl(uVar22,param_2,param_3,param_4,param_5,param_6,param_7,
                                        param_8,param_13,uVar12,pcVar14,piVar16,piVar15,param_14,
                                        param_15,param_16);
          uVar22 = gnt4_HSD_TExpOrder_bl
                             (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar11
                              ,0,0xff,piVar16,piVar15,param_14,param_15,param_16);
          uVar22 = gnt4_HSD_TExpColorOp_bl
                             (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar11
                              ,0,0,0,1,param_14,param_15,param_16);
          pcVar14 = (char *)0x0;
          piVar16 = (int *)0x7;
          piVar15 = (int *)0x0;
          param_14 = 7;
          param_15 = (undefined4 *)0x0;
          param_16 = 6;
          uVar22 = gnt4_HSD_TExpColorIn_bl
                             (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar11
                              ,7,(undefined4 *)0x0,7,(undefined4 *)0x0,7,(undefined4 *)0x0,6,
                              unaff_r25);
          *ppcVar20 = (char *)piVar11;
          *ppiVar19 = (int *)0x1;
          uVar12 = extraout_r4_02;
        }
        else {
          piVar11 = gnt4_HSD_TExpTev_bl(uVar22,param_2,param_3,param_4,param_5,param_6,param_7,
                                        param_8,param_13,uVar12,pcVar14,piVar16,piVar15,param_14,
                                        param_15,param_16);
          uVar22 = gnt4_HSD_TExpOrder_bl
                             (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar11
                              ,0,0xff,piVar16,piVar15,param_14,param_15,param_16);
          uVar22 = gnt4_HSD_TExpColorOp_bl
                             (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar11
                              ,0,0,0,1,param_14,param_15,param_16);
          pcVar14 = (char *)0x0;
          piVar16 = (int *)0x7;
          piVar15 = (int *)0x0;
          param_14 = 7;
          param_15 = (undefined4 *)0x0;
          param_16 = 1;
          uVar22 = gnt4_HSD_TExpColorIn_bl
                             (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar11
                              ,7,(undefined4 *)0x0,7,(undefined4 *)0x0,7,(undefined4 *)0x0,1,
                              unaff_r24);
          *ppcVar20 = (char *)piVar11;
          *ppiVar19 = (int *)0x1;
          uVar12 = extraout_r4_03;
        }
      }
      iVar9 = iVar9 + 1;
      ppcVar20 = ppcVar20 + 1;
      pbVar13 = pbVar13 + 1;
      ppiVar19 = ppiVar19 + 1;
    } while (iVar9 < 4);
    uVar22 = gnt4_HSD_TExpColorOp_bl
                       (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar10,
                        (uint)*pbVar21,pbVar21[2],(uint)pbVar21[4],(uint)pbVar21[6],param_14,
                        param_15,param_16);
    uVar22 = gnt4_HSD_TExpColorIn_bl
                       (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar10,
                        local_68[0],(undefined4 *)local_78,local_68[1],local_74,local_68[2],local_70
                        ,local_68[3],local_6c);
    *param_11 = piVar10;
    uVar12 = extraout_r4_06;
    pcVar14 = local_78;
    piVar16 = local_68[1];
    piVar15 = local_74;
    param_14 = local_68[2];
    param_15 = local_70;
    param_16 = local_68[3];
  }
  if ((*(uint *)(pbVar21 + 0x1c) & 0x80000000) != 0) {
    puVar17 = local_88;
    ppuVar18 = local_98;
    pbVar13 = pbVar21 + 0xc;
    iVar9 = 0;
    do {
      bVar1 = *pbVar13;
      if (bVar1 == 0x41) {
        *ppuVar18 = (undefined4 *)unaff_r29;
        *puVar17 = 6;
      }
      else if (bVar1 < 0x41) {
        if (bVar1 == 7) {
          *puVar17 = 7;
          *ppuVar18 = (undefined4 *)0x0;
        }
        else if (bVar1 < 7) {
          if (bVar1 == 4) {
            *puVar17 = 5;
            *ppuVar18 = (undefined4 *)0xffffffff;
          }
          else {
LAB_8023fabc:
            pcVar14 = &DAT_80435e08;
            uVar22 = gnt4___assert_bl(uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                      ,&DAT_80435df0,0x50a,&DAT_80435e08,piVar16,piVar15,param_14,
                                      param_15,param_16);
            uVar12 = extraout_r4_09;
          }
        }
        else {
          if (bVar1 < 0x40) goto LAB_8023fabc;
          *ppuVar18 = (undefined4 *)unaff_r30;
          *puVar17 = 6;
        }
      }
      else if (bVar1 == 0x44) {
        piVar11 = gnt4_HSD_TExpTev_bl(uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                      ,param_13,uVar12,pcVar14,piVar16,piVar15,param_14,param_15,
                                      param_16);
        uVar22 = gnt4_HSD_TExpOrder_bl
                           (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar11,0
                            ,0xff,piVar16,piVar15,param_14,param_15,param_16);
        uVar22 = gnt4_HSD_TExpAlphaOp_bl
                           (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar11,0
                            ,0,0,1,param_14,param_15,param_16);
        pcVar14 = (char *)0x0;
        piVar16 = (int *)0x7;
        piVar15 = (int *)0x0;
        param_14 = 7;
        param_15 = (undefined4 *)0x0;
        param_16 = 6;
        uVar22 = gnt4_HSD_TExpAlphaIn_bl
                           (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar11,7
                            ,(undefined4 *)0x0,7,(undefined4 *)0x0,7,(undefined4 *)0x0,6,unaff_r25);
        *ppuVar18 = piVar11;
        *puVar17 = 5;
        uVar12 = extraout_r4_07;
      }
      else if (bVar1 < 0x44) {
        if (bVar1 < 0x43) {
          *ppuVar18 = (undefined4 *)unaff_r28;
          *puVar17 = 6;
        }
        else {
          *ppuVar18 = (undefined4 *)unaff_r27;
          *puVar17 = 6;
        }
      }
      else {
        if (0x45 < bVar1) goto LAB_8023fabc;
        piVar11 = gnt4_HSD_TExpTev_bl(uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                      ,param_13,uVar12,pcVar14,piVar16,piVar15,param_14,param_15,
                                      param_16);
        uVar22 = gnt4_HSD_TExpOrder_bl
                           (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar11,0
                            ,0xff,piVar16,piVar15,param_14,param_15,param_16);
        uVar22 = gnt4_HSD_TExpAlphaOp_bl
                           (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar11,0
                            ,0,0,1,param_14,param_15,param_16);
        pcVar14 = (char *)0x0;
        piVar16 = (int *)0x7;
        piVar15 = (int *)0x0;
        param_14 = 7;
        param_15 = (undefined4 *)0x0;
        param_16 = 6;
        uVar22 = gnt4_HSD_TExpAlphaIn_bl
                           (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar11,7
                            ,(undefined4 *)0x0,7,(undefined4 *)0x0,7,(undefined4 *)0x0,6,unaff_r23);
        *ppuVar18 = piVar11;
        *puVar17 = 5;
        uVar12 = extraout_r4_08;
      }
      iVar9 = iVar9 + 1;
      ppuVar18 = ppuVar18 + 1;
      pbVar13 = pbVar13 + 1;
      puVar17 = puVar17 + 1;
    } while (iVar9 < 4);
    uVar22 = gnt4_HSD_TExpAlphaOp_bl
                       (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar10,
                        (uint)pbVar21[1],pbVar21[3],(uint)pbVar21[5],(uint)pbVar21[7],param_14,
                        param_15,param_16);
    gnt4_HSD_TExpAlphaIn_bl
              (uVar22,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar10,local_88[0],
               local_98[0],local_88[1],local_98[1],local_88[2],local_98[2],local_88[3],local_98[3]);
    *param_12 = piVar10;
  }
  gnt4___restore_gpr();
  return;
}



// ==== 8023fb48  gnt4-TObjMakeTExp-bl ====

void gnt4_TObjMakeTExp_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               char *param_11,int **param_12,int *param_13,int *param_14,int *param_15,
               undefined4 param_16)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  uint uVar5;
  int **ppiVar6;
  int *piVar7;
  int *piVar8;
  int *piVar9;
  undefined8 extraout_f1;
  undefined8 uVar10;
  undefined8 extraout_f1_00;
  undefined8 extraout_f1_01;
  undefined8 uVar11;
  int *local_30;
  int *local_2c [11];
  
  uVar11 = gnt4__savegpr_25_bl();
  iVar2 = (int)((ulonglong)uVar11 >> 0x20);
  local_2c[0] = (int *)0xffffffff;
  uVar5 = (uint)param_11 & *(uint *)(iVar2 + 0x4c) & 0x1f0;
  local_30 = (int *)0xffffffff;
  piVar1 = (int *)-((int)-uVar5 >> 0x1f);
  ppiVar6 = param_12;
  piVar7 = param_13;
  piVar8 = param_14;
  uVar10 = extraout_f1;
  piVar3 = gnt4_HSD_TExpTev_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               param_14,uVar5,param_11,param_12,param_13,param_14,param_15,param_16)
  ;
  if ((*(int *)(iVar2 + 0xa8) != 0) &&
     ((*(uint *)(*(int *)(iVar2 + 0xa8) + 0x1c) & 0xc0000000) != 0)) {
    ppiVar6 = &local_30;
    piVar7 = param_14;
    piVar8 = piVar1;
    uVar10 = gnt4_MakeColorGenTExp_bl
                       (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)uVar11,
                        iVar2,local_2c,ppiVar6,param_14,piVar1,param_15,param_16);
  }
  uVar10 = gnt4_HSD_TExpOrder_bl
                     (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,iVar2,
                      0xff,ppiVar6,piVar7,piVar8,param_15,param_16);
  uVar5 = *(uint *)(iVar2 + 0x4c) & 0xf0000;
  if (uVar5 == 0x40000) {
    uVar10 = gnt4_HSD_TExpColorOp_bl
                       (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,0,0,0,
                        1,piVar8,param_15,param_16);
    ppiVar6 = (int **)0x1;
    piVar7 = *param_12;
    piVar8 = (int *)0x1;
    param_16 = 7;
    piVar9 = local_2c[0];
    uVar10 = gnt4_HSD_TExpColorIn_bl
                       (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,7,
                        (undefined4 *)0x0,1,piVar7,1,local_2c[0],7,(undefined4 *)0x0);
  }
  else if (uVar5 < 0x40000) {
    if (uVar5 == 0x20000) {
      uVar10 = gnt4_HSD_TExpColorOp_bl
                         (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,0,0,
                          0,1,piVar8,param_15,param_16);
      ppiVar6 = (int **)0x1;
      piVar8 = (int *)0x1;
      param_16 = 7;
      piVar7 = local_2c[0];
      piVar9 = local_2c[0];
      uVar10 = gnt4_HSD_TExpColorIn_bl
                         (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,1,
                          *param_12,1,local_2c[0],1,local_2c[0],7,(undefined4 *)0x0);
    }
    else if (uVar5 < 0x20000) {
      if (uVar5 == 0x10000) {
        uVar10 = gnt4_HSD_TExpColorOp_bl
                           (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,0,
                            0,0,1,piVar8,param_15,param_16);
        ppiVar6 = (int **)0x1;
        piVar8 = (int *)0x5;
        param_16 = 7;
        piVar7 = local_2c[0];
        piVar9 = local_30;
        uVar10 = gnt4_HSD_TExpColorIn_bl
                           (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,1,
                            *param_12,1,local_2c[0],5,local_30,7,(undefined4 *)0x0);
      }
      else {
        if ((uVar5 < 0x10000) && (uVar5 == 0)) goto LAB_8023fdfc;
LAB_8023fed4:
        uVar10 = gnt4___assert_bl(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  &DAT_80435df0,0x576,&DAT_80435e08,ppiVar6,piVar7,piVar8,param_15,
                                  param_16);
        piVar9 = param_15;
      }
    }
    else {
      if (uVar5 != 0x30000) goto LAB_8023fed4;
      piVar9 = (int *)gnt4_HSD_TExpCnst_bl
                                (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 iVar2 + 0x50,6,(char *)0x3,param_14,piVar7,piVar8,param_15,param_16
                                );
      uVar10 = gnt4_HSD_TExpColorOp_bl
                         (extraout_f1_00,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          piVar3,0,0,0,1,piVar8,param_15,param_16);
      ppiVar6 = (int **)0x1;
      piVar8 = (int *)0x6;
      param_16 = 7;
      piVar7 = local_2c[0];
      uVar10 = gnt4_HSD_TExpColorIn_bl
                         (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,1,
                          *param_12,1,local_2c[0],6,piVar9,7,(undefined4 *)0x0);
    }
  }
  else if (uVar5 == 0x70000) {
    uVar10 = gnt4_HSD_TExpColorOp_bl
                       (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,0,0,0,
                        1,piVar8,param_15,param_16);
    ppiVar6 = (int **)0x7;
    piVar7 = (int *)0x0;
    piVar8 = (int *)0x7;
    piVar9 = (int *)0x0;
    param_16 = 1;
    uVar10 = gnt4_HSD_TExpColorIn_bl
                       (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,1,
                        local_2c[0],7,(undefined4 *)0x0,7,(undefined4 *)0x0,1,*param_12);
  }
  else if (uVar5 < 0x70000) {
    if (uVar5 == 0x60000) {
LAB_8023fdfc:
      uVar10 = gnt4_HSD_TExpColorOp_bl
                         (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,0,0,
                          0,1,piVar8,param_15,param_16);
      ppiVar6 = (int **)0x7;
      piVar7 = (int *)0x0;
      piVar8 = (int *)0x7;
      piVar9 = (int *)0x0;
      param_16 = 1;
      uVar10 = gnt4_HSD_TExpColorIn_bl
                         (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,7,
                          (undefined4 *)0x0,7,(undefined4 *)0x0,7,(undefined4 *)0x0,1,*param_12);
    }
    else {
      if ((0x5ffff < uVar5) || (uVar5 != 0x50000)) goto LAB_8023fed4;
      uVar10 = gnt4_HSD_TExpColorOp_bl
                         (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,0,0,
                          0,1,piVar8,param_15,param_16);
      ppiVar6 = (int **)0x7;
      piVar7 = (int *)0x0;
      piVar8 = (int *)0x7;
      piVar9 = (int *)0x0;
      param_16 = 1;
      uVar10 = gnt4_HSD_TExpColorIn_bl
                         (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,7,
                          (undefined4 *)0x0,7,(undefined4 *)0x0,7,(undefined4 *)0x0,1,local_2c[0]);
    }
  }
  else {
    if (uVar5 != 0x80000) goto LAB_8023fed4;
    uVar10 = gnt4_HSD_TExpColorOp_bl
                       (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,1,0,0,
                        1,piVar8,param_15,param_16);
    ppiVar6 = (int **)0x7;
    piVar7 = (int *)0x0;
    piVar8 = (int *)0x7;
    piVar9 = (int *)0x0;
    param_16 = 1;
    uVar10 = gnt4_HSD_TExpColorIn_bl
                       (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,1,
                        local_2c[0],7,(undefined4 *)0x0,7,(undefined4 *)0x0,1,*param_12);
  }
  *param_12 = piVar3;
  if (piVar1 != (int *)0x0) goto LAB_80240198;
  uVar5 = *(uint *)(iVar2 + 0x4c) & 0xf00000;
  if (uVar5 == 0x400000) {
    uVar10 = gnt4_HSD_TExpAlphaOp_bl
                       (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,0,0,0,
                        1,piVar8,piVar9,param_16);
    gnt4_HSD_TExpAlphaIn_bl
              (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,7,
               (undefined4 *)0x0,7,(undefined4 *)0x0,7,(undefined4 *)0x0,5,local_30);
  }
  else if (uVar5 < 0x400000) {
    if (uVar5 == 0x200000) {
      puVar4 = (undefined4 *)
               gnt4_HSD_TExpCnst_bl
                         (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          iVar2 + 0x50,6,(char *)0x3,param_14,piVar7,piVar8,piVar9,param_16);
      uVar10 = gnt4_HSD_TExpAlphaOp_bl
                         (extraout_f1_01,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          piVar3,0,0,0,1,piVar8,piVar9,param_16);
      gnt4_HSD_TExpAlphaIn_bl
                (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,5,
                 (undefined4 *)*param_13,5,local_30,6,puVar4,7,(undefined4 *)0x0);
    }
    else if (uVar5 < 0x200000) {
      if (uVar5 == 0x100000) {
        uVar10 = gnt4_HSD_TExpAlphaOp_bl
                           (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,0,
                            0,0,1,piVar8,piVar9,param_16);
        gnt4_HSD_TExpAlphaIn_bl
                  (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,5,
                   (undefined4 *)*param_13,5,local_30,5,local_30,7,(undefined4 *)0x0);
      }
      else {
        if ((uVar5 < 0x100000) && (uVar5 == 0)) goto LAB_802400ac;
LAB_80240184:
        gnt4___assert_bl(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         &DAT_80435df0,0x5b0,&DAT_80435e08,ppiVar6,piVar7,piVar8,piVar9,param_16);
      }
    }
    else {
      if (uVar5 != 0x300000) goto LAB_80240184;
      uVar10 = gnt4_HSD_TExpAlphaOp_bl
                         (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,0,0,
                          0,1,piVar8,piVar9,param_16);
      gnt4_HSD_TExpAlphaIn_bl
                (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,7,
                 (undefined4 *)0x0,5,(undefined4 *)*param_13,5,local_30,7,(undefined4 *)0x0);
    }
  }
  else if (uVar5 == 0x600000) {
    uVar10 = gnt4_HSD_TExpAlphaOp_bl
                       (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,0,0,0,
                        1,piVar8,piVar9,param_16);
    gnt4_HSD_TExpAlphaIn_bl
              (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,5,local_30,7,
               (undefined4 *)0x0,7,(undefined4 *)0x0,5,(undefined4 *)*param_13);
  }
  else if (uVar5 < 0x600000) {
    if (uVar5 != 0x500000) goto LAB_80240184;
LAB_802400ac:
    uVar10 = gnt4_HSD_TExpAlphaOp_bl
                       (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,0,0,0,
                        1,piVar8,piVar9,param_16);
    gnt4_HSD_TExpAlphaIn_bl
              (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,7,
               (undefined4 *)0x0,7,(undefined4 *)0x0,7,(undefined4 *)0x0,5,(undefined4 *)*param_13);
  }
  else {
    if (uVar5 != 0x700000) goto LAB_80240184;
    uVar10 = gnt4_HSD_TExpAlphaOp_bl
                       (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,1,0,0,
                        1,piVar8,piVar9,param_16);
    gnt4_HSD_TExpAlphaIn_bl
              (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,5,local_30,7,
               (undefined4 *)0x0,7,(undefined4 *)0x0,5,(undefined4 *)*param_13);
  }
  *param_13 = (int)piVar3;
LAB_80240198:
  gnt4__restgpr_25_bl();
  return;
}



// ==== 802401b0  gnt4-HSD_TObjAssignResources-bl ====

void gnt4_HSD_TObjAssignResources_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               char *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 extraout_r4;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  double extraout_f1;
  double dVar12;
  
  iVar1 = gnt4__savegpr_25_bl();
  iVar8 = 0;
  uVar7 = 8;
  iVar6 = 0;
  iVar4 = 0;
  iVar11 = iVar1;
  if (iVar1 != 0) {
    for (; iVar11 != 0; iVar11 = *(int *)(iVar11 + 8)) {
      iVar5 = iVar11;
      if (((*(uint *)(iVar11 + 0x4c) & 0xf) != 4) &&
         (iVar5 = iVar4, (*(uint *)(iVar11 + 0x4c) & 0x1000000) != 0)) {
        iVar6 = iVar11;
      }
      iVar4 = iVar5;
    }
    if (iVar4 != 0) {
      uVar7 = 7;
    }
    if (iVar6 != 0) {
      uVar7 = uVar7 - 2;
    }
    uVar3 = 0;
    uVar10 = 0;
    dVar12 = extraout_f1;
    for (iVar11 = iVar1; iVar11 != 0; iVar11 = *(int *)(iVar11 + 8)) {
      uVar9 = uVar10;
      if ((*(uint *)(iVar11 + 0x4c) & 0xf) == 4) {
        if (iVar11 != iVar4) {
          *(undefined4 *)(iVar11 + 0xc) = 0xff;
        }
      }
      else if ((*(uint *)(iVar11 + 0x4c) & 0x1000000) == 0) {
        if (uVar10 < uVar7) {
          uVar9 = uVar10 + 1;
          uVar2 = gnt4_HSD_Index2TexMap_bl
                            (dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,uVar10,
                             uVar3,param_11,param_12,param_13,param_14,param_15,param_16);
          *(undefined4 *)(iVar11 + 0xc) = uVar2;
          switch(*(undefined4 *)(iVar11 + 0xc)) {
          case 0:
            uVar2 = 0x40;
            break;
          case 1:
            uVar2 = 0x43;
            break;
          case 2:
            uVar2 = 0x46;
            break;
          case 3:
            uVar2 = 0x49;
            break;
          case 4:
            uVar2 = 0x4c;
            break;
          case 5:
            uVar2 = 0x4f;
            break;
          case 6:
            uVar2 = 0x52;
            break;
          case 7:
            uVar2 = 0x55;
            break;
          default:
            param_11 = s_unexpected_texmap_id__803abcc8;
            dVar12 = (double)gnt4_HSD_Panic_bl(dVar12,param_2,param_3,param_4,param_5,param_6,
                                               param_7,param_8,&DAT_80435df0,600,
                                               s_unexpected_texmap_id__803abcc8,param_12,param_13,
                                               param_14,param_15,param_16);
            uVar2 = 0;
            uVar3 = extraout_r4;
          }
          *(undefined4 *)(iVar11 + 0x14) = uVar2;
          uVar10 = *(uint *)(iVar11 + 0x4c) & 0xf;
          if ((uVar10 < 4) && (uVar10 != 0)) {
            uVar2 = gnt4_HSD_Index2TexCoord_bl
                              (dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,
                               uVar3,param_11,param_12,param_13,param_14,param_15,param_16);
            *(undefined4 *)(iVar11 + 0xa4) = uVar2;
            iVar8 = iVar8 + 1;
          }
        }
        else {
          *(undefined4 *)(iVar11 + 0xc) = 0xff;
        }
      }
      else if (iVar11 != iVar6) {
        *(undefined4 *)(iVar11 + 0xc) = 0xff;
      }
      uVar10 = uVar9;
    }
    for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 8)) {
      if (((*(int *)(iVar1 + 0xc) != 0xff) && ((*(uint *)(iVar1 + 0x4c) & 0x1000000) == 0)) &&
         ((*(uint *)(iVar1 + 0x4c) & 0xf) == 0)) {
        uVar2 = gnt4_HSD_Index2TexCoord_bl
                          (dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,
                           uVar3,param_11,param_12,param_13,param_14,param_15,param_16);
        *(undefined4 *)(iVar1 + 0xa4) = uVar2;
        iVar8 = iVar8 + 1;
      }
    }
    uVar7 = uVar10;
    if (iVar6 != 0) {
      uVar7 = uVar10 + 1;
      uVar2 = gnt4_HSD_Index2TexMap_bl
                        (dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,uVar10,uVar3
                         ,param_11,param_12,param_13,param_14,param_15,param_16);
      *(undefined4 *)(iVar6 + 0xc) = uVar2;
      *(undefined4 *)(iVar6 + 0x14) = 0x39;
      uVar2 = gnt4_HSD_Index2TexCoord_bl
                        (dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,uVar3,
                         param_11,param_12,param_13,param_14,param_15,param_16);
      *(undefined4 *)(iVar6 + 0xa4) = uVar2;
      iVar8 = iVar8 + 2;
    }
    if (iVar4 != 0) {
      uVar2 = gnt4_HSD_Index2TexMap_bl
                        (dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,uVar7,uVar3,
                         param_11,param_12,param_13,param_14,param_15,param_16);
      *(undefined4 *)(iVar4 + 0xc) = uVar2;
      uVar3 = gnt4_HSD_Index2TexCoord_bl
                        (dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,uVar3,
                         param_11,param_12,param_13,param_14,param_15,param_16);
      *(undefined4 *)(iVar4 + 0xa4) = uVar3;
    }
  }
  gnt4__restgpr_25_bl();
  return;
}



// ==== 80240410  gnt4-HSD_TObjSetup-bl ====

void gnt4_HSD_TObjSetup_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               char *param_11,uint param_12,uint param_13,uint param_14,uint param_15,uint param_16)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  int *piVar5;
  int iVar6;
  int iVar7;
  uint *puVar8;
  uint uVar9;
  uint *puVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  uint *puVar14;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  undefined8 uVar15;
  longlong lVar16;
  uint auStack_80 [3];
  int local_74 [8];
  uint auStack_54 [21];
  
  piVar2 = (int *)gnt4__savegpr_22_bl();
  iVar13 = 0;
  iVar7 = 0;
  uVar12 = 0;
  uVar11 = 0x10;
  DAT_804368b4 = piVar2;
  if (piVar2 != (int *)0x0) {
    lVar16 = gnt4_HSD_TObjAssignResources_bl
                       (extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar2,
                        0x803b0000,param_11,param_12,param_13,param_14,param_15,param_16);
    uVar4 = (undefined4)lVar16;
    uVar15 = extraout_f1_00;
    if (0xffffffff < lVar16) {
      iVar3 = gnt4_HSD_Index2TexCoord_bl
                        (extraout_f1_00,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         (int)((ulonglong)lVar16 >> 0x20) + -1,uVar4,param_11,param_12,param_13,
                         param_14,param_15,param_16);
      uVar15 = gnt4_HSD_StateRegisterTexGen_bl
                         (uVar15,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,uVar4
                          ,param_11,param_12,param_13,param_14,param_15,param_16);
      uVar4 = extraout_r4;
    }
    for (; piVar2 != (int *)0x0; piVar2 = (int *)piVar2[2]) {
      puVar10 = (uint *)piVar2[0x16];
      if (piVar2[3] != 0xff) {
        uVar15 = gnt4_TObjSetupMtx_bl
                           (uVar15,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar2,
                            uVar4,param_11,param_12,param_13,param_14,param_15,param_16);
        if (puVar10 == (uint *)0x0) {
          uVar15 = gnt4___assert_bl(uVar15,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    &DAT_80435df0,0x644,s_imagedesc_803abeb0,param_12,param_13,
                                    param_14,param_15,param_16);
        }
        if (*puVar10 == 0) {
          uVar15 = gnt4___assert_bl(uVar15,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    &DAT_80435df0,0x645,s_imagedesc_>image_ptr_803abebc,param_12,
                                    param_13,param_14,param_15,param_16);
        }
        puVar14 = (uint *)piVar2[0x18];
        if (puVar14 == (uint *)0x0) {
          puVar14 = &DAT_803abea0;
        }
        uVar1 = puVar10[2];
        uVar9 = *puVar14;
        if ((int)uVar1 < 0xb) {
          if (uVar1 != 7) {
            if (6 < (int)uVar1) {
              if (*(byte *)(piVar2 + 0x1c) == 0xff) {
                puVar8 = (uint *)piVar2[0x17];
              }
              else {
                puVar8 = *(uint **)(piVar2[0x1b] + (uint)*(byte *)(piVar2 + 0x1c) * 4);
              }
              if (puVar8 == (uint *)0x0) {
                gnt4___assert_bl(uVar15,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 &DAT_80435df0,0x655,&DAT_80435e0c,param_12,param_13,param_14,
                                 param_15,param_16);
              }
              piVar5 = local_74;
              iVar6 = 0;
              iVar3 = iVar13;
              if (0 < iVar13) {
                do {
                  if (*(short *)(*piVar5 + 0xc) == *(short *)(puVar8 + 3)) break;
                  piVar5 = piVar5 + 1;
                  iVar6 = iVar6 + 1;
                  iVar3 = iVar3 + -1;
                } while (iVar3 != 0);
              }
              if (iVar6 < iVar13) {
                puVar8[2] = *(uint *)(local_74[iVar6] + 8);
              }
              else if (iVar13 < 8) {
                if (*(ushort *)(puVar8 + 3) < 0x101) {
                  puVar8[2] = uVar12;
                  uVar12 = uVar12 + 1;
                }
                else {
                  puVar8[2] = uVar11;
                  uVar11 = uVar11 + 1;
                }
                gnt4_GXInitTlutObj_bl(auStack_80,*puVar8,puVar8[1],*(undefined2 *)(puVar8 + 3));
                gnt4_GXLoadTlut_bl(auStack_80,puVar8[2]);
                iVar13 = iVar13 + 1;
                *(uint **)((int)local_74 + iVar7) = puVar8;
                iVar7 = iVar7 + 4;
              }
              else {
                puVar8[2] = 0;
              }
              uVar1 = -puVar10[3] | puVar10[3];
              param_16 = uVar1 >> 0x1f;
              param_15 = piVar2[0x11];
              gnt4_GXInitTexObjCI_bl
                        (auStack_54,*puVar10,(uint)*(ushort *)(puVar10 + 1),
                         (uint)*(ushort *)((int)puVar10 + 6),puVar10[2],piVar2[0x10],param_15,
                         (byte)(uVar1 >> 0x1f),puVar8[2]);
              if (uVar9 == 5) {
                uVar9 = 3;
              }
              goto LAB_80240684;
            }
            if (-1 < (int)uVar1) goto LAB_80240640;
          }
LAB_80240674:
          gnt4___assert_bl(uVar15,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           &DAT_80435df0,0x691,&DAT_80435e08,param_12,param_13,param_14,param_15,
                           param_16);
        }
        else {
          if (uVar1 != 0xe) goto LAB_80240674;
LAB_80240640:
          uVar1 = -puVar10[3] | puVar10[3];
          param_16 = uVar1 >> 0x1f;
          param_15 = piVar2[0x11];
          gnt4_GXInitTexObj_bl
                    (auStack_54,*puVar10,(uint)*(ushort *)(puVar10 + 1),
                     (uint)*(ushort *)((int)puVar10 + 6),puVar10[2],piVar2[0x10],param_15,
                     (byte)(uVar1 >> 0x1f));
        }
LAB_80240684:
        if (puVar10[3] == 0) {
          uVar9 = uVar9 & 1;
        }
        param_11 = (char *)piVar2[0x15];
        param_2 = (double)(float)puVar10[5];
        param_3 = (double)(float)puVar14[1];
        param_12 = (uint)*(byte *)(puVar14 + 2);
        param_13 = (uint)*(byte *)((int)puVar14 + 9);
        param_14 = puVar14[3];
        gnt4_GXInitTexObjLOD_bl
                  ((double)(float)puVar10[4],param_2,param_3,auStack_54,uVar9,(int)param_11,param_12
                   ,*(byte *)((int)puVar14 + 9),param_14);
        uVar15 = gnt4_GXLoadTexObj_bl(auStack_54,piVar2[3]);
        uVar4 = extraout_r4_00;
      }
    }
  }
  gnt4__restgpr_22_bl();
  return;
}



// ==== 802406ec  gnt4-HSD_TGTex2Index-bl ====

undefined4
gnt4_HSD_TGTex2Index_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
          undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  
  switch(param_9) {
  case 4:
    uVar1 = 0;
    break;
  case 5:
    uVar1 = 1;
    break;
  case 6:
    uVar1 = 2;
    break;
  case 7:
    uVar1 = 3;
    break;
  case 8:
    uVar1 = 4;
    break;
  case 9:
    uVar1 = 5;
    break;
  case 10:
    uVar1 = 6;
    break;
  case 0xb:
    uVar1 = 7;
    break;
  default:
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435df0,
                     0x6bf,&DAT_80435e08,param_12,param_13,param_14,param_15,param_16);
    uVar1 = 4;
  }
  return uVar1;
}



// ==== 80240780  gnt4-HSD_TexCoordID2TexGenSrc-bl ====

undefined4
gnt4_HSD_TexCoordID2TexGenSrc_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
          undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  
  switch(param_9) {
  case 0:
    uVar1 = 0xc;
    break;
  case 1:
    uVar1 = 0xd;
    break;
  case 2:
    uVar1 = 0xe;
    break;
  case 3:
    uVar1 = 0xf;
    break;
  case 4:
    uVar1 = 0x10;
    break;
  case 5:
    uVar1 = 0x11;
    break;
  case 6:
    uVar1 = 0x12;
    break;
  default:
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435df0,
                     0x6e4,&DAT_80435e08,param_12,param_13,param_14,param_15,param_16);
    uVar1 = 0xc;
  }
  return uVar1;
}



// ==== 80240808  gnt4-HSD_TexCoord2Index-bl ====

undefined4
gnt4_HSD_TexCoord2Index_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
          undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  
  switch(param_9) {
  case 0:
    uVar1 = 0;
    break;
  case 1:
    uVar1 = 1;
    break;
  case 2:
    uVar1 = 2;
    break;
  case 3:
    uVar1 = 3;
    break;
  case 4:
    uVar1 = 4;
    break;
  case 5:
    uVar1 = 5;
    break;
  case 6:
    uVar1 = 6;
    break;
  case 7:
    uVar1 = 7;
    break;
  default:
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435df0,
                     0x70a,&DAT_80435e08,param_12,param_13,param_14,param_15,param_16);
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80240898  gnt4-HSD_Index2TexCoord-bl ====

undefined4
gnt4_HSD_Index2TexCoord_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
          undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  
  switch(param_9) {
  case 0:
    uVar1 = 0;
    break;
  case 1:
    uVar1 = 1;
    break;
  case 2:
    uVar1 = 2;
    break;
  case 3:
    uVar1 = 3;
    break;
  case 4:
    uVar1 = 4;
    break;
  case 5:
    uVar1 = 5;
    break;
  case 6:
    uVar1 = 6;
    break;
  case 7:
    uVar1 = 7;
    break;
  default:
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435df0,
                     0x722,&DAT_80435e08,param_12,param_13,param_14,param_15,param_16);
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80240928  gnt4-HSD_TexMtx2Index-bl ====

undefined4
gnt4_HSD_TexMtx2Index_bl
          (double param_1,double param_2,double param_3,double param_4,double param_5,double param_6
          ,double param_7,double param_8,undefined4 param_9,undefined4 param_10,undefined4 param_11,
          undefined4 param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
          undefined4 param_16)

{
  undefined4 uVar1;
  
  switch(param_9) {
  case 0x1e:
    uVar1 = 0;
    break;
  default:
    gnt4_HSD_Panic_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435df0,
                      0x74f,s_specified_texmtx_id_desn_t_exist_803abf54,param_12,param_13,param_14,
                      param_15,param_16);
    uVar1 = 0xffffffff;
    break;
  case 0x21:
    uVar1 = 1;
    break;
  case 0x24:
    uVar1 = 2;
    break;
  case 0x27:
    uVar1 = 3;
    break;
  case 0x2a:
    uVar1 = 4;
    break;
  case 0x2d:
    uVar1 = 5;
    break;
  case 0x30:
    uVar1 = 6;
    break;
  case 0x33:
    uVar1 = 7;
    break;
  case 0x36:
    uVar1 = 8;
    break;
  case 0x39:
    uVar1 = 9;
    break;
  case 0x3c:
    uVar1 = 10;
  }
  return uVar1;
}



// ==== 802409d8  gnt4-HSD_Index2TexMtx-bl ====

undefined4
gnt4_HSD_Index2TexMtx_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
          undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  double dVar2;
  
  switch(param_9) {
  case 0:
    uVar1 = 0x1e;
    break;
  case 1:
    uVar1 = 0x21;
    break;
  case 2:
    uVar1 = 0x24;
    break;
  case 3:
    uVar1 = 0x27;
    break;
  case 4:
    uVar1 = 0x2a;
    break;
  case 5:
    uVar1 = 0x2d;
    break;
  case 6:
    uVar1 = 0x30;
    break;
  case 7:
    uVar1 = 0x33;
    break;
  case 8:
    uVar1 = 0x36;
    break;
  case 9:
    uVar1 = 0x39;
    break;
  case 10:
    uVar1 = 0x3c;
    break;
  default:
    dVar2 = (double)gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                     ,s_texmtx_index_exceed_hardware_lim_803abff4,param_9,0x803b0000
                                     ,param_12,param_13,param_14,param_15,param_16);
    gnt4_HSD_Panic_bl(dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435df0,
                      0x76f,&DAT_80435e14,param_12,param_13,param_14,param_15,param_16);
    uVar1 = 0x3c;
  }
  return uVar1;
}



// ==== 80240a94  gnt4-HSD_Index2TexMap-bl ====

undefined4
gnt4_HSD_Index2TexMap_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
          undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  
  switch(param_9) {
  case 0:
    uVar1 = 0;
    break;
  case 1:
    uVar1 = 1;
    break;
  case 2:
    uVar1 = 2;
    break;
  case 3:
    uVar1 = 3;
    break;
  case 4:
    uVar1 = 4;
    break;
  case 5:
    uVar1 = 5;
    break;
  case 6:
    uVar1 = 6;
    break;
  case 7:
    uVar1 = 7;
    break;
  default:
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435df0,
                     0x795,&DAT_80435e08,param_12,param_13,param_14,param_15,param_16);
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80240b24  gnt4-HSD_TexMap2Index-bl ====

undefined4
gnt4_HSD_TexMap2Index_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
          undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  
  switch(param_9) {
  case 0:
    uVar1 = 0;
    break;
  case 1:
    uVar1 = 1;
    break;
  case 2:
    uVar1 = 2;
    break;
  case 3:
    uVar1 = 3;
    break;
  case 4:
    uVar1 = 4;
    break;
  case 5:
    uVar1 = 5;
    break;
  case 6:
    uVar1 = 6;
    break;
  case 7:
    uVar1 = 7;
    break;
  default:
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435df0,
                     0x7ad,&DAT_80435e08,param_12,param_13,param_14,param_15,param_16);
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80240bb4  gnt4-HSD_TObjRemoveAll-bl ====

void gnt4_HSD_TObjRemoveAll_bl(int *param_1)

{
  int *piVar1;
  
  while (piVar1 = param_1, piVar1 != (int *)0x0) {
    param_1 = (int *)piVar1[2];
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 0x30))(piVar1);
      (**(code **)(*piVar1 + 0x34))(piVar1);
    }
  }
  return;
}



// ==== 80240c28  zz_0240c28_ ====

undefined4 zz_0240c28_(int param_1)

{
  if (param_1 == 0) {
    return 0;
  }
  return *(undefined4 *)(param_1 + 8);
}



// ==== 80240c40  gnt4-HSD_TObjAlloc-bl ====

int * gnt4_HSD_TObjAlloc_bl
                (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  int *piVar1;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined **ppuVar2;
  
  ppuVar2 = DAT_804368b0;
  if (DAT_804368b0 == (undefined **)0x0) {
    ppuVar2 = &PTR_gnt4_TObjInfoInit_bl_803abc08;
  }
  piVar1 = gnt4_hsdNew_bl(ppuVar2);
  if (piVar1 == (int *)0x0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435df0,
                     0x812,&DAT_80435e18,in_r6,in_r7,in_r8,in_r9,in_r10);
  }
  return piVar1;
}



// ==== 80240c9c  gnt4-HSD_TlutAlloc-bl ====

int * gnt4_HSD_TlutAlloc_bl
                (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int *__s;
  
  __s = gnt4_hsdAllocMemPiece_bl
                  (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x10,param_10,
                   param_11,param_12,param_13,param_14,param_15,param_16);
  if (__s == (int *)0x0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435df0,
                     0x82f,&DAT_80435e0c,param_12,param_13,param_14,param_15,param_16);
  }
  gnt4_memset(__s,0,0x10);
  return __s;
}



// ==== 80240cf4  gnt4-HSD_TlutFree-bl ====

void gnt4_HSD_TlutFree_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 *param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  if (param_9 != (undefined4 *)0x0) {
    gnt4_hsdFreeMemPiece_bl
              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11
               ,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 80240d20  gnt4-HSD_TObjTevAlloc-bl ====

int * gnt4_HSD_TObjTevAlloc_bl
                (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int *__s;
  
  __s = gnt4_hsdAllocMemPiece_bl
                  (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x20,param_10,
                   param_11,param_12,param_13,param_14,param_15,param_16);
  if (__s == (int *)0x0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435df0,
                     0x85a,&DAT_80435e1c,param_12,param_13,param_14,param_15,param_16);
  }
  gnt4_memset(__s,0,0x20);
  return __s;
}



