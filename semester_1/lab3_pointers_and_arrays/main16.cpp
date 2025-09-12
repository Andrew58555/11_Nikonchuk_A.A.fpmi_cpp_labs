#include <bits/stdc++.h>
const int N = 100000;
double a[N];

double rnd(){
    int x = rand();
    int y = rand() + 1;
    if (x % 2 == 0)
        return - 100 * x / (double) y;
    return 100 * x / (double) y;
}

int main() {
    int n;
    std::cout << "Enter n : ";
    if (!(std::cin >> n) || n < 1) {
        std::cout << "Error";
        std::exit(0);
    }
    std::cout << "Do you want to generate random array?\n";
    std::cout << "Enter 1, if you want or 0, if not : ";
    int ch;
    if (!(std::cin >> ch) || (ch != 0 && ch != 1)) {
        std::cout << "Error";
        std::exit(0);
    }
    double pr = 1.000;
    double min_a = 1e7, ind = 0;
    if (ch == 1) {
        std::cout << "Random array : ";
        for (int i = 0; i < n; i++) {
            a[i] = rnd();
            std::cout << a[i] << " ";
            if (a[i] > 0)
                pr *= a[i];
            if (a[i] < min_a)
                min_a = std::min(min_a, a[i]), ind = i;
        }
    }
    else {
        std::cout << "Enter n elements of array : ";
        for (int i = 0; i < n; i++) {
            if (!(std::cin >> a[i])) {
                std::cout << "Error";
                std::exit(0);
            }
            if (a[i] > 0)
                pr *= a[i];
            if (a[i] < min_a)
                min_a = std::min(min_a, a[i]), ind = i;
        }
    }

    double sum = 0;
    for (int i = 0; i < ind; i++) {
        sum += a[i];
    }
    bool fl;
    for (int i = 0; i < n - 1; i += 2) {
        fl = false;
        for (int j = 0; j < n - i - 1 && j + 2 < n; j += 2) {
            if (a[j] > a[j + 2]) {
                std::swap(a[j], a[j + 2]);
                fl = true;
            }
        }
        if (!fl)
            break;
    }
    for (int i = 1; i < n - 1; i += 2) {
        fl = false;
        for (int j = 1; j < n - i - 1 && j + 2 < n; j += 2) {
            if (a[j] > a[j + 2]) {
                std::swap(a[j], a[j + 2]);
                fl = true;
            }
        }
        if (!fl)
            break;
    }
    std::cout << "sum = " << sum << ", pr = " << pr << "\nArray : ";
    for (int i = 0; i < n; i++)
        std::cout << a[i] << " ";
    return 0;
}
