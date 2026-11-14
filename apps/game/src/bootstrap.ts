import { showStartupFailure } from "./startupFailure.js";

// Keep the error boundary outside main's module evaluation. Renderer creation
// can throw before main installs its asset-loading catch or renders any UI.
void import("./main").catch(showStartupFailure);
