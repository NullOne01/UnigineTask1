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
void CellList<T>::generate() {
    int cells_num_y = (right_top_.y - left_bottom_.y) / cell_side_ + 2;
    int cells_num_x = (right_top_.x - left_bottom_.x) / cell_side_ + 2;

    std::vector<std::vector<T>> row(cells_num_x, std::vector<T>());
    grid_.resize(cells_num_y, row);
}

template<typename T>
bool CellList<T>::isInBounds(const Vector2<double> &pos) {
    return (pos.x >= left_bottom_.x && pos.x <= right_top_.x) &&
        (pos.y >= left_bottom_.y && pos.y <= right_top_.y);
}

template class CellList<Unit *>;