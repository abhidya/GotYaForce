// =============================================================================
// hleSelftestMain.ts — end-to-end proof for the AUDIO and DVD halves of the
// HLE host.
//
// Boots two wasm modules on the real composed-module runtime — worker-owned
// shared memory, Atomics RPC bridge, signature-accurate import trampolines —
// so their DVD calls and their AI/DSP register accesses cross the H2 bridge
// exactly as a composed ROM module's would.
//
// TWO LEGS, and the second one is not hand-written:
//   A. test/fixtures/hle-selftest/ — HAND-WRITTEN ROM-SHAPED call sequences.
//      A human chose them, modelling the game's own file driver `zz_0274dd4_`
//      and `AIInit`'s register order.
//   B. test/fixtures/hle-rom-unit/ — the VERBATIM DECOMPILATION of seven ROM
//      bodies (AIInitDMA, AIStartDMA, the two AIVR setters, the play-state
//      reader, the ROM's strcat, and gcCiGetFileSize), with the AI/DSP MMIO
//      accesses lowered and nothing else changed. It gets its own worker and
//      its own 0x807A0000-byte shared memory.
//
// WHAT THIS PROVES
//   1. DVD calls reach the adapters through the real bridge, resolve a path
//      against a real GameCube FST, and deliver the right BYTES into GC memory.
//   2. An asynchronous DVD read's completion callback is delivered back into
//      the module as an INVOKE-REQUEST at a worker park point (design R3), and
//      the ROM-side callback observes the transferred byte count.
//   3. An UNIMPLEMENTED DVD entry point fails LOUDLY with a declared servicing
//      error, instead of no-opping into a buffer of zeroes.
//   4. AI/DSP register accesses reach the register file, and the ROM's own
//      read-modify-write masking round-trips: the address AIInitDMA encodes
//      into two half-registers decodes back to the address it was given.
//   5. The MusyX mailbox spin loop `zz_0217dd8_` runs terminates — the host's
//      null DSP consumes the command instead of hanging the module.
//   6. REAL ROM CODE (leg B) drives the whole audio path: AIInitDMA +
//      AIStartDMA move DSP-ADPCM-decoded PCM out of the arena, through the
//      DMA reconstruction, into a WebAudio AudioBuffer whose samples are the
//      decoder's samples.
//   7. REAL ROM CODE (leg B) drives the whole DVD path: gcCiGetFileSize builds
//      a path with the ROM's own strcat, opens it, and returns the file's
//      length out of the DVDFileInfo the adapter filled in.
//
// WHAT THIS DOES NOT PROVE — stated here because a green page invites the
// opposite reading:
//   * nothing about whether any of this matches a GameCube. Every adapter is a
//     synthetic stand-in and nothing has been compared against console
//     behaviour or a real drive;
//   * the disc is one this page BUILT. The repository contains no disc bytes;
//   * and above all, THE MIXER IS ABSENT. The PCM in leg 6 was put there by
//     this page, not by the game: Gotcha Force's voices are MusyX microcode on
//     the GameCube DSP and none of it is translated. A real composed module
//     would DMA a buffer of silence. See docs/audio-dvd-hle-host.md.
// =============================================================================

import { defineAdapter } from "../adapters.js";
import { gcAddressForSymbol } from "../composed.js";
import { FrameValueClass } from "../frame.js";
import { RomRuntimeHost, exposeBridgeLedger } from "../host.js";
import { BridgeCallError, BridgeStatus } from "../protocol.js";
import {
  AUDIO_NO_BEHAVIOURAL_CLAIM,
  AudioHost,
  WebAudioBackend,
  decodeDspAdpcm,
  pcmToAiDmaBytes,
  registerAudioAdapters,
  registerMmioAdapters,
} from "../audio/index.js";
import {
  DVD_NO_BEHAVIOURAL_CLAIM,
  DvdHost,
  SyntheticDisc,
  registerDvdAdapters,
  type DvdPendingCallback,
} from "../dvd/index.js";

/** Trampoline dispatch frames, inside the 16 MiB selftest memory and clear of
 *  emscripten's static data and stack. */
