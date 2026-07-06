---
title: Call Graph
---

<script setup>
import CallGraph from './.vitepress/theme/components/CallGraph.vue'
</script>

# Call graph

Interactive force-directed graph of the 400 most-connected decompiled functions. Edges represent caller→callee relationships from `function-evidence-index.json`. Node color encodes the function's topic bucket.

<CallGraph />

::: tip Explore
Hover any node for details. Toggle topics in the filter bar above the canvas. Use the mouse wheel to zoom, drag to pan.
:::

For the full 11,972-function index with search and source viewer, see the [Function Explorer](./functions).
