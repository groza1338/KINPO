#include <gtest/gtest.h>
#include "funcs.h"


// Стена одинаковой высоты
TEST(CalculateWaterVolumeTest, EqualHeightWalls) {
    vector<uint32_t> wall_heights = {3, 3, 3};
    vector<uint32_t> water_heights(wall_heights.size(), 0);
    uint32_t expected_volume = 0;
    vector<uint32_t> expected_water_heights = {0, 0, 0};

    uint32_t volume = calculateWaterVolume(wall_heights, water_heights);

    EXPECT_EQ(volume, expected_volume);
    EXPECT_EQ(water_heights, expected_water_heights);
}

// Минимальное количество стен (0 или 1 или 2)
TEST(CalculateWaterVolumeTest, MinimumNumberOfWalls) {
    vector<uint32_t> wall_heights = {3, 2};
    vector<uint32_t> water_heights(wall_heights.size(), 0);
    uint32_t expected_volume = 0;
    vector<uint32_t> expected_water_heights = {0, 0};

    uint32_t volume = calculateWaterVolume(wall_heights, water_heights);

    EXPECT_EQ(volume, expected_volume);
    EXPECT_EQ(water_heights, expected_water_heights);
}

// Стены образуют ямы
TEST(CalculateWaterVolumeTest, WallsFormPits) {
    vector<uint32_t> wall_heights = {3, 0, 2, 0, 4};
    vector<uint32_t> water_heights(wall_heights.size(), 0);
    uint32_t expected_volume = 7;
    vector<uint32_t> expected_water_heights = {0, 3, 1, 3, 0};

    uint32_t volume = calculateWaterVolume(wall_heights, water_heights);

    EXPECT_EQ(volume, expected_volume);
    EXPECT_EQ(water_heights, expected_water_heights);
}

// Стены чередуются
TEST(CalculateWaterVolumeTest, AlternatingWalls) {
    vector<uint32_t> wall_heights = {1, 3, 1, 3, 1, 3};
    vector<uint32_t> water_heights(wall_heights.size(), 0);
    uint32_t expected_volume = 4;
    vector<uint32_t> expected_water_heights = {0, 0, 2, 0, 2, 0};

    uint32_t volume = calculateWaterVolume(wall_heights, water_heights);

    EXPECT_EQ(volume, expected_volume);
    EXPECT_EQ(water_heights, expected_water_heights);
}

// Высоты стен последовательно уменьшаются
TEST(CalculateWaterVolumeTest, DecreasingWallHeights) {
    vector<uint32_t> wall_heights = {5, 4, 3, 2, 1};
    vector<uint32_t> water_heights(wall_heights.size(), 0);
    uint32_t expected_volume = 0;
    vector<uint32_t> expected_water_heights = {0, 0, 0, 0, 0};

    uint32_t volume = calculateWaterVolume(wall_heights, water_heights);

    EXPECT_EQ(volume, expected_volume);
    EXPECT_EQ(water_heights, expected_water_heights);
}

// Высоты стен на граничных уровнях
TEST(CalculateWaterVolumeTest, BoundaryWallHeights) {
    vector<uint32_t> wall_heights = {0, 4294967295, 0};
    vector<uint32_t> water_heights(wall_heights.size(), 0);
    uint32_t expected_volume = 0;
    vector<uint32_t> expected_water_heights = {0, 0, 0};

    uint32_t volume = calculateWaterVolume(wall_heights, water_heights);

    EXPECT_EQ(volume, expected_volume);
    EXPECT_EQ(water_heights, expected_water_heights);
}