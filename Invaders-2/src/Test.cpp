/*
 * Test.cpp
 *
 *  Created on: Apr 8, 2017
 *      Author: Daniel
 */

#include "Player.h"
#include "Weapon.h"
#include "Enemy.h"
#include "Basic_Enemy.h"
#include "Display.h"
#include "World.h"

#include <memory>
#include <functional>
#include <iostream>
#include <ctime>
#include <chrono>

#include "SDL.h"

using namespace std;
using namespace proj;


void events(SDL_Event event, shared_ptr<World> w) {
    shared_ptr<Player> p = w->getPlayer();
    switch (event.type) {
    //What we'll do on certain key events.
    case SDL_KEYDOWN :
        switch (event.key.keysym.sym) {
        //If the key is the left arrow, we move left.
        case SDLK_LEFT:
            p->set_X_Speed(p->get_X_Speed() - 1.5);
            break;
        //If the key is the right arrow, we move right.
        case SDLK_RIGHT:
            p->set_X_Speed(p->get_X_Speed() + 1.5);
            break;
        //*f the key is space, we fire.
        case SDLK_SPACE:
            vector<shared_ptr<Bullet>> bullets = w->getBullets();
            p->fire(bullets, -10);
            w->setBullets(bullets);
            break;
        }
    }
}

int main(int argc, char *argv[]) {

    try {
        //Test various outputs for the static players. These double as tests for Ship and Sprite.
        shared_ptr<Player> p = make_shared<Player>(Player(shared_ptr<Weapon<Bullet>>(), 100));
        shared_ptr<Player> p2 = make_shared<Player>(Player(shared_ptr<Weapon<Bullet>>(), 50));
        if (!(p->getHealth() == p->getMaxHealth() && p->getSpeed() == 0 && p->isColliding(*p2))) {
            return 1;
        }
        //Test outputs with non-static players. These double as tests for virtual classes Ship and Sprite.
        p->changeHealth(p->getHealth() - 5);
        p->setX(p->getX() + 3);
        p->setY(p->getY() + 3);
        if (p->getHealth() == p->getMaxHealth() || p->getX() == p2->getX() || p->getY() == p2->getY() || !p->isColliding(*p2)) {
            return 2;
        }

        //Tests that basic enemy pathing and player damaging works correctly.
        auto basic_path = [](shared_ptr<Player> player, Enemy* enemy)
        {
            enemy->set_Y_Speed(2);
        };

        shared_ptr<Enemy> enemy = make_shared<Basic_Enemy>(Basic_Enemy(50, basic_path));

        p->changeHealth(p->getMaxHealth());

        enemy->setX(p->getX());
        enemy->setY(p->getY());
        vector<shared_ptr<Bullet>> bullets;
        enemy->update(p, bullets);


        if (p->getHealth() == p->getMaxHealth()) {
            return 3;
        }

        Display display = Display();
        display.addImage("resource/player.png");
        display.addImage("resource/basic_enemy.png");
        display.addImage("resource/laserGreen.png");
        display.addImage("resource/laserRed.png");
        display.addImage("resource/basic_shooter.png");
        display.addImage("resource/laserGreenShot.png");
        display.addImage("resource/laserRedShot.png");
        display.addImage("resource/superLaser_enemy.png");

        shared_ptr<World> world = make_shared<World>(World(100));

        SDL_Event event;

        while (!world->isOver()) {
            while(SDL_PollEvent(&event)) {
                events(event, world);
            }

            world->update();
            display.refresh(*world);
        }

        cout << "Game over. Press any key to start again." << endl;

        return 0;
    } catch (const exception& e) {
        cerr << e.what() << endl;
        throw e;//return 5;
    }
}




/**BOOST_AUTO_TEST_CASE(player_test1) {
	Player p(shared_ptr<Weapon>(), 100);
	Player p2(shared_ptr<Weapon>(), 50);

	//Checks that the health is initialized to max health.
	BOOST_CHECK(p.getHealth() == p.getMaxHealth());

	//Checks that the health has been reduced, but max health hasn't.
	p.changeHealth(p.getHealth() - 5);
	BOOST_CHECK(p.getHealth() != p.getMaxHealth());

	//Checks that p and p2 are colliding.
	BOOST_CHECK(p.isColliding(p2));

	//Checks that p is being moved.
	p.setX(p.getX() + 3);
	p.setY(p.getY() + 3);
	BOOST_CHECK(p.getX() != p2.getX());



}*/
