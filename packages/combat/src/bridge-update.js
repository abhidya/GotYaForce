const fs = require('fs');
const file = 'packages/combat/src/bridge.ts';
let content = fs.readFileSync(file, 'utf8');

// Replace all old pl09 registrations
content = content
  // GUARD WITCH / SHIELD WITCH
  .replace(
    /pl0903: makeSimpleRegistration\("pl0903".*?\n.*?pl090a: makeSimpleRegistration\("pl090a".*?\n/,
    `      pl0903: makeSimpleRegistration("pl0903", (a, ctx) => configureNurseFamily(a, "pl0903", ctx)),\n      pl090a: makeSimpleRegistration("pl090a", (a, ctx) => configureNurseFamily(a, "pl090a", ctx)),\n`
  )
  // PATRA WITCH / ISIS WITCH
  .replace(
    /pl0902: makeSimpleRegistration\("pl0902".*?\n.*?pl0909: makeSimpleRegistration\("pl0909".*?\n/,
    `      pl0902: makeSimpleRegistration("pl0902", (a, ctx) => configureNurseFamily(a, "pl0902", ctx)),\n      pl0909: makeSimpleRegistration("pl0909", (a, ctx) => configureNurseFamily(a, "pl0909", ctx)),\n`
  )
  // FORTRESS BORGS (pl0e00/pl0e05)
  .replace(
    /pl0e00: makeSimpleRegistration\("pl0e00".*?\n.*?pl0e05: makeSimpleRegistration\("pl0e05".*?\n/,
    `      pl0e00: makeSimpleRegistration("pl0e00", (a, ctx) => configureFortressFamily(a, "pl0e00", ctx)),\n      pl0e05: makeSimpleRegistration("pl0e05", (a, ctx) => configureFortressFamily(a, "pl0e05", ctx)),\n`
  )
  // DEATH BORG THETA / DEATH BORG IOTA
  .replace(
    /pl0906: makeSimpleRegistration\("pl0906".*?\n.*?pl090b: makeSimpleRegistration\("pl090b".*?\n/,
    `      pl0906: makeSimpleRegistration("pl0906", (a, ctx) => configureNurseFamily(a, "pl0906", ctx)),\n      pl090b: makeSimpleRegistration("pl090b", (a, ctx) => configureNurseFamily(a, "pl090b", ctx)),\n`
  )
  // BASTET WITCH / SEKHMET WITCH
  .replace(
    /pl0907: makeSimpleRegistration\("pl0907".*?\n.*?pl090c: makeSimpleRegistration\("pl090c".*?\n/,
    `      pl0907: makeSimpleRegistration("pl0907", (a, ctx) => configureNurseFamily(a, "pl0907", ctx)),\n      pl090c: makeSimpleRegistration("pl090c", (a, ctx) => configureNurseFamily(a, "pl090c", ctx)),\n`
  )
  // ANGEL NURSE family (pl0900/0908/090d)
  .replace(
    /pl0900: makeSimpleRegistration\("pl0900".*?\n.*?pl0908: makeSimpleRegistration\("pl0908".*?\n.*?pl090d: makeSimpleRegistration\("pl090d".*?\n/,
    `      pl0900: makeSimpleRegistration("pl0900", (a, ctx) => configureNurseFamily(a, "pl0900", ctx)),\n      pl0908: makeSimpleRegistration("pl0908", (a, ctx) => configureNurseFamily(a, "pl0908", ctx)),\n      pl090d: makeSimpleRegistration("pl090d", (a, ctx) => configureNurseFamily(a, "pl090d", ctx)),\n`
  )
  // DEATH BORG NU family (pl0f01/pl0f02/pl0f03)
  .replace(
    /pl0f01: makeSimpleRegistration\("pl0f01".*?\n.*?pl0f02: makeSimpleRegistration\("pl0f02".*?\n.*?pl0f03: makeSimpleRegistration\("pl0f03".*?\n/,
    `      pl0f01: makeSimpleRegistration("pl0f01", (a, ctx) => configureNuFamily(a, "pl0f01", ctx)),\n      pl0f02: makeSimpleRegistration("pl0b02", (a, ctx) => configureNuFamily(a, "pl0f02", ctx)),\n      pl0f03: makeSimpleRegistration("pl0f03", (a, ctx) => configureNuFamily(a, "pl0f03", ctx)),\n`
  );

fs.writeFileSync(file, content);
console.log("Done");
