#include <iostream>
#include <string>
#include <algorithm>

const int N = 1000;
std::string a[N], b[N];

bool letter(char l) {
    if (l >= 'a' && l <= 'z' || l >= 'A' && l <= 'Z') {
        return true;
    }
    else {
        return false;
    }
}

int koll(std::string s) {
    int k = 0;
    for (auto i : s) {
        if (i >= 'A' && i <= 'Z') {
            k++;
        }
    }
    return k;
}

bool comp(std::string a, std::string b) {
    if (koll(a) == koll(b))
        return a < b;
    return koll(a) < koll(b);
}

int main() {

    std::string s;
    std::cout << "Enter sentence\n";
    getline(std::cin, s);
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] -= 32;
        }
        else if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] += 32;
        }
    }
    int a1 = 0, b1 = 0;
    int ind = 0;
    while (ind < s.size()) {
        std::string cur1;
        while (letter(s[ind]) && ind < s.size()) {
            cur1 += s[ind];
            ind++;
        }
        a[a1] = cur1;
        a1++;
    
        std::string cur2;
        while (!letter(s[ind]) && ind < s.size()) {
            cur2 += s[ind];
            ind++;
        }
        b[b1] = cur2;
        b1++;
    }
    std::sort(a, a + a1, comp);
    std::cout << "Changed sentence \n";
    int z = 0;
    while (z < a1) {
        std::cout << a[z];
        if (z < b1)
            std::cout << b[z];
        z++;
    }
    return 0;
}
