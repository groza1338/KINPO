#include "Header.h"

int main(int argc, char* argv[]) {
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

    // Проверяем, имеют ли файлы правильное расширение
    if (!(hasTxtExtension(input_file))){
        cerr << input_file << " не является допустимым форматом" << endl;
        return 1;
    }
    if (!hasTxtExtension(output_file)){
        cerr << output_file << " не является допустимым форматом" << endl;
        return 1;
    }

    // Создаем вектор для хранения высот стен
    vector<u_int32_t> numbers;
    string invalid_word;
    // Считываем данные из входного файла
    ErrorType error = readFromFile(input_file, invalid_word, numbers);
    switch (error) {
        case ErrorType::OutOfRange:
            cerr << "Ошибка: Число " <<invalid_word<< " вне допустимого диапазона [0..4294967295]" << endl;
            break;
        case ErrorType::NotANumber:
            cerr << "Ошибка: Найдено слово - " << invalid_word << endl;
            break;
        case ErrorType::NoError:
            // Записываем результат в выходной файл
            writeInFile(output_file, trap(numbers));
            break;
    }
    return 0;
}


/**
 * @brief Функция trap вычисляет количество воды, которое может быть удержано между стенами.
 *
 * Эта функция реализует алгоритм, основанный на поиске максимальных высот стен слева и справа от каждой стены,
 * чтобы определить количество воды, которое может быть удержано над каждой стеной.
 *
 * @param height Массив высот стен.
 * @return Количество воды, которое может быть удержано между стенами.
 */
uint32_t trap(const vector<uint32_t>& height) {
    uint8_t n = height.size();
    if (n == 0) return 0; // Если массив пустой, возвращаем 0

    vector<uint32_t> max_left(n), max_right(n);

    // Находим максимальную высоту стены слева от текущей позиции
    max_left[0] = height[0];
    for (int i = 1; i < n; ++i) {
        max_left[i] = max(max_left[i - 1], height[i]); // Вычисляем максимум между текущей высотой стены и предыдущим максимумом слева
    }

    // Находим максимальную высоту стены справа от текущей позиции
    max_right[n - 1] = height[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        max_right[i] = max(max_right[i + 1], height[i]); // Вычисляем максимум между текущей высотой стены и предыдущим максимумом справа
    }

    uint32_t water_trapped = 0;
    // Находим объем воды, который может быть удержан над каждой стеной
    for (int i = 0; i < n; ++i) {
        water_trapped += min(max_left[i], max_right[i]) - height[i]; // Вычисляем количество воды над каждой стеной и суммируем
    }

    return water_trapped;
}


/**
 * @brief Функция readFromFile считывает данные из файла по указанному пути и сохраняет их в векторе numbers.
 *
 * Эта функция открывает указанный файл для чтения, считывает данные из него и сохраняет их в векторе numbers.
 * При возникновении ошибок в файле, функция возвращает соответствующий тип ошибки.
 *
 * @param file_path Путь к файлу для чтения.
 * @param invalid_word Некорректное слово, встреченное в файле.
 * @param numbers Вектор, в который будут сохранены данные из файла.
 * @return ErrorType Тип ошибки (если есть) или NoError, если ошибок не было.
 */
ErrorType readFromFile(const string& file_path, string& invalid_word, vector<uint32_t>& numbers) {
    ifstream input_file(file_path);
    // Проверяем, успешно ли открыт файл
    if (!input_file) {
        cerr << "Ошибка: Не удалось открыть файл для чтения!" << endl;
        return ErrorType::NoError;
    }

    string line;
    getline(input_file, line);

    istringstream iss(line);
    string word;
    // Читаем данные из файла
    while (iss >> word) {
        try {
            size_t pos;
            int64_t number = stoul(word, &pos);
            // Проверяем, не выходит ли число за пределы допустимого диапазона
            if (number > numeric_limits<uint32_t>::max()) {
                invalid_word = word;
                input_file.close();
                return ErrorType::OutOfRange;
            }
            if (number < numeric_limits<uint32_t>::min()){
                invalid_word = word;
                input_file.close();
                return ErrorType::OutOfRange;
            }
            numbers.push_back(number);
        } catch (const std::invalid_argument& e) {
            // Если встречено некорректное слово, возвращаем соответствующую ошибку
            invalid_word = word;
            input_file.close();
            return ErrorType::NotANumber;
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
 * @param data Данные, которые будут записаны в файл.
 */
void writeInFile(const string &file_path, const uint32_t data) {
    ofstream output_file(file_path);
    if (!output_file) {
        cerr << "Не удалось открыть файл для записи!" << endl;
        return;
    }

    output_file << data; // Записываем данные в файл
    output_file.close(); // Закрываем файл
    cout << "Успех!" << endl;
}


/**
 * @brief Проверяет, имеет ли файл расширение .txt.
 *
 * @param filename Имя файла.
 * @return true, если имя файла имеет расширение .txt, в противном случае - false.
 */
bool hasTxtExtension(const string& filename) {
    // Получаем длину строки
    size_t length = filename.length();

    // Если длина строки меньше 4 символов, то она не может содержать расширение .txt
    if (length < 4) {
        return false;
    }

    // Получаем подстроку с последних четырех символов
    string extension = filename.substr(length - 4);

    // Сравниваем полученную подстроку с .txt
    return extension == ".txt";
}