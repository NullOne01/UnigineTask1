#ifndef UNIGINETASK1_MODEL_CONTAINERS_CELLLIST_H_
#define UNIGINETASK1_MODEL_CONTAINERS_CELLLIST_H_

#include <unordered_map>
#include <vector>
#include "../math/Vector2.h"

/**
 * Cell list
 * @tparam T Type of values to store
 */
template<typename T>
class CellList {
public:
    CellList(double cell_side, const Vector2<double> &left_bottom, const Vector2<double> &right_top);

    std::pair<int, int> addItem(const T &item, const Vector2<double> &pos);

    const std::unordered_map<T, std::pair<int, int>> hash_map;

private:
    double cell_side_;
    Vector2<double> left_bottom_;
    Vector2<double> right_top_;

    std::vector<std::vector<std::vector<T>>> grid_;

    void generate();

    bool isInBounds(const Vector2<double> &pos);
};

#endif //UNIGINETASK1_MODEL_CONTAINERS_CELLLIST_H_
