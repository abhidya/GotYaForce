// ==== 80088f98  zz_0088f98_ ====

void zz_0088f98_(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = *(int *)(param_1 + 4);
  iVar2 = *(int *)(param_1 + 8);
  uVar3 = (uint)*(char *)(param_1 + 1);
  if ((iVar1 == 0) && (iVar2 == 0)) {
    (&DAT_803c706c)[uVar3] = 0;
    (&DAT_803c6f6c)[uVar3] = 0;
  }
  else if ((iVar1 == 0) && (iVar2 != 0)) {
    (&DAT_803c706c)[uVar3] = iVar2;
    *(undefined4 *)(iVar2 + 4) = 0;
  }
  else if ((iVar1 == 0) || (iVar2 != 0)) {
    *(int *)(iVar1 + 8) = iVar2;
    *(int *)(iVar2 + 4) = iVar1;
  }
  else {
    (&DAT_803c6f6c)[uVar3] = iVar1;
    *(undefined4 *)(iVar1 + 8) = 0;
  }
  if ((int)uVar3 < 0x38) {
    if ((param_2 != 0) && (*(char *)(param_2 + 0x83) == '\0')) {
      uVar3 = (uVar3 & 0xfffffff8) + *(char *)(param_2 + 0x3e4) + 1;
    }
  }
  *(char *)(param_1 + 1) = (char)uVar3;
  if (param_3 == 0) {
    iVar1 = (&DAT_803c706c)[uVar3];
    (&DAT_803c706c)[uVar3] = param_1;
    *(undefined4 *)(param_1 + 4) = 0;
    if (iVar1 == 0) {
      (&DAT_803c6f6c)[uVar3] = param_1;
      *(undefined4 *)(param_1 + 8) = 0;
      return;
    }
    *(int *)(param_1 + 8) = iVar1;
    *(int *)(iVar1 + 4) = param_1;
    return;
  }
  iVar1 = (&DAT_803c6f6c)[uVar3];
  (&DAT_803c6f6c)[uVar3] = param_1;
  *(undefined4 *)(param_1 + 8) = 0;
  if (iVar1 == 0) {
    (&DAT_803c706c)[uVar3] = param_1;
    *(undefined4 *)(param_1 + 4) = 0;
    return;
  }
  *(int *)(param_1 + 4) = iVar1;
  *(int *)(iVar1 + 8) = param_1;
  return;
}



// ==== 80089100  zz_0089100_ ====

void zz_0089100_(int param_1,uint param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x100) == 0) {
    return;
  }
  *(char *)(param_1 + 0x85) = (char)param_2;
  if ((param_2 & 0x40) != 0) {
    if (param_3 != 0) {
      uVar1 = param_2 & 0xf;
      iVar2 = (&DAT_80436278)[uVar1];
      (&DAT_80436278)[uVar1] = param_1;
      *(undefined4 *)(param_1 + 0x108) = 0;
      if (iVar2 == 0) {
        (&DAT_80436280)[uVar1] = param_1;
        *(undefined4 *)(param_1 + 0x104) = 0;
        return;
      }
      *(int *)(param_1 + 0x104) = iVar2;
      *(int *)(iVar2 + 0x108) = param_1;
      return;
    }
    uVar1 = param_2 & 0xf;
    iVar2 = (&DAT_80436280)[uVar1];
    (&DAT_80436280)[uVar1] = param_1;
    *(undefined4 *)(param_1 + 0x104) = 0;
    if (iVar2 == 0) {
      (&DAT_80436278)[uVar1] = param_1;
      *(undefined4 *)(param_1 + 0x108) = 0;
      return;
    }
    *(int *)(param_1 + 0x108) = iVar2;
    *(int *)(iVar2 + 0x104) = param_1;
    return;
  }
  if ((param_2 & 0x20) != 0) {
    if (param_3 != 0) {
      uVar1 = param_2 & 0xf;
      iVar2 = (&DAT_80436268)[uVar1];
      (&DAT_80436268)[uVar1] = param_1;
      *(undefined4 *)(param_1 + 0x108) = 0;
      if (iVar2 == 0) {
        (&DAT_80436270)[uVar1] = param_1;
        *(undefined4 *)(param_1 + 0x104) = 0;
        return;
      }
      *(int *)(param_1 + 0x104) = iVar2;
      *(int *)(iVar2 + 0x108) = param_1;
      return;
    }
    uVar1 = param_2 & 0xf;
    iVar2 = (&DAT_80436270)[uVar1];
    (&DAT_80436270)[uVar1] = param_1;
    *(undefined4 *)(param_1 + 0x104) = 0;
    if (iVar2 == 0) {
      (&DAT_80436268)[uVar1] = param_1;
      *(undefined4 *)(param_1 + 0x108) = 0;
      return;
    }
    *(int *)(param_1 + 0x108) = iVar2;
    *(int *)(iVar2 + 0x104) = param_1;
    return;
  }
  if ((param_2 & 0x10) == 0) {
    if (param_3 != 0) {
      iVar2 = (&DAT_80436288)[param_2];
      (&DAT_80436288)[param_2] = param_1;
      *(undefined4 *)(param_1 + 0x108) = 0;
      if (iVar2 == 0) {
        (&DAT_80436290)[param_2] = param_1;
        *(undefined4 *)(param_1 + 0x104) = 0;
        return;
      }
      *(int *)(param_1 + 0x104) = iVar2;
      *(int *)(iVar2 + 0x108) = param_1;
      return;
    }
    iVar2 = (&DAT_80436290)[param_2];
    (&DAT_80436290)[param_2] = param_1;
    *(undefined4 *)(param_1 + 0x104) = 0;
    if (iVar2 == 0) {
      (&DAT_80436288)[param_2] = param_1;
      *(undefined4 *)(param_1 + 0x108) = 0;
      return;
    }
    *(int *)(param_1 + 0x108) = iVar2;
    *(int *)(iVar2 + 0x104) = param_1;
    return;
  }
  if (param_3 != 0) {
    uVar1 = param_2 & 0xf;
    iVar2 = (&DAT_803c6f3c)[uVar1];
    (&DAT_803c6f3c)[uVar1] = param_1;
    *(undefined4 *)(param_1 + 0x108) = 0;
    if (iVar2 == 0) {
      (&DAT_803c6f54)[uVar1] = param_1;
      *(undefined4 *)(param_1 + 0x104) = 0;
      return;
    }
    *(int *)(param_1 + 0x104) = iVar2;
    *(int *)(iVar2 + 0x108) = param_1;
    return;
  }
  uVar1 = param_2 & 0xf;
  iVar2 = (&DAT_803c6f54)[uVar1];
  (&DAT_803c6f54)[uVar1] = param_1;
  *(undefined4 *)(param_1 + 0x104) = 0;
  if (iVar2 == 0) {
    (&DAT_803c6f3c)[uVar1] = param_1;
    *(undefined4 *)(param_1 + 0x108) = 0;
    return;
  }
  *(int *)(param_1 + 0x108) = iVar2;
  *(int *)(iVar2 + 0x104) = param_1;
  return;
}



// ==== 80089338  zz_0089338_ ====

void zz_0089338_(int param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  
  if (*(int *)(param_1 + 0x100) == 0) {
    return;
  }
  *(undefined1 *)(param_1 + 0x85) = *(undefined1 *)(param_2 + 0x85);
  if (param_3 != 0) {
    iVar1 = *(int *)(param_2 + 0x108);
    *(int *)(param_2 + 0x108) = param_1;
    *(int *)(param_1 + 0x104) = param_2;
    *(int *)(param_1 + 0x108) = iVar1;
    if (iVar1 != 0) {
      *(int *)(iVar1 + 0x104) = param_1;
      return;
    }
    uVar2 = (uint)*(char *)(param_2 + 0x85);
    if ((uVar2 & 0x20) != 0) {
      (&DAT_80436268)[uVar2 & 0xf] = param_1;
      return;
    }
    if ((uVar2 & 0x10) != 0) {
      (&DAT_803c6f3c)[uVar2 & 0xf] = param_1;
      return;
    }
    (&DAT_80436288)[uVar2] = param_1;
    return;
  }
  iVar1 = *(int *)(param_2 + 0x104);
  *(int *)(param_2 + 0x104) = param_1;
  *(int *)(param_1 + 0x104) = iVar1;
  *(int *)(param_1 + 0x108) = param_2;
  if (iVar1 != 0) {
    *(int *)(iVar1 + 0x108) = param_1;
    return;
  }
  uVar2 = (uint)*(char *)(param_2 + 0x85);
  if ((uVar2 & 0x40) != 0) {
    (&DAT_80436280)[uVar2 & 0xf] = param_1;
    return;
  }
  if ((uVar2 & 0x20) != 0) {
    (&DAT_80436270)[uVar2 & 0xf] = param_1;
    return;
  }
  if ((uVar2 & 0x10) != 0) {
    (&DAT_803c6f54)[uVar2 & 0xf] = param_1;
    return;
  }
  (&DAT_80436290)[uVar2] = param_1;
  return;
}



// ==== 80089444  zz_0089444_ ====

void zz_0089444_(int param_1)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  uVar3 = (uint)*(char *)(param_1 + 0x85);
  if (uVar3 == 0xffffffff) {
    return;
  }
  iVar4 = *(int *)(param_1 + 0x104);
  iVar5 = *(int *)(param_1 + 0x108);
  if ((uVar3 & 0x40) == 0) {
    if ((uVar3 & 0x20) == 0) {
      if ((uVar3 & 0x10) == 0) {
        piVar1 = &DAT_80436290 + uVar3;
        piVar2 = &DAT_80436288 + uVar3;
      }
      else {
        piVar1 = &DAT_803c6f54 + (uVar3 & 0xf);
        piVar2 = &DAT_803c6f3c + (uVar3 & 0xf);
      }
    }
    else {
      piVar1 = &DAT_80436270 + (uVar3 & 0xf);
      piVar2 = &DAT_80436268 + (uVar3 & 0xf);
    }
  }
  else {
    piVar1 = &DAT_80436280 + (uVar3 & 0xf);
    piVar2 = &DAT_80436278 + (uVar3 & 0xf);
  }
  if ((iVar4 == 0) && (iVar5 == 0)) {
    *piVar1 = 0;
    *piVar2 = 0;
  }
  else if ((iVar4 == 0) && (iVar5 != 0)) {
    *piVar1 = iVar5;
    *(undefined4 *)(iVar5 + 0x104) = 0;
  }
  else if ((iVar4 == 0) || (iVar5 != 0)) {
    *(int *)(iVar4 + 0x108) = iVar5;
    *(int *)(iVar5 + 0x104) = iVar4;
  }
  else {
    *piVar2 = iVar4;
    *(undefined4 *)(iVar4 + 0x108) = 0;
  }
  *(undefined4 *)(param_1 + 0x100) = 0;
  *(undefined1 *)(param_1 + 0x85) = 0xff;
  return;
}



// ==== 80089554  zz_0089554_ ====

void zz_0089554_(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = &DAT_80436290;
  iVar2 = 0;
  do {
    for (iVar1 = *piVar3; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x108)) {
      if (*(code **)(iVar1 + 0x100) != (code *)0x0) {
        (**(code **)(iVar1 + 0x100))(iVar1);
      }
    }
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 1;
  } while (iVar2 < 2);
  iVar2 = 0;
  piVar3 = &DAT_80436280;
  do {
    for (iVar1 = *piVar3; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x108)) {
      if (*(code **)(iVar1 + 0x100) != (code *)0x0) {
        (**(code **)(iVar1 + 0x100))(iVar1);
      }
    }
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 1;
  } while (iVar2 < 2);
  iVar2 = 0;
  piVar3 = &DAT_803c6f54;
  do {
    for (iVar1 = *piVar3; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x108)) {
      if (*(code **)(iVar1 + 0x100) != (code *)0x0) {
        (**(code **)(iVar1 + 0x100))(iVar1);
      }
    }
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 1;
  } while (iVar2 < 6);
  return;
}



// ==== 80089658  zz_0089658_ ====

void zz_0089658_(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = &DAT_80436270;
  iVar1 = 0;
  do {
    for (iVar2 = *piVar3; iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x108)) {
      if (*(code **)(iVar2 + 0x100) != (code *)0x0) {
        (**(code **)(iVar2 + 0x100))(iVar2);
      }
    }
    iVar1 = iVar1 + 1;
    piVar3 = piVar3 + 1;
  } while (iVar1 < 2);
  return;
}



// ==== 800896d0  zz_00896d0_ ====

void zz_00896d0_(int param_1)

{
  int iVar1;
  
  for (iVar1 = (&DAT_803c6f54)[param_1]; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x108)) {
    if (*(code **)(iVar1 + 0x100) != (code *)0x0) {
      (**(code **)(iVar1 + 0x100))(iVar1);
    }
  }
  return;
}



// ==== 8008972c  zz_008972c_ ====

void zz_008972c_(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = &DAT_80436280;
  iVar1 = 0;
  do {
    for (iVar2 = *piVar3; iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x108)) {
      if (*(code **)(iVar2 + 0x100) != (code *)0x0) {
        (**(code **)(iVar2 + 0x100))(iVar2);
      }
    }
    iVar1 = iVar1 + 1;
    piVar3 = piVar3 + 1;
  } while (iVar1 < 2);
  return;
}



// ==== 800897a4  zz_00897a4_ ====

void zz_00897a4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  undefined1 *puVar1;
  
  for (puVar1 = (undefined1 *)(&DAT_803c706c)[param_9]; puVar1 != (undefined1 *)0x0;
      puVar1 = *(undefined1 **)(puVar1 + 8)) {
    param_1 = zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar1);
  }
  (&DAT_803c706c)[param_9] = 0;
  (&DAT_803c6f6c)[param_9] = 0;
  return;
}



// ==== 80089814  zz_0089814_ ====

void zz_0089814_(undefined1 *param_1)

{
  if ((&DAT_803c718c)[(char)param_1[3]] == 0) {
    (&DAT_803c718c)[(char)param_1[3]] = param_1;
    (&DAT_803c716c)[(char)param_1[3]] = param_1;
  }
  else {
    *(undefined1 **)((&DAT_803c718c)[(char)param_1[3]] + 4) = param_1;
    (&DAT_803c718c)[(char)param_1[3]] = param_1;
  }
  (&DAT_803c71ac)[(char)param_1[3]] = (&DAT_803c71ac)[(char)param_1[3]] + 1;
  *param_1 = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  return;
}



// ==== 80089898  zz_0089898_ ====

void zz_0089898_(uint param_1)

{
  byte bVar1;
  char *pcVar2;
  
  if (((int)param_1 < 0x38) && ((param_1 & 7) != 7)) {
    if ((int)param_1 < 8) {
      bVar1 = PTR_DAT_80433934[0xd2];
    }
    else {
      bVar1 = PTR_DAT_80433934[0xd1];
    }
    if ((bVar1 & 0x80) != 0) {
      return;
    }
  }
  for (pcVar2 = (char *)(&DAT_803c706c)[param_1]; pcVar2 != (char *)0x0;
      pcVar2 = *(char **)(pcVar2 + 8)) {
    if (*pcVar2 != '\0') {
      *(undefined4 *)(pcVar2 + 0x2c) = *(undefined4 *)(pcVar2 + 0x20);
      *(undefined4 *)(pcVar2 + 0x30) = *(undefined4 *)(pcVar2 + 0x24);
      *(undefined4 *)(pcVar2 + 0x34) = *(undefined4 *)(pcVar2 + 0x28);
      *(undefined4 *)(pcVar2 + 0x76) = *(undefined4 *)(pcVar2 + 0x70);
      *(undefined2 *)(pcVar2 + 0x7a) = *(undefined2 *)(pcVar2 + 0x74);
      (**(code **)(pcVar2 + 0xc))(pcVar2);
      if (pcVar2[0x86] != '\0') {
        pcVar2[0x1ca] = '\0';
      }
    }
  }
  return;
}



// ==== 8008997c  zz_008997c_ ====

void zz_008997c_(int param_1)

{
  uint uVar1;
  char *pcVar2;
  int iVar3;
  undefined4 *puVar4;
  
  if (param_1 < 0x38) {
    iVar3 = 0;
    puVar4 = &DAT_803c4e84;
    do {
      if (*(char *)*puVar4 != '\0') {
        if (param_1 < 8) {
          uVar1 = (uint)(byte)PTR_DAT_80433934[0xd2] & 1 << iVar3;
        }
        else {
          uVar1 = (uint)(byte)PTR_DAT_80433934[0xd1] & 1 << iVar3;
        }
        if (uVar1 == 0) {
          for (pcVar2 = (char *)(&DAT_803c7070)[param_1 + iVar3]; pcVar2 != (char *)0x0;
              pcVar2 = *(char **)(pcVar2 + 8)) {
            if (*pcVar2 != '\0') {
              *(undefined4 *)(pcVar2 + 0x2c) = *(undefined4 *)(pcVar2 + 0x20);
              *(undefined4 *)(pcVar2 + 0x30) = *(undefined4 *)(pcVar2 + 0x24);
              *(undefined4 *)(pcVar2 + 0x34) = *(undefined4 *)(pcVar2 + 0x28);
              *(undefined4 *)(pcVar2 + 0x76) = *(undefined4 *)(pcVar2 + 0x70);
              *(undefined2 *)(pcVar2 + 0x7a) = *(undefined2 *)(pcVar2 + 0x74);
              (**(code **)(pcVar2 + 0xc))(pcVar2);
              if (pcVar2[0x86] != '\0') {
                pcVar2[0x1ca] = '\0';
              }
            }
          }
        }
      }
      iVar3 = iVar3 + 1;
      puVar4 = puVar4 + 1;
    } while (iVar3 < 6);
  }
  return;
}



// ==== 80089a94  zz_0089a94_ ====

void zz_0089a94_(uint param_1)

{
  if (((int)param_1 < 0x38) && ((param_1 & 7) == 0)) {
    zz_008997c_(param_1);
    zz_0089898_(param_1);
    zz_0089898_(param_1 + 7);
  }
  else {
    zz_0089898_(param_1);
  }
  return;
}



