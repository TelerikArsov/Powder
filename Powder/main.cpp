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
	window.setVerticalSyncEnabled(true);
	ImGui::SFML::Init(window);
	Simulation gol(92, 92, WINDOW_WIDTH, WINDOW_HEIGHT, 9.8f);
	gol.add_element(new GOL("WALL", "s1/b1"));
	gol.add_element(new Sand(gol));
	gol.add_element(new Water(gol));
	gol.add_brush(new CircleBrush());
	gol.add_brush(new SquareBrush());
	gol.selected_brush = 0;
	gol.selected_element = EL_SAND;

	sf::Clock clock;
	const unsigned int max_fps = 60;
	float elapsed = 0.0f;
	bool mouse_left_hold = false;

	ImGuiIO& io = ImGui::GetIO();

	//window.setFramerateLimit(max_fps);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
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
				if (io.WantCaptureMouse) break;

				if (event.mouseButton.button == sf::Mouse::Left)
				{
						mouse_left_hold = true;
				}
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (io.WantCaptureMouse) break;

				if (event.mouseButton.button == sf::Mouse::Left)
				{
						mouse_left_hold = false;
				}
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					gol.air->add_pressure(gol.mouse_cell_x, gol.mouse_cell_y, -25);
				}
				if (event.key.code == sf::Keyboard::Escape)
				{
					gol.pause();
				}
				if (event.key.code == sf::Keyboard::A)
				{
					gol.tick(true, 1 / 60.0f);
				}
			}
			if (mouse_left_hold)
			{
				gol.spawn_at_mouse();
			}
		}
		sf::Time time = clock.restart();
		elapsed = time.asSeconds();
		//if(gol.active_elements.size() > 0 && gol.active_elements.front())
			//std::cout << gol.active_elements.front()->velocity.y << std::endl;
		std::cout << 1 / elapsed << std::endl;
		ImGui::SFML::Update(window, time);
		//ImGui::ShowDemoWindow();
		gol.tick(false, elapsed);
		window.clear();
		gol.render(&window);
		ImGui::SFML::Render(window);
		window.display();
	}
	ImGui::SFML::Shutdown();
	return 0;
}