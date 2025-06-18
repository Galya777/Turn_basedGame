//
// Created by galya777 on 11.05.25.
//

#ifndef TURN_BASEDGAME_UNLIVINGUNIT_H
#define TURN_BASEDGAME_UNLIVINGUNIT_H

#include "../Basics/Unit.h"

class UndeadUnit : public Unit {
public:
    UndeadUnit(int hp, Armor* arm, int gold, int mana = -1)
            : Unit(hp, arm, gold), hasMana(mana >= 0), manaPoints(mana) {}

    bool hasManaAttribute() const override { return hasMana; }
    int getMana() const override { return hasMana ? manaPoints : -1; }

    void setMana(int m) override {
        if (m < 0) throw std::invalid_argument("Mana cannot be negative");
        manaPoints = m;
        hasMana = true;
    }

    void increaseMana(int amount) override {
        if (hasMana) manaPoints += amount;
    }

    std::string getType() const override { return "Undead"; }

    ~UndeadUnit() override = default;
     void attack(Unit& target) override{};

    Unit* clone() const override {
        return new UndeadUnit(*this);
    }
private:
    bool hasMana;
    int manaPoints;
};


#endif //TURN_BASEDGAME_UNLIVINGUNIT_H
