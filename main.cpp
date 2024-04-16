#include "Header.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
#pragma clang diagnostic ignored "-Wc++11-extensions"

int main(int argc, char *argv[]) {
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
	string invalid_word;
	// Считываем данные из входного файла
	ErrorType error = readFromFile(input_file, invalid_word, numbers);
	switch (error) {
		case ErrorType::OutOfRange:
			cerr << "Ошибка: Входной параметр \"" << invalid_word << "\" не принадлежит диапазону [0..4294967295]."
				 << endl;
			break;
		case ErrorType::NotANumber:
			cerr << "Ошибка: Входной параметр \"" << invalid_word << "\" не является натуральным числом" << endl;
			break;
		case ErrorType::ManyLinesInInputFile:cerr << "Ошибка: Во входном файле несколько строк." << endl;
			break;
		case ErrorType::NotTxtExtension:
			cerr << "Ошибка: Недопустимое расширение файла \"" << invalid_word << "\"\nДопустимое расширение: \".txt\""
				 << endl;
			break;
		case ErrorType::BadFile:cerr << "Ошибка: Неверно указан файл с входными данными. Возможно, файл не существует.";
			break;
		case ErrorType::TooManyNumbersInFile:
			cerr << "Ошибка: Во входном файле слишком много чисел, убедитесь, что их <= 100" << endl;
			break;
		case ErrorType::NoError:
			// Записываем результат в выходной файл
			string wallSchema;
			writeInFile(output_file, calculateWaterVolume(numbers, wallSchema), wallSchema);
			break;
	}
	return 0;
}

/**
 * @brief Функция calculateWaterVolume вычисляет количество воды, которое может быть удержано между стенами.
 * Также создает рисунок стены и воды.
 *
 * @param height Массив высот стен.
 * @param[out] wall_drawing Рисунок стены и воды.
 * @return Количество воды, которое может быть удержано между стенами.
 */
uint32_t calculateWaterVolume(const vector<uint32_t> &height, string &wall_drawing) {
	uint32_t n = height.size();
	if (n==0) return 0; // Если массив пустой, возвращаем 0

	// Создаем векторы для хранения максимальной высоты стен слева и справа от каждой позиции
	vector<uint32_t> left_max(n), right_max(n);
	uint32_t water_trapped = 0; // Переменная для хранения общего количества воды, которое может быть удержано

	// Находим максимальную высоту стены слева от каждой позиции
	left_max[0] = height[0];
	for (uint32_t i = 1; i < n; ++i) {
		left_max[i] = max(left_max[i - 1], height[i]);
	}

	// Находим максимальную высоту стены справа от каждой позиции
	right_max[n - 1] = height[n - 1];
	for (int64_t i = n - 2; i >= 0; --i) {
		right_max[i] = max(right_max[i + 1], height[i]);
	}

	wall_drawing = ""; // Строка для рисунка стены и воды

	// Проходимся по высотам, начиная с самой высокой
	for (int64_t row = *max_element(height.begin(), height.end()); row >= 1; --row) {
		string row_str; // Строка для хранения текущей строки рисунка

		// Проходимся по каждой стене в текущей строке
		for (uint32_t col = 0; col < n; ++col) {
			if (height[col] >= row) {
				row_str += "# "; // Если высота стены больше или равна текущему уровню, добавляем '#' к рисунку
			} else {
				// Если высота стены меньше текущего уровня, но слева и справа от нее есть стены, добавляем '~' к рисунку и увеличиваем общее количество воды
				if (col > 0 && col < n - 1 && left_max[col] >= row && right_max[col] >= row) {
					row_str += "~ ";
					++water_trapped;
				} else {
					row_str += "  "; // Если нет стен слева и/или справа, добавляем пробелы к рисунку
				}
			}
		}
		wall_drawing += row_str + "\n"; // Добавляем текущую строку к рисунку стены и воды
	}

	return water_trapped; // Возвращаем общее количество воды, которое может быть удержано между стенами
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
	if (lastDotPos==string::npos) {
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
 * @param invalid_word Некорректное слово, встреченное в файле.
 * @param numbers Вектор, в который будут сохранены данные из файла.
 * @return ErrorType Тип ошибки (если есть) или NoError, если ошибок не было.
 */
ErrorType readFromFile(const string &file_path, string &invalid_word, vector<uint32_t> &numbers) {
	// Проверяем, имеет ли файл правильное расширение
	if (const auto extension = getFileExtension(file_path); extension!=".txt") {
		invalid_word = extension;
		return ErrorType::NotTxtExtension;
	}
	ifstream input_file(file_path);
	// Проверяем, успешно ли открыт файл
	if (!input_file) {
		return ErrorType::BadFile;
	}

	string line;
	uint8_t line_count = 0;
	uint32_t numbers_count = 0;
	while (getline(input_file, line)) {
		line_count++;
		if (line_count > 1) {
			input_file.close();
			return ErrorType::ManyLinesInInputFile;
		}
		istringstream iss(line);
		string word;
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
				if (number < numeric_limits<uint32_t>::min()) {
					invalid_word = word;
					input_file.close();
					return ErrorType::OutOfRange;
				}
				numbers.push_back(number);
				numbers_count++;
				if (numbers_count > 100) {
					input_file.close();
					return ErrorType::TooManyNumbersInFile;
				}
			}
			catch (const std::invalid_argument &e) {
				// Если встречено некорректное слово, возвращаем соответствующую ошибку
				invalid_word = word;
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
 * @param water Данные, которые будут записаны в файл.
 */
void writeInFile(const string &file_path, const uint32_t water, const string &walls) {
	ofstream output_file(file_path);
	if (!output_file) {
		cerr
			<< "Ошибка: Неверно указан файл для выходных данных. Возможно, указанного расположения не существует или нет прав на запись."
			<< endl;
		return;
	}

	output_file << water << endl << walls << endl; // Записываем данные в файл
	output_file.close(); // Закрываем файл
	cout << "Успех!" << endl;
}

#pragma clang diagnostic pop