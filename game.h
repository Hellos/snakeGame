#pragma once
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "consts.h"
#include "snake.h"
#include "fruit.h"
#include <ctime>
#include <iostream>
#include "SDL_ttf.h"

using namespace std;

class Snake;

class Game
{
private:
    bool running = false;
    int fps = 0;


    void UpdateWindowTitle();
    void GameLoop();
    void Render();
    void Update();
    void PollEvents();
    void Close();
    SDL_Texture* renderText(const string &message, SDL_Color color,int x, int y ,int width, int height);

    Snake* snake = nullptr;

    TTF_Font *font = nullptr;
public:
    Game();
    void Run();

    static void Draw(int x, int y);

    SDL_Window *window = nullptr;
    static SDL_Renderer *renderer;
    static Fruit* fruit;
    static Block grid[GRID_WIDTH][GRID_HEIGHT];
    void showMenu();

};
