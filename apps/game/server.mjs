import { randomBytes } from "node:crypto";
import { WebSocketServer } from "ws";
import borgsData from "../../packages/assets/data/borgs.json" with { type: "json" };

const PORT = Number(process.env.PORT ?? 5174);
const MAX_PLAYERS = 4;
const FORCE_LIMIT = 30;
const DEFAULT_BORG_ID = "pl0615";
const DEFAULT_ARENA_ID = "challenge";
const DEFAULT_ENERGY_BUDGET = 1000;
const borgs = new Map(borgsData.borgs.map((borg) => [borg.id, borg]));
const defaultBorgId = borgs.has(DEFAULT_BORG_ID) ? DEFAULT_BORG_ID : borgsData.borgs[0]?.id;
const rooms = new Map();

const wss = new WebSocketServer({ port: PORT });
wss.on("connection", (socket) => {
  const client = {
    id: randomBytes(4).toString("hex"),
    socket,
    roomCode: "",
    player: null,
  };

  socket.on("message", (data) => handleMessage(client, data.toString("utf8")));
  socket.on("close", () => leaveRoom(client));
  socket.on("error", () => leaveRoom(client));
});

wss.on("listening", () => {
  console.log(`Gotcha Force Adventure server ws://localhost:${PORT}`);
});

function handleMessage(client, raw) {
  let msg;
  try {
    msg = JSON.parse(raw);
  } catch {
    send(client, { type: "error", message: "Bad message." });
    return;
  }

  if (msg.type === "create") {
    const payload = validateJoinPayload(msg);
    if (!payload.ok) return send(client, { type: "error", message: payload.message });

    const roomCode = makeRoomCode();
    rooms.set(roomCode, {
      code: roomCode,
      clients: new Set(),
      stage: stageSummary(msg.stageId ?? msg.stage ?? DEFAULT_ARENA_ID),
    });
    joinRoom(client, roomCode, payload.name, payload.borg);
  } else if (msg.type === "join") {
    const payload = validateJoinPayload(msg, { requireRoomCode: true });
    if (!payload.ok) return send(client, { type: "error", message: payload.message });
    joinRoom(client, payload.roomCode, payload.name, payload.borg);
  } else if (msg.type === "ready" && client.player) {
    const payload = validateReadyPayload(msg);
    if (!payload.ok) return send(client, { type: "error", message: payload.message });

    client.player.ready = payload.ready;
    client.player.force = payload.force;
    client.player.energy = payload.energyBudget;
    client.player.forceEnergy = payload.forceEnergy;
    broadcastState(client.roomCode);
  } else if (msg.type === "pose" && client.player) {
    client.player.x = finite(msg.x);
    client.player.y = finite(msg.y);
    client.player.z = finite(msg.z);
    client.player.ry = finite(msg.ry);
    client.player.anim = String(msg.anim ?? "idle");
    broadcastState(client.roomCode);
  }
}

function joinRoom(client, roomCode, name, borg) {
  const room = rooms.get(roomCode);
  if (!room) {
    send(client, { type: "error", message: "Room not found." });
    return;
  }
  if (room.clients.size >= MAX_PLAYERS) {
    send(client, { type: "error", message: "Room is full." });
    return;
  }

  leaveRoom(client);
  client.roomCode = roomCode;
  client.player = {
    id: client.id,
    name,
    ready: false,
    x: room.clients.size * 90,
    y: 0,
    z: 0,
    ry: 0,
    borg,
    force: [borg],
    energy: DEFAULT_ENERGY_BUDGET,
    forceEnergy: energyForForce([borg]),
    anim: "idle",
  };
  room.clients.add(client);
  send(client, { type: "welcome", playerId: client.id, roomCode, stage: room.stage, players: players(room) });
  broadcastState(roomCode);
}

function leaveRoom(client) {
  const room = rooms.get(client.roomCode);
  if (room) {
    room.clients.delete(client);
    if (room.clients.size === 0) rooms.delete(client.roomCode);
    else broadcastState(client.roomCode);
  }
  client.roomCode = "";
  client.player = null;
}

function players(room) {
  return [...room.clients].map((client) => client.player).filter(Boolean);
}

function broadcastState(roomCode) {
  const room = rooms.get(roomCode);
  if (!room) return;
  const state = { type: "state", stage: room.stage, players: players(room) };
  for (const client of room.clients) send(client, state);
}

function send(client, value) {
  if (client.socket.readyState === client.socket.OPEN) {
    client.socket.send(JSON.stringify(value));
  }
}

function makeRoomCode() {
  const alphabet = "ABCDEFGHJKLMNPQRSTUVWXYZ23456789";
  do {
    let code = "";
    for (let i = 0; i < 4; i += 1) code += alphabet[Math.floor(Math.random() * alphabet.length)];
    if (!rooms.has(code)) return code;
  } while (true);
}

function finite(value) {
  const n = Number(value);
  return Number.isFinite(n) ? n : 0;
}

function validateJoinPayload(msg, options = {}) {
  const name = String(msg.name ?? "Player").trim().slice(0, 18) || "Player";
  const borg = String(msg.borg ?? defaultBorgId);
  if (!borgs.has(borg)) return { ok: false, message: "Selected borg does not exist." };

  if (options.requireRoomCode) {
    const roomCode = String(msg.roomCode ?? "").toUpperCase().replace(/[^A-Z0-9]/g, "");
    if (roomCode.length !== 4) return { ok: false, message: "Room code must be 4 characters." };
    return { ok: true, name, borg, roomCode };
  }

  return { ok: true, name, borg };
}

function validateReadyPayload(msg) {
  if (typeof msg.ready !== "boolean") return { ok: false, message: "Ready must be true or false." };
  if (!Array.isArray(msg.force)) return { ok: false, message: "Force must be a list." };

  const force = msg.force.map((id) => String(id)).slice(0, FORCE_LIMIT);
  if (force.length === 0) return { ok: false, message: "Force must include at least one borg." };
  const missing = force.find((id) => !borgs.has(id));
  if (missing) return { ok: false, message: `Selected borg does not exist: ${missing}.` };

  const energyBudget = Number(msg.energy);
  if (!Number.isFinite(energyBudget) || energyBudget <= 0) {
    return { ok: false, message: "Energy budget must be a positive number." };
  }

  const forceEnergy = energyForForce(force);
  if (forceEnergy > energyBudget) {
    return { ok: false, message: `Force energy ${forceEnergy} exceeds budget ${energyBudget}.` };
  }

  return { ok: true, ready: msg.ready, force, energyBudget, forceEnergy };
}

function energyForForce(force) {
  return force.reduce((total, id) => total + Number(borgs.get(id)?.energy ?? 0), 0);
}

function stageSummary(stageId) {
  const id = String(stageId ?? DEFAULT_ARENA_ID).trim().toLowerCase();
  if (/^st\d{2}$/.test(id)) return { id, name: id.toUpperCase() };
  return { id: DEFAULT_ARENA_ID, name: "Challenge" };
}
