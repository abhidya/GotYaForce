import assert from "node:assert/strict";
import { EventEmitter } from "node:events";
import test from "node:test";

import { CdpClient } from "./lib/cdp-client.mjs";

class FakeSocket extends EventEmitter {
  readyState = 1;
  sent = [];

  send(message, callback) {
    this.sent.push(JSON.parse(message));
    callback?.();
  }

  terminate() {
    this.readyState = 3;
  }
}

test("CDP commands have a bounded timeout", async () => {
  const client = new CdpClient(new FakeSocket());
  await assert.rejects(client.send("NeverReplies", {}, 20), /timed out after 20ms/);
  assert.equal(client.pending.size, 0);
});

test("socket close rejects every pending command", async () => {
  const socket = new FakeSocket();
  const client = new CdpClient(socket);
  const first = client.send("First", {}, 1000);
  const second = client.send("Second", {}, 1000);
  socket.emit("close");
  await assert.rejects(first, /CDP socket closed/);
  await assert.rejects(second, /CDP socket closed/);
  assert.equal(client.pending.size, 0);
});

test("socket error rejects every pending command", async () => {
  const socket = new FakeSocket();
  const client = new CdpClient(socket);
  const pending = client.send("Pending", {}, 1000);
  socket.emit("error", new Error("reset"));
  await assert.rejects(pending, /CDP socket error: reset/);
  assert.equal(client.pending.size, 0);
});

test("a matching response resolves and clears its command", async () => {
  const socket = new FakeSocket();
  const client = new CdpClient(socket);
  const response = client.send("Runtime.enable");
  const [{ id }] = socket.sent;
  socket.emit("message", JSON.stringify({ id, result: { enabled: true } }));
  assert.deepEqual(await response, { enabled: true });
  assert.equal(client.pending.size, 0);
});
