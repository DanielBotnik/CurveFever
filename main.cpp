#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include "Utility.h"
#include "Line.h"
#include "Board.h"
#include "Snake.h"

using namespace std;

int main()
{
	srand(time(NULL));

	//int FPS = 0;
	const int height = 800;
	const int width = 800;
	const float speed = 75;
	const float angleRotation = 2.5;
	
	sf::ContextSettings windowSettings;
	windowSettings.antialiasingLevel = 16;

	sf::RenderWindow window(sf::VideoMode(height, width), "CurveFever",sf::Style::Default,windowSettings);
	sf::Vector2f pos(height / 2.0, width / 2.0);
	sf::Vector2f velocity(0, 1);

	Board myBoard = Board(width,height);
	myBoard.setColor(sf::Color::Green);

	Snake player(pos, velocity, sf::Color::Red, &myBoard, sf::Keyboard::Key::A, sf::Keyboard::Key::D);
	Snake player2(sf::Vector2f(200, 200), velocity, sf::Color::Blue, &myBoard, sf::Keyboard::Key::Left, sf::Keyboard::Key::Right);

	sf::Clock deltaTime;
	sf::Clock fpsTime;
	float dt = 0.001f;

	while (window.isOpen()) {
		player.update(dt);
		player2.update(dt);
		myBoard.updatePowerUp();
		window.clear();
		myBoard.draw(window);
		/*
		FPS++;
		if (fpsTime.getElapsedTime().asSeconds() > 1) {
			std::cout << FPS << std::endl;
			fpsTime.restart();
			FPS = 0;
		}
		*/
		player.draw(window); 
		player2.draw(window);
		window.display();
		sf::Event ev;
		while (window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed)
				window.close();
		}
		
		dt = deltaTime.restart().asSeconds();
	}

	return 0;
}