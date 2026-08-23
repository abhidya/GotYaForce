"""Strict schema-1 validation for the product oracle owner registry.

This module is the single product-side contract shared by the registry producer
and priority consumer.  It deliberately validates the complete document and
the marker/index/source relationship before returning owner data.
"""

from __future__ import annotations

import json
import os
import re
import stat
import unicodedata
from collections import Counter, defaultdict
from dataclasses import dataclass
from pathlib import Path, PurePosixPath
from typing import Any


ORACLE_REGISTRY_SCHEMA = 1

TOP_LEVEL_KEYS = {
    "oracle_registry_schema",
    "meta",
    "summary",
    "ranked_units",
    "functions",
    "excluded",
}
META_KEYS = {"generated_by", "inputs", "conventions"}
INPUT_KEYS = {"queue", "skipped", "chunk_index", "family_coverage"}
CONVENTION_KEYS = {
    "address",
    "structural_class",
    "citation_grade",
    "gap_alignment",
    "ranked_units_sort",
    "oracle_able_units",
}
SUMMARY_KEYS = {
    "functions_total",
    "units_total",
    "excluded_total",
    "excluded_reasons",
    "structural_class_counts",
    "citation_grade_counts",
    "class_by_citation_grade",
    "gap_aligned_functions",
    "gap_aligned_functions_partial_family",
    "fully_gap_aligned_units",
    "fully_gap_aligned_unit_names",
    "oracle_able_units",
    "oracle_able_unit_names",
    "anomalies",
}
RANKED_UNIT_KEYS = {
    "unit",
    "oracle_kind",
    "fn_count",
    "gap_partial_slots",
    "gap_family_ctors",
    "port_citations",
    "port_grade_fns",
    "total_citations",
    "max_structural_class",
    "total_loc",
    "fully_gap_aligned",
}
FUNCTION_KEYS = {
    "name",
    "address",
    "unit",
    "chunk_file",
    "line_range",
    "loc",
    "return_type",
    "params",
    "returns_value",
    "has_pointer_args",
    "external_callees",
    "global_refs",
    "structural_class",
    "ts_citations",
    "citation_grade",
    "citation_scan_skipped",
    "gap_alignment",
}
EXCLUDED_KEYS = {"name", "address", "chunk", "reason"}
ORACLE_BUCKETS = {
    "differential_vs_ts",
    "state_diff",
    "citations_no_family",
    "trace_only",
}

IDENTIFIER_RX = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
ADDRESS_RX = re.compile(r"^0x[0-9a-f]{8}$")
HEX_ADDRESS_RX = re.compile(r"^[0-9a-fA-F]{8}$")
ZZ_RX = re.compile(r"^zz_([0-9a-fA-F]{7})_$")
FUN_RX = re.compile(r"^FUN_([0-9a-fA-F]{8})$")
MARKER_RX = re.compile(r"^// ==== ([0-9a-fA-F]{8})\s+(.+?) ====\s*$")
CLASS_RANK = {"A": 0, "B": 1, "C": 2, "D": 3, "E": 4}
REPARSE_ATTRIBUTE = 0x400


class OracleRegistryValidationError(ValueError):
    """The registry is not the exact fail-closed schema-1 owner contract."""


@dataclass(frozen=True)
class _ValidatedPath:
    """Identity-bound path chain and containment observed before a file read."""

    path: Path
    root_identity: tuple[int, ...]
    components: tuple[tuple[str, tuple[int, ...]], ...]
    resolved_root: str
    resolved_file: str

    @property
    def final_identity(self) -> tuple[int, ...]:
        return self.components[-1][1]


def _fail(message: str) -> None:
    raise OracleRegistryValidationError(message)


def _exact_keys(value: Any, expected: set[str], where: str) -> dict[str, Any]:
    if type(value) is not dict:
        _fail(f"{where} must be an object")
    actual = set(value)
    if actual != expected:
        _fail(
            f"{where} keys mismatch: missing={sorted(expected - actual)!r} "
            f"extra={sorted(actual - expected)!r}"
        )
    return value


def _nonempty_string(value: Any, where: str) -> str:
    if type(value) is not str or not value:
        _fail(f"{where} must be a nonempty string")
    return value


def _nonnegative_int(value: Any, where: str) -> int:
    if type(value) is not int or value < 0:
        _fail(f"{where} must be a nonnegative integer")
    return value


def _positive_int(value: Any, where: str) -> int:
    if type(value) is not int or value <= 0:
        _fail(f"{where} must be a positive integer")
    return value


def _exact_bool(value: Any, where: str) -> bool:
    if type(value) is not bool:
        _fail(f"{where} must be a boolean")
    return value


