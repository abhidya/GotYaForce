/** Simulation integration, not a player/browser playthrough: force KOs in real
 * Challenge's first battle and check the real session proceeds to battle two. */
import { createGameSession } from '../apps/game/src/gameSession.js';
import { EXPORTED_STAGE_CATALOG_ADAPTER } from '../apps/game/src/sim/adapter.js';
import { battleOutcomeFromState } from '../apps/game/src/sim/presentation.js';
import { createChallengeRun, computeResults } from '@gf/missions';
import { emptyInput } from '@gf/combat';
import { battleStateForSelfcheck } from '../packages/combat/src/battle.js';
import data from '../packages/assets/data/borgs.json' with {type:'json'};
const check=(v:unknown,m:string)=>{if(!v) throw Error(m)};
const slot={no:1,name:'TEST',borgIds:['pl0615']};
const session=createGameSession({initialForceSlots:[slot], forceFromSlot:s=>s.borgIds,validForce:ids=>[...ids],
 createRun:createChallengeRun,borgs:data.borgs, borgStats:data.borgs as any,stageCatalog:EXPORTED_STAGE_CATALOG_ADAPTER,
 loadStageAssets:async()=>({renderState:{},modelUrls:[]}) as any});
console.info=()=>{};
for(const e of [{type:'boot-ready'},{type:'title-enter'},{type:'menu-select',mode:'challenge'},
 {type:'difficulty-select',budget:1500},{type:'players-select',playerCount:1},{type:'box-continue'},
 {type:'force-slot-confirm',slot},{type:'briefing-confirm'}] as const) session.dispatch(e);
const {battle,localPlayerId}=await session.prepareBattle();session.dispatch({type:'battle-started'});
const state=battleStateForSelfcheck(battle);let frames=0;
while(battle.observe().result==='ongoing' && frames++<10000){
 for(const b of state.borgs) {if(b.team===1 && b.alive) b.hp=0; if(b.team===0 && b.alive) b.hp=100000;}
 battle.step(1/60,{[localPlayerId]:emptyInput()});
}
check(battle.observe().result==='win',`battle did not resolve to win: ${battle.observe().result}`);
const results=computeResults(battleOutcomeFromState(battle,localPlayerId));
check(results.outcome==='WIN','battle telemetry did not map win');
session.dispatch({type:'battle-resolved',battleResults:results,drops:[],stats:{attack:results.attack,hitRatio:results.hitRatio*100,dodgeRatio:results.dodgeRatio*100,enemyBorgsDefeated:results.enemyBorgsDefeated,enemyTotalCost:results.costWon,playerBorgsDefeated:results.playerBorgsDefeated,playerTotalCost:results.costLost,allyBorgsDefeated:results.allyBorgsDefeated,grandTotal:results.grandTotal}});
const snap=session.snapshot();check(snap.screen==='briefing',`expected second briefing, got ${snap.screen}`);
check(snap.run?.current===1,`expected second battle, got ${snap.run?.current}`);
console.log(`challenge real-win PASS: forced enemy defeat to next briefing in ${frames} frames`);
