#ifndef GVOZDKOV_FUNCS_H
#define GVOZDKOV_FUNCS_H

#include <vector>
#include <string>
#include <cstdint>

using namespace std;

uint32_t calculateWaterVolume(const vector<uint32_t> &wall_heights, vector<uint32_t> &water_heights);

string drawWallSchema(const vector<uint32_t> &wall_heights, const vector<uint32_t> &water_heights);

#endif //GVOZDKOV_FUNCS_H
