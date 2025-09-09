#include <bits/stdc++.h>
#define int long long

int32_t main()
{
    int n;
    std::cout << "Enter n : ";
    std::cin >> n;
    int sum = 0, l = 1;
    for (int i = 1; i <= n; i++) {
        sum += l;
        l += 2;
    }
    std::cout << sum;
    return 0;
}
