# Archived animation selector and setup metadata evidence

2026-11-13. Read-only local authenticated ProgramDB inspection, with no original
executable access, runtime capture, network, publication or new constant targets.

Reader: `research/tools/matching-decomp/read_archived_setup_metadata_evidence.py`.
Both existing authenticated `db.3.gbf` and `db.4.gbf` snapshots under
`research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/`
pass the existing constant reader's snapshot/schema/mapping/data5 checks and agree:

- Selector `8004d1f4..8004d244`, 80 bytes, SHA-256
  `9e0f6e4ba064be40990771590bfc7bd13f3fa71b4299825c03df53932bf73bd2`.
- Metadata `8004d244..8004d548`, 772 bytes, SHA-256
  `f2464189801b361f9fdadecff1325e0f69c9cb2c4b1c2101f64fabc1fc1e5128`.

Ends are exclusive. Selector returns at d240. Metadata has internal returns for
negative/out-of-range channels and each channel body; its final return is d544.
All direct branches in these spans remain inside their respective function spans;
there are no calls. The source display endpoints therefore agree with this bounded
control-flow inspection. Selected word annotations, not raw ranges, are emitted.
Mapping remains MAIN_.text1 key/subblock 1, start 800055e0, length 2796416,
chain root 21. Snapshot hashes and executable metadata caveat are emitted by the
reader. Agreement does not prove unchanged original-DOL bytes or live parity.

## Selector order

Shared group reads actor+1d8c, masks group to seven bits and doubles it. Family
group0 first loads actor+582 and sign-extends it, then loads actor+1d88. Family
index doubling is modulo32, not an unsigned-byte mask. Both group and action
relative offsets use `lhax` (signed16), with action displacement relative to the
resolved group base. Actor/group/action are r3/r4/r5. This is independent of the
unverified setup-table dispatch and does not enable that dispatch.

## Metadata order

Actor/channel/part/metadata are r3/r4/r5/r6. Load metadata[0] and store part+32
before branching on channel. For each admitted channel, source byte loads and
stores alternate: selector2a, selector2b, rewind26 (zero-extended byte to halfword),
auxiliary37. Mirror control snapshots the flags byte, reading mirror30 only on
the XOR1 branch. Flags are loaded AGAIN after mirror processing for loop2c:
d2d8/d3fc/d49c/d524 for channels0/1/2/3. Low two flags zero preserve mirror without
reading it. Channel1 actor stores +1d98/+1d99/+1d9b each follow their own byte load.

Channel0 metadata9 is loaded once at d2f8, sign-tested, and retained in r7.
Negative case: load part33 at d304; load actor descriptor4b0 at d308; sign-extend
and double bank at d30c/d310; load descriptor+be at d314; add target base d318;
store actor target+1d74 at d31c. Nonnegative case loads bank at d324, sign-extends,
doubles and adds target, then stores retained r7 at d334, without metadata reread.

Metadata10 is loaded at d338 only after the first target store and retained in
r6. Negative case separately reloads part33 at d344 and descriptor4b0 at d348,
loads fallback+bf at d354 and stores actor target+1d75 at d35c. Direct case loads
bank at d364 then stores retained r6 at d374, without metadata reread. After both
target stores, part33 is loaded AGAIN at d378. If zero, load +1d74/store +1d94,
then load +1d75/store +1d95. No parallel snapshot of both final copy sources.

The target-bank sign extension and modulo32 shift are instruction facts. Host
rejection of negative/out-of-layout storage, invalid owned records, arithmetic
backing overflow or unsupported aliases remains host policy, not source behavior.
Do not validate unused fields eagerly or roll back completed writes on refusal.

## Verification

`python -m unittest discover -s research/tools/matching-decomp -p test_archived_setup_metadata_evidence.py`
passes seven synthetic-only tests: spoof resistance, schema failure propagation,
exact allowlist/unchanged constants, hash/word/output checks, width/alignment/bounds,
independent field decoding, and selected branch/endpoints. Both snapshot CLIs pass.
Aggregate repository results are recorded in the source-owned dispatch plan, not
treated as original execution evidence. No new constants or dispatch table
targets. These prerequisites
do not establish full ready actor setup, asset hydration or gameplay parity.