// ==== 80089aec  zz_0089aec_ ====

void zz_0089aec_(void)

{
  int iVar1;
  char *pcVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  for (pcVar2 = DAT_803c712c; pcVar2 != (char *)0x0; pcVar2 = *(char **)(pcVar2 + 8)) {
    if (*pcVar2 != '\0') {
      (**(code **)(pcVar2 + 0xc))(pcVar2);
    }
  }
  puVar4 = &DAT_803c4e84;
  iVar1 = 0;
  puVar3 = &DAT_803c706c;
  do {
    if (*(char *)*puVar4 != '\0') {
      for (pcVar2 = (char *)puVar3[0x31]; pcVar2 != (char *)0x0; pcVar2 = *(char **)(pcVar2 + 8)) {
        if (*pcVar2 != '\0') {
          (**(code **)(pcVar2 + 0xc))(pcVar2);
        }
      }
    }
    iVar1 = iVar1 + 1;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
    pcVar2 = DAT_803c7148;
  } while (iVar1 < 6);
  for (; pcVar2 != (char *)0x0; pcVar2 = *(char **)(pcVar2 + 8)) {
    if (*pcVar2 != '\0') {
      (**(code **)(pcVar2 + 0xc))(pcVar2);
    }
  }
  return;
}



// ==== 80089c00  zz_0089c00_ ====

void zz_0089c00_(int param_1)

{
  char *pcVar1;
  
  for (pcVar1 = (char *)(&DAT_803c706c)[param_1]; pcVar1 != (char *)0x0;
      pcVar1 = *(char **)(pcVar1 + 8)) {
    zz_0089d28_(pcVar1);
  }
  return;
}



// ==== 80089c4c  zz_0089c4c_ ====

void zz_0089c4c_(int param_1)

{
  char *pcVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = &DAT_803c4e84;
  iVar2 = 0;
  do {
    if (*(char *)*puVar3 != '\0') {
      for (pcVar1 = (char *)(&DAT_803c7070)[param_1 + iVar2]; pcVar1 != (char *)0x0;
          pcVar1 = *(char **)(pcVar1 + 8)) {
        zz_0089d28_(pcVar1);
      }
    }
    iVar2 = iVar2 + 1;
    puVar3 = puVar3 + 1;
  } while (iVar2 < 6);
  return;
}



// ==== 80089cd0  zz_0089cd0_ ====

void zz_0089cd0_(uint param_1)

{
  if (((int)param_1 < 0x38) && ((param_1 & 7) == 0)) {
    zz_0089c4c_(param_1);
    zz_0089c00_(param_1);
    zz_0089c00_(param_1 + 7);
  }
  else {
    zz_0089c00_(param_1);
  }
  return;
}



// ==== 80089d28  zz_0089d28_ ====

void zz_0089d28_(char *param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  if (*param_1 == '\0') {
    return;
  }
  if (param_1[0x82] == '\0') {
    return;
  }
  uVar2 = (uint)param_1[0x82];
  if ((int)uVar2 < 0x10) {
    iVar1 = uVar2 - 1;
    iVar3 = (&DAT_803c6efc)[iVar1];
    param_1[0x110] = '\0';
    param_1[0x111] = '\0';
    param_1[0x112] = '\0';
    param_1[0x113] = '\0';
    (&DAT_803c6efc)[iVar1] = param_1;
    if (iVar3 == 0) {
      (&DAT_803c6f1c)[iVar1] = param_1;
      return;
    }
    *(char **)(iVar3 + 0x110) = param_1;
    return;
  }
  if ((int)uVar2 < 0x20) {
    iVar1 = (uVar2 & 0xf) - 1;
    iVar3 = (&DAT_803c6ed4)[iVar1];
    param_1[0x110] = '\0';
    param_1[0x111] = '\0';
    param_1[0x112] = '\0';
    param_1[0x113] = '\0';
    (&DAT_803c6ed4)[iVar1] = param_1;
    if (iVar3 == 0) {
      (&DAT_803c6ee8)[iVar1] = param_1;
      return;
    }
    *(char **)(iVar3 + 0x110) = param_1;
    return;
  }
  if ((int)uVar2 < 0x30) {
    iVar1 = (uVar2 & 0xf) - 1;
    iVar3 = (&DAT_803c6eac)[iVar1];
    param_1[0x110] = '\0';
    param_1[0x111] = '\0';
    param_1[0x112] = '\0';
    param_1[0x113] = '\0';
    (&DAT_803c6eac)[iVar1] = param_1;
    if (iVar3 == 0) {
      (&DAT_803c6ec0)[iVar1] = param_1;
      return;
    }
    *(char **)(iVar3 + 0x110) = param_1;
    return;
  }
  if (0x3f < (int)uVar2) {
    iVar1 = (uVar2 & 0xf) - 1;
    iVar3 = (&DAT_803c6e4c)[iVar1];
    param_1[0x110] = '\0';
    param_1[0x111] = '\0';
    param_1[0x112] = '\0';
    param_1[0x113] = '\0';
    (&DAT_803c6e4c)[iVar1] = param_1;
    if (iVar3 == 0) {
      (&DAT_803c6e64)[iVar1] = param_1;
      return;
    }
    *(char **)(iVar3 + 0x110) = param_1;
    return;
  }
  iVar1 = (uVar2 & 0xf) - 1;
  iVar3 = (&DAT_803c6e7c)[iVar1];
  param_1[0x110] = '\0';
  param_1[0x111] = '\0';
  param_1[0x112] = '\0';
  param_1[0x113] = '\0';
  (&DAT_803c6e7c)[iVar1] = param_1;
  if (iVar3 == 0) {
    (&DAT_803c6e94)[iVar1] = param_1;
    return;
  }
  *(char **)(iVar3 + 0x110) = param_1;
  return;
}



// ==== 80089eb4  FUN_80089eb4 ====

void FUN_80089eb4(void)

{
  char *pcVar1;
  
  pcVar1 = (char *)(&DAT_803c6f1c)[(char)PTR_DAT_80433930[0x34]];
  while( true ) {
    if (pcVar1 == (char *)0x0) break;
    if ((*pcVar1 != '\0') && (*(code **)(pcVar1 + 0x10c) != (code *)0x0)) {
      (**(code **)(pcVar1 + 0x10c))(pcVar1);
    }
    pcVar1 = *(char **)(pcVar1 + 0x110);
  }
  return;
}



// ==== 80089f28  FUN_80089f28 ====

void FUN_80089f28(void)

{
  char *pcVar1;
  
  pcVar1 = (char *)(&DAT_803c6ee8)[(char)PTR_DAT_80433930[0x34]];
  while( true ) {
    if (pcVar1 == (char *)0x0) break;
    if ((*pcVar1 != '\0') && (*(code **)(pcVar1 + 0x10c) != (code *)0x0)) {
      (**(code **)(pcVar1 + 0x10c))(pcVar1);
    }
    pcVar1 = *(char **)(pcVar1 + 0x110);
  }
  return;
}



// ==== 80089f9c  FUN_80089f9c ====

void FUN_80089f9c(void)

{
  char *pcVar1;
  
  pcVar1 = (char *)(&DAT_803c6ec0)[(char)PTR_DAT_80433930[0x34]];
  while( true ) {
    if (pcVar1 == (char *)0x0) break;
    if ((*pcVar1 != '\0') && (*(code **)(pcVar1 + 0x10c) != (code *)0x0)) {
      (**(code **)(pcVar1 + 0x10c))(pcVar1);
    }
    pcVar1 = *(char **)(pcVar1 + 0x110);
  }
  return;
}



// ==== 8008a010  FUN_8008a010 ====

void FUN_8008a010(void)

{
  int iVar1;
  char *pcVar2;
  undefined4 *puVar3;
  
  if (PTR_DAT_80433930[0x34] == '\0') {
    iVar1 = 0;
    puVar3 = &DAT_803c6e94;
    do {
      pcVar2 = (char *)*puVar3;
      while( true ) {
        if (pcVar2 == (char *)0x0) break;
        if ((*pcVar2 != '\0') && (*(code **)(pcVar2 + 0x10c) != (code *)0x0)) {
          (**(code **)(pcVar2 + 0x10c))(pcVar2);
        }
        pcVar2 = *(char **)(pcVar2 + 0x110);
      }
      iVar1 = iVar1 + 1;
      puVar3 = puVar3 + 1;
    } while (iVar1 < 6);
  }
  return;
}



// ==== 8008a0a8  FUN_8008a0a8 ====

void FUN_8008a0a8(void)

{
  int iVar1;
  char *pcVar2;
  undefined4 *puVar3;
  int *piVar4;
  
  if (PTR_DAT_80433930[0x34] == '\0') {
    piVar4 = &DAT_803c4e84;
    iVar1 = 0;
    puVar3 = &DAT_803c6e64;
    do {
      if ((*piVar4 != 0) && (*(char *)(*piVar4 + 0x82) != '\0')) {
        pcVar2 = (char *)*puVar3;
        while( true ) {
          if (pcVar2 == (char *)0x0) break;
          if ((*pcVar2 != '\0') && (*(code **)(pcVar2 + 0x10c) != (code *)0x0)) {
            (**(code **)(pcVar2 + 0x10c))(pcVar2);
          }
          pcVar2 = *(char **)(pcVar2 + 0x110);
        }
      }
      iVar1 = iVar1 + 1;
      puVar3 = puVar3 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar1 < 6);
  }
  return;
}



// ==== 8008a16c  zz_008a16c_ ====

void zz_008a16c_(void)

{
  DAT_803c6efc = 0;
  DAT_803c6f1c = 0;
  DAT_803c6e4c = 0;
  DAT_803c6e64 = 0;
  DAT_803c6e7c = 0;
  DAT_803c6e94 = 0;
  DAT_803c6eac = 0;
  DAT_803c6ec0 = 0;
  DAT_803c6ed4 = 0;
  DAT_803c6ee8 = 0;
  DAT_803c6f00 = 0;
  DAT_803c6f20 = 0;
  DAT_803c6f04 = 0;
  DAT_803c6f24 = 0;
  DAT_803c6f08 = 0;
  DAT_803c6f28 = 0;
  DAT_803c6f0c = 0;
  DAT_803c6f2c = 0;
  DAT_803c6f10 = 0;
  DAT_803c6f30 = 0;
  DAT_803c6f14 = 0;
  DAT_803c6f34 = 0;
  DAT_803c6f18 = 0;
  DAT_803c6f38 = 0;
  DAT_803c6eb0 = 0;
  DAT_803c6ec4 = 0;
  DAT_803c6ed8 = 0;
  DAT_803c6eec = 0;
  DAT_803c6eb4 = 0;
  DAT_803c6ec8 = 0;
  DAT_803c6edc = 0;
  DAT_803c6ef0 = 0;
  DAT_803c6eb8 = 0;
  DAT_803c6ecc = 0;
  DAT_803c6ee0 = 0;
  DAT_803c6ef4 = 0;
  DAT_803c6ebc = 0;
  DAT_803c6ed0 = 0;
  DAT_803c6ee4 = 0;
  DAT_803c6ef8 = 0;
  DAT_803c6e50 = 0;
  DAT_803c6e68 = 0;
  DAT_803c6e80 = 0;
  DAT_803c6e98 = 0;
  DAT_803c6e54 = 0;
  DAT_803c6e6c = 0;
  DAT_803c6e84 = 0;
  DAT_803c6e9c = 0;
  DAT_803c6e58 = 0;
  DAT_803c6e70 = 0;
  DAT_803c6e88 = 0;
  DAT_803c6ea0 = 0;
  DAT_803c6e5c = 0;
  DAT_803c6e74 = 0;
  DAT_803c6e8c = 0;
  DAT_803c6ea4 = 0;
  DAT_803c6e60 = 0;
  DAT_803c6e78 = 0;
  DAT_803c6e90 = 0;
  DAT_803c6ea8 = 0;
  return;
}



// ==== 8008a28c  zz_008a28c_ ====

void zz_008a28c_(void)

{
  DAT_80436250 = 0;
  DAT_8043624e = 0;
  DAT_8043624c = 0;
  DAT_8043624a = 0;
  DAT_80436248 = 0;
  DAT_80436246 = 0;
  DAT_80436244 = 0;
  DAT_80436242 = 0;
  DAT_80436240 = 0;
  DAT_8043623e = 0;
  return;
}



// ==== 8008a2bc  zz_008a2bc_ ====

void zz_008a2bc_(int param_1)

{
  int iVar1;
  char *pcVar2;
  uint uVar3;
  
  pcVar2 = *(char **)(param_1 + 0x20);
  if (pcVar2 == (char *)0x0) {
    return;
  }
  if (*pcVar2 == '\0') {
    return;
  }
  iVar1 = *(int *)(param_1 + 0x28);
  if (pcVar2[0x83] == '\0') {
    if ((*(uint *)(pcVar2 + 0x76c) & 1 << (uint)*(byte *)(iVar1 + 1)) == 0) {
      return;
    }
    if (*(float *)(pcVar2 + 0x720) <= FLOAT_80437c40) {
      if (((*(ushort *)(iVar1 + 2) & 0x40) != 0) && ((*(ushort *)(pcVar2 + 0x272) & 0x40) == 0)) {
        uVar3 = (uint)DAT_80436248;
        DAT_80436248 = DAT_80436248 + 1;
        (&DAT_803c2f7c)[uVar3] = param_1;
      }
      if (((*(ushort *)(iVar1 + 2) & 2) != 0) && ((*(ushort *)(pcVar2 + 0x272) & 2) == 0)) {
        uVar3 = (uint)DAT_8043624e;
        DAT_8043624e = DAT_8043624e + 1;
        (&DAT_803c417c)[uVar3] = param_1;
      }
    }
    if (((*(ushort *)(iVar1 + 2) & 2) != 0) && ((*(ushort *)(pcVar2 + 0x272) & 2) == 0)) {
      uVar3 = (uint)DAT_8043623e;
      DAT_8043623e = DAT_8043623e + 1;
      (&DAT_803c117c)[uVar3] = param_1;
    }
    goto LAB_8008a43c;
  }
  if (*(char *)(*(int *)(param_1 + 0x24) + 0x83) == '\0') {
    if (*(float *)(*(int *)(param_1 + 0x24) + 0x720) <= FLOAT_80437c40) goto LAB_8008a3d4;
  }
  else {
LAB_8008a3d4:
    if (((*(ushort *)(iVar1 + 2) & 0x40) != 0) && ((*(ushort *)(pcVar2 + 0x272) & 0x40) == 0)) {
      uVar3 = (uint)DAT_80436248;
      DAT_80436248 = DAT_80436248 + 1;
      (&DAT_803c2f7c)[uVar3] = param_1;
    }
  }
  if (((*(ushort *)(iVar1 + 2) & 2) != 0) && ((*(ushort *)(pcVar2 + 0x272) & 2) == 0)) {
    uVar3 = (uint)DAT_8043624e;
    DAT_8043624e = DAT_8043624e + 1;
    (&DAT_803c417c)[uVar3] = param_1;
  }
LAB_8008a43c:
  if ((*(ushort *)(iVar1 + 2) & 1) != 0) {
    if ((*(ushort *)(pcVar2 + 0x272) & 1) == 0) {
      if (pcVar2[0x276] == '\0') {
        uVar3 = (uint)DAT_80436250;
        DAT_80436250 = DAT_80436250 + 1;
        (&DAT_803c477c)[uVar3] = param_1;
      }
    }
  }
  if (((*(ushort *)(iVar1 + 2) & 4) != 0) && ((*(ushort *)(pcVar2 + 0x272) & 4) == 0)) {
    uVar3 = (uint)DAT_8043624c;
    DAT_8043624c = DAT_8043624c + 1;
    (&DAT_803c3b7c)[uVar3] = param_1;
  }
  if (((*(ushort *)(iVar1 + 2) & 8) != 0) && ((*(ushort *)(pcVar2 + 0x272) & 8) == 0)) {
    uVar3 = (uint)DAT_8043624a;
    DAT_8043624a = DAT_8043624a + 1;
    (&DAT_803c357c)[uVar3] = param_1;
  }
  if (((*(ushort *)(iVar1 + 2) & 0x10) != 0) && ((*(ushort *)(pcVar2 + 0x272) & 0x10) == 0)) {
    uVar3 = (uint)DAT_80436246;
    DAT_80436246 = DAT_80436246 + 1;
    (&DAT_803c297c)[uVar3] = param_1;
  }
  if ((*(ushort *)(iVar1 + 2) & 0x20) != 0) {
    if ((*(ushort *)(pcVar2 + 0x272) & 0x20) == 0) {
      if (pcVar2[0x1eb] == '\0') {
        uVar3 = (uint)DAT_80436244;
        DAT_80436244 = DAT_80436244 + 1;
        (&DAT_803c237c)[uVar3] = param_1;
      }
    }
  }
  if (((*(ushort *)(iVar1 + 2) & 0x400) != 0) && ((*(ushort *)(pcVar2 + 0x272) & 0x400) == 0)) {
    uVar3 = (uint)DAT_80436242;
    DAT_80436242 = DAT_80436242 + 1;
    (&DAT_803c1d7c)[uVar3] = param_1;
  }
  if ((*(ushort *)(iVar1 + 2) & 0x80) == 0) {
    return;
  }
  if ((*(ushort *)(pcVar2 + 0x272) & 0x80) != 0) {
    return;
  }
  if (pcVar2[0x276] != '\0') {
    return;
  }
  uVar3 = (uint)DAT_80436240;
  DAT_80436240 = DAT_80436240 + 1;
  (&DAT_803c177c)[uVar3] = param_1;
  return;
}



// ==== 8008a5d0  zz_008a5d0_ ====

