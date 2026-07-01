#!/usr/bin/env node
// Golden-trace analyzer: fit movement constants (gravity, jump velocity, ground speed,
// acceleration, dash) directly from a golden JSONL recorded by trace-golden-record.mjs.
//
// Pure kinematics on the recorded trajectory — no sim required. Output is EVIDENCE for
// upgrading TUNED constants to DERIVED, not an automatic upgrade: per the repo ground rule,
// a human writes the behavior-notes.md entry (citing the golden file) before constants.ts
// changes. Fits from a single trace are provisional until reproduced on a second trace.
//
// Usage: node scripts/trace-golden-analyze.mjs <golden.jsonl> [--ground-eps 0.5] [--out file.md]

import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");

function median(values) {
  if (!values.length) return null;
  const s = [...values].sort((a, b) => a - b);
  const m = Math.floor(s.length / 2);
  return s.length % 2 ? s[m] : (s[m - 1] + s[m]) / 2;
}

function hypot2(x, z) {
  return Math.sqrt(x * x + z * z);
}

/**
 * Analyze golden records: [{f, pos:{x,y,z}, vel?:{x,y,z}, pad:{stickX,stickY,buttons}, …}].
 * Returns { groundY, fits: {…}, checks: {…} } — every fit carries a sample count `n`;
 * treat small n as weak evidence.
 */
export function analyzeGolden(records, opts = {}) {
  const groundEps = opts.groundEps ?? 0.5;
  const n = records.length;
  if (n < 60) throw new Error(`trace too short (${n} frames); need at least ~60`);

  // Derived per-frame velocity: motion INTO frame i (pos[i] - pos[i-1]).
  const dvel = records.map((r, i) =>
    i === 0
      ? { x: 0, y: 0, z: 0 }
      : {
          x: r.pos.x - records[i - 1].pos.x,
          y: r.pos.y - records[i - 1].pos.y,
          z: r.pos.z - records[i - 1].pos.z,
        },
  );

  // Ground level: the most common quantized Y among near-stationary-Y frames.
  const yCounts = new Map();
  for (let i = 1; i < n; i += 1) {
    if (Math.abs(dvel[i].y) < 0.01) {
      const key = Math.round(records[i].pos.y * 100) / 100;
      yCounts.set(key, (yCounts.get(key) ?? 0) + 1);
    }
  }
  const groundY = [...yCounts.entries()].sort((a, b) => b[1] - a[1])[0]?.[0];
  if (groundY === undefined) throw new Error("could not infer ground Y (no stationary-Y frames)");
  const airborne = records.map((r) => r.pos.y > groundY + groundEps);

  // Validate the recorded +0x58 velocity field against derived deltas (when present).
  let velFieldCheck = null;
  const velSamples = records
    .map((r, i) => (i > 0 && r.vel ? Math.abs(r.vel.y - dvel[i].y) : null))
    .filter((v) => v !== null);
  if (velSamples.length) {
    velFieldCheck = { meanAbsDiffY: velSamples.reduce((a, b) => a + b, 0) / velSamples.length, n: velSamples.length };
  }

  // Gravity: median per-frame decrease of vertical velocity across consecutive airborne
  // frames (excluding frames where jump is freshly pressed, which reset vy).
  const gravitySamples = [];
  for (let i = 2; i < n; i += 1) {
    if (airborne[i - 1] && airborne[i] && dvel[i].y < dvel[i - 1].y) {
      gravitySamples.push(dvel[i - 1].y - dvel[i].y);
    }
  }

  // Jump velocity: derived vy on the first airborne frame of each ground→air transition.
  const jumpSamples = [];
  for (let i = 1; i < n; i += 1) {
    if (!airborne[i - 1] && airborne[i] && dvel[i].y > 0) jumpSamples.push(dvel[i].y);
  }

  // Ground speed: steady-state horizontal speed during sustained full-stick ground runs.
  const stickMag = (r) => (r.pad ? hypot2(r.pad.stickX / 127, r.pad.stickY / 127) : null);
  const groundRunSpeeds = [];
  let run = [];
  for (let i = 1; i < n; i += 1) {
    const held = stickMag(records[i]);
    if (!airborne[i] && held !== null && held > 0.85) run.push(hypot2(dvel[i].x, dvel[i].z));
    else {
      if (run.length >= 20) groundRunSpeeds.push(...run.slice(Math.floor(run.length / 2)));
      run = [];
    }
  }
  if (run.length >= 20) groundRunSpeeds.push(...run.slice(Math.floor(run.length / 2)));
  const maxGroundSpeed = median(groundRunSpeeds);

  // Acceleration: per-frame horizontal speed gain in the first frames of a press-from-rest,
  // while still below 80% of steady speed.
  const accelSamples = [];
  for (let i = 6; i < n; i += 1) {
    const restBefore = [1, 2, 3, 4, 5].every((k) => hypot2(dvel[i - k].x, dvel[i - k].z) < 0.05);
    const held = stickMag(records[i]);
    if (!airborne[i] && restBefore && held !== null && held > 0.85) {
      for (let j = i; j < Math.min(i + 8, n); j += 1) {
        const s0 = hypot2(dvel[j - 1].x, dvel[j - 1].z);
        const s1 = hypot2(dvel[j].x, dvel[j].z);
        if (maxGroundSpeed && s1 > maxGroundSpeed * 0.8) break;
        if (s1 > s0) accelSamples.push(s1 - s0);
      }
    }
  }

  // Dash: clusters of horizontal speed clearly above steady ground speed.
  const dashes = [];
  if (maxGroundSpeed) {
    let cluster = null;
    for (let i = 1; i < n; i += 1) {
      const s = hypot2(dvel[i].x, dvel[i].z);
      if (!airborne[i] && s > maxGroundSpeed * 1.02 + 0.2) {
        cluster = cluster ?? { start: i, speeds: [] };
        cluster.speeds.push(s);
      } else if (cluster) {
        dashes.push({ startFrame: cluster.start, durationFrames: cluster.speeds.length, peakSpeed: Math.max(...cluster.speeds), medianSpeed: median(cluster.speeds) });
        cluster = null;
      }
    }
  }

  return {
    frames: n,
    groundY,
    airborneFrames: airborne.filter(Boolean).length,
    checks: { velFieldVsDerived: velFieldCheck },
    fits: {
      gravityPerFrame: { value: median(gravitySamples), n: gravitySamples.length },
      jumpVelocity: { value: median(jumpSamples), n: jumpSamples.length },
      maxGroundSpeed: { value: maxGroundSpeed, n: groundRunSpeeds.length },
      groundAccelPerFrame: { value: median(accelSamples), n: accelSamples.length },
      dashes,
    },
  };
}

