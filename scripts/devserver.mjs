// Zero-dependency static dev server for the Gotcha Force web slice.
// Usage: node scripts/devserver.mjs [rootDir] [port]
// Reusable local dev server until the Vite/netcode stack lands.
import { createServer } from 'node:http';
import { readFile, stat } from 'node:fs/promises';
import { join, normalize, extname } from 'node:path';

const ROOT = process.argv[2] || 'apps/slice';
const PORT = Number(process.argv[3] || 5173);

const MIME = {
  '.html': 'text/html; charset=utf-8',
  '.js': 'text/javascript; charset=utf-8',
  '.mjs': 'text/javascript; charset=utf-8',
  '.css': 'text/css; charset=utf-8',
  '.json': 'application/json; charset=utf-8',
  '.dae': 'model/vnd.collada+xml',
  '.gltf': 'model/gltf+json',
  '.glb': 'model/gltf-binary',
  '.png': 'image/png',
  '.jpg': 'image/jpeg',
  '.webp': 'image/webp',
  '.ktx2': 'image/ktx2',
  '.wasm': 'application/wasm',
  '.ogg': 'audio/ogg',
  '.bin': 'application/octet-stream',
};

const server = createServer(async (req, res) => {
  try {
    let urlPath = decodeURIComponent(new URL(req.url, 'http://x').pathname);
    if (urlPath === '/') urlPath = '/index.html';
    const filePath = normalize(join(ROOT, urlPath));
    if (!filePath.startsWith(normalize(ROOT))) { res.writeHead(403).end('forbidden'); return; }
    const s = await stat(filePath);
    if (s.isDirectory()) { res.writeHead(403).end('no listing'); return; }
    const body = await readFile(filePath);
    res.writeHead(200, {
      'Content-Type': MIME[extname(filePath).toLowerCase()] || 'application/octet-stream',
      'Cache-Control': 'no-cache',
      'Access-Control-Allow-Origin': '*',
    });
    res.end(body);
  } catch (e) {
    res.writeHead(404, { 'Content-Type': 'text/plain' }).end('404: ' + req.url);
  }
});

server.listen(PORT, () => console.log(`dev server: http://localhost:${PORT}  (root=${ROOT})`));
