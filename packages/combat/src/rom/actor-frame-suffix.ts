/** Bounded actual8006f88c,80055ee4,8005b880 and8005b98c, offline only.
 * Authenticated instruction/cell/scalar evidence:
 * research/decomp/frame-suffix-evidence-2026-11-14.md and
 * research/decomp/sound-event-helper-evidence-2026-11-14.md.
 * Existing actual fields and genuine prehook/attribute/status/gauge/animation
 * owners remain live. Only missing8cc/1eb/276 are copied/sealed, with no defaults.
 * Posthook's Sasuke6e9 path and reached sound calleesf036c/f061c remain boundaries.
 * Null4e8, four explicit signed auxiliary37==-1 values, and terminated
 * nonfiring/ignored-kind event chains genuinely return;
 * none is manufactured. Constructor802d3b48 is NONNULL802d3ca0, so an explicit
 * null fixture is not retail sound hydration. No frame completion/release occurs
 * here. Source failures permanently latch the shared Double lifecycle.
 * Stable synchronous non-proxy own-data owners, finite exact binary32 RN00/NI0,
 * and bounded decoded byte arrays are host bounds, not original execution proof.
 */
import type {RomActor} from './actor.js';
import {getDoubleNinjaOwnerState, type DoubleNinjaOwnerState} from '../ninjaX.js';
import {isSourceActorDoublePrehookRuntime, markIncompleteSourceActorDoubleLifecycle,
  requireCompleteSourceActorDoubleLifecycle, requireSourceActorDoubleInvocation, type SourceActorDoublePrehookRuntime} from './actor-double-prehook.js';
import {isSourceActorGaugeScaleRuntime, type SourceActorGaugeScaleRuntime} from './actor-gauge-scale.js';
import {isSourceActorAnimationDispatchRuntime, type SourceActorAnimationDispatchRuntime} from './actor-animation-dispatch.js';
import {isSourceActorJointMappingRuntime} from './actor-joint-mapping.js';
import {isSourceJointAnimationFeedbackRuntime} from './joint-animation-feedback.js';
import {isSourceAnimationSetupMetadataRuntime, type SourceAnimationSetupMetadataRuntime} from './animation-setup-metadata.js';
import {requireCompleteSourceActorAnimationTransition} from './actor-animation-transition.js';
import {addSourceFloat32} from './source-float.js';
import {isSourceActorSoundTable,readSourceActorSoundTableByte,type SourceActorSoundEventTable} from './actor-sound-table.js';