const TRAMPOLINE_BASE = 0x600000;
const TRAMPOLINE_SLOTS = 32;
/** Scratch inside the 16 MiB selftest memory, past the trampoline frames. */
const SCRATCH = 0x700000;
const PATH_ADDR = SCRATCH;
const FILEINFO_ADDR = SCRATCH + 0x200;
const DEST_ADDR = SCRATCH + 0x400;
const BLOCK_ADDR = SCRATCH + 0x1000;
const ABS_DEST_ADDR = SCRATCH + 0x1100;

/** The ROM unit's own 0x807A0000-byte arena. Its dispatch frames and scratch
 *  go above the ROM data it touches (0x8040b1cc..0x8040c178) and below the end. */
const ROM_TRAMPOLINE_BASE = 0x80520000;
const ROM_FILENAME_ADDR = 0x80530000;
/** [CORPUS] FUN_802756fc strcpy's the base directory from here. */
const ROM_BASEDIR_ADDR = 0x8040c178;
/** [CORPUS] FUN_802756fc calls this pointer on error; null means "no logger". */
const ROM_ERRLOG_ADDR = 0x8040b1d0;
/** 32-byte aligned, which the AI DMA address register requires. */
const ROM_AUDIO_BUFFER = 0x80600000;

/** The file the DVD legs read. Path shape copied from the ROM's own habit of
 *  building "<basedir><name>" and normalizing backslashes. */
const DISC_FILE_PATH = "/borg/bg0001.dat";
const DISC_FILE_NAME = "bg0001.dat";
const DISC_BASEDIR = "/borg/";

interface CheckResult {
  name: string;
  pass: boolean;
  expected: string;
  actual: string;
}

const results: CheckResult[] = [];

function check(name: string, actual: unknown, expected: unknown): void {
  const pass = Object.is(actual, expected) || JSON.stringify(actual) === JSON.stringify(expected);
  results.push({ name, pass, expected: String(expected), actual: String(actual) });
}

function checkNear(name: string, actual: number, expected: number, tolerance: number): void {
  const pass = Math.abs(actual - expected) <= tolerance;
  results.push({ name, pass, expected: `${expected} +/-${tolerance}`, actual: String(actual) });
}

function render(done: boolean, report: unknown, error?: string): void {
  const all = results.every((r) => r.pass) && !error;
  const root = document.getElementById("results");
  if (root) {
    root.innerHTML =
      `<h1 data-status="${done ? (all ? "pass" : "fail") : "running"}">` +
      `Audio/DVD HLE host self-test: ${done ? (all ? "PASS" : "FAIL") : "running"}</h1>` +
      `<p class="claim"><strong>AUDIO BEHAVIOURAL CLAIM:</strong> ${AUDIO_NO_BEHAVIOURAL_CLAIM}</p>` +
      `<p class="claim"><strong>DVD BEHAVIOURAL CLAIM:</strong> ${DVD_NO_BEHAVIOURAL_CLAIM}</p>` +
      (error ? `<p class="error">${error}</p>` : "") +
      `<table><tr><th>check</th><th>expected</th><th>actual</th><th></th></tr>` +
      results
        .map(
          (r) =>
            `<tr class="${r.pass ? "pass" : "fail"}"><td>${r.name}</td><td>${r.expected}</td>` +
            `<td>${r.actual}</td><td>${r.pass ? "PASS" : "FAIL"}</td></tr>`,
        )
        .join("") +
      `</table>`;
  }
  (window as unknown as Record<string, unknown>)["__gfHleSelfTest"] = {
    done,
    pass: done && all,
    // Repeated in the machine-readable payload too: a smoke script reading
    // `pass` must trip over what `pass` does not mean.
    audioBehaviouralClaim: AUDIO_NO_BEHAVIOURAL_CLAIM,
    dvdBehaviouralClaim: DVD_NO_BEHAVIOURAL_CLAIM,
    verified: false,
    error: error ?? null,
    results,
    report,
    crossOriginIsolated: window.crossOriginIsolated,
  };
}

/** Write a NUL-terminated latin-1 string into the arena. */
function writeCString(mem: { writeBytes(addr: number, bytes: Uint8Array): void }, addr: number, text: string): void {
  const bytes = new Uint8Array(text.length + 1);
  for (let i = 0; i < text.length; i++) bytes[i] = text.charCodeAt(i) & 0xff;
  mem.writeBytes(addr, bytes);
}

