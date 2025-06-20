// Created by galya777 on 10.06.25.

#include "GameState.h"
#include <random>
#include <iostream>
#include <fstream>
#include "ConfigLoader.h"

GameState::GameState() = default;

GameState::~GameState() {
    for (auto* u : currentLivingUnits) delete u;
    for (auto* u : currentUndeadUnits) delete u;
    for (auto* c : availableLivingCommanders) delete c;
    for (auto* c : availableUndeadCommanders) delete c;
}


int GameState::getGoldPlayer1() const { return goldPlayer1; }
int GameState::getGoldPlayer2() const { return goldPlayer2; }
void GameState::addGoldPlayer1(int amount) { goldPlayer1 += amount; }
void GameState::addGoldPlayer2(int amount) { goldPlayer2 += amount; }

int GameState::getWinsPlayer1() const { return winsPlayer1; }
int GameState::getWinsPlayer2() const { return winsPlayer2; }
void GameState::incrementWinsPlayer1() { winsPlayer1++; }
void GameState::incrementWinsPlayer2() { winsPlayer2++; }

void GameState::setSelectedLivingCommander(Comander* c) { selectedLivingCommander = c; }
void GameState::setSelectedUndeadCommander(Comander* c) { selectedUndeadCommander = c; }

Comander* GameState::getSelectedLivingCommander() const { return selectedLivingCommander; }
Comander* GameState::getSelectedUndeadCommander() const { return selectedUndeadCommander; }

std::vector<Comander*>& GameState::getAvailableLivingCommanders() { return availableLivingCommanders; }
std::vector<Comander*>& GameState::getAvailableUndeadCommanders() { return availableUndeadCommanders; }

void GameState::addLivingCommander(Comander* commander) {
    availableLivingCommanders.push_back(commander);
}

void GameState::addUndeadCommander(Comander* commander) {
    availableUndeadCommanders.push_back(commander);
}

std::vector<Unit*>& GameState::getCurrentLivingUnits() { return currentLivingUnits; }
std::vector<Unit*>& GameState::getCurrentUndeadUnits() { return currentUndeadUnits; }

void GameState::clearCurrentUnits() {
    for (auto* u : currentLivingUnits) delete u;
    for (auto* u : currentUndeadUnits) delete u;
    currentLivingUnits.clear();
    currentUndeadUnits.clear();
}

void GameState::saveToFile(const std::string& filename) {
    std::ofstream out(filename, std::ios::out | std::ios::trunc);
    if (!out.is_open()) {
        std::cerr << "Error: Unable to open file for saving: " << filename << "\n";
        return;
    }

    out << goldPlayer1 << ' ' << goldPlayer2 << '\n';
    out << winsPlayer1 << ' ' << winsPlayer2 << '\n';

    for (const auto* cmd : availableLivingCommanders) {
        out << "L|" << cmd->serialize() << '\n';
    }
    for (const auto* cmd : availableUndeadCommanders) {
        out << "U|" << cmd->serialize() << '\n';
    }

    out.close();
    std::cout << "Game state saved to " << filename << "\n";
}



void GameState::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Error: Unable to open file for loading: " << filename << "\n";
        return;
    }

    clearCurrentUnits();
    for (auto* c : availableLivingCommanders) delete c;
    for (auto* c : availableUndeadCommanders) delete c;
    availableLivingCommanders.clear();
    availableUndeadCommanders.clear();

    std::string headerLine;
    if (!std::getline(in, headerLine)) {
        std::cerr << "Error: File is empty or corrupt.\n";
        return;
    }

    std::istringstream goldStream(headerLine);
    if (!(goldStream >> goldPlayer1 >> goldPlayer2)) {
        std::cerr << "Error: Invalid gold values.\n";
        return;
    }

    if (!std::getline(in, headerLine)) {
        std::cerr << "Error: Missing win data.\n";
        return;
    }

    std::istringstream winStream(headerLine);
    if (!(winStream >> winsPlayer1 >> winsPlayer2)) {
        std::cerr << "Error: Invalid win data.\n";
        return;
    }

    std::string line;
    while (std::getline(in, line)) {
        if (line.size() < 3 || line[1] != '|') {
            std::cerr << "Warning: Skipping invalid line: " << line << "\n";
            continue;
        }

        char type = line[0];
        std::string data = line.substr(2);
        Comander* cmd = Comander::deserialize(data);

        if (!cmd) {
            std::cerr << "Warning: Could not deserialize commander: " << data << "\n";
            continue;
        }

        if (type == 'L') {
            availableLivingCommanders.push_back(cmd);
        } else if (type == 'U') {
            availableUndeadCommanders.push_back(cmd);
        } else {
            std::cerr << "Warning: Unknown commander type: " << type << "\n";
            delete cmd;
        }
    }

    in.close();
    std::cout << "Game loaded successfully from " << filename << "\n";
}


void GameState::reset() {
    goldPlayer1 = 1000;
    goldPlayer2 = 1000;
    winsPlayer1 = 0;
    winsPlayer2 = 0;
    clearCurrentUnits();
    selectedLivingCommander = nullptr;
    selectedUndeadCommander = nullptr;
}

