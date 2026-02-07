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

    void PrintWithIndent(std::ostream& out, size_t indent = 0u) const {
        std::string outer_line_prefix = std::string(indent, ' ');
        std::string inner_line_prefix = std::string(indent + 2u, ' ');

        out << outer_line_prefix << "Item information:\n";
        out << outer_line_prefix << "{\n";
        out << inner_line_prefix << "Name: " << name_ << '\n';
        out << inner_line_prefix << "Amount: " << amount_ << '\n';
        if (durability_.has_value()) {
            out << inner_line_prefix << "Durability: " << durability_.value() << '\n';
        }
        out << inner_line_prefix << (is_stackable_ ? "Stackable" : "Not stackable") << '\n';
        out << inner_line_prefix << (is_selected_ ? "Selected" : "Not selected") << '\n';
        out << outer_line_prefix << "}" << std::endl;
    }
};


inline std::ostream& operator<<(std::ostream& out, const ItemInfo& info) {
    
    info.PrintWithIndent(out);  
    return out;
}


using ItemInfoPtr = std::unique_ptr<ItemInfo>;
