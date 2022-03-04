#include "fruit.h"
#include "game.h"

Fruit::Fruit()
{

}

void Fruit::spawnFood()
{
    int x, y;
        while (true)
        {
            x = rand() % GRID_WIDTH;
            y = rand() % GRID_HEIGHT;

            if (Game::grid[x][y] == Block::empty)
            {
                Game::grid[x][y] = Block::food;
                food.x = x;
                food.y = y;
                break;
            }
        }
}

void Fruit::Render()
{
    Game::Draw(food.x, food.y);
}
