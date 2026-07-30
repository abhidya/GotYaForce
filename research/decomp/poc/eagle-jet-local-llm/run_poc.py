#!/usr/bin/env python3
"""Run a contained local-LLM port-artifact POC for FUN_8012b458.

The model receives authoritative decompile/DOL evidence plus one historical
advisory summary. A deterministic validator gates TypeScript candidate
generation. Nothing under packages/ is modified.
"""

from __future__ import annotations

import hashlib
import json
import os
import re
import struct
import sys
from pathlib import Path
from typing import Any

from dotenv import load_dotenv


HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]
OGHIDRA = ROOT / "research" / "tools" / "OGhidra"
OUTPUT = HERE / "output"
FUNCTION_ADDRESS = "0x8012b458"

sys.path.insert(0, str(OGHIDRA))

from src.config import get_config  # noqa: E402
from src.custom_api_client import CustomAPIClient  # noqa: E402


EXPECTED_CLAIMS: dict[str, Any] = {
    "fx_mode_6e8": {"offset": "0x6e8", "value": "0x83", "frequency": "every_tick"},
    "timer_seed_558": {"offset": "0x558", "value": 45.0, "source_address": "0x80439d80"},
    "retire_hitbox_7f": {"callee": "0x800107a0", "argument": "0x7f"},
    "sound_cue_20": {"callee": "0x800f036c", "argument": "0x20"},
    "prepared_parts_607": {"borg_id": "0x0607", "part_slots": [1, 2], "value": 0},
    "prepared_parts_61b": {"borg_id": "0x061b", "part_slots": [4, 5], "value": 0},
    "timer_decrement": {"offset": "0x558", "delta_offset": "0x1dc8", "operation": "subtract_f32"},
    "expiry_compare": {"timer_offset": "0x558", "operator": "<=", "floor": 0.0},
    "exit_cleanup_call": {"callee": "0x8006a53c", "argument": "0x10"},
    "cleanup_cooldown": {"offset": "0x694", "value": "16_plus_dt"},
    "cleanup_action_bits": {"offset": "0x5e0", "operation": "and", "mask": "0xfffffffc"},
    "cleanup_cue": {"callee": "0x8006a6fc", "argument": "0x1b"},
}


def extract_function(path: Path, address: str, next_address: str) -> str:
    text = path.read_text(encoding="utf-8")
    start = text.index(f"// ==== {address}")
    end = text.index(f"// ==== {next_address}", start)
    return text[start:end].strip()


def read_dol() -> tuple[bytes, list[tuple[int, int, int]]]:
    raw = (ROOT / "user-data" / "GG4E" / "disc" / "sys" / "boot.dol").read_bytes()
    offsets = struct.unpack(">18I", raw[0x00:0x48])
    addresses = struct.unpack(">18I", raw[0x48:0x90])
    sizes = struct.unpack(">18I", raw[0x90:0xD8])
    sections = [
        (offsets[index], addresses[index], sizes[index])
        for index in range(18)
        if sizes[index] > 0
    ]
    return raw, sections


def dol_bytes_at(raw: bytes, sections: list[tuple[int, int, int]], address: int, size: int) -> bytes:
    for file_offset, memory_address, section_size in sections:
        if memory_address <= address and address + size <= memory_address + section_size:
            start = file_offset + address - memory_address
            return raw[start : start + size]
    raise ValueError(f"address 0x{address:08x} is outside DOL sections")


