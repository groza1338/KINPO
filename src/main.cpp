#include "Header.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
#pragma clang diagnostic ignored "-Wc++11-extensions"

int main(int argc, char *argv[]) {
    // Зафиксируем начальное время
    auto start = chrono::steady_clock::now();
    string input_file, output_file;

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

    // Создаем вектор для хранения высот стен
    vector <u_int32_t> numbers;
    string invalid_value;
    // Считываем данные из входного файла
    ErrorType error = readFromFile(input_file, invalid_value, numbers);
    switch (error) {
        case ErrorType::OutOfRange:
            cerr << "Ошибка: Входной параметр \"" << invalid_value << "\" не принадлежит диапазону [0..4294967295]."
                 << endl;
            break;
        case ErrorType::NotANumber:
            cerr << "Ошибка: Входной параметр \"" << invalid_value << "\" не является натуральным числом" << endl;
            break;
        case ErrorType::ManyLinesInInputFile:
            cerr << "Ошибка: Во входном файле несколько строк." << endl;
            break;
        case ErrorType::NotTxtExtension:
            cerr << "Ошибка: Недопустимое расширение файла \"" << invalid_value << "\"\nДопустимое расширение: \".txt\""
                 << endl;
            break;
        case ErrorType::BadFile:
            cerr << "Ошибка: Неверно указан файл с входными данными. Возможно, файл не существует.";
            break;
        case ErrorType::TooManyNumbersInFile:
            cerr << "Ошибка: Во входном файле слишком много чисел, убедитесь, что их <= 100" << endl;
            break;
        case ErrorType::NoError:
            // Записываем результат в выходной файл
            string wallSchema;
            writeInFile(output_file, calculateWaterVolume(numbers), '\n', drawWallSchema(numbers));
            break;
    }
    // Зафиксируем конечное время
    auto end = std::chrono::steady_clock::now();

    // Вычислим время выполнения
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Выведем результат
    std::cout << "Время выполнения: " << duration.count() << " мс" << std::endl;
    return 0;
}

/**
 * @brief Функция calculateWaterVolume вычисляет количество воды, которое может быть удержано между стенами.
 * Также создает рисунок стены и воды.
 *
 * @param wall_heights Массив высот стен.
 * @return Количество воды, которое может быть удержано между стенами.
 */
uint32_t calculateWaterVolume(const vector <uint32_t> &wall_heights) {
    uint32_t n = wall_heights.size();
    if (n == 0 || n == 1 || n == 2) return 0;

    uint32_t water_trapped = 0;
    uint32_t left_max = 0, right_max = 0;
    uint32_t left = 0, right = n - 1;

    while (left < right) {
        if (wall_heights[left] < wall_heights[right]) {
            if (wall_heights[left] >= left_max) {
                left_max = wall_heights[left];
            } else {
                water_trapped += left_max - wall_heights[left];
            }
            ++left;
        } else {
            if (wall_heights[right] >= right_max) {
                right_max = wall_heights[right];
            } else {
                water_trapped += right_max - wall_heights[right];
            }
            --right;
        }
    }

    return water_trapped;
}

/**
 * @brief Функция drawWallSchema создает строку, представляющую рисунок стены и воды.
 *
 * @param heights Массив высот стен.
 * @return Строка, представляющая рисунок стены и воды.
 */
string drawWallSchema(const vector <uint32_t> &heights) {
    uint32_t n = heights.size();
    if (n == 0) return "";
    string wall_drawing;
    wall_drawing.clear(); // Очищаем строку рисунка
    if (n == 1) {
        for (int i = 0; i < heights[0]; i++) {
            wall_drawing.push_back('#');
            wall_drawing.push_back('\n');
        }
        return wall_drawing;
    }
    vector <uint32_t> left_max(n), right_max(n);

    // Предварительное вычисление максимумов слева и справа
    left_max[0] = heights[0];
    for (uint32_t i = 1; i < n; ++i) {
        left_max[i] = max(left_max[i - 1], heights[i]);
    }

    right_max[n - 1] = heights[n - 1];
    for (int64_t i = n - 2; i >= 0; --i) {
        right_max[i] = max(right_max[i + 1], heights[i]);
    }


    // Используем указатели для обхода вектора и флаги для управления потоком
    const uint32_t *left_max_ptr;
    const uint32_t *right_max_ptr;

    // Проходимся по высотам, начиная с самой высокой
    for (int64_t row = *max_element(heights.begin(), heights.end()); row >= 1; --row) {
        bool water_started = false; // Флаг, указывающий началась ли зона с водой

        // Сбрасываем указатели в начало векторов максимумов
        left_max_ptr = &left_max[0];
        right_max_ptr = &right_max[0];
        // Проходимся по каждой стене в текущей строке
        for (const uint32_t &h: heights) {
            if (h >= row) {
                wall_drawing.push_back(
                        '#'); // Добавляем '#' к рисунку, если высота стены больше или равна текущему уровню
                wall_drawing.push_back(' ');
                water_started = true;
            } else {
                if (water_started && *left_max_ptr >= row && *right_max_ptr >= row) {
                    wall_drawing.push_back(
                            '~'); // Добавляем '~' к рисунку, если началась зона с водой и есть стены слева и справа
                    wall_drawing.push_back(' ');
                } else {
                    wall_drawing.push_back(' '); // Добавляем пробел к рисунку, если нет стен слева и/или справа
                }
            }
            ++left_max_ptr;
            ++right_max_ptr;
        }
        wall_drawing.push_back('\n'); // Добавляем символ новой строки к рисунку
    }
    return wall_drawing;
}

