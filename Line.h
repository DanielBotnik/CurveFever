#pragma once

#include <SFML/Graphics.hpp>
#include "Utility.h"

class Line
{
public:
	Line();
	Line(float thicc, sf::Color color);
	void addPoint(sf::Vector2f point);
	void setThicc(float thicc);
	void clear();
	std::vector<sf::Vector2f> getLine();
	int getSize();
	float getThicc();
	void draw(sf::RenderWindow& window);
	void drawLine(sf::RenderWindow& window);

private:
	float thicc;
	std::vector<sf::Vector2f> line;
	sf::VertexArray vertexArray;
	sf::VertexArray lineVertexArray;
	sf::Color color;

};