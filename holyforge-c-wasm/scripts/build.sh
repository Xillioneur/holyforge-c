#!/bin/bash
mkdir -p public
emcc src/main.c -o public/community.js \
  -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
  -s MODULARIZE=1 \
  -s EXPORT_NAME='createCommunityModule' \
  -s USE_SDL=2 \
  -O2
echo "WASM module built in public/community.js and public/community.wasm"