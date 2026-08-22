from __future__ import annotations

import copy
import hashlib
import json
import os
import subprocess
import sys
from collections.abc import Callable
from pathlib import Path

import pytest


DATA_DIR = Path(__file__).resolve().parent
PRODUCT_ROOT = DATA_DIR.parents[2]
if str(DATA_DIR) not in sys.path:
    sys.path.insert(0, str(DATA_DIR))

import build_oracle_registry as producer
import build_unit_priority as priority_consumer
import oracle_registry_schema as schema_contract
from oracle_registry_schema import (
    OracleRegistryValidationError,
    load_oracle_registry_v1,
    validate_oracle_registry_v1,
)


MARKER_WINS_ROWS = (
    ("zz_00262b4_", "0x800262b4", "0x80026250", "auto-c0003-004"),
    ("zz_00c3484_", "0x800c3484", "0x800c2d4c", "auto-c0020-004"),
    ("zz_0147d74_", "0x80147d74", "0x80147ce4", "auto-c0038-005"),
    ("zz_0181c70_", "0x80181c70", "0x80181c54", "auto-c0045-009"),
    ("zz_01aadb4_", "0x801aadb4", "0x801aad50", "auto-c0051-010"),
    ("zz_0232a10_", "0x80232a10", "0x80232a08", "auto-c0068-012"),
    ("zz_0281554_", "0x80281554", "0x802813dc", "auto-c0076-007"),
    ("zz_02a8e80_", "0x802a8e80", "0x802a8b3c", "auto-c0078-016"),
)
COORDINATE_CATALOG_SHA256 = (
    "f6f8b9d73e5e29d6ae66fabea4ea0c0a2cccb26b43b3a18a8103cab90dfff5cc"
)
EXCLUSION_CATALOG_SHA256 = (
    "7c59595c9480f3a0eff65240c9e32f893957cbf4d1a017b97cc08d142e74a2fa"
)


def _anomaly(name: str, encoded: str, marker: str) -> str:
    return (
        f"{name}: name addr {int(encoded, 16):08x} != marker "
        f"{int(marker, 16):08x} (marker wins)"
    )


def _catalog_sha256(registry: dict) -> str:
    rows = [
        [
            function["name"],
            function["address"],
            function["unit"],
            function["chunk_file"],
            function["line_range"],
        ]
        for function in registry["functions"]
    ]
    payload = (json.dumps(rows, ensure_ascii=False, separators=(",", ":")) + "\n").encode()
    return hashlib.sha256(payload).hexdigest()


def _exclusion_catalog_sha256(registry: dict) -> str:
    payload = (
        json.dumps(registry["excluded"], ensure_ascii=False, separators=(",", ":"))
        + "\n"
    ).encode()
    return hashlib.sha256(payload).hexdigest()


def _expected_marker_rows(registry: dict) -> list[tuple[str, str, str]]:
    by_name = {function["name"]: function for function in registry["functions"]}
    observed = []
    for name, encoded, marker, unit in MARKER_WINS_ROWS:
        function = by_name[name]
        assert function["address"] == marker
        assert function["unit"] == unit
        observed.append((name, encoded, marker))
    assert registry["summary"]["anomalies"] == [
        _anomaly(name, encoded, marker)
        for name, encoded, marker, _unit in MARKER_WINS_ROWS
    ]
    return observed


