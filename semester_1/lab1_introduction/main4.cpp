#include <iostream>

int main() {

    int k;
    std::cout << "Enter k : ";
    if (!(std::cin >> k) || k < 1) {
        std::cout << "Error!";
        return 1;
    }
    int subf = 1;
    if (k % 2 == 0) {
        for (int i = 2; i <= k; i += 2) {
            subf *= i;
        }
    }
    else {
        for (int i = 1; i <= k; i += 2) {
            subf *= i;
        }
    }
    std::cout << "subfactorial = " << subf;
    return 0;
}
