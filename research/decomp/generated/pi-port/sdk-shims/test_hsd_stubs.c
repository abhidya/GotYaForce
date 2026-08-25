#include "gnt4_sdk_shim.h"
#include <stdio.h>

int main(void)
{
  if (gnt4_HSD_CObjGetFov_bl(0) != 0) {
    printf("FAIL: CObjGetFov");
    return 1;
  }

  if ((undefined8)gnt4_HSD_DObjClearFlags_bl(0, 0) != (undefined8)0) {
    printf("FAIL: DObjClearFlags");
    return 1;
  }
  if ((undefined8)gnt4_HSD_JObjReqAnimAll((int *)0, 1.0) != (undefined8)0) {
    printf("FAIL: JObjReqAnimAll");
    return 1;
  }

  if (gnt4_HSD_JObjGetDObj(0) != 0) {
    printf("FAIL: JObjGetDObj");
    return 1;
  }
  if (gnt4_HSD_JObjLoadJoint(0, 0, 0, 0, 0, 0, 0, 0, (int *)0, 0, (char *)0, 0, 0, 0, 0, 0) != (int *)0) {
    printf("FAIL: JObjLoadJoint");
    return 1;
  }

  gnt4_HSD_CObjSetFar_bl(0.0, 0);
  gnt4_HSD_CObjSetNear_bl(0.0, 0);
  gnt4_HSD_LObjRemoveAll_bl(0);
  gnt4_HSD_MObjSetFlags_bl(0, 0);
  gnt4_HSD_JObjAddAnimAll();

  printf("HSD_TESTS_PASS\n");
  return 0;
}
