#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Функция для нахождения всех возможных комбинаций сумм натуральных чисел
void findCombinations(int n) {
    // Стек для хранения текущей комбинации
    vector<int> stack;

    // Итеративный процесс для поиска комбинаций
    while (true) {
        int sum = 0;
        for (int num : stack) {
            sum += num;
        }

        // Если сумма равна n, выводим комбинацию
        if (sum == n) {
            cout << "{";
            for (int i = 0; i < stack.size(); ++i) {
                if (i > 0) {
                    cout << ", ";
                }
                cout << stack[i];
            }
            cout << "}\n";
        }

        // Находим следующее число для добавления в комбинацию
        int next = (stack.empty() ? 1 : stack.back() + 1);

        // Если следующее число больше n или стек пуст, завершаем процесс
        if (next > n || stack.empty()) {
            if (stack.empty()) {
                // Если стек пуст, значит мы проверили все возможные комбинации
                break;
            } else {
                // Удаляем последний элемент из стека и пробуем следующее число
                next = stack.back() + 1;
                stack.pop_back();
            }
        } else {
            // Добавляем следующее число в стек
            stack.push_back(next);
        }
    }
}

int main() {
    // Ввод числа N
    int n;
    cout << "Введите натуральное число N: ";
    cin >> n;

    auto start = high_resolution_clock::now();

    // Поиск и вывод комбинаций
    findCombinations(n);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Время выполнения: " << duration.count() << " микросекунд" << endl;

    return 0;
}
