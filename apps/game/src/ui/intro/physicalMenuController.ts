import {
  PHYSICAL_MENU_DIRECTION_TABLE,
  PHYSICAL_MENU_MODE_DISPATCH,
} from "../titleIntroScript.generated.js";

export type PhysicalMenuDirection = "up" | "down" | "left" | "right";

export interface PhysicalMenuController {
  readonly index: number;
  readonly dispatchAddress: string;
  setIndex(index: number): void;
  move(direction: PhysicalMenuDirection): number;
}

/**
 * Input/selection port of the physical menu controller at 0x800bf8d4.
 *
 * FUN_800c0454 converts a direction into one of four columns in DAT_80301cf0;
 * global mode 3 then dispatches the selected index through PTR_FUN_802cfdc4.
 */
export function createPhysicalMenuController(initialIndex = 0): PhysicalMenuController {
  let index = initialIndex;

  function assertIndex(value: number): void {
    if (!Number.isInteger(value) || value < 0 || value >= PHYSICAL_MENU_DIRECTION_TABLE.length) {
      throw new RangeError(`physical menu index ${value} is outside the source table`);
    }
  }

  assertIndex(index);
  return {
    get index() {
      return index;
    },
    get dispatchAddress() {
      return PHYSICAL_MENU_MODE_DISPATCH[index]!.address;
    },
    setIndex(nextIndex) {
      assertIndex(nextIndex);
      index = nextIndex;
    },
    move(direction) {
      const row = PHYSICAL_MENU_DIRECTION_TABLE[index]!;
      index = row[direction];
      return index;
    },
  };
}
