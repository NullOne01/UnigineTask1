#ifndef UNIGINETASK1_MODEL_GAME_GAMEINFO_H_
#define UNIGINETASK1_MODEL_GAME_GAMEINFO_H_

#include <memory>
#include <vector>
#include "Unit.h"
#include "../containers/CellList.h"

class GameInfo {
public:
    GameInfo(double sector_angle, double view_distance,
             const Vector2<double> &left_bottom, const Vector2<double> &right_top);

    double sector_angle;
    double cos_half_sector_angle;
    double view_distance;

    std::vector<std::unique_ptr<Unit>> units;
    CellList<Unit *> world_map;
};

#endif //UNIGINETASK1_MODEL_GAME_GAMEINFO_H_
