import * as THREE from 'three';
import {BattleScene} from '../apps/game/src/sim/battleScene.js';
import type {BattleProjectileObservation} from '../packages/combat/src/types.js';
function assert(ok:unknown,msg:string):asserts ok{if(!ok)throw Error(`[gblackChargeScene] ${msg}`);}
function near(a:number,b:number,msg:string){assert(Math.abs(a-b)<1e-6,`${msg}: ${a} != ${b}`);}
export async function runGBlackChargeSceneSelfcheck():Promise<void>{
 const load=THREE.TextureLoader.prototype.load;
 THREE.TextureLoader.prototype.load=function(){return new THREE.Texture();};
 const root=new THREE.Group();let scene:BattleScene;
 try{scene=new BattleScene(root,{loadModel:async()=>new THREE.Group(),loadClip:async()=>null});}
 finally{THREE.TextureLoader.prototype.load=load;}
 const internals=scene as unknown as{projectileActors:Map<string,{node:THREE.Object3D;material:THREE.Material&{opacity:number};gblackCharge?:string}>};
 const source={kind:'sweep',phase:'pending',stage:0,origin:{x:10,y:20,z:30},direction:{x:0,y:0,z:1},
  start:{x:10,y:20,z:30},end:{x:10,y:20,z:10030},visualScale:[1,1,1]};
 const pr={uid:'black-charge',ownerUid:'owner',team:0,pos:{x:10,y:20,z:73},vel:{x:0,y:0,z:1},
  life:1,hitRadius:30,visualKind:'energy',gblackChargeSource:source} as unknown as BattleProjectileObservation;
 const sync=(p:BattleProjectileObservation[]=[])=>scene.sync([],p);
 sync([pr]);const actor=internals.projectileActors.get(pr.uid)!;
 assert(actor.gblackCharge==='sweep'&&!actor.node.visible,'pending child is hidden and source routed');
 source.phase='active';sync([pr]);assert(actor.node.visible&&actor.node.children.length===2,'two crossed planes show windup');
 near(actor.node.scale.x,60,'windup width');near(actor.node.scale.y,60,'windup length');
 source.visualScale=[0,0,0];sync([pr]);near(actor.node.scale.x,0,'zero curve scale has no artificial minimum');
 source.visualScale=[.5,.5,1];source.stage=2;sync([pr]);
 near(actor.node.position.x,10,'sweep midpoint X');near(actor.node.position.z,5030,'sweep midpoint Z');
 near(actor.node.scale.x,30,'sweep curve width');near(actor.node.scale.y,10000,'ray distance independent of width/model scale');
 const axis=new THREE.Vector3(0,1,0).applyQuaternion(actor.node.quaternion);
 near(axis.z,1,'sweep long axis follows source segment');
 const snapshot=JSON.stringify(pr),pose=actor.node.position.clone(),scale=actor.node.scale.clone();
 scene.update(10);sync([pr,pr]);
 assert(JSON.stringify(pr)===snapshot&&actor.node.position.equals(pose)&&actor.node.scale.equals(scale),'render pause and repeated sync do not advance source data');
 assert(internals.projectileActors.size===1,'duplicate UID does not duplicate actor');
 let disposals=0,geometryDisposals=0;actor.material.addEventListener('dispose',()=>disposals++);
 for(const node of actor.node.children)(node as THREE.Mesh).geometry.addEventListener('dispose',()=>geometryDisposals++);
 source.phase='freed';sync([pr]);assert(!actor.node.visible,'freed observation is hidden before removal');
 const impact={...pr,pos:{x:50,y:60,z:70},gblackChargeSource:{kind:'impact',scale:1.25,alpha:.4}} as unknown as BattleProjectileObservation;
 sync([impact]);const next=internals.projectileActors.get(pr.uid)!;
 assert(next!==actor&&next.gblackCharge==='impact'&&disposals===1&&!actor.node.parent,'kind change replaces old visual once');
 near(next.node.scale.x,775,'impact diameter follows source scale');near(next.material.opacity,.4,'impact alpha follows source clock');
 let impactDisposals=0;next.material.addEventListener('dispose',()=>impactDisposals++);
 sync();sync();assert(impactDisposals===1&&geometryDisposals===0,'removal disposes material once, preserves shared geometry');
 scene.clear();assert(impactDisposals===1&&disposals===1,'repeated cleanup does not dispose retired materials again');
 console.log('[gblackChargeScene] PASS: source geometry/scales, pause, kind replacement and disposal');
}
