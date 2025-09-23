#include "simple_container.h"
#include "container_iterator.h" // include here!


Container::Container(): size_(0), arr_(nullptr) {}

Container::Container(size_t cap): size_(0), arr_(new int[cap]) {}

void Container::Push(int value) {
    arr_[size_] = value;
    ++size_;
}

size_t Container::Size() const {
    return size_;
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

