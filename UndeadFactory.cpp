//
// Created by galya777 on 09.06.25.
//

#include "UndeadFactory.h"

UndeadFactory::UndeadFactory() = default;

UndeadFactory::~UndeadFactory() {
    for (Unit* u : undeadPrototypes)
        delete u;
}

void UndeadFactory::registerConversion(const std::string& fromType, Unit* undeadPrototype) {
    sourceTypes.push_back(fromType);
    undeadPrototypes.push_back(undeadPrototype->clone());
}

Unit* UndeadFactory::getUndeadFor(const std::string& fromType) const {
    for (size_t i = 0; i < sourceTypes.size(); ++i) {
        if (sourceTypes[i] == fromType)
            return undeadPrototypes[i]->clone();
    }
    return nullptr;
}