/** Best-effort read of the current TUNED values for the comparison column. */
export function currentConstants() {
  try {
    const src = fs.readFileSync(path.join(repoRoot, "packages", "combat", "src", "constants.ts"), "utf8");
    const grab = (name) => {
      const m = src.match(new RegExp(`${name}\\s*[:=]\\s*(-?\\d+(?:\\.\\d+)?)`));
      return m ? Number(m[1]) : null;
    };
    return { GRAVITY: grab("GRAVITY"), JUMP_VELOCITY: grab("VELOCITY"), DASH_SPEED: grab("SPEED"), ACCEL: grab("ACCEL") };
  } catch {
    return {};
  }
}

export function loadGolden(file) {
  const lines = fs.readFileSync(file, "utf8").split(/\r?\n/).filter(Boolean);
  const meta = JSON.parse(lines[0]);
  const records = (meta.schema === "gf-golden-trace-v1" ? lines.slice(1) : lines).map((l) => JSON.parse(l));
  return { meta: meta.schema ? meta : null, records };
}

function fmt(fit) {
  if (!fit || fit.value === null || fit.value === undefined) return "no data";
  return `${fit.value.toFixed(4)} (n=${fit.n}${fit.n < 10 ? " — WEAK" : ""})`;
}

async function main() {
  const file = process.argv[2];
  if (!file || file.startsWith("--")) {
    console.error("usage: node scripts/trace-golden-analyze.mjs <golden.jsonl>");
    process.exit(2);
  }
  const { meta, records } = loadGolden(file);
  const result = analyzeGolden(records);
  const cur = currentConstants();

  const lines = [
    `# Golden-trace fit — ${path.basename(file)}`,
    "",
    `Source: \`${file}\`${meta ? ` (borg ${meta.borg}, label ${meta.label}, base ${meta.borgBase})` : ""}`,
    `Frames: ${result.frames} (${result.airborneFrames} airborne) — inferred ground Y = ${result.groundY}`,
    result.checks.velFieldVsDerived
      ? `Velocity-field check (+0x58 vs position deltas): mean |diff| = ${result.checks.velFieldVsDerived.meanAbsDiffY.toFixed(5)} over ${result.checks.velFieldVsDerived.n} frames`
      : "Velocity-field check: no recorded vel in trace",
    "",
    "| quantity | trace fit (units/frame) | current constant |",
    "|---|---|---|",
    `| gravity | ${fmt(result.fits.gravityPerFrame)} | ${cur.GRAVITY ?? "?"} |`,
    `| jump velocity | ${fmt(result.fits.jumpVelocity)} | ${cur.JUMP_VELOCITY ?? "?"} |`,
    `| max ground speed | ${fmt(result.fits.maxGroundSpeed)} | (per-borg: base + speed·scale) |`,
    `| ground accel | ${fmt(result.fits.groundAccelPerFrame)} | ${cur.ACCEL ?? "?"} |`,
    "",
    `Dashes detected: ${result.fits.dashes.length}`,
    ...result.fits.dashes.map((d) => `- frame ${d.startFrame}: ${d.durationFrames} frames, median speed ${d.medianSpeed.toFixed(2)}, peak ${d.peakSpeed.toFixed(2)}`),
    "",
    "> Evidence, not an upgrade: reproduce on a second trace, then record the finding in",
    "> research/decomp/behavior-notes.md (cite this golden file) before touching constants.ts.",
  ];
  const outPath = process.argv.includes("--out")
    ? process.argv[process.argv.indexOf("--out") + 1]
    : path.join(repoRoot, "research", "traces", "GG4E", `golden-fit-${path.basename(file, ".jsonl")}.md`);
  fs.writeFileSync(outPath, lines.join("\n") + "\n");
  console.log(lines.join("\n"));
  console.log(`\nwrote ${outPath}`);
}

if (process.argv[1] && import.meta.url === new URL(`file:///${process.argv[1].replace(/\\/g, "/")}`).href) {
  main().catch((error) => {
    console.error(error.message ?? error);
    process.exit(1);
  });
}
