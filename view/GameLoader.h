#ifndef UNIGINETASK1_VIEW_GAMELOADER_H_
#define UNIGINETASK1_VIEW_GAMELOADER_H_

#include <string>
#include "../model/game/GameInfo.h"
class GameLoader {
public:
    GameInfo readGameInfo(const std::string &file_name);
};

#endif //UNIGINETASK1_VIEW_GAMELOADER_H_
