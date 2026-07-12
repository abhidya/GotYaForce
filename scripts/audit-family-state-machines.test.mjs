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

function portEvidence() {
  return Object.fromEntries([
    "rootDispatch", "variantDispatch", "phaseTransitions", "constants",
    "streamBehavior", "bridgeWiring", "focusedTests",
  ].map((field) => [field, [`fixture:${field}`]]));
}

function ported(constructorAddress, actionIndex, coverage) {
  return { constructorAddress, actionIndex, status: "ported", coverage };
}

function addMember(input, { id, constructorAddress = "0x80000000", variants = [0, 1] }) {
  const tableId = `t-${id}`;
  input.commandData.borgs[id] = { constructorAddress, tableId };
  input.commandData.tables[tableId] = {
    evidence: `fixture:${tableId}`,
    types: [{ type: 2, records: variants.map((variantIndex, i) => ({ address: `0x${20 + i}`, actionIndex: 2, variantIndex, disabled: false })) }],
  };
  input.actionData.borgs[id] = {
    constructorAddress,
    root: "0x20",
    actionTable: "0x30",
    actions: { 2: { handler: "0x40", variants: Object.fromEntries(variants.map((v) => [v, {}])) } },
  };
  input.implementationIds.add(id);
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
  assert.ok(audit.structuralErrors.some((x) => x.includes("requires explicit member and live-variant coverage")));
});

test("rejects false ported claims missing any independent completeness evidence", () => {
  const fields = Object.keys(portEvidence());
  for (const omitted of fields) {
    const input = fixture();
    const evidence = portEvidence();
    delete evidence[omitted];
    input.reviewed.classifications = [ported("0x80000000", 2, [{ member: "pl0000", variants: [], evidence }])];
    const audit = buildAudit(input);
    assert.ok(audit.structuralErrors.some((x) => x.includes(`requires ${omitted} evidence`)), omitted);
  }
});

test("rejects constructor promotion that omits a live member or live variant", () => {
  const input = fixture();
  addMember(input, { id: "pl0001", variants: [0, 1] });
  input.reviewed.classifications = [ported("0x80000000", 2, [
    { member: "pl0000", variants: [], evidence: portEvidence() },
  ])];
  let audit = buildAudit(input);
  assert.ok(audit.structuralErrors.some((x) => x.includes("does not cover live member pl0001")));

  input.reviewed.classifications[0].coverage.push({ member: "pl0001", variants: [0], evidence: portEvidence() });
  audit = buildAudit(input);
  assert.ok(audit.structuralErrors.some((x) => x.includes("do not match ROM-live variants [0,1]")));
});

function delegationFixture(targetStatus = "ported") {
  const input = fixture();
  addMember(input, { id: "pl0100", constructorAddress: "0x80000100", variants: [0] });
  const source = {
    constructorAddress: "0x80000000",
    actionIndex: 2,
    status: "delegated",
    target: { constructorAddress: "0x80000100", actionIndex: 2 },
    coverage: [{ member: "pl0000", variants: [], romDelegationEvidence: ["fixture:ROM branch to target"] }],
  };
  const target = targetStatus === "ported"
    ? ported("0x80000100", 2, [{ member: "pl0100", variants: [0], evidence: portEvidence() }])
    : { constructorAddress: "0x80000100", actionIndex: 2, status: targetStatus };
  input.reviewed.classifications = [source, target];
  return input;
}

test("rejects nonexistent and incomplete delegation targets", () => {
  let input = delegationFixture();
  const valid = buildAudit(input);
  assert.deepEqual(valid.structuralErrors, []);
  assert.deepEqual(valid.families[0].actions.find((x) => x.actionIndex === 2).classificationCoverage[0].romDelegationEvidence, ["fixture:ROM branch to target"]);
  input.reviewed.classifications[0].target.constructorAddress = "0xdeadbeef";
  let audit = buildAudit(input);
  assert.ok(audit.structuralErrors.some((x) => x.includes("targets nonexistent audited slot")));

  input = delegationFixture("partial");
  audit = buildAudit(input);
  assert.ok(audit.structuralErrors.some((x) => x.includes("targets incomplete slot")));
});

test("rejects delegation cycles", () => {
  const input = delegationFixture("delegated");
  input.reviewed.classifications[1] = {
    constructorAddress: "0x80000100",
    actionIndex: 2,
    status: "delegated",
    target: { constructorAddress: "0x80000000", actionIndex: 2 },
    coverage: [{ member: "pl0100", variants: [0], romDelegationEvidence: ["fixture:ROM return delegation"] }],
  };
  const audit = buildAudit(input);
  assert.ok(audit.structuralErrors.some((x) => x.includes("delegation cycle")));
});
