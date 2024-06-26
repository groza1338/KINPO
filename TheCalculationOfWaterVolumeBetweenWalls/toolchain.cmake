# Путь к компилятору C и C++
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)

# Определите флаги компилятора и линкера
set(CMAKE_C_FLAGS "-static")
set(CMAKE_CXX_FLAGS "-static")
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")

# Укажите путь к поиску библиотек и заголовков
set(CMAKE_FIND_ROOT_PATH /usr/local/Cellar/mingw-w64/x86_64-w64-mingw32)

# Задайте пути поиска
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
