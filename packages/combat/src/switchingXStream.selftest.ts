import {createSwitchingXStream,tickSwitchingXStream} from './switchingXStream.js';
function check(value:unknown,message:string):asserts value{if(!value)throw new Error(message);}
export function runSwitchingXStreamSelfTest():void{
  for(const slot of [4,5] as const){
    const stream=createSwitchingXStream(slot);let release=0,releases=0,end=0,recovery=0;
    for(let tick=1;tick<200;tick++){
      const event=tickSwitchingXStream(stream,1);
      if(event.contact===1){release=tick;releases++;}
      if(event.animation){recovery=tick;check(event.animation[0]===0&&event.animation[1]===14,'air recovery descriptor');}
      if(event.completed){end=tick;break;}
    }
    check(release===28&&releases===1,'absolute frame25 releases once after source blend');
    check(slot===4?end===83&&recovery===0:end===97&&recovery===81,'original clip endpoint/recovery clocks');
    const frame=stream.frame;tickSwitchingXStream(stream,1);check(stream.frame===frame,'completed stream is stable');
  }
  console.log('[switchingXStream] PASS: authored release and recovery clocks');
}
