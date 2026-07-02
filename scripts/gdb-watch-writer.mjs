#!/usr/bin/env node
// Catch WHO writes the per-frame scratch transform translations (behavior-notes §aa).
//
// Sets a WRITE watchpoint on the scratch matrix translation float (default 0x803c112c —
// the z-component of the transform pool at 0x803c1100, written every frame for every
// rendered actor). On each hit, records PC + LR + r0-r31. The writer function + its live
// register context reveal the SOURCE actor-struct pointer chain — the real per-actor world
// transform the RAM scans couldn't find.
//
// Usage: node scripts/gdb-watch-writer.mjs [--addr 803c112c] [--hits 10] [--port 5555]
// Requires Dolphin running with the GDB stub (scripts/launch-dolphin-gdb.mjs).

import { GdbRemote, isMem1 } from "./lib/gdb-remote.mjs";

const args = new Map();
for (let i = 2; i < process.argv.length; i += 1) {
  const a = process.argv[i];
  if (a.startsWith("--")) args.set(a.slice(2), process.argv[i + 1]?.startsWith("--") ? "1" : process.argv[++i]);
}
const ADDR = Number.parseInt(args.get("addr") ?? "803c112c", 16) >>> 0;
const HITS = Number.parseInt(args.get("hits") ?? "10", 10);
const PORT = Number.parseInt(args.get("port") ?? "5555", 10);

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

  // Write watchpoint: Z2,addr,4
  const reply = await gdb.send(`Z2,${ADDR.toString(16)},4`);
  if (reply !== "OK") throw new Error(`stub rejected write watchpoint: ${reply}`);
  console.log(`write watchpoint @ 0x${ADDR.toString(16)}; collecting ${HITS} hits`);

  const hits = [];
  try {
    while (hits.length < HITS) {
      const { pc } = await gdb.continueAndWaitStop(30000);
      if (pc === null) continue;
      const regs = {};
      for (let r = 0; r < 32; r += 1) regs[`r${r}`] = await gdb.readReg(r);
      const lr = await gdb.readReg(0x43);
      hits.push({ pc, lr, regs });
      const memPtrs = Object.entries(regs)
        .filter(([, v]) => isMem1(v))
        .map(([k, v]) => `${k}=0x${v.toString(16)}`)
        .join(" ");
      console.log(`hit ${hits.length}: pc=0x${pc.toString(16)} lr=0x${lr?.toString(16)} | MEM1 ptrs: ${memPtrs}`);
    }
  } finally {
    await gdb.send(`z2,${ADDR.toString(16)},4`).catch(() => {});
    gdb.socket.write("$c#63"); // fire-and-forget continue so the game runs on
    setTimeout(() => gdb.close(), 300);
  }

  // Summary: unique writer PCs and their frequency.
  const byPc = new Map();
  for (const h of hits) byPc.set(h.pc, (byPc.get(h.pc) ?? 0) + 1);
  console.log("\nunique writer PCs:");
  for (const [pc, n] of [...byPc.entries()].sort((a, b) => b[1] - a[1])) {
    const sample = hits.find((h) => h.pc === pc);
    console.log(`  0x${pc.toString(16)} (${n} hits)  lr=0x${sample.lr?.toString(16)}`);
  }
  console.log("\nfull register dumps (JSON):");
  console.log(JSON.stringify(hits.map((h) => ({ pc: h.pc.toString(16), lr: h.lr?.toString(16), regs: Object.fromEntries(Object.entries(h.regs).map(([k, v]) => [k, v?.toString(16)])) })), null, 1));
}

main().catch((e) => {
  console.error(e.message ?? e);
  process.exit(1);
});
