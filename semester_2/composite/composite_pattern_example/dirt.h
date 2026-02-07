#pragma once

#include "item.h"


class Dirt : public Item {
private:
    
public:
    Dirt(uint32_t amount)
      : Item(std::make_unique<ItemInfo>("Dirt", amount, std::nullopt, true, false)) {}
    

    void print_info(size_t indent = 0u) const override {
        if (info_->is_selected_) {
            info_->PrintWithIndent(std::cout, indent);
        } else {
            std::cout << std::string(indent, ' ') << "Item \"" << info_->name_ << "\" is unselected\n";
        }
    }

    void use() override {
        std::cout << info_->amount_ << " of " << info_->name_ << " were dropped\n";
        info_->amount_ = 0;
        deselect();
    }

};

