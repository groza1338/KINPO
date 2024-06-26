cmake_minimum_required(VERSION 3.10)
project(Gvozdkov)

set(CMAKE_CXX_STANDARD 17)

# Указываем пути к заголовочным файлам
include_directories(src test)

# Добавляем исполняемый файл для основного приложения
add_executable(Gvozdkov_run src/main.cpp)

# Добавляем тесты
add_subdirectory(test)

# Добавляем зависимость от тестов, чтобы они всегда собирались
add_dependencies(Gvozdkov_run Gvozdkov_test)

# Установка для статической сборки
#set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")
