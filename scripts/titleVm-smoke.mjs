import { createTitleVm } from "../apps/game/src/ui/intro/titleVm.ts";

const log = [];
const sink = {
  attachDeskArchives: () => log.push("attach"),
  screenColor: () => log.push("color"),
  selectWidgetOrEffect: (e) => log.push("effect:" + e),
  setCameraMode: (m) => log.push("cam:" + m),
  setAudioCue: (c) => log.push("cue:" + c),
  actorPlayAnim: (s, g, a) => log.push("anim s" + s + " g" + g + " a" + a),
  actorReset: (s) => log.push("reset s" + s),
  actorSetVisible: (s, v) => log.push("vis s" + s + ":" + v),
  toggleOverlay: (on) => log.push("overlay:" + (on ? "on" : "off")),
  copyOverlayTransform: () => log.push("copyXform"),
  titleLightBar: () => log.push("lightbar"),
  spawnTitleWidget: (id) => log.push("widget:" + id),
  setTitleWidgetMode: (m) => log.push("wmode:" + m),
  playSound: (c) => log.push("sound:" + c),
};

const vm = createTitleVm(sink);
let frames = 0;
while (frames < 4000 && vm.state.endRequested === 0) {
  vm.tick();
  frames++;
}

const anim = log.filter((x) => x.startsWith("anim"));
const s = vm.state;
const ok = s.endRequested === 1 && anim.filter((x) => x.includes("s0")).length > 0 && anim.filter((x) => x.includes("s1")).length > 0 && s.actors.length === 2;
console.log("frames=" + frames + " pc=" + s.pc + " end=" + s.endRequested);
console.log("actors=" + s.actors.map((a) => a.slot + ":" + a.borgId).join(", "));
console.log("anim events=" + anim.length + " (s0=" + anim.filter((x) => x.includes("s0")).length + " s1=" + anim.filter((x) => x.includes("s1")).length + ")");
console.log("first 10 events: " + log.slice(0, 10).join(" | "));
console.log("VERDICT: " + (ok ? "PASS — VM executes full script, both G RED + Sasuke animated, reaches end" : "FAIL"));
if (!ok) process.exit(1);