def _string_list(value: Any, where: str) -> list[str]:
    if type(value) is not list:
        _fail(f"{where} must be a list")
    for index, item in enumerate(value):
        if type(item) is not str:
            _fail(f"{where}[{index}] must be a string")
    return value


def _unique_strings(value: Any, where: str, *, sorted_required: bool) -> list[str]:
    items = _string_list(value, where)
    if len(items) != len(set(items)):
        _fail(f"{where} must contain unique strings")
    if sorted_required and items != sorted(items):
        _fail(f"{where} must be sorted")
    return items


def _string_count_map(value: Any, where: str) -> dict[str, int]:
    if type(value) is not dict:
        _fail(f"{where} must be an object")
    for key, count in value.items():
        if type(key) is not str:
            _fail(f"{where} keys must be strings")
        _nonnegative_int(count, f"{where}.{key}")
    return value


def _relative_posix_path(
    value: Any,
    where: str,
    *,
    prefix: str | None = None,
    suffix: str | None = None,
) -> str:
    path = _nonempty_string(value, where)
    if unicodedata.normalize("NFC", path) != path:
        _fail(f"{where} must be NFC-normalized")
    if "\\" in path or ":" in path or path.startswith("//"):
        _fail(f"{where} must be a POSIX product-relative path")
    if any(ord(char) < 32 or ord(char) == 127 for char in path):
        _fail(f"{where} contains a control character")
    pure = PurePosixPath(path)
    if pure.is_absolute() or not pure.parts:
        _fail(f"{where} must be relative")
    if any(part in {"", ".", ".."} for part in path.split("/")):
        _fail(f"{where} contains an empty, dot, or dot-dot segment")
    if re.match(r"^[A-Za-z]:", path):
        _fail(f"{where} contains drive syntax")
    if prefix is not None and not path.startswith(prefix):
        _fail(f"{where} must start with {prefix!r}")
    if suffix is not None and not path.endswith(suffix):
        _fail(f"{where} must end with {suffix!r}")
    return path


def _is_reparse(st: os.stat_result) -> bool:
    attributes = int(getattr(st, "st_file_attributes", 0))
    tag = int(getattr(st, "st_reparse_tag", 0))
    return bool(attributes & REPARSE_ATTRIBUTE) or tag != 0


def _identity(st: os.stat_result) -> tuple[int, ...]:
    return (
        int(st.st_dev),
        int(st.st_ino),
        int(st.st_mode),
        int(st.st_nlink),
        int(st.st_size),
        int(st.st_mtime_ns),
        int(getattr(st, "st_file_attributes", 0)),
        int(getattr(st, "st_reparse_tag", 0)),
    )


def _inspect_product_root(product_root: Path) -> tuple[Path, os.stat_result]:
    root = Path(product_root)
    if not root.is_absolute():
        _fail("product_root must be absolute")
    try:
        root_st = os.lstat(root)
    except OSError as exc:
        _fail(f"product_root cannot be inspected: {exc}")
    if not stat.S_ISDIR(root_st.st_mode):
        _fail("product_root must be an ordinary directory")
    if stat.S_ISLNK(root_st.st_mode) or _is_reparse(root_st) or os.path.ismount(root):
        _fail("product_root must not be a symlink, reparse point, or mount")
    return root, root_st


def _validate_product_root(product_root: Path) -> Path:
    return _inspect_product_root(product_root)[0]


def _exact_file_path(product_root: Path, path: Path, where: str) -> _ValidatedPath:
    root, root_st = _inspect_product_root(product_root)
    root_identity = _identity(root_st)
    candidate = Path(path)
    if not candidate.is_absolute():
        _fail(f"{where} must be absolute")
    try:
        relative = candidate.relative_to(root)
    except ValueError:
        _fail(f"{where} escapes product_root")
    if not relative.parts:
        _fail(f"{where} must name a file")

    current = root
    component_bindings: list[tuple[str, tuple[int, ...]]] = []
    for index, part in enumerate(relative.parts):
        try:
            names = {entry.name for entry in os.scandir(current)}
        except OSError as exc:
            _fail(f"{where} component cannot be enumerated: {exc}")
        if part not in names:
            _fail(f"{where} has incorrect on-disk spelling at {part!r}")
        current = current / part
        try:
            component_st = os.lstat(current)
        except OSError as exc:
            _fail(f"{where} component cannot be inspected: {exc}")
        component_bindings.append((part, _identity(component_st)))
        if stat.S_ISLNK(component_st.st_mode) or _is_reparse(component_st):
            _fail(f"{where} contains a symlink or reparse point")
        final = index == len(relative.parts) - 1
        if final:
            if not stat.S_ISREG(component_st.st_mode):
                _fail(f"{where} must be an ordinary file")
            if component_st.st_nlink != 1:
                _fail(f"{where} must not be hard-linked")
        elif not stat.S_ISDIR(component_st.st_mode) or os.path.ismount(current):
            _fail(f"{where} contains a non-ordinary directory component")

    try:
        resolved_root = root.resolve(strict=True)
        resolved_file = current.resolve(strict=True)
        resolved_file.relative_to(resolved_root)
    except (OSError, ValueError):
        _fail(f"{where} does not resolve under product_root")
    root_folded = os.path.normcase(str(resolved_root)).casefold()
    file_folded = os.path.normcase(str(resolved_file)).casefold()
    prefix = root_folded.rstrip("\\/") + os.sep.casefold()
    if not file_folded.startswith(prefix):
        _fail(f"{where} fails case-folded containment")
    return _ValidatedPath(
        path=current,
        root_identity=root_identity,
        components=tuple(component_bindings),
        resolved_root=root_folded,
        resolved_file=file_folded,
    )


