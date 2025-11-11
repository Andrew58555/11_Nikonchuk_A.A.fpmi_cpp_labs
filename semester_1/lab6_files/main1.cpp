#include <iostream>
#include <string>
#include <map>
#include <fstream>

bool isEmptyFile(std::ifstream& file) {
    return file.peek() == std::ifstream::traits_type::eof();
}

std::string readDataFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        throw std::string("Error: Could not open file \"") + filename + "\"";
    }

    if (isEmptyFile(in)) {
        throw std::string("Error: file \"") + filename + "\" is empty!";
    }

    std::string content;
    std::string line;
    while (getline(in, line)) {
        content += line + "\n";
    }
    if (!content.empty() && content.back() == '\n') {
        content.pop_back();
    }

    in.close();
    return content;
}

bool isLetter(char c) {
    return std::isalpha(static_cast<char>(c));
}

std::string toLowercase(const std::string& str) {
    std::string result = str;
    for (char& c : result) {
        if (c >= 'A' && c <= 'Z') {
            c += 32;
        }
    }
    return result;
}

std::map<std::string, int> countWords(const std::string& text) {
    std::map<std::string, int> wordCount;
    std::string lowerText = toLowercase(text);

    size_t pos = 0;
    while (pos < lowerText.size()) {
        while (pos < lowerText.size() && std::isspace(lowerText[pos])) {
            pos++;
        }

        std::string word;
        while (pos < lowerText.size() && !std::isspace(lowerText[pos])) {
            word += lowerText[pos];
            pos++;
        }
        if (!word.empty()) {
            wordCount[word]++;
        }
    }
    return wordCount;
}

std::pair<std::string, int> findMostFrequentWord(const std::map<std::string, int>& wordCount) {
    if (wordCount.empty()) {
        throw std::string("Error: No words found in the file!");
    }

    std::string mostFrequent;
    int maxCount = 0;

    for (const auto& [word, count] : wordCount) {
        if (count > maxCount) {
            maxCount = count;
            mostFrequent = word;
        }
    }

    return {mostFrequent, maxCount};
}

int main() {

    const std::string input_file = "input.txt";

    try {
        std::string fileContent = readDataFromFile(input_file);

        std::map<std::string, int> wordCount = countWords(fileContent);

        auto [mostFrequentWord, frequency] = findMostFrequentWord(wordCount);

        std::cout << "Word: \"" << mostFrequentWord << "\" appears in the file " << frequency << " times" << std::endl;
    }
    catch (const std::string& msg) {
        std::cerr << msg << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
        return 1;
    }
    return 0;
}
