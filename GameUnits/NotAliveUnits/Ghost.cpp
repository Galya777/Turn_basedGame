//
// Created by galya777 on 08.06.25.
//

#include "Ghost.h"

Ghost::Ghost()
        : UndeadUnit(0, nullptr, 500), alive(true) // 500 злато цена, няма броня, здраве 0
{}

// Добавя 250 здраве на целева немъртва единица
// Връща true ако успешно, след което самоунищожава Ghost-а
bool Ghost::empowerUndead(UndeadUnit& target) {
    if (!alive) return false; // ако е вече мъртъв, не може
    target.heal(target.getHealth().getCurrent() + 250);
    die(); // самоунищожение
    return true;
}

void Ghost::die() {
    alive = false;
    // Допълнителни действия при унищожение, ако има нужда
}

