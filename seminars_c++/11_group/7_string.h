#pragma once
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
        if(this == &other){
            return *this;
        }
        
        size_ = other.size_;
        delete[] arr_;
        arr_ = new char[size_];
        //for (int i = 0; i<size_;i++){
        //    this->arr_[i]=other.arr_[i];
        //}
        std::copy(other.arr_, other.arr_ + size_, arr_);

        return *this;
    }
};
