#include <fstream>
#include "GameLoader.h"
#include "../model/game/Constants.h"

GameInfo GameLoader::readGameInfo(const std::string &file_name) {
    std::ifstream file_stream(file_name);
    if (!file_stream.is_open()) {
        std::throw_with_nested( std::runtime_error("File not found") );
    }

    double sector_angle, view_distance;
    file_stream >> sector_angle >> view_distance;

    std::vector<std::unique_ptr<Unit>> units;
    units.resize(MEDIUM_NUMBER_OF_UNITS);

    double min_x, min_y, max_x, max_y;
    double pos_x, pos_y, view_x, view_y;
    while (file_stream >> pos_x >> pos_y >> view_x >> view_y) {
        units.push_back(std::make_unique<Unit>(pos_x, pos_y, view_x, view_y));

        min_x = std::min(min_x, pos_x);
        max_x = std::max(max_x, pos_x);

        min_y = std::min(min_y, pos_y);
        max_y = std::max(max_y, pos_y);
    }
    file_stream.close();

    GameInfo game_info(sector_angle, view_distance, {min_x, min_y}, {max_x, max_y});
    return game_info;
}
