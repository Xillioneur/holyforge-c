#!/bin/bash

echo "Starting HolyForge Build..."

# 1. Build WASM Module
echo "Building WASM Community Module..."
cd holyforge-c-wasm
./scripts/build.sh
cd ..

# 2. Build and Run SSG
echo "Building and Running SSG..."
cd holyforge-c
make clean
make
cd ..

echo "Build Complete. Files are in holyforge-c/public/"
