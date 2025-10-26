#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp> 

namespace Player
{
	class SnakeController;

	class PlayerService
	{
	private:
		SnakeController* snake_controller;

		void createController();
		void destroy();

	public:
		PlayerService();
		~PlayerService();

		std::vector<sf::Vector2i> getCurrentSnakePositionList();

		void initialize();
		void update();
		void render();

		void spawnPlayer();
	};
}
