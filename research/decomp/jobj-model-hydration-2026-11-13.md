# Bounded model DAT to owned JObj transforms

Source audit: 2026-11-13, starting checkout `82ebca3a` on `feat/double-clone-lifecycle`. This note uses the already-local Ghidra export only. No original binary comparison, asset inspection, live replay, matrix verification or retail execution was performed. Repository `AGENTS.md` labels its former wasm-driver runbook retired; no `.agents` directory exists in this checkout.

## Recommended contract

The implemented bounded API is `createSourceJObjModelHydrationRuntime(joints, limits).hydrateModelArchive(bytes, publicIndex)`. It accepts bare DAT bytes and one explicitly selected model public index, using the existing `SourceJObjAnimationRuntime` owner methods. It returns the selected runtime root, frozen public metadata and a frozen data-offset-to-owned-joint list. It does not accept or fabricate class callback selectors: bindings initially have null AObj/RObj/DObj/class callback fields, and the actual consumer later installs its real packed scalar callback. Subsequent attachment, packed dispatch and scalar update use this same runtime, not a disconnected playback skeleton.

The admitted graph contains ordinary non-instance, nonquaternion JObj descriptors with null class-name, display payload, RObj and optional matrix pointers. A null class-name is a sufficient bounded ordinary-class domain; a non-null unknown name can fall back to base allocation in retail, but reproducing that requires class lookup and is not implied here. Flags `0x1000` and `0x20000` refuse. Display-mode bits `0x20`/`0x4000` are preserved when the payload is null; any non-null payload refuses regardless of gating. No flags are silently cleared. Any repeated reachable descriptor, including acyclic sharing, refuses as an explicit host-domain restriction.
This is a host import/preflight, not a complete `HSD_JObjLoadJoint` port or an emulation of allocation/fault order. Bounds, relocation classification, finite-f32 requirements, cycle checks, node/depth budgets and overlap restrictions must be documented as host limits. Use private copied input bytes. Validate the complete admitted graph before exposing owner effects, and document that already-completed owner effects cannot be rolled back if an adapter fails.

## Source facts and field mapping

All line references below are in `research/decomp/ghidra-export/chunk_0071.c`.

- `JObjInit_bl` at 7583–7599 sets runtime `flags14 = 0x40` on successful parent initialization. `JObjLoad` at 5610 ORs descriptor flags into existing flags, rather than replacing them. The base load therefore begins with `(descriptor.flags04 | 0x40) >>> 0`.
- `JObjLoad` at 5598–5609 zeros runtime child `+10`, sibling `+08` and parent `+0c`. Descriptor `child08` and `next0c` are not copied directly into runtime link fields.
- Rotation descriptor `+14/+18/+1c` copies to runtime `+1c/+20/+24`; scale `+20/+24/+28` to `+2c/+30/+34`; translation `+2c/+30/+34` to `+38/+3c/+40` (5636–5646). Preserve all nine values, including negative zero. Do not substitute identity/default scale or translation.
- Display handling at 5612–5630 branches on `0x4000` and `0x20`; ordinary mode calls DObj loading, alternate modes retain payload and one walks/mutates it. RObj loading runs at 5631–5635. These are real omitted capabilities, not dummy effects to claim as implemented.
- Descriptor association is recorded through ID insertion and runtime `+84` at 5662–5665. This is source descriptor association, not proof that runtime allocation is memoized.

## One selected root, child sibling chains

`HSD_JObjLoadJoint` (5709–5745) allocates and loads only its supplied root descriptor. It does not follow that descriptor's own `next0c`. In `JObjLoad` (5666–5700), the non-instance case iterates `descriptor.child08`, then each child's `next0c`. Every child is independently allocated and loaded before `HSD_JObjAddChild` attaches it. Descendants are consequently loaded before that child is attached to its parent.

Distinguish descriptor inspection from runtime traversal. Source metadata may retain a root's raw next pointer, but that target must not become another runtime root or sibling merely because it is present. A host may impose structural bounds on ignored metadata; it must label that stricter limit rather than assert that retail traverses it. A malformed/unsupported graph reachable only through the selected root's next must not accidentally be hydrated.

The implementation's global descriptor seen-set deliberately refuses both cycles and repeated acyclic descriptors. That is a narrower host domain than source ordinary loading, not proof that source rejects sharing. Because each admitted descriptor occurs exactly once, descriptor/depth budgets bound the supported graph without DAG expansion. Independent imports and repeated root selections still produce fresh runtime objects.
## Descriptor sharing is not runtime sharing

Each ordinary child encounter allocates (`5673–5692`), and each LoadJoint call allocates (`5709–5745`). Two parents referencing the same descriptor would require separate runtime symbols and transform records. The implemented domain refuses that repeated-descriptor case before allocation rather than incorrectly collapsing it into one owner. If sharing is supported later, immutable source descriptor caching must remain separate from runtime occurrence allocation.
Instances are different: ResolveRefs (`5751–5795`) looks up the child's descriptor ID, replaces the runtime child and increments its reference count when `flags & 0x1000`. Excluding instances and all reference-bearing payloads avoids pretending to implement this aliasing/ID-table behavior. Do not derive ID-table collision behavior for repeated descriptors from the ordinary allocation observation.

