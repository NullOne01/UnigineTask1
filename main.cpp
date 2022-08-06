#include <iostream>
#include "view/GameLoader.h"
#include "view/GameSaver.h"
#include "view/GameCalculation.h"

int main() {
    GameLoader game_loader;
    auto game_info = game_loader.readGameInfo("resources/data_big.txt");

    GameCalculation game_calculation;
    game_calculation.calculateUnits(&game_info);

    GameSaver game_saver;
    game_saver.writeGameInfo(game_info, "result.txt");

    std::cout << "I'm done!" << std::endl;

    return 0;
}
