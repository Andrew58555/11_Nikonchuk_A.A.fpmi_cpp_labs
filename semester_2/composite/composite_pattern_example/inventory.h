#pragma once

#include "item.h"


#include <unordered_map>
#include <array>
#include <random>


using CellNumber = uint32_t;
const int MAX_CELLS_NUMBER = 36;


// class Composite
class Inventory: public Item {
private:
    std::unordered_map<CellNumber, ItemPtr> inventory_;
    std::array<bool, MAX_CELLS_NUMBER> cells_;
public:
    Inventory(): Item(nullptr), cells_() {
    } 
	
    void add_item(ItemPtr item) {
        if (inventory_.size() == MAX_CELLS_NUMBER) {
            std::cout << "Inventory is full\n";
            return;
        }
        for(int i = 0; i < MAX_CELLS_NUMBER; ++i) {
            if (!cells_[i]) {
                inventory_.emplace(i, std::move(item));
                cells_[i] = true;
                break;
            }
        }
    }

    // select ALL of items in composite
    virtual void select() override { 
        for (const auto& [cell, item] : inventory_) {
            item->select();
        }
    }
    
    // deselect ALL of items in composite
    virtual void deselect() override {
        for (const auto& [cell, item] : inventory_) {
            item->deselect();
        }
    }

    // print information about ALL items
    // in composite
    void print_info(size_t indent = 0u) const override {
        std::cout << std::string(indent, ' ') << "<--------------------->\n";
        indent += 4u;
        for (const auto& [cell, item] : inventory_) {
            std::cout << std::string(indent, ' ') << "Cell: " << cell << '\n';
            item->print_info(indent + 2u);
        }
        std::cout << std::string(indent - 4u, ' ') << "<--------------------->" << std::endl;
    }

    // use ALL items in composite
    void use() override {
        for (const auto& [cell, item] : inventory_) {
            item->use();
        }
    }

    // we don't need to delete allocated memory
    // because we are using smart pointer
    // std::unique_ptr which manages
    // the memery himself
    ~Inventory() = default;
};


using InventoryPtr = std::unique_ptr<Inventory>;