## AddChild parent links and flag summaries

`HSD_JObjAddChild` at 6113–6173 requires an orphan child with no sibling. It appends it to the parent's existing child chain (6147–6165), then writes child.parent0c (6166). Maintain these links in the actual `SourceJObjScalarHeader` and `SourceJObjAnimationBinding`, not in a parallel facade.

At 6167–6170 the propagated mask is exactly:

`mask = (child.flags14 | (child.flags14 << 10)) & 0x70000000`

It ORs that mask into the parent and proceeds through ancestors while the current ancestor lacks any mask bit. Both the child's already-aggregated high bits and its own bits 18–20 contribute. Do not propagate all child flags or only the shifted low bits. For an importer that constructs source-order subtrees before attachment, descendant summaries are already in the child's flags when the child is attached. Normalize JavaScript bitwise results back to uint32. Parent root remains null; selected root runtime sibling remains null.

## Matrix omission is a deliberate boundary

Even when descriptor `matrix38` is null, JObjLoad initializes the live matrix at runtime `+44` to identity and zeros `+74` (5647–5651). For non-null descriptor matrix, it allocates runtime `+78` and copies 0x30 bytes (5653–5659). Thus rejecting non-null matrix is necessary but insufficient to claim a complete JObj load: current scalar owners have neither live nor inverse matrix storage or matrix setup.

The useful supported result is owned initial transforms and topology feeding genuine packed scalar animation. The projection is not skinning, rendering, geometry, a complete executable model loader or a demonstrated playable actor. It can feed the existing local transform pose-capture pipeline, as the composed synthetic integration does; this does not supply world matrices or a general quaternion backend. Keep those boundaries visible in implementation comments and completion reports.

## Integration and regression checklist

1. A synthetic bare DAT public selects the model root explicitly; public enumeration/name order is never actor joint-bank order. Preserve DAT relocation distinction: relocated raw zero means data+0, unrelocated zero means null, public offset zero means data+0. Use existing archive conventions, not pointer guessing.
2. Distinct nontrivial rotation/scale/translation values, negative zero and descriptor flags survive creation; each runtime flag includes 0x40. Mutation of input bytes or one runtime copy must not mutate other owners/source records.
3. Root-next target is not allocated; child siblings and grandchildren are linked in order with correct parent identities. Repeated reachable descriptors, including acyclic sharing, refuse before allocation; cycles and descriptor/depth-budget exhaustion also refuse. Independent imports allocate fresh owners.
4. Descendant local flag bits 18–20 and preexisting subtree bits 28–30 propagate up multiple levels; unrelated bits do not. Root sibling and root parent stay null.
5. Instances, non-null classes/display/RObj/matrix and invalid finite-f32 or pointer/relocation shapes refuse before owner creation under the host preflight contract.
6. Integrate an explicitly selected imported joint into the existing animation-archive hydration, archive setup, JObjAddAnim and actual packed FObj/AObj callback flow. Assert that packed evaluation changes that exact joint's owned transform record, preserves unrelated model values and participates in existing dirty/update behavior. Do not substitute the model root when the explicit actor-bank mapping selects a child. Hand-written replacement transform symbols or a second playback state do not meet this check.
7. Do not claim model node order supplies `actor+1d9c`, joint-bank indices, actor selection, model public selection or model-to-animation matching. Those require separate explicit evidence/inputs.

## Read-only implementation and composed-test review

Reviewed `packages/combat/src/rom/jobj-model-hydration.ts`, its selftest and the model addition to `attached-setup-animation.selftest.ts`. The importer implements the bounded domain above. Reverse preorder computes completed subtree summary flags before allocating owners; this reproduces final projected flags while deliberately not claiming source allocation/effect order. Actual owned child/sibling/parent fields are linked, and the selected root's next is ignored except for global relocation validity.

The integration fixture explicitly selects model public 0 at data+0x80, maps the actor's active joint to data+0x40, and retains the other child at data+0 and grandchild at data+0xc0. It independently imports an animation DAT, runs the actual bank/setup/opcode01/attachment/packed scalar callback path and captures a local pose from the same imported owner. Assertions cover unchanged unrelated joints, frame/wait behavior, replacement ownership, rejected reimport preserving active ownership, fresh successful reimport and actual dirty-subtree traversal. Its world matrices and pose pool are separate explicit fixture inputs; Euler conversion remains the existing positive-zero-only fixture backend. This is meaningful owner-path integration, not production model selection or original-asset replay.

Final stable-version read-only review is complete. No blocking source-semantic or composed-owner-path issue was found within the stated domain. The final runtime additionally revalidates all owned transforms, topology and bindings after the last adapter call, refusing intervening mutation instead of returning a bad graph. Final units include all nine scalar mappings at all four fixture nodes, positive null-payload display-mode flag cases, receiver preservation and a 4096-deep iterative hierarchy. The source review did not edit runtime code or independently rerun execution checks. Separate focused selftests, enhanced strict TypeScript, actual-command integration and 4096 variable-tree references covering 36,884 owned joints passed.
