// mot.ts — MOT animation (motion) container parser.
// Status: PARTIAL upstream (NeoGF mottool parses the CONTAINER ONLY — no bones/keyframes).
// Big-endian. Container layout solved; keyframe/bone-track decode is unsolved and must be
// correlated with the model skeleton once mdl-arc is cracked. Export target: glTF animation.
// TODO: parse container (port mottool), then reverse keyframe tracks -> AnimationClip data.
export {};
