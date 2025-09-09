#include <bits/stdc++.h>
#define int long long

int32_t main()
{
    int n, m;
    std::cout << "Enter n : ";
    std::cin >> n;
    std::cout << "Enter m : ";
    std::cin >> m;
    for (int i = 1; i <= std::min(n, m); i++) {
        if (n % i == 0 && m % i == 0)
            std::cout << i << " ";
    }
    return 0;
}
