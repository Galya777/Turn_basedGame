//
// Created by galya777 on 08.06.25.
//

#include "Necromancer.h"

Necromancer::Necromancer()
        : UndeadCaster(300, new Unarmored(), 400, 200)
{}

void Necromancer::attack(Unit& target) {
    target.takeDamage(4);
}

std::vector<Skeleton*> Necromancer::castSummonSkeletons(const std::vector<Unit*>& deadLivingUnits) {
    std::vector<Skeleton*> summoned;

    if (mana < 150)
        return summoned;

    if (deadLivingUnits.size() < 3)
        return summoned;

    useMana(150);

    // Призоваваме до 3 скелета
    for (int i = 0; i < 3; ++i) {
        Skeleton* newSkeleton = new Skeleton();
        summoned.push_back(newSkeleton);
    }

    return summoned;
}

