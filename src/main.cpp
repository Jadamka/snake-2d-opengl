#include "game.h"
#include <iostream>

int main()
{
    Game game;
    if(game.Init(800, 800, "Snake") != -1){
        game.Run();
        game.Clear();
    }
    else{
        std::cout << "Something went wrong!!!" << std::endl;
    }

    return 0;
}
