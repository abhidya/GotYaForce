import { GcFunctionRegistry, GcMemory, f32, type GcRuntime } from "./gcRuntime.js";

function assert(condition: unknown, message: string): asserts condition {
  if (!condition) throw new Error(message);
}

const memory = new GcMemory(0x8000_0000, 0x100);
memory.writeU32(0x8000_0000, 0x1234_5678);
assert(memory.bytes(0x8000_0000, 4).join(",") === "18,52,86,120", "u32 must be big-endian");
memory.writeS16(0x8000_0004, -2);
assert(memory.readS16(0x8000_0004) === -2, "s16 round-trip failed");
memory.writeF32(0x8000_0008, 1 / 3);
assert(memory.readF32(0x8000_0008) === f32(1 / 3), "f32 round-trip failed");

const functions = new GcFunctionRegistry();
const runtime = { memory, functions, host: {} } as unknown as GcRuntime;
functions.register(0x8000_1000, (_runtime, value) => value + 1);
functions.alias(0x8000_1010, 0x8000_1000);
assert(functions.call(runtime, 0x8000_1010, 41) === 42, "function alias dispatch failed");

