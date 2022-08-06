#ifndef UNIGINETASK1_GAMESAVER_H
#define UNIGINETASK1_GAMESAVER_H


#include "../model/game/GameInfo.h"

class GameSaver {
public:
    void writeGameInfo(const GameInfo &game_info, const std::string &file_name);
};


#endif //UNIGINETASK1_GAMESAVER_H
