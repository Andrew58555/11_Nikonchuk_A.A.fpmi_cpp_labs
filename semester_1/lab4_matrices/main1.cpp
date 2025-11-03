#include <iostream>
#include <random>
#include <stdexcept>
#include <limits>

void deleteMatrix(int** arr, int size) {
    for (int i = 0; i < size; i++) {
        delete[] arr[i];
        arr[i] = nullptr;
    }
    delete[] arr;
    arr = nullptr;
}

int** createMatrix(int size) {
    int** arr = new int*[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = new int[size];
    }
    return arr;
}

int inputInt(const std::string& prompt) {
    int value;
    std::cout << prompt;
    if (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::runtime_error("Invalid input: expected integer");
    }
    if (std::cin.peek() != '\n' && std::cin.peek() != ' ') {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::runtime_error("Invalid input: expected integer, got floating point or other characters");
    }
    return value;
}

int inputIntWithValidation(const std::string& prompt, bool (*validator)(int) = nullptr) {
    int value = inputInt(prompt);
    if (validator && !validator(value)) {
        throw std::runtime_error("Input value does not satisfy the condition");
    }
    return value;
}

bool isPositive(int n) { return n > 0; }
bool isBinary(int n) { return n == 0 || n == 1; }

void fillRandomMatrix(int** arr, int size, std::mt19937& gen) {
    int a = inputIntWithValidation("Enter a: ");
    int b = inputIntWithValidation("Enter b: ");
    std::uniform_int_distribution<> dist(std::min(a, b), std::max(a, b));
    std::cout << "Random matrix:\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            arr[i][j] = dist(gen);
            std::cout << arr[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void fillManualMatrix(int** arr, int size) {
    std::cout << "Enter matrix:\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            arr[i][j] = inputInt("");
        }
    }
}

void processColumns(int** arr, int size) {
    for (int i = 0; i < size; i++) {
        int max_elem = -1e9;
        bool hasPositive = false;
        for (int j = 0; j < size; j++) {
            max_elem = std::max(max_elem, arr[j][i]);
            if (arr[j][i] > 0) hasPositive = true;
        }
        if (hasPositive) {
            std::cout << "In column " << i + 1 << " there is positive element\n";
        } else {
            std::cout << "Max element in column " << i + 1 << " is " << max_elem << "\n";
        }
    }
}

int countNegativeInTriangle(int** arr, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i + j + 1 >= size && arr[i][j] < 0) {
                count++;
            }
        }
    }
    return count;
}

void fillMatrix(int** arr, int size, std::mt19937& gen) {
    int choice = inputIntWithValidation(
        "Do you want to generate random matrix?\nEnter 1 for yes or 0 for no: ",
        isBinary
    );
    if (choice == 1) {
        fillRandomMatrix(arr, size, gen);
    } else {
        fillManualMatrix(arr, size);
    }
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    int** arr = nullptr;
    try {
        int n = inputIntWithValidation(
            "Enter n (size of square matrix): ",
            isPositive
        );
        arr = createMatrix(n);
        fillMatrix(arr, n, gen);
        processColumns(arr, n);
        int negativeCount = countNegativeInTriangle(arr, n);
        std::cout << "Number of negative elements in lower right triangle: " << negativeCount << "\n";
        deleteMatrix(arr, n);
    } catch (const std::exception& e) {
        if (arr != nullptr) {
            deleteMatrix(arr, 0);
        }
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
