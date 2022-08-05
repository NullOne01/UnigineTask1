#include <iostream>
#include "view/GameLoader.h"

int main() {
    GameLoader game_loader;
    auto game_info = game_loader.readGameInfo("resources/data_big.txt");

    for (auto &unit: game_info.units) {
        auto neighbours = game_info.world_map.getNeighbours(unit.get());
        for (auto &neighbour: neighbours) {
            if (neighbour == unit.get()) {
                continue;
            }

            Vector2<double> b(neighbour->pos.x - unit->pos.x, neighbour->pos.y - unit->pos.y);
            if (b.absolute() >= game_info.view_distance) {
                continue;
            }

            double ab = Vector2<double>::dotProduct(unit->view, b);
            double cos_alpha = ab / b.absolute();
            if (cos_alpha >= game_info.cos_half_sector_angle) {
                unit->units_can_see++;
            }
        }
    }

    std::cout << "Hello, World!" << std::endl;

    return 0;
}
