#pragma once
#include <SFML/System/Vector2.hpp>
#include "Direction.h"
#include "LinkedList/SingleLinkedList.h"

using namespace LinkedList;

namespace Player
{
	enum class SnakeState
	{
		ALIVE,
		DEAD,
	};

	enum class InputState
	{
		WAITING,
		PROCESSING
	};


	class SnakeController
	{
	private:
		const int initial_snake_length = 10;

		const sf::Vector2i default_position = sf::Vector2i(25, 13);
		const Direction default_direction = Direction::RIGHT;

		const float movement_frame_duration = 0.1f;
		float elapsed_duration = 0.f;

		const float restart_duration = 2.f;
		float restart_counter = 0.f;

		SnakeState current_snake_state;
		InputState current_input_state;
		Direction current_snake_direction;
		SingleLinkedList* single_linked_list;

		void processBodyCollision();
		void processElementsCollision();
		void processFoodCollision();

		void createLinkedList();
		void processPlayerInput();
		void updateSnakeDirection();
		void moveSnake();
		void processSnakeCollision();
		void delayedUpdate();
		void handleRestart();
		void reset();
		void destroy();

	public:
		SnakeController();
		~SnakeController();

		void initialize();
		void update();
		void render();

		std::vector<sf::Vector2i> getCurrentSnakePositionList();

		void spawnSnake();
		void respawnSnake();
		void setSnakeState(SnakeState state);
		SnakeState getSnakeState();
	};
}
