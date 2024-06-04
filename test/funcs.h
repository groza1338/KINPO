#ifndef GVOZDKOV_FUNCS_H
#define GVOZDKOV_FUNCS_H

#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <initializer_list>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
#pragma clang diagnostic ignored "-Wc++11-extensions"

using namespace std;

uint32_t calculateWaterVolume(const vector<uint32_t> &wall_heights, vector<uint32_t> &water_heights);

string drawWallSchema(const vector<uint32_t> &wall_heights, const vector<uint32_t> &water_heights);

#pragma clang diagnostic pop
#endif //GVOZDKOV_FUNCS_H
