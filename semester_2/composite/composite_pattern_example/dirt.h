#pragma once

#include "item.h"


class Dirt : public Item {
private:
    
public:
    Dirt(uint32_t amount)
      : Item(std::make_unique<ItemInfo>("Dirt", amount, std::nullopt, true, false)) {}
    

    void print_info() const override {
        if (info_->is_selected_) {
            std::cout << *info_;
        } else {
            std::cout << "Item \"" << info_->name_ << "\" is unselected\n";
        }
    }

    void use() override {
        std::cout << info_->amount_ << " of " << info_->name_ << " were dropped\n";
        info_->amount_ = 0;
        deselect();
    }

};

