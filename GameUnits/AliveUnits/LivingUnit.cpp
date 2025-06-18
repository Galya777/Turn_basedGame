//
// Created by galya777 on 11.05.25.
//

#include "LivingUnit.h"


void LivingUnit::attack(Unit& target) {
int baseDamage = weapon ? weapon->getDamage() : 10; // default base damage
int reduced = target.getArmor() ? target.getArmor()->absorbDamage(baseDamage) : baseDamage;
target.takeDamage(reduced);
}


