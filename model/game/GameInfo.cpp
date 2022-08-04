#include "GameInfo.h"

GameInfo::GameInfo(double sector_angle,
                   double view_distance,
                   const Vector2<double> &left_bottom,
                   const Vector2<double> &right_top)
    : sector_angle(sector_angle), view_distance(view_distance) {
    world_map = std::make_unique<CellList<Unit *>>(view_distance, left_bottom, right_top);
}