def _validate_open_file(st: os.stat_result, where: str) -> None:
    if not stat.S_ISREG(st.st_mode):
        _fail(f"{where} opened handle must be an ordinary file")
    if st.st_nlink != 1:
        _fail(f"{where} opened handle must not be hard-linked")
    if _is_reparse(st):
        _fail(f"{where} opened handle must not be a reparse point")


def _stable_read_file(product_root: Path, path: Path, where: str) -> bytes:
    before_binding = _exact_file_path(product_root, path, where)
    flags = os.O_RDONLY | getattr(os, "O_BINARY", 0) | getattr(os, "O_NOINHERIT", 0)
    flags |= getattr(os, "O_NOFOLLOW", 0)
    try:
        descriptor = os.open(before_binding.path, flags)
        with os.fdopen(descriptor, "rb") as handle:
            handle_before = os.fstat(handle.fileno())
            _validate_open_file(handle_before, where)
            payload = handle.read()
            handle_after = os.fstat(handle.fileno())
    except OSError as exc:
        _fail(f"{where} stable read failed: {exc}")
    after_binding = _exact_file_path(product_root, path, where)
    handle_before_identity = _identity(handle_before)
    handle_after_identity = _identity(handle_after)
    if (
        handle_before_identity != before_binding.final_identity
        or handle_after_identity != before_binding.final_identity
        or after_binding != before_binding
        or after_binding.final_identity != handle_after_identity
        or len(payload) != handle_before.st_size
    ):
        _fail(f"{where} changed during stable read")
    return payload


def _decode_utf8(payload: bytes, where: str) -> str:
    try:
        return payload.decode("utf-8", errors="strict")
    except UnicodeDecodeError as exc:
        _fail(f"{where} is not UTF-8: {exc}")


def _reject_constant(value: str) -> None:
    _fail(f"JSON constant {value!r} is forbidden")


def _reject_duplicate_keys(pairs: list[tuple[str, Any]]) -> dict[str, Any]:
    result: dict[str, Any] = {}
    for key, value in pairs:
        if key in result:
            _fail(f"duplicate JSON object key {key!r}")
        result[key] = value
    return result


def parse_oracle_registry_bytes(payload: bytes) -> dict[str, Any]:
    """Decode strict UTF-8 JSON while rejecting duplicates and non-finite values."""

    text = _decode_utf8(payload, "oracle registry")
    try:
        value = json.loads(
            text,
            object_pairs_hook=_reject_duplicate_keys,
            parse_constant=_reject_constant,
        )
    except OracleRegistryValidationError:
        raise
    except (json.JSONDecodeError, TypeError, ValueError) as exc:
        _fail(f"oracle registry is not strict JSON: {exc}")
    if type(value) is not dict:
        _fail("oracle registry top level must be an object")
    return value


def _encoded_address(name: str) -> int | None:
    match = ZZ_RX.fullmatch(name)
    if match:
        return 0x80000000 + int(match.group(1), 16)
    match = FUN_RX.fullmatch(name)
    if match:
        return int(match.group(1), 16)
    return None


def _marker_anomaly(name: str, encoded: int, marker: int) -> str:
    return f"{name}: name addr {encoded:08x} != marker {marker:08x} (marker wins)"