/**
 * @brief Функция getFileExtension извлекает расширение файла из переданного имени файла.
 *
 * Эта функция находит позицию последней точки в имени файла и извлекает подстроку,
 * начиная с позиции после последней точки, что позволяет определить расширение файла.
 *
 * @param filename Имя файла.
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
 * @brief Функция readFromFile считывает данные из файла по указанному пути и сохраняет их в векторе numbers.
 *
 * Эта функция открывает указанный файл для чтения, считывает данные из него и сохраняет их в векторе numbers.
 * При возникновении ошибок в файле, функция возвращает соответствующий тип ошибки.
 *
 * @param file_path Путь к файлу для чтения.
 * @param invalid_value Некорректное значение, встреченное в файле.
 * @param numbers Вектор, в который будут сохранены данные из файла.
 * @return ErrorType Тип ошибки (если есть) или NoError, если ошибок не было.
 */
ErrorType readFromFile(const string &file_path, string &invalid_value, vector <uint32_t> &numbers) {
    // Проверяем расширение файла
    if (const auto extension = getFileExtension(file_path); extension != ".txt") {
        invalid_value = extension;
        return ErrorType::NotTxtExtension;
    }

    // Открываем файл для чтения
    ifstream input_file(file_path);
    if (!input_file) {
        return ErrorType::BadFile;
    }

    // Считываем данные из файла
    string line;
    uint8_t line_count = 0;
    uint32_t numbers_count = 0;
    while (getline(input_file, line)) {
        line_count++;
        // Проверяем, что в файле только одна строка
        if (line_count > 1) {
            input_file.close();
            return ErrorType::ManyLinesInInputFile;
        }
        // Обрабатываем каждое слово в строке
        istringstream iss(line);
        string word;
        while (iss >> word) {
            try {
                size_t pos = 0;
                // Парсим число
                uint64_t number;
                try {
                    number = stoul(word, &pos);
                }
                catch (const out_of_range &e) {
                    invalid_value = word;
                    input_file.close();
                    return ErrorType::OutOfRange;
                }
                // Проверяем, не выходит ли число за пределы допустимого диапазона uint32_t
                if (number > numeric_limits<uint32_t>::max() || number < numeric_limits<uint32_t>::min()) {
                    invalid_value = word;
                    input_file.close();
                    return ErrorType::OutOfRange;
                }
                // Проверяем, что число было считано полностью
                if (pos != word.size()) {
                    throw invalid_argument("Invalid characters after number");
                }
                // Сохраняем число в векторе
                numbers.push_back(number);
                numbers_count++;
                // Проверяем, что не считано слишком много чисел
                if (numbers_count > 100) {
                    input_file.close();
                    return ErrorType::TooManyNumbersInFile;
                }
            } catch (const std::invalid_argument &e) {
                // Если встречено некорректное слово, возвращаем соответствующую ошибку
                invalid_value = word;
                input_file.close();
                return ErrorType::NotANumber;
            }
        }
    }
    input_file.close();
    return ErrorType::NoError;
}

/**
 * @brief Функция writeInFile записывает данные в файл по указанному пути.
 *
 * Эта функция открывает указанный файл для записи и записывает в него переданные данные.
 *
 * @param file_path Путь к файлу для записи.
 * @param args Переменное количество аргументов для записи в файл.
 */
template<typename... Args>
void writeInFile(const string &file_path, Args &&... args) {
    ofstream output_file(file_path);
    if (!output_file) {
        cerr
                << "Ошибка: Неверно указан файл для выходных данных. Возможно, указанного расположения не существует или нет прав на запись."
                << endl;
        return;
    }

    // Записываем переданные данные в файл
    (output_file << ... << std::forward<Args>(args)) << endl;

    output_file.close(); // Закрываем файл
    cout << "Успех!" << endl;
}

#pragma clang diagnostic pop
