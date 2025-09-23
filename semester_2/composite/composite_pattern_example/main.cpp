#include "utils.h"


int main() {

#if 1
    InventoryPtr inventory = utils::CreateSimpleInventory();
    utils::PrintInventoryWithFormat(inventory);
#endif

#if 0
    std::mt19937 gen;

    InventoryPtr inventory = std::make_unique<Inventory>();

    InventoryPtr dirt_inventory = utils::GenerateInventory<Dirt, 3>(gen);
    InventoryPtr logs_inventory = utils::GenerateInventory<Log, 3>(gen);
    InventoryPtr swords_inventory = utils::GenerateInventory<Sword, 3>(gen);

    inventory->add_item(std::move(dirt_inventory));
    inventory->add_item(std::move(logs_inventory));
    inventory->add_item(std::move(swords_inventory));

    utils::PrintInventoryWithFormat(inventory);
#endif

    return 0;
}
