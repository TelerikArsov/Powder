#include <SFML/Graphics.hpp>
#include <iostream>
#include "Simulation.h"
#include "Elements.h"
#include "CircleBrush.h"
#include "SquareBrush.h"

int main()
{
	int WINDOW_HEIGHT = 1000, WINDOW_WIDTH = 1000;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
	Simulation gol(20, 20, WINDOW_WIDTH, WINDOW_HEIGHT);
	gol.available_add(new GOL(1, "WALL", "s12345/b3"));
	gol.available_add(new Sand());
	gol.brushes.push_back(new CircleBrush());
	gol.brushes.push_back(new SquareBrush());
	gol.selected_brush = 1;
	gol.selected_element = 1;
	sf::Clock clock;
	bool mouse_left_hold = false;
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
				gol.resize_brush(event.mouseWheelScroll.delta);
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					mouse_left_hold = true;
				}
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					mouse_left_hold = false;
				}
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Q) 
				{
					gol.selected_element = 0;
				}
				if (event.key.code == sf::Keyboard::E)
				{
					gol.selected_element = 1;
				}
				if (event.key.code == sf::Keyboard::Escape)
				{
					gol.pause();
				}
				if (event.key.code == sf::Keyboard::A)
				{
					gol.tick(true);
				}
				if (event.key.code == sf::Keyboard::S) 
				{
					int x = static_cast<float>(gol.mouse_x) / gol.cell_width;
					int y = static_cast<float>(gol.mouse_y) / gol.cell_height;
					for (auto el : gol.active_elements)
					{
						if (el->identifier == 2) 
						{
							el->move(x, y);
						}
					}
				}
			}
			if (mouse_left_hold)
			{
				gol.spawn_mouse();
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