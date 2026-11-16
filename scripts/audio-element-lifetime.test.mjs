import assert from 'node:assert/strict';
import fs from 'node:fs';
import vm from 'node:vm';
import test from 'node:test';
import ts from 'typescript';

const source = ts.createSourceFile('index.ts', fs.readFileSync(new URL('../packages/audio/src/index.ts', import.meta.url), 'utf8'), ts.ScriptTarget.Latest, true);
const code = ts.transpileModule(source.statements.filter(n => !ts.isExportDeclaration(n)).map(n => n.getText(source)).join('\n'), {
  compilerOptions: { target: ts.ScriptTarget.ES2022, module: ts.ModuleKind.CommonJS },
}).outputText;
async function harness({ pending = false } = {}) {
  const elements = [];
  class Audio extends EventTarget {
    constructor(src) { super(); this.src = src; this.dataset = {}; this.pauses = 0; this.loads = 0; elements.push(this); }
    play() { return pending ? new Promise((resolve, reject) => { this.resolve = resolve; this.reject = reject; }) : Promise.resolve(); }
    pause() { this.pauses++; }
    load() { this.loads++; }
  }
  const context = vm.createContext({ exports: {}, Audio, URL });
  vm.runInContext(code, context);
  const manager = await context.exports.createAudioManager({ baseUrl: 'https://audio.invalid/', manifest: {
    files: [{ key: 'hit', type: 'sfx', path: 'hit.wav' }, { key: 'voice', type: 'voice', path: 'voice.wav' }],
  } });
  return { manager, elements };
}
for (const key of ['hit', 'voice']) {
  for (const event of ['ended', 'error']) {
    test(`${key}: ${event} releases playback and removes volume/mute ownership`, async () => {
      const { manager } = await harness();
      const audio = await manager.playSfx(key);
      audio.dispatchEvent(new Event(event));
      assert.equal(audio.src, '');
      assert.equal(audio.loads, 1);
      assert.equal(audio.pauses, 1);
      const volume = audio.volume;
      manager.setVolumes({ master: 0.25 }); manager.setMuted(true);
      assert.equal(audio.volume, volume);
      assert.equal(audio.muted, false);
      audio.dispatchEvent(new Event('error')); audio.dispatchEvent(new Event('ended'));
      manager.dispose();
      assert.equal(audio.loads, 1, 'terminal cleanup is idempotent');
    });
  }
}
test('disposing multiple live sounds releases each only once', async () => {
  const { manager } = await harness();
  const a = await manager.playSfx('hit'), b = await manager.playSfx('voice');
  manager.dispose(); manager.dispose();
  for (const audio of [a, b]) {
    audio.dispatchEvent(new Event('error'));
    assert.equal(audio.src, ''); assert.equal(audio.loads, 1); assert.equal(audio.pauses, 1);
  }
});

test('play rejection releases its element without affecting another sound', async () => {
  const { manager, elements } = await harness({ pending: true });
  const first = manager.playSfx('hit'), second = manager.playSfx('voice');
  const rejection = assert.rejects(first, /play failed/);
  elements[0].reject(new Error('play failed'));
  await rejection;
  elements[1].resolve(); await second;
  assert.equal(elements[0].src, ''); assert.equal(elements[0].loads, 1);
  assert.notEqual(elements[1].src, '');
  manager.setMuted(true);
  assert.equal(elements[0].muted, false); assert.equal(elements[1].muted, true);
});
for (const terminal of ['error', 'dispose']) {
  test(`${terminal} during pending play tolerates later rejection`, async () => {
    const { manager, elements } = await harness({ pending: true });
    const playback = manager.playSfx('hit');
    const rejection = assert.rejects(playback, /aborted/);
    if (terminal === 'dispose') manager.dispose();
    else elements[0].dispatchEvent(new Event('error'));
    elements[0].reject(new Error('aborted')); await rejection;
    assert.equal(elements[0].loads, 1); assert.equal(elements[0].pauses, 1);
    manager.dispose(); assert.equal(elements[0].loads, 1);
  });
}
