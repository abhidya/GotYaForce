import assert from "node:assert/strict";
import path from "node:path";
import test from "node:test";
import { fileURLToPath } from "node:url";
import { readFileSync, writeFileSync } from "node:fs";
import { execFileSync } from "node:child_process";
import ts from "typescript";
import { emitInlineModuleGraph } from "./lib/ts-inline-module.mjs";

// Real app helper, session, Challenge VM, mission progression, combat config and
// storage. Only assets/DOM/drawing and combat construction are isolated. A second
// session graph injects a VM-build failure solely to exercise the real fallback.
// Synthetic costs establish the bounded browser contract, not retail parity.
const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
function emit(name, entry, stubs = {}) {
  const graph = emitInlineModuleGraph({ label: `affordable-force-${name}`, entry: path.join(root, entry),
    outDir: path.join(root, ".tmp", `affordable-force-${name}`), stubs });
  // Optional negative control: substitute only historical session/UI source into
  // the emitted graph. Never check out or rewrite a shared worktree source file.
  // Example: GF_PREFIX_BASELINE=9c62021 node --test scripts/affordable-force-prefix.test.mjs
  const baseline = process.env.GF_PREFIX_BASELINE;
  if (baseline && ['session','fallback','ui'].includes(name)) {
    assert.match(baseline,/^[0-9a-f]{7,40}$/i,'baseline must be a commit hash');
    const compile = source => ts.transpileModule(source,{compilerOptions:{module:ts.ModuleKind.ES2022,target:ts.ScriptTarget.ES2022}}).outputText;
    const imports = source => ts.createSourceFile('entry.js',source,ts.ScriptTarget.ES2022,true).statements
      .filter(s=>ts.isImportDeclaration(s)||ts.isExportDeclaration(s)).map(s=>s.moduleSpecifier).filter(Boolean);
    const emittedPath=fileURLToPath(graph.url); const emitted=readFileSync(emittedPath,'utf8');
    const current=compile(readFileSync(path.join(root,entry),'utf8'));
    const before=imports(current),after=imports(emitted); assert.equal(before.length,after.length);
    const links=new Map(before.map((s,i)=>[s.text,after[i].text]));
    const historical=execFileSync('git',['show',`${baseline}:${entry}`],{cwd:root,encoding:'utf8'});
    let rewritten=compile(historical);
    for(const specifier of imports(rewritten).reverse()) {
      assert.ok(links.has(specifier.text),`unmapped historical import ${specifier.text}`);
      rewritten=rewritten.slice(0,specifier.getStart()+1)+links.get(specifier.text)+rewritten.slice(specifier.getEnd()-1);
    }
    writeFileSync(emittedPath,rewritten);
  }
  return graph;
}
const combat = "export const DEFAULT_BOUNDS = {x:500,z:400}; export const createBattle = config => ({config});";
const helper = emit("helper", "apps/game/src/forceDeployment.ts");
const missions = emit("missions", "packages/missions/src/challenge.ts");
const reference = emit("reference", "packages/missions/src/challenge-reference.ts");
const config = emit("config", "packages/missions/src/combat-config.ts", { "@gf/combat": combat });
const sessionStubs = { "@gf/assets": "export {};", "@gf/combat": combat,
  "@gf/missions": [missions, reference, config].map(g => `export * from ${JSON.stringify(g.url)};`).join("\n") };