void GameState::generateRandomUndeadArmy() {
    std::random_device rd;
    std::mt19937 gen(rd());

    // ✅ Случаен брой немъртви единици (от 1 до 5)
    std::uniform_int_distribution<> unitCount(1, 5);
    int count = unitCount(gen);

    CommanderLoader loader;
    std::vector<std::string> undeadUnitTypes = { "Skeleton", "Gul", "Necromancer", "Zombi", "Dibbuk", "Reverant", "Ghost" };

    std::uniform_int_distribution<> typeDist(0, (int)undeadUnitTypes.size() - 1);

    for (int i = 0; i < count; ++i) {
        std::string randomType = undeadUnitTypes[typeDist(gen)];
        Unit* unit = loader.createUnit(randomType);
        if (unit) currentUndeadUnits.push_back(unit);
    }

    // ✅ Случаен немъртъв главнокомандващ
    if (!availableUndeadCommanders.empty()) {
        std::uniform_int_distribution<> cmdDist(0, (int)availableUndeadCommanders.size() - 1);
        selectedUndeadCommander = availableUndeadCommanders[cmdDist(gen)];
    }
}

void GameState::startDuel() {
    std::cout << "\n=== DUEL BEGINS ===\n";
    std::cout << "[DEBUG] selectedLivingCommander = " << (selectedLivingCommander ? selectedLivingCommander->getName() : "nullptr") << "\n";
    std::cout << "[DEBUG] selectedUndeadCommander = " << (selectedUndeadCommander ? selectedUndeadCommander->getName() : "nullptr") << "\n";

    if (!selectedLivingCommander || !selectedUndeadCommander) {
        std::cout << "Error: Both factions must have a selected commander.\n";
        return;
    }

    if (currentLivingUnits.empty() || currentUndeadUnits.empty()) {
        std::cout << "Error: Both factions must have at least one unit.\n";
        return;
    }

    std::vector<Unit*> fallenLivingUnits;
    std::vector<Unit*> fallenUndeadUnits;

    std::cout << "\nUndead units attack first:\n";
    for (Unit* attacker : currentUndeadUnits) {
        if (currentLivingUnits.empty()) break;
        Unit* target = currentLivingUnits.front();

        int damage = 10 + rand() % 11;
        std::cout << "Undead unit deals " << damage << " damage.\n";
        target->takeDamage(damage);

        if (!target->isAlive()) {
            std::cout << "A living unit has been destroyed.\n";
            fallenLivingUnits.push_back(target);
            currentLivingUnits.erase(currentLivingUnits.begin());
        }
    }

    std::cout << "\nUndead commander uses ability:\n";
    selectedUndeadCommander->useAbility(currentUndeadUnits, currentLivingUnits, fallenUndeadUnits);

    std::cout << "\nLiving units counterattack:\n";
    for (Unit* attacker : currentLivingUnits) {
        if (currentUndeadUnits.empty()) break;
        Unit* target = currentUndeadUnits.front();

        int damage = 10 + rand() % 11;
        std::cout << "Living unit deals " << damage << " damage.\n";
        target->takeDamage(damage);

        if (!target->isAlive()) {
            std::cout << "An undead unit has been destroyed.\n";
            fallenUndeadUnits.push_back(target);
            currentUndeadUnits.erase(currentUndeadUnits.begin());
        }
    }

    std::cout << "\nLiving commander uses ability:\n";
    selectedLivingCommander->useAbility(currentLivingUnits, currentUndeadUnits, fallenLivingUnits);

    std::cout << "\nUndead attempt to raise additional units:\n";

    CommanderLoader loader;
    int revived = rand() % 2 + 1;
    for (int i = 0; i < revived; ++i) {
        Unit* u = loader.createUnit("UndeadInfantry");
        if (u) {
            currentUndeadUnits.push_back(u);
            std::cout << "A new undead unit has been raised.\n";
        }
    }

    std::cout << "\nFinal attack by the living:\n";
    for (Unit* attacker : currentLivingUnits) {
        if (currentUndeadUnits.empty()) break;
        Unit* target = currentUndeadUnits.front();

        int damage = 10 + rand() % 11;
        std::cout << "Living unit deals " << damage << " damage.\n";
        target->takeDamage(damage);

        if (!target->isAlive()) {
            std::cout << "An undead unit has been destroyed.\n";
            fallenUndeadUnits.push_back(target);
            currentUndeadUnits.erase(currentUndeadUnits.begin());
        }
    }

    std::cout << "\n=== DUEL RESULTS ===\n";
    bool livingWin = currentUndeadUnits.empty();
    bool undeadWin = currentLivingUnits.empty();

    if (livingWin && !undeadWin) {
        std::cout << "The living have won the duel.\n";
        incrementWinsPlayer1();
    } else if (undeadWin && !livingWin) {
        std::cout << "The undead have won the duel.\n";
        incrementWinsPlayer2();
    } else {
        std::cout << "The duel ends in a draw. Both factions still have units remaining.\n";
    }

    std::cout << "\nEach faction receives 1000 gold.\n";
    addGoldPlayer1(1000);
    addGoldPlayer2(1000);

    if (getWinsPlayer1() >= 3) {
        std::cout << "\nThe living have won the game with 3 victories!\n";
        reset();
    } else if (getWinsPlayer2() >= 3) {
        std::cout << "\nThe undead have won the game with 3 victories!\n";
        reset();
    } else {
        std::cout << "The game continues. Score - Living: " << getWinsPlayer1()
                  << ", Undead: " << getWinsPlayer2() << "\n";
    }

    for (Unit* u : fallenLivingUnits) delete u;
    for (Unit* u : fallenUndeadUnits) delete u;

    currentLivingUnits.clear();
    currentUndeadUnits.clear();
    selectedLivingCommander = nullptr;
    selectedUndeadCommander = nullptr;

    std::cout << "=== END OF DUEL ===\n";
}




