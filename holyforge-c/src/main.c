#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef struct {
    const char *id;
    const char *title;
    const char *subtitle;
    const char *description;
    const char *tag;
    const char *status;
    const char *download_url;
    const char *series; 
    int season; 
} Game;

const char *HTML_HEADER = 
"<!DOCTYPE html>\n"
"<html lang=\"en\">\n"
"<head>\n"
"    <meta charset=\"UTF-8\">\n"
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
"    <title>%s | HolyForge Games</title>\n"
"    <link rel=\"stylesheet\" href=\"/static/css/style.css\">\n"
"    <link href=\"https://fonts.googleapis.com/css2?family=Cinzel:wght@400;700&family=Lora&display=swap\" rel=\"stylesheet\">\n"
"    <script>\n"
"        (function() {\n"
"            const savedTheme = localStorage.getItem('theme') || 'light';\n"
"            document.documentElement.setAttribute('data-theme', savedTheme);\n"
"        })();\n"
"    </script>\n"
"</head>\n"
"<body>\n"
"    <header>\n"
"        <nav>\n"
"            <a href=\"/\" class=\"logo\">HolyForge</a>\n"
"            <div class=\"links\">\n"
"                <a href=\"/games.html\">Games</a>\n"
"                <a href=\"/blog.html\">Journal</a>\n"
"                <a href=\"/community.html\">Community</a>\n"
"                <a href=\"/about.html\">About</a>\n"
"                <button onclick=\"toggleTheme()\" class=\"theme-toggle\">Theme</button>\n"
"            </div>\n"
"        </nav>\n"
"    </header>\n"
"    <main>\n";

const char *HTML_FOOTER = 
"    </main>\n"
"    <footer>\n"
"        <div class=\"footer-content\">\n"
"            <div class=\"footer-section\">\n"
"                <p>&copy; 2026 HolyForge Games. Ad Maiorem Dei Gloriam.</p>\n"
"                <p style=\"margin-top: 10px; opacity: 0.6;\">Forged in the heart of C and the spirit of Truth.</p>\n"
"            </div>\n"
"            <div class=\"footer-section\" style=\"text-align: right;\">\n"
"                <p>HolyForge Games is a trademark coming soon.</p>\n"
"                <p style=\"opacity: 0.6;\">v2.1.0-alpha</p>\n"
"            </div>\n"
"        </div>\n"
"    </footer>\n"
"    <script>\n"
"        function toggleTheme() {\n"
"            const html = document.documentElement;\n"
"            const currentTheme = html.getAttribute('data-theme');\n"
"            const newTheme = currentTheme === 'dark' ? 'light' : 'dark';\n"
"            html.setAttribute('data-theme', newTheme);\n"
"            localStorage.setItem('theme', newTheme);\n"
"        }\n"
"    </script>\n"
"</body>\n"
"</html>\n";

void ensure_directory(const char *path) {
    #ifdef _WIN32
        _mkdir(path);
    #else
        mkdir(path, 0755);
    #endif
}

void write_page(const char *filename, const char *title, const char *content) {
    char path[256];
    snprintf(path, sizeof(path), "public/%s", filename);
    char *last_slash = strrchr(path, '/');
    if (last_slash) {
        *last_slash = '\0';
        ensure_directory(path);
        *last_slash = '/';
    }
    FILE *f = fopen(path, "w");
    if (!f) { perror("Error opening file"); return; }
    fprintf(f, HTML_HEADER, title);
    fprintf(f, "%s", content);
    fprintf(f, "%s", HTML_FOOTER);
    fclose(f);
    printf("Generated: %s\n", path);
}

