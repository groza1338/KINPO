#include <fstream>
#include <iostream>
#include <sstream>
#include <unistd.h>

#include "Header.h"

int main(int argc, char *argv[]) {
    // Проверка на аргумент --test
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--test") {
            // Попытка запустить тесты из текущей директории
            std::vector<char*> args;
            args.push_back((char*)"./Gvozdkov_test");
            args.push_back(nullptr);
            execvp("./Gvozdkov_test", args.data());

            // Если первая попытка не удалась, пробуем запустить из поддиректории test
            args[0] = (char*)"../test/Gvozdkov_test";
            execvp("../test/Gvozdkov_test", args.data());

            // Если и эта попытка не удалась, выводим сообщение об ошибке
            std::cerr << "Не найден файл Gvozdkov_test";
            return 1;
        }
    }

    string input_file, output_file;
    setlocale(LC_ALL, "ru_RU.UTF-8");
    // Если передано недостаточно аргументов через командную строку
    if (argc < 3) {
        // Запросить у пользователя ввод имен файлов
        cout << "Введите путь к исходному файлу: ";
        cin >> input_file;
        cout << "Введите путь к конечному файлу: ";
        cin >> output_file;
    } else {
        // Использовать аргументы командной строки
        input_file = argv[1];
        output_file = argv[2];
    }

    // Зафиксируем начальное время
    // auto start = chrono::steady_clock::now();

    // Создаем вектор для хранения высот стен
    vector<uint32_t> numbers;
    string invalid_value;
    // Считываем данные из входного файла
    set<ErrorInfo> errors = readFromFile(input_file, numbers);

    // Обрабатываем все ошибки
    for (const auto &error : errors) {
        switch (error.type) {
            case ErrorType::OutOfRange:
                cerr << "Ошибка: Входной параметр \"" << error.detail << "\" не принадлежит диапазону [0..4294967295]."
                     << endl;
                break;
            case ErrorType::NotANumber:
                cerr << "Ошибка: Входной параметр \"" << error.detail << "\" не является натуральным числом" << endl;
                break;
            case ErrorType::ManyLinesInInputFile:
                cerr << "Ошибка: Во входном файле несколько строк." << endl;
                break;
            case ErrorType::NotTxtExtension:
                cerr << "Ошибка: Недопустимое расширение файла \"" << error.detail << "\"\nДопустимое расширение: \".txt\""
                     << endl;
                break;
            case ErrorType::FileNotFound:
                cerr << "Ошибка: Неверно указан файл с входными данными. Возможно, файл не существует.";
                break;
            case ErrorType::TooManyNumbersInFile:
                cerr << "Ошибка: Во входном файле слишком много чисел, убедитесь, что их <= 100" << endl;
                break;
            case ErrorType::NoNumbers:
                cerr << "Ошибка: Во входном файле нет чисел удовлетворяющих условию!" << endl;
                break;
        }
    }

    if (errors.empty()) {
        // Создаем вектор для хранения высот воды
        vector<uint32_t> water_heights(numbers.size(), 0);
        // Считаем объем воды
        auto water_volume = calculateWaterVolume(numbers, water_heights);
        // Создаем схему стен и воды
        auto water_schema = drawWallSchema(numbers, water_heights);
        // Записываем результат в выходной файл
        writeInFile(output_file, water_volume, water_schema);
    }
    // Зафиксируем конечное время
    // auto end = std::chrono::steady_clock::now();

    // Вычислим время выполнения
    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Выведем результат
    // std::cout << "Время выполнения: " << duration.count() << " мс" << std::endl;
    return 0;
}

/**
 * @brief Вычисляет количество воды, которое может быть удержано между стенами.
 *
 * @param[in] wall_heights Вектор высот стен.
 * @param[out] water_heights Вектор для хранения высот воды.
 * @return Общее количество воды, удерживаемой между стенами.
 */
uint32_t calculateWaterVolume(const vector<uint32_t> &wall_heights, vector<uint32_t> &water_heights) {
    uint8_t n = wall_heights.size();
    if (n <= 2) return 0; // Не может быть удержано воды

    vector<uint32_t> max_left(n, 0); // Массив максимальной высоты стены слева от текущей
    vector<uint32_t> max_right(n, 0); // Массив максимальной высоты стены справа от текущей

    // Вычисляем максимальную высоту стены слева от каждой стены
    uint32_t max_height = 0;
    for (int i = 0; i < n; ++i) {
        max_height = max(max_height, wall_heights[i]);
        max_left[i] = max_height;
    }

    // Вычисляем максимальную высоту стены справа от каждой стены
    max_height = 0;
    for (int i = n - 1; i >= 0; --i) {
        max_height = max(max_height, wall_heights[i]);
        max_right[i] = max_height;
    }

    uint32_t total_water = 0;

    // Вычисляем высоту воды между стенами
    for (int i = 0; i < n; ++i) {
        uint32_t water_level = min(max_left[i], max_right[i]) - wall_heights[i];
        if (water_level > 0) {
            total_water += water_level; // Увеличиваем общее количество воды
            water_heights[i] = water_level; // Сохраняем высоту воды для текущей стены
        } else {
            water_heights[i] = 0;
        }
    }

    return total_water;
}

