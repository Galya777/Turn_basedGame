//
// Created by galya777 on 10.06.25.
//

#include "GameState.h"
#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include "ConfigLoader.h"

GameState::GameState() = default;

GameState::~GameState() {
    clearCurrentUnits();
    clearCommanders();
}

void GameState::clearCurrentUnits() {
    for (auto* u : currentLivingUnits) delete u;
    currentLivingUnits.clear();
    for (auto* u : currentUndeadUnits) delete u;
    currentUndeadUnits.clear();
}

void GameState::clearCommanders() {
    for (auto* c : availableLivingCommanders) delete c;
    availableLivingCommanders.clear();
    for (auto* c : availableUndeadCommanders) delete c;
    availableUndeadCommanders.clear();
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
    if (commander) availableLivingCommanders.push_back(commander);
}

void GameState::addUndeadCommander(Comander* commander) {
    if (commander) availableUndeadCommanders.push_back(commander);
}

std::vector<Unit*>& GameState::getCurrentLivingUnits() { return currentLivingUnits; }
std::vector<Unit*>& GameState::getCurrentUndeadUnits() { return currentUndeadUnits; }

void GameState::saveToFile(const std::string& filename) {
    std::ofstream out(filename, std::ios::out | std::ios::trunc);
    if (!out) {
        std::cerr << "Error: Unable to open file for saving: " << filename << "\n";
        return;
    }

    out << goldPlayer1 << ' ' << goldPlayer2 << '\n'
        << winsPlayer1 << ' ' << winsPlayer2 << '\n';

    for (const auto* cmd : availableLivingCommanders) {
        out << "L|" << cmd->serialize() << '\n';
    }
    for (const auto* cmd : availableUndeadCommanders) {
        out << "U|" << cmd->serialize() << '\n';
    }

    std::cout << "Game state saved to " << filename << "\n";
}

void GameState::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Error: Unable to open file for loading: " << filename << "\n";
        return;
    }

    clearCurrentUnits();
    clearCommanders();

    std::string line;

    // Load gold
    if (!std::getline(in, line)) {
        std::cerr << "Error: File is empty or corrupt (missing gold data).\n";
        return;
    }
    std::istringstream goldStream(line);
    if (!(goldStream >> goldPlayer1 >> goldPlayer2)) {
        std::cerr << "Error: Invalid gold values.\n";
        return;
    }

    // Load wins
    if (!std::getline(in, line)) {
        std::cerr << "Error: Missing win data.\n";
        return;
    }
    std::istringstream winsStream(line);
    if (!(winsStream >> winsPlayer1 >> winsPlayer2)) {
        std::cerr << "Error: Invalid win data.\n";
        return;
    }

    // Load commanders
    while (std::getline(in, line)) {
        if (line.size() < 3 || line[1] != '|') {
            std::cerr << "Warning: Skipping invalid line: " << line << "\n";
            continue;
        }

        char faction = line[0];
        std::string data = line.substr(2);

        Comander* cmd = Comander::deserialize(data);
        if (!cmd) {
            std::cerr << "Warning: Could not deserialize commander: " << data << "\n";
            continue;
        }

        if (faction == 'L') {
            availableLivingCommanders.push_back(cmd);
        } else if (faction == 'U') {
            availableUndeadCommanders.push_back(cmd);
        } else {
            std::cerr << "Warning: Unknown commander faction: " << faction << "\n";
            delete cmd;
        }
    }

    std::cout << "Game loaded successfully from " << filename << "\n";
}

void GameState::reset() {
    goldPlayer1 = 1000;
    goldPlayer2 = 1000;
    winsPlayer1 = 0;
    winsPlayer2 = 0;
    clearCurrentUnits();
    clearCommanders();
    selectedLivingCommander = nullptr;
    selectedUndeadCommander = nullptr;
}

