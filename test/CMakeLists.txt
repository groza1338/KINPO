# Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# Имя проекта для тестов
project(Gvozdkov_test)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)

# Указываем пути к заголовочным файлам
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../src)

# Добавляем Google Test как подмодуль
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/googletest googletest)

# Добавляем исполняемый файл для тестов
add_executable(Gvozdkov_test
        CalculateWaterVolumeTest.cpp
        DrawWallSchemaTest.cpp
        funcs.cpp
)

# Линкуем Google Test и pthread
target_link_libraries(Gvozdkov_test gtest gtest_main pthread)

# Определяем каталоги для заголовочных файлов
target_include_directories(Gvozdkov_test PUBLIC ${CMAKE_SOURCE_DIR}/src)

# Включаем тестирование
enable_testing()

# Регистрация тестов
add_test(NAME CalculateWaterVolumeTest COMMAND Gvozdkov_test)
add_test(NAME DrawWallSchemaTest COMMAND Gvozdkov_test)
