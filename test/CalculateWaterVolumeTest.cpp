#include <gtest/gtest.h>
#include "../src/Header.h"

// Тестирование функции calculateWaterVolume для пустого вектора
TEST(CalculateWaterVolumeTest, EmptyVector) {
std::vector<uint32_t> heights = {};
// Ожидаемый результат: 0
EXPECT_EQ(calculateWaterVolume(heights), 0);
}

// Тестирование функции calculateWaterVolume для вектора с одним элементом
TEST(CalculateWaterVolumeTest, OneElementVector) {
std::vector<uint32_t> heights = {5};
// Ожидаемый результат: 0
EXPECT_EQ(calculateWaterVolume(heights), 0);
}

// Тестирование функции calculateWaterVolume для вектора с двумя элементами
TEST(CalculateWaterVolumeTest, TwoElementVector) {
std::vector<uint32_t> heights = {5, 10};
// Ожидаемый результат: 0
EXPECT_EQ(calculateWaterVolume(heights), 0);
}

// Базовый тест для функции calculateWaterVolume с различными высотами стен
TEST(CalculateWaterVolumeTest, BasicTest) {
std::vector<uint32_t> heights = {3, 0, 0, 2, 0, 4};
// Ожидаемый результат: 10 (высоты воды: 3, 3, 1, 3)
EXPECT_EQ(calculateWaterVolume(heights), 10);
}

// Тестирование функции calculateWaterVolume для вектора, где все высоты равны нулю
TEST(CalculateWaterVolumeTest, AllZeroes) {
std::vector<uint32_t> heights = {0, 0, 0, 0, 0, 0};
// Ожидаемый результат: 0
EXPECT_EQ(calculateWaterVolume(heights), 0);
}

// Тестирование функции calculateWaterVolume для вектора, где все высоты одинаковы
TEST(CalculateWaterVolumeTest, AllSameHeight) {
std::vector<uint32_t> heights = {5, 5, 5, 5, 5, 5};
// Ожидаемый результат: 0
EXPECT_EQ(calculateWaterVolume(heights), 0);
}

// Тестирование функции calculateWaterVolume для вектора со случайными высотами стен
TEST(CalculateWaterVolumeTest, RandomHeights) {
std::vector<uint32_t> heights = {5, 0, 3, 2, 6, 4, 0, 5, 3, 7, 7};
// Ожидаемый результат: 22 (высоты воды: 5, 2, 3, 2, 6, 1, и 3)
EXPECT_EQ(calculateWaterVolume(heights), 22);
}