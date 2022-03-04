#include "snake.h"
#include "game.h"

Snake::Snake()
{
    pos.x = 0;
    pos.y = 0;
    alive = true;
}

void Snake::GrowBody(int quantity)
{
    growing += quantity;
    std::cout << "growing: " << growing << std::endl;
}

void Snake::PollEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if(e.type == SDL_QUIT){
            SDL_Quit();
        }
        if (e.type == SDL_KEYDOWN)
                {
                    switch (e.key.keysym.sym)
                    {
                        case SDLK_w:
                            if (last_dir != Move::down || size == 1)
                                dir = Move::up;
                            break;

                        case SDLK_s:
                            if (last_dir != Move::up || size == 1)
                                dir = Move::down;
                            break;

                        case SDLK_a:
                            if (last_dir != Move::right || size == 1)
                                dir = Move::left;
                            break;

                        case SDLK_d:
                            if (last_dir != Move::left || size == 1)
                                dir = Move::right;
                            break;
                        case SDLK_ESCAPE:
                            SDL_Quit();
                        break;
                    }
                }
    }
}

void Snake::Update()
{
    switch (dir)
       {
           case Move::up:
               pos.y -= speed;
               pos.x = floorf(pos.x);
               break;

           case Move::down:
               pos.y += speed;
               pos.x = floorf(pos.x);
               break;

           case Move::left:
               pos.x -= speed;
               pos.y = floorf(pos.y);
               break;

           case Move::right:
               pos.x += speed;
               pos.y = floorf(pos.y);
               break;
       }

       // Wrap
       if (pos.x < 0) pos.x = GRID_WIDTH - 1;
       else if (pos.x > GRID_WIDTH-1) pos.x = 0;

       if (pos.y < 0) pos.y = GRID_HEIGHT - 1;
       else if (pos.y > GRID_HEIGHT-1) pos.y = 0;

       int new_x = static_cast<int>(pos.x);
       int new_y = static_cast<int>(pos.y);

       // Check if head position has changed
       if (new_x != head.x || new_y != head.y)
       {
           last_dir = dir;

           // If we are growing, just make a new neck
           if (growing > 0)
           {
               size++;
               body.push_back(head);
               growing--;
               Game::grid[head.x][head.y] = Block::body;
           }
           else
           {
               // We need to shift the body
               SDL_Point free = head;
               vector<SDL_Point>::reverse_iterator rit = body.rbegin();
               for ( ; rit != body.rend(); ++rit)
               {
                   Game::grid[free.x][free.y] = Block::body;
                   swap(*rit, free);
               }

               Game::grid[free.x][free.y] = Block::empty;
           }

       }

       head.x = new_x;
       head.y = new_y;

       Block & next = Game::grid[head.x][head.y];
       // Check if there's food over here
       if (next == Block::food)
       {
           score++;
           Game::fruit->spawnFood();
           GrowBody(1);
       }
       // Check if we're dead
       else if (next == Block::body)
       {
           alive = false;
       }

       next = Block::head;
}

void Snake::Render()
{

    Game::Draw(static_cast<int>(pos.x), static_cast<int>(pos.y));
}

void Snake::RenderBody()
{
    for (SDL_Point & point : body)
        {
            Game::Draw(point.x, point.y);
        }
}

bool Snake::isAlive()
{
    return alive;
}