def build_evidence() -> dict[str, Any]:
    target = extract_function(
        ROOT / "research" / "decomp" / "ghidra-export" / "chunk_0034.c",
        "8012b458",
        "8012b554",
    )
    cleanup = extract_function(
        ROOT / "research" / "decomp" / "ghidra-export" / "chunk_0009.c",
        "8006a53c",
        "8006a5a4",
    )
    session_path = (
        ROOT
        / "research"
        / "analysis_sessions"
        / "session_1784383187_d5104c60"
        / "session.json"
    )
    session = json.loads(session_path.read_text(encoding="utf-8"))
    historical = session["analyzed_functions"]["8012b458"]["behavior_summary"]

    dol, sections = read_dol()
    constants: dict[str, Any] = {}
    for address in (0x80439D7C, 0x80439D80):
        raw = dol_bytes_at(dol, sections, address, 4)
        constants[f"0x{address:08x}"] = {
            "raw_hex": raw.hex(),
            "u32_be": f"0x{struct.unpack('>I', raw)[0]:08x}",
            "f32_be": struct.unpack(">f", raw)[0],
        }

    return {
        "program": {
            "name": "boot.dol",
            "sha256": hashlib.sha256(dol).hexdigest(),
            "image_base": "0x80000000",
            "language": "PowerPC:BE:32",
        },
        "records": [
            {
                "id": "decompile:8012b458",
                "tier": "authoritative",
                "kind": "ghidra_decompile",
                "content": target,
            },
            {
                "id": "decompile:8006a53c",
                "tier": "authoritative",
                "kind": "ghidra_decompile",
                "content": cleanup,
            },
            {
                "id": "dol-f32:80439d7c",
                "tier": "authoritative",
                "kind": "dol_big_endian_f32",
                "content": constants["0x80439d7c"],
            },
            {
                "id": "dol-f32:80439d80",
                "tier": "authoritative",
                "kind": "dol_big_endian_f32",
                "content": constants["0x80439d80"],
            },
            {
                "id": "historical-summary:8012b458",
                "tier": "advisory",
                "kind": "prior_llm_summary",
                "content": historical,
                "warning": "Discovery lead only. It may contain confident semantic or numeric errors.",
            },
        ],
    }


def build_prompt(evidence: dict[str, Any], model_name: str) -> str:
    claim_contract = json.dumps(EXPECTED_CLAIMS, indent=2)
    evidence_json = json.dumps(evidence, indent=2)
    return f"""
Produce one strict JSON object for a source-derived port artifact. Do not use Markdown fences and
do not add prose outside the JSON.

Target: FUN_8012b458 at {FUNCTION_ADDRESS}, an action handler used by EAGLE JET.
Model provenance name: {model_name}

Rules:
- Authoritative records may support mechanical claims. The historical summary is advisory only.
- Adjudicate conflicts yourself. In particular, determine whether 0x7f is a duration or a helper
  argument and identify the actual timer seed.
- Preserve offsets, widths, branch direction, comparison operators, helper arguments, and the
  difference between behavior performed by the target and behavior performed by its cleanup callee.
- Make port_ir control flow explicit: route phase 0 to INIT and nonzero phase to DECREMENT; make
  the 0x607 and 0x61b Borg branches mutually exclusive; route unmatched Borg IDs past both setup
  blocks; and encode the expiry comparison with lhs=current_timer, rhs=zero, true target EXPIRE,
  and a false target that returns.
- Do not invent semantic field names. Put interpretations in hypotheses.
- Use exactly the stable claim IDs below. If evidence cannot support one, omit it and explain why
  in unknowns. The `value` for a recovered claim must use exactly the contracted JSON shape.

Claim contract:
{claim_contract}

Required object shape:
{{
  "artifact_schema": 1,
  "producer": {{
    "application": "OGhidra-local-poc",
    "task_mode": "port_1to1",
    "prompt_revision": "eagle-jet-poc-v1",
    "model_name": "{model_name}"
  }},
  "program": {{ "name": "boot.dol", "sha256": "...", "image_base": "0x80000000", "language": "PowerPC:BE:32" }},
  "function": {{ "address": "0x8012b458", "original_name": "FUN_8012b458" }},
  "evidence_refs": ["..."],
  "analysis": {{
    "classification": "code_driven_state_handler",
    "summary": "...",
    "claims": [
      {{
        "id": "stable id from contract",
        "kind": "mechanical_observation",
        "value": {{}},
        "confidence": 0.0,
        "evidence_refs": ["authoritative record id"],
        "verification": "pending"
      }}
    ],
    "hypotheses": [],
    "unknowns": [],
    "dependencies": [],
    "suitability": "typed_handwritten_integration"
  }},
  "port_ir": {{
    "kind": "per_frame_state_handler",
    "entry": [],
    "update": [],
    "exit": []
  }},
  "verification": {{ "status": "unverified", "checks": [] }}
}}

Evidence bundle:
{evidence_json}
""".strip()


