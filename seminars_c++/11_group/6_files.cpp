#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

bool IsEmptyFile(std::ifstream& file) {
    return file.peek() == std::ifstream::traits_type::eof();
}

std::vector<int32_t> ReadDataFromFile(const std::string& filename) {

    std::ifstream in{filename};
    
    if (!in.is_open()) {
        throw ("Error: Could not open file \"" + filename + "\"");
    }

    if (IsEmptyFile(in)) {
        throw ("Error: file \"" + filename + "\" is empty!");
    }

    std::vector<int32_t> numbers;
    
    int32_t x;
    while ( in >> x ) {
        numbers.push_back(x);
    }
    
    in.close();
    return numbers;
}

double CalculateAverage(const std::vector<int32_t>& nums) {
    int64_t sum = std::accumulate(nums.begin(), nums.end(), int64_t{});
    return static_cast<double>(sum) / nums.size();
}

void WriteAvgToOutputFile(const std::string& filename, double value) {
    
    std::ofstream out{filename};

    if (!out.is_open()) {
        throw ("Error: Could not open file \"" + filename + "\"");
    }

    out << value;
    out.close();
}


void PrintVector(const std::vector<int32_t>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << ' ';
    }
    std::cout << std::endl;
}


int main() {

    const std::string empty_file{"empty.txt"};
    const std::string input_file{"intup.txt"};
    const std::string output_file{"output.txt"};
    
    try {
        std::vector<int32_t> numbers = ReadDataFromFile(empty_file);
#if 0
        std::cout << "--------------------\n";
        PrintVector(numbers);
        std::cout << "--------------------\n";
#endif
        double avg = CalculateAverage(numbers);
        WriteAvgToOutputFile(output_file, avg);
        std::cout << "Result has been written to "
                  << std::quoted(output_file) << '\n';
    } catch(const std::string& msg) {
        std::cerr << msg << std::endl;
    }

}
