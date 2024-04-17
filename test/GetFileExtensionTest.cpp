#include <gtest/gtest.h>
#include "funcs.h"

// Тест для проверки getFileExtension
TEST(GetFileExtensionTest, TestNoExtension) {
    // Вызываем функцию с именем файла без расширения
    std::string filename = "myfile";
    std::string result = getFileExtension(filename);
    // Ожидаемый результат - пустая строка, так как расширение отсутствует
    ASSERT_EQ(result, "");
}

TEST(GetFileExtensionTest, TestWithExtension) {
    // Вызываем функцию с именем файла с расширением
    std::string filename = "myfile.txt";
    std::string result = getFileExtension(filename);
    // Ожидаемый результат - ".txt"
    ASSERT_EQ(result, ".txt");
}

TEST(GetFileExtensionTest, TestMultipleDots) {
    // Вызываем функцию с именем файла, содержащим несколько точек
    std::string filename = "my.file.name.txt";
    std::string result = getFileExtension(filename);
    // Ожидаемый результат - ".txt"
    ASSERT_EQ(result, ".txt");
}

// Тест для проверки работы с пустой строкой
TEST(GetFileExtensionTest, TestEmptyString) {
// Вызываем функцию с пустой строкой
    std::string filename = "";
    std::string result = getFileExtension(filename);
// Ожидаемый результат - пустая строка, так как строка пустая
    ASSERT_EQ(result, "");
}
