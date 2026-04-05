#include <SDL2/SDL.h>
#include <cmath>

// Easy circle draw function
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

    SDL_Window* window = SDL_CreateWindow("Simple Circle",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Center & radius
    int cx = width / 2;
    int cy = height / 2;
    int radius = 100;

    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;
        }

        // Background black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Circle white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        drawCircle(renderer, cx, cy, radius);

        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    return 0;
}