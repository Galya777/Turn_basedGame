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
    UndeadCaster(int hp, Armor* armor, int goldCost, int manaAmount);

    virtual void useMana(int amount);
    int getMana() const;
    Unit* clone() const override;

    virtual ~UndeadCaster();
};

#endif //TURN_BASEDGAME_UNDEADCASTER_H

