#include <iostream>
#include "game.h"
#include "locale.h"

using namespace std;

int main(int argc, char * argv[])
{
    setlocale( LC_ALL,"Russian" );
    cout << "Тест" << endl;
    Game game = Game();
    game.Run();
    cout << "Game has terminated successfully" << endl;
    return 0;
}
