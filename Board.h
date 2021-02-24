#pragma once

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include "Utility.h"
#include "PowerUp.h"
#include "Snake.h"

class Snake;

class Board {

public:
	Board(int width, int height);

	sf::Vector2f getSize();
	sf::Vector2f getOffset();

	void setColor(sf::Color color);

	void updatePowerUp();
	void checkPowerUpCollision(Snake *s);

	void addSnake(Snake *s);

	void draw(sf::RenderWindow& window);

	bool checkEnemyCollision(Snake *player);

private:
	sf::Vector2f size;
	sf::Vector2f offset;
	sf::RectangleShape background;

	sf::Clock timer;
	sf::Clock generateThreeTimer;

	std::vector<PowerUp*> powerUps;
	std::vector<Snake*> snakes;

	float nextPowerUp;
	float delay;

	int generateThreeCount;

	bool generateThree;
};