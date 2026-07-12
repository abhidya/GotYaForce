import { defineConfig } from 'vitepress'
import { dirname, join } from 'node:path'
import { fileURLToPath } from 'node:url'

const BASE = process.env.GH_PAGES_BASE ?? '/GotYaForce/'
const SKIP_PUBLIC_ASSETS = process.env.GF_ATLAS_SKIP_MODELS === '1'
const __dirname = dirname(fileURLToPath(import.meta.url))
const PUBLIC_DIR = join(__dirname, '..', 'public')

export default defineConfig({
  title: 'Gotcha Force Research Atlas',
  description: 'Decompilation progress, systems, borg atlas, stage atlas, and evidence for Gotcha Force (GG4E / NTSC-U).',
  base: BASE,
  cleanUrls: true,
  lastUpdated: true,
  vite: { publicDir: SKIP_PUBLIC_ASSETS ? false : PUBLIC_DIR },
  head: [
    ['link', { rel: 'icon', type: 'image/svg+xml', href: `${BASE}favicon.svg` }],
    ['link', { rel: 'preconnect', href: 'https://fonts.googleapis.com' }],
    ['link', { rel: 'preconnect', href: 'https://fonts.gstatic.com', crossorigin: '' }],
    [
      'link',
      {
        rel: 'stylesheet',
        href: 'https://fonts.googleapis.com/css2?family=Inter:wght@400;500;600;700&family=JetBrains+Mono:wght@400;500;700&family=Space+Grotesk:wght@500;600;700&display=swap'
      }
    ],
    ['meta', { name: 'theme-color', content: '#101114' }]
  ],
  themeConfig: {
    siteTitle: 'GF Research Atlas',
    outline: { level: [2, 3], label: 'On this page' },
    docFooter: { prev: 'Prev', next: 'Next' },
    lastUpdatedText: 'Last verified',
    darkModeSwitchLabel: 'Theme',
    returnToTopLabel: 'Back to top',
    sidebarMenuLabel: 'Sections',
    search: { provider: 'local', options: { translations: { button: { buttonText: 'Search atlas', buttonKey: 'k' } } } },
    nav: [
      { text: 'Overview', link: '/' },
      { text: 'Progress', link: '/progress' },
      { text: 'Functions', link: '/functions' },
      { text: 'Call Graph', link: '/call-graph' },
      {
        text: 'Architecture',
        items: [
          { text: 'Execution Map', link: '/execution-map' },
          { text: 'Memory Map', link: '/memory-map' },
          { text: 'Source Map', link: '/source-map' },
          { text: 'Call Graph', link: '/call-graph' }
        ]
      },
      { text: 'Systems', link: '/systems/' },
      { text: 'Borg Atlas', link: '/borgs/' },
      { text: 'Stage Atlas', link: '/stages/' },
      {
        text: 'Atlases',
        items: [
          { text: 'Weapons & Items', link: '/weapons/' },
          { text: 'Force (Gacha + Fusion)', link: '/force/' },
          { text: 'Modes', link: '/modes/' }
        ]
      },
      {
        text: 'Research',
        items: [
          { text: 'Evidence', link: '/evidence/' },
          { text: 'Data Tables', link: '/data-tables/' },
          { text: 'Tooling', link: '/tooling/' },
          { text: 'Roadmap', link: '/roadmap/' }
        ]
      }
    ],
    sidebar: {
      '/systems/': [
        {
          text: 'Systems',
          items: [
            { text: 'Overview', link: '/systems/' },
            { text: 'Combat & Damage', link: '/systems/combat' },
            { text: 'Damage Formula & Type Matrix', link: '/systems/damage' },
            { text: 'Status Effects', link: '/systems/status-effects' },
            { text: 'Action Stream / Cue Script', link: '/systems/action-stream' },
            { text: 'Particle Effects', link: '/systems/particles' },
            { text: 'Anim-Coupled SFX', link: '/systems/audio-sfx' },
            { text: 'HUD', link: '/systems/hud' },
            { text: 'Controls', link: '/systems/controls' }
          ]
        }
      ],
      '/stages/': [
        {
          text: 'Stage Atlas',
          items: [
            { text: 'Overview', link: '/stages/' },
            { text: 'Lighting & Render State', link: '/stages/lighting' },
            { text: 'Geometry & Collision', link: '/stages/geometry' },
            { text: 'Export Plan', link: '/stages/export' },
            { text: 'Readability Flags', link: '/stages/readability' }
          ]
        }
      ],
      '/borgs/': [
        {
          text: 'Borg Atlas',
          items: [
            { text: 'Overview', link: '/borgs/' },
            { text: 'Color Variants', link: '/force/color-variants' },
            { text: 'Stat Growth', link: '/systems/stat-growth' }
          ]
        }
      ],
      '/force/': [
        {
          text: 'Force',
          items: [
            { text: 'Overview', link: '/force/' },
            { text: 'Gotcha-Box Drops', link: '/force/gotcha-box' },
            { text: 'Fusion Pairs', link: '/force/fusion' },
            { text: 'Color Variants', link: '/force/color-variants' }
          ]
        }
      ],
      '/modes/': [
        {
          text: 'Modes',
          items: [
            { text: 'Overview', link: '/modes/' },
            { text: 'Story / Adventure', link: '/modes/story' },
            { text: 'Challenge', link: '/modes/challenge' },
            { text: 'Versus / Co-op', link: '/modes/versus' },
            { text: 'Attract Demo', link: '/modes/attract' }
          ]
        }
      ],
      '/evidence/': [
        {
          text: 'Evidence',
          items: [
            { text: 'Overview', link: '/evidence/' },
            { text: 'Function Index', link: '/evidence/functions' },
            { text: 'Runtime Traces', link: '/evidence/traces' },
            { text: 'Save / GCI Format', link: '/evidence/save-gci' },
            { text: 'Disc / ISO Layout', link: '/evidence/disc-iso' },
            { text: 'Trace Validity Ledger', link: '/evidence/traces-ledger' }
          ]
        }
      ],
      '/tooling/': [
        {
          text: 'Tooling',
          items: [
            { text: 'RE Stack', link: '/tooling/' },
            { text: 'Pipeline Patches', link: '/tooling/patches' }
          ]
        }
      ]
    },
    socialLinks: [{ icon: 'github', link: 'https://github.com/abhidya/GotYaForce' }],
    footer: {
      message: 'Research documentation. No copyrighted game assets are hosted. All claims cite disc/code offsets and repro steps.',
      copyright: 'Gotcha Force fan research — not affiliated with Nintendo/Capcom.'
    }
  }
})
