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
    ~UndeadFactory() {
        for (Unit* u : undeadPrototypes)
            delete u;
    }

    void registerConversion(const std::string& fromType, Unit* undeadPrototype) {
        sourceTypes.push_back(fromType);
        undeadPrototypes.push_back(undeadPrototype->clone());
    }

    Unit* getUndeadFor(const std::string& fromType) const {
        for (size_t i = 0; i < sourceTypes.size(); ++i) {
            if (sourceTypes[i] == fromType)
                return undeadPrototypes[i]->clone();
        }
        return nullptr;
    }
};

#endif

