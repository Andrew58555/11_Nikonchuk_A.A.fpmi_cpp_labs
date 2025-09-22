#include <iostream>
#include <random>

const int N = 1000;
int a[N][N];
int n;

void rnd() {
    int a1, b1;
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
    int x = a1 + b1;
    a1 = std::min(a1, b1);
    b1 = x - a1;
    std::uniform_int_distribution<int> dist(a1, b1);
    std::cout << "Random matrix :\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x1 = dist(gen);
            a[i][j] = x1;
            std::cout << a[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void enterMatrix() {
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

int main() {

    std::cout << "Enter n (length of square) : ";
    if (!(std::cin >> n) || n < 0) {
        std::cout << "Error";
        return 0;
    }
    std::cout << "Do you want to generate random matrix?\n";
    std::cout << "Enter 1, if you want or 0, if not : ";
    int ch;
    if (!(std::cin >> ch) || (ch != 0 && ch != 1)) {
        std::cout << "Error";
        return 0;
    }
    if (ch == 1) {
        rnd();
    }
    else {
        enterMatrix();
    }
    for (int i = 0; i < n; i++) {
        int cur = -1e4;
        for (int j = 0; j < n; j++) {
            cur = std::max(cur, a[j][i]);
        }
        if (cur >= 0)
            std::cout << "in the " << i + 1 << " cologne there is positive element\n";
        else
            std::cout << "max element in the " << i + 1 << " cologne is " << cur <<"\n";
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i + j + 1 >= n && a[i][j] < 0)
                ans++;
        }
    }
    std::cout << "Answer is " << ans;
    return 0;
}
