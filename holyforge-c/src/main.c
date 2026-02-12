#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

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
"        // Immediate theme initialization to prevent flash\n"
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
"                <a href=\"/\">Home</a>\n"
"                <a href=\"/games.html\">Games</a>\n"
"                <a href=\"/blog.html\">Blog</a>\n"
"                <a href=\"/community.html\">Community</a>\n"
"                <a href=\"/about.html\">About</a>\n"
"                <button onclick=\"toggleTheme()\" class=\"theme-toggle\" id=\"theme-btn\">Theme</button>\n"
"            </div>\n"
"        </nav>\n"
"    </header>\n"
"    <main>\n";

const char *HTML_FOOTER = 
"    </main>\n"
"    <footer>\n"
"        <p>&copy; 2026 HolyForge Games. Ad Maiorem Dei Gloriam.</p>\n"
"        <p class=\"trademark-notice\">HolyForge Games is a trademark of HolyForge Studios. Trademark coming soon.</p>\n"
"    </footer>\n"
"    <script>\n"
"        function toggleTheme() {\n"
"            const html = document.documentElement;\n"
"            const currentTheme = html.getAttribute('data-theme');\n"
"            const newTheme = currentTheme === 'dark' ? 'light' : 'dark';\n"
"            \n"
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
    
    // Simple logic to ensure subdirectories exist
    char *last_slash = strrchr(path, '/');
    if (last_slash) {
        *last_slash = '\0';
        ensure_directory(path);
        *last_slash = '/';
    }

    FILE *f = fopen(path, "w");
    if (!f) {
        perror("Error opening file");
        return;
    }
    
    fprintf(f, HTML_HEADER, title);
    fprintf(f, "%s", content);
    fprintf(f, "%s", HTML_FOOTER);
    
    fclose(f);
    printf("Generated: %s\n", path);
}

