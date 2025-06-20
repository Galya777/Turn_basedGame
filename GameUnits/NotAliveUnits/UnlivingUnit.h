//
// Created by galya777 on 11.05.25.
//

#ifndef TURN_BASEDGAME_UNLIVINGUNIT_H
#define TURN_BASEDGAME_UNLIVINGUNIT_H

#include "../Basics/Unit.h"

class UndeadUnit : public Unit {
public:
    UndeadUnit(int hp, Armor* arm, int gold, int mana = -1);

    bool hasManaAttribute() const override;
    int getMana() const override;
    void setMana(int m) override;
    void increaseMana(int amount) override;

    std::string getType() const override;
    void attack(Unit& target) override; // празна по дизайн
    Unit* clone() const override;

    ~UndeadUnit() override;

private:
    bool hasMana;
    int manaPoints;
};

#endif //TURN_BASEDGAME_UNLIVINGUNIT_H

