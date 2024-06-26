rm -rf build && echo "Папка старого билда удалена"
(mkdir build && cd build && cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake .. && make) && ./cleanup.sh && echo "Билд готов!"