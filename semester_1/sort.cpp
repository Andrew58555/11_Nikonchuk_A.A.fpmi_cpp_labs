#include <iostream>

void Enter(int* arr, int size) {
    std::cout << "Enter " << size << " elements of array\n";
    for (int i = 0; i < size; ++i) {
        if (!(std::cin >> arr[i])) {
            std::cout << "Error";
            delete[] arr;
            arr = nullptr;
            exit(1);
        }
    }
}

void BubbleSort(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (abs(arr[j]) > abs(arr[j + 1])) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    int n;
    std::cout << "Enter n : ";
    if (!(std::cin >> n) || n < 1) {
        std::cout << "Error";
        return 1;
    }
    int *arr = new int [n];
    Enter(arr, n);
    BubbleSort(arr, n);
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    delete[] arr;
    arr = nullptr;
    return 0;
}