int main() {
    ensure_directory("public");
    ensure_directory("public/blog");

            // Home Page

            const char *home_content = 

            "        <section class=\"hero\">\n"

            "            <h1>Forging Faith in Digital Worlds</h1>\n"

            "            <p>High-performance C-powered gaming experiences built for the glory of God.</p>\n"

            "            <a href=\"/games.html\" class=\"btn\">Enter the Forge</a>\n"

            "        </section>\n"

            "        <section class=\"content\">\n"

            "            <h2>Latest News</h2>\n"

            "            <div class=\"blog-list\">\n"

            "                <article class=\"blog-item\" style=\"border-bottom: none;\">\n"

            "                    <span class=\"meta\">February 14, 2026</span>\n"

            "                    <h3>Divine Light Theme Launched</h3>\n"

            "                    <p>We have updated the forge with a new 'Divine Light' theme to celebrate the purity of our mission. You can toggle between Light and Dark modes using the button in the navigation bar.</p>\n"

            "                </article>\n"

            "            </div>\n"

            "        </section>\n"

            "        <section class=\"mission\">\n"

        "            <div class=\"content\">\n"

        "                <h2>Our Divine Mission</h2>\n"

        "                <p>\"Whatever you do, work at it with all your heart, as working for the Lord.\"</p>\n"

        "                <p style=\"margin-top: 2rem; font-style: normal; font-size: 1.1rem;\">At HolyForge Games, we believe that software architecture is a reflection of the Creator's order. We use the C language to achieve unparalleled precision, performance, and craftsmanship, creating worlds that inspire virtue and contemplation.</p>\n"

        "            </div>\n"

        "        </section>\n";

        write_page("index.html", "Home", home_content);

    

        // About Page

        const char *about_content = 

        "        <section class=\"content\">\n"

        "            <h2>The Studio of the Cross</h2>\n"

        "            <p>HolyForge Games is a C-focused studio dedicated to creating games that explore the depths of Catholic theology and morality.</p>\n"

        "            <p>Founded on the principles of the 'Holy C' stack, we reject the bloat of modern engines in favor of the purity and discipline of low-level programming. Every line of code is an offering.</p>\n"

        "            <h3>Our Philosophy</h3>\n"

        "            <ul>\n"

        "                <li><strong>Discipline:</strong> Manual memory management as a spiritual exercise.</li>\n"

        "                <li><strong>Performance:</strong> Respecting the user's hardware as a stewardship of resources.</li>\n"

        "                <li><strong>Narrative:</strong> Storytelling that points toward the Eternal Truth.</li>\n"

        "            </ul>\n"

        "            <h3>The Holy C Stack</h3>\n"

        "            <p>We leverage the same tools that built the modern world: C11, C++17, SDL2, and OpenGL. By compiling these native technologies to WebAssembly, we bring desktop-grade performance to the browser without the weight of modern engines.</p>\n"

        "            <h3>The Team</h3>\n"

        "            <p>HolyForge is a collaborative of developers, artists, and theologians united by a shared vision. We operate as a digital monastery—focused, disciplined, and dedicated to our craft.</p>\n"

        "            <p style=\"margin-top: 4rem; font-size: 0.8rem; opacity: 0.5;\">HolyForge Games is a trademark of HolyForge Studios. Trademark coming soon.</p>\n"

        "        </section>\n";

        write_page("about.html", "About Us", about_content);

    

        // Games Page

        const char *games_content = 

        "        <section class=\"content\">\n"

        "            <h2>The Holy Catalog</h2>\n"

        "            <div class=\"game-list\">\n"

        "                <div class=\"game-item\">\n"

        "                    <div class=\"game-content\">\n"

        "                        <h3>Stations of the Cross: The RPG</h3>\n"

        "                        <p>A soul-stirring journey through the streets of Jerusalem. Experience the Passion through a deeply immersive tactical RPG engine built from scratch in C++.</p>\n"

        "                        <div class=\"game-meta\">\n"

        "                            <span class=\"badge\">C++ / Raylib</span>\n"

        "                            <div class=\"game-actions\">\n"

        "                                <a href=\"/play.html?game=stations\" class=\"btn-small\">Play Online</a>\n"

        "                                <a href=\"/static/downloads/stations_rpg_demo.zip\" class=\"btn-small secondary\">Download</a>\n"

        "                            </div>\n"

        "                        </div>\n"

        "                    </div>\n"

        "                </div>\n"

        "                <div class=\"game-item\">\n"

        "                    <div class=\"game-content\">\n"

        "                        <h3>Parables of Strategy</h3>\n"

        "                        <p>A grand strategy game where faith is your strongest resource. Manage dioceses, build cathedrals, and defend the faith against the tides of time.</p>\n"

        "                        <div class=\"game-meta\">\n"

        "                            <span class=\"badge\">Pure C</span>\n"

        "                            <div class=\"game-actions\">\n"

        "                                <a href=\"/play.html?game=parables\" class=\"btn-small\">Play Online</a>\n"

        "                                <a href=\"#\" class=\"btn-small secondary\">Download</a>\n"

        "                            </div>\n"

        "                        </div>\n"

        "                    </div>\n"

        "                </div>\n"

        "                <div class=\"game-item\">\n"

        "                    <div class=\"game-content\">\n"

        "                        <h3>Desert Fathers: Survival</h3>\n"

        "                        <p>Survival simulation in the 4th-century Egyptian desert. Battle the elements and spiritual temptations in this rigorous C11 experience.</p>\n"

        "                        <div class=\"game-meta\">\n"

        "                            <span class=\"badge\">C11 / OpenGL</span>\n"

        "                            <a href=\"#\" class=\"btn-small\">Coming Soon</a>\n"

        "                        </div>\n"

        "                    </div>\n"

        "                </div>\n"

        "                <div class=\"game-item\">\n"

        "                    <div class=\"game-content\">\n"

        "                        <h3>The Divine Comedy: Descent</h3>\n"

        "                        <p>An atmospheric 3D dungeon crawler through the circles of the Inferno, crafted with a custom software renderer to honor the classical era of gaming.</p>\n"

        "                        <div class=\"game-meta\">\n"

        "                            <span class=\"badge\">C / Software Rendered</span>\n"

        "                            <a href=\"#\" class=\"btn-small\">In Dev</a>\n"

        "                        </div>\n"

        "                    </div>\n"

        "                </div>\n"

        "            </div>\n"

        "        </section>\n";

        write_page("games.html", "Game Catalog", games_content);

    

    // Blog Page
    const char *blog_content = 
    "        <section class=\"content\">\n"
    "            <h2>Journal of the Forge</h2>\n"
    "            <div class=\"blog-list\">\n"
    "                <article class=\"blog-item\">\n"
    "                    <h3><a href=\"/blog/the-digital-cathedral.html\">The Digital Cathedral</a></h3>\n"
    "                    <p class=\"meta\">Published on February 14, 2026</p>\n"
    "                    <p>Building structures of light and logic that stand the test of time.</p>\n"
    "                </article>\n"
    "                <article class=\"blog-item\">\n"
    "                    <h3><a href=\"/blog/the-beauty-of-c.html\">The Aesthetic of Manual Memory</a></h3>\n"
    "                    <p class=\"meta\">Published on February 13, 2026</p>\n"
    "                    <p>How the discipline of C allocation mirrors the intentionality of creation.</p>\n"
    "                </article>\n"
    "                <article class=\"blog-item\">\n"
    "                    <h3><a href=\"/blog/first-post.html\">The Philosophy of Holy Code</a></h3>\n"
    "                    <p class=\"meta\">Published on February 12, 2026</p>\n"
    "                    <p>Why we use C to build games that honor the Creator.</p>\n"
    "                </article>\n"
    "            </div>\n"
    "        </section>\n";
    write_page("blog.html", "Blog", blog_content);

    // Third Blog Post
    const char *third_post_content = 
    "        <section class=\"content\">\n"
    "            <article class=\"blog-post\">\n"
    "                <h2>The Digital Cathedral</h2>\n"
    "                <p class=\"meta\">Published on February 14, 2026</p>\n"
    "                <p>When the great cathedrals of Europe were built, they were designed to be sermons in stone. Every arch, every window, and every statue pointed toward the heavens.</p>\n"
    "                <p>In the 21st century, we are building cathedrals of code. A well-written C program is like a Gothic arch—perfectly balanced, efficient, and beautiful in its structural necessity. We believe that software should not just be 'content,' but a sanctuary where users can find peace, beauty, and truth.</p>\n"
    "                <p>Our commitment to C is a commitment to longevity. While modern frameworks crumble in years, a pure C game can run for decades. We build for the long haul. We build for the soul.</p>\n"
    "                <a href=\"/blog.html\" class=\"btn-small\">Back to Blog</a>\n"
    "            </article>\n"
    "        </section>\n";
    write_page("blog/the-digital-cathedral.html", "The Digital Cathedral", third_post_content);

    // Second Blog Post
    const char *second_post_content = 
    "        <section class=\"content\">\n"
    "            <article class=\"blog-post\">\n"
    "                <h2>The Aesthetic of Manual Memory</h2>\n"
    "                <p class=\"meta\">Published on February 13, 2026</p>\n"
    "                <p>Modern game development has become a layer-cake of abstractions. While garbage collection and managed languages offer convenience, they distance the creator from the medium.</p>\n"
    "                <p>In C, when you call <code>malloc()</code>, you are making a claim on the physical reality of the machine. You are requesting a specific portion of the universe to hold your data. When you call <code>free()</code>, you are returning that resource with gratitude.</p>\n"
    "                <p>This cycle of stewardship—requesting, using, and returning—is a fundamental aspect of the HolyForge philosophy. We believe that by being close to the metal, we are closer to the truth of the machine, and by extension, the logic of the Logos.</p>\n"
    "                <a href=\"/blog.html\" class=\"btn-small\">Back to Blog</a>\n"
    "            </article>\n"
    "        </section>\n";
    write_page("blog/the-beauty-of-c.html", "The Aesthetic of Manual Memory", second_post_content);

    // Community Page
    const char *community_content = 
    "        <section class=\"content\">\n"
    "            <h2>Prayer Wall</h2>\n"
    "            <p>Leave a prayer request. Our C-powered WASM engine will process it with the utmost efficiency.</p>\n"
    "            \n"
    "            <div class=\"prayer-form\">\n"
    "                <input type=\"text\" id=\"prayer-name\" placeholder=\"Your Name (optional)\" class=\"input-field\">\n"
    "                <textarea id=\"prayer-intention\" placeholder=\"Your Intention\" class=\"input-field\"></textarea>\n"
    "                <button onclick=\"addPrayer()\" class=\"btn\">Offer Prayer</button>\n"
    "            </div>\n"
    "            \n"
    "            <div id=\"prayer-list\" class=\"prayer-list\">\n"
    "                <!-- Prayers will be added here via WASM -->\n"
    "            </div>\n"
    "        </section>\n"
    "        <script src=\"/static/js/community.js\"></script>\n"
    "        <script>\n"
    "            let communityModule;\n"
    "            createCommunityModule().then(module => {\n"
    "                communityModule = module;\n"
    "                console.log('WASM Community Module Loaded');\n"
    "            });\n"
    "\n"
    "            function addPrayer() {\n"
    "                const name = document.getElementById('prayer-name').value || 'Anonymous';\n"
    "                const intention = document.getElementById('prayer-intention').value;\n"
    "                \n"
    "                if (!intention) {\n"
    "                    alert('Please enter an intention.');\n"
    "                    return;\n"
    "                }\n"
    "                \n"
    "                // Call the WASM function via cwrap\n"
    "                const formatPrayer = communityModule.cwrap('format_prayer', 'string', ['string', 'string']);\n"
    "                const html = formatPrayer(name, intention);\n"
    "                \n"
    "                const list = document.getElementById('prayer-list');\n"
    "                list.innerHTML = html + list.innerHTML;\n"
    "                \n"
    "                document.getElementById('prayer-intention').value = '';\n"
    "            }\n"
    "        </script>\n";
    write_page("community.html", "Community", community_content);

    // Play Page (Game Player)
    const char *play_content = 
    "        <section class=\"content\">\n"
    "            <h2 id=\"game-title\">The Holy Player</h2>\n"
    "            <div class=\"game-container\" id=\"canvas-container\">\n"
    "                <div class=\"game-placeholder-text\" id=\"loading-text\">\n"
    "                    <h3>Forging Game Instance...</h3>\n"
    "                    <p>The C-powered WASM engine is initializing.</p>\n"
    "                </div>\n"
    "                <canvas id=\"canvas\" style=\"display:none;\" oncontextmenu=\"event.preventDefault()\"></canvas>\n"
    "            </div>\n"
    "            <div class=\"game-controls\">\n"
    "                <p>Controls: Use Arrows to move. Visit the Golden Crosses.</p>\n"
    "                <a href=\"/games.html\" class=\"btn-small\">Back to Catalog</a>\n"
    "            </div>\n"
    "        </section>\n"
    "        <script src=\"/static/js/community.js\"></script>\n"
    "        <script>\n"
    "            const urlParams = new URLSearchParams(window.location.search);\n"
    "            const gameId = urlParams.get('game');\n"
    "            \n"
    "            const Module = {\n"
    "                canvas: document.getElementById('canvas'),\n"
    "                print: (text) => console.log(text),\n"
    "                onRuntimeInitialized: () => {\n"
    "                    console.log('WASM Engine Ready');\n"
    "                }\n"
    "            };\n"
    "\n"
    "            createCommunityModule(Module).then(module => {\n"
    "                document.getElementById('loading-text').style.display = 'none';\n"
    "                document.getElementById('canvas').style.display = 'block';\n"
    "                \n"
    "                // Start the game engine\n"
    "                module._start_game();\n"
    "            });\n"
    "        </script>\n";
    write_page("play.html", "Play Online", play_content);

    // First Blog Post
    const char *first_post_content = 
    "        <section class=\"content\">\n"
    "            <article class=\"blog-post\">\n"
    "                <h2>The Philosophy of Holy Code</h2>\n"
    "                <p class=\"meta\">Published on February 12, 2026</p>\n"
    "                <p>In the beginning was the Word, and the Word was with God, and the Word was God. In the world of silicon and electrons, the Word manifests as code.</p>\n"
    "                <p>We choose C because it is a language of discipline. It requires the programmer to be mindful of every byte, every pointer, and every memory allocation. This mindfulness is a form of prayer, a way to honor the intricate design of the universe through careful craftsmanship.</p>\n"
    "                <p>Our games are not just entertainment; they are digital icons. We strive to create experiences that lead the player towards truth, beauty, and goodness. AMDG.</p>\n"
    "                <a href=\"/blog.html\" class=\"btn\">Back to Blog</a>\n"
    "            </article>\n"
    "        </section>\n";
    write_page("blog/first-post.html", "The Philosophy of Holy Code", first_post_content);

    return 0;
}