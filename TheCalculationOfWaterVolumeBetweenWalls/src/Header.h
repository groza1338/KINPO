#ifndef GVOZDKOV_HEADER_H
#define GVOZDKOV_HEADER_H

#include <vector>
#include <string>
#include <set>
#include <cstdint>


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
    ErrorType type;
    string detail;

    explicit ErrorInfo(ErrorType t, string d = "") : type(t), detail(std::move(d)) {}

    bool operator<(const ErrorInfo &other) const {
        return type < other.type || (type == other.type && detail < other.detail);
    }
};

uint32_t calculateWaterVolume(const vector<uint32_t> &wall_heights, vector<uint32_t> &water_heights);

void writeInFile(const string &file_path, uint32_t water_volume, const string &wall_schema);

string drawWallSchema(const vector<uint32_t> &wall_heights, const vector<uint32_t> &water_heights);

string getFileExtension(const string &filename);

set<ErrorInfo> readFromFile(const string &file_path, vector<uint32_t> &numbers);

#endif //GVOZDKOV_HEADER_H
