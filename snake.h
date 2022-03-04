#ifndef SNAKE_H
#define SNAKE_H

#include "object.h"
#include "game.h"
#include "consts.h"
#include "math.h"
#include <vector>

using namespace std;

class Snake : public Obj {
private:
    bool alive = false;

    Move last_dir = Move::up;
    Move dir = Move::up;

    SDL_Point head = { static_cast<int>(pos.x), static_cast<int>(pos.y) };
    std::vector<SDL_Point> body;

    float speed = 0.5F;
    int growing = 0;
    int score = 0;
    int size = 1;

public:


    Snake();
    void GrowBody(int quantity);
    int getScore(){ return score; };
    void PollEvents();
    void Update();
    void Render();
    void RenderBody();
    bool isAlive();
};

#endif // SNAKE_H
