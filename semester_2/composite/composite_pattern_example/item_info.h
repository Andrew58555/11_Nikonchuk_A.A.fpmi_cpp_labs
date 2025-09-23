#pragma once

#include <optional>
#include <string>
#include <cstdint>
#include <iostream>
#include <memory>


struct ItemInfo {
    std::string name_ = "";
    uint32_t amount_ = 0;
    std::optional<uint32_t> durability_ = std::nullopt;
    bool is_stackable_ = false;
    bool is_selected_ = false;

    ItemInfo(const std::string name, uint32_t amount, std::optional<uint32_t> durability, 
            bool is_stackable, bool is_selected)
      : name_(name), amount_(amount), durability_(durability),
      is_stackable_(is_stackable), is_selected_(is_selected) {}
};


inline std::ostream& operator<<(std::ostream& out, const ItemInfo& info) {

    std::string line_prefix = "  ";
    out << "Item information:\n";
    out << "{\n";
    out << line_prefix << "Name: " << info.name_ << '\n';
    out << line_prefix << "Amount: " << info.amount_ << '\n';
    if (info.durability_.has_value()) {
        out << line_prefix << "Durability: " << info.durability_.value() << '\n';
    }
    out << line_prefix << (info.is_stackable_ ? "Stackable" : "Not stackable") << '\n';
    out << line_prefix << (info.is_selected_ ? "Selected" : "Not selected") << '\n';
    out << "}" << std::endl;
    
    return out;
}


using ItemInfoPtr = std::unique_ptr<ItemInfo>;

