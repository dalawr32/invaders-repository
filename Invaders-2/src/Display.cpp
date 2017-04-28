/**
  * Source file for the Display class.
  * This class is used to display images
  * from the game world.
  * Much of it has been refactored from
  * Prof. Kenneth Baclawski's
  * ping project which can be found at
  * http://www.ccs.neu.edu/home/kenb/17/spr/3520/sample/ping4/
  * The player and enemy sprite images come from
  * "MillionthVector" at
  * http://millionthvector.blogspot.com/p/free-sprites.html
  * under a Creative Commons Attribution 4.0 International
  * License, the full details of which can be accessed at
  * https://creativecommons.org/licenses/by/4.0/
  */

#include <SDL.h>
#include <SDL_image.h>
#include <stdexcept>
#include "Player.h"
#include "Weapon.h"
#include <memory>
#include <iostream>
#include <SDL_ttf.h>

#include "Display.h"
#include "World.h"
#include "Bullet.h"
#include "Sprite.h"
#include "Spark.h"

using namespace proj;
using namespace std;

Display::Display(int width, int height)
  : width_(width), height_(height) {

  // Initialize SDL2

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    throw domain_error(string("SDL Initialization failed due to: ") + SDL_GetError());
  }

  // Construct the screen window

  window_ = SDL_CreateWindow("Display", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED,
                             width_, height_, SDL_WINDOW_SHOWN);
  if (!window_) {
    close();
    throw domain_error(string("Unable to create the window due to: ") + SDL_GetError());
  }

  // Construct the renderer

  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer_) {
    close();
    throw domain_error(string("Unable to create the renderer due to: ") + SDL_GetError());
  }

  // Clear the window

  clearBackground();
}

Display::~Display() {
  close();
}

void Display::close() noexcept {
  // Delete the SDL2 resources in reverse order of
  // their construction, starting with the images

  for (SDL_Texture* image : images_) {
    if (image) {
      SDL_DestroyTexture(image);
    }
  }

  // Clear the collection of images to ensure
  // idempotence

  images_.clear();

  // Destroy the renderer and window, and set the
  // variables to nullptr to ensure idempotence

  if (renderer_) {
    SDL_DestroyRenderer(renderer_);
    renderer_ = nullptr;
  }
  if (window_) {
    SDL_DestroyWindow(window_);
    window_ = nullptr;
  }

  // The last step is to quit SDL

  SDL_Quit();
}

void Display::addImage(const string& fileLocation) noexcept {
  if (renderer_) {

    // Load the image from the file

    SDL_Surface* imageSurface = IMG_Load(fileLocation.c_str());

    if (imageSurface) {

      // Convert the image to a texture

      SDL_Texture* imageTexture =
        SDL_CreateTextureFromSurface(renderer_, imageSurface);
      if (imageTexture) {

        // Add the image to the collection

        images_.push_back(imageTexture);
      } else {
        cerr << "Unable to load the image file at " << fileLocation
             << " due to: " << SDL_GetError() << "type: texture error" << endl;
      }

      // The surface is not longer needed

      SDL_FreeSurface(imageSurface);
    } else {
      cerr << "Unable to load the image file at " << fileLocation
           << " due to: " << SDL_GetError() << " type: load error" << endl;
    }
  }
}

void Display::refresh(World& world) {
    if (renderer_) {
        //Clear whole background.
        clearBackground();
        for (shared_ptr<Bullet> b : world.getBullets()) {
            drawSprite(b);
        }
        shared_ptr<Player> player = world.getPlayer();
        drawSprite(player);
        for (shared_ptr<Enemy> e : world.getEnemies()) {
            drawSprite(e);
        }

        for (shared_ptr<Spark> s : world.getSparks()) {
            drawSprite(s);
        }
        drawUI(world);
    } else {
        close();
        throw domain_error("Invalid image index ");
    }
    SDL_RenderPresent(renderer_);
}

void Display::drawUI(World& world) {
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);

    SDL_Rect* rect;
    rect->x = 0;
    rect->y = 700;
    rect->w = 700;
    rect->h = 200;

    //SDL_RenderDrawRect(renderer_, rect);

    SDL_RenderFillRect(renderer_, rect);

    SDL_SetRenderDrawColor(renderer_, 200, 50, 50, 255);

    SDL_Rect fullHealthBar;
    fullHealthBar.x = 200;
    fullHealthBar.y = 725;
    fullHealthBar.w = 300;
    fullHealthBar.h = 50;

    SDL_Rect currentHealthBar;
    currentHealthBar.x = 200;
    currentHealthBar.y = 725;
    currentHealthBar.w = 300 * world.getPlayer()->getHealth() / world.getPlayer()->getMaxHealth();
    currentHealthBar.h = 50;

    SDL_RenderFillRect(renderer_, &currentHealthBar);

    SDL_RenderDrawRect(renderer_, &fullHealthBar);
}

void Display::drawSprite(shared_ptr<Sprite> sprite) {

    SDL_Rect destination = {sprite->getX(), sprite->getY(), sprite->getWidth(), sprite->getHeight()};
    //Player p = Player(shared_ptr<Weapon<Bullet>>(), 100);
   // SDL_Rect destination = {0, 0, 10, 10};

    //Get the image for the player.
    SDL_Texture* imageTexture = images_.at(sprite->getImageIndex());

    if (imageTexture) {

          // Render the image at the location

            if (SDL_RenderCopyEx(renderer_, imageTexture, nullptr,
                               &destination, sprite->getAngle(),
                               nullptr, SDL_FLIP_NONE) != 0) {
            close();
            throw domain_error(string("Unable to render a sprite due to: ")
                               + SDL_GetError());

            }
    }else {
        close();
        throw domain_error("Missing image texture");
    }
}

void Display::clearBackground() {
  if (renderer_) {

    // Clear the window to opaque white

    if (SDL_SetRenderDrawColor(renderer_, 0000, 0000, 0000, 0000) != 0) {
      close();
      throw domain_error(string("Unable to set the background color due to: ")
                         + SDL_GetError());
    }
    if (SDL_RenderClear(renderer_) != 0) {
      close();
      throw domain_error(string("Unable to set the background color due to: ")
                         + SDL_GetError());
    }
  }
}

