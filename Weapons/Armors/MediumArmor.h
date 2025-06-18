//
// Created by galya777 on 11.05.25.
//

#ifndef TURN_BASEDGAME_MEDIUMARMOR_H
#define TURN_BASEDGAME_MEDIUMARMOR_H

#include "Armor.h"

class MediumArmor : public Armor {
public:
    MediumArmor(int durability)
            : Armor(ArmorType::MEDIUM, durability) {}

    float getReductionFactor() const override {
        return 0.5f;
    }

    Armor* clone() const override {
        return new MediumArmor(*this);
    }

    void onHit() override {
        degrade();
    }
};

#endif //TURN_BASEDGAME_MEDIUMARMOR_H