void GameState::generateRandomUndeadArmy() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> unitCountDist(1, 5);
    int count = unitCountDist(gen);

    CommanderLoader loader;
    std::vector<std::string> undeadUnitTypes = {
            "Skeleton", "Gul", "Necromancer", "Zombi", "Dibbuk", "Reverant", "Ghost"
    };
    std::uniform_int_distribution<> typeDist(0, static_cast<int>(undeadUnitTypes.size()) - 1);

    for (int i = 0; i < count; ++i) {
        std::string type = undeadUnitTypes[typeDist(gen)];
        Unit* unit = loader.createUnit(type);
        if (unit) currentUndeadUnits.push_back(unit);
    }

    if (!availableUndeadCommanders.empty()) {
        std::uniform_int_distribution<> cmdDist(0, static_cast<int>(availableUndeadCommanders.size()) - 1);
        selectedUndeadCommander = availableUndeadCommanders[cmdDist(gen)];
    }
}

void GameState::startDuel() {
    std::cout << "\n=== DUEL BEGINS ===\n";
    std::cout << "[DEBUG] Selected Living Commander: " << (selectedLivingCommander ? selectedLivingCommander->getName() : "nullptr") << "\n";
    std::cout << "[DEBUG] Selected Undead Commander: " << (selectedUndeadCommander ? selectedUndeadCommander->getName() : "nullptr") << "\n";

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

    // --- Undead units attack first ---
    std::cout << "\nUndead units attack first:\n";
    for (Unit* attacker : currentUndeadUnits) {
        if (currentLivingUnits.empty()) break;
        Unit* target = currentLivingUnits.front();

        int damage = 10 + (rand() % 11);
        std::cout << "Undead unit deals " << damage << " damage.\n";
        target->takeDamage(damage);

        if (!target->isAlive()) {
            std::cout << "A living unit has been destroyed.\n";
            fallenLivingUnits.push_back(target);
            currentLivingUnits.erase(currentLivingUnits.begin());
        }
    }

    // --- Undead commander ability ---
    std::cout << "\nUndead commander uses ability:\n";
    selectedUndeadCommander->useAbility(currentUndeadUnits, currentLivingUnits, fallenUndeadUnits);

    // --- Living units counterattack ---
    std::cout << "\nLiving units counterattack:\n";
    for (Unit* attacker : currentLivingUnits) {
        if (currentUndeadUnits.empty()) break;
        Unit* target = currentUndeadUnits.front();

        int damage = 10 + (rand() % 11);
        std::cout << "Living unit deals " << damage << " damage.\n";
        target->takeDamage(damage);

        if (!target->isAlive()) {
            std::cout << "An undead unit has been destroyed.\n";
            fallenUndeadUnits.push_back(target);
            currentUndeadUnits.erase(currentUndeadUnits.begin());
        }
    }

    // --- Living commander ability ---
    std::cout << "\nLiving commander uses ability:\n";
    selectedLivingCommander->useAbility(currentLivingUnits, currentUndeadUnits, fallenLivingUnits);

    // --- Undead raise additional units ---
    std::cout << "\nUndead attempt to raise additional units:\n";
    CommanderLoader loader;
    int revivedCount = rand() % 2 + 1;
    for (int i = 0; i < revivedCount; ++i) {
        Unit* u = loader.createUnit("UndeadInfantry");
        if (u) {
            currentUndeadUnits.push_back(u);
            std::cout << "A new undead unit has been raised.\n";
        }
    }

    // --- Final attack by living ---
    std::cout << "\nFinal attack by the living:\n";
    for (Unit* attacker : currentLivingUnits) {
        if (currentUndeadUnits.empty()) break;
        Unit* target = currentUndeadUnits.front();

        int damage = 10 + (rand() % 11);
        std::cout << "Living unit deals " << damage << " damage.\n";
        target->takeDamage(damage);

        if (!target->isAlive()) {
            std::cout << "An undead unit has been destroyed.\n";
            fallenUndeadUnits.push_back(target);
            currentUndeadUnits.erase(currentUndeadUnits.begin());
        }
    }

    // --- Duel result ---
    std::cout << "\n=== DUEL RESULTS ===\n";
    bool livingWin = currentUndeadUnits.empty();
    bool undeadWin = currentLivingUnits.empty();

    if (livingWin && !undeadWin) {
        std::cout << "The living have won the duel!\n";
        incrementWinsPlayer1();
        addGoldPlayer1(100);
    } else if (undeadWin && !livingWin) {
        std::cout << "The undead have won the duel!\n";
        incrementWinsPlayer2();
        addGoldPlayer2(100);
    } else {
        std::cout << "The duel ended in a draw.\n";
    }
}

