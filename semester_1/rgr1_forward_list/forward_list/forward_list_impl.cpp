#include "forward_list_impl.h"
#include <stdexcept>

void ForwardList::CopyFrom(const ForwardList& other) {
    if (other.head_ == nullptr) {
        head_ = nullptr;
        size_ = 0;
        return;
    }

    head_ = new Node(other.head_->value_);
    size_ = 1;

    Node* current = head_;
    Node* other_current = other.head_->next_;

    while (other_current != nullptr) {
        current->next_ = new Node(other_current->value_);
        current = current->next_;
        other_current = other_current->next_;
        ++size_;
    }
}

void ForwardList::ClearNodes() {
    while (head_ != nullptr) {
        Node* temp = head_;
        head_ = head_->next_;
        delete temp;
    }
    size_ = 0;
}

ForwardList::ForwardList() : head_(nullptr), size_(0) {
}

ForwardList::ForwardList(const ForwardList& rhs) {
    CopyFrom(rhs);
}

ForwardList::ForwardList(size_t count, int32_t value) : head_(nullptr), size_(0) {
    for (size_t i = 0; i < count; ++i) {
        PushFront(value);
    }
}

ForwardList::ForwardList(std::initializer_list<int32_t> init) : head_(nullptr), size_(0) {
    for (auto it = init.end(); it != init.begin();) {
        --it;
        PushFront(*it);
    }
}

ForwardList& ForwardList::operator=(const ForwardList& rhs) {
    if (this != &rhs) {
        ClearNodes();
        CopyFrom(rhs);
    }
    return *this;
}

ForwardList::~ForwardList() {
    ClearNodes();
}

void ForwardList::PushFront(int32_t value) {
    Node* new_node = new Node(value);
    new_node->next_ = head_;
    head_ = new_node;
    ++size_;
}

void ForwardList::PopFront() {
    if (head_ == nullptr) {
        return;
    }

    Node* temp = head_;
    head_ = head_->next_;
    delete temp;
    --size_;
}

void ForwardList::Remove(int32_t value) {
    if (head_ == nullptr) {
        return;
    }

    while (head_ != nullptr && head_->value_ == value) {
        PopFront();
    }

    if (head_ == nullptr) {
        return;
    }

    Node* current = head_;
    while (current->next_ != nullptr) {
        if (current->next_->value_ == value) {
            Node* temp = current->next_;
            current->next_ = current->next_->next_;
            delete temp;
            --size_;
        } else {
            current = current->next_;
        }
    }
}

void ForwardList::Clear() {
    ClearNodes();
}

bool ForwardList::FindByValue(int32_t value) {
    Node* current = head_;
    while (current != nullptr) {
        if (current->value_ == value) {
            return true;
        }
        current = current->next_;
    }
    return false;
}

void ForwardList::Print(std::ostream& out) {
    Node* current = head_;
    while (current != nullptr) {
        out << current->value_;
        if (current->next_ != nullptr) {
            out << " ";
        }
        current = current->next_;
    }
}

int32_t ForwardList::Front() const {
    if (head_ == nullptr) {
        throw std::out_of_range("List is empty");
    }
    return head_->value_;
}

size_t ForwardList::Size() const {
    return size_;
}
