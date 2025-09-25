#include <iostream>

const int MAX_LENGTH = 1000;

int main() {
    
    int arr[MAX_LENGTH];
    int* pa = arr; // array-to-pinter conversion
    // arr[2] = *(arr + 2)
    
    int n;
    std::cin >> n;
    
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    
    std::cout << '\n';

    for (int i = 0; i < n; ++i) {
        std::cout << arr[i];
    }

    return 0;
}