/**
 * @brief Создает строку, представляющую схему стен и воды.
 *
 * @param[in] wall_heights Вектор высот стен.
 * @param[in] water_heights Вектор высот воды.
 * @return Строка, представляющая схему стен и воды.
 */
string drawWallSchema(const vector<uint32_t> &wall_heights, const vector<uint32_t> &water_heights) {
    string schema; // Строка для хранения схемы стен и воды

    if (wall_heights.empty() || water_heights.empty() || wall_heights.size() != water_heights.size()) {
        return schema;
    }

    size_t cols = wall_heights.size();
    uint32_t max_height = *max_element(wall_heights.begin(), wall_heights.end());
    vector<uint32_t> current_water_heights = water_heights; // Копируем water_heights для изменения

    // Заполняем схему воздухом и водой
    for (uint32_t row = max_height; row > 0; --row) {
        for (size_t col = 0; col < cols; ++col) {
            if (row <= wall_heights[col]) {
                schema.push_back('#'); // Заполняем стенами
            } else if (row <= wall_heights[col] + current_water_heights[col]) {
                schema.push_back('~'); // Заполняем водой
                --current_water_heights[col];
            } else {
                schema.push_back(' '); // Заполняем пустым пространством
            }
            schema.push_back(' '); // Добавляем пробел после каждого символа
        }
        schema.push_back('\n'); // Добавляем символ переноса строки между строками
    }

    return schema; // Возвращаем схему стен и воды
}

/**
 * @brief Извлекает расширение файла из переданного имени файла.
 *
 * @param[in] filename Имя файла.
 * @return Расширение файла, включая точку (например, ".txt"), или пустая строка, если расширение отсутствует.
 */
string getFileExtension(const string &filename) {
    // Находим позицию последней точки в строке
    size_t lastDotPos = filename.find_last_of('.');
    // Если точка не найдена, значит расширение отсутствует
    if (lastDotPos == string::npos) {
        return "";
    } else {
        // Извлекаем подстроку, начиная с позиции после последней точки
        string extension = '.' + filename.substr(lastDotPos + 1);
        return extension;
    }
}

/**
 * @brief Считывает данные из файла по указанному пути и сохраняет их в векторе numbers.
 *
 * @param[in] file_path Путь к файлу для чтения.
 * @param[out] numbers Вектор, в который будут сохранены данные из файла.
 * @return Вектор ошибок, если они есть, иначе пустой вектор.
 */
set<ErrorInfo> readFromFile(const string &file_path, vector<uint32_t> &numbers) {
    set<ErrorInfo> errors;

    // Проверяем расширение файла
    if (const auto extension = getFileExtension(file_path); extension != ".txt") {
        errors.emplace(ErrorType::NotTxtExtension, extension);
    }

    // Открываем файл для чтения
    ifstream input_file(file_path);
    if (!input_file) {
        errors.emplace(ErrorType::FileNotFound);
        return errors;
    }

    // Считываем данные из файла
    string line;
    uint8_t line_count = 0;
    uint32_t numbers_count = 0;
    while (getline(input_file, line)) {
        line_count++;
        // Проверяем, что в файле только одна строка
        if (line_count > 1) {
            errors.emplace(ErrorType::ManyLinesInInputFile);
            continue;
        }
        // Обрабатываем каждое слово в строке
        istringstream iss(line);
        string word;
        while (iss >> word) {
            // Добавляем проверку на отрицательное число
            if (word[0] == '-') {
                // throw out_of_range("Negative number");
                errors.emplace(ErrorType::OutOfRange, word);
            }
            try {
                size_t pos = 0;
                // Парсим число
                uint64_t number = stoul(word, &pos);
                // Проверяем, не выходит ли число за пределы допустимого диапазона uint32_t
                if (number > numeric_limits<uint32_t>::max()) {
                    errors.emplace(ErrorType::OutOfRange, word);
                } else if (pos != word.size()) {
                    throw invalid_argument("Invalid characters after number");
                } else {
                    // Сохраняем число в векторе
                    numbers.push_back(number);
                    numbers_count++;
                    // Проверяем, что не считано слишком много чисел
                    if (numbers_count > 100) {
                        errors.emplace(ErrorType::TooManyNumbersInFile);
                    }
                }
            } catch (const std::invalid_argument &e) {
                // Если встречено некорректное слово, добавляем соответствующую ошибку
                errors.emplace(ErrorType::NotANumber, word);
            } catch (const out_of_range &e) {
                errors.emplace(ErrorType::OutOfRange, word);
            }
        }
    }
    if (numbers_count == 0) {
        errors.emplace(ErrorType::NoNumbers);
    }
    input_file.close();
    return errors;
}

/**
 * @brief Записывает данные в файл по указанному пути.
 *
 * @param[in] file_path Путь к файлу для записи.
 * @param[in] water_volume Объем воды.
 * @param[in] wall_schema Строка схемы стен и воды.
 */
void writeInFile(const string &file_path, uint32_t water_volume, const string &wall_schema) {
    ofstream output_file(file_path);
    if (!output_file) {
        cerr
                << "Ошибка: Неверно указан файл для выходных данных. Возможно, указанного расположения не существует или нет прав на запись."
                << endl;
        return;
    }

    // Записываем переданные данные в файл
    output_file << water_volume << endl << wall_schema << endl;

    output_file.close(); // Закрываем файл
    // cout << "Успех!" << endl;
}