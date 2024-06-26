#include <gtest/gtest.h>
#include "funcs.h"


// Стена одинаковой высоты
TEST(CalculateWaterVolumeTest, EqualHeightWalls) {
    const vector<uint32_t> wall_heights = {3, 3, 3};
    vector<uint32_t> water_heights(wall_heights.size(), 0);
    constexpr uint32_t expected_volume = 0;
    const vector<uint32_t> expected_water_heights = {0, 0, 0};

    const uint32_t volume = calculateWaterVolume(wall_heights, water_heights);

    EXPECT_EQ(volume, expected_volume);
    EXPECT_EQ(water_heights, expected_water_heights);
}

// Минимальное количество стен (0 или 1 или 2)
TEST(CalculateWaterVolumeTest, MinimumNumberOfWalls) {
    const vector<uint32_t> wall_heights = {3, 2};
    vector<uint32_t> water_heights(wall_heights.size(), 0);
    constexpr uint32_t expected_volume = 0;
    const vector<uint32_t> expected_water_heights = {0, 0};

    const uint32_t volume = calculateWaterVolume(wall_heights, water_heights);

    EXPECT_EQ(volume, expected_volume);
    EXPECT_EQ(water_heights, expected_water_heights);
}

// Стены образуют ямы
TEST(CalculateWaterVolumeTest, WallsFormPits) {
    const vector<uint32_t> wall_heights = {3, 0, 2, 0, 4};
    vector<uint32_t> water_heights(wall_heights.size(), 0);
    constexpr uint32_t expected_volume = 7;
    const vector<uint32_t> expected_water_heights = {0, 3, 1, 3, 0};

    const uint32_t volume = calculateWaterVolume(wall_heights, water_heights);

    EXPECT_EQ(volume, expected_volume);
    EXPECT_EQ(water_heights, expected_water_heights);
}

// Стены чередуются
TEST(CalculateWaterVolumeTest, AlternatingWalls) {
    const vector<uint32_t> wall_heights = {1, 3, 1, 3, 1, 3};
    vector<uint32_t> water_heights(wall_heights.size(), 0);
    constexpr uint32_t expected_volume = 4;
    const vector<uint32_t> expected_water_heights = {0, 0, 2, 0, 2, 0};

    const uint32_t volume = calculateWaterVolume(wall_heights, water_heights);

    EXPECT_EQ(volume, expected_volume);
    EXPECT_EQ(water_heights, expected_water_heights);
}

// Высоты стен последовательно уменьшаются
TEST(CalculateWaterVolumeTest, DecreasingWallHeights) {
    const vector<uint32_t> wall_heights = {5, 4, 3, 2, 1};
    vector<uint32_t> water_heights(wall_heights.size(), 0);
    constexpr uint32_t expected_volume = 0;
    const vector<uint32_t> expected_water_heights = {0, 0, 0, 0, 0};

    const uint32_t volume = calculateWaterVolume(wall_heights, water_heights);

    EXPECT_EQ(volume, expected_volume);
    EXPECT_EQ(water_heights, expected_water_heights);
}

// Высоты стен на граничных уровнях
TEST(CalculateWaterVolumeTest, BoundaryWallHeights) {
    const vector<uint32_t> wall_heights = {0, 4294967295, 0};
    vector<uint32_t> water_heights(wall_heights.size(), 0);
    constexpr uint32_t expected_volume = 0;
    const vector<uint32_t> expected_water_heights = {0, 0, 0};

    const uint32_t volume = calculateWaterVolume(wall_heights, water_heights);

    EXPECT_EQ(volume, expected_volume);
    EXPECT_EQ(water_heights, expected_water_heights);
}