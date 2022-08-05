#include <iostream>
#include "view/GameLoader.h"
#include "xmmintrin.h"

int main() {
    GameLoader game_loader;
    auto game_info = game_loader.readGameInfo("resources/data_big.txt");

    for (auto &unit: game_info.units) {
        auto neighbours = game_info.world_map.getNeighbours(unit.get());
        neighbours.erase(std::remove(neighbours.begin(), neighbours.end(), unit.get()), neighbours.end());
        // Heap allocation. Idk how to create dynamic array without heap.
        float *neighbours_x = new float[neighbours.size()];
        float *neighbours_y = new float[neighbours.size()];
        float *ans = new float[neighbours.size()];
        for (int i = 0; i < neighbours.size(); ++i) {
            neighbours_x[i] = neighbours[i]->pos.x - unit->pos.x;
            neighbours_y[i] = neighbours[i]->pos.y - unit->pos.y;
        }

        alignas(16) float unit_x_arr[4] = {static_cast<float>(unit->view.x), static_cast<float>(unit->view.x),
                                           static_cast<float>(unit->view.x), static_cast<float>(unit->view.x)};
        alignas(16) float unit_y_arr[4] = {static_cast<float>(unit->view.y), static_cast<float>(unit->view.y),
                                           static_cast<float>(unit->view.y), static_cast<float>(unit->view.y)};

        // fuck my life...
        __m128 unit_x = _mm_load_ps(&unit_x_arr[0]);
        __m128 unit_y = _mm_load_ps(&unit_y_arr[0]);

        __m128 r2;
        size_t size4 = neighbours.size() - (neighbours.size() % 4);
        for (int i = 0; i < size4; i += 4) {
            __m128 b_x = _mm_load_ps(&neighbours_x[i]);
            __m128 b_y = _mm_load_ps(&neighbours_y[i]);

            // Dot
            __m128 r1 = _mm_mul_ps(unit_x, b_x);
            r1 = _mm_add_ps(r1, _mm_mul_ps(unit_y, b_y));

            __m128 b_x_sqr = _mm_mul_ps(b_x, b_x);
            __m128 b_y_sqr = _mm_mul_ps(b_y, b_y);

            // Absolute
            r2 = _mm_add_ps(b_x_sqr, b_y_sqr);
            r2 = _mm_sqrt_ps(r2);

            // cos
            __m128 r3 = _mm_div_ps(r1, r2);
            _mm_store_ps(&ans[i], r3);
        }

        for (int i = 0; i < size4; ++i) {
            if (r2[i] <= game_info.view_distance && ans[i] >= game_info.cos_half_sector_angle) {
                unit->units_can_see++;
            }
        }

        delete[] neighbours_x;
        delete[] neighbours_y;
        delete[] ans;

        for (int i = size4; i < neighbours.size(); ++i) {
            auto neighbour = neighbours[i];
            if (neighbour == unit.get()) {
                continue;
            }

            Vector2<double> b(neighbour->pos.x - unit->pos.x, neighbour->pos.y - unit->pos.y);
            if (b.absolute() >= game_info.view_distance) {
                continue;
            }

            double ab = Vector2<double>::dotProduct(unit->view, b);
            double cos_alpha = ab / b.absolute();
            if (cos_alpha >= game_info.cos_half_sector_angle) {
                unit->units_can_see++;
            }
        }
    }

    std::cout << "Hello, World!" << std::endl;

    return 0;
}
