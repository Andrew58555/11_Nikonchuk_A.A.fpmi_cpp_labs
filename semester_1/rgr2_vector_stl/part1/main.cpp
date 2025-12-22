#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <limits>

void inputVector(std::vector<int>& vec);
int calculateSum(const std::vector<int>& vec);
int countEqualTo(const std::vector<int>& vec, int value);
int countGreaterThan(const std::vector<int>& vec, int value);
void replaceZerosWithAverage(std::vector<int>& vec);
void addIntervalSumToAll(std::vector<int>& vec, int a, int b);
void replaceEvenAbsWithDifference(std::vector<int>& vec);
void removeDuplicateAbsoluteValues(std::vector<int>& vec);
void printVector(const std::vector<int>& vec, const std::string& message = "");

int main() {
    std::vector<int> vec;

    std::cout << "Enter numbers (enter any non-number to stop): ";
    inputVector(vec);

    if (vec.empty()) {
        std::cout << "Vector is empty!" << std::endl;
        return 0;
    }

    std::cout << "\n=== Results ===\n";

    int sum = calculateSum(vec);
    std::cout << "1. Sum of numbers = " << sum << std::endl;

    std::cout << "2. Total count of numbers = " << vec.size() << std::endl;

    int target;
    std::cout << "3. Enter number to count equals: ";
    std::cin >> target;
    std::cout << "   Count of numbers equal to " << target << " = " << countEqualTo(vec, target) << std::endl;

    std::cout << "4. Enter number for comparison: ";
    std::cin >> target;
    std::cout << "   Count of numbers greater than " << target << " = " << countGreaterThan(vec, target) << std::endl;

    replaceZerosWithAverage(vec);

    int a, b;
    std::cout << "6. Enter interval [a, b] (1-based indices): ";
    std::cin >> a >> b;
    addIntervalSumToAll(vec, a, b);

    replaceEvenAbsWithDifference(vec);

    removeDuplicateAbsoluteValues(vec);

    return 0;
}

void inputVector(std::vector<int>& vec) {
    int x;
    while (std::cin >> x) {
        vec.push_back(x);
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int calculateSum(const std::vector<int>& vec) {
    return std::accumulate(vec.begin(), vec.end(), 0);
}

int countEqualTo(const std::vector<int>& vec, int value) {
    return std::count(vec.begin(), vec.end(), value);
}

int countGreaterThan(const std::vector<int>& vec, int value) {
    return std::count_if(vec.begin(), vec.end(),
        [value](int num) { return num > value; });
}

void replaceZerosWithAverage(std::vector<int>& vec) {
    int sum = std::accumulate(vec.begin(), vec.end(), 0);
    int avg = sum / vec.size();

    std::cout << "5. Average (integer part) = " << avg << std::endl;

    std::replace_if(vec.begin(), vec.end(),
        [avg](int num) { return num == 0; },
        avg);

    printVector(vec, "   Vector after replacing zeros with average:");
}

void addIntervalSumToAll(std::vector<int>& vec, int a, int b) {
    int n = vec.size();

    a = std::clamp(a, 1, n) - 1;
    b = std::clamp(b, 1, n) - 1;

    if (a > b) {
        std::swap(a, b);
    }

    int interval_sum = std::accumulate(vec.begin() + a, vec.begin() + b + 1, 0);

    std::cout << "   Sum in interval [" << a + 1 << ", " << b + 1 << "] = " << interval_sum << std::endl;

    std::transform(vec.begin(), vec.end(), vec.begin(),
        [interval_sum](int num) { return num + interval_sum; });

    printVector(vec, "   Vector after adding interval sum to all elements:");
}

void replaceEvenAbsWithDifference(std::vector<int>& vec) {
    int min_el = *min_element(vec.begin(), vec.end());
    int max_el = *max_element(vec.begin(), vec.end());
    int diff = max_el - min_el;

    std::cout << "7. Min element = " << min_el << ", Max element = " << max_el << ", Difference = " << diff << std::endl;

    std::transform(vec.begin(), vec.end(), vec.begin(),
        [diff](int num) {
            return (std::abs(num) % 2 == 0) ? diff : num;
        });

    printVector(vec, "   Vector after replacing numbers with even absolute value:");
}

void removeDuplicateAbsoluteValues(std::vector<int>& vec) {
    std::vector<int> result;
    std::vector<int> seen_abs_values;

    std::copy_if(vec.begin(), vec.end(), std::back_inserter(result),
        [&seen_abs_values](int num) {
            int abs_val = std::abs(num);
            if (std::find(seen_abs_values.begin(), seen_abs_values.end(), abs_val) == seen_abs_values.end()) {
                seen_abs_values.push_back(abs_val);
                return true;
            }
            return false;
        });

    vec = std::move(result);
    printVector(vec, "8. Vector after removing numbers with duplicate absolute values (keeping first):");
}

void printVector(const std::vector<int>& vec, const std::string& message) {
    if (!message.empty()) {
        std::cout << message << std::endl;
    }

    std::cout << "   ";
    std::for_each(vec.begin(), vec.end(),
        [i = 0, &vec](int num) mutable {
            std::cout << num;
            if (++i < vec.size()) {
                std::cout << " ";
            }
        });
    std::cout << std::endl;
}
