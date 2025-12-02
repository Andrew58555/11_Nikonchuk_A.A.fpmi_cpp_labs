#pragma once
#include <initializer_list>
#include <iostream>
#include <cstdint>

class String {
private: 
    size_t size_=0;
    char* arr_=nullptr;

public:
    String() {
        std::cout << "Default\n";
    }

    String(char ch, size_t amount)
      : size_(amount + 1), arr_(new char[size_]) {
        std::cout << "User defined\n";
        //arr_ = new char[amount+1];
        for (size_t i = 0; i < amount; ++i) {
            arr_[i] = ch;
        }
        arr_[amount] = '\0';
        //size_ = amount+1;
    }

    String(std::initializer_list<char> list)
      : size_(list.size() + 1), arr_(new char[size_]) {
        
        //size_t i = 0;
        for (size_t i = 0; char item : list) {
            arr_[i] = item;
            ++i;
        }
        //std::copy(list.begin(), list.end(), arr_);
        arr_[size_ - 1] = '\0';
    }

    String (const String& other)
      : size_(other.size_), arr_(new char[size_]){
        //for (size_t i = 0; i < size_;++i) {
        //    arr_[i] =other.arr_[i];
        //}
        std::cout << "Copy ctor\n";
        std::copy(other.arr_, other.arr_ + size_, arr_);
    }

    ~String() {
        std::cout << "Destructor\n";
        delete[] arr_;
    }

    String& operator=(const String& other){
        std::cout << "operator=\n";
        
        if (this == &other) {
            return *this;
        }
        
        // copy and swap
        String copy(other);
        Swap(copy);
        
        //size_ = other.size_;
        //delete[] arr_;
        //arr_ = new char[size_];
        //for (int i = 0; i<size_;i++){
        //    this->arr_[i]=other.arr_[i];
        //}
        //std::copy(other.arr_, other.arr_ + size_, arr_);

        return *this;
    }

    void Swap(String& other) {
        std::swap(size_, other.size_);
        std::swap(arr_, other.arr_);
    }
    // aa df
    // df aa


    char& operator[](size_t index) {
        //std::cout << "non-const";
        return arr_[index];
    }

    const char& operator[](size_t index) const {
        return arr_[index];
    }

    size_t Size() const {
        return size_ == 0u ? 0u : size_ - 1;
    }
    
    //friend std::ostream& operator<<(std::ostream&, const String&); // not friend!!!!!
};


//std::ostream& operator<<(std::ostream&, const String&); // in .h


std::ostream& operator<<(std::ostream& out, const String& str) { // in .cpp

    for (size_t i = 0; i < str.Size(); ++i) {
        out << str[i];
    }

    return out;
}


