#!/usr/bin/env node
// Compares a bounded original Dolphin JIT64 capture with checked-in model
// hierarchy labels. It does not establish mesh, matrix or hardware parity.
import {readFile} from 'node:fs/promises';
const capture = JSON.parse(await readFile('research/decomp/ninja-live-joint-topology-2026-11-18.json', 'utf8'));
if (capture.rows.length !== 4 || capture.rows.filter(r => r.id === 0).length !== 2 ||
    capture.rows.filter(r => r.id === 10).length !== 2) throw Error('missing captured actors');
let checked = 0;
for (const row of capture.rows) {
  const borg = row.id === 0 ? 'pl0000' : 'pl000a';
  const bytes = await readFile(`apps/game/public/models/${borg}/model_00.glb`);
  if (bytes.toString('ascii', 0, 4) !== 'glTF' || bytes.toString('ascii', 16, 20) !== 'JSON') throw Error('invalid GLB JSON chunk');
  const glb = JSON.parse(bytes.subarray(20, 20 + bytes.readUInt32LE(12)).toString('utf8'));
  const nodes = Array.from({length: 20}, (_, i) => {
    const matches = glb.nodes.filter(n => n.name === `JOBJ_${i}`);
    if (matches.length !== 1) throw Error(`${borg} missing or duplicate joint ${i}`);
    return matches[0];
  });
  if (row.links.length !== 20) throw Error('incomplete captured joint table');
  for (let i = 0; i < 20; i++) {
    if (row.links[i].i !== i) throw Error('captured joint order mismatch');
    const actual = (nodes[i].children ?? []).map(index => glb.nodes[index].name)
      .filter(name => /^JOBJ_\d+$/.test(name)).map(name => Number(name.slice(5)));
    const expected = []; let child = row.links[i].child;
    while (child !== -1) {
      if (!Number.isInteger(child) || child < 0 || child >= 20 || expected.includes(child)) throw Error('invalid captured links');
      expected.push(child); child = row.links[child].sibling;
    }
    if (JSON.stringify(actual) !== JSON.stringify(expected)) throw Error(`${borg} joint ${i}: hierarchy mismatch`);
    checked++;
  }
}
console.log(`Ninja hierarchy: ${checked} live indexed joint child lists match exported models`);
