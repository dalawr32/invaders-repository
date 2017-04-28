/**
  * Created by Daniel.
  * Contains all the information for
  * running the internal logic of
  * the game, such as spawning
  * enemies and moving all objects.
  */

#include "World.h"
#include "Enemy.h"
#include "Player.h"
#include "Basic_Enemy.h"
#include "Basic_Shooter.h"
#include "Repeater.h"
#include "Weapon.h"
#include "Spark.h"
#include "Laser_Shooter.h"
#include <mutex>
#include <memory>
#include <iostream>
#include <cmath>
#include <random>
#include <map>
#include <sys/time.h>
#include <time.h>
#include <chrono>

using namespace std;
using namespace proj;

World::World(int difficulty) {
    difficulty_ = difficulty;
    player_ = make_shared<Player>(Player(make_shared<Weapon<Bullet>>(Repeater(30, true)), 100));

    init();

    /*enemies_.push_back(make_shared<Basic_Enemy>(Basic_Enemy(100, movementMap_.at(0), 150, 0)));
    enemies_.push_back(make_shared<Basic_Shooter>(Basic_Shooter(100, 10, movementMap_.at(3), 300, 0)));
    enemies_.push_back(make_shared<Laser_Shooter>(Laser_Shooter(200, 10, movementMap_.at(1), 300, -50)));*/


    seed_seq seed = {0, 670};
    mt19937 engine(seed);
}

void World::init() {
    //This function makes an enemy move in a straight line towards and away from the player.
    auto vertical = [](shared_ptr<Player> player, Enemy* e) {
        if (e->get_Y_Speed() == 0) {
            e->set_Y_Speed(3);
        }
        if (e->getY() > 700) {
            e->set_Y_Speed(-3);
        }
        else if (e->getY() < 0) {
            e->set_Y_Speed(3);
        }
    };

    //This function makes an enemy move in a straight line against a random point on screen.
    auto horizontal = [](shared_ptr<Player> player, Enemy* e) {
        if (e->getY() < 300) {
            e->set_Y_Speed(7);
        }
        else {
            e->set_Y_Speed(0);
            if (e->get_X_Speed() == 0) {
                e->set_X_Speed(3);
            }
            if (e->getX() > 700 - e->getWidth()) {
                e->set_X_Speed(-3);
            }
            else if (e->getX() < 0) {
                e->set_X_Speed(3);
            }
        }
    };

    //This function makes an enemy bounce against the sides of the screen as it moves.
    auto bounce = [](shared_ptr<Player> player, Enemy* e) {
        if (e->get_Y_Speed() == 0) {
            e->set_Y_Speed(3);
        }
        if (e->get_X_Speed() == 0) {
            e->set_X_Speed(5);
        }
        if (e->getY() > 700 - e->getHeight()) {
            e->set_Y_Speed(-3);
        }
        else if (e->getY() < 0) {
            e->set_Y_Speed(3);
        }
        if (e->getX() > 700 - e->getWidth()) {
            e->set_X_Speed(-5);
        }
        else if (e->getX() < 0) {
            e->set_X_Speed(5);
        }
    };

    auto watch = [](shared_ptr<Player> player, Enemy* e) {
        //Let the enemy approach
        if (e->getY() < 200) {
            e->set_Y_Speed(5);
        }
        else {
            //Enemy stops moving once its in range.
            e->set_Y_Speed(0);
            //We rotate the enemy based on whether it's aiming at the player or not.
            if (e->getAngle() % 360 >
                (int)(atan2(e->getX() + e->getWidth()/2 - player->getX() + player->getWidth()/2,
                            player->getY() - player->getHeight()/2 - e->getY() + e->getHeight()/2) * 57.3) % 360) {
                e->setAngle(e->getAngle() - 1);
            }
            else if (e->getAngle() % 360 <
                     (int)(atan2(e->getX() + e->getWidth()/2 - player->getX() + player->getWidth()/2,
                                 player->getY() + player->getHeight()/2 - e->getY() + e->getHeight()/2) * 57.3) % 360) {
                e->setAngle(e->getAngle() + 1);
            }
        }
    };

    //Add the functions to the map of movement types.
    this->movementMap_[0]= vertical;

    this->movementMap_[1] = horizontal;

    this->movementMap_[2] = bounce;

    this->movementMap_[3] = watch;

    seed_seq widthSeed = {0, 670};
    this->engine_width_ = mt19937(widthSeed);
    seed_seq heightSeed = {-100, 0};
    engine_height_ = mt19937(heightSeed);

    seed_seq functionSeed = {0, 3};//this->movementMap_.size()};
    engine_fun_ = mt19937(functionSeed);

    seed_seq typeSeed = {0, 2};
    engine_type_ = mt19937(typeSeed);
}

