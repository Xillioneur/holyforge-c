#!/bin/bash
mkdir -p public

# Build community module (C)
emcc src/main.c -o public/community.js \
  -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
  -s MODULARIZE=1 \
  -s EXPORT_NAME='createCommunityModule' \
  -s USE_SDL=2 \
  -O2

# Build Parables (Modular C++ 3D Wireframe)
em++ src/parables/main.cpp src/parables/engine.cpp src/parables/model.cpp \
  -o public/parables.js \
  -fno-exceptions \
  -fno-rtti \
  -s DISABLE_EXCEPTION_CATCHING=1 \
  -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
  -s MODULARIZE=1 \
  -s EXPORT_NAME='createParablesModule' \
  -s USE_SDL=2 \
  -s NO_FILESYSTEM=1 \
  -O3

# Build Code Review - Episode 8 (C++ / SDL2)
# We removed ASYNCIFY and used emscripten_set_main_loop in main.cpp
echo "Building Code Review Episode 8..."
em++ src/code-review/episode-8/main.cpp \
     src/code-review/episode-8/game.cpp \
     src/code-review/episode-8/training_bot.cpp \
     src/code-review/episode-8/utils.cpp \
  -o public/episode8.js \
  -Isrc/code-review/episode-8 \
  -std=c++17 \
  -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
  -s MODULARIZE=1 \
  -s EXPORT_NAME='createEpisode8Module' \
  -s USE_SDL=2 \
  -s ALLOW_MEMORY_GROWTH=1 \
  -O2

# Build Code Review - Episode 10 (C++ / Raylib)
echo "Building Code Review Episode 10..."
em++ src/code-review/episode-10/main.cpp \
     src/code-review/episode-10/core.cpp \
     src/code-review/episode-10/enemy.cpp \
     src/code-review/episode-10/particles.cpp \
     src/code-review/episode-10/player.cpp \
     src/code-review/episode-10/render.cpp \
  -o public/episode10.js \
  -Isrc/code-review/episode-10 \
  -I/Users/xillioneur/raylib/src \
  /Users/xillioneur/raylib/src/libraylib.web.a \
  -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
  -s MODULARIZE=1 \
  -s EXPORT_NAME='createEpisode10Module' \
  -s USE_GLFW=3 \
  -s ASYNCIFY \
  -O2

echo "WASM modules built in public/"