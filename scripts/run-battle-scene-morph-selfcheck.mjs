#!/usr/bin/env node
import { runBattleSceneMorphSelfcheck } from "../.tmp/battle-scene-morph-selfcheck.mjs";
await runBattleSceneMorphSelfcheck();
console.log("battleScene morph selfcheck: PASS");
