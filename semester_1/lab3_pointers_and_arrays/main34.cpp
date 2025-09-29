#include <iostream>
#include <random>

int ind;
int n;
int max_a = 1;

void random4ik(int a[]) {
    int a1, b1;
    std::cout << "Enter a : ";
    if (!(std::cin >> a1)) {
        std::cout << "Error";
        delete[] a;
        a = nullptr;
        std::exit(1);
    }
    std::cout << "Enter b : ";
    if (!(std::cin >> b1)) {
        std::cout << "Error";
        delete[] a;
        a = nullptr;
        std::exit(1);
    }
    std::mt19937 gen(45218965);
    int x = a1 + b1;
    a1 = std::min(a1, b1);
    b1 = x - a1;
    std::uniform_int_distribution<int> dist(a1, b1);
    std::cout << "Random array : ";
    for (int i = 0; i < n; i++) {
        int x1 = dist(gen);
        a[i] = x1;
        if (a[i] > 0) {
            ind = i;
        }
        std::cout << a[i] << " ";
    }
}

void input(int a[]) {
    std::cout << "Enter " << n << " elements of array : ";
    for (int i = 0; i < n; i++) {
        if (!(std::cin >> a[i])) {
            std::cout << "Error";
            delete[] a;
            a = nullptr;
            std::exit(1);
        }
        if (a[i] > 0) {
            ind = i;
        }
    }
}

void SearchForPalindrom(int a[]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j + i < n; j++) {
            bool flag = true;
            for (int k = i; k <= i + j; k++) {
                if (a[k] != a[i + j - k + i]) {
                    flag = false;
                    break;
                }
            }
            if (flag && max_a < j + 1) {
                max_a = j + 1, ind = i;
            }
        }
    }
}

int main() {
    std::cout << "Enter n : ";
    if (!(std::cin >> n) || n < 1) {
        std::cout << "Error";
        return 1;
    }
    int *a = new int [n];
    std::cout << "Do you want to generate random array?\n";
    std::cout << "Enter 1, if you want or 0, if not : ";
    int ch;
    if (!(std::cin >> ch) || (ch != 0 && ch != 1)) {
        std::cout << "Error";
        delete[] a;
        a = nullptr;
        return 1;
    }
    if (ch == 1) {
        random4ik(a);
    }
    else {
        input(a);
    }
    int sum = 0;
    for (int i = 0; i < ind; i++) {
        sum += a[i];
    }
    std::cout << "sum = " << sum << "\n";
    SearchForPalindrom(a);
    std::cout << "max size of palindrome is " << max_a << "\npalindrome : ";
    for (int i = ind; i < ind + max_a; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\nEntering range...\n";
    int A, B;
    std::cout << "Enter a : ";
    if (!(std::cin >> A) || A < 0) {
        std::cout << "Error";
        delete[] a;
        a = nullptr;
        return 1;
    }
    std::cout << "Enter b : ";
    if (!(std::cin >> B) || B < A || B < 0) {
        std::cout << "Error";
        delete[] a;
        a = nullptr;
        return 1;
    }

    int write = 0;
    for (int i = 0; i < n; ++i) {
        if (abs(a[i]) < A || abs(a[i]) > B) {
            a[write++] = a[i];
        }
    }
    for (int i = write; i < n; ++i) {
        a[i] = 0;
    }
    std::cout << "Update array : ";
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " ";
    }
    delete[] a;
    a = nullptr;
    return 0;
}
