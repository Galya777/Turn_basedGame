//
// Created by galya777 on 05.06.25.
//

#ifndef TURN_BASEDGAME_HEALER_H
#define TURN_BASEDGAME_HEALER_H

#include "LivingUnit.h"
#include "../../Weapons/MeleeWeapon.h"
#include "../../Weapons/Armors/Unarmored.h"

class Healer : public LivingUnit {
public:
    Healer()
            : LivingUnit(
            290,
            new Unarmored(), //The healer is unarmored
            150,
            new MeleeWeapon(2, "Staff"),
            200
    ) {}

    std::string getType() const override { return "Healer"; }

    void heal(LivingUnit& target) {
        if (!hasManaAttribute() || getMana() < 100) {
            throw std::runtime_error("Not enough mana to heal.");
        }
        if (!target.isAlive()) {
            throw std::runtime_error("Cannot heal a dead unit.");
        }

        target.getHealth().restore(100);  // Предполага се, че има метод restore()
        setMana(getMana() - 100);
    }

    Unit* clone() const override {
        return new Healer(*this);
    }
};

#endif //TURN_BASEDGAME_HEALER_H

