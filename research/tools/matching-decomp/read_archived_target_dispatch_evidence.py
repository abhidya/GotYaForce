#!/usr/bin/env python3
"""Fixed target dispatch evidence: 8006b7f4/92, entry-zero cell, 8006b850/528.

Read-only stdlib. Unchanged authentication precedes exactly two separately
frozen code spans and one four-byte pointer cell. No arbitrary-address CLI,
raw output, runtime-dependent pointer following or original execution. The
second code extent is C/index-bounded, NOT independently map-size-proven.
"""
import argparse
import hashlib
import json
from pathlib import Path
import sys

import read_archived_constants as c
import read_archived_command_evidence as command
import read_archived_actor_normal_evidence as normal
import read_archived_target_selector_evidence as selector

TEXT_MAPPING = normal.TEXT_MAPPING
DATA3_MAPPING = normal.DATA3_MAPPING
RANGES = (
    (0x8006b7f4, 92, '227945853f20b8b08ef9f71c6dde02a0ea8136652eb1e4e5d034fdab962d5b12'),
    (0x8006b850, 528, '8a01e4c3f1a21269d2b9fb98b2d6c71ab2d46859d9670049069db7c6eafabb51'),
)
CELL = (0x802d39a0, 4, 0x8006b850, 'a1f65fe8b7d29bda8e482aabf099797030ea8959dbd1559665487fb793a5b9ad')
FLOW = {
    0x8006b7f4: (
        (0x8006b808, 'bc', '8006b820', 4, 2),
        (0x8006b81c, 'b', '8006b840', None, None),
        (0x8006b83c, 'bctrl', None, 20, 0),
        (0x8006b84c, 'blr', None, 20, 0),
    ),
    0x8006b850: (
        (0x8006b874, 'bc', '8006ba44', 4, 2),
        (0x8006b894, 'bc', '8006b918', 4, 1),
        (0x8006b8a0, 'bc', '8006b910', 12, 2),
        (0x8006b8ac, 'bc', '8006b910', 12, 2),
        (0x8006b8b8, 'bc', '8006b910', 12, 2),
        (0x8006b8c0, 'bc', '8006b910', 12, 2),
        (0x8006b8d8, 'bc', '8006b910', 12, 2),
        (0x8006b8e0, 'bc', '8006b910', 12, 2),
        (0x8006b8f0, 'bc', '8006b910', 4, 0),
        (0x8006b914, 'bc', '8006b898', 16, 0),
        (0x8006b920, 'bc', '8006ba44', 12, 2),
        (0x8006b968, 'bl', '8020bc88', None, None),
        (0x8006b980, 'b', '8006b9ac', None, None),
        (0x8006b990, 'bl', '8020bc88', None, None),
        (0x8006b998, 'bc', '8006b9a4', 12, 1),
        (0x8006b9b4, 'bc', '8006b984', 12, 0),
        (0x8006b9c0, 'bc', '8006ba18', 12, 2),
        (0x8006b9d0, 'bc', '8006ba18', 4, 2),
        (0x8006b9e4, 'bc', '8006ba18', 4, 1),
        (0x8006b9f4, 'bc', '8006ba10', 4, 2),
        (0x8006ba04, 'bc', '8006ba10', 12, 2),
        (0x8006ba0c, 'b', '8006ba18', None, None),
        (0x8006ba14, 'bc', '8006b9e8', 16, 0),
        (0x8006ba5c, 'blr', None, 20, 0),
    ),
}
FLOW_NAMES = ('bc', 'b', 'bl', 'blr', 'bclr', 'bctr', 'bctrl')


def expected_flow(entry):
    rows = []
    for pc, name, target, bo, bi in FLOW[entry]:
        row = dict(address=f'{pc:08x}', mnemonic=name)
        if target is not None: row.update(target=target, AA=0, LK=int(name == 'bl'))
        if bo is not None: row.update(BO=bo, BI=bi, LK=int(name == 'bctrl'))
        if name in ('blr', 'bctrl'): row['BH'] = 0
        rows.append(row)
    return rows


def decode_selected(word, pc):
    """Reuse unchanged decoders, allowing only forms in these two fixed spans."""
    c.require(type(word) is int and 0 <= word <= 0xffffffff, 'word bounds')
    c.require(type(pc) is int and 0 <= pc <= 0xfffffffc and pc % 4 == 0, 'PC bounds')
    if word == 0x4e800421: return normal.decode_selected(word, pc)
    decoded = selector.decode_selected(word, pc)
    allowed = {'stwu','mflr','stw','lbz','extsb','bc','addi','stb','b','addis','rlwinm',
               'lwzx','mtctr','lwz','mtlr','blr','stfd','psq_st','stmw','or','lhz',
               'cmpi','cmpli','cmpl','cmp','stwx','mulli','add','lfs','stfs','bl',
               'fmr','fcmpo','psq_l','lfd','lmw'}
    return decoded if decoded and decoded['mnemonic'] in allowed else None