def repair_bare_hex_literals(text: str) -> tuple[str, list[dict[str, Any]]]:
    """Convert JSON-invalid bare 0x literals to decimal without touching strings."""
    repaired: list[str] = []
    repairs: list[dict[str, Any]] = []
    index = 0
    in_string = False
    escaped = False
    while index < len(text):
        char = text[index]
        if in_string:
            repaired.append(char)
            if escaped:
                escaped = False
            elif char == "\\":
                escaped = True
            elif char == '"':
                in_string = False
            index += 1
            continue
        if char == '"':
            in_string = True
            repaired.append(char)
            index += 1
            continue
        match = re.match(r"0x[0-9a-fA-F]+", text[index:])
        if match:
            original = match.group(0)
            replacement = str(int(original, 16))
            repaired.append(replacement)
            repairs.append({"kind": "bare_hex_to_decimal", "from": original, "to": replacement})
            index += len(original)
            continue
        repaired.append(char)
        index += 1
    return "".join(repaired), repairs


def extract_json(raw_response: str) -> tuple[dict[str, Any], list[dict[str, Any]]]:
    text = raw_response.strip()
    fenced = re.search(r"```(?:json)?\s*(\{.*\})\s*```", text, flags=re.DOTALL | re.IGNORECASE)
    if fenced:
        text = fenced.group(1)
    try:
        return json.loads(text), []
    except json.JSONDecodeError:
        repaired, repairs = repair_bare_hex_literals(text)
        return json.loads(repaired), repairs


def canonical(value: Any) -> Any:
    if isinstance(value, dict):
        return {key: canonical(value[key]) for key in sorted(value)}
    if isinstance(value, list):
        return [canonical(item) for item in value]
    if isinstance(value, str) and value.startswith("0x"):
        return value.lower()
    return value


