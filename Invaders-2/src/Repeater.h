#ifndef REPEATER_H_INCLUDED
#define REPEATER_H_INCLUDED

#include "Weapon.h"
#include "Bullet.h"

namespace proj {
class Repeater : public Weapon<Bullet> {
public:
    /**
      * Creates a single-shot, semi-automatic
      * weapon. All values but damage are
      * standardized.
      */
    Repeater(int damage, bool isPlayer);
};
}

#endif // REPEATER_H_INCLUDED
