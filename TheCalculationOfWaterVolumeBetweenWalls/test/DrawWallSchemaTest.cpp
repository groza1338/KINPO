#include <gtest/gtest.h>
#include "funcs.h"

// Стены без воды
TEST(DrawWallSchemaTest, WallsWithoutWater) {
    vector<uint32_t> wall_heights = {3, 3, 3};
    vector<uint32_t> water_heights = {0, 0, 0};
    string expected_schema =
            "# # # \n"
            "# # # \n"
            "# # # \n";

    string schema = drawWallSchema(wall_heights, water_heights);

    EXPECT_EQ(schema, expected_schema);
}

// Две ямы между стенами разной высоты
TEST(DrawWallSchemaTest, TwoPitsBetweenWalls) {
    vector<uint32_t> wall_heights = {3, 1, 3, 1, 2};
    vector<uint32_t> water_heights = {0, 2, 0, 1, 0};
    string expected_schema =
            "# ~ #     \n"
            "# ~ # ~ # \n"
            "# # # # # \n";

    string schema = drawWallSchema(wall_heights, water_heights);

    EXPECT_EQ(schema, expected_schema);
}

// Одна стена
TEST(DrawWallSchemaTest, OneWall) {
    vector<uint32_t> wall_heights = {3};
    vector<uint32_t> water_heights = {0};
    string expected_schema =
            "# \n"
            "# \n"
            "# \n";

    string schema = drawWallSchema(wall_heights, water_heights);

    EXPECT_EQ(schema, expected_schema);
}

// Две стены
TEST(DrawWallSchemaTest, TwoWalls) {
    vector<uint32_t> wall_heights = {2, 3};
    vector<uint32_t> water_heights = {0, 0};
    string expected_schema =
            "  # \n"
            "# # \n"
            "# # \n";

    string schema = drawWallSchema(wall_heights, water_heights);

    EXPECT_EQ(schema, expected_schema);
}