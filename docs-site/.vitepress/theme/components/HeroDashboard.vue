<script setup lang="ts">
import metricsData from '../../data/metrics.json'
import progressData from '../../data/progress.json'
import latestData from '../../data/latest.json'

const m = metricsData
</script>

<template>
  <section class="gf-hero">
    <div class="gf-hero-top">
      <div class="gf-hero-eyebrow">
        <span class="gf-hero-pill">GG4E / NTSC-U</span>
        <span class="gf-hero-pill">GameCube</span>
        <span class="gf-hero-pill">Reverse Engineering</span>
      </div>
      <h1 class="gf-hero-title">Gotcha Force<br /><span>Research Atlas</span></h1>
      <p class="gf-hero-sub">
        A live field guide and evidence dashboard for the decompilation, memory layout, asset pipeline,
        and game systems of <em>Gotcha Force</em> (2003). Every claim traces to disc offsets, RAM fields,
        named functions, and repro steps.
      </p>
      <div class="gf-hero-cta">
        <a class="gf-btn gf-btn-primary" href="/GotYaForce/progress/">View progress dashboard</a>
        <a class="gf-btn" href="/GotYaForce/borgs/">Browse Borg Atlas</a>
        <a class="gf-btn" href="/GotYaForce/evidence/">See evidence ledger</a>
      </div>
    </div>

    <div class="gf-hero-metrics gf-grid gf-grid-4">
      <div class="gf-hero-metric">
        <div class="gf-hero-metric-num">{{ m.functionsIndexed.toLocaleString() }}</div>
        <div class="gf-hero-metric-lbl">Functions indexed</div>
        <div class="gf-hero-metric-sub">Ghidra full-corpus</div>
      </div>
      <div class="gf-hero-metric">
        <div class="gf-hero-metric-num">{{ m.borgsIndexed }}</div>
        <div class="gf-hero-metric-lbl">Borgs catalogued</div>
        <div class="gf-hero-metric-sub">208 indexes · 13 anim slots</div>
      </div>
      <div class="gf-hero-metric">
        <div class="gf-hero-metric-num">{{ m.stagesMapped }}</div>
        <div class="gf-hero-metric-lbl">Stages mapped</div>
        <div class="gf-hero-metric-sub">18 named arenas</div>
      </div>
      <div class="gf-hero-metric">
        <div class="gf-hero-metric-num">{{ m.tunedRemaining }}</div>
        <div class="gf-hero-metric-lbl">TUNED markers left</div>
        <div class="gf-hero-metric-sub">of {{ m.tunedTotal }} total</div>
      </div>
    </div>

    <div class="gf-hero-bottom gf-grid gf-grid-2">
      <div class="gf-hero-panel">
        <div class="gf-panel-header">System coverage</div>
        <ProgressMatrix :systems="progressData.systems" />
      </div>
      <div class="gf-hero-panel">
        <div class="gf-panel-header">Latest findings</div>
        <ul class="gf-hero-latest">
          <li v-for="f in latestData.findings" :key="f.title">
            <a :href="f.href">
              <span class="gf-hero-latest-title">{{ f.title }}</span>
              <span class="gf-hero-latest-meta">{{ f.area }} · {{ f.date }}</span>
            </a>
          </li>
        </ul>
      </div>
    </div>

    <p class="gf-hero-foot">
      Last verified {{ m.lastVerified }}. No copyrighted game assets hosted — only offsets, hashes,
      structs, and repro steps. Not affiliated with Nintendo/Capcom.
    </p>
  </section>
</template>