const vm = emit("vm", "apps/game/src/ui/intro/challengeFlowVm.ts", {"@gf/missions":sessionStubs['@gf/missions']});
const sessionGraph = emit("session", "apps/game/src/gameSession.ts", sessionStubs);
const fallbackGraph = emit("fallback", "apps/game/src/gameSession.ts", { ...sessionStubs,
  "./ui/intro/challengeFlowVm.js": `
    import { createChallengeFlowVm as real, CHALLENGE_FLOW_MODE } from ${JSON.stringify(vm.url)};
    export { CHALLENGE_FLOW_MODE };
    export function createChallengeFlowVm(...args) {
      const vm = real(...args); const tick = vm.tick.bind(vm);
      vm.tick = (...args) => {
        if (vm.state.mode === CHALLENGE_FLOW_MODE.BATTLE_BUILD) throw Error('injected VM build failure');
        return tick(...args);
      }; return vm;
    }`,
});
const { deriveForceDeployment } = await import(helper.url);
const { createChallengeRun } = await import(missions.url);
const { CHALLENGE_GROUP_ROSTERS } = await import(reference.url);
const { createGameSession } = await import(sessionGraph.url);
const { createGameSession: createFallbackSession } = await import(fallbackGraph.url);
console.info = () => {}; // Existing per-screen ROM diagnostics obscure TAP failures.
const costs = new Map([['a',1000], ['b',600], ['c',100], ['d',500], ['e',1600], ['f',200], ['g',1]]);
for (const [name, ids, expected, cost] of [
  ['stop at first overflow, never skip to a cheaper tail', ['a','b','c'], ['a'],1000],
  ['include equality', ['a','d'], ['a','d'],1500],
  ['reject expensive lead without searching later slots', ['e','c'], [],0],
  ['ten 200-cost slots deploy the first seven', Array(10).fill('f'), Array(7).fill('f'),1400],
]) test(name, () => {
  const saved = Object.freeze([...ids]);
  const result = deriveForceDeployment(saved,1500,costs);
  assert.deepEqual(result,{borgIds:expected,cost});
  assert.deepEqual(saved,ids);
  assert.notEqual(result.borgIds,saved);
});
test('30-slot ceiling retains order and a detached work copy', () => {
  const ids = Array.from({length:35}, (_,i) => String(i));
  const result = deriveForceDeployment(Object.freeze(ids),10000,new Map(ids.map(id=>[id,1])));
  assert.deepEqual(result,{borgIds:ids.slice(0,30),cost:30});
});
for (const [label,cost] of [['unknown',undefined],['zero',0],['negative',-1],['NaN',NaN],['infinite',Infinity]]) {
  test(`defensive ${label} cost stops instead of skipping or defaulting`, () => {
    const map = new Map(costs); if (cost !== undefined) map.set('bad',cost);
    assert.deepEqual(deriveForceDeployment(['c','bad','c'],1500,map),{borgIds:['c'],cost:100});
  });
}
test('empty roster and invalid budgets return empty', () => {
  for (const budget of [0,-1,NaN,Infinity]) assert.deepEqual(deriveForceDeployment(['c'],budget,costs),{borgIds:[],cost:0});
  assert.deepEqual(deriveForceDeployment([],1500,costs),{borgIds:[],cost:0});
});
const borgs = [...new Set(Object.values(CHALLENGE_GROUP_ROSTERS).flat())]
  .map(id => ({id,name:id,energy:200,tribe:'fixture'}))
  .concat([...costs].map(([id,energy])=>({id,name:id,energy,tribe:'fixture'})));
