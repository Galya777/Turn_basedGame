//
// Created by galya777 on 08.06.25.
//

#ifndef TURN_BASEDGAME_UNDEADCASTER_H
#define TURN_BASEDGAME_UNDEADCASTER_H

#include "UndeadTypes.h"
#include "../../Weapons/Armors/Armor.h"

class UndeadCaster : public UndeadUnit {
protected:
    int mana;

public:
    UndeadCaster(int hp, Armor* armor, int goldCost, int manaAmount)
            : UndeadUnit(hp, armor, goldCost), mana(manaAmount) {}

    virtual void useMana(int amount) {
        if (amount <= mana) mana -= amount;
        else throw std::runtime_error("Not enough mana!");
    }
    Unit* clone() const override {
        return new UndeadCaster(*this);
    }
    int getMana() const { return mana; }

    virtual ~UndeadCaster() = default;
};


#endif //TURN_BASEDGAME_UNDEADCASTER_H
