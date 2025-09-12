#include <bits/stdc++.h>

int main() {
    int n, m;
    std::cout << "Enter n : ";
    if (!(std::cin >> n) || n < 1) {
        std::cout << "Error!";
        std::exit(1);
    }
    std::cout << "Enter m : ";
    if (!(std::cin >> m) || m < 1) {
        std::cout << "Error!";
        std::exit(1);
    }
    std::cout << "Dividers : ";
    for (int i = 1; i <= std::min(n, m); i++) {
        if (n % i == 0 && m % i == 0)
            std::cout << i << " ";
    }
    return 0;
}



