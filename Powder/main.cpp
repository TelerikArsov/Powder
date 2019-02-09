#include <SFML/Graphics.hpp>
#include <iostream>
#include "Simulation.h"
#include "Elements.h"
#include "CircleBrush.h"
#include "SquareBrush.h"
#include "Vector.h"

int main()
{
	int WINDOW_HEIGHT = 1000, WINDOW_WIDTH = 1000;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
	Simulation gol(368, 368, WINDOW_WIDTH, WINDOW_HEIGHT, 9.8);
	gol.add_element(new GOL(1, "WALL", "s012345678"));
	gol.add_element(new Sand(gol));
	gol.add_brush(new CircleBrush());
	gol.add_brush(new SquareBrush());
	gol.selected_brush = 0;
	gol.selected_element = EL_SAND;
	sf::Clock clock;
	const unsigned int max_fps = 60;
	double elapsed = 0.0f;
	bool mouse_left_hold = false;
	window.setFramerateLimit(max_fps);
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
					gol.selected_element = EL_SAND;
				}
				if (event.key.code == sf::Keyboard::E)
				{
					gol.selected_element = EL_GOL;
				}
				if (event.key.code == sf::Keyboard::Escape)
				{
					gol.pause();
				}
				if (event.key.code == sf::Keyboard::A)
				{
					gol.tick(true, 1 / 60.0);
				}
				/*
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
				*/
			}
			if (mouse_left_hold)
			{
				gol.spawn_at_mouse();
			}
		}
		elapsed = clock.restart().asSeconds();
		//if(gol.active_elements.size() > 0 && gol.active_elements.front())
			//std::cout << gol.active_elements.front()->velocity.y << std::endl;
		std::cout << 1 / elapsed << std::endl;
		gol.tick(false, 1 / 60.0);
		window.clear();
		gol.render(&window);
		window.display();
	}

	return 0;
}