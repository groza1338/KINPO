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
    vector<u_int32_t> numbers;
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
        case ErrorType::NoNumbers:
            cerr << "Ошибка: Во входном файле нет чисел!" << endl;
            break;
        case ErrorType::NoError:
            // Создаем вектор для хранения высот воды
            vector<uint32_t> water_heights(numbers.size(), 0);
            // Записываем результат в выходной файл
            writeInFile(output_file, calculateWaterVolume(numbers, water_heights), '\n',
                        drawWallSchema(numbers, water_heights));
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
 *
 * @param wall_heights Массив высот стен.
 * @return Количество воды, которое может быть удержано между стенами.
 */
uint32_t calculateWaterVolume(const vector<uint32_t> &wall_heights, vector<uint32_t> &water_heights) {
    uint8_t n = wall_heights.size(); // Получаем количество стен
    if (n == 0 || n == 1 || n == 2) return 0; // Если стен нет или их меньше трех, вода не удерживается

    uint32_t water_trapped = 0; // Переменная для хранения количества удержанной воды
    uint32_t left_max = 0, right_max = 0; // Максимальные высоты слева и справа
    uint32_t left = 0, right = n - 1; // Индексы левой и правой стен

    // Проходим по массиву стен, пока индексы левой и правой стен не пересекутся
    while (left < right) {
        // Если высота левой стены меньше высоты правой
        if (wall_heights[left] < wall_heights[right]) {
            // Если высота левой стены больше или равна максимальной высоте слева,
            // обновляем максимальную высоту слева. Иначе добавляем количество удержанной воды.
            if (wall_heights[left] >= left_max) {
                left_max = wall_heights[left];
            } else {
                water_heights[left] = left_max - wall_heights[left];
                water_trapped += water_heights[left];
            }
            ++left; // Переходим к следующей левой стене
        } else {
            // Если высота правой стены больше или равна максимальной высоте справа,
            // обновляем максимальную высоту справа. Иначе добавляем количество удержанной воды.
            if (wall_heights[right] >= right_max) {
                right_max = wall_heights[right];
            } else {
                water_heights[right] = right_max - wall_heights[right];
                water_trapped += water_heights[right];
            }
            --right; // Переходим к следующей правой стене
        }
    }

    return water_trapped; // Возвращаем количество удержанной воды
}


/**
 * @brief Функция рисует схему стен и воды на основе высот стен.
 *
 * @param heights Вектор, содержащий высоты стен.
 * @return Строка, представляющая схему стен и воды.
 */
string drawWallSchema(const vector<uint32_t> &wall_heights, vector<uint32_t> &water_heights) {
    string schema; // Строка для хранения схемы стен и воды

    auto cols = wall_heights.size();
    auto rows = *max_element(wall_heights.begin(), wall_heights.end());

    vector<vector<char>> schema_array(rows, vector<char>(cols, ' ')); // Создаем пустой двумерный вектор

    // Заполняем схему воздухом и водой
    for (size_t col = 0; col < cols; ++col) { // Итерируемся по столбцам
        uint32_t maxHeight = wall_heights[col]; // Максимальная высота текущего столбца

        // Заполняем стены в текущем столбце до его максимальной высоты
        for (size_t row = 0; row < rows && row < maxHeight; ++row) {
            schema_array[row][col] = '#';
        }

        // Заполняем водой
        for (size_t row = maxHeight; row < rows && water_heights[col] > 0; ++row) {
            schema_array[row][col] = '~';
            --water_heights[col];
        }
    }

    // Преобразование двумерного вектора в строку
    for (const auto &row: schema_array) {
        for (char ch: row) {
            schema.push_back(ch); // Добавляем символ в строку
            schema.push_back(' '); // Добавляем пробел после каждого символа
        }
        schema.push_back('\n'); // Добавляем символ переноса строки между строками
    }

    return schema; // Возвращаем схему стен и воды
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
ErrorType readFromFile(const string &file_path, string &invalid_value, vector<uint32_t> &numbers) {
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
    if (numbers_count == 0) {
        input_file.close();
        return ErrorType::NoNumbers;
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