def _synthetic_product(tmp_path: Path) -> tuple[Path, dict]:
    root = tmp_path / "product"
    chunks = root / "research" / "decomp" / "ghidra-export"
    chunks.mkdir(parents=True)
    functions = []
    index_lines = ["address\tname\tchunk_file"]
    for ordinal, (name, _encoded, marker, unit) in enumerate(MARKER_WINS_ROWS):
        chunk_name = f"chunk_{ordinal:04d}.c"
        relative = f"research/decomp/ghidra-export/{chunk_name}"
        params = [] if ordinal % 2 == 0 else ["void"]
        param_text = "" if not params else "void"
        (chunks / chunk_name).write_text(
            f"// ==== {marker[2:]}  {name} ====\n"
            f"int {name}({param_text}) {{ return {ordinal}; }}\n",
            encoding="utf-8",
            newline="\n",
        )
        index_lines.append(f"{marker[2:]}\t{name}\t{chunk_name}")
        functions.append(
            {
                "name": name,
                "address": marker,
                "unit": unit,
                "chunk_file": relative,
                "line_range": [1, 2],
                "loc": 2,
                "return_type": "int",
                "params": params,
                "returns_value": True,
                "has_pointer_args": False,
                "external_callees": {"count": 0, "list": []},
                "global_refs": [],
                "structural_class": "A",
                "ts_citations": [],
                "citation_grade": "none",
                "citation_scan_skipped": None,
                "gap_alignment": None,
            }
        )
    (chunks / "_index.tsv").write_text(
        "\n".join(index_lines) + "\n", encoding="utf-8", newline="\n"
    )
    functions.sort(key=lambda function: (function["address"], function["name"]))
    units = sorted(function["unit"] for function in functions)
    ranked_units = [
        {
            "unit": unit,
            "oracle_kind": "compile_only",
            "fn_count": 1,
            "gap_partial_slots": 0,
            "gap_family_ctors": [],
            "port_citations": 0,
            "port_grade_fns": 0,
            "total_citations": 0,
            "max_structural_class": "A",
            "total_loc": 2,
            "fully_gap_aligned": False,
        }
        for unit in units
    ]
    registry = {
        "oracle_registry_schema": 1,
        "meta": {
            "generated_by": "synthetic-test",
            "inputs": {
                "queue": "research/decomp/generated/queue.json",
                "skipped": "research/decomp/generated/skipped.json",
                "chunk_index": "research/decomp/ghidra-export/_index.tsv",
                "family_coverage": "research/decomp/data/family.json",
            },
            "conventions": {
                "address": "synthetic",
                "structural_class": "synthetic",
                "citation_grade": "synthetic",
                "gap_alignment": "synthetic",
                "ranked_units_sort": "synthetic",
                "oracle_able_units": "synthetic",
            },
        },
        "summary": {
            "functions_total": 8,
            "units_total": 8,
            "excluded_total": 0,
            "excluded_reasons": {},
            "structural_class_counts": {"A": 8},
            "citation_grade_counts": {"none": 8},
            "class_by_citation_grade": {"A": {"none": 8}},
            "gap_aligned_functions": 0,
            "gap_aligned_functions_partial_family": 0,
            "fully_gap_aligned_units": 0,
            "fully_gap_aligned_unit_names": [],
            "oracle_able_units": {
                "differential_vs_ts": 0,
                "state_diff": 0,
                "citations_no_family": 0,
                "trace_only": 8,
            },
            "oracle_able_unit_names": {
                "differential_vs_ts": [],
                "state_diff": [],
                "citations_no_family": [],
                "trace_only": units,
            },
            "anomalies": [
                _anomaly(name, encoded, marker)
                for name, encoded, marker, _unit in MARKER_WINS_ROWS
            ],
        },
        "ranked_units": ranked_units,
        "functions": functions,
        "excluded": [],
    }
    return root, registry


def _make_nonanomalous_encoded_index_mismatch(
    root: Path, registry: dict, owner_name: str, wrong_index_name: str
) -> None:
    function = registry["functions"][0]
    old_name = function["name"]
    old_anomaly = registry["summary"]["anomalies"].pop(0)
    assert old_anomaly.startswith(old_name + ":")
    function["name"] = owner_name
    owner_path = root.joinpath(*function["chunk_file"].split("/"))
    owner_path.write_text(
        owner_path.read_text(encoding="utf-8").replace(old_name, owner_name),
        encoding="utf-8",
        newline="\n",
    )
    index_path = root / "research" / "decomp" / "ghidra-export" / "_index.tsv"
    lines = index_path.read_text(encoding="utf-8").splitlines()
    marker_text = function["address"][2:]
    for index, line in enumerate(lines):
        if line.startswith(marker_text + "\t"):
            fields = line.split("\t")
            fields[1] = wrong_index_name
            lines[index] = "\t".join(fields)
            break
    else:
        raise AssertionError("synthetic index row not found")
    index_path.write_text("\n".join(lines) + "\n", encoding="utf-8", newline="\n")