def validate_artifact(artifact: dict[str, Any], evidence: dict[str, Any]) -> dict[str, Any]:
    checks: list[dict[str, Any]] = []

    def check(name: str, passed: bool, detail: str) -> None:
        checks.append({"name": name, "passed": bool(passed), "detail": detail})

    check("schema-version", artifact.get("artifact_schema") == 1, "artifact_schema must be 1")
    check(
        "normalized-address",
        artifact.get("function", {}).get("address") == FUNCTION_ADDRESS,
        f"function address must be {FUNCTION_ADDRESS}",
    )
    check(
        "program-identity",
        artifact.get("program", {}).get("sha256") == evidence["program"]["sha256"],
        "artifact must preserve the evidence bundle's boot.dol SHA-256",
    )

    known_refs = {record["id"] for record in evidence["records"]}
    claims = artifact.get("analysis", {}).get("claims", [])
    claims_by_id = {
        claim.get("id"): claim for claim in claims if isinstance(claim, dict) and claim.get("id")
    }
    for claim_id, expected in EXPECTED_CLAIMS.items():
        claim = claims_by_id.get(claim_id)
        check(f"claim-present:{claim_id}", claim is not None, "required Eagle Jet mechanical claim")
        if claim is None:
            continue
        check(
            f"claim-value:{claim_id}",
            canonical(claim.get("value")) == canonical(expected),
            f"expected {json.dumps(expected, sort_keys=True)}; got {json.dumps(claim.get('value'), sort_keys=True)}",
        )
        refs = claim.get("evidence_refs", [])
        check(
            f"claim-evidence:{claim_id}",
            bool(refs) and all(ref in known_refs for ref in refs) and all(not ref.startswith("historical-summary:") for ref in refs),
            "claim must cite only known authoritative evidence records",
        )

    response_text = json.dumps(artifact).lower()
    bad_duration = "127-frame" in response_text or "127 frame" in response_text or "duration\": 127" in response_text
    check(
        "historical-0x7f-misread-rejected",
        not bad_duration,
        "0x7f is zz_00107a0_ argument, not the 45-frame timer seed",
    )
    check(
        "no-unsupported-fully-integrated",
        artifact.get("verification", {}).get("status") != "verified",
        "model output must remain unverified until deterministic checks finish",
    )

    update_ir = artifact.get("port_ir", {}).get("update", [])
    timer_seed_index = next(
        (
            index
            for index, row in enumerate(update_ir)
            if isinstance(row, dict)
            and row.get("offset") == "0x558"
            and row.get("type") in {"write_f32", "store_f32"}
            and row.get("value") in {"timer_base", "fVar2"}
        ),
        None,
    )
    decrement_index = next(
        (
            index
            for index, row in enumerate(update_ir)
            if isinstance(row, dict)
            and (
                row.get("offset") == "0x1dc8"
                or row.get("type") == "sub_f32"
                or (
                    row.get("offset") == "0x558"
                    and isinstance(row.get("value"), str)
                    and "delta" in row["value"]
                )
            )
        ),
        None,
    )
    init_separated = False
    if (
        isinstance(timer_seed_index, int)
        and isinstance(decrement_index, int)
        and timer_seed_index < decrement_index
    ):
        between = update_ir[timer_seed_index + 1 : decrement_index]
        init_separated = any(
            isinstance(row, dict)
            and (
                row.get("type") in {"return", "stop"}
                or (row.get("type") == "branch" and row.get("target") == "return")
            )
            for row in between
        )
    check(
        "port-ir-init-update-exclusive",
        init_separated,
        "the initialization branch must return and must not fall through into timer decrement",
    )

    entry_ir = artifact.get("port_ir", {}).get("entry", [])
    phase_branch = next(
        (
            row
            for row in entry_ir
            if isinstance(row, dict)
            and row.get("type") == "branch_if_zero"
            and row.get("offset") == "0x540"
            and row.get("target_label") == "INIT"
        ),
        None,
    )
    update_route = bool(
        isinstance(phase_branch, dict)
        and (
            phase_branch.get("false_target") == "DECREMENT"
            or any(
                isinstance(row, dict)
                and row.get("type") in {"branch", "jump"}
                and row.get("target_label", row.get("target")) == "DECREMENT"
                for row in entry_ir[entry_ir.index(phase_branch) + 1 :]
            )
        )
    )
    check(
        "port-ir-entry-routes-both-paths",
        update_route,
        "phase 0 must route to INIT and the false path must route explicitly to DECREMENT",
    )

    def branch_value(row: dict[str, Any]) -> Any:
        value = row.get("value")
        if isinstance(value, str) and value.startswith("0x"):
            return int(value, 16)
        return value

    borg_607_branch = next(
        (
            (index, row)
            for index, row in enumerate(update_ir)
            if isinstance(row, dict)
            and row.get("type") == "branch_if_eq"
            and branch_value(row) == 0x607
        ),
        None,
    )
    borg_61b_branch = next(
        (
            (index, row)
            for index, row in enumerate(update_ir)
            if isinstance(row, dict)
            and row.get("type") == "branch_if_eq"
            and branch_value(row) == 0x61B
        ),
        None,
    )
    check(
        "port-ir-borg-branches-use-loaded-id",
        bool(
            borg_607_branch
            and borg_61b_branch
            and borg_607_branch[1].get("source") == "borg_id"
            and borg_61b_branch[1].get("source") == "borg_id"
        ),
        "both Borg comparisons must name the loaded borg_id operand",
    )

    labels = {
        row.get("id"): index
        for index, row in enumerate(update_ir)
        if isinstance(row, dict) and row.get("type") == "label"
    }

    def has_exit_between(start: int, end: int) -> bool:
        return any(
            isinstance(row, dict)
            and (
                row.get("type") in {"return", "stop"}
                or (
                    row.get("type") in {"branch", "jump"}
                    and row.get("target_label", row.get("target")) in {"INIT_DONE", "RETURN"}
                )
            )
            for row in update_ir[start:end]
        )

    idx_607 = labels.get("BORG_607")
    idx_61b = labels.get("BORG_61B")
    idx_decrement = labels.get("DECREMENT")
    unmatched_skips = bool(
        borg_61b_branch
        and isinstance(idx_607, int)
        and has_exit_between(borg_61b_branch[0] + 1, idx_607)
    )
    branch_607_exits = bool(
        isinstance(idx_607, int)
        and isinstance(idx_61b, int)
        and has_exit_between(idx_607 + 1, idx_61b)
    )
    branch_61b_exits = bool(
        isinstance(idx_61b, int)
        and isinstance(idx_decrement, int)
        and has_exit_between(idx_61b + 1, idx_decrement)
    )
    check(
        "port-ir-borg-branches-mutually-exclusive",
        unmatched_skips and branch_607_exits and branch_61b_exits,
        "unmatched, 0x607, and 0x61b initialization paths must not fall through into each other",
    )

    expiry_branch = next(
        (
            (index, row)
            for index, row in enumerate(update_ir)
            if isinstance(row, dict) and row.get("type") == "branch_if_lte"
        ),
        None,
    )
    expiry_explicit = bool(
        expiry_branch
        and expiry_branch[1].get("lhs") == "current_timer"
        and expiry_branch[1].get("rhs") in {0, 0.0, "zero"}
        and expiry_branch[1].get("target_label") == "EXPIRE"
        and expiry_branch[1].get("false_target") in {"RETURN", "UPDATE_DONE"}
    )
    check(
        "port-ir-expiry-operands-and-paths",
        expiry_explicit,
        "expiry must encode current_timer <= zero with explicit true and false targets",
    )

    passed = all(item["passed"] for item in checks)
    return {
        "artifact_schema": artifact.get("artifact_schema"),
        "function": FUNCTION_ADDRESS,
        "passed": passed,
        "checks_passed": sum(item["passed"] for item in checks),
        "checks_total": len(checks),
        "checks": checks,
    }


