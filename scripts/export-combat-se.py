#!/usr/bin/env python3
"""Export the REAL per-event combat SE samples from the GameCube soundbanks.

PROVENANCE (all statically verified, 2026-07-04):

  Sound id space   : combat code plays literal soundIds via the wrappers
                     zz_00f036c_/zz_00f0468_/zz_00f04b4_/zz_00f061c_ which funnel into the
                     dispatcher zz_00efb3c_ (0x800efb3c, chunk_0026.c:435). It guards
                     id < 0x180 and splits id into bank = id >> 7, sample = id & 0x7f.
                     The 11 mapped combat events and their literal ids are documented in
                     research/decomp/data/combat-se-ids.json.

  Bank containers  : zz_00434f8_ (0x800434f8, chunk_0005.c) loads bank file triples by
                     AFS member index from the DOL table DAT_802d0bec (boot.dol file
                     offset 0x2cdbec, section base 0x802bae60). The table holds
                     [tsb, chd, dpk] AFS member-index triples for afs_data.afs:
                       battle slot 0: members 2839/2840/2841 = snd_com01.tsb/.chd/.dpk
                       battle slot 1: members 2842/2843/2844 = snd_com02.*
                       battle slot 2: members 2845/2846/2847 = snd_com03.*
                       menu   slot 0: members 2848/2849/2850 = snd_com04.*
                     zz_00435dc_ (0x800435dc) registers them: zz_00f0e5c_(slot, tsb),
                     zz_00ef9d4_(slot, chd, dpkBase). So in battle, bank 0/1/2 of the id
                     space = snd_com01/02/03. (snd_com04 is the menu-mode bank.)

  .tsb  ("TSBD")   : little-endian; 16-byte header (u32 size @+4, u32 entryCount=0x80
                     @+0xc), then 128 x 16-byte entries -- one per soundId sample index.
                     Consumed by zz_00f0f84_ (0x800f0f84, chunk_0026.c:1359):
                       +0  type       (0 = one-shot sample, 1 = sequence cmd, 0xff = empty)
                       +2  prog       +3 key (chd tone-table key)
                       +6  channel|flag  +8 volume (0xff => 0x7f)  +9 pan (0xff => 0x40)
                       +10 s16 pitch offset  +12 vol random  +13 pitch random
                       +15 chain: next entry index to ALSO play (0xff = end)

  .chd ("Head")    : big-endian chunked header. Head: u32 chdSize @+0xc, u32 dpkSize
                     @+0x10, chunk offsets Prog/Smpl/Dspi @+0x14/0x18/0x1c.
                       Prog: tone records (14 bytes): u16 velMask, u8 keyLo, u8 keyHi,
                             u16 x2 pitch-bend(1200), u8 vol, u8 pan, u16, u16 sampleIdx.
                             Tones start at progOff+8+toneOff (u32 toneOff at progOff+16).
                       Smpl: 12-byte records; u16 @+10 = Dspi record index.
                       Dspi: 100-byte records = u32 dpkByteOffset + the standard 96-byte
                             GC DSPADPCM header (numSamples, numNibbles, sampleRate,
                             loopFlag, format, sa/ea/ca, 16 s16 coefficients, gain, ps,
                             hist1/2, loop ps/hists).

  .dpk             : raw GC DSP-ADPCM frames (8-byte frames: 1 header byte -> predictor
                     index + scale, 14 sample nibbles), addressed by Dspi dpkByteOffset.

HONEST NOTES:
  * guard-break ids 0x00/0x80/0x100 (zz_005c290_ layered stinger) resolve to TSB entries
    whose volume byte is 0 in ALL THREE banks -- the engine data mutes them. They are NOT
    exported (shipping them would ship silence; wiring another sample would be wrong).
  * id 0x176 (round/mode global cue) is a TSB type-1 (sequence) entry, not a one-shot
    sample; out of scope here (and non-combat anyway).
  * grab 0x9b is a genuine stereo pair: two tones on key 0x62, pan 0x00 (L) / 0x7f (R),
    Dspi samples 98/99 -> exported as one stereo file.

Usage:  python scripts/export-combat-se.py           (dry run: prints the plan)
        python scripts/export-combat-se.py --export  (writes OGGs + manifest)

Requires ffmpeg on PATH (same dependency as scripts/export-audio-assets.mjs).
Inputs are the extracted afs_data members in user-data/GG4E/afs_data/root/.
Outputs apps/game/public/audio/se/se_<id>.ogg + manifest.json (id-keyed).
"""

from __future__ import annotations

