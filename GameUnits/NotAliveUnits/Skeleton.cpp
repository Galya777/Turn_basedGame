//
// Created by galya777 on 08.06.25.
//

#include "Skeleton.h"


Skeleton::Skeleton()
        : PureUndead(500, new MediumArmor(8), 100)  // MediumArmor с броня 8, 500 HP, 100 злато
{
}

void Skeleton::attack(Unit& target) {
    target.takeDamage(5);
}
