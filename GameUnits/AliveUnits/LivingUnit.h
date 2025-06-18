//
// Created by galya777 on 11.05.25.
//

#ifndef TURN_BASEDGAME_LIVINGUNIT_H
#define TURN_BASEDGAME_LIVINGUNIT_H


#pragma once

#include <vector>
#include "../Basics/Unit.h"
#include "../../Weapons/Weapon.h"



class LivingUnit : public Unit {
public:
    LivingUnit(int hp, Armor* arm,int goldCost, Weapon* weap = nullptr,  int mana = -1)
            : Unit(hp, arm, goldCost), weapon(weap), hasMana(mana >= 0), manaPoints(mana) {}

    ~LivingUnit() override {
        delete weapon;
        for (auto* ability : abilities)
            delete ability;
    }
    bool hasManaAttribute() const { return hasMana; }
    int getMana() const { return hasMana ? manaPoints : -1; }
    void setMana(int m) {
        if (m < 0) throw std::invalid_argument("Mana cannot be negative");
        manaPoints = m;
        hasMana = true;
    }
    Unit* clone() const override {
        return new LivingUnit(*this);
    }
    void attack(Unit& target) override;
    std::string getType() const override { return "Living"; }

protected:
    std::vector<Ability*> abilities;
    Weapon* weapon = nullptr;

    bool hasMana;
    int manaPoints;
};






#endif //TURN_BASEDGAME_LIVINGUNIT_H
