#include <bits/stdc++.h>

int main()
{
    int n;
    std::cout << "Enter n : ";
    if (!(std::cin >> n)) {
        std::cout << "Error!";
        std::exit(1);
    }
    int sum = 0, l = 1;
    for (int i = 1; i <= n; i++) {
        sum += l;
        l += 2;
    }
    std::cout << sum;
    return 0;
}

