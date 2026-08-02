import {
  TITLE_INTRO_PROP_MOTION_ROWS,
  TITLE_INTRO_PROP_SCALAR_CONSTANTS,
  TITLE_INTRO_PROP_WOBBLE_FRAMES,
  TITLE_INTRO_WIDGET_DESCRIPTORS,
} from "../titleIntroScript.generated.js";

/** One GameCube BAM16 turn is 65536 units. */
export const BAM16_TO_RADIANS = (Math.PI * 2) / 0x10000;

export interface TitlePropFrame {
  readonly index: number;
  readonly modelId: number;
  readonly updateKind: number;
  readonly variant: number;
  readonly visible: boolean;
  readonly destroyed: boolean;
  readonly yOffset: number;
  readonly yawRadians: number;
  readonly opacity: number;
}

export interface TitlePropController {
  readonly frames: readonly TitlePropFrame[];
  tick(sceneStep: number): readonly number[];
}

interface MutablePropFrame {
  index: number;
  modelId: number;
  updateKind: number;
  variant: number;
  visible: boolean;
  destroyed: boolean;
  yOffset: number;
  yawRadians: number;
  opacity: number;
  state: number;
  motionState: number;
  waitFrames: number;
  velocity: number;
  acceleration: number;
  accelerationStep: number;
  terminalVelocity: number;
  angularVelocityBam: number;
  angularAccelerationBam: number;
}

function wrapI16(value: number): number {
  return (value << 16) >> 16;
}

/**
 * Browser port of the title prop task cluster at 0x801c84a8..0x801c8e04.
 *
 * The descriptor and motion rows are generated directly from GG4E boot.dol. The
 * controller intentionally exposes only render state: object allocation, HSD JObj
 * callbacks, and SE dispatch remain renderer/sound-system boundaries.
 */
export function createTitlePropController(): TitlePropController {
  const frames: MutablePropFrame[] = TITLE_INTRO_WIDGET_DESCRIPTORS
    .filter((descriptor) => descriptor.modelId >= 0)
    .map((descriptor) => {
      const row = TITLE_INTRO_PROP_MOTION_ROWS[descriptor.variant];
      return {
        index: descriptor.index,
        modelId: descriptor.modelId,
        updateKind: descriptor.updateKind,
        variant: descriptor.variant,
        visible: descriptor.updateKind !== 1,
        destroyed: false,
        yOffset: 0,
        yawRadians: 0,
        opacity: descriptor.updateKind === 2 ? TITLE_INTRO_PROP_SCALAR_CONSTANTS.overlayInitialOpacity : 1,
        state: 0,
        motionState: 0,
        waitFrames: row?.waitFrames ?? 0,
        velocity: row?.velocity ?? 0,
        acceleration: row?.acceleration ?? 0,
        accelerationStep: row?.accelerationStep ?? 0,
        terminalVelocity: row?.terminalVelocity ?? 0,
        angularVelocityBam: row?.angularVelocityBam ?? 0,
        angularAccelerationBam: row?.angularAccelerationBam ?? 0,
      };
    });

  function tickFallingProp(prop: MutablePropFrame, sceneStep: number, sounds: number[]): void {
    const row = TITLE_INTRO_PROP_MOTION_ROWS[prop.variant];
    if (!row) return;

    if (prop.state === 0) {
      if (sceneStep > 8) {
        prop.waitFrames = wrapI16(prop.waitFrames - 1);
        if (prop.waitFrames < 1) {
          prop.state = 1;
          prop.visible = true;
        }
      }
    } else if (prop.state === 1) {
      prop.velocity = Math.fround(prop.velocity + prop.acceleration);
      prop.acceleration = Math.fround(prop.acceleration + prop.accelerationStep);
      if (prop.velocity <= prop.terminalVelocity) {
        prop.state = 2;
        prop.velocity = row.terminalVelocity;
        if (row.soundId >= 0) sounds.push(row.soundId);
      }
    } else if (prop.state === 2) {
      if (prop.variant < 4) {
        if (prop.motionState === 0) {
          prop.motionState = 1;
          prop.angularVelocityBam = 0;
        } else if (prop.motionState === 1 && sceneStep >= 10) {
          if (prop.variant === 0) sounds.push(0x017a);
          prop.motionState = 2;
          prop.waitFrames = 0x1e;
          prop.acceleration = Math.fround(-(prop.velocity / prop.waitFrames));
          prop.angularAccelerationBam = wrapI16(Math.trunc(0x20000 / prop.waitFrames));
        } else if (prop.motionState === 2) {
          prop.velocity = Math.fround(prop.velocity + prop.acceleration);
          prop.angularVelocityBam = wrapI16(
            prop.angularVelocityBam - prop.angularAccelerationBam,
          );
          prop.waitFrames = wrapI16(prop.waitFrames - 1);
          if (prop.waitFrames < 1) prop.motionState = 3;
        } else if (prop.motionState === 3) {
          prop.velocity = TITLE_INTRO_PROP_SCALAR_CONSTANTS.zero;
          prop.angularVelocityBam = 0;
          prop.angularAccelerationBam = 0;
          prop.yawRadians = 0;
          prop.state = 3;
        }
      } else {
        if (prop.motionState === 0) {
          prop.motionState = 1;
          prop.waitFrames = 0;
        }
        if (prop.motionState === 1) {
          prop.velocity = TITLE_INTRO_PROP_WOBBLE_FRAMES[prop.waitFrames] ?? 0;
          prop.waitFrames = wrapI16(prop.waitFrames + 1);
          if (prop.waitFrames >= TITLE_INTRO_PROP_WOBBLE_FRAMES.length) prop.state = 3;
        }
      }
    }

    // FUN_801c8c54 is the model callback: it applies the current linear and angular
    // velocities only while the HSD object is visible.
    if (prop.visible && !prop.destroyed) {
      prop.yOffset = Math.fround(prop.yOffset + prop.velocity);
      prop.yawRadians += prop.angularVelocityBam * BAM16_TO_RADIANS;
    }
  }

  function tick(sceneStep: number): readonly number[] {
    const sounds: number[] = [];
    for (const prop of frames) {
      if (prop.destroyed) continue;
      if (prop.updateKind === 0) {
        if (prop.state === 0 && sceneStep > 1) prop.state = 1;
        else if (prop.state === 1 && sceneStep !== 2) {
          prop.destroyed = true;
          prop.visible = false;
        }
      } else if (prop.updateKind === 1) {
        tickFallingProp(prop, sceneStep, sounds);
      } else if (prop.updateKind === 2) {
        if (prop.state === 0 && sceneStep > 1) prop.state = 1;
        else if (prop.state === 1) {
          prop.opacity = Math.fround(
            prop.opacity - TITLE_INTRO_PROP_SCALAR_CONSTANTS.overlayOpacityStep,
          );
          if (prop.opacity <= TITLE_INTRO_PROP_SCALAR_CONSTANTS.zero) {
            prop.opacity = TITLE_INTRO_PROP_SCALAR_CONSTANTS.zero;
            prop.destroyed = true;
            prop.visible = false;
          }
        }
      }
    }
    return sounds;
  }

  return { frames, tick };
}
