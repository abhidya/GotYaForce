/** Bounded offline scalar receiver of TObjUpdateFunc (8023e0c4).
 * Source: chunk_0069.c:6753–6950. Only tracks 2–8 are admitted: two
 * translation, two scale and three rotation stores, followed by the unconditional
 * flags+4c |= 80000000 write. Image, palette, color, material and all other tracks
 * explicitly refuse, including source no-ops outside this bounded domain.
 * No full TObj receiver, texture matrices, original replay or live game wiring.
 *
 * Factory inputs must be non-proxy own-data records; accessors are never invoked.
 * Every field is required and copied into a sealed, owned mutable data record.
 * Symbols identify those records, not RAM pointers. The method table is frozen.
 * Scalar copies accept finite source f32, preserving signed zero, subnormals and
 * finite extremes without FP arithmetic. This makes no NI=1 arithmetic-parity
 * claim for any composed FObj/AObj helper.
 *
 * Null owner returns before inspecting other arguments. For a supported track,
 * validate the new scalar and the target's writable own-data property, then store
 * without reading its overwritten value. Only afterward inspect flags4c's writable
 * own-data property and uint32 value, then OR the dirty bit. Unrelated scalars are
 * not read or preflighted. Invalid/readonly fields and unknown owner identities
 * are host-domain refusals, not retail branches. A flags refusal retains the
 * completed scalar store; there is no whole-record preflight or rollback.
 */
export interface SourceTObjScalarHeader {
  flags4c: number;
  rotation18: number;
  rotation1c: number;
  rotation20: number;
  scale28: number;
  scale2c: number;
  translation34: number;
  translation38: number;
}
export interface SourceTObjScalarRuntime {
  createTexture(initial: SourceTObjScalarHeader): symbol;
  getTexture(identity: symbol): SourceTObjScalarHeader;
  updateScalar(owner: symbol | null, track: number, value: number): void;
}
const scalars = ['rotation18', 'rotation1c', 'rotation20', 'scale28', 'scale2c',
  'translation34', 'translation38'] as const;
const keys = ['flags4c', ...scalars] as const;
type Scalar = typeof scalars[number];
function fail(reason: string): never {
  throw Error(`[tobj-update] ${reason}; offline execution aborted, prior writes are not rolled back`);
}
function float32(value: unknown, where: string): asserts value is number {
  if (!Number.isFinite(value) || !Object.is(value, Math.fround(value as number))) {
    fail(`${where}: expected finite source float32`);
  }
}
function uint32(value: unknown): asserts value is number {
  if (typeof value !== 'number' || !Number.isInteger(value) || value < 0 || value > 0xffffffff) {
    fail('flags4c: expected uint32');
  }
}
function ownData(record: object, key: string, writable: boolean): PropertyDescriptor {
  const property = Object.getOwnPropertyDescriptor(record, key);
  if (!property || !('value' in property)) fail(`${key}: own data property required`);
  if (writable && !property.writable) fail(`${key}: non-writable field is unsupported`);
  return property;
}
function scalarForTrack(track: number): Scalar {
  switch (track) {
    case 2: return 'translation34';
    case 3: return 'translation38';
    case 4: return 'scale28';
    case 5: return 'scale2c';
    case 6: return 'rotation18';
    case 7: return 'rotation1c';
    case 8: return 'rotation20';
    default: fail('unsupported scalar track');
  }
}
export function createSourceTObjScalarRuntime(): SourceTObjScalarRuntime {
  const textures = new Map<symbol, SourceTObjScalarHeader>();
  const getTexture = (identity: symbol): SourceTObjScalarHeader => {
    const texture = textures.get(identity);
    if (!texture) fail('unknown/non-owned texture identity');
    return texture;
  };
  return Object.freeze({
    createTexture(initial: SourceTObjScalarHeader): symbol {
      if (initial === null || typeof initial !== 'object') fail('initial texture data record required');
      const copied: Partial<SourceTObjScalarHeader> = {};
      for (const key of keys) {
        const value: unknown = ownData(initial, key, false).value;
        if (key === 'flags4c') uint32(value); else float32(value, key);
        Object.defineProperty(copied, key, {value, writable: true, enumerable: true});
      }
      const identity = Symbol('owned scalar TObj');
      textures.set(identity, Object.seal(copied) as SourceTObjScalarHeader);
      return identity;
    },
    getTexture,
    updateScalar(owner: symbol | null, track: number, value: number): void {
      if (owner === null) return;
      const texture = getTexture(owner);
      const field = scalarForTrack(track);
      float32(value, 'callback value');
      ownData(texture, field, true);
      texture[field] = value;
      const flags: unknown = ownData(texture, 'flags4c', true).value;
      uint32(flags);
      texture.flags4c = (flags | 0x80000000) >>> 0;
    },
  });
}
