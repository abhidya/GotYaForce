// poc-run.js — browser-side POC step (HANDOFF-2026-08-09 §5: "Loaded in the actual
// browser app"). Injected into the game's index.html by smoke-browser-wasm-poc.mjs.
// Waits for the game runtime (window.__gf), then loads unit_poc.wasm + arena into the
// SAME page and replays 32 snapshot cases against the node-verified expected outputs.
// Result is published on <html data-gf-wasm-poc="..."> for the headless DOM dump.
(async () => {
  const html = document.documentElement;
  const report = (s) => html.setAttribute("data-gf-wasm-poc", s);
  try {
    // 1. wait for the actual game app to boot and expose its debug handle
    await new Promise((resolve, reject) => {
      const t0 = Date.now();
      (function poll() {
        if (window.__gf && html.getAttribute("data-gf-runtime") === "loaded") return resolve();
        if (Date.now() - t0 > 60000) return reject(new Error("game runtime never loaded"));
        setTimeout(poll, 100);
      })();
    });
    // drive the __gf handle: proves we're inside the live app, not a bare page
    const gf = window.__gf;
    const gfEvidence = `stages=${gf.stages?.length ?? 0} nav=${gf.navigation?.nodeId ?? gf.navigation?.screen ?? "?"}`;

    // 2. load wasm + arena + expectations
    const [wasmBuf, arena, expectations] = await Promise.all([
      fetch("/__poc/unit_poc.wasm").then((r) => r.arrayBuffer()),
      fetch("/__poc/arena.json").then((r) => r.json()),
      fetch("/__poc/browser-expectations.json").then((r) => r.json()),
    ]);
    const f32b = new Float32Array(1);
    const fr = (x) => { f32b[0] = x; return f32b[0]; };
    let dv, u8;
    let shimCalls = 0;
    const env = {
      gnt4_PSVECSubtract_bl: (a, b, o) => { shimCalls++; a >>>= 0; b >>>= 0; o >>>= 0; for (let i = 0; i < 3; i++) dv.setFloat32(o + i * 4, fr(dv.getFloat32(a + i * 4, true) - dv.getFloat32(b + i * 4, true)), true); },
      gnt4_PSVECAdd_bl: (a, b, o) => { shimCalls++; a >>>= 0; b >>>= 0; o >>>= 0; for (let i = 0; i < 3; i++) dv.setFloat32(o + i * 4, fr(dv.getFloat32(a + i * 4, true) + dv.getFloat32(b + i * 4, true)), true); },
      gnt4_PSQUATDotProduct_bl: (a, b) => { shimCalls++; a >>>= 0; b >>>= 0; let s = 0; for (let i = 0; i < 3; i++) s = fr(s + fr(dv.getFloat32(a + i * 4, true) * dv.getFloat32(b + i * 4, true))); return s; },
      gnt4_PSQUATScale_bl: (s, v, o) => { shimCalls++; v >>>= 0; o >>>= 0; for (let i = 0; i < 3; i++) dv.setFloat32(o + i * 4, fr(fr(s) * dv.getFloat32(v + i * 4, true)), true); },
    };
    const { instance } = await WebAssembly.instantiate(wasmBuf, { env });
    const ex = instance.exports;
    u8 = new Uint8Array(ex.memory.buffer);
    dv = new DataView(ex.memory.buffer);
    const b64 = (s) => Uint8Array.from(atob(s), (c) => c.charCodeAt(0));
    for (const s of arena.segments) u8.set(b64(s.b64), s.addr >>> 0);

    // 3. replay the node-verified snapshot corpus
    const S30 = dv.getUint32(0x80433930, true), S34 = dv.getUint32(0x80433934, true), S50 = dv.getUint32(0x80433950, true);
    const HPM = 0x803b069c, ENG = 0x803b068c;
    const REC = 0x80600000, ATT = 0x80601000, ATTB = 0x80602000, DEF = 0x80604000, DESC = 0x80606000;
    const wU8 = (a, v) => { u8[a >>> 0] = v & 0xff; };
    const wU16 = (a, v) => dv.setUint16(a >>> 0, v & 0xffff, true);
    const wU32 = (a, v) => dv.setUint32(a >>> 0, v >>> 0, true);
    const wF32 = (a, v) => dv.setFloat32(a >>> 0, v, true);
    const wI32 = (a, v) => dv.setInt32(a >>> 0, v | 0, true);
    const wI16 = (a, v) => dv.setInt16(a >>> 0, v | 0, true);
    const encodeActor = (base, a, container) => {
      u8.fill(0, base >>> 0, (base + 0x800) >>> 0);
      wU8(base, 1); wU8(base + 0x18, a.isActive ? 1 : 0); wU8(base + 0x83, a.isBorg ? 0 : 1);
      wU8(base + 0x88, a.team); wU16(base + 0x1c4, a.maxHp); wU8(base + 0x3e4, a.slot);
      wU8(base + 0x3e6, a.heroFlag);
      wU8(base + 0x3e8, (a.borgNumber >> 8) & 0xff); wU8(base + 0x3e9, a.borgNumber & 0xff);
      wU8(base + 0x43a, a.handicap); wU8(base + 0x6ca, a.comboRank); wU8(base + 0x6fc, a.pairAttack);
      if (container != null) wF32(container + 0xc4, a.power); else wF32(base + 0xb4, a.power);
    };
    let pass = 0;
    for (const { case: c, expect } of expectations) {
      u8.fill(0, REC, REC + 0x20);
      wU16(REC, c.basePower); wU8(REC + 6, c.ctx.attackerHpCurveIndex); wU8(REC + 7, c.ctx.attackerForceCurveIndex);
      wU16(REC + 0x10, c.ctx.flagsA); wU16(REC + 0x12, c.ctx.flagsB);
      u8.fill(0, ATT, ATT + 0x100); wU32(ATT + 0x90, ATTB);
      encodeActor(ATTB, c.att, ATT);
      encodeActor(DEF, c.def, null);
      wU32(DEF + 0x90, 0); wU32(DEF + 0x4ac, DESC);
      wU16(DEF + 0x59c, c.ctx.victimResistanceMask);
      wU32(DEF + 0x5e0, c.ctx.victimSpawnProtection ? 0x4000000 : 0);
      wU8(DEF + 0x71a, 1); wU32(DEF + 0x5a0, c.ctx.victimStatusImmune ? 2 : 0);
      wU8(DESC + 0x9c, c.ctx.defenderDefenseCurveSelectors[0]);
      wU8(DESC + 0x9d, c.ctx.defenderDefenseCurveSelectors[1]);
      wU8(DESC + 0x9e, c.ctx.defenderDefenseCurveSelectors[2]);
      wI16(HPM + c.att.slot * 2, c.att.hp); wI16(HPM + c.def.slot * 2, c.def.hp);
      for (const a of [c.att, c.def]) {
        wI32(S34 + a.team * 0x3c + 0x114, 3200);
        wI32(ENG + a.team * 4, (32 - a.forceRatioIndex) * 100);
        wU8(S50 + a.team, a.sideRank);
      }
      wU8(S30 + 0x32, c.ctx.cpuHalvingEnabled ? 0 : 2);
      wU8(S34 + 0x1f, 0);
      if ((ex.zz_003cd5c_(REC, ATT, DEF) | 0) === expect) pass++;
    }
    // 4. one Unit B call through the SDK seam in-browser
    const B1 = 0x80609000, B3 = 0x8060b000, B4 = 0x8060c000;
    for (let k = 0; k < 0x200; k += 4) wF32(B1 + k, ((k * 2654435761) % 97) / 7 - 6);
    wF32(0x8060a000 + 0x30, 5); for (let k = 0; k < 24; k += 4) wF32(B3 + k, ((k * 40503) % 89) / 9 - 4);
    wI32(B4, 2);
    ex.FUN_80031634(B1, 0x8060a000, B3, B4);
    report(`pass:${pass}/${expectations.length} shimCalls:${shimCalls} mem:${(ex.memory.buffer.byteLength / 1048576) | 0}MiB ${gfEvidence}`);
  } catch (e) {
    report(`error:${String(e && e.message || e).slice(0, 200)}`);
  }
})();
