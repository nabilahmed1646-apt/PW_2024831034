#include <SDL2/SDL.h>
#include <cmath>
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

    SDL_Window* window = SDL_CreateWindow("Two Circles",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    //  Circle 1 (auto moving)
    int x1 = 0;
    int y1 = height / 2;
    int r1 = 40;

    //  Circle 2 (controlled)
    int x2 = width / 2;
    int y2 = 0;
    int r2 = 40;

    bool running = true;
    SDL_Event e;

    while (running) {

        // 🎮 Event handling
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;

            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:    y2 -= 10; break;
                    case SDLK_DOWN:  y2 += 10; break;
                    case SDLK_LEFT:  x2 -= 10; break;
                    case SDLK_RIGHT: x2 += 10; break;
                }
            }
        }

        //  Move circle 1 (left → right)
        x1 += 3;
        if (x1 > width) x1 = 0;

        //  Collision check
        double distance = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
        bool collision = distance <= (r1 + r2);

        //  Background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //  Circle 1 color
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        drawCircle(renderer, x1, y1, r1);

        //  Circle 2 color
        if (collision)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red if collision
        else
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white

        drawCircle(renderer, x2, y2, r2);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_Quit();
    return 0;
}