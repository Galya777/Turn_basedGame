#include "Comander.h"
#include "../../Weapons/Armors/LeatherArmor.h"
#include "../../Weapons/Armors/MediumArmor.h"
#include "../../Weapons/Armors/HeavyArmor.h"
#include "../../Weapons/Armors/Unarmored.h"
#include <sstream>
#include "../../ConfigLoader.h"

Armor* createArmorFromName(const std::string& name) {
    if (name == "LEATHER") return new LeatherArmor(50);
    if (name == "MEDIUM") return new MediumArmor(30);
    if (name == "HEAVY") return new HeavyArmor(70);
    return new Unarmored(); // Default
}
std::ostream& operator<<(std::ostream& os, ArmorType type) {
    switch (type) {
        case ArmorType::UNARMORED: return os << "UNARMORED";
        case ArmorType::LEATHER:   return os << "LEATHER";
        case ArmorType::MEDIUM:    return os << "MEDIUM";
        case ArmorType::HEAVY:     return os << "HEAVY";
        default:                   return os << "UNKNOWN";
    }
}
std::string Comander::serialize() const {
    std::ostringstream out;
    out << getCommanderType() << ';'
        << name << ';'
        << getHP() << ';'
        << mana << ';'
        << attackPower << ';'
        << goldCost << ';'
        << (armor ? armor->getType() : ArmorType::UNARMORED) << ';'
        << controlledUnits.size();

    for (const auto* unit : controlledUnits) {
        out << ';' << unit->getType() << ':' << unit->getHP() << ':' << unit->getGoldCost()
            << ':' << unit->getArmor()->getType();
    }

    return out.str();
}

Comander* Comander::deserialize(const std::string& data) {
    std::istringstream in(data);
    std::string token;

    std::getline(in, token, ';');
    std::string type = token; // e.g. "Necromancer", "Commander"

    std::getline(in, token, ';');
    std::string name = token;

    std::getline(in, token, ';');
    int hp = std::stoi(token);

    std::getline(in, token, ';');
    int mana = std::stoi(token);

    std::getline(in, token, ';');
    int attackPower = std::stoi(token);

    std::getline(in, token, ';');
    int goldCost = std::stoi(token);

    std::getline(in, token, ';');
    ArmorType armorType = static_cast<ArmorType>(std::stoi(token));
    Armor* armor = nullptr;

    switch (armorType) {
        case ArmorType::LEATHER: armor = new LeatherArmor(50); break;
        case ArmorType::MEDIUM: armor = new MediumArmor(30); break;
        case ArmorType::HEAVY: armor = new HeavyArmor(70); break;
        default: armor = new Unarmored(); break;
    }

    std::getline(in, token, ';');
    int numUnits = std::stoi(token);

    Comander* cmd = new Comander(name, hp, mana, armor, goldCost, attackPower);

    for (int i = 0; i < numUnits; ++i) {
        std::getline(in, token, ';');
        std::istringstream unitStream(token);
        std::string unitTypeStr;
        int unitHp, unitCost, unitArmorInt;

        std::getline(unitStream, unitTypeStr, ':');
        unitStream >> unitHp;
        unitStream.ignore(1); // skip ':'
        unitStream >> unitCost;
        unitStream.ignore(1);
        unitStream >> unitArmorInt;

        Armor* unitArmor;
        switch (static_cast<ArmorType>(unitArmorInt)) {
            case ArmorType::LEATHER: unitArmor = new LeatherArmor(50); break;
            case ArmorType::MEDIUM: unitArmor = new MediumArmor(30); break;
            case ArmorType::HEAVY: unitArmor = new HeavyArmor(70); break;
            default: unitArmor = new Unarmored(); break;
        }

        for (int i = 0; i < numUnits; ++i) {
            std::getline(in, token, ';');
            std::istringstream unitStream(token);
            std::string unitTypeStr;
            int unitHp, unitCost, unitArmorInt;

            std::getline(unitStream, unitTypeStr, ':');
            unitStream >> unitHp;
            unitStream.ignore(1); // skip ':'
            unitStream >> unitCost;
            unitStream.ignore(1);
            unitStream >> unitArmorInt;

            CommanderLoader loader;
            Unit* unit = loader.createUnit(unitTypeStr);
            if (unit) {
                unit->setHP(unitHp);
                unit->setGoldCost(unitCost);
                // Замяна на бронята
                Armor* armor = nullptr;
                switch (static_cast<ArmorType>(unitArmorInt)) {
                    case ArmorType::LEATHER: armor = new LeatherArmor(50); break;
                    case ArmorType::MEDIUM: armor = new MediumArmor(30); break;
                    case ArmorType::HEAVY: armor = new HeavyArmor(70); break;
                    default: armor = new Unarmored(); break;
                }
                unit->setArmor(armor);
                cmd->addUnit(unit);
            }
        }

    }

    return cmd;
}
