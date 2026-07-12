import assert from "node:assert/strict";
import test from "node:test";
import { buildAudit, exitCodeForAudit, stableStringify } from "./audit-family-state-machines.mjs";

function fixture() {
  const table = {
    evidence: "fixture:command-root",
    types: [{ type: 2, records: [
      { address: "0x10", actionIndex: 2, disabled: false },
      { address: "0x14", actionIndex: 3, disabled: true },
    ] }],
  };
  return {
    commandData: { borgs: { pl0000: { constructorAddress: "0x80000000", tableId: "t" } }, tables: { t: table } },
    actionData: { borgs: { pl0000: { constructorAddress: "0x80000000", root: "0x20", actionTable: "0x30", actions: { 2: { handler: "0x40" } } } } },
    implementationIds: new Set(["pl0000"]),
    reviewed: { classifications: [] },
  };
}

test("classifies registered live slots conservatively and ROM-disabled slots inactive", () => {
  const audit = buildAudit(fixture());
  assert.equal(audit.families[0].actions.find((x) => x.actionIndex === 2).status, "partial");
  const inactive = audit.families[0].actions.find((x) => x.actionIndex === 3);
  assert.equal(inactive.status, "inactive");
  assert.match(inactive.evidence[0], /0x14/);
});

test("default succeeds but strict fails when partial or missing live slots remain", () => {
  const audit = buildAudit(fixture());
  assert.equal(exitCodeForAudit(audit, false), 0);
  assert.equal(exitCodeForAudit(audit, true), 1);
});

test("output is deterministic across input insertion order", () => {
  const first = buildAudit(fixture());
  const reversed = fixture();
  reversed.commandData.borgs = Object.fromEntries(Object.entries(reversed.commandData.borgs).reverse());
  assert.equal(stableStringify(first), stableStringify(buildAudit(reversed)));
});

test("rejects duplicate reviewed classifications and evidence-free completion", () => {
  const input = fixture();
  input.reviewed.classifications = [
    { constructorAddress: "0x80000000", actionIndex: 2, status: "ported" },
    { constructorAddress: "0x80000000", actionIndex: 2, status: "partial" },
  ];
  const audit = buildAudit(input);
  assert.ok(audit.structuralErrors.some((x) => x.includes("duplicate constructor classification")));
  assert.ok(audit.structuralErrors.some((x) => x.includes("requires evidence")));
});
