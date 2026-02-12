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
"</head>\n"
"<body>\n"
"    <header>\n"
"        <nav>\n"
"            <a href=\"/\" class=\"logo\">HolyForge</a>\n"
"            <div class=\"links\">\n"
"                <a href=\"/\">Home</a>\n"
"                <a href=\"/games.html\">Games</a>\n"
"                <a href=\"/about.html\">About</a>\n"
"            </div>\n"
"        </nav>\n"
"    </header>\n"
"    <main>\n";

const char *HTML_FOOTER = 
"    </main>\n"
"    <footer>\n"
"        <p>&copy; 2026 HolyForge Games. Ad Maiorem Dei Gloriam.</p>\n"
"    </footer>\n"
"</body>\n"
"</html>\n";

void write_page(const char *filename, const char *title, const char *content) {
    char path[256];
    snprintf(path, sizeof(path), "public/%s", filename);
    
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
    // Create public directory if it doesn't exist
    #ifdef _WIN32
        _mkdir("public");
    #else
        mkdir("public", 0755);
    #endif

    // Home Page
    const char *home_content = 
    "        <section class=\"hero\">\n"
    "            <h1>Forging Faith in Digital Worlds</h1>\n"
    "            <p>Our games are built in C/C++ to honor the craftsmanship of code and the glory of God.</p>\n"
    "            <a href=\"/games.html\" class=\"btn\">View the Catalog</a>\n"
    "        </section>\n";
    write_page("index.html", "Home", home_content);

    // About Page
    const char *about_content = 
    "        <section class=\"content\">\n"
    "            <h2>About HolyForge</h2>\n"
    "            <p>HolyForge Games is a C-focused studio dedicated to creating games that explore the depths of Catholic theology and morality.</p>\n"
    "            <p>We believe that high-performance code and deep spiritual narratives go hand-in-hand.</p>\n"
    "        </section>\n";
    write_page("about.html", "About Us", about_content);

    // Games Page
    const char *games_content = 
    "        <section class=\"content\">\n"
    "            <h2>The Holy Catalog</h2>\n"
    "            <div class=\"game-list\">\n"
    "                <div class=\"game-item\">\n"
    "                    <h3>Stations of the Cross: The RPG</h3>\n"
    "                    <p>Built with our custom C++ engine. A journey of redemption.</p>\n"
    "                    <span class=\"badge\">C++</span>\n"
    "                </div>\n"
    "                <div class=\"game-item\">\n"
    "                    <h3>Parables of Strategy</h3>\n"
    "                    <p>A tactical challenge for the faithful mind.</p>\n"
    "                    <span class=\"badge\">C</span>\n"
    "                </div>\n"
    "            </div>\n"
    "        </section>\n";
    write_page("games.html", "Game Catalog", games_content);

    return 0;
}