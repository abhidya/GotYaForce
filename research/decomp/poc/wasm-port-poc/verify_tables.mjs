// verify_tables.mjs — compare arena-in-memory tables (DOL-sourced) against
// packages/combat/src/data/damageFormula.json (the oracle's tables).
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const here = path.dirname(fileURLToPath(import.meta.url));
const root = path.resolve(here, "..", "..", "..", "..");
const D = JSON.parse(fs.readFileSync(path.join(root, "packages", "combat", "src", "data", "damageFormula.json"), "utf8"));

const module = await WebAssembly.compile(fs.readFileSync(path.join(here, "unit_poc.wasm")));
const instance = await WebAssembly.instantiate(module, { env: new Proxy({}, { get: () => () => 0 }) });
const mem = instance.exports.memory;
const u8 = new Uint8Array(mem.buffer);
const dv = new DataView(mem.buffer);
const arena = JSON.parse(fs.readFileSync(path.join(here, "arena.json"), "utf8"));
for (const s of arena.segments) u8.set(Buffer.from(s.b64, "base64"), s.addr >>> 0);

const slots = [];
for (let i = 0; i < 16; i++) slots.push(dv.getUint32(0x804335e0 + i * 4, true));
console.log("pointer slots:", slots.map((p) => p.toString(16)));

let bad = 0, ok = 0;
function cmpFlat(name, slotIdx) {
  for (let hero = 0; hero < 2; hero++) {
    const base = slots[slotIdx * 2 + hero];
    const vals = D[name][hero].values;
    const jsonPtr = parseInt(D[name][hero].ptr, 16);
    if (jsonPtr !== base) console.log(`  ${name}[${hero}] PTR MISMATCH arena=${base.toString(16)} json=${D[name][hero].ptr}`);
    for (let i = 0; i < vals.length; i++) {
      const a = dv.getFloat32(base + i * 4, true);
      if (a === Math.fround(vals[i])) ok++; else { bad++; if (bad < 8) console.log(`  ${name}[${hero}][${i}] arena=${a} json=${vals[i]}`); }
    }
  }
}
function cmpCurves(name, slotIdx) {
  for (let hero = 0; hero < 2; hero++) {
    const base = slots[slotIdx * 2 + hero];
    const curves = D[name][hero].curves;
    const jsonPtr = parseInt(D[name][hero].ptr, 16);
    if (jsonPtr !== base) console.log(`  ${name}[${hero}] PTR MISMATCH arena=${base.toString(16)} json=${D[name][hero].ptr}`);
    for (let s = 0; s < curves.length; s++) {
      const cptr = dv.getUint32(base + s * 4, true);
      for (let i = 0; i < curves[s].length; i++) {
        const a = dv.getFloat32(cptr + i * 4, true);
        if (a === Math.fround(curves[s][i])) ok++; else { bad++; if (bad < 8) console.log(`  ${name}[${hero}] curve${s}[${i}] arena=${a} json=${curves[s][i]} (cptr=${cptr.toString(16)})`); }
      }
    }
  }
}
cmpFlat("attackRankBySideRank_804335e0", 0);
cmpCurves("attackerHpCurves_804335e8", 1);
cmpCurves("attackerForceCurves_804335f0", 2);
cmpFlat("attackHandicap_804335f8", 3);
cmpCurves("defenseRankCurves_80433600", 4);
cmpCurves("defenderHpCurves_80433608", 5);
cmpCurves("defenderForceCurves_80433610", 6);
cmpFlat("defenseHandicap_80433618", 7);
for (let i = 0; i < D.comboRankScale_802c7ca0.length; i++) {
  const a = dv.getFloat32(0x802c7ca0 + i * 4, true);
  if (a === Math.fround(D.comboRankScale_802c7ca0[i])) ok++; else { bad++; console.log(`  combo[${i}] arena=${a} json=${D.comboRankScale_802c7ca0[i]}`); }
}
console.log(`table compare: ${ok} ok, ${bad} mismatched`);
