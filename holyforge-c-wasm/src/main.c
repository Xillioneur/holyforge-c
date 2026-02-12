#include <emscripten.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// --- Community/Prayer Wall Functions ---
EMSCRIPTEN_KEEPALIVE
const char* format_prayer(const char* name, const char* intention) {
    static char buffer[512];
    snprintf(buffer, sizeof(buffer), 
        "<div class=\"prayer-item\">\n"
        "    <strong>%s</strong> is praying for:\n"
        "    <p>%s</p>\n"
        "</div>", 
        name, intention);
    return buffer;
}

// --- Mini-RPG Game Engine ---

SDL_Window *window;
SDL_Renderer *renderer;
int player_x = 400, player_y = 300;
int station_x = 100, station_y = 100;
int score = 0;
int game_running = 0;

void main_loop() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP: player_y -= 10; break;
                case SDLK_DOWN: player_y += 10; break;
                case SDLK_LEFT: player_x -= 10; break;
                case SDLK_RIGHT: player_x += 10; break;
            }
        }
    }

    // Check collision with "Station"
    if (abs(player_x - station_x) < 20 && abs(player_y - station_y) < 20) {
        score++;
        station_x = (rand() % 700) + 50;
        station_y = (rand() % 500) + 50;
        printf("Station Visited! Total Devotion: %d\n", score);
    }

    // Render
    SDL_SetRenderDrawColor(renderer, 15, 15, 18, 255); // Dark background
    SDL_RenderClear(renderer);

    // Draw Station (Gold Cross Placeholder)
    SDL_SetRenderDrawColor(renderer, 212, 175, 55, 255);
    SDL_Rect station_rect = {station_x - 10, station_y - 10, 20, 20};
    SDL_RenderFillRect(renderer, &station_rect);
    SDL_Rect station_cross_v = {station_x - 3, station_y - 20, 6, 40};
    SDL_RenderFillRect(renderer, &station_cross_v);
    SDL_Rect station_cross_h = {station_x - 15, station_y - 10, 30, 6};
    SDL_RenderFillRect(renderer, &station_cross_h);

    // Draw Player (Blue Knight Placeholder)
    SDL_SetRenderDrawColor(renderer, 26, 35, 126, 255);
    SDL_Rect player_rect = {player_x - 15, player_y - 15, 30, 30};
    SDL_RenderFillRect(renderer, &player_rect);

    SDL_RenderPresent(renderer);
}

EMSCRIPTEN_KEEPALIVE
void start_game() {
    if (game_running) return;
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);
    
    printf("HolyForge Engine: Stations of the Cross Mini-RPG Started.\n");
    game_running = 1;
    emscripten_set_main_loop(main_loop, 0, 1);
}