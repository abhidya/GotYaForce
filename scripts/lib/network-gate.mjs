/** Only deliberate HTMLAudioElement replacement is a non-fatal cancellation. */
export function isExpectedMediaCancellation(event, requestUrl, pageUrl) {
  return (
    event.canceled === true &&
    event.errorText === "net::ERR_ABORTED" &&
    typeof requestUrl === "string" &&
    requestUrl.startsWith(`${pageUrl}audio/`) &&
    /\.ogg(?:[?#]|$)/i.test(requestUrl)
  );
}
