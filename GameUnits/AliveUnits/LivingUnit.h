//
// Created by galya777 on 11.05.25.
//
#ifndef TURN_BASEDGAME_LIVINGUNIT_H
#define TURN_BASEDGAME_LIVINGUNIT_H

#include <vector>
#include "../Basics/Unit.h"
#include "../../Weapons/Weapon.h"
#include <stdexcept>

class Ability;

class LivingUnit : public Unit {
public:
    LivingUnit(int hp, Armor* arm, int goldCost, Weapon* weap = nullptr, int mana = -1);
    ~LivingUnit() override;

    bool hasManaAttribute() const;
    int getMana() const;
    void setMana(int m);

    Unit* clone() const override;

    void attack(Unit& target) override;
    std::string getType() const override;

protected:
    std::vector<Ability*> abilities;
    Weapon* weapon;

    bool hasMana;
    int manaPoints;
};

#endif //TURN_BASEDGAME_LIVINGUNIT_H

