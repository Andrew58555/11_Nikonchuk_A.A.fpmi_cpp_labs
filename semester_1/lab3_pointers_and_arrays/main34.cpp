#include <bits/stdc++.h>
const int N = 100000;
int a[N];

int rnd() {
    int x = rand();
    if (x % 2 == 0)
        return - x;
    return x;
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
    int ind = 0;
    if (ch == 1) {
        std::cout << "Random array : ";
        for (int i = 0; i < n; i++) {
            a[i] = rnd();
            if (a[i] > 0)
                ind = i;
            std::cout << a[i] << " ";
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
                ind = i;
        }
    }
    int sum = 0;
    for (int i = 0; i < ind; i++) {
        sum += a[i];
    }
    std::cout << "sum = " << sum << "\n";
    int max_a = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j + i < n; j++) {
            bool flag = true;
            for (int k = i; k <= i + j; k++) {
                if (a[k] != a[i + j - k + i]) {
                    flag = false;
                    break;
                }
            }
            if (flag && max_a < j + 1)
                max_a = j + 1, ind = i;
        }
    }
    std::cout << "max size of palindrome is " << max_a << "\npalindrome : ";
    for (int i = ind; i < ind + max_a; i++)
        std::cout << a[i] << " ";
    std::cout << "\n";
    int A, B;
    std::cout << "Enter a : ";
    if (!(std::cin >> A)) {
        std::cout << "Error";
        std::exit(0);
    }
    std::cout << "Enter b : ";
    if (!(std::cin >> B) || B < A) {
        std::cout << "Error";
        std::exit(0);
    }
    int h = 0;
    std::cout << "Update array : ";
    for (int i = 0; i < n; i++) {
        if (abs(a[i]) < A or abs(a[i]) > B)
            std::cout << a[i] << " ";
        else
            h++;
    }
    for (int i = 0; i < h; i++) {
        std::cout << "0 ";
    }
    return 0;
}
