#include <bits/stdc++.h>

int main()
{
    int n;
    std::cout << "Enter n : ";
    if (!(std::cin >> n)) {
        std::cout << "Error!";
        std::exit(1);
    }
    int k = 0;
    for (int i = 1; i <= n; i++) {
        k += pow(i, i);
    }
    std::cout << k;
    return 0;
}

