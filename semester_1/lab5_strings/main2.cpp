#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cctype>

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

void splitString(const std::string& str, std::vector<std::string>& words, std::vector<std::string>& separators) {
    words.clear();
    separators.clear();
    size_t i = 0;
    while (i < str.length()) {
        if (std::isalpha(str[i])) {
            std::string word;
            while (i < str.length() && std::isalpha(str[i])) {
                word += str[i];
                i++;
            }
            words.push_back(word);
        }
        else {
            std::string separator;
            while (i < str.length() && !std::isalpha(str[i])) {
                separator += str[i];
                i++;
            }
            separators.push_back(separator);
        }
    }
}

std::string assembleString(const std::vector<std::string>& words, const std::vector<std::string>& separators) {
    std::string result;
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
    return result;
}
int main() {
    std::string input;

    std::cout << "Enter sentence: ";
    std::getline(std::cin, input);

    std::string swappedCase = swapCase(input);

    std::vector<std::string> words, separators;

    splitString(swappedCase, words, separators);

    std::sort(words.begin(), words.end(), compareWords);

    std::string result = assembleString(words, separators);
    std::cout << "Changed sentence: " << result << std::endl;

    words.clear();separators.clear();
    return 0;
}
