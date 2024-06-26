#include "funcs.h"

#include <algorithm>


uint32_t calculateWaterVolume(const vector<uint32_t> &wall_heights, vector<uint32_t> &water_heights) {
    const uint8_t n = wall_heights.size();
    if (n <= 2) return 0; // Не может быть удержано воды

    vector<uint32_t> max_left(n, 0); // Массив максимальной высоты стены слева от текущей
    vector<uint32_t> max_right(n, 0); // Массив максимальной высоты стены справа от текущей

    // Вычисляем максимальную высоту стены слева от каждой стены
    uint32_t max_height = 0;
    for (int i = 0; i < n; ++i) {
        max_height = max(max_height, wall_heights[i]);
        max_left[i] = max_height;
    }

    // Вычисляем максимальную высоту стены справа от каждой стены
    max_height = 0;
    for (int i = n - 1; i >= 0; --i) {
        max_height = max(max_height, wall_heights[i]);
        max_right[i] = max_height;
    }

    uint32_t total_water = 0;

    // Вычисляем высоту воды между стенами
    for (int i = 0; i < n; ++i) {
        if (const uint32_t water_level = min(max_left[i], max_right[i]) - wall_heights[i]; water_level > 0) {
            total_water += water_level; // Увеличиваем общее количество воды
            water_heights[i] = water_level; // Сохраняем высоту воды для текущей стены
        } else {
            water_heights[i] = 0;
        }
    }

    return total_water;
}

string drawWallSchema(const vector<uint32_t> &wall_heights, const vector<uint32_t> &water_heights) {
    string schema; // Строка для хранения схемы стен и воды

    if (wall_heights.empty() || water_heights.empty() || wall_heights.size() != water_heights.size()) {
        return schema;
    }

    const size_t cols = wall_heights.size();
    const uint32_t max_height = *max_element(wall_heights.begin(), wall_heights.end());
    vector<uint32_t> current_water_heights = water_heights; // Копируем water_heights для изменения

    // Заполняем схему воздухом и водой
    for (uint32_t row = max_height; row > 0; --row) {
        for (size_t col = 0; col < cols; ++col) {
            if (row <= wall_heights[col]) {
                schema.push_back('#'); // Заполняем стенами
            } else if (row <= wall_heights[col] + current_water_heights[col]) {
                schema.push_back('~'); // Заполняем водой
                --current_water_heights[col];
            } else {
                schema.push_back(' '); // Заполняем пустым пространством
            }
            schema.push_back(' '); // Добавляем пробел после каждого символа
        }
        schema.push_back('\n'); // Добавляем символ переноса строки между строками
    }

    return schema; // Возвращаем схему стен и воды
}