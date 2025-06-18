//
// Created by galya777 on 05.06.25.
//

#ifndef TURN_BASEDGAME_WIZARD_H
#define TURN_BASEDGAME_WIZARD_H

#include "LivingUnit.h"
#include "../../Weapons/Armors/LeatherArmor.h"
#include "../../Weapons/MeleeWeapon.h" // или SpellWeapon, ако имаш такава специализация

class Wizard : public LivingUnit {
public:
    Wizard()
            : LivingUnit(
            325,
            new LeatherArmor(3),
            250,
            new MeleeWeapon(10, "Magic Bolt"), // Може да се замени с SpellWeapon
            200
    ) {}

    void attack(Unit& target) override {
        if (getMana() < 50) return; // не атакува, ако няма достатъчно мана

        setMana(getMana() - 50);
        int baseDamage = weapon ? weapon->getDamage() : 0;
        int actualDamage = target.getArmor() ? target.getArmor()->absorbDamage(baseDamage) : baseDamage;
        target.takeDamage(actualDamage);
    }

    std::string getType() const override {
        return "Wizard";
    }
    Unit* clone() const override {
        return new Wizard(*this);
    }
};

#endif //TURN_BASEDGAME_WIZARD_H

