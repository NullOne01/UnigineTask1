#include <iostream>
#include "view/GameLoader.h"

int main() {
    GameLoader game_loader;
    game_loader.readGameInfo("resources/data1.txt");

    std::cout << "Hello, World!" << std::endl;


    return 0;
}