import hashlib
import json
import struct
import subprocess
import sys
import tempfile
import wave
from datetime import date
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
BANK_DIR = ROOT / "user-data" / "GG4E" / "afs_data" / "root"
OUT_DIR = ROOT / "apps" / "game" / "public" / "audio" / "se"

# Battle-mode bank slots (DOL table DAT_802d0bec, boot.dol 0x2cdbec; see header comment).
BATTLE_SLOTS = ["snd_com01", "snd_com02", "snd_com03"]
AFS_MEMBERS = {
    "snd_com01": {"tsb": 2839, "chd": 2840, "dpk": 2841},
    "snd_com02": {"tsb": 2842, "chd": 2843, "dpk": 2844},
    "snd_com03": {"tsb": 2845, "chd": 2846, "dpk": 2847},
}

# The 11 mapped combat events (research/decomp/data/combat-se-ids.json). The break trio
# 0x00/0x80/0x100 is intentionally absent: TSB volume 0 in every bank (see HONEST NOTES).
COMBAT_IDS = {
    0x08: ("shot fire / projectile launch", "zz_006ee14_ projectile spawn (chunk_0009.c:3859)"),
    0x10: ("wall/ground crash impact, light borg families", "FUN_8005a580 knockback-terrain impact (chunk_0007.c:2949)"),
    0x13: ("wall/ground crash impact, heavy borg families", "FUN_8005a580 knockback-terrain impact (chunk_0007.c:2946)"),
    0x1E: ("landing / touchdown / footfall", "FUN_8005e31c state slot 31 + grounded handlers (chunk_0007.c:5215)"),
    0x25: ("jump / hop launch", "FUN_80061338 launch state (chunk_0007.c:7157)"),
    0x26: ("actor-vs-actor body bump", "zz_002fcbc_ collision resolver (chunk_0003.c:8378)"),
    0x9B: ("grab/throw connect", "FUN_8005ace8 clash/grab resolution (chunk_0007.c:3283)"),
    0xDD: ("knockdown / heavy landing thud", "FUN_8005dffc state slot 30 knockdown (chunk_0007.c:5111)"),
    0xF2: ("dash / boost / deploy-warp launch", "start_forced_move_to_point + FUN_8005e868 spawn state (chunk_0007.c:5446)"),
}


def be16(data: bytes, off: int) -> int:
    return struct.unpack_from(">H", data, off)[0]


def be32(data: bytes, off: int) -> int:
    return struct.unpack_from(">I", data, off)[0]


def parse_chd(path: Path) -> dict:
    d = path.read_bytes()
    if d[0:4] != b"Head":
        raise ValueError(f"{path.name}: missing Head chunk")
    prog_off, smpl_off, dspi_off = be32(d, 0x14), be32(d, 0x18), be32(d, 0x1C)

    if d[prog_off : prog_off + 4] != b"Prog":
        raise ValueError(f"{path.name}: missing Prog chunk")
    prog_size = be32(d, prog_off + 4)
    tone_off = be32(d, prog_off + 16)  # relative to progOff+8
    tones = []
    p = prog_off + 8 + tone_off
    while p + 14 <= prog_off + prog_size:
        vel = be16(d, p)
        if vel == 0xFFFF:
            break
        tones.append(
            {
                "lo": d[p + 2],
                "hi": d[p + 3],
                "vol": d[p + 8],
                "pan": d[p + 9],
                "sample": be16(d, p + 12),
            }
        )
        p += 14

    if d[smpl_off : smpl_off + 4] != b"Smpl":
        raise ValueError(f"{path.name}: missing Smpl chunk")
    n_smpl = be32(d, smpl_off + 8)
    smpls = []
    p = smpl_off + 16
    for _ in range(n_smpl + 1):
        if d[p : p + 2] == b"\xff\xff":
            break
        smpls.append({"dsp": be16(d, p + 10)})
        p += 12

    if d[dspi_off : dspi_off + 4] != b"Dspi":
        raise ValueError(f"{path.name}: missing Dspi chunk")
    n_dspi = be32(d, dspi_off + 8)
    dsps = []
    p = dspi_off + 16
    for _ in range(n_dspi + 1):
        dsps.append(
            {
                "dpkOffset": be32(d, p),
                "numSamples": be32(d, p + 4),
                "numNibbles": be32(d, p + 8),
                "sampleRate": be32(d, p + 12),
                "loopFlag": be16(d, p + 16),
                "coefs": struct.unpack_from(">16h", d, p + 32),
            }
        )
        p += 100
    return {"tones": tones, "smpls": smpls, "dsps": dsps}