def _race_input(
    tmp_path: Path, target_kind: str
) -> tuple[Path, dict, Path, Path, str, Callable[[], object]]:
    root, registry = _synthetic_product(tmp_path)
    if target_kind == "registry":
        container = root / "registry-input"
        container.mkdir()
        target = container / "oracle-registry.json"
        target.write_text(
            json.dumps(registry) + "\n", encoding="utf-8", newline="\n"
        )
        where = "oracle registry"
        invoke = lambda: load_oracle_registry_v1(target, root)
    elif target_kind == "index":
        target = root / "research" / "decomp" / "ghidra-export" / "_index.tsv"
        container = target.parent
        where = "chunk index"
        invoke = lambda: validate_oracle_registry_v1(registry, root)
    elif target_kind == "owner":
        function = registry["functions"][0]
        target = root.joinpath(*function["chunk_file"].split("/"))
        container = target.parent
        where = "owner file " + function["chunk_file"]
        invoke = lambda: validate_oracle_registry_v1(registry, root)
    else:
        raise AssertionError(f"unknown target kind {target_kind!r}")
    return root, registry, container, target, where, invoke


def _install_path_race(
    monkeypatch: pytest.MonkeyPatch, where: str, mutation: Callable[[], None]
) -> dict[str, bool]:
    real_exact_file_path = schema_contract._exact_file_path
    state = {"fired": False}

    def racing_exact_file_path(product_root: Path, path: Path, observed_where: str):
        binding = real_exact_file_path(product_root, path, observed_where)
        if not state["fired"] and observed_where == where:
            state["fired"] = True
            mutation()
        return binding

    monkeypatch.setattr(schema_contract, "_exact_file_path", racing_exact_file_path)
    return state


def _install_post_eof_path_race(
    monkeypatch: pytest.MonkeyPatch, where: str, mutation: Callable[[], None]
) -> dict[str, bool]:
    real_exact_file_path = schema_contract._exact_file_path
    state = {"calls": 0, "fired": False}

    def racing_exact_file_path(product_root: Path, path: Path, observed_where: str):
        if observed_where == where:
            state["calls"] += 1
            if state["calls"] == 2 and not state["fired"]:
                state["fired"] = True
                mutation()
        return real_exact_file_path(product_root, path, observed_where)

    monkeypatch.setattr(schema_contract, "_exact_file_path", racing_exact_file_path)
    return state


def _create_directory_reparse(link: Path, target: Path) -> None:
    if os.name == "nt":
        completed = subprocess.run(
            ["cmd.exe", "/d", "/c", "mklink", "/J", str(link), str(target)],
            check=False,
            capture_output=True,
            text=True,
            creationflags=getattr(subprocess, "CREATE_NO_WINDOW", 0),
        )
        if completed.returncode:
            raise AssertionError(
                f"failed to create test junction: {completed.stdout}{completed.stderr}"
            )
    else:
        link.symlink_to(target, target_is_directory=True)


def _remove_directory_reparse(path: Path) -> None:
    if os.name == "nt":
        os.rmdir(path)
    else:
        path.unlink()


def test_producer_regeneration_is_schema_v1_and_byte_deterministic() -> None:
    command = [sys.executable, str(DATA_DIR / "build_oracle_registry.py")]
    subprocess.run(command, cwd=PRODUCT_ROOT, check=True, capture_output=True, text=True)
    first = (DATA_DIR / "oracle-registry.json").read_bytes()
    subprocess.run(command, cwd=PRODUCT_ROOT, check=True, capture_output=True, text=True)
    second = (DATA_DIR / "oracle-registry.json").read_bytes()
    assert first == second

    registry = load_oracle_registry_v1(DATA_DIR / "oracle-registry.json", PRODUCT_ROOT)
    assert registry["oracle_registry_schema"] == 1
    assert len(registry["functions"]) == 10_954
    assert len(registry["excluded"]) == 1_018
    assert _exclusion_catalog_sha256(registry) == EXCLUSION_CATALOG_SHA256
    assert len(registry["summary"]["anomalies"]) == 8
    assert _catalog_sha256(registry) == COORDINATE_CATALOG_SHA256
    _expected_marker_rows(registry)


