#include <bits/stdc++.h>
#define int long long

int32_t main()
{
    int n;
    std::cout << "Enter n : ";
    std::cin >> n;
    int a = n;
    int min_a = 11;
    while (a) {
        int c = a % 10;
        min_a = std::min(min_a, c);
        a /= 10;
    }
    int k = 0, res = 0;
    a = n;
    while (a) {
        int c = a % 10;
        if (c != min_a) {
            res += c * pow(10, k);
            k++;
        }
        a /= 10;
    }
    std::cout << res;
    return 0;
}