<style scoped>
.gf-hero {
  padding: 8px 0 24px;
}
.gf-hero-top {
  padding: 24px 0 20px;
  border-bottom: 1px solid var(--gf-border);
  margin-bottom: 24px;
}
.gf-hero-eyebrow {
  display: flex;
  gap: 6px;
  flex-wrap: wrap;
  margin-bottom: 14px;
}
.gf-hero-pill {
  font-family: var(--gf-mono);
  font-size: 0.7rem;
  padding: 2px 9px;
  border-radius: 999px;
  background: var(--gf-panel-2);
  color: var(--gf-muted);
  border: 1px solid var(--gf-border);
}
.gf-hero-title {
  font-family: var(--gf-display);
  font-weight: 700;
  font-size: clamp(2.4rem, 6vw, 4rem);
  line-height: 1.05;
  letter-spacing: -0.03em;
  margin: 0 0 14px;
  color: var(--gf-text);
}
.gf-hero-title span {
  background: linear-gradient(135deg, var(--gf-accent) 0%, var(--gf-accent-2) 100%);
  -webkit-background-clip: text;
  background-clip: text;
  color: transparent;
}
.gf-hero-sub {
  font-size: 1.05rem;
  color: var(--gf-text-dim);
  max-width: 680px;
  margin: 0 0 20px;
  line-height: 1.6;
}
.gf-hero-sub em {
  color: var(--gf-text);
  font-style: normal;
  font-weight: 500;
}
.gf-hero-cta {
  display: flex;
  gap: 10px;
  flex-wrap: wrap;
}
.gf-btn {
  display: inline-flex;
  align-items: center;
  padding: 10px 18px;
  border-radius: 8px;
  font-family: var(--gf-display);
  font-weight: 500;
  font-size: 0.9rem;
  text-decoration: none;
  border: 1px solid var(--gf-border-strong);
  color: var(--gf-text);
  background: var(--gf-panel);
  transition: all 0.18s;
}
.gf-btn:hover {
  border-color: var(--gf-accent-2);
  color: var(--gf-accent-2);
}
.gf-btn-primary {
  background: linear-gradient(135deg, var(--gf-accent) 0%, var(--gf-accent-2) 100%);
  color: var(--gf-bg);
  border-color: transparent;
  font-weight: 600;
}
.gf-btn-primary:hover {
  color: var(--gf-bg);
  filter: brightness(1.08);
}
.gf-hero-metrics {
  margin-bottom: 20px;
}
.gf-hero-metric {
  background: var(--gf-panel);
  border: 1px solid var(--gf-border);
  border-radius: 12px;
  padding: 18px;
  position: relative;
  overflow: hidden;
}
.gf-hero-metric::before {
  content: '';
  position: absolute;
  top: 0;
  left: 0;
  right: 0;
  height: 2px;
  background: linear-gradient(90deg, var(--gf-accent), var(--gf-accent-2));
  opacity: 0.6;
}
.gf-hero-metric-num {
  font-family: var(--gf-display);
  font-weight: 700;
  font-size: 2.2rem;
  letter-spacing: -0.02em;
  background: linear-gradient(135deg, var(--gf-accent) 0%, var(--gf-accent-2) 100%);
  -webkit-background-clip: text;
  background-clip: text;
  color: transparent;
  line-height: 1;
}
.gf-hero-metric-lbl {
  font-family: var(--gf-display);
  font-size: 0.86rem;
  color: var(--gf-text);
  margin-top: 8px;
}
.gf-hero-metric-sub {
  font-family: var(--gf-mono);
  font-size: 0.72rem;
  color: var(--gf-muted);
  margin-top: 2px;
}
.gf-hero-panel {
  background: var(--gf-panel);
  border: 1px solid var(--gf-border);
  border-radius: 12px;
  padding: 18px;
}
.gf-hero-latest {
  list-style: none;
  padding: 0;
  margin: 0;
}
.gf-hero-latest li {
  border-bottom: 1px solid var(--gf-border);
}
.gf-hero-latest li:last-child {
  border-bottom: none;
}
.gf-hero-latest a {
  display: flex;
  justify-content: space-between;
  align-items: center;
  gap: 10px;
  padding: 10px 0;
  text-decoration: none;
}
.gf-hero-latest-title {
  color: var(--gf-text);
  font-size: 0.92rem;
}
.gf-hero-latest a:hover .gf-hero-latest-title {
  color: var(--gf-accent-2);
}
.gf-hero-latest-meta {
  font-family: var(--gf-mono);
  font-size: 0.72rem;
  color: var(--gf-muted);
  white-space: nowrap;
}
.gf-hero-foot {
  margin-top: 20px;
  padding-top: 16px;
  border-top: 1px solid var(--gf-border);
  font-size: 0.8rem;
  color: var(--gf-muted);
}
@media (max-width: 620px) {
  .gf-hero-cta .gf-btn {
    flex: 1;
    justify-content: center;
  }
}
</style>
