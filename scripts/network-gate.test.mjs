import assert from "node:assert/strict";
import test from "node:test";

import { isExpectedMediaCancellation } from "./lib/network-gate.mjs";

const pageUrl = "http://127.0.0.1:9000/GotYaForce/game/";
const audioUrl = `${pageUrl}audio/bgm/bgm00.ogg`;

test("deliberately replaced OGG media is the only allowed loading failure", () => {
  assert.equal(isExpectedMediaCancellation({ canceled: true, errorText: "net::ERR_ABORTED" }, audioUrl, pageUrl), true);
  assert.equal(isExpectedMediaCancellation({ canceled: false, errorText: "net::ERR_ABORTED" }, audioUrl, pageUrl), false);
  assert.equal(isExpectedMediaCancellation({ canceled: true, errorText: "net::ERR_ABORTED" }, `${pageUrl}models/a.glb`, pageUrl), false);
});

test("network resets, timeouts, and blocked/no-response loads remain fatal", () => {
  for (const event of [
    { canceled: false, errorText: "net::ERR_CONNECTION_RESET" },
    { canceled: false, errorText: "net::ERR_TIMED_OUT" },
    { canceled: false, errorText: "net::ERR_BLOCKED_BY_CLIENT", blockedReason: "inspector" },
  ]) {
    assert.equal(isExpectedMediaCancellation(event, audioUrl, pageUrl), false, event.errorText);
  }
});
