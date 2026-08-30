// boundary.mjs — machinery shared by the two CALLEE-BOUNDARY replay standards.
//
// Two harnesses replay a captured callee boundary rather than a write set:
//   run-spine.mjs       standard boundary_green   — NONTERMINATING spine functions
//   run-transcript.mjs  standard transcript_green — ORDINARY (returning) functions
// Both stub every out-of-unit callee, assert the calls arrive in the captured
// order with the captured arguments, apply the callee's captured memory deltas,
// and return the captured return value. They differ only in how a run is
// terminated (iteration/call cap vs. the function's own return), in whether a
// return value is part of the claim, and in whether the corpus is one long run
// or N independent cases.
//
// This module holds the parts that are IDENTICAL between them, so the two
// standards cannot drift apart in their notion of "same argument" or "same
// callee". Everything that differs — the divergence WORDING, the verdict token,
// the result-artifact `standard` field — deliberately stays in each runner, so
// no refactor here can make one standard's evidence readable as the other's.
//
// NOTHING in this file decides a verdict. It formats, compares and reads.
import fs from "node:fs";
import path from "node:path";
import { createHash } from "node:crypto";
import { execSync } from "node:child_process";

export const sha256 = (buf) => createHash("sha256").update(buf).digest("hex");

export const hex = (v) => "0x" + (v >>> 0).toString(16);

/** Parse a "0x…" (or bare-hex) address. `onBad` is the caller's fatal handler. */
export const parseAddr = (s, onBad) => {
  const v = typeof s === "number" ? s : Number.parseInt(s, 16);
  if (!Number.isInteger(v) || v < 0) onBad(`bad address ${s}`);
  return v >>> 0;
};

/**
 * BOXED float: {"t":"f64"|"f32","bits":"<hex>"}. JSON cannot spell NaN or
 * Infinity, and a PowerPC argument register carrying residue is routinely one
 * of them — so a non-finite captured float travels bit-exact in this box and is
 * unboxed here. NOTE: JS canonicalises NaN, so a boxed NaN can only ever be
 * compared as "both are NaN"; the payload bits are not observable across the
 * wasm/JS import boundary. Shared verbatim by spine_schema 1 and
 * transcript_schema 1 — the two schemas MUST agree on this encoding.
 */
const boxView = new DataView(new ArrayBuffer(8));
export const unbox = (v) => {
  if (v === null || typeof v !== "object" || typeof v.bits !== "string") return v;
  if (v.t === "f64") { boxView.setBigUint64(0, BigInt("0x" + v.bits)); return boxView.getFloat64(0); }
  if (v.t === "f32") { boxView.setUint32(0, Number.parseInt(v.bits, 16)); return boxView.getFloat32(0); }
  return v;
};

/** Captured-vs-actual value equality: i32 mod 2^32, i64 via BigInt, floats via Object.is. */
export const valueEq = (boxed, actual) => {
  const expected = unbox(boxed);
  if (typeof actual === "bigint") {
    return BigInt.asUintN(64, BigInt(expected)) === BigInt.asUintN(64, actual);
  }
  if (typeof expected === "number" && Number.isInteger(expected) && Number.isInteger(actual)) {
    return (expected >>> 0) === (actual >>> 0);
  }
  return Object.is(expected, actual);
};

export const fmtVal = (v) => {
  const u = unbox(v);
  if (typeof u === "bigint") return `${u}n`;
  return v !== u ? `${u}[0x${v.bits}]` : String(u);
};

export const fmtArgs = (a) => `(${a.map(fmtVal).join(", ")})`;

/** Decode a captured `ret` field into the value a stub should hand back. */
export const decodeRet = (ret) => {
  if (ret == null) return undefined;
  if (typeof ret === "object" && ret.t === "i64") return BigInt(ret.v);
  return unbox(ret);
};

/**
 * The boundary shim object: EVERY function import dispatches into `onCall`
 * under its own import name — a Proxy target, so imports the capture never
 * names still get order-checked (arriving out of order IS the divergence, not
 * an unshimmed throw).
 */
export const makeBoundaryShimProxy = (onCall) => new Proxy({}, {
  get: (t, k) => typeof k === "string" ? (...a) => onCall(k, a) : undefined,
});

/**
 * Compare a list of {addr,b64} expectations against live linear memory.
 * Returns null when every byte matches, else the FIRST divergent byte as
 * {addr, expected, got} — the caller owns the message wording.
 */
export const firstOwnedMismatch = (u8, owned, onBad) => {
  for (const o of owned ?? []) {
    const addr = parseAddr(o.addr, onBad);
    const expect = Buffer.from(o.b64, "base64");
    for (let k = 0; k < expect.length; k++) {
      if (u8[addr + k] !== expect[k]) {
        return { addr: addr + k, expected: expect[k], got: u8[addr + k] };
      }
    }
  }
  return null;
};

export const fmtByte = (b) => "0x" + b.toString(16).padStart(2, "0");

/** Read a JSONL capture file; returns {raw, lines} with blank lines dropped. */
export const readCaptureJsonl = (absPath, onBad) => {
  if (!fs.existsSync(absPath)) onBad(`no capture file at ${absPath}`);
  const raw = fs.readFileSync(absPath);
  const lines = raw.toString("utf8").split("\n").filter((l) => l.length > 0);
  if (lines.length === 0) onBad(`capture file ${absPath} is empty`);
  return { raw, lines };
};

/** Apply a capture record's memory deltas to linear memory. */
export const applyDeltas = (u8, deltas, onBad) => {
  for (const d of deltas ?? []) u8.set(Buffer.from(d.b64, "base64"), parseAddr(d.addr, onBad));
};

export const gitRevOf = (root) => {
  try { return execSync("git rev-parse HEAD", { cwd: root }).toString().trim(); }
  catch { return "unknown"; } // evidence field only
};

export const relPosix = (root, p) => path.relative(root, p).replace(/\\/g, "/");