def _validate_parameter(parameter: Any, where: str) -> str:
    text = _nonempty_string(parameter, where)
    paren_depth = 0
    bracket_depth = 0
    for char in text:
        if char == "(":
            paren_depth += 1
        elif char == ")":
            paren_depth -= 1
        elif char == "[":
            bracket_depth += 1
        elif char == "]":
            bracket_depth -= 1
        elif char == "," and paren_depth == 0 and bracket_depth == 0:
            _fail(f"{where} contains a top-level comma")
        if paren_depth < 0 or bracket_depth < 0:
            _fail(f"{where} has unbalanced delimiters")
    if paren_depth or bracket_depth:
        _fail(f"{where} has unbalanced delimiters")
    return text


def _validate_function(record: Any, index: int) -> dict[str, Any]:
    where = f"functions[{index}]"
    function = _exact_keys(record, FUNCTION_KEYS, where)
    name = _nonempty_string(function["name"], f"{where}.name")
    if not IDENTIFIER_RX.fullmatch(name):
        _fail(f"{where}.name must be a C identifier")
    address = _nonempty_string(function["address"], f"{where}.address")
    if not ADDRESS_RX.fullmatch(address):
        _fail(f"{where}.address must be lowercase 0x plus eight hex digits")
    _nonempty_string(function["unit"], f"{where}.unit")
    _relative_posix_path(
        function["chunk_file"],
        f"{where}.chunk_file",
        prefix="research/decomp/ghidra-export/",
        suffix=".c",
    )

    line_range = function["line_range"]
    if type(line_range) is not list or len(line_range) != 2:
        _fail(f"{where}.line_range must have exactly two integers")
    start = _positive_int(line_range[0], f"{where}.line_range[0]")
    end = _positive_int(line_range[1], f"{where}.line_range[1]")
    if start > end:
        _fail(f"{where}.line_range must be ordered")
    loc = _positive_int(function["loc"], f"{where}.loc")
    if loc != end - start + 1:
        _fail(f"{where}.loc disagrees with line_range")

    return_type = _nonempty_string(function["return_type"], f"{where}.return_type")
    params = function["params"]
    if type(params) is not list:
        _fail(f"{where}.params must be a list")
    for param_index, parameter in enumerate(params):
        _validate_parameter(parameter, f"{where}.params[{param_index}]")
    if "void" in params and params != ["void"]:
        _fail(f"{where}.params may use void only as the sole parameter")

    returns_value = _exact_bool(function["returns_value"], f"{where}.returns_value")
    if returns_value != (" ".join(return_type.split()) != "void"):
        _fail(f"{where}.returns_value disagrees with return_type")
    has_pointer_args = _exact_bool(
        function["has_pointer_args"], f"{where}.has_pointer_args"
    )
    if has_pointer_args != any("*" in parameter for parameter in params):
        _fail(f"{where}.has_pointer_args disagrees with params")

    callees = _exact_keys(
        function["external_callees"], {"count", "list"}, f"{where}.external_callees"
    )
    callee_list = _unique_strings(
        callees["list"], f"{where}.external_callees.list", sorted_required=True
    )
    if _nonnegative_int(callees["count"], f"{where}.external_callees.count") != len(
        callee_list
    ):
        _fail(f"{where}.external_callees count mismatch")

    global_refs = function["global_refs"]
    if type(global_refs) is not list:
        _fail(f"{where}.global_refs must be a list")
    global_identities: set[tuple[str, str, bool]] = set()
    for ref_index, ref_value in enumerate(global_refs):
        ref_where = f"{where}.global_refs[{ref_index}]"
        ref = _exact_keys(ref_value, {"symbol", "prefix_type", "width_known"}, ref_where)
        identity = (
            _nonempty_string(ref["symbol"], f"{ref_where}.symbol"),
            _nonempty_string(ref["prefix_type"], f"{ref_where}.prefix_type"),
            _exact_bool(ref["width_known"], f"{ref_where}.width_known"),
        )
        if identity in global_identities:
            _fail(f"{where}.global_refs must be unique")
        global_identities.add(identity)

    structural_class = _nonempty_string(
        function["structural_class"], f"{where}.structural_class"
    )
    if structural_class not in CLASS_RANK:
        _fail(f"{where}.structural_class is invalid")
    callee_count = len(callee_list)
    if callee_count == 0:
        expected_class = (
            "C"
            if not returns_value
            else "A"
            if not global_refs and not has_pointer_args
            else "B"
        )
    else:
        expected_class = "D" if callee_count <= 2 else "E"
    if structural_class != expected_class:
        _fail(f"{where}.structural_class disagrees with record contents")

    citations = function["ts_citations"]
    if type(citations) is not list:
        _fail(f"{where}.ts_citations must be a list")
    citation_identities: set[tuple[str, str]] = set()
    for citation_index, citation_value in enumerate(citations):
        citation_where = f"{where}.ts_citations[{citation_index}]"
        citation = _exact_keys(citation_value, {"where", "grade"}, citation_where)
        location = _nonempty_string(citation["where"], f"{citation_where}.where")
        try:
            citation_path, line_text = location.rsplit(":", 1)
        except ValueError:
            _fail(f"{citation_where}.where must end with :<positive-line>")
        _relative_posix_path(citation_path, f"{citation_where}.where path")
        if not line_text.isascii() or not line_text.isdigit() or int(line_text) <= 0:
            _fail(f"{citation_where}.where line must be positive")
        grade = citation["grade"]
        if grade not in {"port", "unported", "weak"}:
            _fail(f"{citation_where}.grade is invalid")
        identity = (location, grade)
        if identity in citation_identities:
            _fail(f"{where}.ts_citations must be unique")
        citation_identities.add(identity)

    citation_grade = function["citation_grade"]
    if citation_grade not in {"port", "unported", "weak", "none", None}:
        _fail(f"{where}.citation_grade is invalid")
    scan_skipped = function["citation_scan_skipped"]
    if scan_skipped not in {"ambiguous_name", None}:
        _fail(f"{where}.citation_scan_skipped is invalid")
    if (citation_grade is None) != (scan_skipped == "ambiguous_name"):
        _fail(f"{where} citation grade/scan-skipped fields disagree")
    citation_grades = [citation["grade"] for citation in citations]
    if scan_skipped == "ambiguous_name":
        expected_citation_grade = None
    elif "port" in citation_grades:
        expected_citation_grade = "port"
    elif "unported" in citation_grades:
        expected_citation_grade = "unported"
    elif citation_grades:
        expected_citation_grade = "weak"
    else:
        expected_citation_grade = "none"
    if citation_grade != expected_citation_grade:
        _fail(f"{where}.citation_grade disagrees with ts_citations")

    gap = function["gap_alignment"]
    if gap is not None:
        gap = _exact_keys(gap, {"family_ctor", "partial_slots", "members"}, f"{where}.gap_alignment")
        ctor = _nonempty_string(gap["family_ctor"], f"{where}.gap_alignment.family_ctor")
        if not ADDRESS_RX.fullmatch(ctor):
            _fail(f"{where}.gap_alignment.family_ctor is invalid")
        _nonnegative_int(gap["partial_slots"], f"{where}.gap_alignment.partial_slots")
        _unique_strings(
            gap["members"], f"{where}.gap_alignment.members", sorted_required=False
        )
    return function


