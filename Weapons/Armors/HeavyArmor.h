//
// Created by galya777 on 08.06.25.
//

#ifndef TURN_BASEDGAME_HEAVYARMOR_H
#define TURN_BASEDGAME_HEAVYARMOR_H

#include "Armor.h"

class HeavyArmor : public Armor {
public:
    explicit HeavyArmor(int durability);

    float getReductionFactor() const override;
    Armor* clone() const override;
    void onHit() override;
};

#endif //TURN_BASEDGAME_HEAVYARMOR_H

