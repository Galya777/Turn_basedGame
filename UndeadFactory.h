//
// Created by galya777 on 09.06.25.
//

#ifndef TURN_BASEDGAME_UNDEADFACTORY_H
#define TURN_BASEDGAME_UNDEADFACTORY_H

#include <string>
#include <vector>
#include "GameUnits/Basics/Unit.h"

class UndeadFactory {
private:
    std::vector<std::string> sourceTypes;
    std::vector<Unit*> undeadPrototypes;

public:
    UndeadFactory();
    ~UndeadFactory();

    void registerConversion(const std::string& fromType, Unit* undeadPrototype);
    Unit* getUndeadFor(const std::string& fromType) const;
};

#endif // TURN_BASEDGAME_UNDEADFACTORY_H


