#ifndef GVOZDKOV_HEADER_H
#define GVOZDKOV_HEADER_H

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
enum ErrorType {
    ManyLinesInInputFile,
    NoError,
    NotANumber,
    OutOfRange,
    NotTxtExtension,
    BadFile,
    TooManyNumbersInFile,
    NoNumbers,
};

uint32_t calculateWaterVolume(const vector<uint32_t> &wall_heights, vector<uint32_t> &water_heights);

template<typename... Args>
void writeInFile(const string &file_path, Args&&... args);

string drawWallSchema(const vector<uint32_t> &wall_heights, vector<uint32_t> &water_heights);

string getFileExtension(const string &filename);

ErrorType readFromFile(const string &file_path, string &invalid_value, vector<uint32_t> &numbers);
#pragma clang diagnostic pop
#endif //GVOZDKOV_HEADER_H
