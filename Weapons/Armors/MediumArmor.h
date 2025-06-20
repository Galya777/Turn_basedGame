#ifndef TURN_BASEDGAME_MEDIUMARMOR_H
#define TURN_BASEDGAME_MEDIUMARMOR_H

#include "Armor.h"

class MediumArmor : public Armor {
public:
    explicit MediumArmor(int durability);

    float getReductionFactor() const override;
    Armor* clone() const override;
    void onHit() override;
};

#endif //TURN_BASEDGAME_MEDIUMARMOR_H
