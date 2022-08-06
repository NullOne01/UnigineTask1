#ifndef UNIGINETASK1_GAMECALCULATION_H
#define UNIGINETASK1_GAMECALCULATION_H


#include "../model/game/GameInfo.h"

class GameCalculation {
public:
    void calculateUnits(GameInfo *game_info);

private:
    void calculateBatchUnits(GameInfo *game_info, int from, int to);
};


#endif //UNIGINETASK1_GAMECALCULATION_H