const slot = (borgIds,no=1) => ({no,name:`SAVED ${no}`,borgIds:[...borgIds]});
function makeSession(slots, factory=createGameSession, forceFromSlot=s=>s.borgIds.slice(0,30)) {
  let calls = 0; let seeded;
  const session = factory({initialForceSlots:slots,
    forceFromSlot, validForce: ids => ids.slice(0,30),
    createRun: options => { calls++; seeded = options; return createChallengeRun(options); },
    borgs, borgStats:borgs, stageCatalog:{defaultStageId:'st00',hasStageCollision:()=>true},
    loadStageAssets:async()=>({renderState:{},modelUrls:[]})});
  return {session, get calls(){return calls;},get seeded(){return seeded;}};
}
function enter(session,players=1) {
  for (const event of [{type:'boot-ready'},{type:'title-enter'},{type:'menu-select',mode:'challenge'},
    {type:'difficulty-select',budget:1500},{type:'players-select',playerCount:players},{type:'box-continue'}]) session.dispatch(event);
}
const humans = config => config.forces.filter(f=>f.ownerPlayer !== null).map(f=>f.borgIds);
for (const [label,factory] of [['real VM',createGameSession],['mission fallback',createFallbackSession]]) {
  test(`${label}: independently budget two humans through mission seed and prepared combat`, async () => {
    const slots = [slot(['a','b','c']),slot(['a','d','c'],2)];
    const fixture = makeSession(slots,factory); const {session} = fixture;
    enter(session,2);
    const warnings=[]; const warn=console.warn; console.warn=(...args)=>warnings.push(args);
    try {session.dispatch({type:'force-slot-confirm',slot:slots[0]});} finally {console.warn=warn;}
    assert.equal(session.snapshot().screen,'briefing');
    assert.deepEqual(fixture.seeded.playerForces.map(f=>f.borgIds),[['a'],['a','d']]);
    assert.deepEqual(humans(session.snapshot().pendingBattleConfig),[['a'],['a','d']]);
    if (label==='real VM') {
      assert.equal(warnings.length,0);
      assert.equal(typeof session.snapshot().pendingBattleConfig.meta.stageByte,'number','actual VM setup has stage metadata');
    } else assert.ok(warnings.some(args=>String(args[0]).includes('VM battle build failed')));
    session.dispatch({type:'briefing-confirm'});
    const prepared=await session.prepareBattle();
    assert.deepEqual(humans(prepared.config),[['a'],['a','d']]);
    assert.deepEqual(humans(prepared.battle.config),[['a'],['a','d']]);
    assert.deepEqual(prepared.localPlayerIds,['p0','p1']);
    assert.deepEqual(session.snapshot().forceSlots,slots,'deployment must not prune saved slots');
    assert.deepEqual(slots,[slot(['a','b','c']),slot(['a','d','c'],2)]);
  });
}
for (const [name,slots,players] of [
  ['expensive lead',[slot(['e','c'])],1], ['empty saved slot',[slot([])],1],
  ['second human empty',[slot(['c']),slot(['e','c'],2)],2],
  ['unknown lead',[slot(['unknown','c'])],1],
]) test(`session independently rejects ${name} before creating run`, () => {
  const fixture=makeSession(slots); enter(fixture.session,players);
  fixture.session.dispatch({type:'force-slot-confirm',slot:slots[0]});
  assert.equal(fixture.session.snapshot().screen,'select-force'); assert.equal(fixture.calls,0);
  assert.equal(fixture.session.snapshot().pendingBattleConfig,null);
  assert.deepEqual(fixture.session.snapshot().forceSlots,slots);
});
test('session does not use legacy catalog fallback for an empty saved force', () => {
  let fallbackCalls=0; const slots=[slot([])];
  const {session}=makeSession(slots,createGameSession,()=>{fallbackCalls++;return ['c'];});
  enter(session); session.dispatch({type:'force-slot-confirm',slot:slots[0]});
  assert.equal(session.snapshot().screen,'select-force'); assert.equal(fallbackCalls,0);
});
test('real VM gives each human seven of ten 200-cost Borgs', () => {
  const slots=[slot(Array(10).fill('f')),slot(Array(10).fill('f'),2)];
  const {session}=makeSession(slots); enter(session,2);
  session.dispatch({type:'force-slot-confirm',slot:slots[0]});
  assert.deepEqual(humans(session.snapshot().pendingBattleConfig),[Array(7).fill('f'),Array(7).fill('f')]);
  assert.deepEqual(session.snapshot().forceSlots,slots);
});
test('session caps affordable deployment at 30 without truncating a longer saved roster', () => {
  const slots=[slot(Array(35).fill('g'))]; const {session}=makeSession(slots); enter(session);
  session.dispatch({type:'force-slot-confirm',slot:slots[0]});
  assert.deepEqual(humans(session.snapshot().pendingBattleConfig),[Array(30).fill('g')]);
  assert.deepEqual(session.snapshot().forceSlots,slots);
});

