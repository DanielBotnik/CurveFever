#include "PowerUp.h"
#include <fstream>
#include <iostream>

PowerUp::PowerUp(sf::Vector2f position,PowerUpType type) {
	this->position = position;
	this->type = type;
	this->texture = (sf::Texture*)malloc(sizeof(sf::Texture));
	radius = 25;
	delay = 5;
}

PowerUp::~PowerUp() {
	free(this->texture);
}

sf::Vector2f PowerUp::getPosition() {
	return position;
}

float PowerUp::getDelay() {
	return delay;
}

float PowerUp::getRadius() {
	return radius;
}

PowerUpType PowerUp::getPowerUpType() {
	return type;
}

void PowerUp::startTimer() {
	timer.restart();
}

bool PowerUp::isTimeUp() {
	return timer.getElapsedTime().asSeconds() > delay;
}

void PowerUp::draw(sf::RenderWindow &window) {
	/* For some reason only works if i load the Textures here otherwise
	   some Textures get mixed up with anothers when creating new Textures (insert Confused Emoji)*/
	switch (type) {
	case PowerUpType::DECREASE_MY_SIZE:
		this->texture->loadFromFile("Images/img1.png");
		break;
	case PowerUpType::DECREASE_ENEMY_SIZE:
		this->texture->loadFromFile("Images/img2.png");
		break;
	case PowerUpType::INCREASE_MY_SIZE:
		this->texture->loadFromFile("Images/img3.png");
		break;
	case PowerUpType::INCREASE_ENEMY_SIZE:
		this->texture->loadFromFile("Images/img4.png");
		break;
	case PowerUpType::REVERSE_MY_KEYS:
		this->texture->loadFromFile("Images/img5.png");
		break;
	case PowerUpType::REVERSE_ENEMY_KEYS:
		this->texture->loadFromFile("Images/img6.png");
		break;
	case PowerUpType::DECREASE_MY_SPEED:
		this->texture->loadFromFile("Images/img7.png");
		break;
	case PowerUpType::DECREASE_ENEMY_SPEED:
		this->texture->loadFromFile("Images/img8.png");
		break;
	case PowerUpType::INCREASE_MY_SPEED:
		this->texture->loadFromFile("Images/img9.png");
		break;
	case PowerUpType::INCREASE_ENEMY_SPEED:
		this->texture->loadFromFile("Images/img10.png");
		break;
	case PowerUpType::MAKE_ME_POINTY:
		this->texture->loadFromFile("Images/img11.png");
		break;
	case PowerUpType::MAKE_ENEMY_POINTY:
		this->texture->loadFromFile("Images/img12.png");
		break;
	case PowerUpType::MAKE_ME_DOT:
		this->texture->loadFromFile("Images/img13.png");
		break;
	case PowerUpType::MAKE_WALL_OFF:
		this->texture->loadFromFile("Images/img14.png");
		break;
	case PowerUpType::GENERTE_THREE_POWERUPS:
		this->texture->loadFromFile("Images/img15.png");
		break;
	case PowerUpType::CLEAN_BOARD:
		this->texture->loadFromFile("Images/img16.png");
		break;
	case PowerUpType::CLEAN_MY_LINE:
		this->texture->loadFromFile("Images/img17.png");
		break;
	case PowerUpType::MAKE_WALL_OFF_FOR_ME:
		this->texture->loadFromFile("Images/img18.png");
		break;
	}
	sprite.setTexture(*this->texture);
	sprite.setOrigin(sf::Vector2f(2 * radius, 2 * radius));
	sprite.setPosition(position);
	sprite.setScale(0.5f, 0.5f);

	window.draw(sprite);
}


