import * as THREE from 'three';
import {BattleScene} from '../apps/game/src/sim/battleScene.js';
import {createGredRangedFlight,stepGredRangedFlight} from '../packages/combat/src/gredRangedFlight.js';
import type {BattleProjectileObservation} from '../packages/combat/src/types.js';
function assert(ok:unknown,msg:string):asserts ok{if(!ok)throw Error(`[gredRangedScene] ${msg}`);}
function near(a:number,b:number,msg:string){assert(Math.abs(a-b)<1e-4,`${msg}: ${a} != ${b}`);}
export async function runGredRangedSceneSelfcheck():Promise<void>{
 const load=THREE.TextureLoader.prototype.load;
 THREE.TextureLoader.prototype.load=function(){return new THREE.Texture();};
 const root=new THREE.Group();let scene:BattleScene;
 try{scene=new BattleScene(root,{loadModel:async()=>new THREE.Group(),loadClip:async()=>null});}
 finally{THREE.TextureLoader.prototype.load=load;}
 const internals=scene as unknown as{projectileActors:Map<string,{node:THREE.Object3D;material:THREE.Material&{opacity:number};gredRanged?:boolean}>};
 const source={flight:createGredRangedFlight(43,{x:10,y:20,z:30},{x:0,y:0,z:1})};
 const pr={uid:'ranged',ownerUid:'owner',team:0,pos:{x:10,y:20,z:30},vel:{x:0,y:0,z:1},
  life:300,hitRadius:21.645,visualKind:'energy',gredRangedSource:source} as unknown as BattleProjectileObservation;
 const sync=(p:BattleProjectileObservation[]=[pr])=>scene.sync([],p);
 sync();const actor=internals.projectileActors.get(pr.uid)!;
 assert(actor.gredRanged&&!actor.node.visible,'pending child is hidden/source routed');
 source.flight=stepGredRangedFlight(source.flight).state;sync();
 assert(actor.node.visible&&actor.node.children.length===2,'initialized procedural crossed planes');
 near(actor.node.scale.x,40,'width follows original width normalization');near(actor.node.scale.y,1,'initial source length one');
 near(actor.node.position.z,30.5,'trail midpoint behind source tip');
 for(let i=0;i<20;i++)source.flight=stepGredRangedFlight(source.flight).state;
 sync();near(actor.node.scale.y,1000,'RED drawing length caps1000');
 near(actor.node.position.z,source.flight.pos.z-500,'trail anchored at tip');
 const axis=new THREE.Vector3(0,1,0).applyQuaternion(actor.node.quaternion);near(axis.z,1,'long axis follows source trail');
 const collision=source.flight.collisionScale;
 const snapshot=JSON.stringify(pr),pose=actor.node.position.clone(),scale=actor.node.scale.clone();
 scene.update(12);sync([pr,pr]);
 assert(JSON.stringify(pr)===snapshot&&actor.node.position.equals(pose)&&actor.node.scale.equals(scale),'render pause/repeated sync never advances flight');
 assert(internals.projectileActors.size===1,'duplicate UID does not duplicate visual');
 source.flight=stepGredRangedFlight(source.flight,{priorContactBits:2}).state;
 source.flight=stepGredRangedFlight(source.flight).state;sync();
 near(actor.node.scale.y,source.flight.length,'contact tail follows simulation shrink');
 near(source.flight.collisionScale,collision,'drawing tail does not resize HIT sphere');
 let disposals=0,geometryDisposals=0;actor.material.addEventListener('dispose',()=>disposals++);
 for(const mesh of actor.node.children)(mesh as THREE.Mesh).geometry.addEventListener('dispose',()=>geometryDisposals++);
 source.flight=stepGredRangedFlight(createGredRangedFlight(101,{x:0,y:0,z:0},{x:0,y:0,z:1},2)).state;
 for(let i=0;i<20;i++)source.flight=stepGredRangedFlight(source.flight).state;
 sync();near(actor.node.scale.x,80,'model scale affects width');near(actor.node.scale.y,500,'NEO cap500 independent of model scale');
 source.flight=stepGredRangedFlight(source.flight,{outsideBounds:()=>true}).state;
 source.flight=stepGredRangedFlight(source.flight).state;sync();near(actor.node.scale.x,80*Math.fround(.9),'expiry tail narrows independently');
 for(let i=0;i<80&&source.flight.phase!=='freed';i++)source.flight=stepGredRangedFlight(source.flight).state;
 sync();assert(!actor.node.visible,'released/freed observations hidden');
 sync([]);sync([]);scene.clear();
 assert(disposals===1&&geometryDisposals===0&&!actor.node.parent,'dispose private material once, retain shared geometry');
 console.log('[gredRangedScene] PASS: length/width, tip anchor, independent sphere, tails, pause and disposal');
}