/**
 * The DSP-ADPCM block both audio legs decode.
 *
 * Deliberately NOT a real soundbank sample: the repository has no disc bytes,
 * so there is no real DPK to read (docs/audio-dvd-hle-host.md §2). What this
 * is instead is an ADPCM stream whose expected output is derivable BY HAND, so
 * the check is not "the decoder agreed with itself". The frame header 0x00
 * selects coefficient pair 0 and scale 1<<0 == 1, and coefficient pair 0 is
 * (0, 0), so the decode reduces to
 *     sample = floor((nibble * 1 * 2048 + 0 + 0 + 1024) / 2048) = nibble
 * for every 4-bit sample, sign-extended at 8. So the PCM this produces is
 * exactly the nibble sequence, and any arithmetic slip anywhere in the decoder
 * changes it.
 */
function buildAdpcmProbe(frames: number): { adpcm: Uint8Array; coefs: Int16Array; expected: Int16Array } {
  const coefs = new Int16Array(16); // all zero: pair 0 is (0, 0)
  const adpcm = new Uint8Array(frames * 8);
  const expected = new Int16Array(frames * 14);
  let n = 0;
  for (let f = 0; f < frames; f++) {
    adpcm[f * 8] = 0x00; // scale exponent 0, coefficient pair 0
    for (let b = 0; b < 7; b++) {
      const hi = (f + b) % 8; // 0..7 -> positive nibbles
      const lo = (f + b + 1) % 8;
      adpcm[f * 8 + 1 + b] = (hi << 4) | lo;
      expected[n++] = hi;
      expected[n++] = lo;
    }
  }
  return { adpcm, coefs, expected };
}

/** Fixture scaffolding, NOT part of any measured surface: the ROM bodies call
 *  gnt4_OSDisableInterrupts_bl / gnt4_OSRestoreInterrupts_bl, which belong to
 *  the OS family this work does not cover. They are registered here, in the
 *  test page, so they can never be mistaken for audio or DVD coverage. */
function registerScaffoldOsAdapters(host: RomRuntimeHost): void {
  const evidence =
    "FIXTURE SCAFFOLD, not part of the audio or DVD surface: interrupt masking has no meaning on a host " +
    "that services adapters on one thread. Counted in no coverage figure.";
  host.registerAdapter(
    defineAdapter({
      gcAddr: gcAddressForSymbol("gnt4_OSDisableInterrupts_bl").gcAddr,
      name: "gnt4_OSDisableInterrupts_bl [scaffold]",
      evidence,
      evidenceClass: "synthetic",
      retClass: FrameValueClass.I32,
      service: (ctx) => ctx.frame.setRetI32(0),
    }),
  );
  host.registerAdapter(
    defineAdapter({
      gcAddr: gcAddressForSymbol("gnt4_OSRestoreInterrupts_bl").gcAddr,
      name: "gnt4_OSRestoreInterrupts_bl [scaffold]",
      evidence,
      evidenceClass: "synthetic",
      retClass: FrameValueClass.VOID,
      service: (ctx) => ctx.frame.setRetVoid(),
    }),
  );
}

// =============================================================================
// Leg A — hand-written ROM-shaped sequences
// =============================================================================

