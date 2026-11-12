import * as THREE from 'three';
import {BattleScene} from '../apps/game/src/sim/battleScene.js';
import {createNinjaShurikenFlight,stepNinjaShurikenFlight} from '../packages/combat/src/ninjaShurikenFlight.js';
import {createNinjaImpact} from '../packages/combat/src/ninjaProjectile.js';
import type {BattleProjectileObservation,Projectile} from '../packages/combat/src/types.js';
function assert(ok:unknown,msg:string):asserts ok{if(!ok)throw Error(`[ninjaScene] ${msg}`);}
function near(a:number,b:number,msg:string){assert(Math.abs(a-b)<1e-5,`${msg}: ${a} != ${b}`);}
export async function runNinjaSceneSelfcheck():Promise<void>{
 const load=THREE.TextureLoader.prototype.load;THREE.TextureLoader.prototype.load=function(){return new THREE.Texture();};
 const root=new THREE.Group();let scene:BattleScene;
 try{scene=new BattleScene(root,{loadModel:async()=>new THREE.Group(),loadClip:async()=>null});}
 finally{THREE.TextureLoader.prototype.load=load;}
 const internals=scene as unknown as {projectileActors:Map<string,{node:THREE.Object3D;material:THREE.Material&{opacity:number};ninja?:string}>};
 const source={kind:'primary' as const,flight:createNinjaShurikenFlight(3,{origin:{x:10,y:200,z:30},yaw:.4,ownerScale:2,collisionScale:.75}),ownerBorgId:'pl000a',ownerFormId:'pl000a',hitUids:[],contactPending:false};
 const pr={uid:'ninja-scene',ownerUid:'owner',team:0,pos:{x:10,y:200,z:30},vel:{x:0,y:0,z:40},life:600,hitRadius:7.5,visualKind:'energy',ninjaSource:source} as Projectile;
 const sync=(rows:BattleProjectileObservation[]=[pr])=>scene.sync([],rows);
 sync();const actor=internals.projectileActors.get(pr.uid)!;
 assert(actor.ninja==='primary'&&!actor.node.visible,'pending source child hidden');
 source.flight=stepNinjaShurikenFlight(source.flight).state;pr.pos={...source.flight.pos};sync();
 assert(actor.node.visible&&(actor.node as THREE.Mesh).geometry.getAttribute('position').count===12,'procedural four-blade visual');
 near(actor.node.rotation.y,source.flight.yaw+source.flight.spinAngleS16*Math.PI*2/65536,'source spin relative to owner yaw');
 near(actor.node.scale.x,4,'draw multiplier2 independent from collision scale.75');near(pr.hitRadius,7.5,'render does not promote drawing size to HIT');
 const snapshot=JSON.stringify(pr),pose=actor.node.rotation.clone();scene.update(20);sync([pr,pr]);
 assert(JSON.stringify(pr)===snapshot&&actor.node.rotation.equals(pose)&&internals.projectileActors.size===1,'paused/repeated render cannot advance source');
 let disposal=0,geometryDisposal=0;actor.material.addEventListener('dispose',()=>disposal++);
 (actor.node as THREE.Mesh).geometry.addEventListener('dispose',()=>geometryDisposal++);
 source.flight=stepNinjaShurikenFlight(source.flight,{ownerInvalid:'owner-dead'}).state;sync();assert(!actor.node.visible,'released source hidden');
 const impact=createNinjaImpact(pr,pr.pos,2);impact.uid=pr.uid;sync([impact]);
 const next=internals.projectileActors.get(pr.uid)!;assert(next!==actor&&next.ninja==='impact'&&disposal===1,'source kind replacement disposes old private material');
 assert(impact.ninjaSource?.kind==='impact','impact fixture');near(next.node.scale.x,620*impact.ninjaSource.scale,'impact scale follows85e00');
 impact.ninjaSource.alpha=.25;sync([impact]);near(next.material.opacity,.25,'impact simulation alpha');
 let impactDisposal=0;next.material.addEventListener('dispose',()=>impactDisposal++);sync([]);sync([]);scene.clear();
 assert(geometryDisposal===0&&impactDisposal===1&&!actor.node.parent&&!next.node.parent,'omission disposes private material once, retains shared geometry');
 console.log('[ninjaScene] PASS: procedural blade/spin, source scaling, independent HIT, hidden phases, pause and disposal');
}
