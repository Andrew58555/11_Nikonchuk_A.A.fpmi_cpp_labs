#include <iostream>
#include <string>
#include <map>

bool letter(char l) {
    if (l >= 'a' && l <= 'z' || l >= 'A' && l <= 'Z') {
        return true;
    }
    else {
        return false;
    }
}

int main() {

    freopen("input.txt", "r", stdin);
    std::string s;
    getline(std::cin, s);
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] += 32;
        }
    }
    int ind = 0;
    std::map<std::string, int> a;
    while (ind < s.size()) {

        std::string cur1;
        while (letter(s[ind]) && ind < s.size()) {
            cur1 += s[ind];
            ind++;
        }
        if (cur1 != "") {
            a[cur1]++;
        }
        while (!letter(s[ind]) && ind < s.size()) {
            ind++;
        }
    }
    std::string s1;
    int max_a = 0;
    for (auto [l, r] : a) {
        if (r > max_a) {
            max_a = r;
            s1 = l;
        }
    }
    std::cout << "Word : " << s1 << " appears in the sentence " << max_a << " times";
    return 0;
}

