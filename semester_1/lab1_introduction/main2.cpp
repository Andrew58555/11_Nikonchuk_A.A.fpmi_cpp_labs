#include <iostream>

int main() {

    int n;
    std::cout << "Enter n : ";
    if (!(std::cin >> n) || n < 1) {
        std::cout << "Error!";
        return 1;
    }
    int sum = 0;
    int pr = 1;
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 0) {
            sum += i;
        }
        else {
            pr *= i;
        }
    }
    std::cout << "sum = " << sum << ", pr = " << pr;
    return 0;
}
