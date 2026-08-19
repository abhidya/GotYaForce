#include "gnt4_shim.h"

/* stage-2 generated prototypes */
void collision_hit_pair_pass_active_vs_borgs(void);
void collision_hit_pair_pass_active_vs_secondary(void);
void collision_hit_pair_pass_object_lists(void);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0003.c 7026-7164 ==== */
// ==== 8002d7c4  collision_hit_pair_pass_active_vs_borgs ====

/* WARNING: Removing unreachable block (ram,0x8002db3c) */
/* WARNING: Removing unreachable block (ram,0x8002d7d4) */

void collision_hit_pair_pass_active_vs_borgs(void)

{
  undefined4 *puVar1;
  ushort uVar2;
  bool bVar3;
  bool bVar4;
  int *piVar5;
  int *piVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int unaff_r31;
  double dVar18;
  double in_f31;
  float afStack_68 [3];
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  
  piVar5 = &DAT_803c477c;
  for (iVar12 = 0; iVar12 < (int)(uint)DAT_80436250; iVar12 = iVar12 + 1) {
    iVar17 = *piVar5;
    bVar3 = true;
    bVar4 = false;
    iVar13 = *(int *)(iVar17 + 0x20);
    iVar14 = *(int *)(iVar17 + 0x2c) + (uint)*(byte *)(iVar17 + 0x11) * 0x18;
    uVar2 = *(ushort *)(iVar14 + 0x10);
    if ((uVar2 & 0x800) == 0) {
      if (*(int *)(iVar17 + 0x58) == 2) {
        if ((uVar2 & 1) == 0) {
          bVar3 = false;
          in_f31 = (double)FLOAT_80436f98;
        }
        else {
          bVar3 = true;
        }
      }
      piVar6 = &DAT_803c2f7c;
      for (iVar15 = 0; iVar15 < (int)(uint)DAT_80436248; iVar15 = iVar15 + 1) {
        iVar16 = *piVar6;
        if ((((*(ushort *)(*(int *)(iVar17 + 0x28) + 2) & 0x4000) == 0) ||
            ((*(ushort *)(*(int *)(iVar16 + 0x28) + 2) & 0x2000) != 0)) &&
           (iVar8 = zz_002fd7c_(iVar17,iVar16,0x40), iVar8 != 0)) {
          iVar9 = *(int *)(iVar16 + 0x24);
          iVar8 = *(int *)(iVar17 + 0x24);
          if (((((*(char *)(iVar9 + 0x83) != '\0') || (*(char *)(iVar8 + 0x83) != '\0')) ||
               (*(char *)(iVar9 + 0x88) != *(char *)(iVar8 + 0x88))) ||
              ((((*(char *)(iVar9 + 0x1db) == '\0' || (*(char *)(iVar8 + 1000) == '\x0e')) ||
                (*(int *)(iVar9 + 0x1e4) != iVar8)) &&
               (((*(char *)(iVar8 + 0x1db) == '\0' || (*(char *)(iVar9 + 1000) == '\x0e')) ||
                (*(int *)(iVar8 + 0x1e4) != iVar9)))))) &&
             ((iVar8 = zz_0039f6c_(iVar17 + 0x58,iVar16 + 0x58), iVar8 != 0 &&
              (((*(ushort *)(iVar14 + 0x12) & 0x10) == 0 ||
               (*(char *)(iVar13 + 0x88) != *(char *)(*(int *)(iVar16 + 0x20) + 0x88))))))) {
            puVar10 = (undefined4 *)(iVar17 + 0x54);
            puVar11 = (undefined4 *)0x803b04cc;
            iVar8 = 0x2d;
            do {
              puVar1 = puVar10 + 1;
              puVar10 = puVar10 + 2;
              uVar7 = *puVar10;
              puVar11[1] = *puVar1;
              puVar11 = puVar11 + 2;
              *puVar11 = uVar7;
              iVar8 = iVar8 + -1;
            } while (iVar8 != 0);
            puVar10 = (undefined4 *)(iVar16 + 0x54);
            puVar11 = (undefined4 *)&DAT_803b0364;
            iVar8 = 0x2d;
            do {
              puVar1 = puVar10 + 1;
              puVar10 = puVar10 + 2;
              uVar7 = *puVar10;
              puVar11[1] = *puVar1;
              puVar11 = puVar11 + 2;
              *puVar11 = uVar7;
              iVar8 = iVar8 + -1;
            } while (iVar8 != 0);
            zz_0030348_(&DAT_803b04d0,&DAT_803b0368,*(int *)(iVar17 + 0x58),*(int *)(iVar16 + 0x58))
            ;
            iVar8 = zz_0030490_(&DAT_803b04d0,&DAT_803b0368,
                                *(int *)(iVar17 + 0x58) << 3 | *(uint *)(iVar16 + 0x58));
            if (iVar8 != 0) {
              if (bVar3) {
                resolve_hitbox_target_effects_and_damage(iVar17,iVar16);
              }
              else {
                dVar18 = gnt4_PSVECSquareDistance_bl((float *)&DAT_803b0374,(float *)&DAT_803b0504);
                if (dVar18 <= in_f31) {
                  bVar4 = true;
                  local_5c = DAT_803b0720;
                  local_58 = DAT_803b0724;
                  local_54 = DAT_803b0728;
                  unaff_r31 = iVar16;
                  in_f31 = dVar18;
                }
              }
            }
          }
        }
        piVar6 = piVar6 + 1;
      }
      if ((!bVar3) && (bVar4)) {
        DAT_803b0720 = local_5c;
        DAT_803b0724 = local_58;
        DAT_803b0728 = local_54;
        gnt4_PSVECSubtract_bl((float *)&DAT_803b0720,(float *)(iVar17 + 0x98),afStack_68);
        dVar18 = gnt4_PSVECSquareMag_bl(afStack_68);
        if ((double)FLOAT_80436f68 < dVar18) {
          iVar13 = *(int *)(iVar17 + 0x20);
          gnt4_PSVECAdd_bl((float *)(iVar17 + 0x98),afStack_68,(float *)(iVar17 + 0x98));
          gnt4_PSVECAdd_bl((float *)(iVar13 + 0x20),afStack_68,(float *)(iVar13 + 0x20));
          gnt4_PSQUATScale_bl((double)FLOAT_80436f7c,afStack_68,afStack_68);
          gnt4_PSVECAdd_bl((float *)(iVar17 + 100),afStack_68,(float *)(iVar17 + 100));
          if (*(code **)(iVar13 + 0x100) != (code *)0x0) {
            (**(code **)(iVar13 + 0x100))(iVar13);
          }
        }
        resolve_hitbox_target_effects_and_damage(iVar17,unaff_r31);
      }
    }
    piVar5 = piVar5 + 1;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0003.c 7168-7306 ==== */
// ==== 8002db58  collision_hit_pair_pass_active_vs_secondary ====

/* WARNING: Removing unreachable block (ram,0x8002deec) */
/* WARNING: Removing unreachable block (ram,0x8002db68) */

void collision_hit_pair_pass_active_vs_secondary(void)

{
  undefined4 *puVar1;
  ushort uVar2;
  ushort uVar3;
  bool bVar4;
  bool bVar5;
  int *piVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int *piVar17;
  int unaff_r31;
  double dVar18;
  double in_f31;
  float afStack_68 [3];
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  
  piVar6 = &DAT_803c477c;
  for (iVar14 = 0; iVar14 < (int)(uint)DAT_80436250; iVar14 = iVar14 + 1) {
    iVar16 = *piVar6;
    bVar4 = true;
    bVar5 = false;
    iVar12 = *(int *)(iVar16 + 0x2c) + (uint)*(byte *)(iVar16 + 0x11) * 0x18;
    if (*(int *)(iVar16 + 0x58) == 2) {
      if ((*(ushort *)(iVar12 + 0x10) & 1) == 0) {
        bVar4 = false;
        in_f31 = (double)FLOAT_80436f98;
      }
      else {
        bVar4 = true;
      }
    }
    piVar17 = &DAT_803c417c;
    for (iVar13 = 0; iVar13 < (int)(uint)DAT_8043624e; iVar13 = iVar13 + 1) {
      iVar15 = *piVar17;
      uVar2 = *(ushort *)(*(int *)(iVar15 + 0x28) + 2);
      if ((((((uVar2 & 0x800) == 0) || (((int)*(short *)(iVar12 + 0x12) & 0x8000U) != 0)) &&
           ((uVar3 = *(ushort *)(*(int *)(iVar16 + 0x28) + 2), (uVar3 & 0x1000) != 0 ||
            ((uVar2 & 0x2000) == 0)))) &&
          ((((uVar3 & 0x4000) == 0 || ((uVar2 & 0x2000) != 0)) &&
           ((*(byte *)(*(int *)(iVar15 + 0x20) + 0x1da) & 2) == 0)))) &&
         (iVar8 = zz_002fd7c_(iVar16,iVar15,2), iVar8 != 0)) {
        iVar9 = *(int *)(iVar15 + 0x24);
        iVar8 = *(int *)(iVar16 + 0x24);
        if (((((*(char *)(iVar9 + 0x83) != '\0') || (*(char *)(iVar8 + 0x83) != '\0')) ||
             (*(char *)(iVar9 + 0x88) != *(char *)(iVar8 + 0x88))) ||
            ((((*(char *)(iVar9 + 0x1db) == '\0' || (*(char *)(iVar8 + 1000) == '\x0e')) ||
              (*(int *)(iVar9 + 0x1e4) != iVar8)) &&
             (((*(char *)(iVar8 + 0x1db) == '\0' || (*(char *)(iVar9 + 1000) == '\x0e')) ||
              (*(int *)(iVar8 + 0x1e4) != iVar9)))))) &&
           (iVar8 = zz_0039f6c_(iVar16 + 0x58,iVar15 + 0x58), iVar8 != 0)) {
          puVar10 = (undefined4 *)(iVar16 + 0x54);
          puVar11 = (undefined4 *)0x803b04cc;
          iVar8 = 0x2d;
          do {
            puVar1 = puVar10 + 1;
            puVar10 = puVar10 + 2;
            uVar7 = *puVar10;
            puVar11[1] = *puVar1;
            puVar11 = puVar11 + 2;
            *puVar11 = uVar7;
            iVar8 = iVar8 + -1;
          } while (iVar8 != 0);
          puVar10 = (undefined4 *)(iVar15 + 0x54);
          puVar11 = (undefined4 *)&DAT_803b0364;
          iVar8 = 0x2d;
          do {
            puVar1 = puVar10 + 1;
            puVar10 = puVar10 + 2;
            uVar7 = *puVar10;
            puVar11[1] = *puVar1;
            puVar11 = puVar11 + 2;
            *puVar11 = uVar7;
            iVar8 = iVar8 + -1;
          } while (iVar8 != 0);
          zz_0030348_(&DAT_803b04d0,&DAT_803b0368,*(int *)(iVar16 + 0x58),*(int *)(iVar15 + 0x58));
          iVar8 = zz_0030490_(&DAT_803b04d0,&DAT_803b0368,
                              *(int *)(iVar16 + 0x58) << 3 | *(uint *)(iVar15 + 0x58));
          if (iVar8 != 0) {
            if (bVar4) {
              resolve_hitbox_target_effects_and_damage(iVar16,iVar15);
            }
            else {
              dVar18 = gnt4_PSVECSquareDistance_bl((float *)&DAT_803b0374,(float *)&DAT_803b0504);
              if (dVar18 <= in_f31) {
                bVar5 = true;
                local_5c = DAT_803b0720;
                local_58 = DAT_803b0724;
                local_54 = DAT_803b0728;
                unaff_r31 = iVar15;
                in_f31 = dVar18;
              }
            }
          }
        }
      }
      piVar17 = piVar17 + 1;
    }
    if ((!bVar4) && (bVar5)) {
      DAT_803b0720 = local_5c;
      DAT_803b0724 = local_58;
      DAT_803b0728 = local_54;
      if ((*(ushort *)(*(int *)(unaff_r31 + 0x2c) + (uint)*(byte *)(unaff_r31 + 0x11) * 0x18 + 0x12)
          & 0x3c0) == 0) {
        gnt4_PSVECSubtract_bl((float *)&DAT_803b0720,(float *)(iVar16 + 0x98),afStack_68);
        dVar18 = gnt4_PSVECSquareMag_bl(afStack_68);
        if ((double)FLOAT_80436f68 < dVar18) {
          iVar12 = *(int *)(iVar16 + 0x20);
          gnt4_PSVECAdd_bl((float *)(iVar16 + 0x98),afStack_68,(float *)(iVar16 + 0x98));
          gnt4_PSVECAdd_bl((float *)(iVar12 + 0x20),afStack_68,(float *)(iVar12 + 0x20));
          gnt4_PSQUATScale_bl((double)FLOAT_80436f7c,afStack_68,afStack_68);
          gnt4_PSVECAdd_bl((float *)(iVar16 + 100),afStack_68,(float *)(iVar16 + 100));
          if (*(code **)(iVar12 + 0x100) != (code *)0x0) {
            (**(code **)(iVar12 + 0x100))(iVar12);
          }
        }
      }
      resolve_hitbox_target_effects_and_damage(iVar16,unaff_r31);
    }
    piVar6 = piVar6 + 1;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0003.c 7310-7426 ==== */
// ==== 8002df08  collision_hit_pair_pass_object_lists ====

/* WARNING: Removing unreachable block (ram,0x8002e1ac) */
/* WARNING: Removing unreachable block (ram,0x8002df18) */

void collision_hit_pair_pass_object_lists(void)

{
  undefined4 *puVar1;
  bool bVar2;
  bool bVar3;
  int *piVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int *piVar13;
  int unaff_r31;
  double dVar14;
  double in_f31;
  float afStack_58 [3];
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  
  piVar4 = &DAT_803c177c;
  for (iVar10 = 0; iVar10 < (int)(uint)DAT_80436240; iVar10 = iVar10 + 1) {
    iVar12 = *piVar4;
    bVar2 = true;
    bVar3 = false;
    if (*(int *)(iVar12 + 0x58) == 2) {
      if ((*(ushort *)(*(int *)(iVar12 + 0x2c) + (uint)*(byte *)(iVar12 + 0x11) * 0x18 + 0x10) & 1)
          == 0) {
        bVar2 = false;
        in_f31 = (double)FLOAT_80436f98;
      }
      else {
        bVar2 = true;
      }
    }
    piVar13 = &DAT_803c117c;
    for (iVar9 = 0; iVar9 < (int)(uint)DAT_8043623e; iVar9 = iVar9 + 1) {
      iVar11 = *piVar13;
      iVar6 = zz_002fd7c_(iVar12,iVar11,2);
      if ((iVar6 != 0) && (iVar6 = zz_0039f6c_(iVar12 + 0x58,iVar11 + 0x58), iVar6 != 0)) {
        puVar7 = (undefined4 *)(iVar12 + 0x54);
        puVar8 = (undefined4 *)0x803b04cc;
        iVar6 = 0x2d;
        do {
          puVar1 = puVar7 + 1;
          puVar7 = puVar7 + 2;
          uVar5 = *puVar7;
          puVar8[1] = *puVar1;
          puVar8 = puVar8 + 2;
          *puVar8 = uVar5;
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
        puVar7 = (undefined4 *)(iVar11 + 0x54);
        puVar8 = (undefined4 *)&DAT_803b0364;
        iVar6 = 0x2d;
        do {
          puVar1 = puVar7 + 1;
          puVar7 = puVar7 + 2;
          uVar5 = *puVar7;
          puVar8[1] = *puVar1;
          puVar8 = puVar8 + 2;
          *puVar8 = uVar5;
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
        zz_0030348_(&DAT_803b04d0,&DAT_803b0368,*(int *)(iVar12 + 0x58),*(int *)(iVar11 + 0x58));
        iVar6 = zz_0030490_(&DAT_803b04d0,&DAT_803b0368,
                            *(int *)(iVar12 + 0x58) << 3 | *(uint *)(iVar11 + 0x58));
        if (iVar6 != 0) {
          if (bVar2) {
            resolve_hitbox_target_effects_and_damage(iVar12,iVar11);
          }
          else {
            dVar14 = gnt4_PSVECSquareDistance_bl((float *)&DAT_803b0374,(float *)&DAT_803b0504);
            if (dVar14 <= in_f31) {
              bVar3 = true;
              local_4c = DAT_803b0720;
              local_48 = DAT_803b0724;
              local_44 = DAT_803b0728;
              unaff_r31 = iVar11;
              in_f31 = dVar14;
            }
          }
        }
      }
      piVar13 = piVar13 + 1;
    }
    if ((!bVar2) && (bVar3)) {
      DAT_803b0720 = local_4c;
      DAT_803b0724 = local_48;
      DAT_803b0728 = local_44;
      gnt4_PSVECSubtract_bl((float *)&DAT_803b0720,(float *)(iVar12 + 0x98),afStack_58);
      dVar14 = gnt4_PSVECSquareMag_bl(afStack_58);
      if ((double)FLOAT_80436f68 < dVar14) {
        iVar9 = *(int *)(iVar12 + 0x20);
        gnt4_PSVECAdd_bl((float *)(iVar12 + 0x98),afStack_58,(float *)(iVar12 + 0x98));
        gnt4_PSVECAdd_bl((float *)(iVar9 + 0x20),afStack_58,(float *)(iVar9 + 0x20));
        gnt4_PSQUATScale_bl((double)FLOAT_80436f7c,afStack_58,afStack_58);
        gnt4_PSVECAdd_bl((float *)(iVar12 + 100),afStack_58,(float *)(iVar12 + 100));
        if (*(code **)(iVar9 + 0x100) != (code *)0x0) {
          (**(code **)(iVar9 + 0x100))(iVar9);
        }
      }
      resolve_hitbox_target_effects_and_damage(iVar12,unaff_r31);
    }
    piVar4 = piVar4 + 1;
  }
  return;
}