void zz_008a5d0_(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  DAT_8043623c = DAT_8043623c + 1;
  if (DAT_8043623c == 0) {
    DAT_8043623c = 1;
  }
  *(short *)(param_1 + 0x26c) = DAT_8043623c;
  if (param_3 == 0) {
    return;
  }
  *(undefined1 *)(param_1 + 0x2ad) = 0;
  if (*(char *)(param_2 + 0x83) != '\0') {
    return;
  }
  *(int *)(param_2 + 0x404) = *(int *)(param_2 + 0x404) + 1;
  iVar1 = *(int *)(param_1 + 0xcc);
  if (iVar1 == 0) {
    return;
  }
  if (*(char *)(iVar1 + 0x83) != '\0') {
    return;
  }
  if (*(char *)(param_2 + 0x88) == *(char *)(iVar1 + 0x88)) {
    return;
  }
  *(int *)(iVar1 + 0x40c) = *(int *)(iVar1 + 0x40c) + 1;
  return;
}



// ==== 8008a65c  FUN_8008a65c ====

/* WARNING: Removing unreachable block (ram,0x8008a70c) */

void FUN_8008a65c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  short sVar1;
  int iVar2;
  bool bVar3;
  char cVar4;
  byte bVar5;
  int iVar6;
  char *pcVar7;
  byte *pbVar8;
  undefined8 uVar9;
  
  pcVar7 = *(char **)(param_9 + 0x20);
  if ((pcVar7[0x1d8] == '\0') && (*pcVar7 != '\0')) {
    if (((pcVar7[0x83] == '\0') && (*(short *)(param_9 + 0x4a) != -1)) &&
       ((int)*(short *)(param_9 + 0x4c) != (int)pcVar7[0x1ced] + pcVar7[0x1cec] * 0x1000)) {
      zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    }
    else {
      param_9[0x13] = 0;
      bVar5 = param_9[0x10];
      pbVar8 = *(byte **)(param_9 + 0x28);
      if (bVar5 == 1) {
        *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(param_9 + 0x30);
        *(undefined4 *)(param_9 + 0x40) = *(undefined4 *)(param_9 + 0x34);
        *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(param_9 + 0x38);
        uVar9 = gnt4_PSMTXMultVec_bl
                          (*(float **)(param_9 + 0x60),(float *)(pbVar8 + 0xc),
                           (float *)(param_9 + 0x30));
        sVar1 = *(short *)(param_9 + 0x4a);
        if (-1 < sVar1) {
          if (pcVar7[0x83] == '\0') {
            if (sVar1 < (short)(int)*(float *)(pcVar7 + 0x1cdc)) {
              zz_0088e50_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
              return;
            }
          }
          else {
            *(short *)(param_9 + 0x4a) = sVar1 + -1;
            if (*(short *)(param_9 + 0x4a) < 1) {
              zz_0088e50_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
              return;
            }
          }
        }
        (*(code *)(&PTR_FUN_802da740)[*pbVar8])(param_9);
        if ((((*(ushort *)(pbVar8 + 2) & 1) != 0) || ((*(ushort *)(pbVar8 + 2) & 0x80) != 0)) &&
           ((iVar2 = *(int *)(param_9 + 0x2c) + (uint)(byte)param_9[0x11] * 0x18,
            '\0' < *(char *)(iVar2 + 0x16) &&
            ((((iVar6 = *(int *)(param_9 + 0x24), *(char *)(iVar6 + 0x83) != '\0' ||
               (cVar4 = zz_008b480_(), cVar4 == '\0')) ||
              (bVar5 = zz_008b480_(), (*(byte *)(iVar6 + 0x3e5) & bVar5) != 0)) &&
             ((cVar4 = zz_008b290_(), cVar4 == '\0' &&
              (param_9[0x4e] = param_9[0x4e] + -1, (char)param_9[0x4e] < '\x01')))))))) {
          param_9[0x4e] = *(undefined1 *)(iVar2 + 0x16);
          zz_008a5d0_((int)pcVar7,*(int *)(param_9 + 0x24),0);
          if ((*(ushort *)(iVar2 + 0x10) & 0x20) != 0) {
            pcVar7[0x2ad] = '\0';
          }
        }
        if (pcVar7[0x281] != '\0') {
          param_9[0x10] = 2;
        }
        bVar3 = zz_008aa40_((int)param_9);
        if (!bVar3) {
          zz_008a2bc_((int)param_9);
        }
      }
      else if (bVar5 == 0) {
        gnt4_PSMTXMultVec_bl
                  (*(float **)(param_9 + 0x60),(float *)(pbVar8 + 0xc),(float *)(param_9 + 0x30));
        *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(param_9 + 0x30);
        *(undefined4 *)(param_9 + 0x40) = *(undefined4 *)(param_9 + 0x34);
        *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(param_9 + 0x38);
        sVar1 = *(short *)(param_9 + 0x48);
        if (0 < sVar1) {
          if (pcVar7[0x83] != '\0') {
            *(short *)(param_9 + 0x48) = sVar1 + -1;
            return;
          }
          if ((short)(int)*(float *)(pcVar7 + 0x1cdc) < sVar1) {
            return;
          }
        }
        param_9[0x10] = param_9[0x10] + '\x01';
        param_9[0x4e] = 0;
        (*(code *)(&PTR_FUN_802da758)[*pbVar8])(param_9);
        if ((((*(ushort *)(pbVar8 + 2) & 1) != 0) || ((*(ushort *)(pbVar8 + 2) & 0x80) != 0)) &&
           (param_9[0x11] = (char)*(undefined2 *)(pbVar8 + 4), pcVar7[0x1ca] == '\0')) {
          pcVar7[0x1ca] = '\x01';
          iVar2 = *(int *)(param_9 + 0x2c) + (uint)(byte)param_9[0x11] * 0x18;
          param_9[0x4e] = *(undefined1 *)(iVar2 + 0x16);
          if ((*(ushort *)(iVar2 + 0x10) & 0x20) == 0) {
            zz_008a5d0_((int)pcVar7,*(int *)(param_9 + 0x24),1);
          }
          else {
            zz_008a5d0_((int)pcVar7,*(int *)(param_9 + 0x24),0);
          }
        }
        if (pcVar7[0x281] != '\0') {
          param_9[0x10] = 2;
        }
        bVar3 = zz_008aa40_((int)param_9);
        if (!bVar3) {
          zz_008a2bc_((int)param_9);
        }
      }
      else if (bVar5 < 3) {
        if (pcVar7[0x281] == '\0') {
          param_9[0x10] = 1;
        }
        bVar3 = zz_008aa40_((int)param_9);
        if (!bVar3) {
          zz_008a2bc_((int)param_9);
        }
      }
    }
  }
  else {
    zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  return;
}



// ==== 8008aa40  zz_008aa40_ ====

bool zz_008aa40_(int param_1)

{
  bool bVar1;
  float *pfVar2;
  int iVar3;
  double dVar4;
  float local_18;
  float local_14;
  float local_10;
  
  pfVar2 = *(float **)(param_1 + 0x60);
  local_18 = *pfVar2;
  local_14 = pfVar2[4];
  local_10 = pfVar2[8];
  dVar4 = gnt4_PSVECMag_bl(&local_18);
  if (FLOAT_80437c44 < (float)dVar4) {
    iVar3 = *(int *)(param_1 + 0x60);
    local_18 = *(float *)(iVar3 + 4);
    local_14 = *(float *)(iVar3 + 0x14);
    local_10 = *(float *)(iVar3 + 0x24);
    dVar4 = gnt4_PSVECMag_bl(&local_18);
    if (FLOAT_80437c44 < (float)dVar4) {
      iVar3 = *(int *)(param_1 + 0x60);
      local_18 = *(float *)(iVar3 + 8);
      local_14 = *(float *)(iVar3 + 0x18);
      local_10 = *(float *)(iVar3 + 0x28);
      dVar4 = gnt4_PSVECMag_bl(&local_18);
      bVar1 = (float)dVar4 <= FLOAT_80437c44;
    }
    else {
      bVar1 = true;
    }
  }
  else {
    bVar1 = true;
  }
  return bVar1;
}



// ==== 8008ab30  zz_008ab30_ ====

void zz_008ab30_(int param_1)

{
  char cVar1;
  undefined1 *puVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  
  *(undefined1 *)(param_1 + 0x86) = 1;
  *(undefined1 *)(param_1 + 0x1d8) = 0;
  pcVar5 = *(char **)(param_1 + 0x3fc);
  pcVar6 = pcVar5;
  for (iVar4 = 0; (-1 < *pcVar6 && (iVar4 < 0x20)); iVar4 = iVar4 + 1) {
    puVar2 = zz_0088aa0_(param_1,4,0x30,0,0);
    if (puVar2 != (undefined1 *)0x0) {
      *puVar2 = 1;
      *(code **)(puVar2 + 0xc) = FUN_8008a65c;
      *(int *)(puVar2 + 0x20) = param_1;
      *(int *)(puVar2 + 0x24) = param_1;
      pcVar3 = pcVar5 + *pcVar6 * 0x50 + 0x20;
      *(char **)(puVar2 + 0x28) = pcVar3;
      if ((pcVar3[1] & 0x80U) == 0) {
        *(uint *)(puVar2 + 0x60) = param_1 + (uint)(byte)pcVar3[1] * 0x30 + 0x8d4;
      }
      else {
        *(int *)(puVar2 + 0x60) = param_1 + 0x1aa4;
      }
      *(undefined1 **)(puVar2 + 0x5c) = puVar2;
      *(undefined4 *)(puVar2 + 0x2c) = *(undefined4 *)(param_1 + 0x27c);
      puVar2[0x11] = (char)*(undefined2 *)(pcVar3 + 4);
      *(undefined2 *)(puVar2 + 0x48) = *(undefined2 *)(pcVar3 + 6);
      *(undefined2 *)(puVar2 + 0x4a) = *(undefined2 *)(pcVar3 + 8);
      puVar2[0x12] = *pcVar6;
      if ((*(ushort *)(pcVar3 + 2) & 0x200) != 0) {
        cVar1 = *(char *)(param_1 + 0x501);
        if (cVar1 < 4) {
          *(char *)(param_1 + 0x501) = cVar1 + '\x01';
          *(undefined1 **)(param_1 + cVar1 * 4 + 0x530) = puVar2;
        }
      }
    }
    pcVar6 = pcVar6 + 1;
  }
  return;
}



// ==== 8008ac80  zz_008ac80_ ====

undefined4 zz_008ac80_(int param_1,int param_2)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  
  uVar4 = 0;
  iVar7 = *(int *)(param_1 + 0x90);
  if (iVar7 == 0) {
    uVar4 = 0;
  }
  else {
    *(undefined4 *)(param_1 + 0x27c) = *(undefined4 *)(iVar7 + 0x27c);
    iVar5 = *(int *)(iVar7 + 0x3fc);
    pcVar6 = (char *)(iVar5 + 0xa20 + param_2 * 4);
    for (iVar3 = 0; (-1 < *pcVar6 && (iVar3 < 4)); iVar3 = iVar3 + 1) {
      puVar1 = zz_0088aa0_(iVar7,4,0x30,0,0);
      if (puVar1 != (undefined1 *)0x0) {
        *puVar1 = 1;
        *(code **)(puVar1 + 0xc) = FUN_8008a65c;
        *(int *)(puVar1 + 0x20) = param_1;
        puVar1[0x14] = (char)param_2;
        if (*(int *)(param_1 + 0x90) == 0) {
          *(undefined4 *)(puVar1 + 0x24) = *(undefined4 *)(param_1 + 0x8c);
        }
        else {
          *(int *)(puVar1 + 0x24) = *(int *)(param_1 + 0x90);
        }
        iVar2 = iVar5 + 0xaa0 + *pcVar6 * 0x50;
        *(int *)(puVar1 + 0x28) = iVar2;
        if (*(char *)(param_1 + 0x83) == '\0') {
          if ((*(byte *)(iVar2 + 1) & 0x80) == 0) {
            *(uint *)(puVar1 + 0x60) = param_1 + (uint)*(byte *)(iVar2 + 1) * 0x30 + 0x8d4;
          }
          else {
            *(int *)(puVar1 + 0x60) = param_1 + 0x1aa4;
          }
          *(short *)(puVar1 + 0x4c) =
               (short)*(char *)(param_1 + 0x1ced) + *(char *)(param_1 + 0x1cec) * 0x1000;
        }
        else {
          *(int *)(puVar1 + 0x60) = param_1 + 0x114;
        }
        *(undefined1 **)(puVar1 + 0x5c) = puVar1;
        uVar4 = 1;
        *(undefined4 *)(puVar1 + 0x2c) = *(undefined4 *)(param_1 + 0x27c);
        puVar1[0x11] = (char)*(undefined2 *)(iVar2 + 4);
        *(undefined2 *)(puVar1 + 0x48) = *(undefined2 *)(iVar2 + 6);
        *(undefined2 *)(puVar1 + 0x4a) = *(undefined2 *)(iVar2 + 8);
        *(undefined1 *)(param_1 + 0x86) = 1;
        *(undefined1 *)(param_1 + 0x1d8) = 0;
        puVar1[0x12] = *pcVar6;
      }
      pcVar6 = pcVar6 + 1;
    }
  }
  return uVar4;
}



// ==== 8008ae10  zz_008ae10_ ====

void zz_008ae10_(int param_1,byte param_2)

{
  zz_008ae60_(param_1,param_1,param_2,0);
  return;
}



// ==== 8008ae3c  zz_008ae3c_ ====

void zz_008ae3c_(int param_1,int param_2,byte param_3)

{
  zz_008ae60_(param_1,param_2,param_3,1);
  return;
}



// ==== 8008ae60  zz_008ae60_ ====

undefined4 zz_008ae60_(int param_1,int param_2,byte param_3,int param_4)

{
  char cVar1;
  int iVar2;
  undefined1 *puVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  byte *pbVar7;
  
  uVar6 = 0;
  *(undefined **)(param_2 + 0x27c) = &DAT_802c4760;
  iVar2 = *(int *)(PTR_DAT_80433934 + 0x98);
  pbVar7 = (byte *)(iVar2 + (uint)param_3 * 4);
  for (iVar5 = 0; (*pbVar7 != 0xff && (iVar5 < 4)); iVar5 = iVar5 + 1) {
    if (param_4 == 0) {
      puVar3 = zz_008893c_(4,0x30,0,0);
    }
    else {
      puVar3 = zz_0088aa0_(param_1,4,0x30,0,0);
    }
    if (puVar3 != (undefined1 *)0x0) {
      *puVar3 = 1;
      *(code **)(puVar3 + 0xc) = FUN_8008a65c;
      *(int *)(puVar3 + 0x20) = param_2;
      puVar3[0x14] = param_3;
      if (*(int *)(param_2 + 0x90) == 0) {
        *(undefined4 *)(puVar3 + 0x24) = *(undefined4 *)(param_2 + 0x8c);
      }
      else {
        *(int *)(puVar3 + 0x24) = *(int *)(param_2 + 0x90);
      }
      uVar6 = 1;
      iVar4 = iVar2 + 0x400 + (uint)*pbVar7 * 0x50;
      *(int *)(puVar3 + 0x28) = iVar4;
      *(int *)(puVar3 + 0x60) = param_2 + 0x114;
      *(undefined1 **)(puVar3 + 0x5c) = puVar3;
      *(undefined4 *)(puVar3 + 0x2c) = *(undefined4 *)(param_2 + 0x27c);
      puVar3[0x11] = (char)*(undefined2 *)(iVar4 + 4);
      *(undefined2 *)(puVar3 + 0x48) = *(undefined2 *)(iVar4 + 6);
      *(undefined2 *)(puVar3 + 0x4a) = *(undefined2 *)(iVar4 + 8);
      *(undefined1 *)(param_2 + 0x86) = 1;
      *(undefined1 *)(param_2 + 0x1d8) = 0;
      puVar3[0x12] = *pbVar7;
      if ((*(char *)(param_2 + 0x83) == '\0') && ((*(ushort *)(iVar4 + 2) & 0x200) != 0)) {
        cVar1 = *(char *)(param_1 + 0x501);
        if (cVar1 < 4) {
          *(char *)(param_1 + 0x501) = cVar1 + '\x01';
          *(undefined1 **)(param_1 + cVar1 * 4 + 0x530) = puVar3;
        }
      }
    }
    pbVar7 = pbVar7 + 1;
  }
  return uVar6;
}



// ==== 8008aff0  zz_008aff0_ ====

void zz_008aff0_(int param_1)

{
  if ((*(char *)(param_1 + 2) != '\x03') && (*(char *)(param_1 + 2) != '\0')) {
    return;
  }
  *(undefined1 *)(param_1 + 0x1d8) = 1;
  return;
}



// ==== 8008b010  zz_008b010_ ====

void zz_008b010_(int param_1)

{
  PTR_DAT_80433934[0x66] = (char)param_1;
  if (1 < param_1) {
    return;
  }
  if (param_1 < 0) {
    return;
  }
  *(undefined2 *)(PTR_DAT_80433934 + 0xd6) = 0;
  return;
}



// ==== 8008b038  zz_008b038_ ====

void zz_008b038_(char param_1)

{
  PTR_DAT_80433934[0x15d4] = param_1 + '\x01';
  return;
}



// ==== 8008b048  zz_008b048_ ====

void zz_008b048_(void)

{
  if (PTR_DAT_80433934[0x15d4] != '\0') {
    zz_008b010_((char)PTR_DAT_80433934[0x15d4] + -1);
  }
  PTR_DAT_80433934[0x15d4] = 0;
  return;
}



// ==== 8008b08c  zz_008b08c_ ====

void zz_008b08c_(int param_1)

{
  byte *pbVar1;
  
  if (param_1 == 2) {
    PTR_DAT_80433934[0xd1] = 0xff;
    PTR_DAT_80433934[0xd2] = ~PTR_DAT_80433934[0xda];
    return;
  }
  if (1 < param_1) {
    if (param_1 == 4) {
      pbVar1 = PTR_DAT_80433934 + 0xeb;
      PTR_DAT_80433934[0xd2] = ~*pbVar1;
      PTR_DAT_80433934[0xd1] = ~*pbVar1;
      return;
    }
    if (3 < param_1) {
      return;
    }
    pbVar1 = PTR_DAT_80433934 + 0xda;
    PTR_DAT_80433934[0xd2] = ~*pbVar1;
    PTR_DAT_80433934[0xd1] = ~*pbVar1;
    return;
  }
  if (param_1 == 0) {
    PTR_DAT_80433934[0xd2] = 0;
    PTR_DAT_80433934[0xd1] = 0;
    return;
  }
  if (param_1 < 0) {
    return;
  }
  PTR_DAT_80433934[0xd2] = 0xff;
  PTR_DAT_80433934[0xd1] = 0xff;
  return;
}