class Element {
  children=[]; style={}; attrs={}; listeners={}; className=''; textContent='';
  append(...nodes){for(const n of nodes){n.parent=this;this.children.push(n);}}
  appendChild(n){this.append(n);return n;}
  get firstChild(){return this.children[0];}
  removeChild(n){this.children.splice(this.children.indexOf(n),1);}
  remove(){this.parent?.removeChild(this);}
  setAttribute(k,v){this.attrs[k]=v;}
  addEventListener(k,f){this.listeners[k]=f;}
  querySelector(selector){return this.children.flatMap(n=>[n,...n.descendants()]).find(n=>n.className.split(' ').includes(selector.slice(1)));}
  descendants(){return this.children.flatMap(n=>[n,...n.descendants()]);}
}
globalThis.document={createElement:()=>new Element()};
const stored=new Map();
globalThis.window={localStorage:{getItem:k=>stored.get(k)??null,setItem:(k,v)=>stored.set(k,v)}};
const uiGraph=emit('ui','apps/game/src/ui/screens/SelectForce.ts',{
  '../bitmapText.js':`export const bitmapText = className => Object.assign(document.createElement('span'),{className}); export const setBitmapText = (node,text) => {node.textContent=text;};`,
  '../assets.js':"export const borgBannerPath=id=>id; export const borgMiniPath=id=>id;",
  '../captureCrop.js':"export const captureCropImg=()=>document.createElement('img');",
  '../sceneModel.js':"export const createUiSceneHost=()=>document.createElement('div'); export const mountUiSceneModels=()=>()=>{};",
  '../../assetCatalog.js':"export const createGameAssetCatalog=()=>({loadModelLibraryPaths:async()=>new Map()});",
  '../../publicUrl.js':"export const publicUrl=path=>path;",
});
const {createSelectForce}=await import(uiGraph.url);
function mount(slots,playerCount=1,callbacks={}) {
  const container=new Element(); let confirmed; let edited;
  const handle=createSelectForce(container,{catalog:borgs,slots,selectedSlot:0,limit:1500,playerCount,
    onConfirm:s=>{confirmed=s;callbacks.onConfirm?.(s);},onEdit:s=>{edited=s;},...callbacks});
  return {container,handle,get confirmed(){return confirmed;},get edited(){return edited;}};
}
test('UI preview uses affordable count/cost/remain; confirm and edit retain full saved roster', () => {
  stored.clear(); const slots=[slot(['a','b','c'])]; const ui=mount(slots);
  assert.equal(ui.container.querySelector('.gf-select-cost-value').textContent,'1000');
  assert.equal(ui.container.querySelector('.gf-select-limit').textContent,'500 REMAIN');
  assert.match(ui.container.querySelector('.gf-select-deployment').textContent,/1\/3 deploy, COST 1000, 500 REMAIN/);
  ui.handle.handleMenuInput({action:'confirm'}); assert.deepEqual(ui.confirmed,slots[0]);
  ui.handle.handleMenuInput({action:'edit'}); assert.deepEqual(ui.edited.borgIds,['a','b','c']);
  ui.handle.destroy();
});
test('UI blocks confirmation and identifies an empty second human; edit remains available', () => {
  const slots=[slot(['c']),slot(['e','c'],2)]; const ui=mount(slots,2);
  ui.handle.handleMenuInput({action:'confirm'}); assert.equal(ui.confirmed,undefined);
  const status=ui.container.querySelector('.gf-select-deployment');
  assert.equal(status.attrs.role,'status'); assert.equal(status.attrs['aria-live'],'polite');
  assert.match(status.textContent,/P2: No deployable Borg/);
  ui.handle.handleMenuInput({action:'right'}); ui.handle.handleMenuInput({action:'edit'});
  assert.deepEqual(ui.edited.borgIds,['e','c']); ui.handle.destroy();
});
test('UI repeatedly blocks an unknown lead, shows no fabricated Borg, then recovers on valid selection', () => {
  const ui=mount([slot(['unknown','c']),slot(['a','d'],2)]);
  for(let i=0;i<2;i++) ui.handle.handleMenuInput({action:'confirm'});
  assert.equal(ui.confirmed,undefined);
  assert.equal(ui.container.querySelector('.gf-select-pad').children.length,0);
  assert.match(ui.container.querySelector('.gf-select-deployment').textContent,/P1: No deployable Borg/);
  ui.handle.handleMenuInput({action:'right'}); ui.handle.handleMenuInput({action:'confirm'});
  assert.deepEqual(ui.confirmed.borgIds,['a','d']); ui.handle.destroy();
});
test('UI confirmation, session sync and fresh-page storage reload preserve over-budget tail', async () => {
  const slots=[slot(['a','b','c'])]; const {session}=makeSession(slots); enter(session);
  const ui=mount(structuredClone(slots),1,{
    onSlotsSynced:slots=>session.dispatch({type:'force-slots-synced',slots}),
    onConfirm:slot=>session.dispatch({type:'force-slot-confirm',slot}),
  });
  ui.handle.handleMenuInput({action:'confirm'});
  assert.equal(session.snapshot().screen,'briefing'); ui.handle.destroy();
  const storageGraph=emit('storage-revisit','apps/game/src/forceSlotStorage.ts',{'./ui/screens/SelectForce.js':'export {};'});
  const storage=await import(storageGraph.url);
  storage.saveForceSlots(session.snapshot().forceSlots);
  const restored=[slot([])]; storage.syncForceSlots(restored);
  assert.deepEqual(restored,slots);
  assert.deepEqual(JSON.parse(stored.get('gf-force-slots-v1')),slots);
});
