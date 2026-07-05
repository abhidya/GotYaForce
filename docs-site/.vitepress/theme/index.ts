import type { Theme } from 'vitepress'
import DefaultTheme from 'vitepress/theme'
import { h } from 'vue'
import './style.css'
import StatusBadge from './components/StatusBadge.vue'
import MetricCard from './components/MetricCard.vue'
import ProgressMatrix from './components/ProgressMatrix.vue'
import EvidenceCard from './components/EvidenceCard.vue'
import AtlasTable from './components/AtlasTable.vue'
import ClaimTrail from './components/ClaimTrail.vue'
import ViewToggle from './components/ViewToggle.vue'
import HeroDashboard from './components/HeroDashboard.vue'

export default {
  extends: DefaultTheme,
  Layout: () => h(DefaultTheme.Layout),
  enhanceApp({ app }) {
    app.component('StatusBadge', StatusBadge)
    app.component('MetricCard', MetricCard)
    app.component('ProgressMatrix', ProgressMatrix)
    app.component('EvidenceCard', EvidenceCard)
    app.component('AtlasTable', AtlasTable)
    app.component('ClaimTrail', ClaimTrail)
    app.component('ViewToggle', ViewToggle)
    app.component('HeroDashboard', HeroDashboard)
  }
} satisfies Theme