def _validate_excluded(record: Any, index: int) -> dict[str, Any]:
    where = f"excluded[{index}]"
    excluded = _exact_keys(record, EXCLUDED_KEYS, where)
    for key in sorted(EXCLUDED_KEYS):
        _nonempty_string(excluded[key], f"{where}.{key}")
    return excluded


def _validate_ranked_unit(record: Any, index: int) -> dict[str, Any]:
    where = f"ranked_units[{index}]"
    ranked = _exact_keys(record, RANKED_UNIT_KEYS, where)
    _nonempty_string(ranked["unit"], f"{where}.unit")
    _nonempty_string(ranked["oracle_kind"], f"{where}.oracle_kind")
    for key in (
        "fn_count",
        "gap_partial_slots",
        "port_citations",
        "port_grade_fns",
        "total_citations",
        "total_loc",
    ):
        _nonnegative_int(ranked[key], f"{where}.{key}")
    _unique_strings(
        ranked["gap_family_ctors"], f"{where}.gap_family_ctors", sorted_required=True
    )
    max_class = _nonempty_string(
        ranked["max_structural_class"], f"{where}.max_structural_class"
    )
    if max_class not in CLASS_RANK:
        _fail(f"{where}.max_structural_class is invalid")
    _exact_bool(ranked["fully_gap_aligned"], f"{where}.fully_gap_aligned")
    return ranked


def _validate_meta(value: Any) -> dict[str, Any]:
    meta = _exact_keys(value, META_KEYS, "meta")
    _nonempty_string(meta["generated_by"], "meta.generated_by")
    inputs = _exact_keys(meta["inputs"], INPUT_KEYS, "meta.inputs")
    for key in sorted(INPUT_KEYS):
        _relative_posix_path(inputs[key], f"meta.inputs.{key}")
    conventions = _exact_keys(meta["conventions"], CONVENTION_KEYS, "meta.conventions")
    for key in sorted(CONVENTION_KEYS):
        if type(conventions[key]) is not str:
            _fail(f"meta.conventions.{key} must be a string")
    return meta


