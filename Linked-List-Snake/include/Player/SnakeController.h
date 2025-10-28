#pragma once
#include <SFML/System/Vector2.hpp>
#include "Direction.h"
#include "LinkedList/SingleLinkedList.h"
#include "Food/FoodType.h"

using namespace LinkedList;
using namespace Food;

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

	enum class TimeComplexity
	{
		NONE,
		ONE,   // O(1)
		N,     // O(n)
	};

	enum class LinkedListOperations
	{
		NONE,
		INSERT_AT_HEAD,
		INSERT_AT_TAIL,
		INSERT_AT_MID,
		REMOVE_AT_HEAD,
		REMOVE_AT_TAIL,
		REMOVE_AT_MID,
		DELETE_HALF_LIST,
		REVERSE_LIST,
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

		int player_score;

		TimeComplexity time_complexity;
		LinkedListOperations last_linked_list_operation;

		SnakeState current_snake_state;
		InputState current_input_state;
		Direction current_snake_direction;
		SingleLinkedList* single_linked_list;

		void processBodyCollision();
		void processElementsCollision();
		void processFoodCollision();
		void OnFoodCollected(FoodType food_type);

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

		int getPlayerScore();

		TimeComplexity getTimeComplexity();
		LinkedListOperations getLastOperation();

		std::vector<sf::Vector2i> getCurrentSnakePositionList();

		void spawnSnake();
		void respawnSnake();
		void setSnakeState(SnakeState state);
		SnakeState getSnakeState();
	};
}
