#include "Snake.h"

Snake::Snake(sf::Vector2f position, sf::Vector2f velocity, sf::Color color, 
	Board* board, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey) {
	this->position = position;
	this->velocity = velocity;
	this->color = color;
	this->board = board;
	this->leftKey = leftKey;
	this->rightKey = rightKey;

	size = 3;
	speed = 75;
	rotateAngle = 3;
	delay = 5;
	nextGap = randFloat(delay);
	gapLength = size / speed * 10;
	

	lineTimerEnd = false;
	startTimerEnd = false;
	noLine = true;
	alive = true;

	//lines.push_back(Line(size, color));
	//lines[lines.size() - 1].addPoint(position);

	startCircle.setFillColor(color);
	startCircle.setOrigin(size, size);
	startCircle.setRadius(size);
	startCircle.setPosition(position);
	endCircle.setFillColor(color);
	endCircle.setOrigin(size, size);
	endCircle.setRadius(size);
	endCircle.setPosition(position);

	board->addSnake(this);
}

void Snake::control(float dt) {
	if (sf::Keyboard::isKeyPressed(rightKey)) {
		velocity = rotateVector(velocity, rotateAngle*dt);
	}

	if (sf::Keyboard::isKeyPressed(leftKey)) {
		velocity = rotateVector(velocity, -rotateAngle*dt);
	}
	if (!checkSelfCollision()) {
		position += velocity * speed * dt;
	}
	endCircle.setPosition(position);
}

void Snake::draw(sf::RenderWindow &window) {
	window.draw(startCircle);
	window.draw(endCircle);
	for (Line *line : lines) {
		line->draw(window);
	}
}

sf::Vector2f Snake::getLastPoint() {
	return lines[lines.size() - 1]->getLine()[lines[lines.size() - 1]->getLine().size() - 1];
}

void Snake::update(float dt) {
	
	if (!alive) {
		return;
	}

	startCollision();
	control(dt);

	if (checkSelfCollision() || checkWallCollision() || (!noLine && board->checkEnemyCollision(this))) {
		alive = false;
	}
	
	board->checkPowerUpCollision(this);
	
	if (lineTimer.getElapsedTime().asSeconds() < nextGap && !noLine && dist(getLastPoint(),position) > 3 && alive) {
		lines[lines.size() - 1]->addPoint(position);
	}
	else if (lineTimer.getElapsedTime().asSeconds() >= nextGap && !lineTimerEnd && !noLine && alive) {
		lineTimerEnd = true;
		lines[lines.size() - 1]->addPoint(position + velocity * size);
	}
	else if (lineTimer.getElapsedTime().asSeconds() > nextGap + gapLength && !noLine && alive) {
		lines.push_back(new Line(size, color));
		lines[lines.size() - 1]->addPoint(position - velocity * size);
		lines[lines.size() - 1]->addPoint(position);
		lineTimer.restart();
		nextGap = randFloat(delay);
		lineTimerEnd = false;
	}

	for (int i = 0; i < effects.size(); i++) {
		if (effects[i]->isTimeUp()) {
			PowerUp* eff = effects[i];
			switch (eff->getPowerUpType()) {
			case PowerUpType::DECREASE_MY_SIZE:
				setSize(size * 2);
				break;
			case PowerUpType::INCREASE_MY_SIZE:
				setSize(size / 2);
				break;
			case PowerUpType::REVERSE_MY_KEYS:
				reverseKeys();
				break;
			case PowerUpType::DECREASE_MY_SPEED:
				setSpeed(speed * 2);
				break;
			case PowerUpType::INCREASE_MY_SPEED:
				setSpeed(speed / 2);
				break;
			case PowerUpType::MAKE_ME_POINTY:
				break;
			case PowerUpType::MAKE_ME_DOT:
				lineOn();
				break;
			case PowerUpType::MAKE_WALL_OFF_FOR_ME:
				break;
			}
			effects.erase(effects.begin() + i);
			delete eff;
		}
	}

}

void Snake::startCollision() {
	if (startTimer.getElapsedTime().asSeconds() < 2) {
		lineOff();
		startCircle.setPosition(position);
	}
	else if (!startTimerEnd && startTimer.getElapsedTime().asSeconds() > 2) {
		lineOn();
		startTimerEnd = true;
	}
}

void Snake::lineOn() {
	noLine = false;
	lines.push_back(new Line(size, color));
	lines[lines.size() - 1]->addPoint(position);
}

void Snake::lineOff() {
	noLine = true;
}

bool Snake::checkSelfCollision() {
	if (noLine || lineTimerEnd) {
		return false;
	}
	for (int i = 0; i < lines.size(); i++) {
		for (int j = 1; j < lines[i]->getLine().size() - 1; j++) {
			if (dist(position, lines[i]->getLine()[j]) < size + lines[i]->getThicc() && !(i == lines.size() - 1 && lines[i]->getSize() - j < 10*size)) {
				return true;
			}
		}
	}
	return false;
}

bool Snake::checkWallCollision() {
	if (position.x - size < board->getOffset().x || position.y - size < board->getOffset().y || position.x + size > board->getSize().x || position.y + size > board->getSize().y) {
		return true;
	}
	return false;
}

sf::Vector2f Snake::getPosition() {
	return position;
}

float Snake::getSize() {
	return size;
}

std::vector<Line*>* Snake::getLines() {
	return &lines;
}

void Snake::setSize(float size) {
	float diff = size / this->size;
	this->size = size;
	endCircle.setRadius(size);
	endCircle.setOrigin(size, size);
	gapLength *= diff;
	lines[lines.size() - 1]->setThicc(size);
}

void Snake::addEffect(PowerUp* effect) {
	this->effects.push_back(effect);
	effect->startTimer();
}

void Snake::reverseKeys() {
	sf::Keyboard::Key temp = rightKey;
	rightKey = leftKey;
	leftKey = temp;
}

void Snake::setSpeed(float speed) {
	float diff = speed / this->speed;
	this->speed = speed;
	rotateAngle *= diff;
	gapLength /= diff;
}

float Snake::getSpeed() {
	return speed;
}

void Snake::earseSnake() {
	for (int i = 0; i < lines.size(); i++)
	{
		lines[i]->clear();
		delete lines[i];
	}
	lines.resize(0);
	lines.push_back(new Line(size, color));
	lines[lines.size() - 1]->addPoint(position);
	startCircle.setPosition(position);
}