def parse_tsb(path: Path) -> list[dict]:
    d = path.read_bytes()
    if d[0:4] != b"TSBD":
        raise ValueError(f"{path.name}: missing TSBD magic")
    count = struct.unpack_from("<I", d, 0x0C)[0]
    entries = []
    for i in range(count):
        p = 0x10 + i * 16
        entries.append(
            {
                "type": d[p],
                "key": d[p + 3],
                "vol": d[p + 8],
                "pan": d[p + 9],
                "pitch": struct.unpack_from("<h", d, p + 10)[0],
                "next": d[p + 15],
            }
        )
    return entries


def decode_dsp_adpcm(dpk: bytes, rec: dict) -> list[int]:
    """Standard GameCube DSP-ADPCM decode (8-byte frames, 14 samples per frame)."""
    coefs = rec["coefs"]
    out: list[int] = []
    hist1 = hist2 = 0
    num = rec["numSamples"]
    pos = rec["dpkOffset"]
    end = rec["dpkOffset"] + (rec["numNibbles"] + 1) // 2
    while len(out) < num and pos < end:
        header = dpk[pos]
        pos += 1
        scale = 1 << (header & 0x0F)
        c1 = coefs[(header >> 4) * 2]
        c2 = coefs[(header >> 4) * 2 + 1]
        for i in range(14):
            if len(out) >= num or pos >= end:
                break
            byte = dpk[pos]
            nibble = (byte >> 4) if i % 2 == 0 else (byte & 0x0F)
            if i % 2 == 1:
                pos += 1
            if nibble >= 8:
                nibble -= 16
            sample = (nibble * scale * 2048 + c1 * hist1 + c2 * hist2 + 1024) >> 11
            sample = max(-32768, min(32767, sample))
            out.append(sample)
            hist2, hist1 = hist1, sample
    return out


def resolve_id(sound_id: int, banks: dict) -> dict:
    """soundId -> {rate, layers:[{pcm, gain, pan}]} via TSB entry chain + chd tone table."""
    bank_name = BATTLE_SLOTS[sound_id >> 7]
    chd, tsb, dpk = banks[bank_name]
    layers = []
    idx = sound_id & 0x7F
    seen: set[int] = set()
    rate = None
    while idx not in seen:
        seen.add(idx)
        entry = tsb[idx]
        if entry["type"] == 0xFF:
            break
        if entry["type"] != 0:
            raise ValueError(f"id {sound_id:#x}: TSB entry {idx} is type {entry['type']} (sequence), not a one-shot")
        if entry["pitch"] != 0:
            raise ValueError(f"id {sound_id:#x}: nonzero TSB pitch offset {entry['pitch']} unsupported")
        entry_vol = 0x7F if entry["vol"] == 0xFF else entry["vol"]
        for tone in chd["tones"]:
            if not (tone["lo"] <= entry["key"] <= tone["hi"]):
                continue
            dsp = chd["dsps"][chd["smpls"][tone["sample"]]["dsp"]]
            if dsp["loopFlag"]:
                raise ValueError(f"id {sound_id:#x}: looped sample unsupported")
            if rate is None:
                rate = dsp["sampleRate"]
            if dsp["sampleRate"] != rate:
                raise ValueError(f"id {sound_id:#x}: mixed sample rates")
            layers.append(
                {
                    "pcm": decode_dsp_adpcm(dpk, dsp),
                    "gain": (entry_vol / 127.0) * (tone["vol"] / 127.0),
                    "pan": tone["pan"],  # 0x00 hard L .. 0x40 center .. 0x7f hard R
                    "dsp": dsp,
                    "tsbEntry": idx,
                }
            )
        if entry["next"] == 0xFF:
            break
        idx = entry["next"]
    if not layers:
        raise ValueError(f"id {sound_id:#x}: no audible layers resolved")
    if all(layer["gain"] == 0.0 for layer in layers):
        raise ValueError(f"id {sound_id:#x}: all layers muted (TSB vol 0)")
    return {"bank": bank_name, "rate": rate, "layers": layers}


def mix_to_stereo(layers: list[dict]) -> tuple[list[int], list[int]]:
    length = max(len(layer["pcm"]) for layer in layers)
    left = [0.0] * length
    right = [0.0] * length
    for layer in layers:
        pan = layer["pan"] / 127.0  # 0=L .. ~0.5=center .. 1=R
        gl = (1.0 - pan) ** 0.5 * layer["gain"]  # equal-power pan law
        gr = pan**0.5 * layer["gain"]
        for i, s in enumerate(layer["pcm"]):
            left[i] += s * gl
            right[i] += s * gr
    clamp = lambda v: max(-32768, min(32767, int(round(v))))
    return [clamp(v) for v in left], [clamp(v) for v in right]