def test_producer_preserves_unspecified_and_explicit_void_spelling() -> None:
    assert producer.split_params("") == []
    assert producer.split_params("void") == ["void"]
    assert producer.split_params("int (*callback)(int, int), void *context") == [
        "int (*callback)(int, int)",
        "void *context",
    ]


def test_shared_validator_accepts_all_eight_marker_wins_rows_and_void_forms(
    tmp_path: Path,
) -> None:
    root, registry = _synthetic_product(tmp_path)
    validated = validate_oracle_registry_v1(registry, root)
    _expected_marker_rows(validated)
    assert [function["params"] for function in validated["functions"][:2]] == [
        [],
        ["void"],
    ]


@pytest.mark.parametrize("schema", [None, True, "1", 0, 2])
def test_shared_validator_rejects_non_v1_schema(tmp_path: Path, schema: object) -> None:
    root, registry = _synthetic_product(tmp_path)
    registry["oracle_registry_schema"] = schema
    with pytest.raises(OracleRegistryValidationError, match="oracle_registry_schema"):
        validate_oracle_registry_v1(registry, root)


def test_shared_validator_rejects_missing_schema(tmp_path: Path) -> None:
    root, registry = _synthetic_product(tmp_path)
    del registry["oracle_registry_schema"]
    with pytest.raises(OracleRegistryValidationError):
        validate_oracle_registry_v1(registry, root)


@pytest.mark.parametrize("schema", [None, True, "1", 0, 2])
def test_priority_consumer_rejects_non_v1_before_use(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch, schema: object
) -> None:
    root = tmp_path / "product"
    root.mkdir()
    registry_path = root / "oracle-registry.json"
    registry_path.write_text(
        json.dumps({"oracle_registry_schema": schema}) + "\n",
        encoding="utf-8",
        newline="\n",
    )
    output_path = root / "unit-priority.json"
    monkeypatch.setattr(priority_consumer, "PRODUCT_ROOT", root)
    monkeypatch.setattr(priority_consumer, "REGISTRY_PATH", registry_path)
    monkeypatch.setattr(priority_consumer, "OUTPUT_PATH", output_path)
    with pytest.raises(OracleRegistryValidationError):
        priority_consumer.main()
    assert not output_path.exists()