def _read_index(product_root: Path, relative_path: str) -> dict[int, tuple[str, str]]:
    path = product_root.joinpath(*PurePosixPath(relative_path).parts)
    payload = _stable_read_file(product_root, path, "chunk index")
    text = _decode_utf8(payload, "chunk index")
    lines = text.splitlines()
    if not lines or lines[0] != "address\tname\tchunk_file":
        _fail("chunk index header is invalid")
    by_address: dict[int, tuple[str, str]] = {}
    seen_names: set[str] = set()
    for line_number, line in enumerate(lines[1:], 2):
        parts = line.split("\t")
        if len(parts) != 3:
            _fail(f"chunk index line {line_number} must have three fields")
        address_text, name, chunk = parts
        if not HEX_ADDRESS_RX.fullmatch(address_text):
            _fail(f"chunk index line {line_number} address is invalid")
        if not name or any(ord(char) < 32 or ord(char) == 127 for char in name):
            _fail(f"chunk index line {line_number} name is invalid")
        if not chunk or "/" in chunk or "\\" in chunk or not chunk.endswith(".c"):
            _fail(f"chunk index line {line_number} chunk is invalid")
        address = int(address_text, 16)
        if name in seen_names:
            _fail(f"chunk index duplicates name {name!r}")
        if address in by_address:
            _fail(f"chunk index duplicates address {address_text!r}")
        by_address[address] = (name, chunk)
        seen_names.add(name)
    return by_address


def _validate_owner_evidence(
    registry: dict[str, Any], product_root: Path, meta: dict[str, Any]
) -> None:
    index = _read_index(product_root, meta["inputs"]["chunk_index"])
    chunk_spellings: dict[str, str] = {}
    chunk_payloads: dict[str, list[str]] = {}
    expected_anomalies: list[str] = []

    for function in registry["functions"]:
        chunk_file = function["chunk_file"]
        folded = chunk_file.casefold()
        prior = chunk_spellings.setdefault(folded, chunk_file)
        if prior != chunk_file:
            _fail(f"chunk_file case-fold collision: {prior!r} and {chunk_file!r}")

    for record_index, function in enumerate(registry["functions"]):
        where = f"functions[{record_index}]"
        chunk_file = function["chunk_file"]
        if chunk_file not in chunk_payloads:
            chunk_path = product_root.joinpath(*PurePosixPath(chunk_file).parts)
            payload = _stable_read_file(product_root, chunk_path, f"owner file {chunk_file}")
            chunk_payloads[chunk_file] = _decode_utf8(
                payload, f"owner file {chunk_file}"
            ).splitlines()
        lines = chunk_payloads[chunk_file]
        start, end = function["line_range"]
        if end > len(lines):
            _fail(f"{where}.line_range exceeds owner file")
        marker_match = MARKER_RX.fullmatch(lines[start - 1])
        if marker_match is None:
            _fail(f"{where} has no exact marker at line_range start")
        marker_address = int(marker_match.group(1), 16)
        marker_name = marker_match.group(2)
        if marker_name != function["name"]:
            _fail(f"{where} marker name disagrees with record")
        emitted_address = int(function["address"][2:], 16)
        if marker_address != emitted_address:
            _fail(f"{where} marker address disagrees with emitted address")
        index_entry = index.get(marker_address)
        if index_entry is None:
            _fail(f"{where} has no chunk-index owner")
        if index_entry[1] != PurePosixPath(chunk_file).name:
            _fail(f"{where} marker/index/chunk evidence disagrees")
        encoded = _encoded_address(function["name"])
        if encoded is not None and index_entry[0] != function["name"]:
            _fail(f"{where} encoded owner label disagrees with chunk index")
        if encoded is not None and encoded != marker_address:
            expected_anomalies.append(
                _marker_anomaly(function["name"], encoded, marker_address)
            )

    if registry["summary"]["anomalies"] != expected_anomalies:
        _fail("summary.anomalies does not exactly match marker-wins evidence")


