import * as THREE from 'three';
import { BattleScene } from '../apps/game/src/sim/battleScene.js';
import { createGBlackGroundWaveChild, stepGBlackGroundWaveChild } from '../packages/combat/src/gblackGroundWave.js';
import type { Projectile } from '../packages/combat/src/types.js';
function check(v:unknown,m:string):asserts v { if(!v)throw Error(`G BLACK wave scene: ${m}`); }
const near=(a:number,b:number)=>Math.abs(a-b)<1e-5;
export async function runBattleSceneGblackWaveSelfcheck():Promise<void>{
 const original=THREE.TextureLoader.prototype.load;
 THREE.TextureLoader.prototype.load=function(){return new THREE.Texture();};
 let scene:BattleScene;
 try {scene=new BattleScene(new THREE.Group(),{loadModel:async()=>new THREE.Group(),loadClip:async()=>null});}
 finally {THREE.TextureLoader.prototype.load=original;}
 const internals=scene as unknown as {projectileActors:Map<string,{node:THREE.Object3D;material:THREE.SpriteMaterial;beam:boolean}>};
 const context={terrainHeight:()=>25,rngByte:()=>0};
 const child=stepGBlackGroundWaveChild(createGBlackGroundWaveChild({pos:{x:10,y:25,z:30},modelScale:2,collisionScale:3}),context).state;
 const p:Projectile={uid:'wave-scene',ownerUid:'owner',team:0,pos:{...child.pos},vel:{x:0,y:0,z:0},
  life:30,damage:1,hitstun:0,knockback:1,homingTurn:0,homingTarget:null,hitRadius:450,
  visualKind:'flame',gblackGroundWaveSource:{...child,ownerBorgId:'pl062a',ownerFormId:'pl062a',hitUids:[]}};
 const sync=()=>scene.sync([], [p],null,false,[]);
 sync();const visual=internals.projectileActors.get(p.uid)!;
 check(visual&&!visual.beam,'active pulse gets generic flame, not invisible emitter or beam');
 check(near(visual.node.scale.x,120)&&near(visual.node.scale.y,150)&&near(visual.node.position.y,100),
  'source scale curve controls placeholder dimensions and ground anchor, independently of radius450');
 const snapshot=JSON.stringify(p), scale=visual.node.scale.clone();
 scene.update(100);sync();
 check(JSON.stringify(p)===snapshot&&visual.node.scale.equals(scale),'render updates cannot advance simulation lifetime or scale');
 let state=child;
 for(let i=0;i<3;i++)state=stepGBlackGroundWaveChild(state,context).state;
 p.gblackGroundWaveSource={...state,ownerBorgId:'pl062a',ownerFormId:'pl062a',hitUids:[]};sync();
 check(near(visual.node.scale.y,750)&&near(visual.node.position.y,400)&&p.hitRadius===450,'age3 visual growth leaves collision radius untouched');
 let disposed=0;visual.material.addEventListener('dispose',()=>disposed++);
 scene.sync([],[],null,false,[]);scene.clear();scene.clear();
 check(!visual.node.parent&&disposed===1&&internals.projectileActors.size===0,'authoritative omission and repeated clear retire material once');
 console.log('[gblackWaveScene] PASS: generic presentation, source scale, pause independence and cleanup');
}
