#include <iostream>

int main() {

    int n;
    std::cout << "Enter n : ";
    if (!(std::cin >> n) || n < 1) {
        std::cout << "Error!";
        return 1;
    }
    int sum = 0, l = 1;
    for (int i = 1; i <= n; i++) {
        sum += l;
        l += 2;
    }
    std::cout << "sum = " << sum;
    return 0;
}
