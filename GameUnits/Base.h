#ifndef TURN_BASEDGAME_BASE_H
#define TURN_BASEDGAME_BASE_H

#include <vector>
#include <string>
#include <utility>
#include "Basics/Unit.h"

class UndeadFactory;
class CommanderLoader;

class Base {
private:
    int gold;
    int unitLimit;
    int currentUnitCount;
    std::vector<Unit*> units;
    std::vector<Unit*> commanders;
    std::vector<std::pair<std::string, int>> commanderTypeCount;
    UndeadFactory* undeadFactory;

public:
    Base(int initialGold, int unitLimit, UndeadFactory* undeadFactory);
    ~Base();

    Unit* spawnUnit(Unit* prototype, bool isCommander = false);
    Unit* spawnUnit(const std::string& unitTypeName, bool isCommander = false);
    Unit* resurrectUnit(Unit* deadUnit);

    void addGold(int amount);
    int getGold() const;
    int getUnitLimit() const;
    int getCurrentUnitCount() const;

    const std::vector<Unit*>& getUnits() const;
    const std::vector<Unit*>& getCommanders() const;

    void clearUnits();
    void clearCommanders();
    void recoverUnits();

private:
    void recoverMana(std::vector<Unit*>& unitList);
    int getCommanderTypeCount(const std::string& type) const;
    void incrementCommanderTypeCount(const std::string& type);
};

#endif //TURN_BASEDGAME_BASE_H

