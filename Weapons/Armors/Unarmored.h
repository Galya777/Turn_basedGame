//
// Created by galya777 on 08.06.25.
//

#ifndef TURN_BASEDGAME_UNARMORED_H
#define TURN_BASEDGAME_UNARMORED_H

#include "Armor.h"

class Unarmored : public Armor {
public:
    Unarmored();

    float getReductionFactor() const override;
    Armor* clone() const override;
    void onHit() override;
};

#endif //TURN_BASEDGAME_UNARMORED_H

