#include "Snake.h"
#include <iostream>

Board::Board(int width,int height) {
	size = sf::Vector2f(width, height);
	offset = sf::Vector2f(5, 5);
	background.setOutlineColor(sf::Color::White);
	background.setSize(size - 2.f * offset);
	background.setOutlineThickness(offset.x);
	background.setFillColor(sf::Color::Transparent);
	background.setPosition(offset);
	delay = 7.f;
	nextPowerUp = 3.f + randFloat(delay);
	generateThree = false;
}

sf::Vector2f Board::getSize() {
	return size - offset;
}

sf::Vector2f Board::getOffset() {
	return offset;
}

void Board::setColor(sf::Color color) {
	background.setOutlineColor(color);
}

void Board::updatePowerUp() {
	if (timer.getElapsedTime().asSeconds() > 3) {
		powerUps.push_back(new PowerUp(sf::Vector2f( 50 + randFloat(size.x - 100), 50 + randFloat(size.y - 100)), PowerUpType(14 + rand() % 3)));
		nextPowerUp = 5 + randFloat(delay);
		timer.restart();
	}

	if (generateThree && generateThreeTimer.getElapsedTime().asMilliseconds() > 300 * generateThreeCount) {
		generateThreeCount++;
		powerUps.push_back(new PowerUp(sf::Vector2f(50 + randFloat(size.x - 100), 50 + randFloat(size.y - 100)), PowerUpType(rand() % 18)));
		if (generateThree > 4) {
			generateThree = false;
		}
	}
}

void Board::draw(sf::RenderWindow &window) {
	window.draw(background);
	for (PowerUp* pu : powerUps) {
		pu->draw(window);
	}
}

void Board::checkPowerUpCollision(Snake *s) {
	for (int i = 0; i < powerUps.size(); i++) {
		if (dist(s->getPosition(), powerUps[i]->getPosition()) < powerUps[i]->getRadius() + s->getSize()) {

			PowerUp* pu = powerUps[i];
			switch (pu->getPowerUpType()) {
			case PowerUpType::DECREASE_MY_SIZE:
				s->setSize(s->getSize() / 2);
				s->addEffect(new PowerUp(sf::Vector2f(0, 0), PowerUpType::DECREASE_MY_SIZE));
				break;
			case PowerUpType::DECREASE_ENEMY_SIZE:
				for (int j = 0; j < snakes.size(); j++) {
					if (snakes[j] == s) {
						continue;
					}
					snakes[j]->setSize(snakes[j]->getSize() / 2);
					snakes[j]->addEffect(new PowerUp(sf::Vector2f(0, 0), PowerUpType::DECREASE_MY_SIZE));
				}
				break;
			case PowerUpType::INCREASE_MY_SIZE:
				s->setSize(s->getSize() * 2);
				s->addEffect(new PowerUp(sf::Vector2f(0, 0), PowerUpType::INCREASE_MY_SIZE));
				break;
			case PowerUpType::INCREASE_ENEMY_SIZE:
				for (int j = 0; j < snakes.size(); j++) {
					if (snakes[j] == s) {
						continue;
					}
					snakes[j]->setSize(snakes[j]->getSize() * 2);
					snakes[j]->addEffect(new PowerUp(sf::Vector2f(0, 0), PowerUpType::INCREASE_MY_SIZE));
				}
				break;
			case PowerUpType::REVERSE_MY_KEYS:
				s->reverseKeys();
				s->addEffect(new PowerUp(sf::Vector2f(0, 0), PowerUpType::REVERSE_MY_KEYS));
				break;
			case PowerUpType::REVERSE_ENEMY_KEYS:
				for (int j = 0; j < snakes.size(); j++) {
					if (snakes[j] == s) {
						continue;
					}
					snakes[j]->reverseKeys();
					snakes[j]->addEffect(new PowerUp(sf::Vector2f(0, 0), PowerUpType::REVERSE_MY_KEYS));
				}
				break;
			case PowerUpType::DECREASE_MY_SPEED:
				s->setSpeed(s->getSpeed() / 2);
				s->addEffect(new PowerUp(sf::Vector2f(0, 0), PowerUpType::DECREASE_MY_SPEED));
				break;
			case PowerUpType::DECREASE_ENEMY_SPEED:
				for (int j = 0; j < snakes.size(); j++) {
					if (snakes[j] == s) {
						continue;
					}
					snakes[j]->setSpeed(snakes[j]->getSpeed() / 2);
					snakes[j]->addEffect(new PowerUp(sf::Vector2f(0, 0), PowerUpType::DECREASE_MY_SPEED));
				}
				break;
			case PowerUpType::INCREASE_MY_SPEED:
				s->setSpeed(s->getSpeed() * 2);
				s->addEffect(new PowerUp(sf::Vector2f(0, 0), PowerUpType::INCREASE_MY_SPEED));
				break;
			case PowerUpType::INCREASE_ENEMY_SPEED:
				for (int j = 0; j < snakes.size(); j++) {
					if (snakes[j] == s) {
						continue;
					}
					snakes[j]->setSpeed(snakes[j]->getSpeed() * 2);
					snakes[j]->addEffect(new PowerUp(sf::Vector2f(0, 0), PowerUpType::INCREASE_ENEMY_SPEED));
				}
				break;
			case PowerUpType::MAKE_ME_POINTY:
				break;
			case PowerUpType::MAKE_ENEMY_POINTY:
				break;
			case PowerUpType::MAKE_ME_DOT:
				s->lineOff();
				s->addEffect(new PowerUp(sf::Vector2f(0, 0), PowerUpType::MAKE_ME_DOT));
				break;
			case PowerUpType::MAKE_WALL_OFF:
				break;
			case PowerUpType::GENERTE_THREE_POWERUPS:
				generateThree = true;
				generateThreeCount = 1;
				generateThreeTimer.restart();
				break;
			case PowerUpType::CLEAN_BOARD:
				for (int j = 0; j < snakes.size(); j++) {
					if (snakes[j] == s) {
						continue;
					}
					snakes[j]->earseSnake();
				}
				break;
			case PowerUpType::CLEAN_MY_LINE:
				s->earseSnake();
				break;
			case PowerUpType::MAKE_WALL_OFF_FOR_ME:
				break;
			}
			
			powerUps.erase(powerUps.begin() + i);
			delete pu;
		}
	}
}

void Board::addSnake(Snake* s) {
	snakes.push_back(s);
}

bool Board::checkEnemyCollision(Snake* s) {
	sf::Vector2f position = s->getPosition();
	for (int i = 0; i < snakes.size(); i++) {
		if (s == snakes[i]) {
			continue;
		}
		for (int j = 0; j < snakes[i]->getLines()->size(); j++) {
			Line* line = (*snakes[i]->getLines())[j];
			for (int k = 0; k < line->getLine().size(); k++) {
				if (dist(position, line->getLine()[k]) <= s->getSize() + line->getThicc()) {
					return true;
				}
			}
		}
	}
	return false;
}