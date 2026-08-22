#!/usr/bin/env node
// Runner for the @gf/core render-loop resilience contract.
// Requires packages/core to be built first: pnpm --filter @gf/core build
import assert from "node:assert/strict";
import { startRenderLoop } from "../packages/core/dist/index.js";

// A throwing frame must not kill the loop.
{
  let calls = 0, pending = null, errors = [];
  const h = startRenderLoop({
    frame() { calls += 1; if (calls <= 3) throw new Error("boom " + calls); },
    requestFrame: (cb) => { pending = cb; return calls + 1; },
    cancelFrame: () => { pending = null; },
    onFrameError: (e, n) => errors.push([String(e.message), n]),
  });
  for (let i = 0; i < 6; i++) { const cb = pending; pending = null; cb(); }
  // startRenderLoop schedules the first frame but does not invoke it, so six
  // driven callbacks are six frame() calls.
  assert.equal(calls, 6, "loop keeps requesting frames after a throw");
  assert.deepEqual(errors, [["boom 1", 1]], "first error reported, repeats suppressed");
  h.stop();
  const before = calls;
  if (pending) pending();
  assert.equal(calls, before, "stop() halts the loop");
}

// A clean frame resets the consecutive counter, so a later fault reports again.
{
  let calls = 0, pending = null, errors = [];
  startRenderLoop({
    frame() { calls += 1; if (calls === 1 || calls === 3) throw new Error("e" + calls); },
    requestFrame: (cb) => { pending = cb; return 1; },
    cancelFrame: () => {},
    onFrameError: (e, n) => errors.push([e.message, n]),
  });
  for (let i = 0; i < 4; i++) { const cb = pending; pending = null; cb(); }
  assert.deepEqual(errors, [["e1", 1], ["e3", 1]], "counter resets after a clean frame");
}
console.log("render-loop resilience: all checks passed");
