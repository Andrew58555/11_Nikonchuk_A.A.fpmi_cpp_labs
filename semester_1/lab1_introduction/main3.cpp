#include <bits/stdc++.h>
#define int long long

int32_t main()
{
    int n;
    std::cout << "Enter n : ";
    std::cin >> n;
    int k = 0;
    for (int i = 1; i <= n; i++) {
        k += pow(i, i);
    }
    std::cout << k;
    return 0;
}
