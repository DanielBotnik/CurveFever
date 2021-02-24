#include "Utility.h"
#include <time.h>


sf::Vector2f rotateVector(sf::Vector2f vec, float angle) {
	float x = vec.x * cosf(angle) - vec.y * sinf(angle);
	float y = vec.x * sinf(angle) + vec.y * cosf(angle);
	return sf::Vector2f(x, y);
}

float Norm(sf::Vector2f vec) {
	return sqrtf(powf(vec.x, 2) + powf(vec.y, 2));
}

float randFloat(float times) {
	return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * times;
}

float dist(sf::Vector2f v1, sf::Vector2f v2) {
	return sqrtf(powf(v1.x - v2.x, 2) + powf(v1.y - v2.y, 2));
}