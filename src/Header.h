#ifndef GVOZDKOV_HEADER_H
#define GVOZDKOV_HEADER_H

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
enum class ErrorType {
    ManyLinesInInputFile,
    NotANumber,
    OutOfRange,
    NotTxtExtension,
    FileNotFound,
    TooManyNumbersInFile,
    NoNumbers,
};

struct ErrorInfo {
    ErrorType error_type;
    string invalid_value;

    explicit ErrorInfo(ErrorType type, string value = "") : error_type(type), invalid_value(std::move(value)) {}
};

uint32_t calculateWaterVolume(const vector<uint32_t> &wall_heights, vector<uint32_t> &water_heights);

template<typename... Args>
void writeInFile(const string &file_path, Args&&... args);

string drawWallSchema(const vector<uint32_t> &wall_heights, vector<uint32_t> &water_heights);

string getFileExtension(const string &filename);

vector<ErrorInfo> readFromFile(const string &file_path, vector<uint32_t> &numbers);
#pragma clang diagnostic pop
#endif //GVOZDKOV_HEADER_H
