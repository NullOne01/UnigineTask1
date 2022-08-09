#include "GameCalculation.h"
#include <thread>
#include <xmmintrin.h>
#include <future>
#include <algorithm>

void GameCalculation::calculateUnits(GameInfo *game_info) {
    // Best option is one task per CPU.
    int thread_num = std::thread::hardware_concurrency();
    int batch_size = game_info->units.size() / thread_num + 1;

    std::vector<std::shared_future<void>> async_tasks;
    async_tasks.reserve(thread_num);

    // Start new threads with batches to calculate.
    int units_passed = 0;
    while (units_passed < game_info->units.size()) {
        int index_from = units_passed;
        units_passed += batch_size;
        units_passed = std::min(units_passed, static_cast<int>(game_info->units.size()));
        int index_to = units_passed;

        auto func = [this, &game_info, index_from, index_to] {
            calculateBatchUnits(game_info, index_from, index_to);
        };
        std::shared_future<void> ready_future(std::async(std::launch::async, func));
        async_tasks.push_back(ready_future);
    }

    // Wait until all threads finish.
    for (auto &task: async_tasks) {
        task.get();
    }
}

void GameCalculation::calculateBatchUnits(GameInfo *game_info, int from, int to) {
    for (int unit_num = from; unit_num < to; ++unit_num) {
        auto unit = game_info->units[unit_num].get();
        auto neighbours = game_info->world_map.getNeighbours(unit);
        neighbours.erase(std::remove(neighbours.begin(), neighbours.end(), unit), neighbours.end());
        // Creating huge arrays and praying that this info would fit.
        constexpr int MAX_ARRAY_SIZE = 1 << 13;
        alignas(16) float neighbours_x[MAX_ARRAY_SIZE];
        alignas(16) float neighbours_y[MAX_ARRAY_SIZE];
        alignas(16) float ans[MAX_ARRAY_SIZE];
        for (int i = 0; i < neighbours.size(); ++i) {
            neighbours_x[i] = neighbours[i]->pos.x - unit->pos.x;
            neighbours_y[i] = neighbours[i]->pos.y - unit->pos.y;
        }

        alignas(16) float unit_x_arr[4] = {static_cast<float>(unit->view.x), static_cast<float>(unit->view.x),
                                           static_cast<float>(unit->view.x), static_cast<float>(unit->view.x)};
        alignas(16) float unit_y_arr[4] = {static_cast<float>(unit->view.y), static_cast<float>(unit->view.y),
                                           static_cast<float>(unit->view.y), static_cast<float>(unit->view.y)};

        // fuck my life... SIMD below
        __m128 unit_x = _mm_load_ps(&unit_x_arr[0]);
        __m128 unit_y = _mm_load_ps(&unit_y_arr[0]);

        __m128 r_length;
        size_t size4 = neighbours.size() - (neighbours.size() % 4);
        // cos = (dot(unit, b) / |b|)
        for (int i = 0; i < size4; i += 4) {
            __m128 b_x = _mm_load_ps(&neighbours_x[i]);
            __m128 b_y = _mm_load_ps(&neighbours_y[i]);

            // Dot
            __m128 r_dot = _mm_mul_ps(unit_x, b_x);
            r_dot = _mm_add_ps(r_dot, _mm_mul_ps(unit_y, b_y));

            __m128 b_x_sqr = _mm_mul_ps(b_x, b_x);
            __m128 b_y_sqr = _mm_mul_ps(b_y, b_y);

            // Absolute
            r_length = _mm_add_ps(b_x_sqr, b_y_sqr);
            r_length = _mm_sqrt_ps(r_length);

            // cos
            __m128 r_cos = _mm_div_ps(r_dot, r_length);
            _mm_store_ps(&ans[i], r_cos);
        }

        for (int i = 0; i < size4; ++i) {
            if (r_length[i] <= game_info->view_distance && ans[i] >= game_info->cos_half_sector_angle) {
                unit->units_can_see++;
            }
        }

        for (int i = size4; i < neighbours.size(); ++i) {
            auto neighbour = neighbours[i];
            if (neighbour == unit) {
                continue;
            }

            Vector2<double> b(neighbour->pos.x - unit->pos.x, neighbour->pos.y - unit->pos.y);
            if (b.absolute() >= game_info->view_distance) {
                continue;
            }

            double ab = Vector2<double>::dotProduct(unit->view, b);
            double cos_alpha = ab / b.absolute();
            if (cos_alpha >= game_info->cos_half_sector_angle) {
                unit->units_can_see++;
            }
        }
    }
}
