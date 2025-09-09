#include <bits/stdc++.h>

int main()
{
    int k;
    std::cout << "Enter k : ";
    if (!(std::cin >> k)) {
        std::cout << "Error!";
        std::exit(1);
    }
    if (k % 2 == 0) {
        int f = 1;
        for (int i = 2; i <= k; i += 2) {
            f *= i;
        }
        std::cout << f;
        return 0;
    }
    int f = 1;
    for (int i = 1; i <= k; i += 2) {
        f *= i;
    }
    std::cout << f;
    return 0;
}


