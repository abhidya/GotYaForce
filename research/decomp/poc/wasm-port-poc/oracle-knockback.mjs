// packages/combat/src/data/knockbackStrength.json
var knockbackStrength_default = {
  provenance: {
    bootDolPath: "user-data/GG4E/disc/sys/boot.dol",
    bootDolSha1: "91b32873d62ae25c0a9b08d665e1e8c19ae38a5f",
    generatedBy: "gen-knockback-strength-tables.mjs",
    evidence: "zz_005ec20_ @0x8005ec20 reads *(float*)(&DAT_802dd8a0 + strength*4) (chunk_0007.c:5568); FUN_8005ed38 @0x8005ed38 reads *(float*)(&DAT_802d3664 + strength*4) (chunk_0007.c:5630); strength = actor+0x702 (the hit record +0x0d severity byte, clamped 0..15).",
    addresses: {
      horizontalLaunch: "0x802dd8a0",
      velocityMagnitude: "0x802d3664"
    },
    entryCount: 16,
    expectedForm: {
      horizontalLaunch: "strength * 7.0  (0,7,14,...,105)",
      velocityMagnitude: "(strength + 1) * 8.0  (8,16,...,128)"
    }
  },
  horizontalLaunch: [
    0,
    7,
    14,
    21,
    28,
    35,
    42,
    49,
    56,
    63,
    70,
    77,
    84,
    91,
    98,
    105
  ],
  velocityMagnitude: [
    8,
    16,
    24,
    32,
    40,
    48,
    56,
    64,
    72,
    80,
    88,
    96,
    104,
    112,
    120,
    128
  ]
};

