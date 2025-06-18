//
// Created by galya777 on 09.06.25.
//

#include "DancerWithBlades.h"

DancerWithBlades::DancerWithBlades(const std::string& name)
        : Comander(name, 4000, 0, new MediumArmor(25), 0, 300) {}

Comander* DancerWithBlades::clone() const {
    return new DancerWithBlades(*this);
}

std::string DancerWithBlades::getCommanderType() const {
    return "DancerWithBlades";
}

bool DancerWithBlades::canUseAbility() const {
    return false; // no abilities
}

void DancerWithBlades::useAbility(std::vector<Unit*>&, std::vector<Unit*>&, std::vector<Unit*>&) {
    //This Character has no ability
}
