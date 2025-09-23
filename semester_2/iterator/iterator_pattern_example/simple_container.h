#ifndef SIMPLE_CONTAINER
#define SIMPLE_CONTAINER

#include <iostream>

#include "iterator.h"
// we don't need to include "container_iterator.h" here
// because we have a base class Iterator<T>
// (we won't use ContainerIterator class here!)
// so we will include "container_iterator.h"
// directly into "container_iterator.cpp" file
// (see "container_iterator.cpp" for more informarion)


// your container (e.g. deque, stack, vector, queue and etc.)
// can be a template
class Container {
private:
    // it's possible not to mark
    // ContainerIterator as a friend
    // (see "container_iterator.cpp"
    // for more information)
    friend class ContainerIterator;
private:
    size_t size_;
    int* arr_;
public:
    Container();
    Container(size_t);

    void Push(int item = 0);
    size_t Size() const;

    int& operator[](size_t);
    const int& operator[](size_t) const;

    ~Container();

    // method for creating an iterator
    // this method MUST be in a container!!!
    Iterator<int>* CreateIterator() const;
};

std::ostream& operator<<(std::ostream&, const Container&);

#endif // SIMPLE_CONTAINER
