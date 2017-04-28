/*
 * Created by Daniel Lawrence.
 * Implementation of the Spark header.
 */


#include "Spark.h"

#include "Sprite.h"


using namespace std;
using namespace proj;

Spark::Spark(int x, int y, bool hitEnemy)
: Sprite(x, y, 0, 0), hitEnemy_(hitEnemy) {}

void Spark::update() {
    this->time_++;
    this->setWidth(time_/2);
    this->setHeight(time_/2);
}

bool Spark::shouldEnd() const noexcept {
    return this->time_ > 20;
}

int Spark::getImageIndex() {
    if (hitEnemy_) {
        return 5;
    }
    else {
        return 6;
    }
}
