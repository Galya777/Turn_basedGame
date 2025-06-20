#ifndef TURN_BASEDGAME_COMMANDERLOADER_H
#define TURN_BASEDGAME_COMMANDERLOADER_H

#include <string>
#include <vector>
#include "GameUnits/Comanders/Comander.h"
#include "Weapons/Armors/Armor.h"

class CommanderLoader {
private:
    std::vector<Comander*> livingCommanders;
    std::vector<Comander*> undeadCommanders;

public:
    static Armor* createArmor(const std::string& name);
    Unit* createUnit(const std::string& unitType, bool isCommander = false);
    void assignUnitsToCommander(Comander* commander, const std::vector<std::string>& unitTypes);
    bool commanderNameExists(const std::string& name);
    void parseCommanderLine(const std::string& line, bool isLiving);
    void loadCommandersFromFile(const std::string& filename, bool isLiving);
    const std::vector<Comander*>& getLivingCommanders() const;
    const std::vector<Comander*>& getUndeadCommanders() const;
    ~CommanderLoader();
};

#endif // TURN_BASEDGAME_COMMANDERLOADER_H
