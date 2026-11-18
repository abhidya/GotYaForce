#!/usr/bin/env node
// Numeric emulator evidence only; this is not original-hardware parity.
import {readFile} from 'node:fs/promises';
import {createRequire} from 'node:module';
import path from 'node:path';
import {fileURLToPath} from 'node:url';
const root=fileURLToPath(new URL('../',import.meta.url));
const require=createRequire(path.join(root,'packages/combat/package.json'));
const {build}=require('esbuild');
const result=await build({absWorkingDir:root,entryPoints:['packages/combat/src/rom/source-reciprocal-estimate.ts'],bundle:true,platform:'node',format:'esm',write:false});
const {sourceReciprocalEstimateBounded: estimate}=await import(`data:text/javascript;base64,${Buffer.from(result.outputFiles[0].text).toString('base64')}`);
const bytes=new DataView(new ArrayBuffer(4));
const fromBits=n=>{bytes.setUint32(0,n,false);return bytes.getFloat32(0,false);};
const bits=n=>{bytes.setFloat32(0,n,false);return bytes.getUint32(0,false);};
let count=0;
for(const file of ['fres-dolphin-grid-2026-11-18.json','fres-dolphin-fine-2026-11-18.json','fres-dolphin-half-2026-11-18.json']) {
  const samples=JSON.parse(await readFile(path.join(root,'research/decomp',file),'utf8'));
  if(samples.length!==128) throw Error(`${file}: incomplete sample set`);
  for(const [input,expected] of samples){if(bits(estimate(fromBits(parseInt(input,16))))!==parseInt(expected,16)) throw Error(`${file}: mismatch at ${input}`);count++;}
}
const notes=await readFile(path.join(root,'research/decomp/jobj-world-matrix-integration-2026-11-13.md'),'utf8');
const values=notes.split('### Controlled `fres` sweep')[1]?.split('```text\n')[1]?.split('```')[0]?.trim().split(/\s+/).map(Number);
if(values?.length!==65)throw Error('65-sample sweep missing');
for(let i=0;i<65;i++){const input=Math.fround((1+i/64)**2);if(bits(estimate(input))!==bits(values[i]))throw Error(`sweep mismatch at ${i}`);count++;}
for(const input of [0,-1,.5,.25,4.1,Infinity,NaN,1+2**-30]){let rejected=false;try{estimate(input);}catch{rejected=true;}if(!rejected)throw Error(`invalid input accepted: ${input}`);}
console.log(`[source-reciprocal-estimate] ${count} Dolphin observations matched; bounded candidate, not hardware parity`);
