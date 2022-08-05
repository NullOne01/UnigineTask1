#ifndef UNIGINETASK1_MODEL_GAME_UNIT_H_
#define UNIGINETASK1_MODEL_GAME_UNIT_H_

#include "../math/Vector2.h"

class Unit {
public:
    Unit(double pos_x, double pos_y, double view_x, double view_y);

    Vector2<double> pos;
    Vector2<double> view;
    int units_can_see{};
};

#endif //UNIGINETASK1_MODEL_GAME_UNIT_H_
