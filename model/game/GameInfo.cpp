#include "GameInfo.h"
#include "cmath"
#include "../math/Utils.h"

GameInfo::GameInfo(double sector_angle,
                   double view_distance,
                   const Vector2<double> &left_bottom,
                   const Vector2<double> &right_top)
        : sector_angle(sector_angle), view_distance(view_distance),
          world_map(view_distance, left_bottom, right_top) {
    // Precalculate cos of given sector.
    double half_angle = sector_angle / 2;
    cos_half_sector_angle = cos(Utils::degToRad(half_angle));
}
