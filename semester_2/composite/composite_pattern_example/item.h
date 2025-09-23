#pragma once

#include "item_info.h"

#include <memory>


// abstracte base class, which represents 
// item's interface
class Item {
protected:
    ItemInfoPtr info_;

protected:
    Item(ItemInfoPtr&& info): info_(std::move(info)) {}

public:
    virtual void select() {
        info_->is_selected_ = true;
    }
    
    virtual void deselect() {
        info_->is_selected_ = false;
    }

    virtual void print_info() const = 0;
    virtual void use() = 0;
    
    // virtual dtor
    virtual ~Item() = default;
};


using ItemPtr = std::unique_ptr<Item>;