// ==== 8008b140  zz_008b140_ ====

void zz_008b140_(int param_1,undefined1 param_2)

{
  PTR_DAT_80433934[0xd8] = (char)(1 << param_1);
  PTR_DAT_80433934[0xd9] = param_2;
  *(undefined2 *)(PTR_DAT_80433934 + 0xd6) = 2;
  PTR_DAT_80433934[0xda] = PTR_DAT_80433934[param_1 * 0x3c + 0x101];
  zz_00f6e3c_((char)param_1,param_2);
  return;
}



// ==== 8008b198  zz_008b198_ ====

void zz_008b198_(void)

{
  *(undefined2 *)(PTR_DAT_80433934 + 0xd6) = 0;
  PTR_DAT_80433934[0xd9] = 0;
  PTR_DAT_80433934[0xd8] = 0;
  PTR_DAT_80433934[0xda] = 0;
  PTR_DAT_80433934[0xdb] = 0;
  zz_008b08c_(0);
  return;
}



// ==== 8008b1e8  zz_008b1e8_ ====

void zz_008b1e8_(void)

{
  PTR_DAT_80433934[0xdb] = 1;
  return;
}



// ==== 8008b1f8  zz_008b1f8_ ====

undefined4 zz_008b1f8_(void)

{
  byte bVar1;
  short sVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  if (*(short *)(PTR_DAT_80433934 + 0xd6) != 0) {
    sVar2 = *(short *)(PTR_DAT_80433934 + 0xd6) + -1;
    *(short *)(PTR_DAT_80433934 + 0xd6) = sVar2;
    if ((sVar2 < 1) || (PTR_DAT_80433934[0xdb] != '\0')) {
      zz_008b198_();
    }
    else {
      bVar1 = PTR_DAT_80433934[0xd9];
      if (bVar1 == 2) {
        zz_008b08c_(1);
      }
      else if ((bVar1 < 2) && (bVar1 != 0)) {
        zz_008b08c_(3);
      }
      uVar3 = 1;
    }
  }
  return uVar3;
}



// ==== 8008b290  zz_008b290_ ====

undefined1 zz_008b290_(void)

{
  return PTR_DAT_80433934[0xd9];
}



// ==== 8008b29c  zz_008b29c_ ====

void zz_008b29c_(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  for (iVar2 = 0; iVar2 < (char)PTR_DAT_80433934[0x53]; iVar2 = iVar2 + 1) {
    PTR_DAT_80433934[iVar1 + 0x100] = 0;
    iVar1 = iVar1 + 0x3c;
  }
  zz_008b198_();
  return;
}



// ==== 8008b2f0  zz_008b2f0_ ====

int zz_008b2f0_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined *puVar1;
  int iVar2;
  char cVar5;
  int iVar3;
  uint uVar4;
  undefined4 in_r10;
  undefined *puVar6;
  int iVar7;
  
  iVar7 = 0;
  cVar5 = zz_008b290_();
  if (cVar5 == '\0') {
    iVar3 = 0;
    iVar2 = (int)(char)PTR_DAT_80433934[0x53];
    puVar6 = PTR_DAT_80433934;
    if (0 < iVar2) {
      do {
        iVar7 = (int)(char)puVar6[0x100];
        if (iVar7 != 0) {
          param_1 = zz_008b140_(iVar3,puVar6[0x100]);
          puVar6[0x100] = 0;
          break;
        }
        puVar6 = puVar6 + 0x3c;
        iVar3 = iVar3 + 1;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    cVar5 = zz_008b480_();
    if (((cVar5 == '\0') && (iVar7 == 0)) && (PTR_DAT_80433934[0xea] != '\0')) {
      uVar4 = zz_00055fc_();
      uVar4 = uVar4 % 6;
      iVar2 = 6;
      do {
        if (((uint)(byte)PTR_DAT_80433934[0xea] & 1 << uVar4) != 0) {
          PTR_DAT_80433934[0xeb] = (char)(1 << uVar4);
          puVar6 = PTR_DAT_80433934;
          PTR_DAT_80433934[0xea] = PTR_DAT_80433934[0xea] & ~PTR_DAT_80433934[0xeb];
          *(undefined2 *)(PTR_DAT_80433934 + 0xe8) =
               *(undefined2 *)(PTR_DAT_80433934 + uVar4 * 2 + 0xdc);
          PTR_DAT_80433934[0xee] = (char)uVar4;
          puVar1 = PTR_DAT_80433934;
          iVar7 = (&DAT_803c4e84)[uVar4];
          *(undefined2 *)(PTR_DAT_80433934 + 0xec) = *(undefined2 *)(iVar7 + 1000);
          zz_00e9b08_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,1,1,puVar1,
                      iVar7,puVar6,uVar4,in_r10);
          zz_00f036c_((&DAT_803c4e84)[uVar4],0x102);
          zz_0092dcc_((&DAT_803c4e84)[uVar4],3);
          return uVar4 + 0x80;
        }
        uVar4 = (int)(uVar4 + 1) % 6;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
  }
  return iVar7;
}



// ==== 8008b480  zz_008b480_ ====

undefined1 zz_008b480_(void)

{
  return PTR_DAT_80433934[0xeb];
}



// ==== 8008b48c  zz_008b48c_ ====

undefined4
zz_008b48c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  short sVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  if (*(short *)(PTR_DAT_80433934 + 0xe8) != 0) {
    sVar1 = *(short *)(PTR_DAT_80433934 + 0xe8) + -1;
    *(short *)(PTR_DAT_80433934 + 0xe8) = sVar1;
    if ((sVar1 < 1) ||
       (*(short *)(PTR_DAT_80433934 + 0xec) !=
        *(short *)((&DAT_803c4e84)[(byte)PTR_DAT_80433934[0xee]] + 1000))) {
      zz_008b514_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    }
    else {
      zz_008b08c_(4);
      uVar2 = 1;
    }
  }
  return uVar2;
}



// ==== 8008b514  zz_008b514_ ====

void zz_008b514_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined4 *puVar1;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar2;
  
  if ((PTR_DAT_80433934[0xeb] & 1) != 0) {
    *(undefined1 *)(DAT_803c4e84 + 0x656) = 2;
  }
  if ((PTR_DAT_80433934[0xeb] & 2) != 0) {
    *(undefined1 *)(DAT_803c4e88 + 0x656) = 2;
  }
  if ((PTR_DAT_80433934[0xeb] & 4) != 0) {
    *(undefined1 *)(DAT_803c4e8c + 0x656) = 2;
  }
  if ((PTR_DAT_80433934[0xeb] & 8) != 0) {
    *(undefined1 *)(DAT_803c4e90 + 0x656) = 2;
  }
  if ((PTR_DAT_80433934[0xeb] & 0x10) != 0) {
    *(undefined1 *)(DAT_803c4e94 + 0x656) = 2;
  }
  puVar1 = &DAT_803c4e98;
  if ((PTR_DAT_80433934[0xeb] & 0x20) != 0) {
    *(undefined1 *)(DAT_803c4e98 + 0x656) = 2;
  }
  PTR_DAT_80433934[0xeb] = 0;
  *(undefined2 *)(PTR_DAT_80433934 + 0xe8) = 0;
  uVar2 = zz_008b08c_(0);
  zz_00e9b08_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,1,0,puVar1,in_r7,in_r8
              ,in_r9,in_r10);
  return;
}



// ==== 8008b640  zz_008b640_ ====

void zz_008b640_(void)

{
  *(undefined2 *)(PTR_DAT_80433934 + 0xe8) = 1;
  return;
}



// ==== 8008b650  zz_008b650_ ====

void zz_008b650_(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  uint *puVar5;
  uint uVar6;
  uint uVar7;
  uint *puVar8;
  int iVar9;
  
  puVar8 = &DAT_803c727c;
  puVar5 = &DAT_803c71fc;
  iVar9 = 0;
  do {
    zz_008b7c8_((int *)puVar8);
    iVar9 = iVar9 + 1;
    uVar7 = *puVar8;
    *(undefined1 *)((int)puVar5 + 0x15) = *(undefined1 *)((int)puVar8 + 0x15);
    uVar6 = puVar8[4];
    uVar1 = *(undefined1 *)((int)puVar8 + 0x16);
    puVar5[1] = *puVar5;
    uVar2 = *(undefined1 *)((int)puVar8 + 0x17);
    *puVar5 = uVar7;
    uVar3 = *(undefined1 *)(puVar8 + 6);
    puVar5[4] = uVar6;
    uVar4 = *(undefined1 *)((int)puVar8 + 0x19);
    *(undefined1 *)((int)puVar5 + 0x16) = uVar1;
    uVar1 = *(undefined1 *)((int)puVar8 + 0x1a);
    *(undefined1 *)((int)puVar5 + 0x17) = uVar2;
    uVar2 = *(undefined1 *)((int)puVar8 + 0x1b);
    *(undefined1 *)(puVar5 + 6) = uVar3;
    uVar3 = *(undefined1 *)(puVar8 + 7);
    *(undefined1 *)((int)puVar5 + 0x19) = uVar4;
    uVar4 = *(undefined1 *)((int)puVar8 + 0x1d);
    puVar8 = puVar8 + 8;
    *(undefined1 *)((int)puVar5 + 0x1a) = uVar1;
    *(undefined1 *)((int)puVar5 + 0x1b) = uVar2;
    *(undefined1 *)(puVar5 + 7) = uVar3;
    *(undefined1 *)((int)puVar5 + 0x1d) = uVar4;
    puVar5[2] = *puVar5 & ~puVar5[1];
    puVar5[3] = puVar5[1] & ~*puVar5;
    puVar5 = puVar5 + 8;
  } while (iVar9 < 4);
  return;
}



// ==== 8008b73c  FUN_8008b73c ====

/* WARNING: Removing unreachable block (ram,0x8008b77c) */
/* WARNING: Removing unreachable block (ram,0x8008b778) */

undefined1 FUN_8008b73c(char param_1,char param_2,int param_3)

{
  uint uVar1;
  undefined1 uVar2;
  
  if ((uint)((int)param_1 * (int)param_1 + (int)param_2 * (int)param_2) < (uint)(param_3 * param_3))
  {
    uVar2 = 0;
  }
  else {
    uVar1 = FUN_800452a0((double)((longlong)(double)param_2 * 0x3ff0000000000000),
                         (double)((longlong)(double)param_1 * 0x3ff0000000000000));
    uVar2 = (&DAT_80433928)[(uVar1 & 0xffff) + 0x1000 >> 0xd & 7];
  }
  return uVar2;
}



// ==== 8008b7b0  map_main_menu_direction_to_mode ====

int map_main_menu_direction_to_mode(uint direction_mask)

{
  return (int)(char)(&DAT_802da770)[direction_mask & 0xf];
}



// ==== 8008b7c8  zz_008b7c8_ ====

void zz_008b7c8_(int *param_1)

{
  if (param_1[1] != *param_1) {
    *(undefined1 *)(param_1 + 5) = 0;
    return;
  }
  *(char *)(param_1 + 5) = *(char *)(param_1 + 5) + '\x01';
  if (*(byte *)(param_1 + 5) < 0x24) {
    return;
  }
  *(undefined1 *)(param_1 + 5) = 0x1e;
  param_1[4] = *param_1;
  return;
}



// ==== 8008b810  zz_008b810_ ====

uint zz_008b810_(uint param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  
  puVar4 = &DAT_803c727c;
  uVar2 = 0;
  iVar3 = 0;
  do {
    if (((param_1 & 1 << iVar3) != 0) && (uVar1 = zz_008b900_(), (uVar1 & 0xffff & puVar4[2]) != 0))
    {
      uVar2 = uVar2 | 1 << iVar3;
    }
    iVar3 = iVar3 + 1;
    puVar4 = puVar4 + 8;
  } while (iVar3 < 4);
  return uVar2;
}



// ==== 8008b888  zz_008b888_ ====

uint zz_008b888_(uint param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  
  puVar4 = &DAT_803c71fc;
  uVar2 = 0;
  iVar3 = 0;
  do {
    if (((param_1 & 1 << iVar3) != 0) && (uVar1 = zz_008b900_(), (uVar1 & 0xffff & puVar4[2]) != 0))
    {
      uVar2 = uVar2 | 1 << iVar3;
    }
    iVar3 = iVar3 + 1;
    puVar4 = puVar4 + 8;
  } while (iVar3 < 4);
  return uVar2;
}



// ==== 8008b900  zz_008b900_ ====

undefined4 zz_008b900_(void)

{
  return 0x100;
}



// ==== 8008b908  zz_008b908_ ====

uint zz_008b908_(uint param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  
  puVar4 = &DAT_803c727c;
  uVar2 = 0;
  iVar3 = 0;
  do {
    if (((param_1 & 1 << iVar3) != 0) && (uVar1 = zz_008b9f8_(), (uVar1 & 0xffff & puVar4[2]) != 0))
    {
      uVar2 = uVar2 | 1 << iVar3;
    }
    iVar3 = iVar3 + 1;
    puVar4 = puVar4 + 8;
  } while (iVar3 < 4);
  return uVar2;
}



// ==== 8008b980  zz_008b980_ ====

uint zz_008b980_(uint param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  
  puVar4 = &DAT_803c71fc;
  uVar2 = 0;
  iVar3 = 0;
  do {
    if (((param_1 & 1 << iVar3) != 0) && (uVar1 = zz_008b9f8_(), (uVar1 & 0xffff & puVar4[2]) != 0))
    {
      uVar2 = uVar2 | 1 << iVar3;
    }
    iVar3 = iVar3 + 1;
    puVar4 = puVar4 + 8;
  } while (iVar3 < 4);
  return uVar2;
}



// ==== 8008b9f8  zz_008b9f8_ ====

undefined4 zz_008b9f8_(void)

{
  return 0x200;
}



// ==== 8008ba00  zz_008ba00_ ====

int zz_008ba00_(uint param_1,int param_2,int param_3,uint param_4)

{
  int iVar1;
  
  if ((((param_1 & 0xf) == 1) && (param_2 = param_2 + -1, param_2 < 0)) &&
     (param_2 = param_3, (param_4 & 1) != 0)) {
    param_2 = 0;
  }
  iVar1 = param_2;
  if ((((param_1 & 0xf) == 2) && (iVar1 = param_2 + 1, param_3 < param_2 + 1)) &&
     (iVar1 = param_3, (param_4 & 1) == 0)) {
    iVar1 = 0;
  }
  return iVar1;
}



// ==== 8008ba58  zz_008ba58_ ====

int zz_008ba58_(uint param_1,int param_2,int param_3,uint param_4)

{
  int iVar1;
  
  if ((((param_1 & 0xf) == 8) && (param_2 = param_2 + -1, param_2 < 0)) &&
     (param_2 = param_3, (param_4 & 1) != 0)) {
    param_2 = 0;
  }
  iVar1 = param_2;
  if ((((param_1 & 0xf) == 4) && (iVar1 = param_2 + 1, param_3 < param_2 + 1)) &&
     (iVar1 = param_3, (param_4 & 1) == 0)) {
    iVar1 = 0;
  }
  return iVar1;
}



// ==== 8008bab0  zz_008bab0_ ====

