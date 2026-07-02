#!/usr/bin/env node
// Find the PERSISTENT source of the per-frame scratch transforms (behavior-notes §aa) using
// execute breakpoints (Z0 — supported by Dolphin's stub) instead of write watchpoints (Z2 —
// rejected by this build).
//
// Break at the matrix-library entries:
//   PSMTXCopy(src, dst)     @ 0x8020af28 : r3=src, r4=dst
//   PSMTXConcat(a, b, dst)  @ 0x8020af5c : r3=a, r4=b, r5=dst
// When dst lands in the scratch pool (0x803c1080-0x803c1180), the SOURCE registers point at
// the persistent per-actor world transform. Collect unique sources + LR callers, release the
// CPU, and HOLD the stub connection open (single-client stub halts the game on disconnect).
//
// Usage: node scripts/gdb-catch-matrix-src.mjs [--matches 14] [--seconds 60] [--port 5555]

import { GdbRemote, isMem1 } from "./lib/gdb-remote.mjs";

const args = new Map();
for (let i = 2; i < process.argv.length; i += 1) {
  const a = process.argv[i];
  if (a.startsWith("--")) args.set(a.slice(2), process.argv[i + 1]?.startsWith("--") ? "1" : process.argv[++i]);
}
const MATCHES = Number.parseInt(args.get("matches") ?? "14", 10);
const BUDGET_MS = Number.parseInt(args.get("seconds") ?? "60", 10) * 1000;
const PORT = Number.parseInt(args.get("port") ?? "5555", 10);

const MTX_COPY = 0x8020af28;
const MTX_CONCAT = 0x8020af5c;
const SCRATCH_LO = 0x803c1080;
const SCRATCH_HI = 0x803c1180;

async function connectWithRetry(gdb, attempts = 30, delayMs = 4000) {
  for (let i = 1; ; i += 1) {
    try {
      await gdb.connect();
      return;
    } catch (e) {
      if (i >= attempts) throw e;
      if (i === 1) console.log(`stub not up (${e.code ?? e.message}); retrying every ${delayMs / 1000}s`);
      await new Promise((r) => setTimeout(r, delayMs));
    }
  }
}

async function main() {
  const gdb = new GdbRemote("127.0.0.1", PORT);
  await connectWithRetry(gdb);
  console.log("connected to GDB stub");
  gdb.interrupt();
  await gdb.waitPacket(8000).catch(() => {});

  const kinds = new Map();
  for (const a of [MTX_COPY, MTX_CONCAT]) kinds.set(a, await gdb.setBreak(a));
  console.log("breakpoints armed at PSMTXCopy/PSMTXConcat; hunting scratch-pool writers");

  const found = [];
  const seenSrc = new Set();
  let stops = 0;
  const started = Date.now();
  try {
    while (found.length < MATCHES && Date.now() - started < BUDGET_MS) {
      let stop;
      try {
        stop = await gdb.continueAndWaitStop(15000);
      } catch {
        console.log(`  …no stops in 15s (${stops} matrix stops so far)`);
        continue;
      }
      if (stop.pc !== MTX_COPY && stop.pc !== MTX_CONCAT) continue;
      stops += 1;
      const r3 = await gdb.readReg(3);
      const r4 = await gdb.readReg(4);
      const r5 = stop.pc === MTX_CONCAT ? await gdb.readReg(5) : null;
      const dst = stop.pc === MTX_COPY ? r4 : r5;
      if (dst === null || dst < SCRATCH_LO || dst >= SCRATCH_HI) continue;
      const lr = await gdb.readReg(0x43);
      const srcs = stop.pc === MTX_COPY ? [r3] : [r3, r4];
      for (const s of srcs) {
        if (!isMem1(s)) continue;
        // Read the source matrix translation NOW — a live moving actor identifies itself
        // by its translation changing across repeated catches.
        let t = null;
        const blk = await gdb.readMem(s, 0x30).catch(() => null);
        if (blk && blk.length >= 0x30) {
          t = [blk.readFloatBE(0x0c), blk.readFloatBE(0x1c), blk.readFloatBE(0x2c)].map((v) => Math.round(v * 10) / 10);
        }
        found.push({ fn: stop.pc === MTX_COPY ? "Copy" : "Concat", src: s, dst, lr, t });
        seenSrc.add(s);
        console.log(`MATCH ${found.length}: ${stop.pc === MTX_COPY ? "Copy" : "Concat"} src=0x${s.toString(16)} lr=0x${lr?.toString(16)} T=${t ? `(${t.join(",")})` : "?"}`);
      }
    }
  } finally {
    for (const [a, k] of kinds) await gdb.clearBreak(a, k).catch(() => {});
    gdb.socket.write("$c#63"); // release the CPU
  }

  console.log(`\n${stops} matrix-call stops; ${seenSrc.size} unique persistent source matrices:`);
  for (const s of seenSrc) console.log(`  0x${s.toString(16)}`);
  const byLr = new Map();
  for (const f of found) byLr.set(f.lr, (byLr.get(f.lr) ?? 0) + 1);
  console.log("callers (lr):");
  for (const [lr, n] of [...byLr.entries()].sort((a, b) => b[1] - a[1])) console.log(`  0x${lr?.toString(16)} (${n})`);

  console.log("\nGAME RELEASED AND RUNNING. This process stays alive to keep the stub client");
  console.log("connected (disconnect halts the game). Verify sources via DME from another shell.");
  await new Promise(() => {});
}

main().catch((e) => {
  console.error(e.message ?? e);
  process.exit(1);
});
