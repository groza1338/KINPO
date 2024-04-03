#ifndef GVOZDKOV_HEADER_H
#define GVOZDKOV_HEADER_H
using namespace std;
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
enum ErrorType {
    NoError,
    NotANumber,
    OutOfRange
};
uint32_t trap(const vector<uint32_t >& height);
void writeInFile(const string& file_path, uint32_t data);
bool hasTxtExtension(const string& filename);
ErrorType readFromFile(const string& file_path, string& invalid_word, vector<uint32_t>& numbers);
#endif //GVOZDKOV_HEADER_H
