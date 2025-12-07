#include "vector_impl.h"


Vector::Vector() {}

Vector::Vector(size_t size) : size_(size), capacity_(size) {
    vector_ = new int[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        vector_[i] = 0;
    }
}

Vector::Vector(std::initializer_list<int> list) : size_(list.size()), capacity_(list.size()) {
    vector_ = new int[capacity_];
    std::copy(list.begin(), list.end(), vector_);
}

Vector::Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_) {
    vector_ = new int[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        vector_[i] = other.vector_[i];
    }
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        Vector temp(other);
        Swap(temp);
    }
    return *this;
}

Vector::~Vector() {
    delete[] vector_;
    vector_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

void Vector::Swap(Vector& other) {
    std::swap(vector_, other.vector_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

int& Vector::operator[](size_t index) {
    return vector_[index];
}

const int& Vector::operator[](size_t index) const {
    return vector_[index];
}

int& Vector::At(size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return vector_[index];
}

const int& Vector::At(size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return vector_[index];
}

size_t Vector::Size() const {
    return size_;
}

size_t Vector::Capacity() const {
    return capacity_;
}

void Vector::PushBack(int value) {
    if (size_ >= capacity_) {
        size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        Reserve(new_capacity);
    }
    vector_[size_] = value;
    ++size_;
}

void Vector::PopBack() {
    if (size_ > 0) {
        --size_;
    }
}

void Vector::Clear() {
    size_ = 0;
}

void Vector::Reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
        int* new_vector = new int[new_capacity];
        for (size_t i = 0; i < size_; ++i) {
            new_vector[i] = vector_[i];
        }
        delete[] vector_;
        vector_ = new_vector;
        capacity_ = new_capacity;
    }
}

std::ostream& operator<<(std::ostream& os, const Vector& vec) {
    os << "[";
    for (size_t i = 0; i < vec.size_; ++i) {
        os << vec.vector_[i];
        if (i != vec.size_ - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
