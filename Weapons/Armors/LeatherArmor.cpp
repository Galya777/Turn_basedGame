//
// Created by galya777 on 08.06.25.
//

#include "LeatherArmor.h"

LeatherArmor::LeatherArmor(int durability)
        : Armor(ArmorType::LEATHER, durability) {}

float LeatherArmor::getReductionFactor() const {
    return 0.3f;
}

Armor* LeatherArmor::clone() const {
    return new LeatherArmor(*this);
}

void LeatherArmor::onHit() {
    degrade();
}