uint zz_008bab0_(uint param_1,uint param_2,int param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  puVar3 = &DAT_803c71fc;
  puVar2 = &DAT_803c727c;
  uVar5 = 0;
  iVar4 = 0;
  iVar6 = 2;
  do {
    if ((param_1 & 1 << iVar4) != 0) {
      if (param_3 == 0) {
        uVar1 = puVar2[2] | puVar2[4];
      }
      else {
        uVar1 = puVar3[2] | puVar3[4];
      }
      if ((param_2 & 1) != 0) {
        uVar5 = uVar5 | uVar1;
      }
      if ((param_2 & 2) != 0) {
        uVar5 = uVar5 | uVar1 >> 0x10 & 0xf;
      }
      if ((param_2 & 4) != 0) {
        uVar5 = uVar5 | uVar1 >> 0x14 & 0xf;
      }
    }
    if ((param_1 & 1 << iVar4 + 1) != 0) {
      if (param_3 == 0) {
        uVar1 = puVar2[10] | puVar2[0xc];
      }
      else {
        uVar1 = puVar3[10] | puVar3[0xc];
      }
      if ((param_2 & 1) != 0) {
        uVar5 = uVar5 | uVar1;
      }
      if ((param_2 & 2) != 0) {
        uVar5 = uVar5 | uVar1 >> 0x10 & 0xf;
      }
      if ((param_2 & 4) != 0) {
        uVar5 = uVar5 | uVar1 >> 0x14 & 0xf;
      }
    }
    puVar3 = puVar3 + 0x10;
    puVar2 = puVar2 + 0x10;
    iVar4 = iVar4 + 2;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  return uVar5;
}



// ==== 8008bbc0  zz_008bbc0_ ====

uint zz_008bbc0_(undefined4 param_1,uint param_2)

{
  return param_2 & 0xff1f7f;
}



// ==== 8008bbd0  zz_008bbd0_ ====

void zz_008bbd0_(int param_1,uint param_2)

{
  bool bVar1;
  undefined1 *puVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  
  if ((param_2 & 1) != 0) {
    PTR_DAT_8043394c[0x28] = 2;
    PTR_DAT_8043394c[0x29] = 3;
    PTR_DAT_8043394c[0x2a] = 2;
    PTR_DAT_8043394c[0x2c] = 4;
    PTR_DAT_8043394c[0x2d] = 4;
    PTR_DAT_8043394c[0x2e] = 4;
  }
  if ((param_2 & 2) != 0) {
    if (param_2 == 0xff) {
      iVar3 = 0;
      iVar5 = 2;
      do {
        puVar2 = PTR_DAT_8043394c + iVar3;
        *puVar2 = DAT_80433920;
        puVar2[1] = uRam80433921;
        puVar2[2] = uRam80433922;
        puVar2[3] = uRam80433923;
        puVar2[4] = uRam80433924;
        puVar2[5] = uRam80433925;
        puVar2[6] = uRam80433926;
        puVar2[7] = 0;
        puVar2 = PTR_DAT_8043394c + iVar3 + 8;
        iVar3 = iVar3 + 0x10;
        *puVar2 = DAT_80433920;
        puVar2[1] = uRam80433921;
        puVar2[2] = uRam80433922;
        puVar2[3] = uRam80433923;
        puVar2[4] = uRam80433924;
        puVar2[5] = uRam80433925;
        puVar2[6] = uRam80433926;
        puVar2[7] = 0;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      PTR_DAT_8043394c[0x30] = 0;
    }
    else {
      puVar2 = PTR_DAT_8043394c + param_1 * 8;
      *puVar2 = DAT_80433920;
      puVar2[1] = uRam80433921;
      puVar2[2] = uRam80433922;
      puVar2[3] = uRam80433923;
      puVar2[4] = uRam80433924;
      puVar2[5] = uRam80433925;
      puVar2[6] = uRam80433926;
      puVar2[7] = 0;
      PTR_DAT_8043394c[0x30] = PTR_DAT_8043394c[0x30] & ~(byte)(1 << param_1);
    }
  }
  if ((param_2 & 4) != 0) {
    *(undefined4 *)(PTR_DAT_8043394c + 0x20) = 0;
    *(undefined4 *)(PTR_DAT_8043394c + 0x24) = 0;
  }
  if ((param_2 & 8) != 0) {
    bVar1 = gnt4_OSGetSoundMode_bl();
    uVar4 = bVar1 ^ 1;
    PTR_DAT_8043394c[0x2b] = (char)uVar4;
    zz_00f0f38_((uint)bVar1);
    zz_026e0e0_(uVar4);
  }
  if (param_2 == 0xff) {
    PTR_DAT_8043394c[0x2f] = 1;
  }
  return;
}



// ==== 8008bdc8  zz_008bdc8_ ====

void zz_008bdc8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int *param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  if (*param_9 != 0x20af30) {
    gnt4_OSPanic(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80437c48,0x38,
                 s_invalid_version_number_for_textu_802b0c30,param_12,param_13,param_14,param_15,
                 param_16);
  }
  param_9[2] = param_9[2] + (int)param_9;
  for (uVar2 = 0; (uVar2 & 0xffff) < (uint)param_9[1]; uVar2 = uVar2 + 1) {
    iVar3 = (uVar2 & 0xffff) * 8;
    iVar1 = *(int *)(param_9[2] + iVar3);
    if (iVar1 != 0) {
      *(int *)(param_9[2] + iVar3) = (int)param_9 + iVar1;
      iVar1 = *(int *)(param_9[2] + iVar3);
      if (*(char *)(iVar1 + 0x23) == '\0') {
        *(int *)(iVar1 + 8) = (int)param_9 + *(int *)(iVar1 + 8);
        *(undefined1 *)(*(int *)(param_9[2] + iVar3) + 0x23) = 1;
      }
    }
    iVar3 = iVar3 + 4;
    iVar1 = *(int *)(param_9[2] + iVar3);
    if (iVar1 != 0) {
      *(int *)(param_9[2] + iVar3) = (int)param_9 + iVar1;
      iVar1 = *(int *)(param_9[2] + iVar3);
      if (*(char *)(iVar1 + 2) == '\0') {
        *(int *)(iVar1 + 8) = (int)param_9 + *(int *)(iVar1 + 8);
        *(undefined1 *)(*(int *)(param_9[2] + iVar3) + 2) = 1;
      }
    }
  }
  return;
}



// ==== 8008bed8  zz_008bed8_ ====

int zz_008bed8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int *param_9,undefined4 *param_10,uint *param_11,uint *param_12,undefined4 param_13,
               undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  ushort *puVar4;
  undefined2 *puVar5;
  uint uVar6;
  int iVar7;
  double dVar8;
  
  iVar2 = zz_008bdc8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                      param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  for (iVar7 = 0; iVar7 < iVar2; iVar7 = iVar7 + 1) {
    piVar3 = (int *)cPoseAccumulator__GetNodeMatrix_((int)param_9,iVar7);
    puVar4 = (ushort *)*piVar3;
    uVar6 = *(uint *)(puVar4 + 2);
    if (((int)uVar6 < 0xb) && (7 < (int)uVar6)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if (bVar1) {
      gnt4_GXInitTexObjCI_bl
                (param_11,*(uint *)(puVar4 + 4),(uint)puVar4[1],(uint)*puVar4,uVar6,0,0,'\0',0);
      puVar5 = (undefined2 *)piVar3[1];
      gnt4_GXInitTlutObj_bl(param_12,*(uint *)(puVar5 + 4),*(uint *)(puVar5 + 2),*puVar5);
      dVar8 = (double)FLOAT_80437c50;
      gnt4_GXInitTexObjLOD_bl(dVar8,dVar8,dVar8,param_11,1,1,0,'\0',0);
      param_10[1] = param_12;
      param_10[3] = *(undefined4 *)(piVar3[1] + 8);
    }
    else {
      gnt4_GXInitTexObj_bl
                (param_11,*(uint *)(puVar4 + 4),(uint)puVar4[1],(uint)*puVar4,uVar6,0,0,'\0');
      dVar8 = (double)FLOAT_80437c50;
      gnt4_GXInitTexObjLOD_bl(dVar8,dVar8,dVar8,param_11,1,1,0,'\0',0);
      param_10[1] = 0;
      param_10[3] = 0;
    }
    *param_10 = param_11;
    param_11 = param_11 + 8;
    param_12 = param_12 + 3;
    *(undefined2 *)(param_10 + 5) = *(undefined2 *)(*piVar3 + 2);
    *(undefined2 *)((int)param_10 + 0x16) = *(undefined2 *)*piVar3;
    param_10[4] = *(undefined4 *)(*piVar3 + 4);
    param_10[2] = *(undefined4 *)(*piVar3 + 8);
    param_10 = param_10 + 6;
  }
  return iVar2;
}



// ==== 8008c088  zz_008c088_ ====

void zz_008c088_(void)

{
  DAT_804361e8 = 0;
  DAT_804361d8 = 0;
  return;
}



// ==== 8008c098  zz_008c098_ ====

void zz_008c098_(void)

{
  DAT_804361dc = 0;
  DAT_804361e0 = 0;
  DAT_804361d4 = 0;
  DAT_804361e4 = 0;
  DAT_804361d0 = 0;
  return;
}



// ==== 8008c0b4  zz_008c0b4_ ====

void zz_008c0b4_(undefined4 param_1)

{
  undefined4 *puVar1;
  
  if (DAT_804361e8 == 0x40) {
    return;
  }
  puVar1 = &DAT_803bb020 + DAT_804361e8;
  DAT_804361e8 = DAT_804361e8 + 1;
  *puVar1 = param_1;
  return;
}



// ==== 8008c0dc  zz_008c0dc_ ====

void zz_008c0dc_(undefined4 param_1)

{
  undefined4 *puVar1;
  
  if (DAT_804361e4 == 0x200) {
    return;
  }
  puVar1 = &DAT_803ba820 + DAT_804361e4;
  DAT_804361e4 = DAT_804361e4 + 1;
  *puVar1 = param_1;
  return;
}



// ==== 8008c104  zz_008c104_ ====

void zz_008c104_(undefined4 param_1)

{
  undefined4 *puVar1;
  
  if (DAT_804361e0 == 0x200) {
    return;
  }
  puVar1 = &DAT_803ba020 + DAT_804361e0;
  DAT_804361e0 = DAT_804361e0 + 1;
  *puVar1 = param_1;
  return;
}



// ==== 8008c12c  zz_008c12c_ ====

void zz_008c12c_(undefined4 param_1)

{
  undefined4 *puVar1;
  
  if (DAT_804361dc == 0x200) {
    return;
  }
  puVar1 = &DAT_803b9820 + DAT_804361dc;
  DAT_804361dc = DAT_804361dc + 1;
  *puVar1 = param_1;
  return;
}



// ==== 8008c154  zz_008c154_ ====

void zz_008c154_(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = &DAT_803bb020;
  for (iVar2 = DAT_804361e8; 0 < iVar2; iVar2 = iVar2 + -1) {
    (*(code *)*puVar1)();
    puVar1 = puVar1 + 1;
  }
  return;
}



// ==== 8008c1b0  zz_008c1b0_ ====

void zz_008c1b0_(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = &DAT_803ba820;
  for (iVar2 = DAT_804361e4; 0 < iVar2; iVar2 = iVar2 + -1) {
    (*(code *)*puVar1)();
    puVar1 = puVar1 + 1;
  }
  gnt4_HSD_StateInvalidate_bl(0xffffffff);
  return;
}



// ==== 8008c214  zz_008c214_ ====

void zz_008c214_(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  gnt4_HSD_StateInvalidate_bl(0xffffffff);
  puVar1 = &DAT_803ba020;
  for (iVar2 = DAT_804361e0; 0 < iVar2; iVar2 = iVar2 + -1) {
    (*(code *)*puVar1)();
    puVar1 = puVar1 + 1;
  }
  return;
}



// ==== 8008c278  zz_008c278_ ====

void zz_008c278_(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  gnt4_HSD_StateInvalidate_bl(0xffffffff);
  puVar1 = &DAT_803b9820;
  for (iVar2 = DAT_804361dc; 0 < iVar2; iVar2 = iVar2 + -1) {
    (*(code *)*puVar1)();
    puVar1 = puVar1 + 1;
  }
  return;
}



// ==== 8008c2dc  zz_008c2dc_ ====

void zz_008c2dc_(void)

{
  short *psVar1;
  int iVar2;
  
  if (DAT_804361d8 != 0) {
    zz_0027e60_();
    psVar1 = (short *)&DAT_803b7820;
    for (iVar2 = DAT_804361d8; 0 < iVar2; iVar2 = iVar2 + -1) {
      zz_0027fc4_(psVar1);
      psVar1 = psVar1 + 0x20;
    }
  }
  return;
}



// ==== 8008c344  zz_008c344_ ====

void zz_008c344_(void)

{
  short *psVar1;
  int iVar2;
  
  zz_0027e60_();
  psVar1 = (short *)&DAT_803b5820;
  for (iVar2 = DAT_804361d4; 0 < iVar2; iVar2 = iVar2 + -1) {
    zz_0027fc4_(psVar1);
    psVar1 = psVar1 + 0x20;
  }
  return;
}



// ==== 8008c3a0  set_global_menu_mode ====

void set_global_menu_mode(undefined1 menu_mode)

{
  PTR_DAT_80433930[0x3e] = menu_mode;
  return;
}



// ==== 8008c3ac  dispatch_global_menu_mode ====

void dispatch_global_menu_mode(void)

{
  char menu_mode;

  menu_mode = (char)PTR_DAT_80433930[0x3e];
  (*(code *)(&PTR_FUN_802da780)[menu_mode])();
  zz_009752c_();
  return;
}



// ==== 8008c3f0  zz_008c3f0_ ====

void zz_008c3f0_(void)

{
  uint uVar1;
  
  uVar1 = zz_002b024_();
  if (uVar1 == 1) {
    zz_002ac10_();
    zz_002b034_();
  }
  else if ((0 < (int)uVar1) && ((int)uVar1 < 3)) {
    zz_002b034_();
    zz_002ac10_();
  }
  return;
}



// ==== 8008c440  zz_008c440_ ====

void zz_008c440_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,int param_11,
                int param_12,uint param_13,undefined4 *param_14,undefined4 param_15,
                undefined4 param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 uVar2;
  undefined4 extraout_r4_03;
  undefined4 extraout_r4_04;
  undefined *puVar3;
  float *pfVar4;
  undefined8 uVar5;
  double extraout_f1;
  double extraout_f1_00;
  double extraout_f1_01;
  double dVar6;
  double extraout_f1_02;
  double extraout_f1_03;
  double extraout_f1_04;
  
  zz_0005668_(param_10);
  zz_0009c4c_(DAT_80436214,param_10);
  zz_00058d0_(param_11,1);
  FUN_80009cbc(DAT_80436214,param_11,1);
  puVar3 = PTR_DAT_80433930;
  PTR_DAT_80433930[0x28] = PTR_DAT_80433930[param_9 + 0xc];
  uVar5 = gnt4_PSMTXCopy_bl(*(float **)(PTR_DAT_80433930 + param_9 * 4 + 0x14),
                            (float *)&DAT_803c1100);
  iVar1 = DAT_80436214;
  pfVar4 = *(float **)(PTR_DAT_80433930 + param_9 * 4 + 0x14);
  if (DAT_80436214 == 0) {
    puVar3 = &DAT_80437c60;
    gnt4___assert_bl(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80437c58,
                     0x1a2,&DAT_80437c60,param_12,param_13,param_14,param_15,param_16);
  }
  *(uint *)(iVar1 + 8) = *(uint *)(iVar1 + 8) | 0x80000002;
  gnt4_PSMTXCopy_bl(pfVar4,(float *)(iVar1 + 0x54));
  zz_008c1b0_();
  uVar5 = gnt4_HSD_StateInvalidate_bl(0xffffffff);
  uVar5 = gnt4_HSD_CObjSetCurrent_bl
                    (uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80436214,
                     extraout_r4,puVar3,param_12,param_13,param_14,param_15,param_16);
  if ((int)((ulonglong)uVar5 >> 0x20) != 0) {
    zz_0009838_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,(int)uVar5,
                puVar3,param_12,param_13,(float)param_14,param_15,param_16);
    gnt4_HSD_CObjEndCurrent_bl();
  }
  zz_0050800_(0,0);
  uVar5 = gnt4_HSD_StateInvalidate_bl(0xffffffff);
  uVar5 = gnt4_HSD_CObjSetCurrent_bl
                    (uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80436214,
                     extraout_r4_00,puVar3,param_12,param_13,param_14,param_15,param_16);
  if ((int)((ulonglong)uVar5 >> 0x20) != 0) {
    zz_0009838_(extraout_f1_00,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,(int)uVar5,
                puVar3,param_12,param_13,(float)param_14,param_15,param_16);
    gnt4_HSD_CObjEndCurrent_bl();
  }
  uVar5 = gnt4_HSD_StateInvalidate_bl(0xffffffff);
  uVar5 = gnt4_HSD_CObjSetCurrent_bl
                    (uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80436214,
                     extraout_r4_01,puVar3,param_12,param_13,param_14,param_15,param_16);
  uVar2 = (undefined4)uVar5;
  dVar6 = extraout_f1_01;
  if ((int)((ulonglong)uVar5 >> 0x20) != 0) {
    zz_0009838_(extraout_f1_01,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,uVar2,
                puVar3,param_12,param_13,(float)param_14,param_15,param_16);
    dVar6 = (double)gnt4_HSD_CObjEndCurrent_bl();
    uVar2 = extraout_r4_02;
  }
  uVar5 = gnt4_HSD_CObjSetCurrent_bl
                    (dVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80436214,
                     uVar2,puVar3,param_12,param_13,param_14,param_15,param_16);
  if ((int)((ulonglong)uVar5 >> 0x20) != 0) {
    zz_0009838_(extraout_f1_02,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,(int)uVar5,
                puVar3,param_12,param_13,(float)param_14,param_15,param_16);
    gnt4_HSD_CObjEndCurrent_bl();
  }
  zz_0050800_(1,0);
  uVar5 = gnt4_HSD_StateInvalidate_bl(0xffffffff);
  uVar5 = gnt4_HSD_CObjSetCurrent_bl
                    (uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80436214,
                     extraout_r4_03,puVar3,param_12,param_13,param_14,param_15,param_16);
  if ((int)((ulonglong)uVar5 >> 0x20) != 0) {
    zz_0009838_(extraout_f1_03,param_2,param_3,param_4,param_5,param_6,param_7,param_8,4,(int)uVar5,
                puVar3,param_12,param_13,(float)param_14,param_15,param_16);
    gnt4_HSD_CObjEndCurrent_bl();
  }
  zz_0050800_(2,0);
  uVar5 = gnt4_HSD_StateInvalidate_bl(0xffffffff);
  uVar5 = gnt4_HSD_CObjSetCurrent_bl
                    (uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80436214,
                     extraout_r4_04,puVar3,param_12,param_13,param_14,param_15,param_16);
  if ((int)((ulonglong)uVar5 >> 0x20) != 0) {
    zz_0009838_(extraout_f1_04,param_2,param_3,param_4,param_5,param_6,param_7,param_8,5,(int)uVar5,
                puVar3,param_12,param_13,(float)param_14,param_15,param_16);
    gnt4_HSD_CObjEndCurrent_bl();
  }
  zz_0009790_();
  zz_0050800_(3,0);
  zz_00505a8_();
  return;
}



// ==== 8008c62c  zz_008c62c_ ====

