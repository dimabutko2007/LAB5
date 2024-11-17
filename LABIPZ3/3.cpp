#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

void checkValidInput1(double& value) {
    if (cin.fail()) {
        throw invalid_argument("Помилка: введено некоректне значення.");
    }
}

void checkValidInput2(int& value) {
    if (cin.fail()) {
        throw invalid_argument("Помилка: введено некоректне значення.");
    }
}

void checkValidParams(double a, double b, double h, int n) {
    if (a >= b) {
        throw logic_error("Помилка: початок інтервалу a повинен бути меншим за кінець інтервалу b.");
    }
    if (h <= 0) {
        throw logic_error("Помилка: крок h повинен бути більше 0.");
    }
    if (n < 4) {
        throw logic_error("Помилка: n повинно бути 4 та більше.");
    }
}

double calculate(double x, int n) {
    double y = 0;
    if (x < 0) {
        y = 1;
        for (int j = 2; j <= n - 2; ++j) {
            y *= (j + 1);
        }
    }
    else {
        for (int i = 0; i <= n - 1; ++i) {
            double p = 1;
            for (int j = 0; j <= n - 1; ++j) {
                p *= (x + i + j * j);
            }
            y += p;
        }
    }
    return y;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    double a, b, h, x;
    int n;
    char saveToFile;
    try {
        cout << "Введіть початок інтервалу a: ";
        cin >> a;
        checkValidInput1(a);
        cout << "Введіть кінець інтервалу b (b > a): ";
        cin >> b;
        checkValidInput1(b);
        cout << "Введіть крок h (h > 0): ";
        cin >> h;
        checkValidInput1(h);
        cout << "Введіть значення n (n >= 4): ";
        cin >> n;
        checkValidInput2(n);
        checkValidParams(a, b, h, n);
        cout << "Чи бажаєте записати результати у файл? (+/-): ";
        cin >> saveToFile;
        ofstream file;
        if (saveToFile == '+') {
            file.open("результати.txt");
            if (!file) {
                throw runtime_error("Не вдалося відкрити файл для запису.");
            }
        }
        for (x = a; x <= b; x += h) {
            double y = calculate(x, n);
            cout << "Для x = " << x << ", y = " << y << endl;
            if (saveToFile == '+') {
                file << "Для x = " << x << ", y = " << y << endl;
            }
        }
        if (saveToFile == '+') {
            file.close();
            cout << "Результати записані у файл 'результати.txt'." << endl;
        }
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}