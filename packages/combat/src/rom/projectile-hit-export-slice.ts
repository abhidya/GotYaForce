/** Explicit eight-byte projection of the committed pl0003 HIT export.
 * The generator pushes every remap byte until EXACT ff, without filtering;
 * therefore kind1=[1] proves a24=1,a25=ff under that generator's provenance.
 * Damage/start/end are direct integer reads. Rounded floats, padding and other
 * remaps are deliberately absent. This is not raw asset/full-table recovery or
 * independent archive authentication. The damage table body is not consumed.
 */
import attackData from '../data/attackHitTables.json' with {type: 'json'};
import damageData from '../data/familyDamageRecords.json' with {type: 'json'};
import type {SourceAllocationBytes} from './source-object-allocation.js';

export function createDoubleProjectileHitExportSlice(): {
  pointer27c: object; pointer3fc: SourceAllocationBytes;
} {
  const selected = attackData.borgs.pl0003, remap = selected.kinds['1'], row = selected.records['1'];
  if (remap.length !== 1 || remap[0] !== 1 || row.damageRecordIndex !== 1 || row.activeStart !== 0 || row.activeEnd !== -1)
    throw Error('[projectile-hit-export-slice] committed selected integer evidence changed');
  const binding = damageData.borgs.pl0003, damage = damageData.tables['0x8033b198'];
  if (binding.tableAddress !== '0x8033b198' || damage.address !== '0x8033b198')
    throw Error('[projectile-hit-export-slice] Double constructor damage-table provenance changed');
  // Preserve the actual derived table object as the explicit opaque27c owner.
  // No damage records are fetched and no raw body bytes are manufactured.
  const pointer3fc: SourceAllocationBytes = {0xa24: remap[0], 0xa25: 255};
  for (const [offset, value] of [[0xaf4,row.damageRecordIndex],[0xaf6,row.activeStart],[0xaf8,row.activeEnd]] as const) {
    const raw = value & 65535; pointer3fc[offset] = raw >>> 8; pointer3fc[offset + 1] = raw & 255;
  }
  return {pointer27c: damage, pointer3fc};
}
