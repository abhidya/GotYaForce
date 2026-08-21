/**
 * Stateful rising-edge detector for controls that can remain held while one
 * game screen synchronously hands off to another.
 */
export interface InputEdgeLatch {
  /** Mark the current physical state as already observed without firing it. */
  consume: (pressed: boolean) => void;
  /** Return true once for each released -> pressed transition. */
  poll: (pressed: boolean) => boolean;
}

export function createInputEdgeLatch(initialPressed = false): InputEdgeLatch {
  let pressedLast = initialPressed;

  return {
    consume(pressed) {
      pressedLast = pressed;
    },
    poll(pressed) {
      const rising = pressed && !pressedLast;
      pressedLast = pressed;
      return rising;
    },
  };
}
