import assert from 'node:assert/strict';
import fs from 'node:fs';
import vm from 'node:vm';
import test from 'node:test';
import { execFileSync } from 'node:child_process';
import ts from 'typescript';

// Run production scheduling, slot callbacks, presentation pruning, step/pause gates,
// and teardown. Double only device/audio readiness and the already-tested battle sim.
// AUTHORED_AUDIO_TEST_BASE_REF=e37cb88 runs the same semantic assertions on old code.
const source = process.env.AUTHORED_AUDIO_TEST_BASE_REF
  ? execFileSync('git', ['show', `${process.env.AUTHORED_AUDIO_TEST_BASE_REF}:apps/game/src/main.ts`], { encoding: 'utf8' })
  : fs.readFileSync(new URL('../apps/game/src/main.ts', import.meta.url), 'utf8');
const main = ts.createSourceFile('main.ts', source, ts.ScriptTarget.Latest, true);
const functions = new Set(['seKeyForSoundId', 'playAuthoredSwingSounds', 'clearAuthoredSwingSounds',
  'authoredSwingCueIsCurrent', 'flushAuthoredSwingSounds', 'playRateLimited', 'playSfx',
  'teardownBattle', 'syncBattlePresentation', 'stepBattle', 'resolveBattle']);
const variables = new Set(['authoredSwingTimeMs', 'authoredSwingOwners', 'authoredSwingCues',
  'AUTHORED_SWING_SLOTS', 'AUTHORED_SE_MIN_GAP_MS', 'AUTHORED_MAX_DELAY_MS', 'lastCombatSfxAt',
  'LANDING_FROM_SLOTS', 'LANDING_TO_SLOTS', 'lastAnimSlotByUid', 'simAccumulator', 'SIM_DT',
  'SIM_MAX_CATCHUP_SECONDS', 'SIM_MAX_SUBSTEPS', 'PERCENT_SCALE']);
const nodes = main.statements.filter(n => ts.isFunctionDeclaration(n) && functions.has(n.name?.text)
  || ts.isVariableStatement(n) && n.declarationList.declarations.some(d => variables.has(d.name.getText(main))));
let slotCallback;
function visit(n) {
  if (ts.isPropertyAssignment(n) && n.name.getText(main) === 'onSlotEnter') slotCallback = n.initializer.getText(main);
  ts.forEachChild(n, visit);
}
visit(main);
assert.ok(slotCallback);
const code = ts.transpileModule(nodes.map(n => n.getText(main)).join('\n') + `\nglobalThis.slotEnter = ${slotCallback};`,
  { compilerOptions: { target: ts.ScriptTarget.ES2022, module: ts.ModuleKind.None } }).outputText;
const flush = async () => { for (let i = 0; i < 12; i++) await Promise.resolve(); };
const sounds = [{ frame: 12, id: 103 }, { frame: 24, id: 103 }]; // Decoded pl0000 g0s0.
function harness({ deferred = false } = {}) {
  let now = 0, resolve, reject, result = 'ongoing';
  const calls = [], timers = [], actors = new Map(), pendingSlots = [];
  const readiness = new Promise((a, b) => { resolve = a; reject = b; });
  const audio = { playSfx: async key => { calls.push({ key, at: now }); } };
  const context = vm.createContext({ DISABLE_COMBAT_SFX: false, SOURCE_FRAME_SECONDS: 1 / 60,
    framesToMilliseconds: frame => frame * 1000 / 60, performance: { now: () => now },
    window: { setTimeout: (fn, ms) => timers.push({ fn, due: now + ms }) },
    initAudio: () => deferred ? readiness : Promise.resolve(audio),
    session: null, currentBattlePresentation: () => null, localFocusBorg: () => null,
    battleSceneState: () => ({ actors: [...actors.values()], projectiles: [], projectileDespawns: [] }),
    battleScene: { clear: () => actors.clear(), sync: () => {
      for (const args of pendingSlots.splice(0)) context.slotEnter(...args);
    } }, updateHud() {}, closePauseMenu() {},
    playCombatSfx() {}, collectLocalInputs: () => ({}), stepSimOnce() {},
    battleOutcomeFromState: () => ({ win: false }), computeResults: () => ({}),
    gotchaBox: { revert() {} }, dispatchSession() {},
  });
  vm.runInContext(code, context);
  const freshBattle = () => { context.session = { paused: false, resolved: false, hud: { destroy() {} }, battle: { observe: () => ({ result }) } }; };
  freshBattle();
  const wall = async ms => {
    const end = now + ms;
    for (const t of timers.filter(t => t.due <= end).sort((a, b) => a.due - b.due)) {
      timers.splice(timers.indexOf(t), 1); now = t.due; t.fn(); await flush();
    }
    now = end; await flush();
  };
  return { calls, context, wall, freshBattle, ready: () => resolve(audio), nullReady: () => resolve(null),
    fail: () => reject(new Error('audio unavailable')),
    enter(uid = 'a', events = sounds, slot = 'melee') {
      actors.set(uid, { uid }); context.slotEnter('pl0000', slot, uid, events);
    },
    onNextSync(uid, events, slot = 'melee') { actors.set(uid, { uid }); pendingSlots.push(['pl0000', slot, uid, events]); },
    retire(uid = 'a') { actors.delete(uid); },
    pause() { context.session.paused = true; }, resume() { context.session.paused = false; },
    quit() { context.teardownBattle(); }, finish() { result = 'win'; },
    async steps(count) { for (let i = 0; i < count; i++) { await wall(1000 / 60); context.stepBattle(1 / 60); await flush(); } },
  };
}