// packages/combat/src/damage/sourceKnockback.ts
var BAM16_PER_RADIAN = 10430.3779296875;
var DEGENERATE_MAG_SQ_THRESHOLD = 0.009999999776482582;
var FALLBACK_DIR_X = 0;
var FALLBACK_DIR_Y = 0;
var FALLBACK_DIR_Z = -1;
var BAM16_WRAP = 65536;
var STRENGTH = knockbackStrength_default;
var STRENGTH_TABLE_MAX = 15;
function computeKnockbackLaunchDirection(attacker, defender, ctx) {
  const v = resolveModeVector(attacker, defender, ctx.mode);
  let { x, y, z } = v;
  if (Math.abs(x * x + y * y + z * z) < DEGENERATE_MAG_SQ_THRESHOLD) {
    x = FALLBACK_DIR_X;
    y = FALLBACK_DIR_Y;
    z = FALLBACK_DIR_Z;
  }
  const yawRaw = Math.trunc(Math.atan2(x, z) * BAM16_PER_RADIAN);
  const horizMagSq = Math.abs(x * x + z * z);
  const pitchRaw = Math.trunc(Math.atan2(y, horizMagSq) * BAM16_PER_RADIAN);
  let yaw = yawRaw;
  let pitch = -pitchRaw;
  yaw += toSignedByte(ctx.trimYaw ?? 0) * -256;
  pitch += toSignedByte(ctx.trimPitch ?? 0) * -256;
  return { yaw: wrapBam16(yaw), pitch: wrapBam16(pitch) };
}
function computeKnockbackLaunchDirectionLinked(attackerLinkedPos, targetLinkedPos, ctx) {
  return vectorToKnockbackAngle(
    sub(targetLinkedPos, attackerLinkedPos),
    ctx.trimYaw,
    ctx.trimPitch
  );
}
function vectorToKnockbackAngle(v, trimYaw = 0, trimPitch = 0) {
  let { x, y, z } = v;
  if (Math.abs(x * x + y * y + z * z) < DEGENERATE_MAG_SQ_THRESHOLD) {
    x = FALLBACK_DIR_X;
    y = FALLBACK_DIR_Y;
    z = FALLBACK_DIR_Z;
  }
  const yawRaw = Math.trunc(Math.atan2(x, z) * BAM16_PER_RADIAN);
  const horizMagSq = Math.abs(x * x + z * z);
  const pitchRaw = Math.trunc(Math.atan2(y, horizMagSq) * BAM16_PER_RADIAN);
  const yaw = yawRaw + toSignedByte(trimYaw) * -256;
  const pitch = -pitchRaw + toSignedByte(trimPitch) * -256;
  return { yaw: wrapBam16(yaw), pitch: wrapBam16(pitch) };
}
function angleTrimByteToBam16(trimByte) {
  return toSignedByte(trimByte) * -256;
}
function resolveModeVector(attacker, defender, mode) {
  if (mode === 1) {
    return sub(defender.pos, attacker.pos);
  }
  if (mode === 0 || mode === 2) {
    return attacker.motion38 ?? { x: 0, y: 0, z: 0 };
  }
  if (mode === 4) {
    return attacker.storedAim8dc ?? attacker.muzzle11c ?? { x: 0, y: 0, z: 0 };
  }
  if (mode === 3) {
    return { x: 0, y: 0, z: 0 };
  }
  return { x: 0, y: 0, z: 0 };
}
function knockbackStrengthClamp(strength) {
  const s = Math.abs(Math.trunc(strength));
  return s > STRENGTH_TABLE_MAX ? STRENGTH_TABLE_MAX : s;
}
function launchVelocityMagnitude(strength, airborneBoost = false) {
  const boosted = Math.trunc(Math.abs(strength)) + (airborneBoost ? 2 : 0);
  return STRENGTH.velocityMagnitude[knockbackStrengthClamp(boosted)] ?? 8;
}
function groundHorizontalSpeed(strength, scaleRatio = 1) {
  const idx = knockbackStrengthClamp(strength);
  return scaleRatio * (STRENGTH.horizontalLaunch[idx] ?? 0);
}
var KNOCKBACK_STRENGTH_TABLES = Object.freeze({
  HORIZONTAL: STRENGTH.horizontalLaunch,
  VELOCITY: STRENGTH.velocityMagnitude
});
function sub(a, b) {
  return { x: a.x - b.x, y: a.y - b.y, z: a.z - b.z };
}
function wrapBam16(v) {
  let r = Math.trunc(v) % BAM16_WRAP;
  if (r >= 32768) r -= BAM16_WRAP;
  if (r < -32768) r += BAM16_WRAP;
  return r;
}
function toSignedByte(value) {
  const truncated = Math.trunc(value) & 255;
  return truncated >= 128 ? truncated - 256 : truncated;
}
function defaultSourceKnockbackActor(pos = { x: 0, y: 0, z: 0 }) {
  return { pos };
}
function defaultSourceKnockbackContext(mode = 1) {
  return { mode, trimYaw: 0, trimPitch: 0 };
}
function runSourceKnockbackSelfTests(assert) {
  assert(
    STRENGTH.horizontalLaunch.length === 16 && STRENGTH.horizontalLaunch[6] === 42,
    `DAT_802dd8a0[6] === 42 (s*7) \u2014 got ${STRENGTH.horizontalLaunch[6]}`
  );
  assert(
    STRENGTH.velocityMagnitude.length === 16 && STRENGTH.velocityMagnitude[6] === 56,
    `DAT_802d3664[6] === 56 ((s+1)*8) \u2014 got ${STRENGTH.velocityMagnitude[6]}`
  );
  assert(launchVelocityMagnitude(6) === 56, "launch velocity strength 6 === 56 (melee)");
  assert(launchVelocityMagnitude(4) === 40, "launch velocity strength 4 === 40 (shot)");
  assert(launchVelocityMagnitude(2) === 24, "launch velocity strength 2 === 24 (charge/special)");
  assert(launchVelocityMagnitude(0) === 8, "launch velocity strength 0 === 8 (min)");
  assert(groundHorizontalSpeed(6) === 42, "ground h-speed strength 6 === 42");
  assert(groundHorizontalSpeed(0) === 0, "ground h-speed strength 0 === 0");
  assert(launchVelocityMagnitude(-6) === 56, "negative strength abs'd \u2192 56");
  assert(launchVelocityMagnitude(99) === 128, "over-15 strength clamps to 15 \u2192 128");
  assert(launchVelocityMagnitude(0, true) === 24, "airborne +2 boost: strength 0 \u2192 idx 2 \u2192 24");
  assert(launchVelocityMagnitude(14, true) === 128, "airborne +2 clamps at 15 \u2192 128");
  const origin = defaultSourceKnockbackActor();
  const ahead = computeKnockbackLaunchDirection(origin, { pos: { x: 0, y: 0, z: 5 } }, { mode: 1 });
  assert(ahead.yaw === 0 && ahead.pitch === 0, `mode 1 +Z \u2192 yaw 0 pitch 0 (got ${JSON.stringify(ahead)})`);
  const right = computeKnockbackLaunchDirection(origin, { pos: { x: 5, y: 0, z: 0 } }, { mode: 1 });
  assert(right.yaw > 16128 && right.yaw < 16640, `mode 1 +X \u2192 yaw ~ +0x4000 (got 0x${right.yaw.toString(16)})`);
  const behind = computeKnockbackLaunchDirection(origin, { pos: { x: 0, y: 0, z: -5 } }, { mode: 1 });
  assert(Math.abs(behind.yaw) > 32512, `mode 1 -Z \u2192 yaw ~ \xB10x8000 (got 0x${behind.yaw.toString(16)})`);
  const swap = computeKnockbackLaunchDirection({ pos: { x: 5, y: 0, z: 0 } }, origin, { mode: 1 });
  assert(swap.yaw !== right.yaw, "swapped attacker/defender yields a different yaw (directional)");
  const degenerate = computeKnockbackLaunchDirection(origin, origin, { mode: 1 });
  assert(Math.abs(degenerate.yaw) > 32512, `degenerate \u2192 fallback (0,0,-1) yaw \xB10x8000 (got 0x${degenerate.yaw.toString(16)})`);
  const v = { x: 3, y: 4, z: 0 };
  const romAngle = vectorToKnockbackAngle(v);
  const expectedPitch = -Math.trunc(Math.atan2(4, Math.abs(3 * 3 + 0 * 0)) * BAM16_PER_RADIAN);
  const textbookPitch = -Math.trunc(Math.atan2(4, Math.sqrt(3 * 3 + 0 * 0)) * BAM16_PER_RADIAN);
  assert(romAngle.pitch === wrapBam16(expectedPitch), `pitch matches ROM squared-horiz formula (got 0x${romAngle.pitch.toString(16)})`);
  assert(expectedPitch !== textbookPitch, "ROM squared-horiz pitch differs from textbook sqrt (quirk is load-bearing)");
  assert(angleTrimByteToBam16(0) === 0, "trim byte 0 \u2192 0 BAM");
  assert(Math.abs(angleTrimByteToBam16(128)) === 32768, `trim byte +128 \u2192 \xB10x8000 (180\xB0) \u2014 got 0x${angleTrimByteToBam16(128).toString(16)}`);
  const trimmed = computeKnockbackLaunchDirection(origin, { pos: { x: 0, y: 0, z: 5 } }, { mode: 1, trimYaw: 128 });
  assert(
    Math.abs(Math.abs(trimmed.yaw) - 32768) < 512 || trimmed.yaw < -32256 || trimmed.yaw > 32256,
    `yaw trim +128 rotates ~180\xB0 (got 0x${trimmed.yaw.toString(16)})`
  );
  const a = defaultSourceKnockbackActor({ x: 0, y: 0, z: 0 });
  const d = defaultSourceKnockbackActor({ x: 10, y: 0, z: 0 });
  const angleGRed = computeKnockbackLaunchDirection(a, d, { mode: 1 });
  const angleRepeat = computeKnockbackLaunchDirection(a, d, { mode: 1 });
  assert(
    angleGRed.yaw === angleRepeat.yaw && angleGRed.pitch === angleRepeat.pitch,
    "direction is deterministic & type-category-independent (geometry only)"
  );
}
export {
  KNOCKBACK_STRENGTH_TABLES,
  angleTrimByteToBam16,
  computeKnockbackLaunchDirection,
  computeKnockbackLaunchDirectionLinked,
  defaultSourceKnockbackActor,
  defaultSourceKnockbackContext,
  groundHorizontalSpeed,
  knockbackStrengthClamp,
  launchVelocityMagnitude,
  runSourceKnockbackSelfTests,
  vectorToKnockbackAngle
};
