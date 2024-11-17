#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

void checkValidInput1(double& value) {
    if (cin.fail()) {
        throw invalid_argument("�������: ������� ���������� ��������.");
    }
}

void checkValidInput2(int& value) {
    if (cin.fail()) {
        throw invalid_argument("�������: ������� ���������� ��������.");
    }
}

void checkValidParams(double a, double b, double h, int n) {
    if (a >= b) {
        throw logic_error("�������: ������� ��������� a ������� ���� ������ �� ����� ��������� b.");
    }
    if (h <= 0) {
        throw logic_error("�������: ���� h ������� ���� ����� 0.");
    }
    if (n < 4) {
        throw logic_error("�������: n ������� ���� 4 �� �����.");
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
        cout << "������ ������� ��������� a: ";
        cin >> a;
        checkValidInput1(a);
        cout << "������ ����� ��������� b (b > a): ";
        cin >> b;
        checkValidInput1(b);
        cout << "������ ���� h (h > 0): ";
        cin >> h;
        checkValidInput1(h);
        cout << "������ �������� n (n >= 4): ";
        cin >> n;
        checkValidInput2(n);
        checkValidParams(a, b, h, n);
        cout << "�� ������ �������� ���������� � ����? (+/-): ";
        cin >> saveToFile;
        ofstream file;
        if (saveToFile == '+') {
            file.open("����������.txt");
            if (!file) {
                throw runtime_error("�� ������� ������� ���� ��� ������.");
            }
        }
        for (x = a; x <= b; x += h) {
            double y = calculate(x, n);
            cout << "��� x = " << x << ", y = " << y << endl;
            if (saveToFile == '+') {
                file << "��� x = " << x << ", y = " << y << endl;
            }
        }
        if (saveToFile == '+') {
            file.close();
            cout << "���������� ������� � ���� '����������.txt'." << endl;
        }
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}