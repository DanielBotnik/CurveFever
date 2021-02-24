#pragma once

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include "Utility.h"
#include "Line.h"
#include "Board.h"

class Board;

class Snake {

public:
	Snake(sf::Vector2f position, sf::Vector2f velocity,sf::Color color,Board *board,sf::Keyboard::Key leftKey,sf::Keyboard::Key rightKey);
	
	void control(float dt);
	void draw(sf::RenderWindow& window);
	void update(float dt);
	void startCollision();
	void lineOn();
	void lineOff();
	void setSize(float size);
	void setSpeed(float speed);
	void addEffect(PowerUp*);
	void reverseKeys();
	void earseSnake();

	bool checkSelfCollision();
	bool checkWallCollision();

	sf::Vector2f getLastPoint();
	sf::Vector2f getPosition();

	std::vector<Line*>* getLines();

	float getSize();
	float getSpeed();

private:
	sf::Vector2f position;
	sf::Vector2f velocity;

	std::vector<Line*> lines;
	std::vector<PowerUp*> effects;

	sf::Color color;

	sf::CircleShape startCircle;
	sf::CircleShape endCircle;

	float size;
	float speed;
	float rotateAngle;
	float delay;
	float nextGap;
	float gapLength;
	
	bool lineTimerEnd;
	bool startTimerEnd;
	bool noLine;
	bool alive;

	sf::Clock lineTimer;
	sf::Clock startTimer;

	Board *board;

	sf::Keyboard::Key leftKey;
	sf::Keyboard::Key rightKey;

};