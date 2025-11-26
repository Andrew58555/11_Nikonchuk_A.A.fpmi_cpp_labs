#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>


std::vector<int32_t> ReadNumbersFromFile(const std::filesystem::path& file) {
    const std::string filename = file.native();

    if (!std::filesystem::exists(file)) {
        throw "Error: File \"" + filename + "\" does not exist...";
    }

    if (std::filesystem::is_empty(file)) {
        throw ("Error: Could not read file content. File \"" + filename + "\" is empty...");
    }

    std::ifstream in(file);
    if (!in.is_open()) {
        throw ("Error: Could not open file \"" + filename + "\"...");
    }

    std::vector<int32_t> v;
    
    int32_t x;
    while (in >> x) {
        v.push_back(x);
    }
    
    in.close();
    return v;
}


void WriteSumToFile(const std::filesystem::path& file, int64_t sum) {
    std::ofstream out(file);
    if (!out.is_open()) {
        throw ("Error: Could not open file \"" + file.native() + "\"...");
    }

    out << sum;
    out.close();
}

void PrintVector(const std::vector<int32_t>& vector) {
    for (size_t i = 0; i < vector.size(); ++i) {
        std::cout << vector[i] << ' ';
    }
    std::cout << std::endl;
}


int main() {
    
    // namespace fs = std::filesystem;
    
    const std::filesystem::path input_file{"input.txt"};
    const std::filesystem::path output_file{"output.txt"};
    try {    

        std::vector<int32_t> numbers = ReadNumbersFromFile(input_file);
        std::cout << "File " << std::quoted(input_file.c_str()) << " contents:\n"; 
        std::cout << "------------------------------------\n";
        PrintVector(numbers);
        std::cout << "------------------------------------\n";

        int64_t sum = std::accumulate(numbers.begin(), numbers.end(), int64_t{});
        WriteSumToFile(output_file, sum);

        std::cout << "Data has been successfully written to "
                  << std::quoted(output_file.c_str()) << std::endl;

    } catch(const std::string& msg) {
        std::cerr << msg << std::endl;
        return 1;
    }

    return 0;
}