def correction_prompt(
    artifact: dict[str, Any],
    report: dict[str, Any],
    model_name: str,
) -> str:
    failures = [item for item in report["checks"] if not item["passed"]]
    return f"""
Return one complete strict JSON artifact and nothing else. Correct only the deterministic failures
listed below. Preserve all already-correct claims, evidence references, provenance, and unverified
status. JSON does not allow bare hexadecimal numeric literals: quote hex values or use decimal.
The target's initialization path and per-frame decrement path are an if/else; initialization must
return without decrementing the freshly seeded timer.
For port_ir, use `source: "borg_id"` on both Borg comparisons. After the two comparisons, jump to
`INIT_DONE` for the unmatched case. End each Borg block by jumping to `INIT_DONE`. Define
`INIT_DONE` as a return. The entry phase branch must use `false_target: "DECREMENT"`. Encode expiry
as `{{"type":"branch_if_lte","lhs":"current_timer","rhs":"zero","target_label":"EXPIRE",
"false_target":"RETURN"}}`, and define RETURN as a return.
The Borg dispatch must have this exact control-flow shape (with the existing calls retained):
`branch_if_eq(source=borg_id,value=0x607,target=BORG_607)`;
`branch_if_eq(source=borg_id,value=0x61b,target=BORG_61B)`; unconditional `jump INIT_DONE`;
`BORG_607`; its two calls; unconditional `jump INIT_DONE`;
`BORG_61B`; its two calls; unconditional `jump INIT_DONE`; `INIT_DONE`; `return`.

Model: {model_name}

Failures:
{json.dumps(failures, indent=2)}

Artifact to repair:
{json.dumps(artifact, indent=2)}
""".strip()


