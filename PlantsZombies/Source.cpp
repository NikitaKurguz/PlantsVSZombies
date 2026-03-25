#include "Game.h"

int main()
{
    srand(time(nullptr));
    system("chcp 1251 > nul");

    Game game;
    game.Run();

    return 0;
}