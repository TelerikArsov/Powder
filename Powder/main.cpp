#include <SFML/Graphics.hpp>
#include <iostream>
#include "Simulation.h"
#include "Element/Elements.h"
#include "Brushes/CircleBrush.h"
#include "Brushes/SquareBrush.h"
#include "Utils/Vector.h"
#include "SimTool/Tools/SpawnTool.h"
#include "SimTool/Tools/HeatTool.h"
#include "SimTool/Tools/CoolTool.h"

int main()
{
	int WINDOW_HEIGHT = 1000, WINDOW_WIDTH = 1000;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
	window.setVerticalSyncEnabled(true);
	ImGui::SFML::Init(window);
	Simulation sim(92, 92, WINDOW_WIDTH, WINDOW_HEIGHT, 9.8f);
	sim.add_element(new GOL("WALL", "Wall rule" ,"s1/b1"));
	sim.add_element(new Sand(sim));
	sim.add_element(new Water(sim));
	sim.add_element(new Ice(sim));
	sim.add_brush(new CircleBrush());
	sim.add_brush(new SquareBrush());
	sim.add_tool(new SpawnTool());
	sim.add_tool(new HeatTool());
	sim.add_tool(new CoolTool());
	sim.select_brush(0);
	sim.select_element(EL_SAND);

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
				sim.set_mouse_coordinates(event.mouseMove.x, event.mouseMove.y);
			}
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				sim.resize_brush(event.mouseWheelScroll.delta);
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
					sim.air->add_pressure(sim.mouse_cell_x, sim.mouse_cell_y, -25);
				}
				if (event.key.code == sf::Keyboard::Escape)
				{
					sim.toggle_pause();
				}
				if (event.key.code == sf::Keyboard::A)
				{
					sim.tick(true, 1 / 60.0f);
				}
			}
			if (mouse_left_hold)
			{
				sim.mouse_left_click();
			}
		}
		sf::Time time = clock.restart();
		elapsed = time.asSeconds();
		//if(sim.active_elements.size() > 0 && sim.active_elements.front())
			//std::cout << sim.active_elements.front()->velocity.y << std::endl;
		std::cout << 1 / elapsed << std::endl;
		ImGui::SFML::Update(window, time);
		//ImGui::ShowDemoWindow();
		sim.tick(false, elapsed);
		window.clear();
		sim.render(&window);
		ImGui::SFML::Render(window);
		window.display();
	}
	ImGui::SFML::Shutdown();
	return 0;
}