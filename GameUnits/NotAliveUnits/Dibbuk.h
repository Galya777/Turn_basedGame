//
// Created by galya777 on 08.06.25.
//

#ifndef TURN_BASEDGAME_DIBBUK_H
#define TURN_BASEDGAME_DIBBUK_H

#include "Zombi.h"

class Dibbuk : public Zombie {
private:
    int mana;
public:
    Dibbuk();

    bool canAttack() const;
    void attack(Unit& target) override;
    Unit* clone() const override {
        return new Dibbuk(*this);
    }
    std::string getType() const override { return "Dibbuk"; }
};

#endif // TURN_BASEDGAME_DIBBUK_H