def _validate_summary_and_aggregates(registry: dict[str, Any]) -> None:
    summary = _exact_keys(registry["summary"], SUMMARY_KEYS, "summary")
    integer_fields = (
        "functions_total",
        "units_total",
        "excluded_total",
        "gap_aligned_functions",
        "gap_aligned_functions_partial_family",
        "fully_gap_aligned_units",
    )
    for field in integer_fields:
        _nonnegative_int(summary[field], f"summary.{field}")
    for field in (
        "excluded_reasons",
        "structural_class_counts",
        "citation_grade_counts",
    ):
        _string_count_map(summary[field], f"summary.{field}")
    class_matrix = summary["class_by_citation_grade"]
    if type(class_matrix) is not dict:
        _fail("summary.class_by_citation_grade must be an object")
    for class_name, grade_counts in class_matrix.items():
        if type(class_name) is not str:
            _fail("summary.class_by_citation_grade keys must be strings")
        _string_count_map(grade_counts, f"summary.class_by_citation_grade.{class_name}")
    _unique_strings(
        summary["fully_gap_aligned_unit_names"],
        "summary.fully_gap_aligned_unit_names",
        sorted_required=True,
    )
    _string_list(summary["anomalies"], "summary.anomalies")
    oracle_counts = _exact_keys(
        summary["oracle_able_units"], ORACLE_BUCKETS, "summary.oracle_able_units"
    )
    oracle_names = _exact_keys(
        summary["oracle_able_unit_names"],
        ORACLE_BUCKETS,
        "summary.oracle_able_unit_names",
    )
    for bucket in sorted(ORACLE_BUCKETS):
        _nonnegative_int(oracle_counts[bucket], f"summary.oracle_able_units.{bucket}")
        _unique_strings(
            oracle_names[bucket],
            f"summary.oracle_able_unit_names.{bucket}",
            sorted_required=True,
        )
        if oracle_counts[bucket] != len(oracle_names[bucket]):
            _fail(f"summary oracle bucket {bucket!r} count mismatch")

    functions = registry["functions"]
    excluded = registry["excluded"]
    per_unit: dict[str, list[dict[str, Any]]] = defaultdict(list)
    for function in functions:
        per_unit[function["unit"]].append(function)
    if summary["functions_total"] != len(functions):
        _fail("summary.functions_total mismatch")
    if summary["units_total"] != len(per_unit):
        _fail("summary.units_total mismatch")
    if summary["excluded_total"] != len(excluded):
        _fail("summary.excluded_total mismatch")
    if summary["excluded_reasons"] != dict(Counter(item["reason"] for item in excluded)):
        _fail("summary.excluded_reasons mismatch")
    if summary["structural_class_counts"] != dict(
        Counter(item["structural_class"] for item in functions)
    ):
        _fail("summary.structural_class_counts mismatch")
    citation_counts = Counter(
        item["citation_grade"] or "ambiguous_name" for item in functions
    )
    if summary["citation_grade_counts"] != dict(citation_counts):
        _fail("summary.citation_grade_counts mismatch")
    matrix: dict[str, Counter[str]] = defaultdict(Counter)
    for function in functions:
        matrix[function["structural_class"]][
            function["citation_grade"] or "ambiguous_name"
        ] += 1
    expected_matrix = {
        class_name: dict(sorted(counts.items()))
        for class_name, counts in sorted(matrix.items())
    }
    if summary["class_by_citation_grade"] != expected_matrix:
        _fail("summary.class_by_citation_grade mismatch")
    if summary["gap_aligned_functions"] != sum(
        item["gap_alignment"] is not None for item in functions
    ):
        _fail("summary.gap_aligned_functions mismatch")
    if summary["gap_aligned_functions_partial_family"] != sum(
        item["gap_alignment"] is not None
        and item["gap_alignment"]["partial_slots"] > 0
        for item in functions
    ):
        _fail("summary.gap_aligned_functions_partial_family mismatch")
    fully_aligned = sorted(
        unit
        for unit, records in per_unit.items()
        if records and all(record["gap_alignment"] is not None for record in records)
    )
    if summary["fully_gap_aligned_unit_names"] != fully_aligned:
        _fail("summary.fully_gap_aligned_unit_names mismatch")
    if summary["fully_gap_aligned_units"] != len(fully_aligned):
        _fail("summary.fully_gap_aligned_units mismatch")

    expected_buckets = {bucket: [] for bucket in ORACLE_BUCKETS}
    for unit, records in per_unit.items():
        port_grade_fns = sum(record["citation_grade"] == "port" for record in records)
        citations = sum(len(record["ts_citations"]) for record in records)
        has_gap = any(record["gap_alignment"] is not None for record in records)
        if port_grade_fns:
            bucket = "differential_vs_ts"
        elif citations and has_gap:
            bucket = "state_diff"
        elif citations:
            bucket = "citations_no_family"
        else:
            bucket = "trace_only"
        expected_buckets[bucket].append(unit)
    expected_buckets = {
        bucket: sorted(names) for bucket, names in expected_buckets.items()
    }
    if summary["oracle_able_unit_names"] != expected_buckets:
        _fail("summary.oracle_able_unit_names mismatch")
    if summary["oracle_able_units"] != {
        bucket: len(names) for bucket, names in expected_buckets.items()
    }:
        _fail("summary.oracle_able_units mismatch")

    seen_ranked_units: set[str] = set()
    ranked_units = registry["ranked_units"]
    for index, ranked in enumerate(ranked_units):
        unit = ranked["unit"]
        if unit in seen_ranked_units:
            _fail("ranked_units contains a duplicate unit")
        seen_ranked_units.add(unit)
        records = per_unit.get(unit)
        if not records:
            _fail(f"ranked_units[{index}] names an unknown unit")
        expected = {
            "fn_count": len(records),
            "gap_partial_slots": max(
                (
                    record["gap_alignment"]["partial_slots"]
                    for record in records
                    if record["gap_alignment"] is not None
                ),
                default=0,
            ),
            "gap_family_ctors": sorted(
                {
                    record["gap_alignment"]["family_ctor"]
                    for record in records
                    if record["gap_alignment"] is not None
                }
            ),
            "port_citations": sum(
                citation["grade"] == "port"
                for record in records
                for citation in record["ts_citations"]
            ),
            "port_grade_fns": sum(
                record["citation_grade"] == "port" for record in records
            ),
            "total_citations": sum(len(record["ts_citations"]) for record in records),
            "max_structural_class": max(
                (record["structural_class"] for record in records), key=CLASS_RANK.get
            ),
            "total_loc": sum(record["loc"] for record in records),
            "fully_gap_aligned": all(
                record["gap_alignment"] is not None for record in records
            ),
        }
        for field, expected_value in expected.items():
            if ranked[field] != expected_value:
                _fail(f"ranked_units[{index}].{field} mismatch")
    expected_order = sorted(
        ranked_units,
        key=lambda ranked: (
            -ranked["gap_partial_slots"],
            -ranked["port_citations"],
            CLASS_RANK[ranked["max_structural_class"]],
            ranked["total_loc"],
            ranked["unit"],
        ),
    )
    if ranked_units != expected_order:
        _fail("ranked_units is not in deterministic priority order")
    expected_ranked_units = sorted(
        per_unit,
        key=lambda unit: (
            -max(
                (
                    record["gap_alignment"]["partial_slots"]
                    for record in per_unit[unit]
                    if record["gap_alignment"] is not None
                ),
                default=0,
            ),
            -sum(
                citation["grade"] == "port"
                for record in per_unit[unit]
                for citation in record["ts_citations"]
            ),
            max(CLASS_RANK[record["structural_class"]] for record in per_unit[unit]),
            sum(record["loc"] for record in per_unit[unit]),
            unit,
        ),
    )[:50]
    if [ranked["unit"] for ranked in ranked_units] != expected_ranked_units:
        _fail("ranked_units does not contain the deterministic top units")


