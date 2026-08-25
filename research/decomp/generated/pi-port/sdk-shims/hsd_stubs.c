#include "gnt4_sdk_shim.h"

void gnt4_HSD_CObjGetEyePosition_bl(void)
{
  /* TODO: HSD semantics deferred - stub only. */
}

int gnt4_HSD_CObjGetFov_bl(int obj_ptr)
{
  /* TODO: HSD semantics deferred - stub only. */
  return 0;
}

void gnt4_HSD_CObjGetInterest_bl(void)
{
  /* TODO: HSD semantics deferred - stub only. */
}

int gnt4_HSD_CObjGetUpVector_bl(void)
{
  /* TODO: HSD semantics deferred - stub only. */
  return 0;
}

void gnt4_HSD_CObjGetViewingMtx_bl(void)
{
  /* TODO: HSD semantics deferred - stub only. */
}

void gnt4_HSD_CObjSetFar_bl(double param_1, int param_2)
{
  /* TODO: HSD semantics deferred - stub only. */
}

void gnt4_HSD_CObjSetNear_bl(double param_1, int param_2)
{
  /* TODO: HSD semantics deferred - stub only. */
}

void gnt4_HSD_CObjSetOrtho_bl(double param_1, double param_2, double param_3, double param_4, int param_5)
{
  /* TODO: HSD semantics deferred - stub only. */
}

void gnt4_HSD_CObjSetPerspective_bl(double param_1, double param_2, int param_3)
{
  /* TODO: HSD semantics deferred - stub only. */
}

void gnt4_HSD_CObjSetScissorx4_bl(int param_1, short param_2, short param_3, short param_4, short param_5)
{
  /* TODO: HSD semantics deferred - stub only. */
}

void gnt4_HSD_CObjSetViewportfx4_bl(double param_1, double param_2, double param_3, double param_4, int param_5)
{
  /* TODO: HSD semantics deferred - stub only. */
}

undefined8 gnt4_HSD_DObjClearFlags_bl(int obj, int flags)
{
  /* TODO: HSD semantics deferred - stub only. */
  return (undefined8)0;
}

void gnt4_HSD_DObjSetFlags_bl(int obj, int flags)
{
  /* TODO: HSD semantics deferred - stub only. */
}

int gnt4_HSD_FogLoadDesc_bl(undefined8 p1, double p2, double p3, double p4, double p5, double p6, double p7, double p8, undefined4 *desc, undefined4 extra_r4, void *param_11, undefined4 p12, undefined4 p13, undefined4 p14, undefined4 p15, undefined4 p16)
{
  /* TODO: HSD semantics deferred - stub only. */
  return 0;
}

void gnt4_HSD_JObjAddAnimAll(void)
{
  /* TODO: HSD semantics deferred - stub only. */
}

void gnt4_HSD_JObjAddChild(undefined8 p1, double p2, double p3, double p4, double p5, double p6, double p7, double p8, int p9, int p10, char *p11, undefined4 p12, undefined4 p13, undefined4 p14, undefined4 p15, undefined4 p16)
{
  /* TODO: HSD semantics deferred - stub only. */
}

void gnt4_HSD_JObjAnimAll(undefined8 p1, double p2, double p3, double p4, double p5, double p6, double p7, double p8, int *p9, undefined4 p10, float *p11, undefined4 p12, undefined4 p13, undefined4 p14, undefined4 p15, undefined4 p16)
{
  /* TODO: HSD semantics deferred - stub only. */
}

undefined8 gnt4_HSD_JObjClearFlags(undefined8 p1, double p2, double p3, double p4, double p5, double p6, double p7, double p8, int p9, uint p10, char *p11, undefined4 p12, undefined4 p13, undefined4 p14, undefined4 p15, undefined4 p16)
{
  /* TODO: HSD semantics deferred - stub only. */
  return (undefined8)0;
}

int gnt4_HSD_JObjGetDObj(int param_1)
{
  /* TODO: HSD semantics deferred - stub only. */
  return 0;
}

int * gnt4_HSD_JObjLoadJoint(undefined8 p1, double p2, double p3, double p4, double p5, double p6, double p7, double p8, int *p9, int p10, char *p11, undefined4 p12, undefined4 p13, undefined4 p14, undefined4 p15, undefined4 p16)
{
  /* TODO: HSD semantics deferred - stub only. */
  return (int *)0;
}

undefined8 gnt4_HSD_JObjSetFlags(undefined8 p1, double p2, double p3, double p4, double p5, double p6, double p7, double p8, int p9, uint p10, char *p11, undefined4 p12, undefined4 p13, undefined4 p14, undefined4 p15, undefined4 p16)
{
  /* TODO: HSD semantics deferred - stub only. */
  return (undefined8)0;
}

void gnt4_HSD_JObjSetupMatrixSub_bl(undefined8 p1, double p2, double p3, double p4, double p5, double p6, double p7, double p8, int *p9, uint p10, void *p11, undefined4 p12, undefined4 p13, undefined4 p14, undefined4 p15, undefined4 p16)
{
  /* TODO: HSD semantics deferred - stub only. */
}

int gnt4_HSD_LObjLoadDesc_bl(undefined8 p1, double p2, double p3, double p4, double p5, double p6, double p7, double p8, int *desc, undefined4 extra_r4, int param_11, undefined4 p12, undefined4 p13, undefined4 p14, undefined4 p15, undefined4 p16)
{
  /* TODO: HSD semantics deferred - stub only. */
  return 0;
}

void gnt4_HSD_LObjRemoveAll_bl(int obj_ptr)
{
  /* TODO: HSD semantics deferred - stub only. */
}

undefined8 gnt4_HSD_MObjCompileTev_bl(undefined8 p1, double p2, double p3, double p4, double p5, double p6, double p7, double p8, int *p9, undefined4 p10, char *p11, byte *p12, undefined4 p13, undefined4 p14, undefined4 p15, undefined4 p16)
{
  /* TODO: HSD semantics deferred - stub only. */
  return (undefined8)0;
}

void gnt4_HSD_MObjSetFlags_bl(int obj, uint flags)
{
  /* TODO: HSD semantics deferred - stub only. */
}

undefined8 gnt4_HSD_JObjReqAnimAll(int *jobj, double frame)
{
  /* TODO: HSD semantics deferred - stub only. */
  return (undefined8)0;
}

/* TODO: signature UNSETTLED between corpus units (void* vs int* / char* vs float*).
 * Deliberately declared with empty parens; DO NOT give this a signature until a
 * real SDK reference settles it. No semantics implemented. */
void gnt4_HSD_JObjSetMtxDirtySub_bl() {}

/* TODO: signature UNSETTLED between corpus units. Same rule as above. */
void gnt4___assert_bl() {}
