#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp> 
#include "Level/LevelConfig.h"

namespace Player
{
	using namespace Level; 

	class SnakeController;

	enum class TimeComplexity;
	enum class LinkedListOperations;

	class PlayerService
	{
	private:
		SnakeController* snake_controller;

		void createController();
		void destroy();

	public:
		PlayerService();
		~PlayerService();

		void initialize();
		void update();
		void render();

		void spawnPlayer(LinkedListType level_type);

		std::vector<sf::Vector2i> getCurrentSnakePositionList();

		bool isPlayerDead();

		int getPlayerScore();
		TimeComplexity getTimeComplexity();
		LinkedListOperations getLastOperation();

		SnakeController* getSnakeController();
	};
}
