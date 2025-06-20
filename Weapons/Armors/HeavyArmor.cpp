//
// Created by galya777 on 08.06.25.
//

#include "HeavyArmor.h"

HeavyArmor::HeavyArmor(int durability)
        : Armor(ArmorType::HEAVY, durability) {}

float HeavyArmor::getReductionFactor() const {
    return 0.5f;
}

Armor* HeavyArmor::clone() const {
    return new HeavyArmor(*this);
}

void HeavyArmor::onHit() {
    // This armor is not destroyable; no action needed
}

