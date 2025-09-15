#include <iostream>
#include <random>

const int N = 1000;
double a[N][N];

int main() {

    int n;
    std::cout << "Enter n (length of square) :";
    if (!(std::cin >> n) || n < 0) {
        std::cout << "Error";
        std::exit(0);
    }
    std::cout << "Do you want to generate random matrix?\n";
    std::cout << "Enter 1, if you want or 0, if not : ";
    int ch;
    if (!(std::cin >> ch) || (ch != 0 && ch != 1)) {
        std::cout << "Error";
        std::exit(0);
    }
    if (ch == 1) {
        double a1, b1;
        std::cout << "Enter a : ";
        if (!(std::cin >> a1)) {
            std::cout << "Error";
            std::exit(0);
        }
        std::cout << "Enter b : ";
        if (!(std::cin >> b1)) {
            std::cout << "Error";
            std::exit(0);
        }
        std::mt19937 gen(45218965);
        double x = a1 + b1;
        a1 = std::min(a1, b1);
        b1 = x - a1;
        std::uniform_real_distribution<double> dist(a1, b1);
        std::cout << "Random matrix : ";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                double x1 = dist(gen);
                a[i][j] = x1;
                std::cout << a[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
    else {
        std::cout << "Enter matrix :\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (!(std::cin >> a[i][j])) {
                    std::cout << "Error";
                    std::exit(0);
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        double rt = -1e4;
        for (int j = 0; j < n; j++) {
            rt = std::max(rt, a[j][i]);
        }
        if (rt >= 0)
            std::cout << "in the" << i + 1 << " cologne there is positive element\n";
        else
            std::cout << "max element in the " << i + 1 << " cologne is " << rt <<"\n";
    }
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i + j + 1 >= n && a[i][j] < 0)
                k++;
        }
    }
    std::cout << "Answer is " << k;
    return 0;
}