async function runSelftestLeg(
  disc: SyntheticDisc,
  fileBytes: Uint8Array,
  audioContext: AudioContext,
): Promise<unknown> {
  const response = await fetch("./hle_selftest.threads.wasm");
  if (!response.ok) throw new Error(`hle selftest fixture fetch failed: ${response.status}`);
  const wasmBytes = await response.arrayBuffer();

  const worker = new Worker(new URL("./rom-runtime-worker.js", import.meta.url), { type: "module" });
  // admitSyntheticAdapters: EVERY adapter here is a synthetic stand-in. The
  // registry refuses them by default precisely so this has to be asked for,
  // and asking for it is the declaration that nothing carries a claim.
  const host = await RomRuntimeHost.start(worker, wasmBytes, {
    admitSyntheticAdapters: true,
    bridgeAllImports: true,
    trampolineFrameBase: TRAMPOLINE_BASE,
    trampolineFrameSlots: TRAMPOLINE_SLOTS,
  });
  try {
    exposeBridgeLedger(host);
    registerScaffoldOsAdapters(host);

    const dvd = new DvdHost(disc, host.memory);
    const dvdRegistration = registerDvdAdapters(host, dvd);
    const backend = new WebAudioBackend(audioContext);
    const audio = new AudioHost(backend, host.memory);
    const audioRegistration = registerAudioAdapters(host, audio);
    registerMmioAdapters(host, audio);

    check(
      "every measured DVD entry point has an adapter",
      dvdRegistration.implemented + dvdRegistration.unimplemented,
      15,
    );
    check(
      "every measured audio entry point has an adapter",
      audioRegistration.implemented + audioRegistration.unimplemented,
      20,
    );
    check(
      "the fixture's DVD imports are all bound to the bridge",
      host.bridgedImports.filter((b) => b.symbol.startsWith("gnt4_DVD")).length,
      8,
    );
    check(
      "the fixture's MMIO imports are all bound to the bridge",
      host.bridgedImports.filter((b) => b.symbol.startsWith("__gf_mmio_")).length,
      4,
    );

    // --- proof 1: open, read, close, and the bytes are the disc's -----------
    writeCString(host.memory, PATH_ADDR, DISC_FILE_PATH);
    host.nextFrame();
    const readLength = 0x40; // 32-byte aligned, as the SDK requires
    const got = await host.invokeExport("hle_dvd_open_read_close", [
      PATH_ADDR,
      FILEINFO_ADDR,
      DEST_ADDR,
      readLength,
    ]);
    check("DVDReadPrio reported the whole requested length", got, readLength);
    const delivered = host.memory.readBytes(DEST_ADDR, readLength);
    check(
      "the bytes in GC memory are the disc's bytes",
      Array.from(delivered.subarray(0, 16)).join(","),
      Array.from(fileBytes.subarray(0, 16)).join(","),
    );
    check("the last delivered byte is right too", delivered[readLength - 1], fileBytes[readLength - 1]);
    check("DVDOpen wrote the file's real length into the DVDFileInfo", host.memory.readU32(FILEINFO_ADDR + 0x34), fileBytes.length);
    check(
      "DVDOpen wrote the file's disc offset into the DVDFileInfo",
      host.memory.readU32(FILEINFO_ADDR + 0x30),
      disc.fst[disc.entrynumForPath(DISC_FILE_PATH)]?.startAddr,
    );
    check("no path went missing", dvd.missingPaths, []);

    // --- proof 2: the async completion callback comes back as an invoke -----
    const callbackPtr = await host.invokeExport("hle_callback_ptr", []);
    check("the fixture handed us a ROM-side callback pointer", callbackPtr > 0, true);
    const absLength = 0x20;
    const absOffset = disc.fst[disc.entrynumForPath(DISC_FILE_PATH)]?.startAddr ?? 0;
    const absGot = await host.invokeExport("hle_dvd_abs_read", [
      BLOCK_ADDR,
      ABS_DEST_ADDR,
      absLength,
      absOffset,
      callbackPtr,
    ]);
    check("the absolute read transferred its bytes", absGot, absLength);
    check("the host queued exactly one completion callback", dvd.pending.length, 1);
    check("the queued callback is the ROM's own pointer", dvd.pending[0]?.callbackAddr, callbackPtr);

    // Delivery: NOT from inside the adapter (the ROM is on the stack there) but
    // as an invoke-request at a park point — design R3's interrupt shape.
    const toDeliver: DvdPendingCallback[] = [];
    dvd.drainCallbacks((p) => toDeliver.push(p));
    for (const p of toDeliver) {
      await host.postEvent("hle_deliver_callback", [p.callbackAddr, p.result, p.blockAddr]);
    }
    check("the ROM-side callback ran exactly once", await host.invokeExport("hle_callback_hits", []), 1);
    check("it was handed the transferred byte count", await host.invokeExport("hle_callback_result", []), absLength);
    check("it was handed its own command block", await host.invokeExport("hle_callback_block", []), BLOCK_ADDR);
    check("the completion queue is empty again", dvd.pending.length, 0);

    // --- proof 3: an unimplemented entry point is LOUD ----------------------
    host.nextFrame();
    let unimplementedStatus: unknown = "resolved without error";
    try {
      await host.invokeExport("hle_dvd_call_unimplemented", [BLOCK_ADDR, ABS_DEST_ADDR]);
    } catch (error) {
      unimplementedStatus = error instanceof BridgeCallError ? error.status : `non-bridge: ${String(error)}`;
    }
    check("unimplemented DVDInquiryAsync rejects with ADAPTER_THREW", unimplementedStatus, BridgeStatus.ADAPTER_THREW);
    check("the unimplemented hit is named", dvd.unimplementedHits, ["gnt4_DVDInquiryAsync_bl"]);

    // --- proof 4: the audio registers -------------------------------------
    host.nextFrame();
    await host.invokeExport("hle_audio_init", []);
    check("the ROM-shaped bring-up selected the 32 kHz DSP rate", audio.registers.dspSampleRate(), 32000);
    await host.invokeExport("hle_audio_set_volume", [0x40, 0x60]);
    const volumes = audio.registers.volumes();
    checkNear("AIVR bits 0-7 decoded as the LEFT volume", volumes.left, 0x40 / 255, 1e-6);
    checkNear("AIVR bits 8-15 decoded as the RIGHT volume", volumes.right, 0x60 / 255, 1e-6);
    check("the DAC is not playing yet", await host.invokeExport("hle_audio_play_state", []), 0);
    check("stereo sound mode", await host.invokeExport("hle_sound_mode", []), 1);

    // --- proof 5: the MusyX mailbox spin loop terminates --------------------
    // [CORPUS] `zz_0217dd8_` posts 0xBABE0180 and spins on the busy bit before
    // every audio frame. A host that left the bit set would hang the module.
    const spins = await host.invokeExport("hle_dsp_post", [0xbabe0180 | 0]);
    check("the DSP mailbox spin loop terminated", spins >= 0, true);
    check("the command word the ROM would send was recorded", audio.registers.dspMailbox.includes(0xbabe0180), true);
    check("and it went to a DSP that is not there", audio.report().dspMicrocodeAbsent, true);

    await host.invokeExport("hle_audio_stop", []);

    return {
      source: "HAND-WRITTEN ROM-shaped sequences (test/fixtures/hle-selftest/hle_selftest.c)",
      dvd: dvd.report(),
      audio: audio.report(),
      ledger: host.ledger.snapshot(),
    };
  } finally {
    await host.shutdown();
  }
}