def validate_oracle_registry_v1(
    registry: Any, product_root: Path
) -> dict[str, Any]:
    """Validate the complete in-memory schema-1 registry and owner evidence."""

    root = _validate_product_root(Path(product_root))
    document = _exact_keys(registry, TOP_LEVEL_KEYS, "oracle registry")
    schema = document["oracle_registry_schema"]
    if type(schema) is not int or schema != ORACLE_REGISTRY_SCHEMA:
        _fail("oracle_registry_schema must be integer 1")
    meta = _validate_meta(document["meta"])
    if type(document["ranked_units"]) is not list:
        _fail("ranked_units must be a list")
    if type(document["functions"]) is not list:
        _fail("functions must be a list")
    if type(document["excluded"]) is not list:
        _fail("excluded must be a list")
    for index, ranked in enumerate(document["ranked_units"]):
        _validate_ranked_unit(ranked, index)
    for index, function in enumerate(document["functions"]):
        _validate_function(function, index)
    for index, excluded in enumerate(document["excluded"]):
        _validate_excluded(excluded, index)

    names = [function["name"] for function in document["functions"]]
    addresses = [function["address"] for function in document["functions"]]
    if len(names) != len(set(names)):
        _fail("function names must be globally unique")
    if len(addresses) != len(set(addresses)):
        _fail("authoritative function addresses must be globally unique")
    expected_order = sorted(
        document["functions"], key=lambda function: (function["address"], function["name"])
    )
    if document["functions"] != expected_order:
        _fail("functions must be sorted by authoritative address then name")

    _validate_summary_and_aggregates(document)
    _validate_owner_evidence(document, root, meta)
    return document


def load_oracle_registry_v1(
    registry_path: Path, product_root: Path
) -> dict[str, Any]:
    """Stable-read, parse, and validate an exact schema-1 registry file."""

    root = _validate_product_root(Path(product_root))
    payload = _stable_read_file(root, Path(registry_path), "oracle registry")
    return validate_oracle_registry_v1(parse_oracle_registry_bytes(payload), root)
