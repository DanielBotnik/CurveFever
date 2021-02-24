#pragma once

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include "Utility.h"
#include <time.h>

enum class PowerUpType {
	DECREASE_MY_SIZE,
	DECREASE_ENEMY_SIZE,
	INCREASE_MY_SIZE,
	INCREASE_ENEMY_SIZE,
	REVERSE_MY_KEYS,
	REVERSE_ENEMY_KEYS,
	DECREASE_MY_SPEED,
	DECREASE_ENEMY_SPEED,
	INCREASE_MY_SPEED,
	INCREASE_ENEMY_SPEED,
	MAKE_ME_POINTY,
	MAKE_ENEMY_POINTY,
	MAKE_ME_DOT,
	MAKE_WALL_OFF,
	GENERTE_THREE_POWERUPS,
	CLEAN_BOARD,
	CLEAN_MY_LINE,
	MAKE_WALL_OFF_FOR_ME,
};

class PowerUp
{
public:
	PowerUp(sf::Vector2f position, PowerUpType powerUpType);
	~PowerUp();
	sf::Vector2f getPosition();
	float getDelay();
	float getRadius();
	PowerUpType getPowerUpType();
	void startTimer();
	bool isTimeUp();
	void draw(sf::RenderWindow& window);
private:

	sf::Texture *texture;
	sf::Sprite sprite;
	sf::Vector2f position;

	float radius;
	float delay;
	
	PowerUpType type;

	sf::Clock timer;
};