// =============================================================================
// Leg B — the verbatim ROM unit
// =============================================================================

async function runRomUnitLeg(disc: SyntheticDisc, audioContext: AudioContext): Promise<unknown> {
  const response = await fetch("./hle_rom_unit.threads.wasm");
  if (!response.ok) throw new Error(`hle rom unit fetch failed: ${response.status}`);
  const wasmBytes = await response.arrayBuffer();

  const worker = new Worker(new URL("./rom-runtime-worker.js", import.meta.url), { type: "module" });
  const host = await RomRuntimeHost.start(worker, wasmBytes, {
    admitSyntheticAdapters: true,
    bridgeAllImports: true,
    trampolineFrameBase: ROM_TRAMPOLINE_BASE,
    trampolineFrameSlots: TRAMPOLINE_SLOTS,
  });
  try {
    registerScaffoldOsAdapters(host);
    const dvd = new DvdHost(disc, host.memory);
    registerDvdAdapters(host, dvd);
    const backend = new WebAudioBackend(audioContext);
    const audio = new AudioHost(backend, host.memory);
    registerAudioAdapters(host, audio);
    registerMmioAdapters(host, audio);

    // --- the ROM's own file-size helper, on the ROM's own data --------------
    // [CORPUS] FUN_802756fc strcpy's the base directory from 0x8040c178, then
    // appends the caller's filename with the ROM's own strcat, then opens it.
    writeCString(host.memory, ROM_BASEDIR_ADDR, DISC_BASEDIR);
    writeCString(host.memory, ROM_FILENAME_ADDR, DISC_FILE_NAME);
    host.memory.writeU32(ROM_ERRLOG_ADDR, 0); // no error logger installed
    host.nextFrame();
    const size = await host.invokeExport("FUN_802756fc", [
      0, 0, 0, 0, 0, 0, 0, 0, ROM_FILENAME_ADDR, 0, 0, 0, 0, 0, 0, 0,
    ]);
    const expectedSize = disc.fst[disc.entrynumForPath(DISC_FILE_PATH)]?.length ?? -1;
    check("REAL ROM CODE returned the file's real length", size, expectedSize);
    check("the ROM's own path build resolved against the FST", dvd.missingPaths, []);
    check("the ROM unit hit no unimplemented DVD entry point", dvd.unimplementedHits, []);

    // --- the ROM's own DAC driver, on decoded ADPCM ------------------------
    // 160 stereo frames is the ROM's own block size: [CORPUS] AIInitDMA is
    // called with 0x280 bytes, which at 32 kHz is the 5 ms MusyX frame.
    const probe = buildAdpcmProbe(12);
    const pcm = decodeDspAdpcm({
      data: probe.adpcm,
      offset: 0,
      numSamples: 160,
      numNibbles: probe.adpcm.length * 2,
      coefs: probe.coefs,
    });
    check("the ADPCM decoder produced the hand-derivable samples", Array.from(pcm.subarray(0, 8)).join(","), Array.from(probe.expected.subarray(0, 8)).join(","));
    // The right channel is the left inverted, so a host that mixed the two up
    // fails instead of passing by symmetry.
    const rightPcm = Int16Array.from(pcm, (s) => -s);
    const dmaBytes = pcmToAiDmaBytes(pcm, rightPcm);
    check("the DMA block is the ROM's own 0x280 bytes", dmaBytes.length, 0x280);
    host.memory.writeBytes(ROM_AUDIO_BUFFER, dmaBytes);

    host.nextFrame();
    await host.invokeExport("AIInitDMA", [ROM_AUDIO_BUFFER | 0, 0x280]);
    check("no transfer has started yet (AIInitDMA does not set the enable bit)", audio.dmaBlockCount, 0);
    await host.invokeExport("AIStartDMA", []);
    check("REAL ROM CODE started exactly one DMA transfer", audio.dmaBlockCount, 1);

    const block = backend.recorder.blocks[0];
    check("the DMA reconstructed the address the ROM gave it", `0x${(block?.gcAddr ?? 0).toString(16)}`, `0x${ROM_AUDIO_BUFFER.toString(16)}`);
    check("the DMA reconstructed the length the ROM gave it", block?.byteLength, 0x280);
    check("that is 160 stereo frames", block?.frames, 160);
    check("at the 32 kHz rate the ROM's AIInit selects", block?.sampleRate, 32000);
    check("the block is NOT silent (this page put real samples there)", block?.silent, false);
    check("the first left sample survived the round trip", block?.left[0], pcm[0]);
    check("the first right sample is the inverted one", block?.right[0], rightPcm[0]);
    check("the last left sample survived too", block?.left[159], pcm[159]);

    // The audio device actually received it.
    const buffer = backend.lastBuffer;
    check("a WebAudio AudioBuffer was created", buffer !== null, true);
    check("with two channels", buffer?.numberOfChannels, 2);
    check("and 160 frames", buffer?.length, 160);
    checkNear("its first left sample is the decoded PCM, normalized", buffer?.getChannelData(0)[0] ?? NaN, (pcm[0] as number) / 32768, 1e-6);
    checkNear("its first right sample too", buffer?.getChannelData(1)[0] ?? NaN, (rightPcm[0] as number) / 32768, 1e-6);

    check("the DAC's sample counter advanced by one block", audio.registers.cells.get(0xcc006c08), 160);
    check("one AI DMA completion interrupt is owed to the ROM", audio.pendingInterrupts.length, 1);

    // --- the ROM's own volume setters --------------------------------------
    await host.invokeExport("zz_0214994_", [0x33]); // real AISetStreamVolLeft
    await host.invokeExport("AISetStreamVolLeft", [0x77]); // misnamed; sets RIGHT
    const v = audio.registers.volumes();
    checkNear("the ROM's left setter wrote AIVR bits 0-7", v.left, 0x33 / 255, 1e-6);
    checkNear("the misnamed 'left' setter really wrote the RIGHT field", v.right, 0x77 / 255, 1e-6);
    check("the ROM's own play-state reader reads AICR bit 0 (clear: the ROM never set it)", await host.invokeExport("zz_02147ac_", []), 0);

    return {
      source:
        "VERBATIM ROM decompilation (test/fixtures/hle-rom-unit/rom.c): AIInitDMA @0x80214634, " +
        "AIStartDMA @0x802146bc, zz_0214994_ @0x80214994, AISetStreamVolLeft @0x802149c0, " +
        "zz_02147ac_ @0x802147ac, zz_0238c90_ @0x80238c90, FUN_802756fc @0x802756fc — " +
        "AI/DSP MMIO hand-lowered (the assembly gate does not cover these windows yet)",
      dvd: dvd.report(),
      audio: audio.report(),
      audioBackend: backend.summary(),
      ledger: host.ledger.snapshot(),
    };
  } finally {
    await host.shutdown();
  }
}