def write_wav(path: Path, left: list[int], right: list[int], rate: int) -> None:
    frames = bytearray()
    for l, r in zip(left, right):
        frames += struct.pack("<hh", l, r)
    with wave.open(str(path), "wb") as w:
        w.setnchannels(2)
        w.setsampwidth(2)
        w.setframerate(rate)
        w.writeframes(bytes(frames))


def sha1(path: Path) -> str:
    return hashlib.sha1(path.read_bytes()).hexdigest()


def main() -> None:
    export = "--export" in sys.argv[1:]
    banks = {}
    for name in BATTLE_SLOTS:
        chd = parse_chd(BANK_DIR / f"{name}.chd")
        tsb = parse_tsb(BANK_DIR / f"{name}.tsb")
        dpk = (BANK_DIR / f"{name}.dpk").read_bytes()
        banks[name] = (chd, tsb, dpk)

    plans = []
    for sound_id, (event, caller) in sorted(COMBAT_IDS.items()):
        resolved = resolve_id(sound_id, banks)
        key = f"se_{sound_id:03x}"
        duration = max(len(l["pcm"]) for l in resolved["layers"]) / resolved["rate"]
        plans.append((sound_id, key, event, caller, resolved, duration))
        layer_desc = ", ".join(
            f"tsb[{l['tsbEntry']}] dsp@0x{l['dsp']['dpkOffset']:x} gain={l['gain']:.2f} pan=0x{l['pan']:02x}"
            for l in resolved["layers"]
        )
        print(f"0x{sound_id:03x} {key} [{resolved['bank']}] {duration:.3f}s <- {layer_desc}  ({event})")

    if not export:
        print("\ndry run: pass --export to write OGGs and manifest.json")
        return

    OUT_DIR.mkdir(parents=True, exist_ok=True)
    entries = []
    with tempfile.TemporaryDirectory() as tmp:
        for sound_id, key, event, caller, resolved, duration in plans:
            wav_path = Path(tmp) / f"{key}.wav"
            left, right = mix_to_stereo(resolved["layers"])
            write_wav(wav_path, left, right, resolved["rate"])
            ogg_path = OUT_DIR / f"{key}.ogg"
            subprocess.run(
                ["ffmpeg", "-hide_banner", "-loglevel", "error", "-y", "-i", str(wav_path),
                 "-c:a", "libvorbis", "-q:a", "5", str(ogg_path)],
                check=True,
            )
            members = AFS_MEMBERS[resolved["bank"]]
            entries.append(
                {
                    "key": key,
                    "type": "sfx",
                    "path": f"audio/se/{key}.ogg",
                    "durationSec": round(duration, 3),
                    "loop": False,
                    "soundId": sound_id,
                    "bank": sound_id >> 7,
                    "sample": sound_id & 0x7F,
                    "event": event,
                    "callerEvidence": caller,
                    "sourceBank": resolved["bank"],
                    "sourceArchive": "user-data/GG4E/disc/root/afs_data.afs",
                    "afsMembers": members,
                    "layers": [
                        {
                            "tsbEntry": l["tsbEntry"],
                            "dpkOffset": l["dsp"]["dpkOffset"],
                            "numSamples": l["dsp"]["numSamples"],
                            "sampleRate": l["dsp"]["sampleRate"],
                            "gain": round(l["gain"], 4),
                            "pan": l["pan"],
                        }
                        for l in resolved["layers"]
                    ],
                    "sha1": sha1(ogg_path),
                }
            )
            print(f"wrote {ogg_path.relative_to(ROOT)}")

    manifest = {
        "generated": date.today().isoformat(),
        "source": "Gotcha Force (GG4E) afs_data.afs snd_com01/02/03 soundbanks - GC DSP-ADPCM decoded by scripts/export-combat-se.py",
        "format": "OGG Vorbis",
        "idScheme": "key = se_<soundId hex, 3 digits>; soundId = bank<<7 | sample (dispatcher zz_00efb3c_ @ 0x800efb3c)",
        "notes": (
            "DERIVED combat SE: literal soundIds from research/decomp/data/combat-se-ids.json resolved "
            "through the battle TSB/CHD/DPK banks (afs_data.afs members 2839..2847, DOL bank table "
            "DAT_802d0bec @ boot.dol 0x2cdbec). Gains bake in TSB entry volume x CHD tone volume. "
            "Guard-break ids 0x00/0x80/0x100 are TSB-muted (volume 0) in all three banks and are "
            "deliberately NOT exported. id 0x176 is a TSB type-1 sequence command, not a sample."
        ),
        "files": entries,
    }
    manifest_path = OUT_DIR / "manifest.json"
    manifest_path.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    print(f"wrote {manifest_path.relative_to(ROOT)} ({len(entries)} files)")


if __name__ == "__main__":
    main()
