import * as THREE from 'three';
import {BattleScene} from '../apps/game/src/sim/battleScene.js';
import type {BattleActorView} from '../apps/game/src/sim/battleView.js';
function assert(ok:unknown,msg:string):asserts ok{if(!ok)throw Error(`[teleportScene] ${msg}`);}
const flush=async()=>{await Promise.resolve();await Promise.resolve();};
function frame(hidden?:boolean):BattleActorView{
 return {uid:'teleporter',borgId:'pl0005',combatFormId:undefined,team:0,ownerPlayer:'p1',alive:true,state:'special',anim:'special',
 pos:{x:100,y:50,z:200},vel:{x:0,y:0,z:0},rotY:.25,modelSizeScale:1,lockTarget:null,allyLockTarget:null,
 dashActiveFrames:0,chargeFrames:0,meleeAnimStream:null,meleeSounds:null,lastHitImpactEffectId:undefined,lastHitAttackerTeam:undefined,
 slowHitTimer:0,hasteHitTimer:0,romAfterimage:undefined,...(hidden===undefined?{}:{sourceHidden:hidden})};
}
export async function runTeleportSceneSelfcheck():Promise<void>{
 const load=THREE.TextureLoader.prototype.load;THREE.TextureLoader.prototype.load=function(){return new THREE.Texture();};
 let resolveModel!:(m:THREE.Object3D)=>void;
 const modelPromise=new Promise<THREE.Object3D>(resolve=>{resolveModel=resolve;});
 let scene:BattleScene;
 try{scene=new BattleScene(new THREE.Group(),{loadModel:()=>modelPromise,loadClip:async()=>null});}
 finally{THREE.TextureLoader.prototype.load=load;}
 const actors=(scene as unknown as{actors:Map<string,{group:THREE.Group;ready:boolean}>}).actors;
 const hidden=frame(true);scene.sync([hidden]);const actor=actors.get(hidden.uid)!;
 assert(actor&&!actor.group.visible,'travel hides placeholder before asynchronous model arrives');
 const before=JSON.stringify(hidden);scene.update(20);scene.sync([hidden]);
 assert(!actor.group.visible&&JSON.stringify(hidden)===before,'render pause never advances simulation or visibility');
 resolveModel(new THREE.Group());await flush();scene.sync([hidden]);await flush();
 assert(actor.ready&&!actor.group.visible,'late model cannot resurrect invisible travel');
 scene.sync([frame(false)]);assert(actor.group.visible,'recovery restores exact actor82 visibility');
 scene.sync([hidden]);scene.sync([frame()]);assert(actor.group.visible,'omitted source state restores interrupted presentation');
 scene.sync([hidden]);scene.sync([{...hidden,alive:false,state:'death',anim:'death'}]);
 assert(actor.group.visible,'death ownership cannot strand an actor hidden');
 scene.sync([]);scene.sync([]);scene.clear();assert(actors.size===0&&!actor.group.parent,'omission/repeated cleanup retires actor');
 console.log('[teleportScene] PASS: travel hidden, async model completion, pause, recovery/interruption/death restore and cleanup');
}
