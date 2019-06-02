#include <SFML/Graphics.hpp>
#include <iostream>
#include "Simulation.h"
#include "Element/ElementIncludes.h"
#include "Brushes/CircleBrush.h"
#include "Brushes/SquareBrush.h"
#include "Utils/Vector.h"
#include "SimTool/ToolIncludes.h"

int main()
{
	int WINDOW_HEIGHT = 720, WINDOW_WIDTH = 1280;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
	window.setVerticalSyncEnabled(true);
	ImGui::SFML::Init(window);
	Simulation sim(160, 90, WINDOW_WIDTH, WINDOW_HEIGHT, 9.8f);
	// TODO make the generate script do this
	sim.add_element(std::make_shared<WALL>(sim));
	sim.add_element(std::make_shared<Acid>(sim));
	sim.add_element(std::make_shared<BHOL>(sim));
	sim.add_element(std::make_shared<Brick>(sim));
	sim.add_element(std::make_shared<Caus>(sim));
	sim.add_element(std::make_shared<Coal>(sim));
	sim.add_element(std::make_shared<Dust>(sim));
	sim.add_element(std::make_shared<EXC4>(sim));
	sim.add_element(std::make_shared<Fire>(sim));
	sim.add_element(std::make_shared<Gas>(sim));
	sim.add_element(std::make_shared<Gold>(sim));
	sim.add_element(std::make_shared<Gun>(sim));
	sim.add_element(std::make_shared<Ice>(sim));
	sim.add_element(std::make_shared<Lava>(sim));
	sim.add_element(std::make_shared<Metl>(sim));
	sim.add_element(std::make_shared<Nitr>(sim));
	sim.add_element(std::make_shared<Oil>(sim));
	sim.add_element(std::make_shared<Sand>(sim));
	sim.add_element(std::make_shared<Stone>(sim));
	sim.add_element(std::make_shared<Water>(sim));
	sim.add_element(std::make_shared<WHOL>(sim));
	sim.add_element(std::make_shared<Wood>(sim));
	sim.add_element(std::make_shared<Wtrv>(sim));
	sim.add_brush(std::make_shared<CircleBrush>());
	sim.add_brush(std::make_shared<SquareBrush>());
	sim.add_tool(std::make_shared<SpawnTool>());
	sim.add_tool(std::make_shared<ClearTool>());
	sim.add_tool(std::make_shared<HeatTool>());
	sim.add_tool(std::make_shared<CoolTool>());
	sim.add_tool(std::make_shared<NegPTool>());
	sim.add_tool(std::make_shared<PosPTool>());
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
				if (event.key.code == sf::Keyboard::Escape)
				{
					sim.toggle_pause();
				}
				if (event.key.code == sf::Keyboard::A)
				{
					sim.tick(true, 1 / 60.0f);
				}
			}
			if (event.type == sf::Event::Resized)
			{
				sim.set_window_size(event.size.width, event.size.height);
			}
		}
		if (mouse_left_hold)
		{
			sim.mouse_left_click();
			//std::cout << sim.mouse_cell_x << " " << sim.mouse_cell_y << std::endl;
		}
		sf::Time time = clock.restart();
		elapsed = time.asSeconds();
		//if(sim.active_elements.size() > 0 && sim.active_elements.front())
			//std::cout << sim.active_elements.front()->velocity.y << std::endl;
		//std::cout << 1 / elapsed << std::endl;
		//std::cout << (mouse_left_hold ? "hold" : "nohole") << std::endl;
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