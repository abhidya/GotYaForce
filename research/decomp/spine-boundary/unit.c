#include "gnt4_shim.h"

// ==== 800527d8  zz_00527d8_ ====

void zz_00527d8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
                int param_11,undefined *param_12,undefined4 param_13,undefined *param_14,
                uint param_15,int param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 uVar2;
  undefined8 uVar3;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  
  uVar3 = zz_002a3e4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                      param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  zz_002a638_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  do {
    zz_010d450_();
    zz_008c088_();
    zz_0080278_();
    uVar3 = zz_0052838_();
    uVar3 = zz_00e9994_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int)((ulonglong)uVar3 >> 0x20),(int)uVar3,param_11,param_12,param_13,
                        param_14,param_15,param_16);
    uVar2 = extraout_r4;
    DAT_80436190 = zz_008dbe0_();
    zz_000a004_();
    iVar1 = zz_0018b10_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    zz_00efda8_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,uVar2,param_11,
                param_12,param_13,param_14,param_15,param_16);
    zz_002a4b0_();
    dispatch_global_menu_mode();
    zz_00528b4_();
    zz_00802a8_();
    zz_008c2dc_();
    zz_008c344_();
    uVar3 = zz_0027c34_();
    zz_002a4d4_(extraout_f1_00,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                (int)((ulonglong)uVar3 >> 0x20),(int)uVar3,param_11,param_12,param_13,param_14,
                param_15,param_16);
  } while( true );
}
