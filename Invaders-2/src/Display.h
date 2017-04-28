/**
  * Created by Daniel.
  * Much of the code is refactored
  * or heavily borrows from
  * Prof. Kenneth Baclawski's
  * Ping class, which can be found at
  * http://www.ccs.neu.edu/home/kenb/17/spr/3520/sample/ping4/
  */

#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include "World.h"
#include <SDL.h>

namespace proj {
class Display {
public:
    /**
    * Create a graphical display with specified size.
    * @throw domain_error if the display could not
    * be created and initialized.
    */
    Display(/** Display width. */ int width = 700,
    /** Display height. */ int height = 800);

    /**
    * Destruct the graphical display.  This closes
    * the display.
    */
    ~Display();

  /**
   * Close the graphical display and release the
   * resources.
   */
  void close() noexcept;

  /**
   * Add an image to the collection.
   */
  void addImage(/** The location of the file. */
                const std::string& fileLocation) noexcept;

  /**
   * Refresh the display.
   * @throw domain_error if the display could not
   * be refreshed.
   */
  void refresh(/** The sprites to display. */
               World& world);

private:
  /** The display window. */
  SDL_Window* window_ = nullptr;

  /** The display rendering tool. */
  SDL_Renderer* renderer_ = nullptr;

  /** The collection of images. */
  std::vector<SDL_Texture*> images_;

  /** The width of the window. */
  const int width_ = 0;

  /** The height of the window. */
  const int height_ = 0;

  /**
   * Clear the background to black.
   */
  void clearBackground();

  /**
    * Draws each sprite.
    */
  void drawSprite(/**The sprite being drawn*/
                  std::shared_ptr<Sprite> sprite);

  /**
    * Draws the UI for the world.
    */
  void drawUI(World& world);
};
}

#endif // DISPLAY_H_INCLUDED
