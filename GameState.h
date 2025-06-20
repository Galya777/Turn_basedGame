//
// Created by galya777 on 10.06.25.
//

#ifndef TURN_BASEDGAME_GAMESTATE_H
#define TURN_BASEDGAME_GAMESTATE_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "ConfigLoader.h"
#include "GameUnits/Basics/Unit.h"
#include "GameUnits/Comanders/Comander.h"

class GameState {
private:
    int goldPlayer1 = 1000;
    int goldPlayer2 = 1000;
    int winsPlayer1 = 0;
    int winsPlayer2 = 0;

    std::vector<Unit*> currentLivingUnits;
    std::vector<Unit*> currentUndeadUnits;

    Comander* selectedLivingCommander = nullptr;
    Comander* selectedUndeadCommander = nullptr;

    std::vector<Comander*> availableLivingCommanders;
    std::vector<Comander*> availableUndeadCommanders;

public:
    GameState();
    ~GameState();

    // Достъп до ресурси и победи
    int getGoldPlayer1() const;
    int getGoldPlayer2() const;
    void addGoldPlayer1(int amount);
    void addGoldPlayer2(int amount);

    int getWinsPlayer1() const;
    int getWinsPlayer2() const;
    void incrementWinsPlayer1();
    void incrementWinsPlayer2();

    // Командири
    void setSelectedLivingCommander(Comander* c);
    void setSelectedUndeadCommander(Comander* c);

    Comander* getSelectedLivingCommander() const;
    Comander* getSelectedUndeadCommander() const;

    std::vector<Comander*>& getAvailableLivingCommanders();
    std::vector<Comander*>& getAvailableUndeadCommanders();

    void addLivingCommander(Comander* commander);
    void addUndeadCommander(Comander* commander);

    // Бойни единици
    std::vector<Unit*>& getCurrentLivingUnits();
    std::vector<Unit*>& getCurrentUndeadUnits();
    void clearCurrentUnits();

    // Управление на играта
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    void reset();


    void generateRandomUndeadArmy();

    void startDuel();

    void clearCommanders();
};

#endif //TURN_BASEDGAME_GAMESTATE_H