def compare_handwritten_port() -> dict[str, Any]:
    source = (ROOT / "packages" / "combat" / "src" / "families" / "eagle-jet.ts").read_text(encoding="utf-8")
    expected_tokens = {
        "duration_45": "DURATION: 45.0",
        "fx_mode_83": "FX_MODE: 0x83",
        "hitbox_7f": "HITBOX_KIND: 0x7f",
        "cue_20": "SOUND_CUE: 0x20",
        "cleanup_10": "EXIT_COOLDOWN: 0x10",
        "exit_cue_1b": "EXIT_CUE: 0x1b",
        "parts_4_5": "PREPARED_PARTS: [4, 5]",
    }
    checks = {name: token in source for name, token in expected_tokens.items()}
    return {"passed": all(checks.values()), "checks": checks}


def render_candidate(artifact: dict[str, Any]) -> str:
    values = {claim["id"]: claim["value"] for claim in artifact["analysis"]["claims"]}
    duration = values["timer_seed_558"]["value"]
    return f"""// Generated POC candidate from a deterministically validated local-LLM artifact.
// Untrusted integration scaffold: this file is not imported by production code.

export interface EagleJetPocActor {{
  borgNumber: number;
  phase: number;
  timer: number;
  dt: number;
  effectMode: number;
  controlWord: number;
}}

export interface EagleJetPocHost {{
  retireHitbox(actor: EagleJetPocActor, kind: number): void;
  playCue(actor: EagleJetPocActor, cue: number): void;
  preparePart(actor: EagleJetPocActor, slot: number, value: number): void;
  cleanup(actor: EagleJetPocActor, cooldown: number): void;
}}

export function stepFun8012b458(actor: EagleJetPocActor, host: EagleJetPocHost): void {{
  actor.effectMode = 0x83;
  if (actor.phase === 0) {{
    actor.phase = 1;
    actor.timer = {duration:.1f};
    host.retireHitbox(actor, 0x7f);
    host.playCue(actor, 0x20);
    if (actor.borgNumber === 0x607) {{
      host.preparePart(actor, 1, 0);
      host.preparePart(actor, 2, 0);
    }} else if (actor.borgNumber === 0x61b) {{
      host.preparePart(actor, 4, 0);
      host.preparePart(actor, 5, 0);
    }}
    return;
  }}
  actor.timer -= actor.dt;
  if (actor.timer <= 0) host.cleanup(actor, 0x10);
}}
"""