def range_evidence(db, mapping, address, width):
    c.require(all(type(value) is int for value in (address, width)), 'range integer fields')
    selected = [item for item in RANGES if item[:2] == (address, width)]
    c.require(len(selected) == 1, 'range not allowlisted')
    normal.require_mapping(mapping, TEXT_MAPPING)
    start, end, _, _, _, length, root = mapping
    c.require(address % 4 == width % 4 == 0 and start <= address < address+width <= end,
              'range alignment/bounds')
    raw, spans = db.chain(root, address-start, width, length)
    c.require(len(raw) == width, 'range byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == selected[0][2], 'range digest mismatch')
    instructions = []
    for offset in range(0, width, 4):
        pc = address+offset
        decoded = decode_selected(c.integer(raw, offset, 'I'), pc)
        c.require(decoded is not None, f'unselected instruction at {pc:08x}')
        instructions.append(dict(address=f'{pc:08x}', **decoded))
    c.require([row for row in instructions if row['mnemonic'] in FLOW_NAMES] == expected_flow(address),
              'complete control-flow mismatch')
    c.require(all(address <= int(row['target'],16) < address+width for row in instructions
                  if row['mnemonic'] in ('bc','b')), 'branch outside fixed span')
    return dict(address=f'{address:08x}', end_exclusive=f'{address+width:08x}', width=width,
                sha256=digest, spans=spans, instructions=instructions)


def cell_evidence(db, mapping, address, width):
    """A single selected index-zero cell; no inferred table extent."""
    c.require(all(type(value) is int for value in (address,width)), 'cell integer fields')
    c.require((address,width) == CELL[:2], 'cell range not allowlisted')
    normal.require_mapping(mapping, DATA3_MAPPING)
    start,end,_,_,_,length,root = mapping
    c.require(address % 4 == 0 and start <= address < address+width <= end, 'cell alignment/bounds')
    raw,spans = db.chain(root,address-start,width,length)
    c.require(len(raw) == width, 'cell byte width')
    digest = hashlib.sha256(raw).hexdigest()
    c.require(digest == CELL[3], 'cell digest mismatch')
    target = c.integer(raw,0,'I')
    c.require(target == CELL[2], 'cell target mismatch')
    return dict(address=f'{address:08x}', end_exclusive=f'{address+width:08x}', width=width,
                signed_index=0, target=f'{target:08x}', sha256=digest, spans=spans,
                extent_basis='one separately selected signed-index-zero cell, not table extent')


def inspect(data, digest):
    auth = c.inspect(data,digest)
    db = c.GBF(data); tables = db.tables()
    blocks,subs = db.rows(tables['Memory Blocks']),db.rows(tables['Sub Memory Blocks'])
    image = int(auth['image_offset'],16)
    command.mappings(blocks,subs,image)
    mapping,text_facts = normal.mapping_evidence(blocks,subs,image,TEXT_MAPPING)
    data3,data3_facts = normal.mapping_evidence(blocks,subs,image,DATA3_MAPPING)
    ranges = [range_evidence(db,mapping,pc,width) for pc,width,_ in RANGES]
    cell = cell_evidence(db,data3,CELL[0],CELL[1])
    keys = ('snapshot','snapshot_sha256','program_name','created_with_ghidra_version',
            'executable_sha256_metadata','executable_sha256_property_type','executable_metadata_caveat',
            'file_bytes_table','block_size','master_root','table_roots','image_offset','data5_sha256')
    return dict({key:auth[key] for key in keys}, mappings=[text_facts,data3_facts],ranges=ranges,cell=cell,
        function_coverage=[dict(entry=f'{pc:08x}',end_exclusive=f'{pc+width:08x}',selected_width=width,
            represented_instructions=width//4,unrepresented_instructions=0,unrepresented_ranges=[],
            map_size=width if pc==0x8006b7f4 else None,
            extent_basis='C/index identity and exact named map size' if pc==0x8006b7f4 else
                         'C/index-bounded span; no named map size exists') for pc,width,_ in RANGES],
        selection_basis=dict(reads=3,bytes=624,selected_code_bytes=620,selected_data_cells=1,
            pointer_driven_reads=False,global_payloads_read=False,original_execution=False,
            globals_runtime_values_established=False,constants_selected=False,estimator_imported=False,
            indirect_site='8006b83c',table_base='802d39a0',table_extent_established=False,
            selected_signed_indices=[0],unselected_direct_call_sites=['8006b968','8006b990'],
            unselected_direct_target='8020bc88',
            scopes_sha256=['dbed8ccb85183c2c37a4404be4c8629d0c9152702cfd396c9004649701bc81bc',
                           'afeccd2c0e9c2307560b95573fa87df4235055781b1bbd7f4be539e16edb3236',
                           '994fb4ec6df229a72c7e48143145126995520fbc50761546d844171a6fbdb52b']),
        caveat='Archived ProgramDB static evidence only, not original-DOL identity, execution, MATCH, '
               'live dispatch, runtime integration or playability. All 155 selected instructions represented. '
               '8006b850 is C/index-bounded, not map-size-proven. Only signed index zero cell is selected; '
               'other table cells, globals/actors, live r13, GQR/FPSCR state and 8020bc88 remain unselected. '
               'Existing full-data5 authentication reads are unchanged. Pointers never select runtime reads.')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('snapshot',type=Path)
    args = parser.parse_args()
    try:
        c.require(args.snapshot.is_file(), 'snapshot is not a regular file')
        with args.snapshot.open('rb') as stream:
            c.require(32 <= args.snapshot.stat().st_size <= c.MAX_FILE, 'snapshot size bounds')
            data = stream.read(c.MAX_FILE+1)
        c.require(len(data) <= c.MAX_FILE, 'snapshot exceeds size bound')
        print(json.dumps(inspect(data,hashlib.sha256(data).hexdigest()),indent=2,allow_nan=False))
    except (OSError,c.FormatError) as exc:
        print(json.dumps({'error':str(exc)}),file=sys.stderr)
        return 1
    return 0


if __name__ == '__main__': sys.exit(main())
