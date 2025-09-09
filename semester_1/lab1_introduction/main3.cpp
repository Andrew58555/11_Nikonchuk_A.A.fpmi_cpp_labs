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
//if n == 5, then the answer will be 3413
//if n == 6, then the answer will be 50069
//if n == 10, then the answer will be 10405071317
//if n > 15, then the answer will be outside the data type and output space debris

