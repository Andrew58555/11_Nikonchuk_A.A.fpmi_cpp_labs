#pragma once

#include <cstdint>
#include <iostream>


class String {
private:
    size_t size_ = 0;
    char* data_ = nullptr;

public:
    String() {
        std::cout << "Default.\n";
    }

    String(char c, size_t n)
     : size_(n + 1), data_(new char[size_])  {
        std::cout << "User defined.\n";
        //data_ = new char[n+1];
        for (int i = 0; i < n; ++i){
            data_[i] = c;
        }
        data_[n] = '\0';
        //size_ = n + 1;
    }
    
    String(const String& other)
      : size_(other.size_), data_(new char[size_]){
        // size_ = other.size_;
        // data_ = new char[size_];
        // for (int i = 0; i < size_; ++i) {
        //     data_[i] = other.data_[i];
        // }
        std::cout << "Copy ctor.\n";
        std::copy(other.data_, other.data_ + size_, data_);
    }
    
    ~String(){
        std::cout << "Destructor.\n";
        delete[] data_;
    }

    String& operator=(const String& other) {
        std::cout << "operator=.\n";

        if (this == &other) {
            return *this;
        }

        size_ = other.size_;
        delete[] data_;
        data_ = new char[size_];
        std::copy(other.data_, other.data_ + size_, data_);

        return *this;
    }

};
