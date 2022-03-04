#include "game.h"


SDL_Renderer *Game::renderer = nullptr;
Block Game::grid[GRID_HEIGHT][GRID_HEIGHT] {};
Fruit* Game::fruit = nullptr;


void Game::UpdateWindowTitle()
{
    string title = "Hellosis Snake Рекорд: " + to_string(snake->getScore()) + " ФПС: " + to_string(fps);
    SDL_SetWindowTitle(window, title.c_str());
}

void Game::GameLoop()
{
    Uint32 before, second = SDL_GetTicks(), after;
        int frame_time, frames = 0;

        while (running)
        {
            before = SDL_GetTicks();

              PollEvents();
              Update();
              Render();

            frames++;
            after = SDL_GetTicks();
            frame_time = after - before;

            if (after - second >= 1000)
            {
                fps = frames;
                frames = 0;
                second = after;
                UpdateWindowTitle();
            }

            if (FRAME_RATE > frame_time)
            {
                SDL_Delay(FRAME_RATE - frame_time);
            }
        }
}

void Game::Render()
{
    SDL_Rect block;
    block.w = SCREEN_WIDTH / GRID_WIDTH;
    block.h = SCREEN_WIDTH / GRID_HEIGHT;

    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(renderer);

    SDL_Color color = { 255, 255, 255, 255 };

    renderText("Управление:", color, 16, 0, 128, 32);
    renderText("W - вверх", color, 16, 36, 128, 32);
    renderText("S - вниз", color, 16, 72, 128, 32);
    renderText("A - влево", color, 16, 108, 128, 32);
    renderText("D - вправо", color, 16, 144, 128, 32);
    renderText("D - вправо", color, 16, 144, 128, 32);


    SDL_SetRenderDrawColor(renderer, 0xFF, 0xCC, 0x00, 0xFF);
    fruit->Render();

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    snake->RenderBody();

    if (snake->isAlive()){
        SDL_SetRenderDrawColor(renderer, 0x00, 0x7A, 0xCC, 0xFF);
    }
    else{
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    }
    snake->Render();

    SDL_RenderPresent(renderer);
}

void Game::Update()
{
    if(!snake->isAlive()){
        string name;
        cout << "Введите ваше имя для таблицы рекордов: " << endl;
        cin >> name;

        return;
    }
    snake->Update();
}

void Game::PollEvents()
{
    snake->PollEvents();
}

SDL_Texture *Game::renderText(const string &message, SDL_Color color,int x, int y ,int width, int height)
{
    int iW, iH;
    SDL_Rect dst = {x, y, width, height};
    SDL_Surface* text = TTF_RenderUTF8_Blended(font, message.c_str(), color);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, text);
    SDL_FreeSurface(text);
    SDL_RenderCopy(renderer,tex,NULL,&dst);
    SDL_QueryTexture(tex, NULL, NULL, &iW, &iH);
}

Game::Game()
{
    for (int i = 0; i < GRID_WIDTH; ++i)
        for (int j = 0; j < GRID_HEIGHT; ++j)
        {
            grid[i][j] = Block::empty;
        }

    snake = new Snake();
    fruit = new Fruit();
    TTF_Init();
    font = TTF_OpenFont("cool.ttf", 32);

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
            exit(EXIT_FAILURE);
        }

        // Create Window
        window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (window == NULL)
        {
            cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
            exit(EXIT_FAILURE);
        }

        // Create renderer
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL)
        {
            cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
            exit(EXIT_FAILURE);
        }

    srand(static_cast<unsigned int>(time(0)));
}

void Game::Run()
{
        running = true;
        fruit->spawnFood();
        GameLoop();
}

void Game::Draw(int x, int y)
{
    SDL_Rect block;
    block.w = SCREEN_WIDTH / GRID_WIDTH;
    block.h = SCREEN_WIDTH / GRID_HEIGHT;

    block.x = x * block.w;
    block.y = y * block.h;

    SDL_RenderFillRect(renderer, &block);
}

