//
// Created by galya777 on 08.06.25.
//

#include "Zombi.h"


Zombie::Zombie()
        : RaisedUndead(250, new Unarmored(), 300)
{}

void Zombie::attack(Unit& target) {
    target.takeDamage(15);
}

