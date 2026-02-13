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

typedef struct {
    const char *slug;
    const char *title;
    const char *date;
    const char *excerpt;
    const char *content;
} Post;

const char *HTML_HEADER = 
"<!DOCTYPE html>\n"
"<html lang=\"en\">\n"
"<head>\n"
"    <meta charset=\"UTF-8\">\n"
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
"    <title>%s | HolyForge Games</title>\n"
"    <meta name=\"description\" content=\"%s\">\n"
"    \n"
"    <!-- Open Graph / Facebook -->\n"
"    <meta property=\"og:type\" content=\"website\">\n"
"    <meta property=\"og:title\" content=\"%s | HolyForge Games\">\n"
"    <meta property=\"og:description\" content=\"%s\">\n"
"    <meta property=\"og:image\" content=\"https://holyforge.games/static/images/og-image.jpg\">\n"
"\n"
"    <!-- Twitter -->\n"
"    <meta property=\"twitter:card\" content=\"summary_large_image\">\n"
"    <meta property=\"twitter:title\" content=\"%s | HolyForge Games\">\n"
"    <meta property=\"twitter:description\" content=\"%s\">\n"
"\n"
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
"    <div class=\"aura-container\"><div class=\"aura\"></div></div>\n"
"    <header>\n"
"        <nav>\n"
"            <a href=\"/\" class=\"logo\">HolyForge</a>\n"
"            <div class=\"links\">\n"
"                <a href=\"/games\">Games</a>\n"
"                <a href=\"/journal\">Journal</a>\n"
"                <a href=\"/ledger\">Ledger</a>\n"
"                <a href=\"/sanctuary\">Sanctuary</a>\n"
"                <a href=\"/about\">About</a>\n"
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
"                <p style=\"opacity: 0.6;\">v2.3.1 &bull; Industry Standard URLs</p>\n"
"            </div>\n"
"        </div>\n"
"    </footer>\n"
"    <div id=\"studio-terminal\">\n"
"        <div class=\"terminal-header\"><span>LOG_MONITOR</span><span onclick=\"this.parentElement.parentElement.style.display='none'\" style=\"cursor:pointer\">[X]</span></div>\n"
"        <div id=\"terminal-body\"></div>\n"
"    </div>\n"
"    <script>\n"
"        function toggleTheme() {\n"
"            const html = document.documentElement;\n"
"            const currentTheme = html.getAttribute('data-theme');\n"
"            const newTheme = currentTheme === 'dark' ? 'light' : 'dark';\n"
"            html.setAttribute('data-theme', newTheme);\n"
"            localStorage.setItem('theme', newTheme);\n"
"        }\n"
"        function forgeLog(msg) {\n"
"            const body = document.getElementById('terminal-body');\n"
"            if (!body) return;\n"
"            const line = document.createElement('div');\n"
"            line.className = 'terminal-line';\n"
"            line.innerHTML = `<span>[${new Date().toLocaleTimeString()}]</span> ${msg}`;\n"
"            body.appendChild(line);\n"
"            if (body.children.length > 5) body.removeChild(body.firstChild);\n"
"            document.getElementById('studio-terminal').style.display = 'block';\n"
"        }\n"
"        setTimeout(() => forgeLog('FORGE_READY: Clean URLs enabled.'), 1000);\n"
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

void write_page_ext(const char *filename, const char *title, const char *desc, const char *content) {
    char path[256];
    snprintf(path, sizeof(path), "public/%s", filename);
    
    char tmp[256];
    strcpy(tmp, path);
    char *last_slash = strrchr(tmp, '/');
    if (last_slash) {
        *last_slash = '\0';
        char build_dir[256] = "";
        char *path_parts = strdup(tmp);
        char *token = strtok(path_parts, "/");
        while (token != NULL) {
            if (strlen(build_dir) > 0) strcat(build_dir, "/");
            strcat(build_dir, token);
            ensure_directory(build_dir);
            token = strtok(NULL, "/");
        }
        free(path_parts);
    }

    FILE *f = fopen(path, "w");
    if (!f) { perror("Error opening file"); return; }
    
    fprintf(f, HTML_HEADER, title, desc, title, desc, title, desc);
    fprintf(f, "%s", content);
    fprintf(f, "%s", HTML_FOOTER);
    fclose(f);
    printf("Generated: %s\n", path);
}

