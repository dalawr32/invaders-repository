/*
 * Sprite.h
 *
 *  Created on: Apr 7, 2017
 *      Author: Daniel
 *
 * Represents any object that would eventually be turned into a sprite,
 * such as the player, enemies, and bullets.
 */

#ifndef SPRITE_H_
#define SPRITE_H_

namespace proj{
class Sprite {
public:
	/**
	 * Default destructor for Sprites.
	 */
	virtual ~Sprite(){};

	/**
	 * Gets X coordinate of this sprite.
	 */
	virtual double getX() const noexcept;

	/**
	 * Gets Y coordinate of this sprite.
	 */
	virtual double getY() const noexcept;

	/**
	 * Returns the width of this sprite.
	 */
	virtual int getWidth() const noexcept;

	/**
	 * Returns the height of this sprite.
	 */
	virtual int getHeight() const noexcept;

	/**
	  * Changes the width of this sprite;
	  */
    virtual void setWidth(/**Specified width*/ int width);

    /**
      * Changes the height of this sprite;
      */
    virtual void setHeight(/**Specified height*/ int height);

	/**
	 * Sets the X coordinate of this sprite.
	 * Virtual so restrictions on sprite location
	 * can be placed.
	 */
	virtual void setX(/** New x position*/ double x);

	/**
	 * Sets the Y coordinate of this sprite.
	 * Virtual so restrictions on possible sprite
	 * location can be placed.
	 */
	virtual void setY(/** New y position*/ double y);

	/**
	 * Gets the X speed of this sprite.
	 */
	virtual double get_X_Speed() noexcept;

	/**
	 * Gets the Y speed of this sprite.
	 */
	virtual double get_Y_Speed() noexcept;

	/**
	 * Sets the X velocity of this sprite.
	 */
	virtual void set_X_Speed(/**New x speed*/ double x_speed);

	/**
	 * Sets the Y velocity of this sprite.
	 */
	virtual void set_Y_Speed(/**New y speed*/ double y_speed);

	/**
	  * Gets the angle of the sprite in degrees.
	  */
    virtual int getAngle() const noexcept;

    /**
      * Sets the angle of the sprite in degrees.
      */
    virtual void setAngle(/**New degree angle of sprite*/int angle) noexcept;

	/**
	 * Gets the velocity of this sprite.
	 */
	virtual double getSpeed() noexcept;

	/**
	  * Moves the sprite.
	  */
    virtual void move_sprite();

	/**
	 * Determines whether this Sprite is colliding with another Sprite.
	 */
	virtual bool isColliding(/**Sprite colliding with*/const Sprite& other) noexcept;

	/**
	  * Determines whether it is a player.
	  */
    virtual bool isPlayer();

    /**
      * Determines whether it is an enemy.
      */
    virtual bool isEnemy();

    /**
      * Returns the index of the image representing the specific sprite.
      */
    virtual int getImageIndex();

protected:
    /**
      * Creates a default sprite.
      */
    Sprite();

	/**
	 * Constructor for the Sprite class.
	 */
	Sprite(/**X position*/double x, /**Y position*/double y, /**Width of sprite*/int width, /**Height of sprite*/int height);

private:
	/**
	 * Represents the x coordinate.
	 */
	double x_;

	/**
	 * Represents the y coordinate
	 */
	double y_;

	/**
	 * Represents the distance along the x-axis this sprite reaches.
	 */
	int width_;

	/**
	 * Represents the distance along the y-axis this sprite reaches.
	 */
	int height_;

	/**
	  * Represents the angle in degrees the sprite is rotated by.
	  */
    int angle_ = 0;

	/**
	 * Represents the x speed.
	 */
	double x_speed_ = 0.0;

	/**
	 * Represents the y speed.
	 */
	double y_speed_ = 0.0;
};

}


#endif /* SPRITE_H_ */
