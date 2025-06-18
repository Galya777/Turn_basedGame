//
// Created by galya777 on 08.06.25.
//

#ifndef TURN_BASEDGAME_UNARMORED_H
#define TURN_BASEDGAME_UNARMORED_H

#include "Armor.h"
class Unarmored : public Armor {
    public:
    Unarmored()
                : Armor(ArmorType::UNARMORED, 0) {}

        float getReductionFactor() const override {
            return 0.5f;
        }

        Armor* clone() const override {
            return new Unarmored(*this);
        }

        void onHit() override {
        }
};


#endif //TURN_BASEDGAME_UNARMORED_H