// =============================================================================

async function main(): Promise<void> {
  render(false, null);
  if (!window.crossOriginIsolated) {
    throw new Error("crossOriginIsolated is false — the runtime requires the COI setup (design H1)");
  }

  // The disc this page builds. THE REPOSITORY HAS NO DISC BYTES: research/disc/
  // holds one .gitkeep and every extractor reads an untracked user-data/ tree.
  // So the file below is ours, its FST is synthesized by the same serializer
  // the parser round-trips, and none of it is Gotcha Force's data.
  const fileBytes = new Uint8Array(0x600);
  for (let i = 0; i < fileBytes.length; i++) fileBytes[i] = (i * 7 + 0x11) & 0xff;
  const disc = new SyntheticDisc(
    [
      { path: DISC_FILE_PATH, bytes: fileBytes },
      { path: "/sys/other.dat", bytes: new Uint8Array(0x80).fill(0xab) },
    ],
    "SyntheticDisc built by hleSelftestMain.ts — NOT the game's disc",
  );
  check("the synthesized FST round-tripped through the real parser", disc.fst.length, 5);
  check("the FST resolves the ROM's path", disc.entrynumForPath(DISC_FILE_PATH) > 0, true);
  check("and rejects one that is not there", disc.entrynumForPath("/borg/nope.dat"), -1);

  // --- the ADPCM decoder, against an INDEPENDENT implementation -------------
  // packages/rom-runtime/src/audio/adpcm.ts is a port of the PYTHON decoder in
  // scripts/export-combat-se.py — the one that produced the combat-SE OGGs the
  // game ships. A port checked only against itself proves nothing, so
  // test/fixtures/adpcm/gen-vector.py runs the ORIGINAL over inputs chosen to
  // hit the arithmetic corners (negative coefficients, scale exponent 15,
  // saturation at both clamps — the cases where a JavaScript `>>` would
  // silently differ, because it truncates its operand to int32 first) and the
  // expected PCM is compared here sample for sample.
  const vectorResponse = await fetch("./adpcm-vector.json");
  if (!vectorResponse.ok) throw new Error(`ADPCM cross-check vector fetch failed: ${vectorResponse.status}`);
  const vector = (await vectorResponse.json()) as {
    cases: Array<{ name: string; coefs: number[]; numSamples: number; numNibbles: number; offset: number; data: number[]; expected: number[] }>;
  };
  check("the ADPCM cross-check vector has cases", vector.cases.length > 0, true);
  for (const c of vector.cases) {
    const decoded = decodeDspAdpcm({
      data: Uint8Array.from(c.data),
      offset: c.offset,
      numSamples: c.numSamples,
      numNibbles: c.numNibbles,
      coefs: Int16Array.from(c.coefs),
    });
    const mismatches = c.expected.reduce((n, want, i) => (decoded[i] === want ? n : n + 1), 0);
    check(`ADPCM "${c.name}": ${c.expected.length} samples match the Python reference`, mismatches, 0);
  }

  const audioContext = new AudioContext();

  const legA = await runSelftestLeg(disc, fileBytes, audioContext);
  const legB = await runRomUnitLeg(disc, audioContext);

  render(true, { legA, legB, audioContextSampleRate: audioContext.sampleRate });
  await audioContext.close();
}

main().catch((error: unknown) => {
  render(true, null, error instanceof Error ? `${error.message}\n${error.stack ?? ""}` : String(error));
});
