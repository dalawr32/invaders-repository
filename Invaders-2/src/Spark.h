#ifndef SPARK_H
#define SPARK_H

/**
  * Created by Daniel Lawrence.
  * Spark class represents the Sprites created momentarily when a player or enemy is damaged.
  */

#include "Sprite.h"

namespace proj {
class Spark : public Sprite {
public:
    /**
      * Creates a Spark.
      */
    Spark(/**X coordinate*/int x,
          /**Y coordinate*/ int y,
          /**Determines whether it's from pro-player bullets*/bool hitEnemy);

    /**
      * Updates the Spark on-tick.
      */
    void update();

    /**
      * Determines whether Spark should still exist based on how long it has.
      */
    bool shouldEnd() const noexcept;

    /**
      * Returns the image index of the correct spark.
      */
    virtual int getImageIndex() override;

private:
    /**
      * Determines whether it is reacting to hitting an enemy or not.
      */
    bool hitEnemy_;

    /**
      * Determines how long it's lasted.
      */
    int time_ = 0;
};
}

#endif // SPARK_H
