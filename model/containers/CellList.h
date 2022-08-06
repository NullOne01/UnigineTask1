#ifndef UNIGINETASK1_MODEL_CONTAINERS_CELLLIST_H_
#define UNIGINETASK1_MODEL_CONTAINERS_CELLLIST_H_

#include <unordered_map>
#include <vector>
#include <array>
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

    std::vector<T> getNeighbours(const T &item);

    // TODO: Unordered map is not cache-friendly. Should use another implementation.
    std::unordered_map<T, std::pair<int, int>> hash_map;

private:
    double cell_side_;
    Vector2<double> left_bottom_;
    Vector2<double> right_top_;

    // Warning: Vector of vectors seems not cache-friendly
    std::vector<std::vector<std::vector<T>>> grid_;
    /**
     * Neighbours of each cell. Lazy initialization (through getNeighbours method).
     */
    std::vector<std::vector<std::vector<T>>> neighbours_;

    /**
     * Pool of mutexes. Used when neighbours_ is lazy calculating.
     */
    std::unique_ptr<std::array<std::mutex, 32>> mutexes_pool_;

    void generate();

    bool isInBounds(const Vector2<double> &pos);

    bool isInBoundsIndexes(int y, int x);
};

#endif //UNIGINETASK1_MODEL_CONTAINERS_CELLLIST_H_
