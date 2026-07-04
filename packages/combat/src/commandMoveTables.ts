import commandMoveTablesData from "./data/commandMoveTables.json" with { type: "json" };

export type RuntimeCommandMoveButton = "B Shot" | "B Attack" | "B Charge" | "X" | "X Charge";

export interface CommandMoveTableCoverage {
  rosterBorgs: number;
  exactCommandTableBorgs: number;
  decodedTables: number;
  directCommandTableSources?: number;
  derivedConstructorVectorSources?: number;
}

export interface CommandMoveTableAssignment {
  id: string;
  name: string;
  borgNumber: string;
  family: number;
  variant: number;
  constructorFamilyTable: string;
  constructorAddress: string;
  tableId: string | null;
  exactCommandTable: boolean;
  commandTableResolution?: string | null;
  commandTableEvidence?: string | null;
  pointerLabelAddress?: string | null;
  commandStructAddress?: string | null;
}

export interface CommandMoveRecord {
  tableId: string;
  tableName: string;
  evidence: string;
  commandStructAddress: string;
  rootAddress: string;
  commandType: number;
  commandContext: string;
  mode: number;
  modeName: string;
  subtype: number;
  direction: number | null;
  address: string;
  bytes: readonly [number, number, number, number];
  disabled: boolean;
  cueId: number;
  stateMode: number;
  actionIndex: number;
  variantIndex: number;
}

interface RawCommandMoveData {
  _meta: { coverage: CommandMoveTableCoverage };
  borgs: Record<string, CommandMoveTableAssignment>;
  tables: Record<string, RawCommandTable>;
}

interface RawCommandTable {
  id: string;
  name: string;
  rootAddress: string;
  commandStructAddress: string;
  evidence: string;
  types: RawCommandType[];
}

interface RawCommandType {
  type: number;
  mode: number;
  modeName: string;
  records: RawCommandRecord[];
}

interface RawCommandRecord {
  subtype: number;
  direction: number | null;
  address: string;
  bytes: number[];
  disabled: boolean;
  cueId: number;
  stateMode: number;
  actionIndex: number;
  variantIndex: number;
}

const DATA = commandMoveTablesData as RawCommandMoveData;

const BUTTON_COMMAND_TYPES: Readonly<Record<RuntimeCommandMoveButton, { commandType: number; context: string }>> = {
  "B Shot": {
    commandType: 0,
    context: "B far/no target-proximity path (zz_0069a88_ writes actor+0x585 = 0)",
  },
  "B Attack": {
    commandType: 1,
    context: "B close/target-proximity path (zz_0069a88_/zz_0069b10_ write actor+0x585 = 1)",
  },
  X: {
    commandType: 2,
    context: "secondary/X path (zz_0069b98_ writes actor+0x585 = 2)",
  },
  "B Charge": {
    commandType: 3,
    context: "charged path (zz_0069bf0_ writes actor+0x585 = 3)",
  },
  "X Charge": {
    commandType: 5,
    context: "ranged/target-forced path (zz_0069c50_/zz_0069cb0_ write actor+0x585 = 5)",
  },
};

export function commandMoveTableCoverage(): CommandMoveTableCoverage {
  return DATA._meta.coverage;
}

export function commandMoveTableAssignmentForBorgId(id: string): CommandMoveTableAssignment | null {
  return DATA.borgs[id.toLowerCase()] ?? null;
}

export function hasExactCommandMoveTableForBorgId(id: string): boolean {
  return commandMoveTableAssignmentForBorgId(id)?.exactCommandTable === true;
}

export function commandMoveRecordsForBorgButton(
  id: string,
  button: RuntimeCommandMoveButton,
): CommandMoveRecord[] {
  const assignment = commandMoveTableAssignmentForBorgId(id);
  if (!assignment?.tableId) return [];

  const table = DATA.tables[assignment.tableId];
  const spec = BUTTON_COMMAND_TYPES[button];
  if (!table || !spec) return [];

  const typeEntry = table.types.find((entry) => entry.type === spec.commandType);
  if (!typeEntry) return [];

  return typeEntry.records
    .filter((record) => !record.disabled)
    .map((record) => ({
      tableId: table.id,
      tableName: table.name,
      evidence: table.evidence,
      commandStructAddress: table.commandStructAddress,
      rootAddress: table.rootAddress,
      commandType: typeEntry.type,
      commandContext: spec.context,
      mode: typeEntry.mode,
      modeName: typeEntry.modeName,
      subtype: record.subtype,
      direction: record.direction,
      address: record.address,
      bytes: tuple4(record.bytes),
      disabled: record.disabled,
      cueId: record.cueId,
      stateMode: record.stateMode,
      actionIndex: record.actionIndex,
      variantIndex: record.variantIndex,
    }));
}

export function commandMoveRecordSummaryForBorgButton(
  id: string,
  button: RuntimeCommandMoveButton,
): string | null {
  const records = commandMoveRecordsForBorgButton(id, button);
  const first = records[0];
  if (!first) return null;
  const actions = [...new Set(records.map((record) => record.actionIndex))].join(",");
  const variants = [...new Set(records.map((record) => record.variantIndex))].join(",");
  return `t${first.commandType} ${first.modeName} ${records.length} records action[${actions}] variant[${variants}]`;
}

function tuple4(values: number[]): [number, number, number, number] {
  return [values[0] ?? 0, values[1] ?? 0, values[2] ?? 0, values[3] ?? 0];
}
