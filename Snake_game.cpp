#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>

//Screen and Grid Dimensions
const int SCREEN_WIDTH=800;
const int SCREEN_HEIGHT=800;
const int GRID_SIZE=20;
// Maximum snake length using arrays
const int MAX_SNAKE_LENGTH=100;
// Direction enumeration
enum Direction{UP,DOWN,LEFT,RIGHT};
int main(int argc, char* argv[]){
// Seed random number generator
srand(time(0));
// 1. Initialize SDL2
SDL_Init(SDL_INIT_VIDEO);
// 2. Create Window
SDL_Window*window=SDL_CreateWindow("Easy Snake Game|Score:0", // Added initial score to title
SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
// 3. Create Renderer
SDL_Renderer*renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
// Game variables using simple arrays
int snakeX[MAX_SNAKE_LENGTH];
int snakeY[MAX_SNAKE_LENGTH];
int snakeLength = 3; // Initial length of the snake
// Starting positions for the snake
snakeX[0] = 300; snakeY[0] = 300; // Head
snakeX[1] = 270; snakeY[1] = 300; // Body segment 1
snakeX[2] = 240; snakeY[2] = 300; // Body segment 2
Direction dir = RIGHT; // Initial direction
// Food coordinates
int foodX = 420;
int foodY = 300;
int score = 0; // PART 1: Initialize Score Variable
bool running = true;
bool gameOver = false;
// MAIN GAME LOOP
while (running) {
// A) HANDLE INPUT
SDL_Event event;
while (SDL_PollEvent(&event)) {
if (event.type == SDL_QUIT) {
running = false;
}
else if (event.type == SDL_KEYDOWN) {
if (event.key.keysym.sym == SDLK_UP && dir != DOWN) dir = UP;
if (event.key.keysym.sym == SDLK_DOWN && dir != UP) dir = DOWN;
if (event.key.keysym.sym == SDLK_LEFT && dir != RIGHT) dir = LEFT;
if (event.key.keysym.sym == SDLK_RIGHT && dir != LEFT) dir = RIGHT;
if (event.key.keysym.sym == SDLK_r && gameOver) { // Press 'R' to restart
snakeLength = 3;
snakeX[0] = 300; snakeY[0] = 300;
snakeX[1] = 270; snakeY[1] = 300;
snakeX[2] = 240; snakeY[2] = 300;
dir = RIGHT;
score = 0; // Reset score on restart
gameOver = false;
// Reset Window Title on restart
SDL_SetWindowTitle(window, "Easy Snake Game | Score: 0");
}
}
}

// B) UPDATE LOGIC
if (!gameOver) {
// Shift body segments forward
for (int i = snakeLength - 1; i > 0; i--) {
snakeX[i] = snakeX[i - 1];
snakeY[i] = snakeY[i - 1];
}
// Move the head in the current direction
if (dir == UP) snakeY[0] -= GRID_SIZE;
if (dir == DOWN) snakeY[0] += GRID_SIZE;
if (dir == LEFT) snakeX[0] -= GRID_SIZE;
if (dir == RIGHT) snakeX[0] += GRID_SIZE;
// Collision Detection: Wall Boundaries
if (snakeX[0] < 0 || snakeX[0] >= SCREEN_WIDTH || snakeY[0] < 0 || snakeY[0] >= SCREEN_HEIGHT) {
gameOver = true;
}
// Collision Detection: Self-destruction
for (int i = 1; i < snakeLength; i++) {
if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
gameOver = true;
}
}
// Collision Detection: Eating Food
if (snakeX[0] == foodX && snakeY[0] == foodY) {
if (snakeLength < MAX_SNAKE_LENGTH) {
snakeLength++; // Increase length
}
//  Increase Score & Display Score
score += 10;
std::string titleStr = "Easy Snake Game | Score: " + std::to_string(score);
SDL_SetWindowTitle(window, titleStr.c_str()); // Dynamically updates the window title
// Generate new random position for food
foodX = (rand() % (SCREEN_WIDTH / GRID_SIZE)) * GRID_SIZE;
foodY = (rand() % (SCREEN_HEIGHT / GRID_SIZE)) * GRID_SIZE;
}
//  Display Game Over Screen (Triggers right when gameOver becomes true)
if (gameOver) {
std::string overStr = "GAME OVER! Final Score: " + std::to_string(score) + " | Press 'R' to Restart";
SDL_SetWindowTitle(window, overStr.c_str());
}
}
//  RENDER FRAME
//  Clear screen with a Dark Grey color
SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
SDL_RenderClear(renderer);
if (!gameOver) {
//  Draw Food (Red Square)
SDL_Rect foodRect = { foodX, foodY, GRID_SIZE - 2, GRID_SIZE - 2 };
SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
SDL_RenderFillRect(renderer, &foodRect);
//  Draw Snake (Green Squares)
for (int i = 0; i < snakeLength; i++) {
SDL_Rect snakeRect = { snakeX[i], snakeY[i], GRID_SIZE - 2, GRID_SIZE - 2 };
if (i == 0) {
SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Bright Green for Head
} else {
SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255); // Darker Green for Body
}
SDL_RenderFillRect(renderer, &snakeRect);
}
} else {
// Game Over Visual: Flash screen Red
SDL_SetRenderDrawColor(renderer, 150, 0, 0, 255);
SDL_RenderClear(renderer);
}
// 4. Present the rendered frame to the window
SDL_RenderPresent(renderer);
// Frame rate delay (Controls game speed - Medium)
SDL_Delay(50);
}
// Clean up resources and close SDL2
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();
return 0;
}