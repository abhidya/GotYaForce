// @gf/save — NOT IMPLEMENTED. This package is intentionally empty.
//
// Read this before importing anything from here: there is nothing to import, and the
// emptiness is a recorded product decision, not an oversight or a stub half-way through.
//
// WHAT THIS PACKAGE WAS FOR (PHASE0 §7/§8): borg collection + mission progress persisted to
// IndexedDB, against a schema reverse-engineered from the GameCube memory-card save (*.gci)
// so real saves could round-trip byte-exact.
//
// WHAT ACTUALLY SHIPS TODAY, and where to change persistence instead:
//   * Gotcha-Box pool + collection -> apps/game/src/sim/getStorage.ts (localStorage,
//     versioned, with an unreadable-payload park so a bad row cannot wipe a collection),
//     driven by @gf/missions createGotchaBoxSettlement.
//   * Force slots                  -> apps/game/src/ui/screens/SelectForce.ts (localStorage
//     key "gf-force-slots-v1", same unreadable-payload discipline).
// Neither is the *.gci schema, and neither claims to be.
//
// WHY IT IS STILL HERE rather than deleted: the open item is a product decision the owner
// has not made — docs/audits/game-app-defect-ledger.md §3.6 records it as "either implement
// the @gf/save contract behind the Load Box Data screen, or rename that screen Skip-only",
// because today "Load Box Data" offers a Load that loads nothing. Deleting the package would
// quietly close a decision nobody made and hide the gap; leaving a comment block plus a bare
// `export {}` made it look like a real module. So it stays, and it says what it is.
//
// If you are here to implement it: take the ledger row with you, and remove this notice in
// the same change that makes the Load path do something.
export {};
