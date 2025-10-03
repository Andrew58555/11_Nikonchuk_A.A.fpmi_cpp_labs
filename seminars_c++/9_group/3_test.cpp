#include <iostream>
#include <cstring>

const int value = 7;

void PrintArray(const int* arr, size_t sz) {
    for (size_t i = 0 ; i < sz; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}

int main() {

    int arr[10] = {1, 2, 3, 4, 5};
    const int* c_ptr = &value;
    int* d_arr = new int[50];
    std::memcpy(d_arr, arr, 10 * sizeof(int));
    
    PrintArray(arr, 10);    
    PrintArray(d_arr, 10);  
    
    
    d_arr = c_ptr;
    c_ptr = nullptr;
    arr = c_ptr; // c_ptr = arr

    delete[] d_arr;
    return 0;
}
