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
    BadFile,
    TooManyNumbersInFile
};
uint32_t trap(const vector<uint32_t>& height, string& wall_drawing);
void writeInFile(const string &file_path, uint32_t water, const string& walls);
string getFileExtension(const string& filename);
ErrorType readFromFile(const string& file_path, string& invalid_word, vector<uint32_t>& numbers);
void drawWall(const vector<u_int32_t>& heights);
#endif //GVOZDKOV_HEADER_H