void zz_008c62c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,int param_11)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 uVar2;
  undefined4 extraout_r4_03;
  undefined4 extraout_r4_04;
  undefined4 **ppuVar3;
  float *pfVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 uVar8;
  undefined8 uVar9;
  double extraout_f1;
  double extraout_f1_00;
  double extraout_f1_01;
  double dVar10;
  double extraout_f1_02;
  double extraout_f1_03;
  double extraout_f1_04;
  undefined4 *local_68;
  uint local_64;
  undefined4 local_60;
  float local_5c;
  undefined4 local_58;
  undefined4 local_54;
  float local_50;
  undefined4 local_4c;
  undefined4 local_48;
  float afStack_44 [14];
  
  zz_0005668_(param_10);
  zz_0009c4c_(DAT_80436214,param_10);
  zz_00058d0_(param_11,1);
  FUN_80009cbc(DAT_80436214,param_11,1);
  gnt4_PSMTXCopy_bl(*(float **)(PTR_DAT_80433930 + param_9 * 4 + 0x14),(float *)&DAT_803c1100);
  PTR_DAT_80433930[0x28] = PTR_DAT_80433930[param_9 + 0xc];
  zz_008c1b0_();
  FUN_80009dac(DAT_80436214,param_11);
  puVar7 = &DAT_802b0c78;
  ppuVar3 = &local_68;
  pfVar4 = &local_5c;
  local_50 = DAT_802b0c60;
  local_4c = DAT_802b0c64;
  local_48 = DAT_802b0c68;
  local_5c = DAT_802b0c6c;
  local_58 = DAT_802b0c70;
  local_54 = DAT_802b0c74;
  local_68 = DAT_802b0c78;
  local_64 = DAT_802b0c7c;
  local_60 = DAT_802b0c80;
  uVar5 = DAT_802b0c7c;
  puVar6 = DAT_802b0c78;
  uVar8 = DAT_802b0c74;
  uVar9 = gnt4_C_MTXLookAt_bl(afStack_44,&local_50,(float *)ppuVar3,pfVar4);
  iVar1 = DAT_80436214;
  if (DAT_80436214 == 0) {
    ppuVar3 = (undefined4 **)&DAT_80437c60;
    gnt4___assert_bl(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80437c58,
                     0x1a2,&DAT_80437c60,pfVar4,uVar5,puVar6,puVar7,uVar8);
  }
  *(uint *)(iVar1 + 8) = *(uint *)(iVar1 + 8) | 0x80000002;
  gnt4_PSMTXCopy_bl(afStack_44,(float *)(iVar1 + 0x54));
  uVar9 = gnt4_HSD_StateInvalidate_bl(0xffffffff);
  uVar9 = gnt4_HSD_CObjSetCurrent_bl
                    (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80436214,
                     extraout_r4,(undefined *)ppuVar3,(int)pfVar4,uVar5,puVar6,puVar7,uVar8);
  if ((int)((ulonglong)uVar9 >> 0x20) != 0) {
    zz_0009838_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,(int)uVar9,
                ppuVar3,pfVar4,uVar5,(float)puVar6,puVar7,uVar8);
    gnt4_HSD_CObjEndCurrent_bl();
  }
  zz_0050800_(0,0);
  uVar9 = gnt4_HSD_StateInvalidate_bl(0xffffffff);
  uVar9 = gnt4_HSD_CObjSetCurrent_bl
                    (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80436214,
                     extraout_r4_00,(undefined *)ppuVar3,(int)pfVar4,uVar5,puVar6,puVar7,uVar8);
  if ((int)((ulonglong)uVar9 >> 0x20) != 0) {
    zz_0009838_(extraout_f1_00,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,(int)uVar9,
                ppuVar3,pfVar4,uVar5,(float)puVar6,puVar7,uVar8);
    gnt4_HSD_CObjEndCurrent_bl();
  }
  uVar9 = gnt4_HSD_StateInvalidate_bl(0xffffffff);
  uVar9 = gnt4_HSD_CObjSetCurrent_bl
                    (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80436214,
                     extraout_r4_01,(undefined *)ppuVar3,(int)pfVar4,uVar5,puVar6,puVar7,uVar8);
  uVar2 = (undefined4)uVar9;
  dVar10 = extraout_f1_01;
  if ((int)((ulonglong)uVar9 >> 0x20) != 0) {
    zz_0009838_(extraout_f1_01,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,uVar2,
                ppuVar3,pfVar4,uVar5,(float)puVar6,puVar7,uVar8);
    dVar10 = (double)gnt4_HSD_CObjEndCurrent_bl();
    uVar2 = extraout_r4_02;
  }
  uVar9 = gnt4_HSD_CObjSetCurrent_bl
                    (dVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80436214,
                     uVar2,(undefined *)ppuVar3,(int)pfVar4,uVar5,puVar6,puVar7,uVar8);
  if ((int)((ulonglong)uVar9 >> 0x20) != 0) {
    zz_0009838_(extraout_f1_02,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,(int)uVar9,
                ppuVar3,pfVar4,uVar5,(float)puVar6,puVar7,uVar8);
    gnt4_HSD_CObjEndCurrent_bl();
  }
  zz_0050800_(1,0);
  uVar9 = gnt4_HSD_StateInvalidate_bl(0xffffffff);
  uVar9 = gnt4_HSD_CObjSetCurrent_bl
                    (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80436214,
                     extraout_r4_03,(undefined *)ppuVar3,(int)pfVar4,uVar5,puVar6,puVar7,uVar8);
  if ((int)((ulonglong)uVar9 >> 0x20) != 0) {
    zz_0009838_(extraout_f1_03,param_2,param_3,param_4,param_5,param_6,param_7,param_8,4,(int)uVar9,
                ppuVar3,pfVar4,uVar5,(float)puVar6,puVar7,uVar8);
    gnt4_HSD_CObjEndCurrent_bl();
  }
  zz_0050800_(2,0);
  uVar9 = gnt4_HSD_StateInvalidate_bl(0xffffffff);
  uVar9 = gnt4_HSD_CObjSetCurrent_bl
                    (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80436214,
                     extraout_r4_04,(undefined *)ppuVar3,(int)pfVar4,uVar5,puVar6,puVar7,uVar8);
  if ((int)((ulonglong)uVar9 >> 0x20) != 0) {
    zz_0009838_(extraout_f1_04,param_2,param_3,param_4,param_5,param_6,param_7,param_8,5,(int)uVar9,
                ppuVar3,pfVar4,uVar5,(float)puVar6,puVar7,uVar8);
    gnt4_HSD_CObjEndCurrent_bl();
  }
  zz_0009790_();
  zz_0050800_(3,0);
  zz_00505a8_();
  return;
}



// ==== 8008c88c  zz_008c88c_ ====

void zz_008c88c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,int param_11,
                undefined4 param_12,uint param_13,undefined4 *param_14,undefined4 param_15,
                undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar1;
  float *pfVar2;
  undefined *puVar3;
  int iVar4;
  int *piVar5;
  undefined8 uVar6;
  double dVar7;
  double extraout_f1;
  float afStack_48 [15];
  
  zz_0005668_(param_10);
  zz_0009c4c_(DAT_80436214,param_10);
  zz_00058d0_(param_11,1);
  FUN_80009cbc(DAT_80436214,param_11,1);
  gnt4_PSMTXCopy_bl(*(float **)(PTR_DAT_80433930 + param_9 * 4 + 0x14),(float *)&DAT_803c1100);
  PTR_DAT_80433930[0x28] = PTR_DAT_80433930[param_9 + 0xc];
  zz_008c278_();
  FUN_80009dac(DAT_80436214,param_11);
  pfVar2 = (float *)&DAT_802da7d4;
  puVar3 = &DAT_802da7c8;
  uVar6 = gnt4_C_MTXLookAt_bl(afStack_48,(float *)&DAT_802da7bc,(float *)&DAT_802da7d4,
                              (float *)&DAT_802da7c8);
  iVar4 = DAT_80436214;
  if (DAT_80436214 == 0) {
    pfVar2 = (float *)&DAT_80437c60;
    gnt4___assert_bl(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80437c58,
                     0x1a2,&DAT_80437c60,puVar3,param_13,param_14,param_15,param_16);
  }
  *(uint *)(iVar4 + 8) = *(uint *)(iVar4 + 8) | 0x80000002;
  gnt4_PSMTXCopy_bl(afStack_48,(float *)(iVar4 + 0x54));
  dVar7 = (double)gnt4_HSD_StateInvalidate_bl(0xffffffff);
  iVar4 = 0;
  piVar5 = &DAT_802da7ac;
  uVar1 = extraout_r4;
  do {
    uVar6 = gnt4_HSD_CObjSetCurrent_bl
                      (dVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80436214,
                       uVar1,(undefined *)pfVar2,(int)puVar3,param_13,param_14,param_15,param_16);
    uVar1 = (undefined4)uVar6;
    dVar7 = extraout_f1;
    if ((int)((ulonglong)uVar6 >> 0x20) != 0) {
      zz_0009974_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*piVar5,uVar1,
                  pfVar2,puVar3,param_13,(float)param_14,param_15,param_16);
      dVar7 = (double)gnt4_HSD_CObjEndCurrent_bl();
      uVar1 = extraout_r4_00;
    }
    iVar4 = iVar4 + 1;
    piVar5 = piVar5 + 1;
  } while (iVar4 < 4);
  zz_000993c_();
  return;
}



// ==== 8008c9d4  zz_008c9d4_ ====

void zz_008c9d4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10)

{
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar1;
  undefined4 **ppuVar2;
  float *pfVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  int *piVar8;
  int iVar9;
  undefined8 uVar10;
  double dVar11;
  double extraout_f1;
  undefined4 *local_78;
  uint local_74;
  undefined4 local_70;
  float local_6c;
  undefined4 local_68;
  undefined4 local_64;
  float local_60;
  undefined4 local_5c;
  undefined4 local_58;
  float afStack_54 [16];
  
  zz_0009c4c_(DAT_80436214,param_9);
  FUN_80009cbc(DAT_80436214,param_10,1);
  zz_0005668_(param_9);
  zz_00058d0_(param_10,1);
  puVar6 = &DAT_802b0c9c;
  ppuVar2 = &local_78;
  pfVar3 = &local_6c;
  local_60 = DAT_802b0c84;
  local_5c = DAT_802b0c88;
  local_58 = DAT_802b0c8c;
  local_6c = DAT_802b0c90;
  local_68 = DAT_802b0c94;
  local_64 = DAT_802b0c98;
  local_78 = DAT_802b0c9c;
  local_74 = DAT_802b0ca0;
  local_70 = DAT_802b0ca4;
  uVar4 = DAT_802b0ca0;
  puVar5 = DAT_802b0c9c;
  uVar7 = DAT_802b0c98;
  gnt4_C_MTXLookAt_bl(afStack_54,&local_60,(float *)ppuVar2,pfVar3);
  uVar10 = gnt4_PSMTXCopy_bl(afStack_54,(float *)&DAT_803c1100);
  iVar9 = DAT_80436214;
  if (DAT_80436214 == 0) {
    ppuVar2 = (undefined4 **)&DAT_80437c60;
    gnt4___assert_bl(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80437c58,
                     0x1a2,&DAT_80437c60,pfVar3,uVar4,puVar5,puVar6,uVar7);
  }
  *(uint *)(iVar9 + 8) = *(uint *)(iVar9 + 8) | 0x80000002;
  gnt4_PSMTXCopy_bl(afStack_54,(float *)(iVar9 + 0x54));
  zz_008c214_();
  dVar11 = (double)gnt4_HSD_StateInvalidate_bl(0xffffffff);
  iVar9 = 0;
  piVar8 = &DAT_802da7e0;
  uVar1 = extraout_r4;
  do {
    uVar10 = gnt4_HSD_CObjSetCurrent_bl
                       (dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80436214,
                        uVar1,(undefined *)ppuVar2,(int)pfVar3,uVar4,puVar5,puVar6,uVar7);
    uVar1 = (undefined4)uVar10;
    dVar11 = extraout_f1;
    if ((int)((ulonglong)uVar10 >> 0x20) != 0) {
      zz_0009974_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*piVar8,uVar1,
                  (float *)ppuVar2,pfVar3,uVar4,(float)puVar5,puVar6,uVar7);
      dVar11 = (double)gnt4_HSD_CObjEndCurrent_bl();
      uVar1 = extraout_r4_00;
    }
    iVar9 = iVar9 + 1;
    piVar8 = piVar8 + 1;
  } while (iVar9 < 4);
  zz_000993c_();
  zz_0005668_(param_9);
  zz_00058d0_(param_10,1);
  zz_0050800_(4,0);
  zz_0050800_(5,0);
  zz_00505a8_();
  return;
}



// ==== 8008cb64  FUN_8008cb64 ====

void FUN_8008cb64(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8)

{
  int in_r6;
  uint in_r7;
  undefined4 *in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar1;
  
  PTR_DAT_80433930[0x34] = 0;
  uVar1 = zz_008c440_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,0,0,in_r6,
                      in_r7,in_r8,in_r9,in_r10);
  zz_008c88c_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,0,0,in_r6,in_r7,in_r8,
              in_r9,in_r10);
  uVar1 = zz_008c3f0_();
  uVar1 = zz_008c9d4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,0);
  PTR_DAT_80433930[0x34] = 4;
  zz_008c9d4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,0);
  return;
}



// ==== 8008cbd4  zz_008cbd4_ ====

void zz_008cbd4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  char cVar1;
  int in_r6;
  uint in_r7;
  undefined4 *in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar2;
  
  if (PTR_DAT_80433930[0x33] == '\0') {
    cVar1 = PTR_DAT_80433930[0x29];
    if (cVar1 == '\x02') {
      uVar2 = zz_002acd0_();
      if ((PTR_DAT_80433930[0x31] & 1) == 0) {
        uVar2 = zz_008c440_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,2,3,
                            in_r6,in_r7,in_r8,in_r9,in_r10);
        zz_008c440_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,2,5,in_r6,in_r7,
                    in_r8,in_r9,in_r10);
      }
      else {
        uVar2 = zz_008c440_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,2,4,
                            in_r6,in_r7,in_r8,in_r9,in_r10);
        zz_008c440_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,2,6,in_r6,in_r7,
                    in_r8,in_r9,in_r10);
      }
    }
    else if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        zz_008c440_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,0,0,in_r6,
                    in_r7,in_r8,in_r9,in_r10);
      }
      else if (-1 < cVar1) {
        if (PTR_DAT_80433930[0x3d] == '\0') {
          uVar2 = zz_008c440_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,1,1,
                              in_r6,in_r7,in_r8,in_r9,in_r10);
          zz_008c440_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,1,2,in_r6,
                      in_r7,in_r8,in_r9,in_r10);
        }
        else {
          uVar2 = zz_002acd0_();
          if ((PTR_DAT_80433930[0x31] & 1) == 0) {
            zz_008c440_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,4,7,in_r6,
                        in_r7,in_r8,in_r9,in_r10);
          }
          else {
            zz_008c440_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,4,8,in_r6,
                        in_r7,in_r8,in_r9,in_r10);
          }
        }
      }
    }
    else if (cVar1 < '\x04') {
      uVar2 = zz_002acd0_();
      if ((PTR_DAT_80433930[0x31] & 1) == 0) {
        zz_008c440_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,4,7,in_r6,in_r7,
                    in_r8,in_r9,in_r10);
      }
      else {
        zz_008c440_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,4,8,in_r6,in_r7,
                    in_r8,in_r9,in_r10);
      }
    }
  }
  else {
    zz_008c440_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,0,0,in_r6,in_r7,
                in_r8,in_r9,in_r10);
  }
  uVar2 = zz_008c3f0_();
  if (PTR_DAT_80433930[0x33] == '\0') {
    cVar1 = PTR_DAT_80433930[0x29];
    if (cVar1 == '\x02') {
      if ((PTR_DAT_80433930[0x31] & 1) == 0) {
        uVar2 = zz_008c88c_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,2,3,
                            in_r6,in_r7,in_r8,in_r9,in_r10);
        zz_008c88c_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,2,5,in_r6,in_r7,
                    in_r8,in_r9,in_r10);
      }
      else {
        uVar2 = zz_008c88c_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,2,4,
                            in_r6,in_r7,in_r8,in_r9,in_r10);
        zz_008c88c_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,2,6,in_r6,in_r7,
                    in_r8,in_r9,in_r10);
      }
      zz_002ab70_();
    }
    else if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        zz_008c88c_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,0,0,in_r6,in_r7,
                    in_r8,in_r9,in_r10);
      }
      else if (-1 < cVar1) {
        if (PTR_DAT_80433930[0x3d] == '\0') {
          uVar2 = zz_008c88c_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,1,1,
                              in_r6,in_r7,in_r8,in_r9,in_r10);
          zz_008c88c_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,1,2,in_r6,
                      in_r7,in_r8,in_r9,in_r10);
        }
        else if ((PTR_DAT_80433930[0x31] & 1) == 0) {
          zz_008c88c_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,4,7,in_r6,
                      in_r7,in_r8,in_r9,in_r10);
        }
        else {
          zz_008c88c_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,4,8,in_r6,
                      in_r7,in_r8,in_r9,in_r10);
        }
        zz_002ab70_();
      }
    }
    else if (cVar1 < '\x04') {
      if ((PTR_DAT_80433930[0x31] & 1) == 0) {
        zz_008c88c_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,4,7,in_r6,in_r7,
                    in_r8,in_r9,in_r10);
      }
      else {
        zz_008c88c_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,4,8,in_r6,in_r7,
                    in_r8,in_r9,in_r10);
      }
      zz_002ab70_();
    }
  }
  else {
    zz_008c88c_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,0,0,in_r6,in_r7,
                in_r8,in_r9,in_r10);
  }
  PTR_DAT_80433930[0x31] = PTR_DAT_80433930[0x31] + '\x01';
  return;
}



// ==== 8008cec8  zz_008cec8_ ====

void zz_008cec8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  undefined8 uVar1;
  
  PTR_DAT_80433930[0x34] = 0;
  zz_008cbd4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  uVar1 = zz_002a888_();
  zz_008c9d4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,0);
  uVar1 = zz_002a888_();
  PTR_DAT_80433930[0x34] = 4;
  zz_008c9d4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,0);
  return;
}



// ==== 8008cf20  zz_008cf20_ ====