void World::update() {
    /**Updates every bullet in the world*/
    unsigned int i = 0;
    while (i < bullets_.size() ) {
        shared_ptr<Bullet> b = bullets_.at(i);
        b->Sprite::move_sprite();
        //Determines if bullet should be removed.
        bool collided = false;
        //Check bullet against player.
        if (b->isColliding(*player_) && !b->isFriendly()) {
            player_->changeHealth(player_->getHealth() - b->getDamage());
            sparks_.push_back(make_shared<Spark>(Spark(b->getX(), b->getY(), false)));
            collided = true;
        }
        //Check bullet against every enemy.
        for (shared_ptr<Enemy> enemy : enemies_) {
            if (b->isColliding(*enemy) && b->isFriendly()) {
                enemy->changeHealth(enemy->getHealth() - b->getDamage());
                sparks_.push_back(make_shared<Spark>(Spark(b->getX(), b->getY(), true)));
                collided = true;
            }
        }

        if (collided
            || b->getX() > 700 && b->get_X_Speed() >= 0
            || b->getX() < 0 && b->get_X_Speed() <= 0
            || b->getY() > 700 && b->get_Y_Speed() >= 0
            || b->getY() < 0 && b->get_Y_Speed() <= 0) {
            bullets_.erase(bullets_.begin() + i);
        }
        else {
            i++;
        }
    }


    i = 0;
    while (i < sparks_.size()) {
        shared_ptr<Spark> spark = sparks_.at(i);
        if (spark->shouldEnd()) {
            sparks_.erase(sparks_.begin() + i);
        }
        else {
            spark->update();
            i++;
        }
    }


    /**Updates every enemy in the world, removing it if necessary.*/
    i = 0;
    while(i < enemies_.size()) {
        shared_ptr<Enemy> e = enemies_.at(i);
        if (e->getHealth() <= 0) {
            enemies_.erase(enemies_.begin() + i);
        }
        else {
            e->update(player_, bullets_);
            i++;
        }
    }

    if (player_->getHealth() <= 0) {
        //End the game.
        isOver_ = true;
        return;
    }

    int curDifficulty = 0;
    for (shared_ptr<Enemy> e : enemies_) {
        curDifficulty += e->getDifficulty();
    }

    if (curDifficulty < difficulty_ / 2) {
        shared_ptr<Enemy> newEnemy = createEnemy(difficulty_ - curDifficulty);
        curDifficulty += newEnemy->getDifficulty();
        enemies_.push_back(newEnemy);
    }

    player_->move_sprite();
}

bool World::isOver() {
    return isOver_;
}

shared_ptr<Player> World::getPlayer() noexcept {
    return player_;
}

vector<shared_ptr<Enemy>> World::getEnemies() noexcept {
    return enemies_;
}

vector<shared_ptr<Bullet>> World::getBullets() noexcept {
    return bullets_;
}

vector<shared_ptr<Spark>> World::getSparks() noexcept {
    return sparks_;
}

void World::setBullets(vector<shared_ptr<Bullet>> bullets) {
    this->bullets_ = bullets;
}

shared_ptr<Enemy> World::createEnemy(int difficulty_spike) {
    uniform_int_distribution<int> widthPossible(0, 670);
    int x = widthPossible(engine_width_);

    uniform_int_distribution<int> heightPossible(-100, 0);
    int y = heightPossible(engine_height_);

    uniform_int_distribution<int> possible_function(0, movementMap_.size() - 1);
    int fun = possible_function(engine_fun_);

    uniform_int_distribution<int> possible_type(0, 100);
    int type = possible_type(engine_type_);

    if (type < 50) {
        return make_shared<Basic_Shooter>(Basic_Shooter(30, 3, movementMap_.at(fun), x, y));
    }
    else if (type < 80) {
        if (fun > movementMap_.size()/2) {
            return make_shared<Basic_Enemy>(Basic_Enemy(100, movementMap_.at(2), x, y));
        }
        else {
            return make_shared<Basic_Enemy>(100, movementMap_.at(0), x, y);
        }
    }
    else {
        return make_shared<Laser_Shooter>(200, 30, movementMap_.at(1), x, y);
    }
}
