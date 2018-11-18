#include <SFML/Graphics.hpp>
#include <iostream>
#include "Simulation.h"
#include "GOL.h"

int main()
{
	int WINDOW_HEIGHT = 1000, WINDOW_WIDTH = 1000;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
	Simulation gol(300, 300, WINDOW_WIDTH, WINDOW_HEIGHT);
	gol.available_elements.push_back(new GOL(0, 1, "WALL", "s12345/b3"));
	gol.selected_element = gol.available_elements[0]->identifier;
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseMoved)
			{
				gol.set_mouse_cor(event.mouseMove.x, event.mouseMove.y);
			}
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				gol.resize_spawn(event.mouseWheelScroll.delta);
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					gol.spawn_mouse();
				}
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					gol.pause();
				}
				if (event.key.code == sf::Keyboard::A)
				{
					gol.tick(true);
				}
			}
		}
		sf::Time elapsed = clock.restart();
		std::cout << 1.f / elapsed.asSeconds() << std::endl;
		window.clear();
		gol.render(&window);
		gol.tick();
		window.display();
	}

	return 0;
}