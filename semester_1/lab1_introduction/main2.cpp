#include <bits/stdc++.h>
#define int long long

int32_t main()
{
    int n;
    std::cout << "Enter n : ";
    std::cin >> n;
    int sum = 0;
    int pr = 1;
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 0)
            sum += i;
        else
            pr *= i;
    }
    std::cout << sum << " " << pr;
    return 0;
}
