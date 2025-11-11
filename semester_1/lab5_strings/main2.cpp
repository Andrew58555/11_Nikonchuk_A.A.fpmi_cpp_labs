#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

std::string swapCase(const std::string& str) {
    std::string result = str;
    for (char& c : result) {
        if (std::isupper(c)) {
            c = std::tolower(c);
        } else if (std::islower(c)) {
            c = std::toupper(c);
        }
    }
    return result;
}

int countUppercase(const std::string& word) {
    int count = 0;
    for (char c : word) {
        if (std::isupper(c)) {
            count++;
        }
    }
    return count;
}

bool compareWords(const std::string& a, const std::string& b) {
    int upperA = countUppercase(a);
    int upperB = countUppercase(b);
    if (upperA == upperB) {
        return a < b;
    }
    return upperA < upperB;
}

void splitString(const std::string& str, const std::string& userDelimiters, std::vector<std::string>& words, std::vector<std::string>& separators, bool& startsWithDelimiter) {
    words.clear();
    separators.clear();
    startsWithDelimiter = false;
    if (str.empty()) {
        return;
    }
    auto isDelimiter = [&](char c) {
        if (!userDelimiters.empty()) {
            return userDelimiters.find(c) != std::string::npos;
        }
        return !std::isalpha(c);
    };
    startsWithDelimiter = isDelimiter(str[0]);
    size_t i = 0;
    while (i < str.length()) {
        if (!isDelimiter(str[i])) {
            std::string word;
            while (i < str.length() && !isDelimiter(str[i])) {
                word += str[i];
                i++;
            }
            words.push_back(word);
        }
        else {
            std::string separator;
            while (i < str.length() && isDelimiter(str[i])) {
                separator += str[i];
                i++;
            }
            separators.push_back(separator);
        }
    }
}

std::string assembleString(const std::vector<std::string>& words, const std::vector<std::string>& separators, bool startsWithDelimiter) {
    std::string result;
    if (startsWithDelimiter) {
        size_t totalParts = words.size() + separators.size();
        for (size_t i = 0; i < totalParts; i++) {
            if (i % 2 == 0) {
                if (i / 2 < separators.size()) {
                    result += separators[i / 2];
                }
            } else {
                if (i / 2 < words.size()) {
                    result += words[i / 2];
                }
            }
        }
    } else {
        size_t totalParts = words.size() + separators.size();
        for (size_t i = 0; i < totalParts; i++) {
            if (i % 2 == 0) {
                if (i / 2 < words.size()) {
                    result += words[i / 2];
                }
            } else {
                if (i / 2 < separators.size()) {
                    result += separators[i / 2];
                }
            }
        }
    }
    return result;
}

bool hasOnlyDelimiters(const std::vector<std::string>& words) {
    return words.empty();
}

int main() {
    std::string input;
    std::string userDelimiters;

    std::cout << "Enter sentence: \n";
    std::getline(std::cin, input);

    std::cout << "Enter delimiter characters (press Enter for default delimiters): \n";
    std::getline(std::cin, userDelimiters);

    if (input.empty()) {
        std::cout << "Changed sentence: " << std::endl;
        return 0;
    }

    std::string swappedCase = swapCase(input);

    std::vector<std::string> words, separators;
    bool startsWithDelimiter;

    splitString(swappedCase, userDelimiters, words, separators, startsWithDelimiter);

    if (hasOnlyDelimiters(words)) {
        std::cout << "Task can't be solved: string contains only delimiters" << std::endl;
        return 1;
    }

    std::sort(words.begin(), words.end(), compareWords);

    std::string result = assembleString(words, separators, startsWithDelimiter);
    std::cout << "Changed sentence: " << result << std::endl;

    words.clear();separators.clear();

    return 0;
}
