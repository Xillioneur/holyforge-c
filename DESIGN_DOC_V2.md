# HolyForge Games Website Design Document (v2 - C & Cloudflare Edition)

## 1. Studio Overview
HolyForge Games remains dedicated to crafting immersive gaming experiences inspired by the Catholic faith. Our mission is to forge digital worlds that uplift the spirit and promote virtues like faith, hope, and charity. AMDG.

## 2. High-Level Website Objectives
- Showcase studio identity and mission.
- Catalog and host C/C++ games for download.
- Provide news and blog updates.
- Community engagement via static forums or WASM-powered modules.
- **Cost Efficiency**: Utilize free-tier hosting to ensure sustainability.

## 3. Technical Stack (The "Holy C" Stack)
### 3.1 C Language Implementation
- **Core Engine**: The website is powered by a custom Static Site Generator (SSG) written entirely in **C11**.
- **Logic**: All HTML generation, metadata processing, and templating logic is handled by C code.
- **Dynamic Features**: Community interactions and forms are handled by C code compiled to **WebAssembly (WASM)**, running on Cloudflare's edge.
- **Safety**: Use of standard library strings and buffers with strict bounds checking.

### 3.2 Cloudflare Hosting
- **Cloudflare Pages**: High-performance, global CDN hosting for all static assets and HTML.
- **Cloudflare D1 (Optional)**: If a database is needed for the community, we interface with D1 (SQL) via WASM.
- **Cloudflare KV**: For fast, edge-cached metadata.
- **Zero Cost**: All selected services fall within Cloudflare's generous free tiers.

## 4. Website Architecture
- `src/main.c`: The site generator.
- `src/templates/`: HTML snippets managed as C strings or embedded files.
- `public/`: The output directory for Cloudflare Pages.
- `scripts/build.sh`: Orchestrates the compilation and generation.

## 5. Vision
By using C—the same language we use for our games—we ensure the highest performance and a unified codebase. The site will be as lightweight and efficient as the souls we aim to inspire.
