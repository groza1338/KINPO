#!/bin/bash

# Путь к папке сборки
BUILD_DIR="build"

# Перейти в папку сборки
cd $BUILD_DIR || exit

mv ./test/Gvozdkov_test.exe .

# Удалить все файлы, кроме исполняемых
find . ! -name 'Gvozdkov_run.exe' ! -name 'Gvozdkov_test.exe' -type f -exec rm -f {} +

# Удалить все папки, кроме текущей
find . -type d -not -path "." -exec rm -rf {} +

# Удалить оставшиеся временные файлы
rm -rf CMakeFiles CMakeCache.txt cmake_install.cmake Makefile