int main() {
    ensure_directory("public");

    Game games[] = {
        {
            "stations", "Stations of the Cross", "The RPG", 
            "Experience the Passion through a deeply immersive tactical RPG engine built from the ground up in C++.",
            "cpp.raylib", "Alpha Demo", "/static/downloads/stations_rpg_demo.zip",
            "HolyForge Originals", 0
        },
        {
            "parables", "Parables of Strategy", "Grand Strategy", 
            "Command the faithful and defend the light in a grand strategy experience where faith is your strongest resource.",
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

    Post posts[] = {
        {
            "the-digital-cathedral", "The Digital Cathedral", "February 14, 2026",
            "Building structures of light and logic that stand the test of time.",
            "<p>When the great cathedrals of Europe were built, they were designed to be sermons in stone. Every arch, every window, and every statue pointed toward the heavens.</p><p>In the 21st century, we are building cathedrals of code. A well-written C program is like a Gothic arch—perfectly balanced, efficient, and beautiful in its structural necessity.</p>"
        },
        {
            "the-beauty-of-c", "The Aesthetic of Manual Memory", "February 13, 2026",
            "How the discipline of C allocation mirrors the intentionality of creation.",
            "<p>In C, when you call <code>malloc()</code>, you are making a claim on the physical reality of the machine. You are requesting a specific portion of the universe to hold your data. When you call <code>free()</code>, you are returning that resource with gratitude.</p><p>This cycle of stewardship—requesting, using, and returning—is a fundamental aspect of the HolyForge philosophy.</p>"
        }
    };
    int num_posts = 2;

    // Home Page
    write_page_ext("index.html", "Forging Faith", "High-performance C-powered gaming experiences built for the glory of God.", 
    "        <section class=\"hero\">\n"
    "            <h1>Forging Faith.</h1>\n"
    "            <p>Low-level engineering. High-level devotion.</p>\n"
    "            <div style=\"display: flex; gap: 20px; justify-content: center;\">\n"
    "                <a href=\"/games\" class=\"btn\">Enter the Forge</a>\n"
    "                <a href=\"/ledger\" class=\"btn\" style=\"background: var(--text); color: var(--bg) !important;\">Study the Ledger</a>\n"
    "            </div>\n"
    "        </section>\n"
    "        <section class=\"content\" style=\"border-top: 1px solid var(--border);\">\n"
    "            <div class=\"daily-word\">\n"
    "                <p>\"Whatever you do, work at it with all your heart, as working for the Lord.\"</p>\n"
    "            </div>\n"
    "        </section>\n");

    // Games Catalog
    char games_list_html[16384] = "        <section class=\"content\">\n            <h1 style=\"font-size: 56px; text-align: center; margin-bottom: 80px;\">The Catalog</h1>\n";
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
        "                <div class=\"game-item\" onmouseover=\"forgeLog('ACCESSING_MODULE: %s')\">\n"
        "                    <div class=\"game-content\">\n"
        "                        <div style=\"font-family: monospace; font-size: 11px; color: var(--primary); margin-bottom: 12px; text-transform: uppercase;\">%s%s</div>\n"
        "                        <h3>%s</h3>\n"
        "                        <p>%s</p>\n"
        "                        <div class=\"game-meta\">\n"
        "                            <span class=\"badge\">%s</span>\n"
        "                            <div class=\"game-actions\">\n"
        "                                <a href=\"/play/%s\" class=\"btn-small\">Launch</a>\n"
        "                                <a href=\"/games/%s\" class=\"btn-small\" style=\"margin-left: 15px;\">Details</a>\n"
        "                            </div>\n"
        "                        </div>\n"
        "                    </div>\n"
        "                </div>\n", 
        games[i].title, games[i].series, season_info, games[i].title, games[i].description, games[i].tag, games[i].id, games[i].id);
        strcat(games_list_html, item);

        // Detail Page
        char detail[4096];
        snprintf(detail, sizeof(detail),
        "        <section class=\"content\">\n"
        "            <div style=\"text-align: center; margin-bottom: 80px;\">\n"
        "                <div style=\"font-family: monospace; color: var(--primary); font-size: 13px; margin-bottom: 15px;\">%s %s</div>\n"
        "                <h1 style=\"font-size: 64px; margin-bottom: 20px;\">%s</h1>\n"
        "                <span class=\"badge\">%s</span>\n"
        "            </div>\n"
        "            <div style=\"display: grid; grid-template-columns: 1fr 320px; gap: 80px;\">\n"
        "                <div style=\"font-size: 21px; line-height: 1.5; color: var(--text-dim);\">\n"
        "                    <p>%s</p>\n"
        "                    <h3 style=\"color: var(--text); margin-top: 50px;\">Architectural Vision</h3>\n"
        "                    <p>Designed with modular C++ principles to ensure high-performance execution within the WASM sandbox. This module represents a pilgrimage into the heart of the machine.</p>\n"
        "                </div>\n"
        "                <div class=\"play-sidebar\" style=\"height: fit-content;\">\n"
        "                    <h4 style=\"margin-top: 0; font-family: 'Cinzel'; color: var(--primary);\">Release Info</h4>\n"
        "                    <p style=\"font-size: 14px;\">Status: <strong>%s</strong></p>\n"
        "                    <a href=\"/play/%s\" class=\"btn\" style=\"width:100%%; text-align:center; box-sizing: border-box; background: var(--text); color: var(--bg) !important;\">Launch Module</a>\n"
        "                </div>\n"
        "            </div>\n"
        "            <p style=\"margin-top: 80px; text-align:center;\"><a href=\"/games\" class=\"btn-small\">&larr; Back to Catalog</a></p>\n"
        "        </section>\n",
        games[i].series, season_info, games[i].title, games[i].tag, games[i].description, games[i].status, games[i].id);
        char detail_filename[128];
        snprintf(detail_filename, sizeof(detail_filename), "games/%s/index.html", games[i].id);
        write_page_ext(detail_filename, games[i].title, games[i].description, detail);

        // Individual Play Page (Clean URL)
        char play_pg[8192];
        const char *loader = "createCommunityModule";
        const char *entry = "_start_game";
        const char *script = "community.js";
        const char *ctrls = "<!-- Dynamic -->";
        
        if (strcmp(games[i].id, "parables") == 0) { loader = "createParablesModule"; entry = "_start_parables"; script = "parables.js"; ctrls = "<div class='control-item'><span>Orbit</span><span class='control-key'>Arrows</span></div>"; }
        else if (strcmp(games[i].id, "episode-8") == 0) { loader = "createEpisode8Module"; entry = "main"; script = "episode8.js"; ctrls = "<div class='control-item'><span>Move</span><span class='control-key'>WASD</span></div><div class='control-item'><span>Shoot</span><span class='control-key'>Mouse</span></div>"; }
        else if (strcmp(games[i].id, "episode-10") == 0) { loader = "createEpisode10Module"; entry = "main"; script = "episode10.js"; ctrls = "<div class='control-item'><span>Move</span><span class='control-key'>WASD</span></div><div class='control-item'><span>Jump</span><span class='control-key'>Space</span></div>"; }
        else { ctrls = "<div class='control-item'><span>Move</span><span class='control-key'>Arrows</span></div><div class='control-item'><span>Interact</span><span class='control-key'>Space</span></div>"; }

        snprintf(play_pg, sizeof(play_pg),
        "        <section class=\"content\" style=\"max-width: 1200px;\">\n"
        "            <div class=\"play-header\">\n"
        "                <a href=\"/games\" class=\"btn-small\" style=\"margin-bottom: 20px; display: inline-block;\">&larr; Back to Catalog</a>\n"
        "                <h1>%s</h1>\n"
        "                <div style=\"font-family: monospace; font-size: 13px; color: var(--primary); text-transform: uppercase;\">%s%s</div>\n"
        "            </div>\n"
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
        "            <div class=\"play-info\">\n"
        "                <div>\n"
        "                    <h3>Lore & Context</h3>\n"
        "                    <p>%s</p>\n"
        "                    <h3 style=\"margin-top: 40px;\">Technical Stack</h3>\n"
        "                    <p>%s &bull; WASM</p>\n"
        "                </div>\n"
        "                <div class=\"play-sidebar\">\n"
        "                    <h4 style=\"font-family: 'Cinzel'; color: var(--primary); margin-bottom: 20px;\">How to Play</h4>\n"
        "                    <div>%s</div>\n"
        "                    <h4 style=\"font-family: 'Cinzel'; color: var(--primary); margin-top: 40px; margin-bottom: 10px;\">Status</h4>\n"
        "                    <p style=\"font-size: 14px;\">%s</p>\n"
        "                </div>\n"
        "            </div>\n"
        "            <script>\n"
        "                window.addEventListener('unhandledrejection', function(event) { if (event.reason === 'unwind') event.preventDefault(); });\n"
        "                window.addEventListener('keydown', function(e) { if(e.code === 'Space' && e.target === document.body) e.preventDefault(); });\n"
        "                function toggleFullscreen() {\n"
        "                    const c = document.getElementById('game-container');\n"
        "                    if (!document.fullscreenElement) c.requestFullscreen(); else document.exitFullscreen();\n"
        "                }\n"
        "                const script = document.createElement('script');\n"
        "                script.src = '/static/js/%s?v=' + Date.now();\n"
        "                script.onload = () => {\n"
        "                    const Module = { canvas: document.getElementById('canvas'), noInitialRun: true,\n"
        "                        onRuntimeInitialized: () => {\n"
        "                            document.getElementById('load-bar').style.width = '100%%';\n"
        "                            setTimeout(() => document.getElementById('loading-overlay').style.display = 'none', 500);\n"
        "                            forgeLog('RUNTIME_INIT: %s');\n"
        "                        }\n"
        "                    };\n"
        "                    window['%s'](Module).then(m => {\n"
        "                        if ('%s' === 'main') { if (m.callMain) m.callMain(); else if (m._main) m._main(); }\n"
        "                        else if (m['%s']) m['%s']();\n"
        "                    });\n"
        "                };\n"
        "                document.body.appendChild(script);\n"
        "            </script>\n"
        "        </section>\n",
        games[i].title, games[i].series, season_info, games[i].description, games[i].tag, ctrls, games[i].status, 
        script, games[i].title, loader, entry, entry, entry);
        char play_filename[128];
        snprintf(play_filename, sizeof(play_filename), "play/%s/index.html", games[i].id);
        write_page_ext(play_filename, games[i].title, games[i].description, play_pg);
    }
    if (series_open) strcat(games_list_html, "            </div>\n");
    strcat(games_list_html, "        </section>\n");
    write_page_ext("games/index.html", "The Catalog", "Browse the collection of HolyForge modules.", games_list_html);

    // Journal
    char journal_html[8192] = "        <section class=\"content\">\n            <h1 style=\"font-size: 56px; text-align: center; margin-bottom: 80px;\">The Journal</h1>\n            <div class=\"game-list\">\n";
    for (int i = 0; i < num_posts; i++) {
        char item[1024];
        snprintf(item, sizeof(item),
        "                <div class=\"game-item\" onmouseover=\"forgeLog('READING_ENTRY: %s')\">\n"
        "                    <div class=\"game-content\">\n"
        "                        <div style=\"font-family: monospace; font-size: 11px; color: var(--primary); margin-bottom: 12px;\">%s</div>\n"
        "                        <h3>%s</h3>\n"
        "                        <p>%s</p>\n"
        "                        <div class=\"game-meta\">\n"
        "                            <a href=\"/journal/%s\" class=\"btn-small\">Read Entry &rarr;</a>\n"
        "                        </div>\n"
        "                    </div>\n"
        "                </div>\n",
        posts[i].title, posts[i].date, posts[i].title, posts[i].excerpt, posts[i].slug);
        strcat(journal_html, item);

        char p_content[4096];
        snprintf(p_content, sizeof(p_content),
        "        <article class=\"content\" style=\"max-width: 680px;\">\n"
        "            <div style=\"text-align: center; margin-bottom: 60px;\">\n"
        "                <div style=\"font-family: monospace; color: var(--primary); font-size: 13px;\">%s</div>\n"
        "                <h1 style=\"font-size: 56px; margin-top: 15px; line-height: 1.1;\">%s</h1>\n"
        "            </div>\n"
        "            <div style=\"font-size: 21px; line-height: 1.6; color: var(--text-dim);\">\n"
        "                %s\n"
        "            </div>\n"
        "            <p style=\"margin-top: 80px; text-align:center;\"><a href=\"/journal\" class=\"btn-small\">&larr; Back to Journal</a></p>\n"
        "        </article>\n",
        posts[i].date, posts[i].title, posts[i].content);
        char p_filename[128];
        snprintf(p_filename, sizeof(p_filename), "journal/%s/index.html", posts[i].slug);
        write_page_ext(p_filename, posts[i].title, posts[i].excerpt, p_content);
    }
    strcat(journal_html, "            </div>\n        </section>\n");
    write_page_ext("journal/index.html", "The Journal", "Reflections from the Digital Monastery.", journal_html);

    // Ledger
    write_page_ext("ledger/index.html", "Technical Ledger", "Code snippets and patterns.",
    "        <section class=\"content\">\n"
    "            <h1 style=\"font-size: 56px; text-align: center; margin-bottom: 80px;\">Technical Ledger</h1>\n"
    "            <div class=\"review-card\">\n"
    "                <div style=\"font-family: monospace; color: var(--primary); font-size: 11px; margin-bottom: 10px;\">SYSTEM_HEARTBEAT</div>\n"
    "                <h3>The Main Loop</h3>\n"
    "                <pre><code>void main_loop() {\n    global_game->update();\n    global_game->render();\n}</code></pre>\n"
    "            </div>\n"
    "        </section>\n");

    // Sanctuary
    write_page_ext("sanctuary/index.html", "The Sanctuary", "Communal prayer and reflection.",
    "        <section class=\"content\">\n"
    "            <h1 style=\"font-size: 56px; text-align: center; margin-bottom: 80px;\">The Sanctuary</h1>\n"
    "            <div class=\"daily-word\" style=\"text-align: left; padding: 60px;\">\n"
    "                <h2 style=\"margin-top: 0; font-size: 32px;\">Votive Stand</h2>\n"
    "                <p style=\"font-size: 19px; color: var(--text-dim);\">Light a virtual candle.</p>\n"
    "                <div id=\"votive-stand\" class=\"votive-stand\"></div>\n"
    "                <button onclick=\"lightCandle(); forgeLog('SANCTUARY: Candle lit.')\" class=\"btn\" style=\"background: var(--text); color: var(--bg) !important; margin-top: 40px;\">Light a Candle</button>\n"
    "            </div>\n"
    "        </section>\n"
    "        <script src=\"/static/js/community.js\"></script>\n"
    "        <script>\n"
    "            function lightCandle() {\n"
    "                const s = document.getElementById('votive-stand');\n"
    "                const c = document.createElement('div');\n"
    "                c.className = 'candle'; c.innerHTML = '<div class=\"flame\"></div>';\n"
    "                s.appendChild(c);\n"
    "            }\n"
    "        </script>\n");

    // About
    write_page_ext("about/index.html", "About Us", "The manifesto of HolyForge.", 
    "        <section class=\"manifesto\">\n"
    "            <h1 style=\"font-size: 56px; margin-bottom: 60px;\">The Manifesto.</h1>\n"
    "            <p>Every line of code is an offering.</p>\n"
    "            <p style=\"font-family: 'Cinzel'; color: var(--primary); margin-top: 80px; font-size: 24px;\">Ad Maiorem Dei Gloriam.</p>\n"
    "        </section>\n");

    return 0;
}