def main() -> int:
    OUTPUT.mkdir(parents=True, exist_ok=True)
    evidence = build_evidence()
    (OUTPUT / "evidence-bundle.json").write_text(json.dumps(evidence, indent=2) + "\n", encoding="utf-8")

    reuse_arg = next((arg for arg in sys.argv if arg.startswith("--reuse-attempt-")), None)
    reuse_attempt = int(reuse_arg.rsplit("-", 1)[1]) if reuse_arg else 0
    reuse_saved_attempt = reuse_arg is not None
    repair_saved_attempt = any(arg.startswith("--repair-attempt-") for arg in sys.argv)
    if reuse_saved_attempt:
        repaired_response = (OUTPUT / f"raw-response-attempt-{reuse_attempt}.txt").read_text(encoding="utf-8")
        artifact, second_repairs = extract_json(repaired_response)
        report = validate_artifact(artifact, evidence)
        attempts = [{
            "attempt": reuse_attempt,
            "reused_saved_response": True,
            "syntax_repairs": second_repairs,
            "passed": report["passed"],
            "checks_passed": report["checks_passed"],
            "checks_total": report["checks_total"],
        }]
        model_name = artifact.get("producer", {}).get("model_name", "unknown")
        if not report["passed"] and repair_saved_attempt:
            load_dotenv(OGHIDRA / ".env", override=True)
            config = get_config()
            config.custom_api.llm_logging_enabled = False
            client = CustomAPIClient(config.custom_api)
            repaired_response = client.generate(
                prompt=correction_prompt(artifact, report, model_name),
                system_prompt=(
                    "You repair a structured port artifact using deterministic validator feedback. "
                    "Do not add facts, remove evidence, or promote verification status."
                ),
                temperature=0.1,
                max_tokens=6000,
                phase="review",
            )
            next_attempt = reuse_attempt + 1
            (OUTPUT / f"raw-response-attempt-{next_attempt}.txt").write_text(repaired_response + "\n", encoding="utf-8")
            artifact, third_repairs = extract_json(repaired_response)
            report = validate_artifact(artifact, evidence)
            attempts.append(
                {
                    "attempt": next_attempt,
                    "syntax_repairs": third_repairs,
                    "passed": report["passed"],
                    "checks_passed": report["checks_passed"],
                    "checks_total": report["checks_total"],
                }
            )
    else:
        load_dotenv(OGHIDRA / ".env", override=True)
        config = get_config()
        config.custom_api.llm_logging_enabled = False
        client = CustomAPIClient(config.custom_api)
        model_name = config.custom_api.model
        prompt = build_prompt(evidence, model_name)
        (OUTPUT / "prompt.txt").write_text(prompt + "\n", encoding="utf-8")

        raw_response = client.generate(
            prompt=prompt,
            system_prompt=(
                "You extract mechanically exact PowerPC game behavior into strict JSON. "
                "Authoritative evidence outranks prior LLM prose. Never invent missing semantics."
            ),
            temperature=0.1,
            max_tokens=6000,
            phase="analysis",
        )
        (OUTPUT / "raw-response-attempt-1.txt").write_text(raw_response + "\n", encoding="utf-8")

        artifact, repairs = extract_json(raw_response)
        report = validate_artifact(artifact, evidence)
        attempts = [
            {
                "attempt": 1,
                "syntax_repairs": repairs,
                "passed": report["passed"],
                "checks_passed": report["checks_passed"],
                "checks_total": report["checks_total"],
            }
        ]
        if not report["passed"]:
            repaired_response = client.generate(
                prompt=correction_prompt(artifact, report, model_name),
                system_prompt=(
                    "You repair a structured port artifact using deterministic validator feedback. "
                    "Do not add facts, remove evidence, or promote verification status."
                ),
                temperature=0.1,
                max_tokens=6000,
                phase="review",
            )
            (OUTPUT / "raw-response-attempt-2.txt").write_text(repaired_response + "\n", encoding="utf-8")
            artifact, second_repairs = extract_json(repaired_response)
            report = validate_artifact(artifact, evidence)
            attempts.append(
                {
                    "attempt": 2,
                    "syntax_repairs": second_repairs,
                    "passed": report["passed"],
                    "checks_passed": report["checks_passed"],
                    "checks_total": report["checks_total"],
                }
            )

    comparison = compare_handwritten_port()
    report["attempts"] = attempts
    report["handwritten_port_comparison"] = comparison
    artifact["verification"] = {
        "status": "verified" if report["passed"] and comparison["passed"] else "failed",
        "checks_passed": report["checks_passed"],
        "checks_total": report["checks_total"],
    }

    (OUTPUT / "artifact.json").write_text(json.dumps(artifact, indent=2) + "\n", encoding="utf-8")
    (OUTPUT / "validation-report.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")

    candidate_path = OUTPUT / "fn_8012b458.generated.ts"
    if report["passed"] and comparison["passed"]:
        candidate_path.write_text(render_candidate(artifact), encoding="utf-8")
    elif candidate_path.exists():
        candidate_path.unlink()

    print(
        json.dumps(
            {
                "model": model_name,
                "artifact": str(OUTPUT / "artifact.json"),
                "validation": str(OUTPUT / "validation-report.json"),
                "passed": report["passed"],
                "checks": f"{report['checks_passed']}/{report['checks_total']}",
                "handwrittenComparison": comparison["passed"],
                "candidateGenerated": candidate_path.exists(),
            },
            indent=2,
        )
    )
    return 0 if report["passed"] and comparison["passed"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
