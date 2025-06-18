//
// Created by galya777 on 08.06.25.
//

#ifndef TURN_BASEDGAME_LEATHERARMOR_H
#define TURN_BASEDGAME_LEATHERARMOR_H

#include "Armor.h"

class LeatherArmor : public Armor {
public:
    LeatherArmor(int durability)
            : Armor(ArmorType::LEATHER, durability) {}

    float getReductionFactor() const override {
        return 0.3f;
    }

    Armor* clone() const override {
        return new LeatherArmor(*this);
    }

    void onHit() override {
        degrade();
    }
};

#endif //TURN_BASEDGAME_LEATHERARMOR_H

