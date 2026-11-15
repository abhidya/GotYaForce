/** Shared negative witness for older deliberately sparse target fixtures.
 * Their first absent27764 destination is row0+38 AFTER the third genuine RNG
 * draw and table[2] load, not a successful/rolled-back predecessor boundary. */
interface Fixture {
 massPreparation:{rngState:{byte804360c6:number;byte804360c7:number}};
 actorSlots:Record<number,symbol|null>;teamRows103:readonly object[];physicalActors:readonly object[];
}
export function captureMissingLeaderIngress(x:Fixture) {
 const low='byte804360c6',high='byte804360c7',events:string[]=[];
 let l=x.massPreparation.rngState[low],h=x.massPreparation.rngState[high],reads=0,started=false;
 for(let i=0;i<3;i++){h=Math.floor((h*256+l)*3/256)&255;l=(l+h)&255;}
 const descriptors=x.physicalActors.map(actor=>['pointer330','byte334','byte335'].map(key=>Object.getOwnPropertyDescriptor(actor,key)));
 const check=(ok:boolean,why:string):void=>{if(!ok)throw Error(`[missing-leader-ingress] ${why}`);};
 return {
  observe(owner:object,key:PropertyKey):void {
   if(owner===x.massPreparation.rngState&&key===high&&++reads===5)started=true;
   if(!started)return;
   if(owner===x.massPreparation.rngState&&(key===high||key===low))events.push(String(key));
   if(owner===x.actorSlots&&/^[0-5]$/.test(String(key)))events.push('slot'+String(key));
   if(x.teamRows103.includes(owner)&&key==='pointer38')events.push('row'+x.teamRows103.indexOf(owner));
  },
  assert():void {
   check(events.join(',')===[high,low,high,low,'slot2','row0'].join(','),'exact third RNG/load/first-destination refusal prefix');
   check(x.massPreparation.rngState[low]===l&&x.massPreparation.rngState[high]===h,'third RNG effects retained');
   for(const row of x.teamRows103)check(!Object.hasOwn(row,'pointer38'),'absent row pointers stay absent');
   x.physicalActors.forEach((actor,i)=>['pointer330','byte334','byte335'].forEach((key,j)=>{
    const now=Object.getOwnPropertyDescriptor(actor,key),before=descriptors[i]![j];
    check(now===undefined&&before===undefined||now!==undefined&&before!==undefined&&
      Object.is(now.value,before.value)&&now.get===before.get&&now.set===before.set&&now.writable===before.writable,
      'no leader actor field changes before first row destination');
   }));
  },
 };
}
