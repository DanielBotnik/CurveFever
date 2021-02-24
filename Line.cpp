#include "Line.h"

Line::Line() {
	vertexArray.setPrimitiveType(sf::TrianglesStrip);
	lineVertexArray.setPrimitiveType(sf::LinesStrip);
	thicc = 3;
	color = sf::Color::Red;
}

Line::Line(float thicc, sf::Color color) {
	vertexArray.setPrimitiveType(sf::TrianglesStrip);
	lineVertexArray.setPrimitiveType(sf::LinesStrip);
	this->thicc = thicc;
	this->color = color;
}

void Line::addPoint(sf::Vector2f point) {
	line.push_back(point);
	lineVertexArray.append(sf::Vertex(point,color));
	int size = line.size();
	if (size > 1) {
		sf::Vector2f n = line[size - 1] - line[size - 2];
		n /= Norm(n);
		sf::Vector2f u = sf::Vector2f(n.y, -n.x);
		vertexArray.append(sf::Vertex(u * thicc + line[size - 1], color));
		vertexArray.append(sf::Vertex(-u * thicc + line[size - 1], color));
		vertexArray.append(sf::Vertex(u * thicc + line[size - 2], color));
		vertexArray.append(sf::Vertex(-u * thicc + line[size - 2], color));
	}
	
}

void Line::setThicc(float thicc) {
	this->thicc = thicc;
}

void Line::clear() {
	line.clear();
	vertexArray.clear();
	lineVertexArray.clear();
}

std::vector<sf::Vector2f> Line::getLine() {
	return line;
}

int Line::getSize() {
	return line.size();
}

void Line::draw(sf::RenderWindow &window) {
	window.draw(vertexArray);
}

void Line::drawLine(sf::RenderWindow &window) {
	window.draw(vertexArray);
}

float Line::getThicc() {
	return thicc;
}