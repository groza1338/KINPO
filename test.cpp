#include <iostream>
#include <vector>

using namespace std;

// Функция предназначенная для нахождения всех уникальных сумм натуральных чисел, которые равны начальному натуральному числу.
vector<vector<int>> findSumCombinations(int N)
{
    // Инициализируем вектор, содержащий все возможные комбинации натуральных чисел
    vector<vector<vector<int>>> sumCombination (N + 1);

    sumCombination[0] = { {} };

    // Для каждого числа в диапазоне от 1 до данного натурального числа
    for (int i = 1; i <= N; ++i) {
        // Для каждого числа из диапазона находим комбинации сумм чисел, дающих сумму равную текущему числу
        for (int j = i; j <= N; ++j) {
            // Для каждой комбинации, дающей сумму равной (j - i)
            for (auto& comb : sumCombination[j - i]) {
                // Если комбинация пустая или последнее число меньше или равно текущему рассматриваему числу
                if (comb.empty() || comb.back() <= i) {
                    // Добавляем комбинацию (j - i) с числом i в sumCombination[j]
                    sumCombination[j].push_back(comb);
                    sumCombination[j].back().push_back(i);
                }
            }
        }
    }

    // Возвращаем все комбинации, дающие сумму N
    return sumCombination[N];
}

void printCombinations(const vector<vector<int>>& combinations) {
    // Перебираем все комбинации в обратном порядке
    for (int i = combinations.size() - 1; i >= 0; --i) {
        // Выводим открывающую фигурную скобку перед каждой комбинацией
        cout << "{";

        // Выводим каждую комбинацию в обратном порядке
        for (int j = combinations[i].size() - 1; j >= 0; --j) {
            cout << combinations[i][j];
            // Добавляем запятую после каждого числа, кроме последнего
            if (j != 0) {
                cout << ", ";
            }
        }
        // Выводим закрывающую фигурную скобку после каждой комбинации
        cout << "}";

        // Выводим закрывающую фигурную скобку после каждой комбинации
        cout << "\n";
    }
}


int main() {
    // Запрос у пользователя натурального числа N
    int N;
    cout << "Input number N (1 <= N <= 100): ";
    cin >> N;

    // Находим все возможные комбинации сумм чисел, дающих сумму N
    vector<vector<int>> combinations = findSumCombinations(N);

    // Выводим все комбинации
    printCombinations(combinations);

    return 0;
}