void zz_008cf20_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  int in_r6;
  uint in_r7;
  undefined4 *in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar1;
  
  PTR_DAT_80433930[0x34] = 0;
  uVar1 = zz_008c440_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,2,3,in_r6,
                      in_r7,in_r8,in_r9,in_r10);
  uVar1 = zz_008c88c_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,2,3,in_r6,
                      in_r7,in_r8,in_r9,in_r10);
  PTR_DAT_80433930[0x34] = 1;
  uVar1 = zz_008c440_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,2,5,in_r6,
                      in_r7,in_r8,in_r9,in_r10);
  uVar1 = zz_008c88c_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,2,5,in_r6,
                      in_r7,in_r8,in_r9,in_r10);
  PTR_DAT_80433930[0x34] = 2;
  uVar1 = zz_008c440_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,2,4,in_r6,
                      in_r7,in_r8,in_r9,in_r10);
  uVar1 = zz_008c88c_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,2,4,in_r6,
                      in_r7,in_r8,in_r9,in_r10);
  PTR_DAT_80433930[0x34] = 3;
  uVar1 = zz_008c440_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,2,6,in_r6,
                      in_r7,in_r8,in_r9,in_r10);
  zz_008c88c_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,2,6,in_r6,in_r7,in_r8,
              in_r9,in_r10);
  uVar1 = zz_002a888_();
  PTR_DAT_80433930[0x34] = 4;
  uVar1 = zz_008c440_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,4,0,0,in_r6,
                      in_r7,in_r8,in_r9,in_r10);
  zz_008c88c_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,4,0,0,in_r6,in_r7,in_r8,
              in_r9,in_r10);
  uVar1 = zz_008c3f0_();
  PTR_DAT_80433930[0x34] = 0;
  uVar1 = zz_008c9d4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,0);
  PTR_DAT_80433930[0x34] = 4;
  zz_008c9d4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,0);
  return;
}



// ==== 8008d050  zz_008d050_ ====

void zz_008d050_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  char cVar1;
  undefined8 uVar2;
  
  PTR_DAT_80433930[0x34] = 0;
  zz_008cbd4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  uVar2 = zz_002a888_();
  if (PTR_DAT_80433930[0x33] == '\0') {
    cVar1 = PTR_DAT_80433930[0x29];
    if (cVar1 == '\x02') {
      PTR_DAT_80433930[0x34] = 0;
      uVar2 = zz_008c9d4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,6,3);
      PTR_DAT_80433930[0x34] = 1;
      uVar2 = zz_008c9d4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,6,5);
      PTR_DAT_80433930[0x34] = 2;
      uVar2 = zz_008c9d4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,6,4);
      PTR_DAT_80433930[0x34] = 3;
      uVar2 = zz_008c9d4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,6,6);
      PTR_DAT_80433930[0x34] = 4;
      zz_008c9d4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,0);
    }
    else {
      if (cVar1 < '\x02') {
        if (cVar1 == '\0') {
          PTR_DAT_80433930[0x34] = 0;
          uVar2 = zz_008c9d4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,0);
          PTR_DAT_80433930[0x34] = 4;
          zz_008c9d4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,0);
          return;
        }
        if (cVar1 < '\0') {
          return;
        }
      }
      else if ('\x03' < cVar1) {
        return;
      }
      PTR_DAT_80433930[0x34] = 0;
      uVar2 = zz_008c9d4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,5,7);
      PTR_DAT_80433930[0x34] = 1;
      uVar2 = zz_008c9d4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,5,8);
      PTR_DAT_80433930[0x34] = 4;
      zz_008c9d4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,0);
    }
  }
  else {
    PTR_DAT_80433930[0x34] = 0;
    zz_008c9d4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,0);
  }
  return;
}



// ==== 8008d1c4  zz_008d1c4_ ====

void zz_008d1c4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  int in_r6;
  uint in_r7;
  undefined4 *in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar1;
  
  PTR_DAT_80433930[0x34] = 0;
  zz_008c440_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,3,0,in_r6,in_r7,
              in_r8,in_r9,in_r10);
  uVar1 = zz_002a888_();
  PTR_DAT_80433930[0x34] = 4;
  uVar1 = zz_008c440_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,7,0,in_r6,
                      in_r7,in_r8,in_r9,in_r10);
  PTR_DAT_80433930[0x34] = 5;
  uVar1 = zz_008c440_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,3,0,in_r6,
                      in_r7,in_r8,in_r9,in_r10);
  PTR_DAT_80433930[0x34] = 1;
  zz_008c440_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,7,0,in_r6,in_r7,in_r8,
              in_r9,in_r10);
  uVar1 = zz_002a888_();
  PTR_DAT_80433930[0x34] = 2;
  zz_008c62c_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,7,0);
  uVar1 = zz_002a888_();
  PTR_DAT_80433930[0x34] = 3;
  zz_008c440_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,3,0,in_r6,in_r7,in_r8,
              in_r9,in_r10);
  uVar1 = zz_002a888_();
  PTR_DAT_80433930[0x34] = 6;
  zz_008c440_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,3,0,in_r6,in_r7,in_r8,
              in_r9,in_r10);
  uVar1 = zz_002a888_();
  PTR_DAT_80433930[0x34] = 0;
  uVar1 = zz_008c9d4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,0);
  PTR_DAT_80433930[0x34] = 4;
  zz_008c9d4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,0);
  return;
}



// ==== 8008d2e8  zz_008d2e8_ ====

void zz_008d2e8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  int in_r6;
  uint in_r7;
  undefined4 *in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar1;
  
  PTR_DAT_80433930[0x34] = 1;
  zz_008c9d4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,0);
  uVar1 = zz_002a888_();
  PTR_DAT_80433930[0x34] = 0;
  uVar1 = zz_008c440_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,0,0,in_r6,
                      in_r7,in_r8,in_r9,in_r10);
  zz_008c88c_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,0,0,in_r6,in_r7,in_r8,
              in_r9,in_r10);
  uVar1 = zz_008c3f0_();
  zz_008c9d4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,0);
  return;
}



// ==== 8008d35c  zz_008d35c_ ====

void zz_008d35c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  int in_r6;
  uint in_r7;
  undefined4 *in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar1;
  
  PTR_DAT_80433930[0x34] = 0;
  zz_008c440_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,3,0,in_r6,in_r7,
              in_r8,in_r9,in_r10);
  uVar1 = zz_002a888_();
  PTR_DAT_80433930[0x34] = 1;
  zz_008c440_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,3,0,in_r6,in_r7,in_r8,
              in_r9,in_r10);
  uVar1 = zz_002a888_();
  PTR_DAT_80433930[0x34] = 2;
  zz_008c440_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,3,0,in_r6,in_r7,in_r8,
              in_r9,in_r10);
  uVar1 = zz_002a888_();
  PTR_DAT_80433930[0x34] = 3;
  zz_008c440_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,3,0,in_r6,in_r7,in_r8,
              in_r9,in_r10);
  uVar1 = zz_002a888_();
  PTR_DAT_80433930[0x34] = 4;
  zz_008c440_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,3,0,in_r6,in_r7,in_r8,
              in_r9,in_r10);
  uVar1 = zz_002a888_();
  PTR_DAT_80433930[0x34] = 6;
  zz_008c440_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,3,0,in_r6,in_r7,in_r8,
              in_r9,in_r10);
  uVar1 = zz_002a888_();
  PTR_DAT_80433930[0x34] = 0;
  uVar1 = zz_008c9d4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,0);
  PTR_DAT_80433930[0x34] = 4;
  zz_008c9d4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,0);
  return;
}



// ==== 8008d468  zz_008d468_ ====

void zz_008d468_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  int in_r6;
  uint in_r7;
  undefined4 *in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar1;
  
  PTR_DAT_80433930[0x34] = 0;
  uVar1 = zz_008c440_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,0,0,in_r6,
                      in_r7,in_r8,in_r9,in_r10);
  zz_008c88c_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,0,0,in_r6,in_r7,in_r8,
              in_r9,in_r10);
  uVar1 = zz_002a888_();
  PTR_DAT_80433930[0x34] = 1;
  zz_008c440_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,0,0,in_r6,in_r7,in_r8,
              in_r9,in_r10);
  uVar1 = zz_002a888_();
  PTR_DAT_80433930[0x34] = 2;
  zz_008c440_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,0,0,in_r6,in_r7,in_r8,
              in_r9,in_r10);
  uVar1 = zz_002a888_();
  PTR_DAT_80433930[0x34] = 0;
  uVar1 = zz_008c9d4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,0);
  PTR_DAT_80433930[0x34] = 4;
  zz_008c9d4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,0);
  return;
}



// ==== 8008d524  zz_008d524_ ====

void zz_008d524_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  int in_r6;
  uint in_r7;
  undefined4 *in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar1;
  
  PTR_DAT_80433930[0x34] = 0;
  uVar1 = zz_008c440_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,8,1,in_r6,
                      in_r7,in_r8,in_r9,in_r10);
  PTR_DAT_80433930[0x34] = 1;
  zz_008c440_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,8,2,in_r6,in_r7,in_r8,
              in_r9,in_r10);
  uVar1 = zz_002a888_();
  PTR_DAT_80433930[0x34] = 2;
  zz_008c440_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,3,0,in_r6,in_r7,in_r8,
              in_r9,in_r10);
  uVar1 = zz_002a888_();
  PTR_DAT_80433930[0x34] = 0;
  zz_008c9d4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,0);
  uVar1 = zz_002a888_();
  PTR_DAT_80433930[0x34] = 4;
  zz_008c9d4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,0);
  return;
}



// ==== 8008d5d0  zz_008d5d0_ ====

void zz_008d5d0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  int in_r6;
  uint in_r7;
  undefined4 *in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar1;
  
  PTR_DAT_80433930[0x34] = 1;
  zz_008c440_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,3,0,in_r6,in_r7,
              in_r8,in_r9,in_r10);
  uVar1 = zz_002a888_();
  PTR_DAT_80433930[0x34] = 0;
  zz_008c440_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,0,0,in_r6,in_r7,in_r8,
              in_r9,in_r10);
  uVar1 = zz_002a888_();
  PTR_DAT_80433930[0x34] = 2;
  zz_008c440_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,3,0,in_r6,in_r7,in_r8,
              in_r9,in_r10);
  zz_002a888_();
  return;
}



// ==== 8008d64c  zz_008d64c_ ====

void zz_008d64c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  char cVar1;
  undefined8 uVar2;
  
  uVar2 = zz_002a888_();
  PTR_DAT_80433930[0x34] = 2;
  uVar2 = zz_008c9d4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,0);
  cVar1 = PTR_DAT_80433930[0x29];
  if (cVar1 == '\x02') goto LAB_8008d6ec;
  if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      PTR_DAT_80433930[0x34] = 0;
      uVar2 = zz_008c9d4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,0);
      goto LAB_8008d6ec;
    }
    if (cVar1 < '\0') goto LAB_8008d6ec;
  }
  else if ('\x03' < cVar1) goto LAB_8008d6ec;
  PTR_DAT_80433930[0x34] = 0;
  uVar2 = zz_008c9d4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,5,7);
  PTR_DAT_80433930[0x34] = 1;
  uVar2 = zz_008c9d4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,5,8);
LAB_8008d6ec:
  PTR_DAT_80433930[0x34] = 4;
  zz_008c9d4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,0);
  return;
}



// ==== 8008d714  zz_008d714_ ====

undefined4 zz_008d714_(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_804362b4;
  DAT_804362b4 = param_1;
  return uVar1;
}



// ==== 8008d724  zz_008d724_ ====

undefined4 zz_008d724_(void)

{
  return DAT_804362b4;
}



// ==== 8008d72c  zz_008d72c_ ====

int zz_008d72c_(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = (*DAT_803ac468)();
  if (iVar1 == 0) {
    uVar2 = zz_008d724_();
    *(undefined4 *)(param_1 + 0x20) = uVar2;
    iVar1 = 0;
  }
  return iVar1;
}



// ==== 8008d780  zz_008d780_ ====

undefined4 zz_008d780_(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_804362b0;
  DAT_804362b0 = param_1;
  return uVar1;
}



// ==== 8008d790  zz_008d790_ ====

undefined4 zz_008d790_(void)

{
  return DAT_804362b0;
}



// ==== 8008d798  zz_008d798_ ====

int zz_008d798_(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = (*DAT_803ac468)();
  if (iVar1 == 0) {
    uVar2 = zz_008d790_();
    *(undefined4 *)(param_1 + 0x20) = uVar2;
    iVar1 = 0;
  }
  return iVar1;
}



// ==== 8008d7ec  zz_008d7ec_ ====

int * zz_008d7ec_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 int *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 *puVar1;
  int *piVar2;
  char *pcVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  undefined8 uVar7;
  undefined8 uVar8;
  
  puVar1 = (undefined4 *)(*DAT_803ac46c)();
  pcVar3 = (char *)0x0;
  piVar2 = param_11;
  uVar8 = gnt4_HSD_TExpCnst_bl
                    (extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     *(undefined4 *)(param_9 + 0x20),1,(char *)0x0,param_11,param_13,param_14,
                     param_15,param_16);
  uVar7 = extraout_f1_00;
  piVar2 = gnt4_HSD_TExpTev_bl(extraout_f1_00,param_2,param_3,param_4,param_5,param_6,param_7,
                               param_8,param_11,(int)uVar8,pcVar3,piVar2,param_13,param_14,param_15,
                               param_16);
  uVar7 = gnt4_HSD_TExpColorOp_bl
                    (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar2,0,0,0,1,
                     param_14,param_15,param_16);
  uVar4 = 7;
  uVar5 = 0;
  uVar6 = 1;
  uVar7 = gnt4_HSD_TExpColorIn_bl
                    (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar2,1,puVar1,7
                     ,(undefined4 *)0x0,7,(undefined4 *)0x0,1,
                     (undefined4 *)((ulonglong)uVar8 >> 0x20));
  uVar7 = gnt4_HSD_TExpAlphaOp_bl
                    (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar2,0,0,0,1,
                     uVar4,uVar5,uVar6);
  gnt4_HSD_TExpAlphaIn_bl
            (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar2,7,
             (undefined4 *)0x0,7,(undefined4 *)0x0,7,(undefined4 *)0x0,5,puVar1);
  return piVar2;
}



// ==== 8008d8e8  zz_008d8e8_ ====

int * zz_008d8e8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 int *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 *puVar1;
  int *piVar2;
  int *piVar3;
  char *pcVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  undefined8 uVar10;
  undefined8 extraout_f1_01;
  undefined8 uVar11;
  
  puVar1 = (undefined4 *)(*DAT_803ac46c)();
  pcVar4 = (char *)0x0;
  piVar3 = param_11;
  uVar11 = gnt4_HSD_TExpCnst_bl
                     (extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0x20) + 4,1,(char *)0x0,param_11,param_13,param_14,param_15
                      ,param_16);
  puVar6 = (undefined4 *)((ulonglong)uVar11 >> 0x20);
  uVar10 = extraout_f1_00;
  piVar2 = gnt4_HSD_TExpTev_bl(extraout_f1_00,param_2,param_3,param_4,param_5,param_6,param_7,
                               param_8,param_11,(int)uVar11,pcVar4,piVar3,param_13,param_14,param_15
                               ,param_16);
  uVar10 = gnt4_HSD_TExpColorOp_bl
                     (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar2,0,0,0,1,
                      param_14,param_15,param_16);
  uVar5 = 1;
  uVar8 = 7;
  uVar10 = gnt4_HSD_TExpColorIn_bl
                     (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar2,7,
                      (undefined4 *)0x0,1,puVar1,1,puVar6,7,(undefined4 *)0x0);
  uVar10 = gnt4_HSD_TExpAlphaOp_bl
                     (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar2,0,0,0,1,
                      uVar5,puVar6,uVar8);
  uVar5 = 0;
  uVar8 = 7;
  uVar7 = 0;
  uVar9 = 5;
  uVar10 = gnt4_HSD_TExpAlphaIn_bl
                     (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar2,7,
                      (undefined4 *)0x0,7,(undefined4 *)0x0,7,(undefined4 *)0x0,5,puVar1);
  pcVar4 = (char *)0x0;
  piVar3 = param_11;
  uVar11 = gnt4_HSD_TExpCnst_bl
                     (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(undefined4 *)(param_9 + 0x20),1,(char *)0x0,param_11,uVar5,uVar8,uVar7,uVar9
                     );
  uVar10 = extraout_f1_01;
  piVar3 = gnt4_HSD_TExpTev_bl(extraout_f1_01,param_2,param_3,param_4,param_5,param_6,param_7,
                               param_8,param_11,(int)uVar11,pcVar4,piVar3,uVar5,uVar8,uVar7,uVar9);
  uVar10 = gnt4_HSD_TExpColorOp_bl
                     (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,0,0,0,1,
                      uVar8,uVar7,uVar9);
  uVar5 = 7;
  uVar8 = 0;
  uVar7 = 1;
  uVar10 = gnt4_HSD_TExpColorIn_bl
                     (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,1,piVar2
                      ,7,(undefined4 *)0x0,7,(undefined4 *)0x0,1,
                      (undefined4 *)((ulonglong)uVar11 >> 0x20));
  uVar10 = gnt4_HSD_TExpAlphaOp_bl
                     (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,0,0,0,1,
                      uVar5,uVar8,uVar7);
  gnt4_HSD_TExpAlphaIn_bl
            (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar3,7,
             (undefined4 *)0x0,7,(undefined4 *)0x0,7,(undefined4 *)0x0,5,piVar2);
  return piVar3;
}



// ==== 8008da7c  zz_008da7c_ ====

void zz_008da7c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  undefined4 in_r9;
  undefined4 in_r10;
  
  gnt4_hsdInitClassInfo_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd25810,
             &PTR_gnt4_MObjInfoInit_bl_803ac428,s_poqeel_class_library_802b0cf0,s_fade_mobj_802b0d08
             ,0x54,0x24,in_r9,in_r10);
  DAT_802da830 = zz_008d72c_;
  DAT_802da834 = zz_008d7ec_;
  return;
}



// ==== 8008dae4  zz_008dae4_ ====

void zz_008dae4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  undefined4 in_r9;
  undefined4 in_r10;
  
  gnt4_hsdInitClassInfo_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd257bc,
             &PTR_gnt4_MObjInfoInit_bl_803ac428,s_poqeel_class_library_802b0cf0,
             s_multi_mobj_802b0d14,0x54,0x24,in_r9,in_r10);
  DAT_802da884 = zz_008d798_;
  DAT_802da888 = zz_008d8e8_;
  return;
}



