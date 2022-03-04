#ifndef FRUIT_H
#define FRUIT_H

#include "SDL.h"
#include "object.h"

class Fruit : public Obj
{
public:
    Fruit();
    void spawnFood();
    void Render();
private:
    SDL_Point food;
};

#endif // FRUIT_H
