#pragma once

#include <cstdint>
#include <initializer_list>
#include <iostream>


class String {
private:
    size_t size_ = 0;
    char* data_ = nullptr;

public:
    String() {
        std::cout << "Default.\n";
    }

    explicit String(char c, size_t n)
     : size_(n + 1), data_(new char[size_])  {
        std::cout << "User defined.\n";
        //data_ = new char[n+1];
        for (size_t i = 0; i < n; ++i){
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

    String(std::initializer_list<char> list)
      : size_(list.size() + 1), data_(new char[size_]) {
        
        // int i = 0;
        // since c++20
        for (int i = 0; char item : list) {
            data_[i] = item;
            ++i;
        }
        data_[size_ - 1] = '\0';
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
        
        // swap and copy
        String copy(other);
        Swap(copy);

        //size_ = other.size_;
        //delete[] data_;
        //data_ = new char[size_];
        //std::copy(other.data_, other.data_ + size_, data_);

        return *this;
    }

    void Swap(String& other) {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
    }

    char& operator[](size_t index) {
        return data_[index];
    }

    const char& operator[](size_t index) const {
        return data_[index];
    }

    size_t Size() const {
        return size_ == 0u ? 0u : size_ - 1;
    }

    //friend std::ostream& operator<<(std::ostream&, const String&);
};


std::ostream& operator<<(std::ostream& out, const String& str) {

    for (size_t i = 0; i < str.Size(); ++i) {
        out << str[i];
    }

    return out;
}

