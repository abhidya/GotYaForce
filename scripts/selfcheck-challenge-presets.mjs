#!/usr/bin/env node
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import path from 'node:path';
import { emitInlineModuleGraph } from './lib/ts-inline-module.mjs';
const root = process.cwd();
const data = JSON.parse(readFileSync('packages/assets/data/borgs.json', 'utf8'));
const graph = emitInlineModuleGraph({label:'challenge-presets', entry:path.join(root,'apps/game/src/sim/borgCatalog.ts'), outDir:path.join(root,'.tmp/challenge-presets'), stubs:{
  '../../../../packages/assets/data/borgs.json': `export default ${JSON.stringify(data)};`,
  '@gf/assets': `export function createBorgRoster(data) { return { entries:data.borgs, forceCatalog:()=>data.borgs, validIds:ids=>ids }; }`,
  '@gf/combat': `export const buildProfile=()=>({}); export const actionProfileForProfile=()=>null;`,
  '../ui/index.js': 'export {};',
}});
const { BORG_CATALOG } = await import(graph.url);
const costs = new Map(data.borgs.map(b=>[b.id,b]));
const presets = BORG_CATALOG.defaultForceSlots.filter(s=>s.no>=4);
assert.equal(presets.length,4);
for (const slot of presets) {
  assert.ok(slot.borgIds.length >= 4, `${slot.name} has a team`);
  const members = slot.borgIds.map(id => { const borg=costs.get(id); assert.ok(borg, `${id} exists`); assert.ok(borg.hasModel && borg.hasAnim, `${id} has model and animation`); return borg; });
  const total=members.reduce((sum,b)=>sum+b.energy,0);
  assert.ok(total <= 1500, `${slot.name} costs ${total}, over the smallest challenge budget`);
}
const storage = emitInlineModuleGraph({label:'preset-storage',entry:path.join(root,'apps/game/src/forceSlotStorage.ts'),outDir:path.join(root,'.tmp/preset-storage'),stubs:{'./ui/screens/SelectForce.js':'export {};'}});
const values=new Map([['gf-force-slots-v1',JSON.stringify([{no:1,name:'MY FORCE',borgIds:['pl0004']},{no:4,name:'MY FOURTH',borgIds:['pl0615']}])]]);
globalThis.window={localStorage:{getItem:k=>values.get(k)??null,setItem:(k,v)=>values.set(k,v)}};
const {syncForceSlots}=await import(storage.url);
const slots=BORG_CATALOG.defaultForceSlots.map(s=>({...s,borgIds:[...s.borgIds]}));
syncForceSlots(slots);
assert.deepEqual(slots[0],{no:1,name:'MY FORCE',borgIds:['pl0004']});
assert.deepEqual(slots[3],{no:4,name:'MY FOURTH',borgIds:['pl0615']});
assert.deepEqual(slots[4],presets[1], 'new presets appear to existing saves');
console.log('challenge presets PASS: four multi-Borg teams fit 1500, saved edits take precedence');
