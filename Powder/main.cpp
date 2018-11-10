#include <SFML/Graphics.hpp>
#include "Simulation.h"
#include "BRAN.h"

int main()
{
	int WINDOW_HEIGHT = 200, WINDOW_WIDTH = 200;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
	Simulation gol(WINDOW_HEIGHT / CELLS_Y_COUNT, WINDOW_WIDTH / CELLS_X_COUNT);
	gol.selected_element = new BRAN();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					gol.spawn_mouse(event.mouseButton.x, event.mouseButton.y);
				}
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					gol.pause = !gol.pause;
				}
				if (event.key.code == sf::Keyboard::A)
				{
					gol.tick();
				}
			}
		}

		window.clear();
		gol.render(&window);
		window.display();
	}

	return 0;
}