//
// Created by Сергей Гвоздков on 17.04.2024.
//

#ifndef GVOZDKOV_FUNCS_H
#define GVOZDKOV_FUNCS_H
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
    TooManyNumbersInFile
};

uint32_t calculateWaterVolume(const vector<uint32_t> &heights);

template<typename... Args>
void writeInFile(const string &file_path, Args&&... args);

string drawWallSchema(const vector<uint32_t> &heights);

string getFileExtension(const string &filename);

ErrorType readFromFile(const string &file_path, string &invalid_value, vector<uint32_t> &numbers);
#pragma clang diagnostic pop

#endif //GVOZDKOV_FUNCS_H