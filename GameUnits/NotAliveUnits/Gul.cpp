//
// Created by galya777 on 08.06.25.
//

#include "Gul.h"

Gul::Gul()
        : PureUndead(400, new HeavyArmor(6), 250)
{
}

void Gul::attack(Unit& target) {
    target.takeDamage(12);
}
