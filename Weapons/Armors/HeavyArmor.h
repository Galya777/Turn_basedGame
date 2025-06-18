//
// Created by galya777 on 08.06.25.
//

// HeavyArmor.h
#ifndef TURN_BASEDGAME_HEAVYARMOR_H
#define TURN_BASEDGAME_HEAVYARMOR_H

#include "Armor.h"

class HeavyArmor : public Armor {
public:
    HeavyArmor(int durability)
            : Armor(ArmorType::HEAVY, durability) {}

    float getReductionFactor() const override {
        return 0.5f;
    }

    Armor* clone() const override {
        return new HeavyArmor(*this);
    }

    void onHit() override {
        //this armor is apparently not destroyable
    }
};

#endif //TURN_BASEDGAME_HEAVYARMOR_H
