#include "simple_container.h"
#include "container_iterator.h" // include here!

#include <algorithm>

Container::Container(): size_(0), arr_(nullptr) {}

Container::Container(size_t cap)
  : size_(0), arr_( (cap > 0u) ? (new int[cap]) : nullptr ) {}

Container::Container(const Container& other): Container(other.size_) {
    std::copy(other.arr_, other.arr_ + size_, arr_);
}

void Container::Push(int value) {
    arr_[size_] = value;
    ++size_;
}

size_t Container::Size() const {
    return size_;
}

Container& Container::operator=(const Container& rhs) {
    if (this == &rhs) {
        return *this;
    }
    
    size_ = rhs.size_;
    
    delete[] arr_;
    arr_ = new int[size_];
    std::copy(rhs.arr_, rhs.arr_ + size_, arr_);

    return * this;
}

int& Container::operator[](size_t index) {
    return arr_[index];
}
    
const int& Container::operator[](size_t index) const {
    return arr_[index];
}

Container::~Container() {
    delete[] arr_;
}


Iterator<int>* Container::CreateIterator() const {
    return new ContainerIterator(this); // use ContainerIterator's ctor here!
}


std::ostream& operator<<(std::ostream& out, const Container& cont) {
    for (size_t i = 0; i < cont.Size(); ++i) {
        out << cont[i] << ' ';
    }
    return out;
}