int main() {
    ensure_directory("public");
    ensure_directory("public/games");
    ensure_directory("public/blog");

    Game games[] = {
        {
            "stations", "Stations of the Cross", "The RPG", 
            "Experience the Passion through a deeply immersive tactical RPG engine built from the ground up in C++.",
            "cpp.raylib", "Alpha Demo", "/static/downloads/stations_rpg_demo.zip",
            "HolyForge Originals", 0
        },
        {
            "parables", "Parables of Strategy", "Grand Strategy", 
            "Command the faithful and defend the light in a grand strategy experience where faith is your primary currency.",
            "c11.pure", "Prototype", "#",
            "HolyForge Originals", 0
        },
        {
            "episode-8", "Signal of Redemption", "Episode 8",
            "A fast-paced arena survival game explored in our technical tutorial series.",
            "cpp.sdl2", "Code Review", "#",
            "Code Review", 1
        },
        {
            "episode-10", "Divine Sentinel", "Episode 10",
            "A celestial combat experience showcasing advanced system-level architecture.",
            "cpp.raylib", "Code Review", "#",
            "Code Review", 1
        }
    };
    int num_games = 4;

    // Home Page - Apple Minimalist Style
    char home_content[4096];
    snprintf(home_content, sizeof(home_content),
    "        <section class=\"hero\">\n"
    "            <h1>Forging Faith.</h1>\n"
    "            <p>Low-level engineering. High-level devotion.</p>\n"
    "            <a href=\"/games.html\" class=\"btn primary-gold\">Enter the Forge</a>\n"
    "        </section>\n"
    "        <section class=\"content\">\n"
    "            <div class=\"daily-word\">\n"
    "                <p>\"Whatever you do, work at it with all your heart, as working for the Lord.\"</p>\n"
    "            </div>\n"
    "        </section>\n"
    "        <section class=\"content\" style=\"text-align:center;\">\n"
    "            <h2 style=\"font-size: 40px;\">The Holy C Stack</h2>\n"
    "            <p style=\"color: var(--text-dim); font-size: 19px; max-width: 700px; margin: 20px auto;\">We reject the bloat of modern engines. Our work is built near the metal, honoring the craftsmanship of code as a reflection of divine order.</p>\n"
    "            <div style=\"margin-top: 40px; font-family: monospace; opacity: 0.7; font-size: 14px;\">\n"
    "                <code>while (faith) { code(); devotion(); }</code>\n"
    "            </div>\n"
    "        </section>\n");
    write_page("index.html", "Home", home_content);

    // Games Catalog Page
    char games_list_html[16384] = "        <section class=\"content\">\n            <h1 style=\"font-size: 48px; text-align: center; margin-bottom: 60px;\">The Catalog</h1>\n";
    
    const char* current_series = "";
    int series_open = 0;

    for (int i = 0; i < num_games; i++) {
        if (strcmp(current_series, games[i].series) != 0) {
            if (series_open) strcat(games_list_html, "            </div>\n");
            current_series = games[i].series;
            char series_header[256];
            snprintf(series_header, sizeof(series_header), "            <h2 class=\"series-header\">%s</h2>\n            <div class=\"game-list\">\n", current_series);
            strcat(games_list_html, series_header);
            series_open = 1;
        }

        char season_info[64] = "";
        if (games[i].season > 0) snprintf(season_info, sizeof(season_info), " &bull; Season %d", games[i].season);

        char item[2048];
        snprintf(item, sizeof(item),
        "                <div class=\"game-item\">\n"
        "                    <div class=\"game-content\">\n"
        "                        <div style=\"font-family: monospace; font-size: 11px; color: var(--primary); margin-bottom: 12px; text-transform: uppercase;\">%s%s</div>\n"
        "                        <h3>%s</h3>\n"
        "                        <p>%s</p>\n"
        "                        <div class=\"game-meta\">\n"
        "                            <span class=\"badge\">%s</span>\n"
        "                            <div class=\"game-actions\">\n"
        "                                <a href=\"/play.html?game=%s\" class=\"btn-small\">Play</a>\n"
        "                                <a href=\"/games/%s.html\" class=\"btn-small\" style=\"margin-left: 12px;\">Details</a>\n"
        "                            </div>\n"
        "                        </div>\n"
        "                    </div>\n"
        "                </div>\n", 
        games[i].series, season_info, games[i].title, games[i].description, games[i].tag, games[i].id, games[i].id);
        strcat(games_list_html, item);

        // Detail Page
        char detail[4096];
        snprintf(detail, sizeof(detail),
        "        <section class=\"content\">\n"
        "            <div style=\"text-align: center; margin-bottom: 60px;\">\n"
        "                <div style=\"font-family: monospace; color: var(--primary); font-size: 13px; margin-bottom: 10px;\">%s %s</div>\n"
        "                <h1 style=\"font-size: 48px; margin-bottom: 20px;\">%s</h1>\n"
        "                <span class=\"badge\">%s</span>\n"
        "            </div>\n"
        "            <div style=\"display: grid; grid-template-columns: 1fr 300px; gap: 60px;\">\n"
        "                <div style=\"font-size: 19px; line-height: 1.5; color: var(--text-dim);\">\n"
        "                    <p>%s</p>\n"
        "                    <h3 style=\"color: var(--text); margin-top: 40px;\">Architectural Vision</h3>\n"
        "                    <p>Designed with modular C++ principles to ensure high-performance execution within the WASM sandbox.</p>\n"
        "                </div>\n"
        "                <div class=\"game-item\" style=\"height: fit-content;\">\n"
        "                    <h4 style=\"margin-top: 0; font-family: 'Cinzel'; color: var(--primary);\">Release Info</h4>\n"
        "                    <p style=\"font-size: 13px;\">Status: <strong>%s</strong></p>\n"
        "                    <a href=\"/play.html?game=%s\" class=\"btn primary-gold\" style=\"width:100%%; text-align:center; box-sizing: border-box;\">Launch Module</a>\n"
        "                </div>\n"
        "            </div>\n"
        "            <p style=\"margin-top: 60px; text-align:center;\"><a href=\"/games.html\" class=\"btn-small\">&larr; Back to Catalog</a></p>\n"
        "        </section>\n",
        games[i].series, season_info, games[i].title, games[i].tag, games[i].description, games[i].status, games[i].id);
        char filename[128];
        snprintf(filename, sizeof(filename), "games/%s.html", games[i].id);
        write_page(filename, games[i].title, detail);
    }
    if (series_open) strcat(games_list_html, "            </div>\n");
    strcat(games_list_html, "        </section>\n");
    write_page("games.html", "The Catalog", games_list_html);

    // Minor Pages
    write_page("about.html", "About", "        <section class=\"content\" style=\"text-align:center;\"><h1>The Digital Monastery</h1><p style=\"font-size: 21px; color: var(--text-dim); margin-top: 30px;\">We build for the long haul. We build for the soul.</p></section>");
    write_page("community.html", "Community", "        <section class=\"content\" style=\"text-align:center;\"><h1>The Sanctuary</h1><p style=\"font-size: 21px; color: var(--text-dim); margin-top: 30px;\">A place for shared prayer and collective creation.</p></section>");
    
    // Play Page
    write_page("play.html", "The Forge", 
    "        <section class=\"content\" style=\"max-width: 1200px;\">\n"
    "            <div class=\"play-header\">\n"
    "                <a href=\"/games.html\" class=\"btn-small\" style=\"margin-bottom: 20px; display: inline-block;\">&larr; Back to Catalog</a>\n"
    "                <h1 id=\"game-title\">HolyForge Module</h1>\n"
    "                <div id=\"game-subtitle\" style=\"font-family: monospace; font-size: 13px; color: var(--primary); text-transform: uppercase;\">Initializing...</div>\n"
    "            </div>\n"
    "\n"
    "            <div id=\"game-container\">\n"
    "                <canvas id=\"canvas\" oncontextmenu=\"event.preventDefault()\"></canvas>\n"
    "                <div id=\"loading-overlay\" style=\"position: absolute; top:0; left:0; width:100%%; height:100%%; background: #000; display:flex; flex-direction: column; align-items:center; justify-content:center; color: var(--primary); font-family: 'Cinzel', serif; z-index: 100;\">\n"
    "                    <div style=\"font-size: 1.2rem; margin-bottom: 1rem;\">Forging Engine</div>\n"
    "                    <div style=\"width: 200px; height: 2px; background: #222;\">\n"
    "                        <div id=\"load-bar\" style=\"width: 0%%; height: 100%%; background: var(--primary); transition: width 0.3s ease;\"></div>\n"
    "                    </div>\n"
    "                </div>\n"
    "                <button class=\"fullscreen-btn\" onclick=\"toggleFullscreen()\">Fullscreen</button>\n"
    "            </div>\n"
    "\n"
    "            <div class=\"play-info\">\n"
    "                <div>\n"
    "                    <h3>Description</h3>\n"
    "                    <p id=\"game-description\">Experience high-performance engineering near the metal. This module is built using the Holy C stack, ensuring maximum efficiency and divine structural integrity.</p>\n"
    "                </div>\n"
    "                <div>\n"
    "                    <h3>Technical Stack</h3>\n"
    "                    <p id=\"game-tech\">WebAssembly (WASM) &bull; C++17 &bull; SDL2/Raylib Hardware Abstraction</p>\n"
    "                    <h3 style=\"margin-top: 30px;\">Status</h3>\n"
    "                    <p id=\"game-status\">Active Sandbox</p>\n"
    "                </div>\n"
    "            </div>\n"
    "\n"
    "            <script>\n"
    "                // Prevent spacebar scrolling\n"
    "                window.addEventListener('keydown', function(e) {\n"
    "                    if(e.code === 'Space') e.preventDefault();\n"
    "                });\n"
    "                window.addEventListener('unhandledrejection', function(event) { if (event.reason === 'unwind') event.preventDefault(); });\n"    "                function toggleFullscreen() {\n"
    "                    const c = document.getElementById('game-container');\n"
    "                    if (!document.fullscreenElement) c.requestFullscreen(); else document.exitFullscreen();\n"
    "                }\n"
    "                \n"
    "                const urlParams = new URLSearchParams(window.location.search);\n"
    "                const gameId = urlParams.get('game') || 'stations';\n"
    "                \n"
    "                const gameConfigs = {\n"
    "                    'stations': { \n"
    "                        title: 'Stations of the Cross', \n"
    "                        subtitle: 'HolyForge Originals', \n"
    "                        description: 'A soul-stirring journey through the streets of Jerusalem. Experience the Passion through a deeply immersive tactical RPG engine built from the ground up in C++.',\n"
    "                        tech: 'C++ &bull; Raylib &bull; WebGL 2.0',\n"
    "                        status: 'Alpha Demo',\n"
    "                        script: 'community.js', loader: 'createCommunityModule', entry: '_start_game' \n"
    "                    },\n"
    "                    'parables': { \n"
    "                        title: 'Parables of Strategy', \n"
    "                        subtitle: 'HolyForge Originals', \n"
    "                        description: 'Command the faithful and defend the light in a grand strategy experience where faith is your strongest resource.',\n"
    "                        tech: 'Pure C11 &bull; Software Rasterization',\n"
    "                        status: 'Prototype',\n"
    "                        script: 'parables.js', loader: 'createParablesModule', entry: '_start_parables' \n"
    "                    },\n"
    "                    'episode-8': { \n"
    "                        title: 'Signal of Redemption', \n"
    "                        subtitle: 'Code Review &bull; Season 1', \n"
    "                        description: 'A fast-paced arena survival game explored in our technical tutorial series. This episode focuses on advanced C++ entity management and SDL2 rendering.',\n"
    "                        tech: 'C++17 &bull; SDL2 &bull; OOP Design',\n"
    "                        status: 'Tutorial Complete',\n"
    "                        script: 'episode8.js', loader: 'createEpisode8Module', entry: 'main' \n"
    "                    },\n"
    "                    'episode-10': { \n"
    "                        title: 'Divine Sentinel', \n"
    "                        subtitle: 'Code Review &bull; Season 1', \n"
    "                        description: 'A celestial combat experience showcasing advanced system-level architecture and 3D rendering principles within the Raylib framework.',\n"
    "                        tech: 'C++ &bull; Raylib &bull; WebAssembly',\n"
    "                        status: 'Final Episode',\n"
    "                        script: 'episode10.js', loader: 'createEpisode10Module', entry: 'main' \n"
    "                    }\n"
    "                };\n"
    "                \n"
    "                const config = gameConfigs[gameId] || gameConfigs['stations'];\n"
    "                \n"
    "                // Update page content\n"
    "                document.getElementById('game-title').innerText = config.title;\n"
    "                document.getElementById('game-subtitle').innerHTML = config.subtitle;\n"
    "                document.getElementById('game-description').innerText = config.description;\n"
    "                document.getElementById('game-tech').innerHTML = config.tech;\n"
    "                document.getElementById('game-status').innerText = config.status;\n"
    "\n"
    "                const script = document.createElement('script');\n"
    "                script.src = '/static/js/' + config.script + '?v=' + Date.now();\n"
    "                script.onload = () => {\n"
    "                    const Module = {\n"
    "                        canvas: document.getElementById('canvas'),\n"
    "                        noInitialRun: true,\n"
    "                        onRuntimeInitialized: () => {\n"    "                            document.getElementById('load-bar').style.width = '100%%';\n"
    "                            setTimeout(() => document.getElementById('loading-overlay').style.display = 'none', 500);\n"
    "                        }\n"
    "                    };\n"
    "                    window[config.loader](Module).then(m => {\n"
    "                        if (config.entry === 'main') {\n"
    "                             if (m.callMain) m.callMain();\n"
    "                             else if (m._main) m._main();\n"
    "                        } else if (m[config.entry]) {\n"
    "                            try {\n"
    "                                m[config.entry]();\n"
    "                            } catch (e) {\n"
    "                                if (e !== 'unwind') console.error(e);\n"
    "                            }\n"
    "                        }\n"
    "                    });\n"    "                };\n"
    "                document.body.appendChild(script);\n"
    "            </script>\n"
    "        </section>\n");

    return 0;
}