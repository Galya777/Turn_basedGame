//
// Created by galya777 on 08.06.25.
//

#include "Unarmored.h"

Unarmored::Unarmored()
        : Armor(ArmorType::UNARMORED, 0) {}

float Unarmored::getReductionFactor() const {
    return 0.5f;
}

Armor* Unarmored::clone() const {
    return new Unarmored(*this);
}

void Unarmored::onHit() {
    // No action on hit for unarmored
}

