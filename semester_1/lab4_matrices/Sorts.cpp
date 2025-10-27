#include <iostream>
#include <random>
#include <algorithm>

void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void reverseArray(int* arr, int n) {
    for (int i = 0; i < n / 2; i++) {
        std::swap(arr[i], arr[n - i - 1]);
    }
}

void bubbleSort(int* arr, int n, bool ascending) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (ascending ? arr[j] > arr[j + 1] : arr[j] < arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertionSort(int* arr, int n, bool ascending) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && (ascending ? arr[j] > key : arr[j] < key)) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(int* arr, int left, int mid, int right, bool ascending) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = new int[n1];
    int* R = new int[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (ascending ? L[i] <= R[j] : L[i] >= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    delete[] L;
    L = nullptr;
    delete[] R;
    R = nullptr;
}

void mergeSort(int* arr, int left, int right, bool ascending) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid, ascending);
    mergeSort(arr, mid + 1, right, ascending);
    merge(arr, left, mid, right, ascending);
}

void countingSort(int* arr, int n, bool ascending) {
    if (n == 0) return;
    int max_val = arr[0];
    int min_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) max_val = arr[i];
        if (arr[i] < min_val) min_val = arr[i];
    }
    int range = max_val - min_val + 1;
    int* count = new int[range]();
    int* output = new int[n];
    for (int i = 0; i < n; i++) {
        count[arr[i] - min_val]++;
    }
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i] - min_val] - 1] = arr[i];
        count[arr[i] - min_val]--;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    if (!ascending) {
        reverseArray(arr, n);
    }
    delete[] count;
    count = nullptr;
    delete[] output;
    output = nullptr;
}

int main() {
    int n;
    int choice, method, order_choice;
    std::cout << "Enter array size: ";
    if (!(std::cin >> n) || n <= 0) {
        std::cout << "Error: invalid array size!" << std::endl;
        return 1;
    }
    int* a = new int[n];
    std::cout << "Choose filling method:\n";
    std::cout << "1 - Manual input\n";
    std::cout << "2 - Random generation\n";
    if (!(std::cin >> choice)) {
        std::cout << "Error: invalid input!" << std::endl;
        delete[] a;
        a = nullptr;
        return 1;
    }
    if (choice == 1) {
        std::cout << "Enter " << n << " elements: ";
        for (int i = 0; i < n; i++) {
            if (!(std::cin >> a[i])) {
                std::cout << "Error: invalid input!" << std::endl;
                delete[] a;
                a = nullptr;
                return 1;
            }
        }
    } else if (choice == 2) {
        int a1, b1;
        std::cout << "Enter a: ";
        if (!(std::cin >> a1)) {
            std::cout << "Error: invalid input!" << std::endl;
            delete[] a;
            a = nullptr;
            return 1;
        }
        std::cout << "Enter b: ";
        if (!(std::cin >> b1)) {
            std::cout << "Error: invalid input!" << std::endl;
            delete[] a;
            a = nullptr;
            return 1;
        }
        int x = a1 + b1;
        a1 = std::min(a1, b1);
        b1 = x - a1;
        std::mt19937 gen(45218965);
        std::uniform_int_distribution<int> dist(a1, b1);
        for (int i = 0; i < n; i++) {
            a[i] = dist(gen);
        }
    } else {
        std::cout << "Error: invalid choice!" << std::endl;
        delete[] a;
        return 1;
    }
    std::cout << "Original array: ";
    printArray(a, n);
    std::cout << "Choose sorting order:\n";
    std::cout << "1 - Ascending\n";
    std::cout << "2 - Descending\n";
    if (!(std::cin >> order_choice) || (order_choice != 1 && order_choice != 2)) {
        std::cout << "Error: invalid choice!" << std::endl;
        delete[] a;
        return 1;
    }
    bool ascending = (order_choice == 1);
    std::cout << "Choose sorting method:\n";
    std::cout << "1 - Bubble sort\n";
    std::cout << "2 - Insertion sort\n";
    std::cout << "3 - Merge sort\n";
    std::cout << "4 - Counting sort\n";
    if (!(std::cin >> method)) {
        std::cout << "Error: invalid input!" << std::endl;
        delete[] a;
        return 1;
    }
    switch (method) {
        case 1:
            bubbleSort(a, n, ascending);
            break;
        case 2:
            insertionSort(a, n, ascending);
            break;
        case 3:
            mergeSort(a, 0, n - 1, ascending);
            break;
        case 4:
            countingSort(a, n, ascending);
            break;
        default:
            std::cout << "Error: invalid method!" << std::endl;
            delete[] a;
            a = nullptr;
            return 1;
    }
    std::cout << "Sorted array: ";
    printArray(a, n);
    delete[] a;
    a = nullptr;
    return 0;
}
