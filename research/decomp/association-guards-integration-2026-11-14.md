# Existing-evidence association guards, 2026-11-14

## Bounded source continuation

This checkpoint continues the already-authenticated `8006ae60` third pass
through `8006b380..8006b3b0`. After the existing captured-target83 gate:

1. Load caller `byte7d3` and test **bit 0 only**. Odd bytes skip; zero and
   nonzero even bytes continue.
2. Load captured target `team`, then caller `team`. Both are raw bytes
   sign-extended at use. Equal teams skip; no 0/1-only team restriction is added.
3. Load caller `horizontalDistance75c`, then the same caller's existing
   attribute binding `field814`.
4. Within the explicit finite exact-binary32 domain, skip only when distance
   is **greater** than the threshold. Less and equal reach the next boundary.

The next refusal occurs before `8006b3bc` reloads the physical actor base for
its inner scan. There is no target58a read, candidate traversal, candidate team
read or association-flag write. All skipped outer rows may still reach the
separate mandatory `80027764` boundary; no outer-frame success is added.

## Unchanged evidence scope

The existing [complete target-preparation report](target-preparation-evidence-2026-11-14.md)
and [fixed evidence tests](../tools/matching-decomp/test_archived_target_preparation_evidence.py)
authenticate all 380 instructions of `8006ae60..8006b44c`, with body digest
`6b725b93ac0755d146b4a67fe61ec81127d98afccc77ca5c3fcd990fa199b50a`.
This work uses the retained derived operands; it selects no new archive
payload, follows no source-data pointer, and makes no original-execution claim.

The recorded operations are `lbz` caller7d3 at380; `rlwinm.` bit0 at384;
nonzero branch at388; target/caller team loads at38c/390; their sign extensions
at394/398; equality comparison/branch at39c/3a0; caller75c and814 `lfs` at3a4
and3a8; `fcmpo` at3ac; and a **GT-only** branch at3b0. The register-only setup
at3b4/3b8 grants no permission to execute the inner memory access at3bc.

## Canonical owners and live loads

Flags, team and75c stay on the actual `RomActor`. The threshold stays on the
existing genuine `SourceActorAttributeRefreshBinding`, not a new actor field
or separate threshold table. Its identity is verified against the same
admission/status binding and `massPreparation.attributes` runtime. Registry
and owner checks are repeated after the reached load, so late replacement
cannot authorize the branch. No constructor defaults are introduced.

The six-actor fixture now accepts explicit initial attribute fields because
these existing bindings are sealed. Tests supply814 during original genuine
binding, rather than trying to add a field afterward. The earlier sparse and
target83 fixtures remain unhydrated for814. Zero target83 in that sparse
caller now stops at its missing own byte7d3 cell, not an invented zero.

Each reached scalar is captured once and guards do not reload it for branch
selection. A target-team change during the subsequent caller-team load cannot
change the earlier captured team. The same applies to flags, distance and
threshold. Existing active/pointer/target83 values also stay captured.

Reached aliases, independent caller/target incompleteness and caught reentry
refuse before later source loads. All previously completed mass, candidate,
distance and direction writes remain. Failure closes the entire retained outer
graph and leaves public scheduler/root execution inaccessible. Terminal checks
use the native descriptor intrinsic retained at module load, then revalidate
lifecycle and canonical owners without another observable metadata walk. This
closes late metadata-injected owner/lifecycle/alias changes after814 capture;
it does not reload the already captured branch operands.

## Numerical boundary

Both float operands must be finite, exact binary32 values. Negative finite
values and subnormals are supported in the existing finite host model. All
`+0/-0` combinations compare equal. Read-only source cells are valid.
Missing, malformed, non-exact-f32, NaN and infinite operands refuse at their
reached load; they are never normalized or given defaults.

The source's non-GT fallthrough includes unordered comparisons. Therefore it
must not be rewritten as `distance <= threshold` over arbitrary values.
This bounded continuation does not execute that unordered path, preserve NaN
payloads, emulate `fcmpo` exceptions, or model live FPSCR status. Its finite
comparison is source-ordered branch behavior, not a general floating processor
emulator or evidence of retail operand values.

## Verification scope

The new focused suite is wired into the existing attached-setup aggregate.
Cases cover flag bit selection, raw signed-byte teams, lazy early skips,
finite GT/LT/EQ and signed zero, subnormals, negative values, source order,
captured mutations, readonly cells, malformed operands, late aliases,
independent owner failure, reentry and canonical attribute replacement.

Existing target83 tests retain their own scope and now assert the real missing
caller7d3 boundary. Full contributor/build, strict TypeScript, focused,
matching/evidence, docs with explicit model-sync skip, and oracle/codec checks
remain the validation gates. None is browser, hardware or completed-frame
validation. The existing repeated-primary mass-table caveat is unchanged.

`80027764` remains outside the authenticated body set, and its byte-clear versus
pointer-store semantics remain unresolved. This checkpoint does not broaden
that evidence selection or skip the routine.
