#include <iostream> 


int* MergeWithAllocate(const int* first_array, int first_size,
                       const int* second_array, int second_size) { 
    
    // Handle edge cases 
    if (first_array == nullptr || second_array == nullptr) { 
        return nullptr;
    } 
    if (first_size < 0 || second_size < 0) {
        return nullptr;
    }

    // Allocate memory for the merged array 
    int total_size = first_size + second_size;
    int* result_array = new int[total_size];

    int i = 0; // index for first_array 
    int j = 0; // index for second_array
    int k = 0; // index for result_array 
    
    // Merge elements while both arrays have remaining elements 
    while (i < first_size && j < second_size) {
        if (first_array[i] <= second_array[j]) {
            result_array[k] = first_array[i];
            i++;
        } else { 
            result_array[k] = second_array[j];
            j++;
        } 
        k++;
    }

    // Copy remaining elements from first_array (if any) 
    while (i < first_size) {
        result_array[k] = first_array[i];
        i++;
        k++;
    } 

    // Copy remaining elements from second_array (if any) 
    while (j < second_size) {
        result_array[k] = second_array[j];
        j++;
        k++;
    }

    return result_array;
}


void MergeStd(const int* first_array, int first_size, 
              const int* second_array, int second_size,
              int* result_array) {
    
    // Handle edge cases 
    if (first_array == nullptr || second_array == nullptr || result_array == nullptr) {
        return;
    } 
    if (first_size < 0 || second_size < 0) {
        return;
    }
    
    int i = 0; // index for first_array
    int j = 0; // index for second_array
    int k = 0; // index for result_array 
    
    // Merge elements while both arrays have remaining elements 
    while (i < first_size && j < second_size) {
        if (first_array[i] <= second_array[j]) {
            result_array[k] = first_array[i];
            i++;
        } else {
            result_array[k] = second_array[j];
            j++;
        }
        k++;
    }
    
    // Copy remaining elements from first_array (if any) 
    while (i < first_size) {
        result_array[k] = first_array[i];
        i++;
        k++;
    } 
    
    // Copy remaining elements from second_array (if any) 
    while (j < second_size) {
        result_array[k] = second_array[j];
        j++;
        k++;
    }
}


void PrintArray(const int* arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}


int main() {
    
    const int arr1_sz = 4;
    int arr1[arr1_sz] = {1, 3, 5, 7};

    const int arr2_sz = 6;
    int arr2[arr2_sz] = {2, 4, 6, 8, 9, 10};

    const int result_sz = arr1_sz + arr2_sz;
    
    {
        std::cout << "merging with MergeWithAllocate:\n";
        int* result = MergeWithAllocate(arr1, arr1_sz, arr2, arr2_sz);
        PrintArray(result, result_sz);
        delete[] result; // !!!
    }
    
    std::cout << "--------------------------------------\n";
    
    {
        std::cout << "merging with MergeStd:\n";
        int result[result_sz]; // Pre-allocated result array
        MergeStd(arr1, arr1_sz, arr2, arr2_sz, result);
        PrintArray(result, result_sz);
    }
    
    return 0;
}


