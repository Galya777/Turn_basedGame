//
// Created by galya777 on 08.06.25.
//

#ifndef TURN_BASEDGAME_GHOST_H
#define TURN_BASEDGAME_GHOST_H

#include "UndeadTypes.h"

class Ghost : public UndeadUnit {
public:
    Ghost();


    int getHealth() const  { return 0; }
    int getMana() const  { return 0; }
    int getAttack() const  { return 0; }
    int getArmorStrength() const { return 0; }

    std::string getType() const override { return "Ghost"; }

    // Добавя 250 здраве на друга немъртва единица и се самоунищожава
    bool empowerUndead(UndeadUnit& target);

    // Ghost няма атака
    void attack(Unit& target) override {}

    // Флаг дали е жив/активен
    bool isAlive() const override { return alive; }

    // Маркира Ghost като мъртъв (след самоунищожение)
    void die();

    ~Ghost() override = default;

    Unit* clone() const override {
        return new Ghost(*this);
    }

private:
    bool alive = true;
};

#endif // TURN_BASEDGAME_GHOST_H

