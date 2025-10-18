#include <iostream>
#include <random>

void deleteMatrix(int** arr, int size) {
    for (int i = 0; i < size; i++) {
        delete[] arr[i];
        arr[i] = nullptr;
    }
    delete[] arr;
    arr = nullptr;
}

void rnd(int** arr, int size) {
    int a1, b1;
    std::cout << "Enter a : ";
    if (!(std::cin >> a1)) {
        std::cout << "Error";
        deleteMatrix(arr, size);
        std::exit(0);
    }
    std::cout << "Enter b : ";
    if (!(std::cin >> b1)) {
        std::cout << "Error";
        deleteMatrix(arr, size);
        std::exit(0);
    }
    std::mt19937 gen(45218965);
    int x = a1 + b1;
    a1 = std::min(a1, b1);
    b1 = x - a1;
    std::uniform_int_distribution<int> dist(a1, b1);
    std::cout << "Random matrix :\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int x1 = dist(gen);
            arr[i][j] = x1;
            std::cout << arr[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void enterMatrix(int** arr, int size) {
    std::cout << "Enter matrix :\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (!(std::cin >> arr[i][j])) {
                std::cout << "Error";
                deleteMatrix(arr, size);
                std::exit(0);
            }
        }
    }
}

int main() {
    int n;
    std::cout << "Enter n (length of square) : ";
    if (!(std::cin >> n) || n < 0) {
        std::cout << "Error";
        return 0;
    }
    int** arr = new int *[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = new int[n];
    }
    std::cout << "Do you want to generate random matrix?\n";
    std::cout << "Enter 1, if you want or 0, if not : ";
    int digit;
    if (!(std::cin >> digit) || (digit != 0 && digit != 1)) {
        std::cout << "Error";
        deleteMatrix(arr, n);
        return 0;
    }
    if (digit == 1) {
        rnd(arr, n);
    }
    else {
        enterMatrix(arr, n);
    }
    for (int i = 0; i < n; i++) {
        int max_elem = -1e4;
        for (int j = 0; j < n; j++) {
            max_elem = std::max(max_elem, arr[j][i]);
        }
        if (max_elem >= 0) {
            std::cout << "in the " << i + 1 << " cologne there is positive element\n";
        }
        else {
            std::cout << "max element in the " << i + 1 << " cologne is " << max_elem <<"\n";
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i + j + 1 >= n && arr[i][j] < 0) {
                ans++;
            }
        }
    }
    std::cout << "Answer is " << ans;
    deleteMatrix(arr, n);
    return 0;
}
