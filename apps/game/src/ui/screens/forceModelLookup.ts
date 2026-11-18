/** Share an in-flight/successful catalog request, but allow a later selection to
 * retry a failed fetch. A rejection is returned to the caller for handling. */
export function createForceModelLookup(load: () => Promise<ReadonlyMap<string, string>>): () => Promise<ReadonlyMap<string, string>> {
  let pending: Promise<ReadonlyMap<string, string>> | null = null;
  return () => {
    if (!pending) {
      pending = load().catch((error: unknown) => {
        pending = null;
        throw error;
      });
    }
    return pending;
  };
}