export interface SourceActorFrameSuffixBinding {byte8cc: number; byte1eb: number; byte276: number}
export interface SourceActorFrameSuffixSources {
  prehook: SourceActorDoublePrehookRuntime;
  gauges: SourceActorGaugeScaleRuntime;
  dispatch: SourceActorAnimationDispatchRuntime;
  metadata?: SourceAnimationSetupMetadataRuntime;
}
export interface SourceActorFrameSuffixRuntime {
  bindActor(identity: symbol, initial: Readonly<Partial<SourceActorFrameSuffixBinding>>): void;
  getActualActor(identity: symbol): RomActor;
  getMappingActor(identity: symbol): object;
  getWorldBinding(identity: symbol): object;
  getAttributeBinding(identity: symbol): object;
  getStatusBinding(identity: symbol): object;
  getGaugeBinding(identity: symbol): object;
  getDispatchBinding(identity: symbol): object;
  getPrehookBinding(identity: symbol): object;
  getActorBinding(identity: symbol): Partial<SourceActorFrameSuffixBinding>;
  getPrehookRuntime(): SourceActorDoublePrehookRuntime;
  getGaugeRuntime(): SourceActorGaugeScaleRuntime;
  getDispatchRuntime(): SourceActorAnimationDispatchRuntime;
  getSourceOwners(identity: symbol): readonly object[];
  assertActorComplete(identity: symbol): void;
  runPosthook(identity: symbol): void;
  runHousekeeping(identity: symbol): void;
  runSoundEvents(identity: symbol): void;
}
const genuine = new WeakSet<object>(), claimed = new WeakSet<object>();
export function isSourceActorFrameSuffixRuntime(value: unknown): value is SourceActorFrameSuffixRuntime {
  return value !== null && typeof value === 'object' && genuine.has(value);
}
function fail(reason: string): never {
  throw Error(`[actor-frame-suffix] ${reason}; offline execution aborted, prior writes/effects are not rolled back`);
}
function own(owner: unknown, key: string, writable = false): unknown {
  if (owner === null || typeof owner !== 'object') fail(`${key}: own data record required`);
  const p = Object.getOwnPropertyDescriptor(owner, key);
  if (!p || !('value' in p)) fail(`${key}: own data property required`);
  if (writable && !p.writable) fail(`${key}: non-writable field is unsupported`);
  return p.value;
}
function integer(value: unknown, min: number, max: number, where: string): number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < min || value > max) fail(`${where}: integer out of bounds`);
  return value === 0 ? 0 : value;
}
function float(value: unknown, where: string): number {
  if (typeof value !== 'number' || !Number.isFinite(value) || !Object.is(value, Math.fround(value)))
    fail(`${where}: finite exact source float32 required`);
  return value;
}
export function createSourceActorFrameSuffixRuntime(sources: SourceActorFrameSuffixSources): SourceActorFrameSuffixRuntime {
  const prehook = own(sources, 'prehook'), gauges = own(sources, 'gauges'), dispatch = own(sources, 'dispatch');
  if (!isSourceActorDoublePrehookRuntime(prehook)) fail('genuine source Double prehook required');
  if (!isSourceActorGaugeScaleRuntime(gauges)) fail('genuine source gauge runtime required');
  if (!isSourceActorAnimationDispatchRuntime(dispatch)) fail('genuine source animation dispatch required');
  const mapping = dispatch.getActualMapping(), feedback = dispatch.getActualFeedback();
  if (!isSourceActorJointMappingRuntime(mapping) || !isSourceJointAnimationFeedbackRuntime(feedback) || mapping.getActualFeedback() !== feedback)
    fail('genuine matched source mapping/feedback required');
  const metadata = Object.getOwnPropertyDescriptor(sources, 'metadata') === undefined ? undefined : own(sources, 'metadata');
  if (metadata !== undefined && (!isSourceAnimationSetupMetadataRuntime(metadata) ||
    metadata.getActualMapping() !== mapping || metadata.getActualFeedback() !== feedback)) fail('genuine matched source metadata required');
  let busy = false, poisoned = false;
  const check = (): void => {if (poisoned) fail('caught same-runtime reentry');};
  const guard = <T>(run: () => T): T => {
    if (busy) {poisoned = true; fail('same-runtime reentry unsupported');}
    busy = true; poisoned = false;
    try {const result = run(); check(); return result;} finally {busy = false;}
  };
  const read = (owner: unknown, key: string): unknown => {const result = own(owner, key); check(); return result;};
  const write = (owner: object, key: string, value: number): void => {
    own(owner, key, true); check(); (owner as Record<string, unknown>)[key] = value; check();
  };
  const invoke = <T>(run: () => T): T => {const result = run(); check(); return result;};
  const record = (value: unknown, where: string): object => {
    if (value === null || typeof value !== 'object' || value instanceof Promise) fail(`${where}: synchronous actual record required`);
    return value;
  };
  const byte = (owner: object, key: string): number => integer(read(owner, key), 0, 255, key);
  const signed = (owner: object, key: string): number => byte(owner, key) << 24 >> 24;
  const word = (owner: object, key: string): number => integer(read(owner, key), 0, 0xffffffff, key);
  const f = (owner: object, key: string): number => float(read(owner, key), key);
  const same = (value: unknown, expected: object, where: string): void => {check(); if (value !== expected) fail(`${where}: canonical owner changed or differs`);};
  interface SoundPart {id: symbol; metadata?: object; feedback: object; dispatch?: object}
  interface Entry {
    actual: RomActor; mapping: object; world: object; attribute: object; status: object; gauge: object;
    prehook: object; dispatch: object; binding: Partial<SourceActorFrameSuffixBinding>;
    clone?: DoubleNinjaOwnerState; layout?: object; row?: object; metadataActor?: object; parts: SoundPart[];
  }
  const actors = new Map<symbol, Entry>(), assigned = new WeakSet<object>(), admitted = new WeakSet<object>();
  const entry = (id: symbol): Entry => {const e = actors.get(id); if (!e) fail('unknown/non-owned suffix actor'); return e;};
  const baseOwners = (e: Entry): object[] => [e.actual,e.mapping,e.world,e.attribute,e.status,e.gauge,e.prehook,e.dispatch,e.binding,
    ...(e.clone === undefined ? [] : [e.clone]), ...(e.metadataActor === undefined ? [] : [e.metadataActor]),
    ...e.parts.flatMap(part => [...(part.metadata === undefined ? [] : [part.metadata]),part.feedback,...(part.dispatch === undefined ? [] : [part.dispatch])])];
  // Genuine metadata/dispatch getters expose no presence query. During owner
  // enumeration only, an unbound part is absence rather than a source failure.
  // No numeric field is consumed. A reached sound row still requires that owner.
  const optionalOwner = (get: () => object, missing: string): object | undefined => {
    try {return record(invoke(get),'optional sound owner');} catch (error) {
      check(); if (!(error instanceof Error) || !error.message.startsWith(missing)) throw error;
      return undefined;
    }
  };
  const discoverSoundOwners = (e: Entry): void => {
    if (metadata === undefined) return;
    for (const part of e.parts) {
      for (const [key,get,missing] of [
        ['metadata',() => metadata.getPartBinding(part.id),'[animation-setup-metadata] unknown/non-owned metadata part;'],
        ['dispatch',() => dispatch.getPartBinding(part.id),'[actor-animation-dispatch] unknown/non-owned part binding;'],
      ] as const) {
        const current = optionalOwner(get,missing), retained = part[key];
        if (retained !== undefined) same(current,retained,`sound ${key}`);
        else if (current !== undefined) {
          if (baseOwners(e).includes(current) || assigned.has(current)) fail(`sound ${key} storage owner alias`);
          part[key] = current; if (admitted.has(e)) assigned.add(current);
        }
      }
    }
  };
  const extraOwners = (id: symbol, e: Entry): object[] => {
    discoverSoundOwners(e);
    const owners = [...invoke(() => prehook.getSourceOwners(id)), ...baseOwners(e)];
    if (e.layout !== undefined) owners.push(e.layout);
    if (e.row !== undefined) owners.push(e.row);
    // Descriptor inspection excludes raw aliases without consuming numeric sound
    // data or interpreting a null placeholder as a constructor pointer.
    const sound = Object.getOwnPropertyDescriptor(e.actual, 'soundEventTable'); check();
    if (sound && 'value' in sound && sound.value !== null && typeof sound.value === 'object') owners.push(sound.value);
    return [...new Set(owners)];
  };
  const noShadows = (id: symbol, e: Entry): void => {
    const canonical = new Map<string, object | undefined>([
      ['controlWord',e.actual],['borgNumber',e.actual],['modelScale',e.actual],['sizeScale',e.actual],['soundEventTable',e.actual],
      ['pointer4c0',e.prehook],['byte87',e.attribute],['short272',e.status],['byte7c9',e.gauge],
      ['byte8cc',e.binding],['byte1eb',e.binding],['byte276',e.binding],['arm7c8',e.clone],['offset7b0',e.clone],
    ]);
    for (const owner of extraOwners(id, e)) {
      for (const [key, expected] of canonical) if (owner !== expected && Object.getOwnPropertyDescriptor(owner,key) !== undefined)
        fail(`${key}: competing suffix storage owner`);
      for (const key of ['flags5e0','field5e0','byte3e8','short3e8','field4c0','soundEventTable4e8','field4e8',
        'field87','byte272','field272','field7c9','byte7c8','clone7c8','field7b0','field8cc','field1eb','field276'])
        if (Object.getOwnPropertyDescriptor(owner,key) !== undefined) fail(`${key}: competing suffix storage alias`);
    }
    if (e.parts.length !== 0) {
      const partFields = new Map<string, Set<object>>([
        ['auxiliary37',new Set(e.parts.flatMap(part => part.metadata === undefined ? [] : [part.metadata]))],
        ...(['elapsed08','previous10','previous14'] as const).map(key => [key,new Set(e.parts.flatMap(part => part.dispatch === undefined ? [] : [part.dispatch]))] as [string,Set<object>]),
        ...(['frame0c','duration24'] as const).map(key => [key,new Set(e.parts.map(part => part.feedback))] as [string,Set<object>]),
      ]);
      for (const owner of extraOwners(id,e)) for (const [key,expected] of partFields)
        if (!expected.has(owner) && Object.getOwnPropertyDescriptor(owner,key) !== undefined) fail(`${key}: competing sound part owner`);
    }
    check();
  };
  const reconcile = (id: symbol, e: Entry): void => {
    requireCompleteSourceActorDoubleLifecycle(e.actual); requireCompleteSourceActorAnimationTransition(e.mapping); check();
    invoke(() => prehook.assertActorComplete(id));
    same(invoke(() => prehook.getActualActor(id)),e.actual,'prehook actual');
    same(invoke(() => prehook.getMappingActor(id)),e.mapping,'prehook mapping');
    same(invoke(() => prehook.getWorldBinding(id)),e.world,'prehook world');
    same(invoke(() => prehook.getAttributeBinding(id)),e.attribute,'prehook attribute');
    same(invoke(() => prehook.getStatusBinding(id)),e.status,'prehook status');
    same(invoke(() => prehook.getActorBinding(id)),e.prehook,'prehook pointer');
    same(invoke(() => gauges.getActualActor(id)),e.actual,'gauge actual');
    same(invoke(() => gauges.getWorldBinding(id)),e.world,'gauge world');
    same(invoke(() => gauges.getStatusBinding(id)),e.status,'gauge status');
    same(invoke(() => gauges.getActorBinding(id)),e.gauge,'gauge binding');
    same(invoke(() => dispatch.getSourceActor(id)),e.mapping,'dispatch mapping');
    same(invoke(() => mapping.getActor(id)),e.mapping,'mapping actual');
    same(invoke(() => dispatch.getActorBinding(id)),e.dispatch,'dispatch binding');
    const clone = getDoubleNinjaOwnerState(e.actual); check();
    if (e.clone !== undefined && clone !== e.clone) fail('persistent clone owner changed');
    if (e.clone === undefined && clone !== undefined) {
      record(clone,'clone owner'); if (assigned.has(clone)) fail('persistent clone owner aliases another owner');
      e.clone = clone; if (actors.has(id)) assigned.add(clone);
    }
    if (metadata !== undefined) {
      same(invoke(() => metadata.getActualMapping()),mapping,'metadata mapping');
      same(invoke(() => metadata.getActualFeedback()),feedback,'metadata feedback');
      same(invoke(() => mapping.getLayout(id)),e.layout!,'sound layout');
      same(read(read(e.layout,'parts'),'0'),e.row!,'sound row');
      same(invoke(() => metadata.getActorBinding(id)),e.metadataActor!,'metadata actor');
      for (let index = 0; index < e.parts.length; index++) {
        const part = e.parts[index]!;
        if (read(e.row,String(index)) !== part.id) fail('sound part identity changed');
        if (part.metadata !== undefined) same(invoke(() => metadata.getPartBinding(part.id)),part.metadata,'sound metadata');
        same(invoke(() => feedback.getPart(part.id)),part.feedback,'sound feedback');
        if (part.dispatch !== undefined) same(invoke(() => dispatch.getPartBinding(part.id)),part.dispatch,'sound dispatch');
      }
    }
    noShadows(id,e);
  };
  const source = (id: symbol, operation: 'posthook' | 'housekeeping' | 'sound', body: (e: Entry) => void): void => guard(() => {
    const e = entry(id); requireCompleteSourceActorDoubleLifecycle(e.actual);
    requireSourceActorDoubleInvocation(e.actual,operation,runtime);
    try {reconcile(id,e); body(e); check();} catch (error) {markIncompleteSourceActorDoubleLifecycle(e.actual); throw error;}
  });
  // Bounded archived5b98c predicates and dispatch, with both audio calls refused.
  // Arithmetic assumes the stated finite binary32 RN00/NI0 bounds.
  // The eager80437418 f64 bias (2^52),804373e4 f32 +0 and repeated fsubs
  // convert the single lhz frame exactly: every u16 is representable as f32.
  // These authenticated fixed scalars are code evidence, not injected owners.
  const soundByte = (table: SourceActorSoundEventTable, offset: number): number =>
    invoke(() => readSourceActorSoundTableByte(table,offset));
  const soundEvent = (actual: RomActor, table: SourceActorSoundEventTable, offset: number, now: number, previous: number): void => {
    const halfword = (at: number): number => soundByte(table,at) * 256 + soundByte(table,at + 1);
    const frame = halfword(offset);
    if (frame === 0 ? now > 0 : now < frame || previous >= frame) return;
    const kind = soundByte(table,offset + 3); // lbz: even0xff is unsigned255.
    if (kind >= 4) return;
    let soundId: number;
    if (kind === 1) {
      // One actualb4 load, before the id. Lower8043740c=3f333333;
      // upper80437410=40000000 is reached only after the lower comparison.
      const scale = f(actual,'modelScale');
      if (scale < 0.699999988079071) soundId = (halfword(offset + 4) - 1) >>> 0;
      else if (scale > 2) soundId = (halfword(offset + 4) + 1) >>> 0;
      else soundId = halfword(offset + 4);
    } else soundId = halfword(offset + 4);
    // addi uses the whole32-bit register, never a second u16 truncation.
    // For2/3 the id load precedes scalar80437404=3e4ccccd. No audio callback
    // substitutes for either genuine unresolved source callee.
    const operands = `sound event at byte${offset} (current=${now}, previous=${previous}, kind=${kind}, soundId=${soundId}`;
    if (kind < 2) fail(`8005b98c reached unsupported actual800f036c ${operands}); no audio effect executed`);
    fail(`8005b98c reached unsupported actual800f061c ${operands}, scalar=0.20000000298023224); no audio effect executed`);
  };
  const runtime: SourceActorFrameSuffixRuntime = {
    bindActor(id,initial) {guard(() => {
      if (typeof id !== 'symbol' || actors.has(id)) fail('new symbol actor identity required');
      const actual = record(invoke(() => prehook.getActualActor(id)),'actual actor') as RomActor;
      requireCompleteSourceActorDoubleLifecycle(actual);
      if (claimed.has(actual)) fail('actual actor already claimed by source suffix runtime');
      record(initial,'initial suffix binding');
      const binding: Partial<SourceActorFrameSuffixBinding> = {};
      for (const key of ['byte8cc','byte1eb','byte276'] as const)
        if (Object.getOwnPropertyDescriptor(initial,key) !== undefined) binding[key] = byte(initial,key);
      const e: Entry = {actual,binding:Object.seal(binding),parts:[],
        mapping:record(invoke(() => prehook.getMappingActor(id)),'mapping'),world:record(invoke(() => prehook.getWorldBinding(id)),'world'),
        attribute:record(invoke(() => prehook.getAttributeBinding(id)),'attributes'),status:record(invoke(() => prehook.getStatusBinding(id)),'status'),
        gauge:record(invoke(() => gauges.getActorBinding(id)),'gauge'),prehook:record(invoke(() => prehook.getActorBinding(id)),'prehook'),
        dispatch:record(invoke(() => dispatch.getActorBinding(id)),'dispatch')};
      if (metadata !== undefined) {
        e.layout = record(invoke(() => mapping.getLayout(id)),'layout'); e.row = record(read(read(e.layout,'parts'),'0'),'part row');
        e.metadataActor = record(invoke(() => metadata.getActorBinding(id)),'metadata actor');
        for (let index = 0; index < 4; index++) {
          const part = read(e.row,String(index)); if (typeof part !== 'symbol') fail('sound part: owned symbol required');
          e.parts.push({id:part,feedback:record(invoke(() => feedback.getPart(part)),'part feedback')});
        }
      }
      reconcile(id,e);
      const owners = baseOwners(e);
      if (new Set(owners).size !== owners.length || owners.some(owner => assigned.has(owner))) fail('suffix source storage owner alias');
      check(); actors.set(id,e); admitted.add(e); owners.forEach(owner => assigned.add(owner)); claimed.add(actual);
    });},
    getActualActor(id) {return entry(id).actual;},getMappingActor(id) {return entry(id).mapping;},getWorldBinding(id) {return entry(id).world;},
    getAttributeBinding(id) {return entry(id).attribute;},getStatusBinding(id) {return entry(id).status;},getGaugeBinding(id) {return entry(id).gauge;},
    getDispatchBinding(id) {return entry(id).dispatch;},getPrehookBinding(id) {return entry(id).prehook;},getActorBinding(id) {return entry(id).binding;},
    getPrehookRuntime() {return prehook;},getGaugeRuntime() {return gauges;},getDispatchRuntime() {return dispatch;},
    getSourceOwners(id) {return guard(() => Object.freeze(extraOwners(id,entry(id))));},
    assertActorComplete(id) {guard(() => reconcile(id,entry(id)));},
    runPosthook(id) {source(id,'posthook',e => {
      const target = word(e.prehook,'pointer4c0');
      if (target !== 0x8006f88c) fail(`unsupported actual4c0 target0x${target.toString(16)}`);
      if ((word(e.actual,'controlWord') & 0x02000000) !== 0) {
        if (e.clone === undefined) fail('actual7c8 requires existing explicit persistent clone owner');
        write(e.clone,'arm7c8',0);
      }
      const borg = integer(read(e.actual,'borgNumber'),0,65535,'borgNumber') << 16 >> 16;
      if (borg !== 10) return;
      fail('8006f88c reached unsupported Sasuke actual6e9 owner before actual6ec increment');
    });},
    runHousekeeping(id) {source(id,'housekeeping',e => {
      write(e.attribute,'byte87',(word(e.actual,'controlWord') >>> 6) & 1);
      const mode = signed(e.binding,'byte8cc');
      if (mode === 1) write(e.binding,'byte1eb',0);
      else if (mode === 0) {
        // Archived loads: size7fc then modelb4, one fmuls, ordered comparison2.
        const size = f(e.actual,'sizeScale'), model = f(e.actual,'modelScale');
        const product = float(Math.fround(size * model),'fmuls result');
        write(e.binding,'byte1eb',product < 2 ? 1 : 0);
      } else write(e.binding,'byte1eb',1);
      write(e.binding,'byte276',(word(e.actual,'controlWord') & 0x20000000) !== 0 ? 1 : 0);
      if (signed(e.gauge,'byte7c9') === 0) return;
      const previous = integer(read(e.status,'short272'),-32768,32767,'short272');
      write(e.status,'short272',(previous | 65535) << 16 >> 16);
    });},
    runSoundEvents(id) {source(id,'sound',e => {
      const table = read(e.actual,'soundEventTable');
      if (table === null) return;
      if (!(ArrayBuffer.isView(table) && table instanceof Uint8Array) && !isSourceActorSoundTable(table)) fail('actual4e8 requires explicit decoded sound table or null');
      if (metadata === undefined) fail('8005b8b4 requires actual signed auxiliary37 metadata owner');
      for (let index = 0; index < 4; index++) {
        const part = e.parts[index]!;
        const metadataOwner = record(invoke(() => metadata.getPartBinding(part.id)),'sound metadata');
        if (part.metadata !== undefined) same(metadataOwner,part.metadata,'sound metadata');
        else fail('sound metadata owner was not retained by source owner reconciliation');
        const selector = signed(metadataOwner,'auxiliary37');
        if (selector === -1) continue;
        const current = read(e.actual,'soundEventTable');
        if (!(ArrayBuffer.isView(current) && current instanceof Uint8Array) && !isSourceActorSoundTable(current)) fail('fresh actual4e8 requires explicit decoded nonnull sound table');
        if (selector < 0) fail(`8005b8cc unsupported negative sound event index ${selector}`);
        let offset = selector * 8;
        for (;;) {
          // Keep this row's captured4e8 pointer through every helper return.
          // Both byte2 and the selected clock pair are loaded again per record.
          const mode = soundByte(current,offset + 2);
          const dispatchPart = record(invoke(() => dispatch.getPartBinding(part.id)),'sound dispatch');
          if (part.dispatch === undefined) {
            if (baseOwners(e).includes(dispatchPart) || assigned.has(dispatchPart)) fail('sound dispatch storage owner alias');
            part.dispatch = dispatchPart; assigned.add(dispatchPart);
          } else same(dispatchPart,part.dispatch,'sound dispatch');
          let now: number, previous: number;
          if (mode === 0) {now = f(dispatchPart,'elapsed08'); previous = f(dispatchPart,'previous10');}
          else {
            now = f(part.feedback,'frame0c'); previous = f(dispatchPart,'previous14');
            if (now < previous) {
              const duration = integer(read(part.feedback,'duration24'),-32768,32767,'duration24');
              now = addSourceFloat32(now,duration);
            }
          }
          soundEvent(e.actual,current,offset,now,previous);
          // 5b948 lbz+6,5b94c addi pointer+8,5b950 extsb: the marker is
          // consumed only after a genuine callee return; it is not an index.
          const marker = soundByte(current,offset + 6);
          offset += 8;
          if ((marker << 24 >> 24) === -1) break;
        }
      }
    });},
  };
  genuine.add(runtime); return Object.freeze(runtime);
}
