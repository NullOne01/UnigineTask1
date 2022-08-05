cmake_minimum_required(VERSION 3.20)
project(UnigineTask1)

set(CMAKE_CXX_STANDARD 14)
message(${CMAKE_CURRENT_SOURCE_DIR}/resources/)
message(${CMAKE_BINARY_DIR}/resources/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/ DESTINATION ${CMAKE_BINARY_DIR}/resources/)

add_executable(UnigineTask1 main.cpp model/containers/CellList.cpp model/containers/CellList.h model/math/Vector2.cpp model/math/Vector2.h model/game/GameInfo.cpp model/game/GameInfo.h model/game/Unit.cpp model/game/Unit.h view/GameLoader.cpp view/GameLoader.h model/game/Constants.h model/math/Utils.h)
