//
// Created by galya777 on 11.05.25.
//

#include "MediumArmor.h"

MediumArmor::MediumArmor(int durability)
        : Armor(ArmorType::MEDIUM, durability) {}

float MediumArmor::getReductionFactor() const {
    return 0.5f;
}

Armor* MediumArmor::clone() const {
    return new MediumArmor(*this);
}

void MediumArmor::onHit() {
    degrade();
}