def test_priority_consumer_rejects_missing_schema_before_use(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    root = tmp_path / "product"
    root.mkdir()
    registry_path = root / "oracle-registry.json"
    registry_path.write_text("{}\n", encoding="utf-8", newline="\n")
    output_path = root / "unit-priority.json"
    monkeypatch.setattr(priority_consumer, "PRODUCT_ROOT", root)
    monkeypatch.setattr(priority_consumer, "REGISTRY_PATH", registry_path)
    monkeypatch.setattr(priority_consumer, "OUTPUT_PATH", output_path)
    with pytest.raises(OracleRegistryValidationError):
        priority_consumer.main()
    assert not output_path.exists()


def test_priority_consumer_preserves_v1_owner_rows_and_parameter_spelling(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    root, source_registry = _synthetic_product(tmp_path)
    registry_path = root / "oracle-registry.json"
    registry_path.write_text(
        json.dumps(source_registry) + "\n", encoding="utf-8", newline="\n"
    )
    monkeypatch.setattr(priority_consumer, "PRODUCT_ROOT", root)
    monkeypatch.setattr(priority_consumer, "REGISTRY_PATH", registry_path)
    registry = priority_consumer.load_registry_for_priority()
    assert len(priority_consumer.build_priorities(registry)) == 8
    _expected_marker_rows(registry)
    assert {tuple(function["params"]) for function in registry["functions"]} == {
        (),
        ("void",),
    }


@pytest.mark.parametrize(
    ("owner_name", "wrong_index_name"),
    [
        ("zz_0026250_", "zz_0026251_"),
        ("FUN_80026250", "FUN_80026251"),
    ],
)
def test_producer_rejects_nonanomalous_encoded_index_label_mismatch(
    tmp_path: Path, owner_name: str, wrong_index_name: str
) -> None:
    root, registry = _synthetic_product(tmp_path)
    _make_nonanomalous_encoded_index_mismatch(
        root, registry, owner_name, wrong_index_name
    )
    with pytest.raises(OracleRegistryValidationError, match="encoded owner label"):
        producer.validate_oracle_registry_v1(registry, root)


@pytest.mark.parametrize(
    ("owner_name", "wrong_index_name"),
    [
        ("zz_0026250_", "zz_0026251_"),
        ("FUN_80026250", "FUN_80026251"),
    ],
)
def test_priority_consumer_rejects_nonanomalous_encoded_index_label_mismatch(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
    owner_name: str,
    wrong_index_name: str,
) -> None:
    root, registry = _synthetic_product(tmp_path)
    _make_nonanomalous_encoded_index_mismatch(
        root, registry, owner_name, wrong_index_name
    )
    registry_path = root / "oracle-registry.json"
    registry_path.write_text(
        json.dumps(registry) + "\n", encoding="utf-8", newline="\n"
    )
    output_path = root / "unit-priority.json"
    monkeypatch.setattr(priority_consumer, "PRODUCT_ROOT", root)
    monkeypatch.setattr(priority_consumer, "REGISTRY_PATH", registry_path)
    monkeypatch.setattr(priority_consumer, "OUTPUT_PATH", output_path)
    with pytest.raises(OracleRegistryValidationError, match="encoded owner label"):
        priority_consumer.main()
    assert not output_path.exists()


@pytest.mark.parametrize(
    "mutation",
    [
        "missing_marker",
        "wrong_marker",
        "index_disagreement",
        "missing_anomaly",
        "extra_anomaly",
        "duplicate_name",
        "duplicate_address",
    ],
)
def test_marker_index_anomaly_and_owner_multiplicity_refusals(
    tmp_path: Path, mutation: str
) -> None:
    root, registry = _synthetic_product(tmp_path)
    first = registry["functions"][0]
    first_path = root.joinpath(*first["chunk_file"].split("/"))
    if mutation == "missing_marker":
        lines = first_path.read_text(encoding="utf-8").splitlines()
        lines[0] = "// marker removed"
        first_path.write_text("\n".join(lines) + "\n", encoding="utf-8", newline="\n")
    elif mutation == "wrong_marker":
        lines = first_path.read_text(encoding="utf-8").splitlines()
        lines[0] = lines[0].replace(first["address"][2:], "80000001")
        first_path.write_text("\n".join(lines) + "\n", encoding="utf-8", newline="\n")
    elif mutation == "index_disagreement":
        index_path = root / "research" / "decomp" / "ghidra-export" / "_index.tsv"
        lines = index_path.read_text(encoding="utf-8").splitlines()
        lines[1] = lines[1].replace(first["address"][2:], "80000001")
        index_path.write_text("\n".join(lines) + "\n", encoding="utf-8", newline="\n")
    elif mutation == "missing_anomaly":
        registry["summary"]["anomalies"].pop()
    elif mutation == "extra_anomaly":
        registry["summary"]["anomalies"].append("unexpected")
    elif mutation == "duplicate_name":
        registry["functions"][1]["name"] = first["name"]
    elif mutation == "duplicate_address":
        registry["functions"][1]["address"] = first["address"]
    with pytest.raises(OracleRegistryValidationError):
        validate_oracle_registry_v1(registry, root)


@pytest.mark.parametrize(
    "mutation",
    [
        "top_extra",
        "meta_extra",
        "function_extra",
        "path_escape",
        "path_backslash",
        "path_casefold_collision",
        "bool_as_integer",
    ],
)
def test_unknown_shapes_and_invalid_owner_paths_fail_closed(
    tmp_path: Path, mutation: str
) -> None:
    root, original = _synthetic_product(tmp_path)
    registry = copy.deepcopy(original)
    if mutation == "top_extra":
        registry["extension"] = {}
    elif mutation == "meta_extra":
        registry["meta"]["extension"] = "forbidden"
    elif mutation == "function_extra":
        registry["functions"][0]["extension"] = "forbidden"
    elif mutation == "path_escape":
        registry["functions"][0]["chunk_file"] = "../chunk.c"
    elif mutation == "path_backslash":
        registry["functions"][0]["chunk_file"] = (
            "research/decomp/ghidra-export\\chunk.c"
        )
    elif mutation == "path_casefold_collision":
        registry["functions"][0]["chunk_file"] = (
            "research/decomp/ghidra-export/chunk_COLLIDE.c"
        )
        registry["functions"][1]["chunk_file"] = (
            "research/decomp/ghidra-export/chunk_collide.c"
        )
    elif mutation == "bool_as_integer":
        registry["summary"]["functions_total"] = True
    with pytest.raises(OracleRegistryValidationError):
        validate_oracle_registry_v1(registry, root)


@pytest.mark.parametrize(
    "payload",
    [
        b'{"oracle_registry_schema":1,"oracle_registry_schema":1}\n',
        b'{"oracle_registry_schema":NaN}\n',
        b'{"oracle_registry_schema":Infinity}\n',
        b"\xff\xfe{}",
    ],
)
def test_loader_rejects_duplicate_keys_nonfinite_numbers_and_non_utf8(
    tmp_path: Path, payload: bytes
) -> None:
    root = tmp_path / "product"
    root.mkdir()
    registry_path = root / "oracle-registry.json"
    registry_path.write_bytes(payload)
    with pytest.raises(OracleRegistryValidationError):
        load_oracle_registry_v1(registry_path, root)


def test_loader_rejects_relative_root_and_registry_path(tmp_path: Path) -> None:
    root, registry = _synthetic_product(tmp_path)
    registry_path = root / "oracle-registry.json"
    registry_path.write_text(
        json.dumps(registry) + "\n", encoding="utf-8", newline="\n"
    )
    with pytest.raises(OracleRegistryValidationError, match="product_root must be absolute"):
        load_oracle_registry_v1(registry_path, Path("relative"))
    with pytest.raises(OracleRegistryValidationError, match="must be absolute"):
        load_oracle_registry_v1(Path("oracle-registry.json"), root)


def test_validator_rejects_hard_linked_owner_file(tmp_path: Path) -> None:
    root, registry = _synthetic_product(tmp_path)
    owner_path = root.joinpath(*registry["functions"][0]["chunk_file"].split("/"))
    owner_path.with_name("owner-hardlink.c").hardlink_to(owner_path)
    with pytest.raises(OracleRegistryValidationError, match="hard-linked"):
        validate_oracle_registry_v1(registry, root)


@pytest.mark.parametrize("target_kind", ["registry", "index", "owner"])
def test_stable_read_rejects_ancestor_directory_swap(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch, target_kind: str
) -> None:
    _root, _registry, container, target, where, invoke = _race_input(
        tmp_path, target_kind
    )
    parked = container.with_name(container.name + "-parked")
    incoming = container.with_name(container.name + "-incoming")
    incoming.mkdir()
    (incoming / target.name).write_bytes(target.read_bytes())

    def swap_ancestor() -> None:
        container.rename(parked)
        incoming.rename(container)

    state = _install_path_race(monkeypatch, where, swap_ancestor)
    with pytest.raises(OracleRegistryValidationError, match="changed during stable read"):
        invoke()
    assert state["fired"]


@pytest.mark.parametrize("target_kind", ["registry", "index", "owner"])
def test_stable_read_rejects_reparse_ancestor_race(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch, target_kind: str
) -> None:
    _root, _registry, container, target, where, invoke = _race_input(
        tmp_path, target_kind
    )
    parked = container.with_name(container.name + "-parked")
    reparse_target = container.with_name(container.name + "-reparse-target")
    reparse_target.mkdir()
    (reparse_target / target.name).write_bytes(target.read_bytes())

    def replace_with_reparse() -> None:
        container.rename(parked)
        _create_directory_reparse(container, reparse_target)

    state = _install_post_eof_path_race(monkeypatch, where, replace_with_reparse)
    try:
        with pytest.raises(OracleRegistryValidationError, match="reparse|changed"):
            invoke()
        assert state["fired"]
    finally:
        if container.exists() or container.is_symlink():
            _remove_directory_reparse(container)
        parked.rename(container)
