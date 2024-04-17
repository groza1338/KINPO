#ifndef GVOZDKOV_HEADER_H
#define GVOZDKOV_HEADER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
enum ErrorType {
    ManyLinesInInputFile,
    NoError,
    NotANumber,
    OutOfRange,
    NotTxtExtension,
    FileNotFound,
    TooManyNumbersInFile
};

string calculateWaterVolume(const vector<uint32_t>& wall_heights);

void writeInFile(const string &file_path, string water);

string getFileExtension(const string& filename);

ErrorType readFromFile(const string& file_path, string& invalid_value, vector<uint32_t>& input_values);

#endif //GVOZDKOV_HEADER_H
