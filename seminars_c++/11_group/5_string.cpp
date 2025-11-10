#include <iostream>
#include <string>
#include <vector>

// "hello" -> ['h', 'e', 'l', 'l', 'o', '\0']
// how are you| -> 3

size_t CountWordsAmount(const std::string& text) {
    size_t words_amount = 0;
    
    std::string::size_type beg_index = 0;
    std::string::size_type end_index = text.find_first_of(" ", beg_index);
    
    // std::string::npos
    while (beg_index != std::string::npos) {
    
        std::string word = text.substr(beg_index, end_index - beg_index);
        if (!word.empty()) {
            ++words_amount;
        }
        // std::cout << word << '\n';
        
        beg_index = text.find_first_not_of(" ", end_index);
        end_index = text.find_first_of(" ", end_index + 1);
    }

    return words_amount;
}


std::vector<std::string> SplitText(const std::string& text,
                                  const std::string& delimeters) {
    std::vector<std::string> words;
    
    std::string::size_type beg_index = 0;
    std::string::size_type end_index = text.find_first_of(delimeters, beg_index);
    
    // std::string::npos
    while (beg_index != std::string::npos) {
    
        std::string word = text.substr(beg_index, end_index - beg_index);
        if (!word.empty()) {
            words.push_back(word);
        }
        // std::cout << word << '\n';
        
        beg_index = text.find_first_not_of(delimeters, end_index);
        end_index = text.find_first_of(delimeters, end_index + 1);
    }

    return words;
}


void PrintVector(const std::vector<std::string>& vector) {
    for (size_t i = 0; i < vector.size(); ++i) {
        std::cout << vector[i] << ' ';
    }
    std::cout << std::endl;
}


int main() {

    std::string text;
    std::getline(std::cin, text);
    //std::cout << text;
    
    //size_t words = CountWordsAmount(text);
    //std::cout << words;
    std::string delimeters = " ,:;";
    std::vector<std::string> words = SplitText(text, delimeters);
    PrintVector(words);

    return 0;
}
