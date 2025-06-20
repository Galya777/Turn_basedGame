//
// Created by galya777 on 08.06.25.
//

#ifndef TURN_BASEDGAME_LEATHERARMOR_H
#define TURN_BASEDGAME_LEATHERARMOR_H

#include "Armor.h"

class LeatherArmor : public Armor {
public:
    explicit LeatherArmor(int durability);

    float getReductionFactor() const override;
    Armor* clone() const override;
    void onHit() override;
};

#endif //TURN_BASEDGAME_LEATHERARMOR_H


