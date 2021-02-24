#pragma once

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <random>

sf::Vector2f rotateVector(sf::Vector2f vec, float angle);
float Norm(sf::Vector2f);
float randFloat(float times);
float dist(sf::Vector2f, sf::Vector2f);