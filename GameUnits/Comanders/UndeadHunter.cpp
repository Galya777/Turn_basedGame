//
// Created by galya777 on 09.06.25.
//

#include "UndeadHunter.h"

UndeadHunter::UndeadHunter(const std::string& name)
        : Comander(name, 2000, 1500, new HeavyArmor(17), 0, 75) {}

Comander* UndeadHunter::clone() const {
    return new UndeadHunter(*this);
}

std::string UndeadHunter::getCommanderType() const {
    return "UndeadHunter";
}

bool UndeadHunter::canUseAbility() const {
    return mana >= 1000;
}

void UndeadHunter::useAbility(std::vector<Unit*>& /*allies*/,
                              std::vector<Unit*>& enemies,
                              std::vector<Unit*>& /*fallenAllies*/) {
    if (!canUseAbility()) return;

    // Търсим един немъртъв командир в enemies, за да го унищожим
    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        Unit* enemy = *it;
        if (enemy->getType().find("Undead") != std::string::npos && enemy->isAlive()) {
            enemy->takeDamage(enemy->getHealth().getCurrent()); // Убий го мигновено
            reduceMana(1000);
            break;
        }
    }
}

