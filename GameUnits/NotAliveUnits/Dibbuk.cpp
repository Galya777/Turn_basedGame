//
// Created by galya777 on 08.06.25.
//

#include "Dibbuk.h"

Dibbuk::Dibbuk()
        : Zombie(), mana(300)
{}

bool Dibbuk::canAttack() const {
    return mana >= 150;
}

void Dibbuk::attack(Unit& target) {
    if (canAttack()) {
        target.takeDamage(15);
        mana -= 150;
    }
    // Ако няма манна, атаката не се извършва (можеш да добавиш съобщение или друго поведение)
}

