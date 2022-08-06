#include <cassert>
#include "CellList.h"
#include "../game/Unit.h"

template<typename T>
CellList<T>::CellList(double cell_side, const Vector2<double> &left_bottom, const Vector2<double> &right_top)
        :cell_side_(cell_side), left_bottom_(left_bottom), right_top_(right_top) {
    generate();
}

template<typename T>
std::pair<int, int> CellList<T>::addItem(const T &item, const Vector2<double> &pos) {
    assert(isInBounds(pos));

    int cell_y = (pos.y - left_bottom_.y) / cell_side_;
    int cell_x = (pos.x - left_bottom_.x) / cell_side_;

    grid_[cell_y][cell_x].push_back(item);

    std::pair<int, int> indexes{cell_y, cell_x};
    hash_map[item] = indexes;

    return indexes;
}

template<typename T>
std::vector<T> CellList<T>::getNeighbours(const T &item) {
    std::mutex &mutex = mutexes_pool_->operator[](std::hash<T>{}(item) % mutexes_pool_->size());
    std::unique_lock<std::mutex> lock(mutex);

    std::pair<int, int> item_pos = hash_map[item];

    if (!neighbours_[item_pos.first][item_pos.second].empty()) {
        return neighbours_[item_pos.first][item_pos.second];
    }

    int dir_x[9] = {0, 0, 0, -1, 1, 1, 1, -1, -1};
    int dir_y[9] = {0, 1, -1, 0, 0, 1, -1, 1, -1};

    size_t total_elements = 0;
    for (int i = 0; i < 9; i++) {
        int new_y = item_pos.first + dir_y[i];
        int new_x = item_pos.second + dir_x[i];
        if (!isInBoundsIndexes(new_y, new_x)) {
            continue;
        }

        total_elements += grid_[new_y][new_x].size();
    }

    std::vector<T> ans;
    ans.reserve(total_elements);
    for (int i = 0; i < 9; i++) {
        int new_y = item_pos.first + dir_y[i];
        int new_x = item_pos.second + dir_x[i];
        if (!isInBoundsIndexes(new_y, new_x)) {
            continue;
        }

        ans.insert(ans.end(), grid_[new_y][new_x].begin(), grid_[new_y][new_x].end());
    }

    neighbours_[item_pos.first][item_pos.second] = std::move(ans);
    return neighbours_[item_pos.first][item_pos.second];
}

template<typename T>
void CellList<T>::generate() {
    // Adding 2 more cells each dimension to prevent some out of bounds shit.
    int cells_num_y = (right_top_.y - left_bottom_.y) / cell_side_ + 2;
    int cells_num_x = (right_top_.x - left_bottom_.x) / cell_side_ + 2;

    std::vector<std::vector<T>> row(cells_num_x, std::vector<T>());
    grid_.resize(cells_num_y, row);
    neighbours_.resize(cells_num_y, row);
    mutexes_pool_ = std::make_unique<std::array<std::mutex, 32>>();
}

template<typename T>
bool CellList<T>::isInBounds(const Vector2<double> &pos) {
    return (pos.x >= left_bottom_.x && pos.x <= right_top_.x) &&
           (pos.y >= left_bottom_.y && pos.y <= right_top_.y);
}

template<typename T>
bool CellList<T>::isInBoundsIndexes(int y, int x) {
    return (y >= 0 && y < grid_.size()) &&
           (x >= 0 && x < grid_[0].size());
}

template
class CellList<Unit *>;