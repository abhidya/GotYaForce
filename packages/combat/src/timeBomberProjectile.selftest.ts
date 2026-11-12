import {createTimeBomberPrimary,stepTimeBomberPrimary,timeBomberMuzzle,createTimeBomberExplosion,stepTimeBomberExplosion,TIME_BOMBER_EXPLOSION_DAMAGE} from './timeBomberProjectile.js';
import type {Projectile} from './types.js';
export function runSelfTest():void{
 const ok=(v:unknown,m:string)=>{if(!v)throw Error(`[timeBomberProjectile] ${m}`);};
 const near=(a:number,b:number,m:string)=>ok(Math.abs(a-b)<1e-6,`${m}: ${a} != ${b}`);
 const zero={x:0,y:0,z:0},target={uid:'t',pos:{x:0,y:0,z:2000},radius:60};
 let p=createTimeBomberPrimary(zero,0,target);
 ok(p.pending&&p.life===300&&p.speed===20,'allocator seeds pending flight');near(p.pos.z,0,'no constructor movement');
 p=stepTimeBomberPrimary(p,target);ok(!p.pending&&p.life===300,'initializer retains full life');near(p.pos.z,0,'no initializer movement');
 const aimedOnly=createTimeBomberPrimary(zero,0,{...target,pos:{x:7000,y:0,z:0}},1,null,false);
 ok(aimedOnly.targetUid===null,'d0 bit4 clear disables tracking');
 const aimedFar=createTimeBomberPrimary(zero,0,{...target,pos:{x:7000,y:0,z:0}},1,{x:7000,y:0,z:0},false);
 near(aimedFar.vel.x,20,'outside lock range still initially aims');
 const sideways={...target,pos:{x:2000,y:1000,z:0}};
 for(const speed of [28,36,44]){p=stepTimeBomberPrimary(p,sideways);near(p.speed,speed,'source pre-move acceleration');near(p.vel.x,0,'no steering before period4');}
 p=stepTimeBomberPrimary(p,sideways);ok(p.vel.x>0&&p.vel.y>0&&p.steeringTimer===4,'period4 steers in full3D');near(p.speed,52,'fourth speed');
 p=stepTimeBomberPrimary(p,sideways);near(p.speed,60,'fifth speed');p=stepTimeBomberPrimary(p,sideways);near(p.speed,60,'maximum speed');
 let lost=stepTimeBomberPrimary(p,null);ok(lost.targetUid===null,'invalid original target clears');
 lost=stepTimeBomberPrimary(lost,sideways);ok(lost.targetUid===null,'cannot reacquire original target');
 const close=stepTimeBomberPrimary({...p,pos:zero},{...target,pos:{x:0,y:0,z:260}});ok(close.targetUid===null,'surface distance release threshold');
 const far=stepTimeBomberPrimary({...p,pos:zero},{...target,pos:{x:0,y:0,z:261}});ok(far.targetUid==='t','outside surface release threshold retains target');
 const finalFlight=stepTimeBomberPrimary({...p,life:1},target);ok(finalFlight.alive&&finalFlight.life===0,'life1 still moves');
 ok(!stepTimeBomberPrimary(finalFlight,target).alive,'life0 expires without child');
 ok(!stepTimeBomberPrimary({...p,durability:0},target).alive,'durability exhausted retires without child');
 const m=timeBomberMuzzle(zero,0,2);near(m.x,-357.17944431305016,'joint7 plus local x');near(m.y,260.2520751953125,'joint7 plus local y');near(m.z,63.21999561942282,'joint7 plus local z');
 let cue=-1;const explosion=createTimeBomberExplosion({ownerUid:'o',team:0,pos:zero,timeBomberSource:p} as Projectile,c=>cue=c);
 ok(cue===12&&explosion.romShotKind===179&&explosion.damageRecord===TIME_BOMBER_EXPLOSION_DAMAGE,'explosion19 common179 identity');
 ok(explosion.damageRecord?.comboScoreValue===50&&explosion.damageRecord?.flagsA===0x60&&explosion.damageRecord?.knockbackPitchTrim===32,'not Gatling damage');
 const s=explosion.timeBomberSource!;if(s.kind!=='explosion')throw Error('kind');
 near(s.scale,.01,'initial scale');for(let i=0;i<13;i++)stepTimeBomberExplosion(s);ok(s.phase==='hold','13 expansion frames');
 for(let i=0;i<4;i++)stepTimeBomberExplosion(s);ok(String(s.phase)==='tail','four hold frames');
 for(let i=0;i<30;i++)ok(stepTimeBomberExplosion(s),'tail survives 30');ok(!stepTimeBomberExplosion(s),'tail expires after30');
}
