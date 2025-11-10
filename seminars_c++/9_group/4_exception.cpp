#include <iostream>

int64_t FindSumBetweenZeros(const int32_t* arr, int32_t size/*, int* ret*/) {

    int32_t first_zero_ind = -1;
    int32_t last_zero_ind = -1;

    for (int32_t i = 0; i < size; ++i) {
		if (arr[i] == 0) {
			first_zero_ind = i;
			break;
		}
	}

	for (int32_t i = size - 1; i >= 0; --i) {
		if (arr[i] == 0) {
			last_zero_ind = i;
			break;
		}
	}


    if (first_zero_ind == last_zero_ind) {
        if (first_zero_ind == -1) {
            // *ret = 1;
            // нет нулей
            throw "No zeros";
        } else {
            // *ret = 2;
            // один нуль
            throw "One zero";
        }
    }

    if (last_zero_ind - first_zero_ind == 1) {
        // *ret = 3;
        // два нуля рядом
        throw "There are no elements between zeros!";
    }

    int64_t sum = 0;

    for (int32_t i = first_zero_ind + 1; i < last_zero_ind; ++i) {
        sum += arr[i];
    }
    
    // *ret = 0;
    return sum;
}


int main() {
    
    // solution exists
    {
        const int32_t arr[] = {1, 0, 2, 3, 0, -5, 0, 5};
        const int32_t size = sizeof(arr) / sizeof(int32_t);
        
        //int ret;
        int64_t sum = FindSumBetweenZeros(arr, size/*, &ret*/);
        //if (ret == 0)
        std::cout << "Sum between first and last zeros is " << sum << "\n";
    }
    
    // no solution (there is only one zero in array)
    {
        const int32_t arr[] = {1, 0, 2, 3, -5, 5};
        const int32_t size = sizeof(arr) / sizeof(int32_t);
        try { 
            int64_t sum = FindSumBetweenZeros(arr, size); 
            std::cout << "Sum between first and last zeros is " << sum << "\n";
        } catch(const char* msg) {
            std::cerr << msg << '\n';
        }
    }

    return 0;
}