// ==== 8008db4c  zz_008db4c_ ====

void zz_008db4c_(void)

{
  gnt4_memset(&DAT_803ca850,0,0x148);
  DAT_804362c0 = 0;
  DAT_804362c4 = (void *)(DAT_80436238 + 0x87000);
  DAT_803ca86e = 0;
  DAT_803ca906 = 1;
  DAT_804362bc = 0;
  gnt4_memset(DAT_804362c4,0,0x14000);
  DAT_804362c8 = DAT_80436238 + 0x9b000;
  return;
}



// ==== 8008dbcc  zz_008dbcc_ ====

int zz_008dbcc_(void)

{
  return (int)DAT_803ca850;
}



// ==== 8008dbe0  zz_008dbe0_ ====

int zz_008dbe0_(void)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  zz_008de04_();
  if ((DAT_803ca850 == '\0') && (DAT_804362c0 != DAT_804362bc)) {
    DAT_803ca850 = '\x01';
    iVar3 = (int)DAT_803ca852;
    uVar1 = *(undefined4 *)(&DAT_803ca7d0 + DAT_804362bc * 4);
    (&DAT_803ca86f)[iVar3 * 0x98] = 0;
    (&DAT_803ca870)[iVar3 * 0x98] = (char)uVar1;
    (&DAT_803ca86f)[DAT_803ca852 * 0x98] = 0;
  }
  if (DAT_803ca850 == '\x01') {
    iVar3 = DAT_803ca852 * 0x98;
    iVar2 = (**(code **)(&DAT_802dad98 + (char)(&DAT_803ca870)[iVar3] * 4))
                      (&DAT_803ca868 + DAT_803ca852 * 0x26);
    if (iVar2 == 0) {
      DAT_804362bc = DAT_804362bc + 1 & 0x1f;
      if (DAT_804362c0 == DAT_804362bc) {
        DAT_803ca850 = '\0';
      }
      else {
        iVar2 = DAT_804362bc * 4;
        (&DAT_803ca86f)[iVar3] = 0;
        (&DAT_803ca870)[iVar3] = (char)*(undefined4 *)(&DAT_803ca7d0 + iVar2);
        (&DAT_803ca86f)[DAT_803ca852 * 0x98] = 0;
      }
    }
    else if (iVar2 == -1) {
      DAT_804362bc = 0;
      (&DAT_803ca875)[iVar3] = (&DAT_803ca870)[iVar3];
      DAT_804362c0 = 0;
      if (DAT_803ca853 == 0) {
        DAT_803ca850 = '\0';
      }
      else {
        DAT_803ca850 = '\x02';
      }
    }
  }
  else if (DAT_803ca850 == '\x02') {
    iVar3 = 0;
    do {
      if ((((uint)DAT_803ca853 & 1 << iVar3) != 0) && (iVar2 = zz_0221858_(iVar3), iVar2 != -1)) {
        DAT_803ca853 = DAT_803ca853 & ~(byte)(1 << iVar3);
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 2);
    if (DAT_803ca853 == 0) {
      DAT_803ca850 = '\0';
    }
  }
  return (int)DAT_803ca850;
}



// ==== 8008de04  zz_008de04_ ====

void zz_008de04_(void)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  
  puVar3 = &DAT_803ca850;
  iVar2 = 0;
  do {
    iVar1 = zz_0220f58_(iVar2,(uint *)(puVar3 + 0x48),(undefined4 *)(puVar3 + 0x4c));
    *(int *)(puVar3 + 0x18) = iVar1;
    iVar1 = *(int *)(puVar3 + 0x18);
    if (iVar1 == -2) {
      puVar3[0x21] = 1;
      puVar3[0x22] = 2;
      puVar3[0x23] = 1;
    }
    else if (iVar1 < -2) {
      if (iVar1 == -0x80) {
        puVar3[0x21] = 0xff;
        puVar3[0x22] = 0xff;
        puVar3[0x23] = 0;
      }
      else if ((-0x81 < iVar1) && (-4 < iVar1)) {
        puVar3[0x21] = 0;
        puVar3[0x22] = 0;
        puVar3[0x23] = 0;
      }
    }
    else if (iVar1 == 0) {
      puVar3[0x21] = 1;
      puVar3[0x22] = 1;
      puVar3[0x23] = 1;
    }
    else if (iVar1 < 0) {
      puVar3[0x23] = 0;
    }
    iVar2 = iVar2 + 1;
    puVar3 = puVar3 + 0x98;
  } while (iVar2 < 2);
  return;
}



// ==== 8008df00  zz_008df00_ ====

uint zz_008df00_(int param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = 0;
  if ((param_2 & 1) != 0) {
    uVar2 = zz_008e704_(param_1,0,0x2040,0);
  }
  zz_008e4e4_(0,(short)uVar2);
  uVar1 = uVar2;
  if ((param_2 & 2) != 0) {
    if (*(char *)(param_1 + 0x2042) != '\0') {
      uVar1 = zz_008e704_(param_1 + 0x2084,0,0x40,0);
      uVar2 = uVar2 | uVar1;
    }
  }
  zz_008e4e4_(1,(short)uVar1);
  uVar1 = 0;
  if ((param_2 & 4) != 0) {
    if (*(char *)(param_1 + 0x2043) != '\0') {
      uVar1 = zz_008e704_(param_1 + 0x20c8,0,0xabe4,0);
      uVar2 = uVar2 | uVar1;
    }
  }
  zz_008e4e4_(2,(short)uVar1);
  uVar1 = 0;
  if ((param_2 & 8) != 0) {
    if (*(char *)(param_1 + 0x2044) != '\0') {
      uVar1 = zz_008e704_(param_1 + 0xccb0,0,0x2190,0);
      uVar2 = uVar2 | uVar1;
    }
  }
  zz_008e4e4_(3,(short)uVar1);
  uVar1 = 0;
  if ((param_2 & 0x10) != 0) {
    if (*(char *)(param_1 + 0x2045) != '\0') {
      uVar1 = zz_008e704_(param_1 + 0xee44,0,0x4628,0);
      uVar2 = uVar2 | uVar1;
    }
  }
  zz_008e4e4_(4,(short)uVar1);
  uVar1 = 0;
  if (((param_2 & 0x20) != 0) && (*(char *)(param_1 + 0x2046) != '\0')) {
    uVar1 = zz_008e704_(param_1 + 0x13470,0,600,0);
    uVar2 = uVar2 | uVar1;
  }
  zz_008e4e4_(5,(short)uVar1);
  return uVar2;
}



// ==== 8008e0b8  zz_008e0b8_ ====

undefined4 zz_008e0b8_(int param_1)

{
  return (&DAT_803ca868)[param_1 * 0x26];
}



// ==== 8008e0d0  zz_008e0d0_ ====

int zz_008e0d0_(int param_1)

{
  return (int)(char)(&DAT_803ca874)[param_1 * 0x98];
}



// ==== 8008e0ec  zz_008e0ec_ ====

int zz_008e0ec_(int param_1)

{
  return (int)(char)(&DAT_803ca875)[param_1 * 0x98];
}



// ==== 8008e108  zz_008e108_ ====

undefined4 zz_008e108_(undefined1 param_1)

{
  if (DAT_803ca850 != '\0') {
    return 1;
  }
  DAT_803ca852 = param_1;
  return 0;
}



// ==== 8008e12c  zz_008e12c_ ====

bool zz_008e12c_(char *param_1)

{
  bool bVar1;
  
  bVar1 = DAT_803ca850 == '\0';
  if (bVar1) {
    strcpy((char *)(DAT_803ca852 * 0x98 + -0x7fc35727),param_1);
  }
  return !bVar1;
}



// ==== 8008e184  zz_008e184_ ====

int zz_008e184_(int param_1)

{
  int iVar1;
  
  if (DAT_803ca850 != '\0') {
    return 0;
  }
  iVar1 = (param_1 + 0x1fU & 0xffffffe0) + DAT_80436238;
  *(int *)(&DAT_803ca8b0 + DAT_803ca852 * 0x98) = iVar1;
  return iVar1;
}



// ==== 8008e1c8  zz_008e1c8_ ====

undefined4 zz_008e1c8_(void)

{
  return *(undefined4 *)(&DAT_803ca8b0 + DAT_803ca852 * 0x98);
}



// ==== 8008e1e8  zz_008e1e8_ ====

undefined4 zz_008e1e8_(undefined4 param_1)

{
  if (DAT_803ca850 != '\0') {
    return 1;
  }
  *(undefined4 *)(&DAT_803ca8a0 + DAT_803ca852 * 0x98) = param_1;
  return 0;
}



// ==== 8008e220  zz_008e220_ ====

undefined4 zz_008e220_(undefined4 param_1)

{
  if (DAT_803ca850 != '\0') {
    return 1;
  }
  *(undefined4 *)(&DAT_803ca8a4 + DAT_803ca852 * 0x98) = param_1;
  return 0;
}



// ==== 8008e258  zz_008e258_ ====

undefined4 zz_008e258_(undefined4 param_1)

{
  if (DAT_803ca850 != '\0') {
    return 1;
  }
  *(undefined4 *)(&DAT_803ca8c0 + DAT_803ca852 * 0x98) = param_1;
  return 0;
}



// ==== 8008e290  zz_008e290_ ====

undefined4 zz_008e290_(void)

{
  return *(undefined4 *)(&DAT_803ca8c0 + DAT_803ca852 * 0x98);
}



// ==== 8008e2b0  zz_008e2b0_ ====

undefined4 zz_008e2b0_(undefined4 param_1)

{
  if (DAT_803ca850 != '\0') {
    return 1;
  }
  *(undefined4 *)(&DAT_803ca8a8 + DAT_803ca852 * 0x98) = param_1;
  return 0;
}



// ==== 8008e2e8  zz_008e2e8_ ====

void zz_008e2e8_(undefined1 param_1)

{
  (&DAT_803ca888)[DAT_803ca852 * 0x98] = param_1;
  return;
}



// ==== 8008e308  zz_008e308_ ====

undefined1 zz_008e308_(void)

{
  return (&DAT_803ca888)[DAT_803ca852 * 0x98];
}



// ==== 8008e328  CARDGetXferredBytes ====

undefined4 CARDGetXferredBytes(int param_1)

{
  return *(undefined4 *)(&DAT_803ca89c + param_1 * 0x98);
}



// ==== 8008e340  zz_008e340_ ====

int zz_008e340_(int param_1)

{
  return (int)(char)(&DAT_803ca873)[param_1 * 0x98];
}



// ==== 8008e35c  zz_008e35c_ ====

int zz_008e35c_(int param_1)

{
  return (int)(char)(&DAT_803ca872)[param_1 * 0x98];
}



// ==== 8008e378  zz_008e378_ ====

undefined4 zz_008e378_(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = DAT_803ca852 * 0x98;
  switch(param_1) {
  case 1:
    *(int *)(&DAT_803ca8b8 + iVar1) = *(int *)(&DAT_803ca8b8 + iVar1) + 0xa000;
    break;
  case 4:
    *(int *)(&DAT_803ca8b8 + iVar1) = *(int *)(&DAT_803ca8b8 + iVar1) + 0x4000;
    break;
  case 5:
    *(int *)(&DAT_803ca8b8 + iVar1) = *(int *)(&DAT_803ca8b8 + iVar1) + 0x4000;
    break;
  case 6:
    *(int *)(&DAT_803ca8b8 + iVar1) = *(int *)(&DAT_803ca8b8 + iVar1) + 0xa000;
    break;
  case 9:
    *(int *)(&DAT_803ca8b8 + iVar1) =
         *(int *)(&DAT_803ca8b8 + iVar1) + *(int *)(&DAT_803ca8a0 + iVar1);
    break;
  case 10:
    *(int *)(&DAT_803ca8b8 + iVar1) =
         *(int *)(&DAT_803ca8a0 + iVar1) + *(int *)(&DAT_803ca8b8 + iVar1) + 0x2000;
    break;
  case 0xc:
    *(int *)(&DAT_803ca8b8 + iVar1) = *(int *)(&DAT_803ca8b8 + iVar1) + 0x2000;
  }
  *(undefined4 *)(&DAT_803ca7d0 + DAT_804362c0 * 4) = param_1;
  DAT_804362c0 = DAT_804362c0 + 1 & 0x1f;
  return 0;
}



// ==== 8008e45c  zz_008e45c_ ====

undefined4 zz_008e45c_(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  int iVar1;
  
  iVar1 = param_1 * 0x98;
  if (((&DAT_803ca871)[iVar1] == '\x01') && ((&DAT_803ca873)[iVar1] != '\0')) {
    *param_2 = *(undefined4 *)(&DAT_803ca87c + iVar1);
    *param_3 = *(undefined4 *)(&DAT_803ca878 + iVar1);
    return 0;
  }
  *param_2 = 0;
  *param_3 = 0;
  return 1;
}



// ==== 8008e4b0  zz_008e4b0_ ====

undefined2 zz_008e4b0_(int param_1)

{
  return *(undefined2 *)(&DAT_803ca88a + param_1 * 0x98);
}



// ==== 8008e4c8  zz_008e4c8_ ====

undefined8 zz_008e4c8_(int param_1)

{
  return *(undefined8 *)(&DAT_803ca890 + param_1 * 0x98);
}



// ==== 8008e4e4  zz_008e4e4_ ====

void zz_008e4e4_(int param_1,undefined2 param_2)

{
  *(undefined2 *)(DAT_803ca852 * 0x98 + param_1 * 2 + -0x7fc3573c) = param_2;
  return;
}



// ==== 8008e50c  zz_008e50c_ ====

undefined2 zz_008e50c_(int param_1)

{
  return *(undefined2 *)(DAT_803ca852 * 0x98 + param_1 * 2 + -0x7fc3573c);
}



// ==== 8008e534  zz_008e534_ ====

void zz_008e534_(undefined4 param_1)

{
  *(undefined4 *)(&DAT_803ca8d0 + DAT_803ca852 * 0x98) = param_1;
  return;
}



// ==== 8008e554  zz_008e554_ ====

undefined4 zz_008e554_(void)

{
  return *(undefined4 *)(&DAT_803ca8d0 + DAT_803ca852 * 0x98);
}



// ==== 8008e574  zz_008e574_ ====

void zz_008e574_(undefined4 param_1)

{
  *(undefined4 *)(&DAT_803ca8d4 + DAT_803ca852 * 0x98) = param_1;
  return;
}



// ==== 8008e594  zz_008e594_ ====

undefined4 zz_008e594_(void)

{
  return *(undefined4 *)(&DAT_803ca8d4 + DAT_803ca852 * 0x98);
}



// ==== 8008e5b4  zz_008e5b4_ ====

void zz_008e5b4_(int param_1,undefined1 param_2)

{
  *(undefined1 *)(DAT_803ca852 * 0x98 + param_1 + -0x7fc3577f) = param_2;
  return;
}



// ==== 8008e5d8  zz_008e5d8_ ====

int zz_008e5d8_(int param_1)

{
  return (int)*(char *)(DAT_803ca852 * 0x98 + param_1 + -0x7fc3577f);
}



// ==== 8008e600  zz_008e600_ ====

void zz_008e600_(undefined4 param_1)

{
  DAT_803ca858 = param_1;
  return;
}



// ==== 8008e610  zz_008e610_ ====

void zz_008e610_(undefined4 param_1)

{
  DAT_803ca854 = param_1;
  return;
}



// ==== 8008e620  zz_008e620_ ====

void zz_008e620_(undefined4 param_1)

{
  DAT_803ca85c = param_1;
  return;
}



// ==== 8008e630  zz_008e630_ ====

void zz_008e630_(undefined4 param_1)

{
  DAT_803ca860 = param_1;
  return;
}



// ==== 8008e640  zz_008e640_ ====

void zz_008e640_(int param_1,undefined1 param_2)

{
  (&DAT_803ca8d8)[param_1 * 0x98] = param_2;
  return;
}



// ==== 8008e658  zz_008e658_ ====

int zz_008e658_(int param_1)

{
  return (int)(char)(&DAT_803ca8d8)[param_1 * 0x98];
}



// ==== 8008e6a4  zz_008e6a4_ ====

undefined4 zz_008e6a4_(int *param_1,int *param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (DAT_803ca9d0 == -1) {
    uVar1 = 0xffffffff;
  }
  if (DAT_803ca9c8 == -1) {
    uVar1 = 0xffffffff;
  }
  if (param_1 != (int *)0x0) {
    *param_1 = DAT_803ca9d0;
  }
  if (param_2 != (int *)0x0) {
    *param_2 = DAT_803ca9c8;
  }
  return uVar1;
}



// ==== 8008e704  zz_008e704_ ====

uint zz_008e704_(int param_1,int param_2,int param_3,int param_4)

{
  byte bVar1;
  int iVar2;
  char cVar3;
  uint uVar4;
  byte *pbVar5;
  
  pbVar5 = (byte *)(param_1 + param_2);
  uVar4 = 0;
  if (param_4 == 1) {
    *(undefined1 *)(param_3 + param_1) = 0;
    ((undefined1 *)(param_3 + param_1))[1] = 0;
  }
  iVar2 = (param_3 - param_2) + 2;
  do {
    bVar1 = *pbVar5;
    pbVar5 = pbVar5 + 1;
    uVar4 = uVar4 | bVar1;
    for (cVar3 = '\0'; cVar3 < '\b'; cVar3 = cVar3 + '\x01') {
      uVar4 = uVar4 << 1;
      if ((uVar4 & 0x1000000) != 0) {
        uVar4 = uVar4 ^ 0x102100;
      }
    }
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  uVar4 = uVar4 >> 8 & 0xffff;
  if (param_4 == 1) {
    *(undefined1 *)(param_3 + param_1) = (char)(uVar4 >> 8);
    ((undefined1 *)(param_3 + param_1))[1] = (char)uVar4;
  }
  return uVar4;
}


