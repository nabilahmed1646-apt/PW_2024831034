#include <SDL2/SDL.h>
#include <cmath>
//draw circle
void drawCircle(SDL_Renderer* renderer, int cx, int cy, int radius) {
    for (int i = 0; i < 360; i++) {
        double angle = i * M_PI / 180.0;
        int x = cx + radius * cos(angle);
        int y = cy + radius * sin(angle);
        SDL_RenderDrawPoint(renderer, x, y);
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    int width = 800, height = 600;

    SDL_Window* window = SDL_CreateWindow("Growing Circle",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    int cx = width / 2;
    int cy = height / 2;

    int radius = 10;          // initial radius
    int initialRadius = 10;   // reset value

    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;
        }

        //  Increase radius over time
        radius += 1;

        // Collision check (window boundary)
        if (cx - radius <= 0 || cx + radius >= width ||
            cy - radius <= 0 || cy + radius >= height) {

            radius = initialRadius; // reset
        }

        // Background black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Circle white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        drawCircle(renderer, cx, cy, radius);

        SDL_RenderPresent(renderer);

        SDL_Delay(20); // slow down animation
    }

    SDL_Quit();
    return 0;
}