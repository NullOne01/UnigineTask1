#include <fstream>
#include "GameSaver.h"

void GameSaver::writeGameInfo(const GameInfo &game_info, const std::string &file_name) {
    std::ofstream file(file_name);

    for (int i = 0; i < game_info.units.size(); ++i) {
        auto &unit = game_info.units[i];
        file << "Unit " << i << " can see " << unit->units_can_see << " units\n";
    }

    file.close();
}
