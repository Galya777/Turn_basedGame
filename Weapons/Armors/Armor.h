#ifndef TURN_BASEDGAME_ARMOR_H
#define TURN_BASEDGAME_ARMOR_H

#include <string>

enum class ArmorType {
    UNARMORED,
    LEATHER,
    MEDIUM,
    HEAVY
};

class Armor {
public:
    Armor(ArmorType type, int durability);
    virtual ~Armor() = default;

    virtual Armor* clone() const = 0;

    virtual float getReductionFactor() const = 0; // 0.0 to 1.0
    virtual void onHit() = 0;                      // При удар, се вика за специално поведение

    void degrade();        // Намалява durability с 1
    bool isUsable() const; // Проверява дали е usable (durability > 0)

    int reduceDamage(int dmg);    // Намалява щетите според фактора, ако бронята е usable
    int absorbDamage(int dmg);    // Абсорбира щетите и прилага onHit()

    int getDurability() const;
    ArmorType getType() const;

protected:
    ArmorType type;
    int durability;
};

#endif //TURN_BASEDGAME_ARMOR_H