test('future authored cues freeze during pause and retain remaining delay on repeated resume', async () => {
  const h = harness(); h.enter(); await h.steps(6);
  for (let i = 0; i < 3; i++) { h.pause(); await h.steps(60); assert.equal(h.calls.length, 0); h.resume(); }
  await h.steps(5); assert.equal(h.calls.length, 0);
  await h.steps(1); assert.deepEqual(h.calls.map(c => c.key), ['se_067']);
  h.pause(); await h.wall(2000); assert.equal(h.calls.length, 1);
  h.resume(); await h.steps(12); assert.equal(h.calls.length, 2);
});

test('slot interruption cancels only that actor, including a replacement swing on the same uid', async () => {
  const h = harness(); h.enter(); h.enter('b', [{ frame: 12, id: 104 }]); await h.steps(6);
  h.enter('a', [], 'hit'); await h.steps(6);
  assert.deepEqual(h.calls.map(c => c.key), ['se_068']);
  h.enter('a', [{ frame: 12, id: 105 }]); await h.steps(12);
  assert.deepEqual(h.calls.map(c => c.key), ['se_068', 'se_069']);
});

test('despawn cancels future sounds without requiring another slot callback', async () => {
  const h = harness(); h.enter(); await h.steps(6); h.retire(); await h.steps(30);
  assert.deepEqual(h.calls, []);
});

test('teardown and replacement battle invalidate scheduled and awaiting-init cues', async () => {
  for (const deferred of [false, true]) {
    const h = harness({ deferred }); h.enter(); await h.steps(deferred ? 12 : 6);
    h.quit(); h.freshBattle(); h.ready(); await h.steps(30);
    assert.deepEqual(h.calls, []);
    h.enter('a', [{ frame: 0, id: 104 }]); await h.steps(1);
    assert.deepEqual(h.calls.map(c => c.key), ['se_068']);
  }
});

test('ready audio stays held during pause; interruption while initializing discards its cue', async () => {
  const h = harness({ deferred: true }); h.enter(); await h.steps(12);
  h.pause(); h.ready(); await flush(); assert.deepEqual(h.calls, []);
  await h.wall(1000); assert.deepEqual(h.calls, []);
  h.resume(); await h.steps(1); assert.equal(h.calls.length, 1);
  const interrupted = harness({ deferred: true }); interrupted.enter(); await interrupted.steps(12);
  interrupted.enter('a', [], 'hit'); interrupted.ready(); await flush();
  assert.deepEqual(interrupted.calls, []);
});

test('null and rejected initialization settle quietly without late playback', async () => {
  for (const mode of ['nullReady', 'fail']) {
    const h = harness({ deferred: true }); h.enter(); await h.steps(12); h[mode](); await flush();
    await h.steps(30); assert.deepEqual(h.calls, []);
  }
});

test('actual dispatch preserves sample floor and event ordering, including simultaneous actors', async () => {
  const h = harness(); h.enter(); h.enter('b'); await h.steps(24);
  assert.deepEqual(h.calls.map(c => c.key), ['se_067', 'se_067']);
  const delayed = harness({ deferred: true });
  delayed.enter('a', [{ frame: 24, id: 105 }, { frame: 12, id: 104 }, { frame: 24, id: 106 }]);
  await delayed.steps(24); delayed.ready(); await flush();
  assert.deepEqual(delayed.calls.map(c => c.key), ['se_068', 'se_069', 'se_06a']);
  const same = harness({ deferred: true }); same.enter(); await same.steps(30); same.ready(); await flush();
  assert.equal(same.calls.length, 1, 'late init must not burst the same sample inside its dispatch floor');
});

test('resolution discards future cues and cap remains 2000ms', async () => {
  const h = harness(); h.enter(); await h.steps(6); h.finish(); await h.steps(30);
  assert.deepEqual(h.calls, []);
  const capped = harness(); capped.enter('a', [{ frame: 1000, id: 103 }]); await capped.steps(119);
  assert.deepEqual(capped.calls, []); await capped.steps(1); assert.equal(capped.calls.length, 1);
});


test('presentation interruption wins over a due cue; a new slot is not aged by preceding catch-up steps', async () => {
  const h = harness(); h.enter(); await h.steps(11);
  h.onNextSync('a', [], 'hit'); await h.steps(1); assert.deepEqual(h.calls, []);
  h.onNextSync('a', [{ frame: 12, id: 104 }]);
  await h.wall(250); h.context.stepBattle(0.25); await flush();
  assert.deepEqual(h.calls, []);
  await h.steps(11); assert.deepEqual(h.calls, []);
  await h.steps(1); assert.deepEqual(h.calls.map(c => c.key), ['se_068']);
});

test('wall time alone never advances future cues, and SFX-disabled mode remains silent', async () => {
  const h = harness(); h.enter(); await h.wall(60000); assert.deepEqual(h.calls, []);
  await h.steps(12); assert.equal(h.calls.length, 1);
  const disabled = harness(); disabled.context.DISABLE_COMBAT_SFX = true;
  disabled.enter(); await disabled.steps(30); assert.deepEqual(disabled.calls, []);
});
