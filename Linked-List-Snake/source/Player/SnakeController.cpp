#include "Player/SnakeController.h"
#include "Global/ServiceLocator.h"
#include "Level/LevelService.h"
#include "Event/EventService.h"
#include "Sound/SoundService.h"
#include "Element/ElementService.h"
#include "Food/FoodService.h"  

namespace Player
{
	using namespace Global;
	using namespace Level;
	using namespace EventSpace;
	using namespace SoundSpace;
	using namespace Element;

	SnakeController::SnakeController()
	{
		linked_list = nullptr;
		current_snake_direction = default_direction;
		current_input_state = InputState::WAITING;
		player_score = 0;

		time_complexity = TimeComplexity::NONE;
		last_linked_list_operation = LinkedListOperations::NONE;
	}

	SnakeController::~SnakeController()
	{
		destroy();
	}

	void SnakeController::createLinkedList(LinkedListType level_type)
	{
		if (linked_list != nullptr)
		{
			delete linked_list;
			linked_list = nullptr;
		}

		switch (level_type)
		{
		case LinkedListType::SINGLE_LINKED_LIST:
			linked_list = new LinkedListLib::SingleLinked::SingleLinkedList(); //error
			break;
		case LinkedListType::DOUBLE_LINKED_LIST:
			linked_list = new LinkedListLib::DoubleLinked::DoubleLinkedList();
			break;
		}

		initializeLinkedList();
	}

	// ... rest of the methods remain exactly the same ...
	void SnakeController::initializeLinkedList()
	{
		if (linked_list == nullptr) return;

		float width = ServiceLocator::getInstance()->getLevelService()->getCellWidth();
		float height = ServiceLocator::getInstance()->getLevelService()->getCellHeight();

		reset();
		linked_list->initialize(width, height, default_position, default_direction);
	}

	void SnakeController::initialize()
	{

	}

	void SnakeController::processFoodCollision()
	{
		if (linked_list == nullptr) return;

		FoodService* food_service = ServiceLocator::getInstance()->getFoodService();
		FoodType food_type;

		if (food_service->processFoodCollision(linked_list->getHeadNode(), food_type))
		{
			ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::PICKUP);

			player_score++;

			food_service->destroyFood();
			OnFoodCollected(food_type);
		}
	}

	void SnakeController::OnFoodCollected(Food::FoodType food_type)
	{
		if (linked_list == nullptr) return;

		switch (food_type)
		{
		case FoodType::PIZZA:
			linked_list->insertNodeAtTail();
			last_linked_list_operation = LinkedListOperations::INSERT_AT_TAIL;
			time_complexity = TimeComplexity::N;
			break;

		case FoodType::BURGER:
			linked_list->insertNodeAtHead();
			last_linked_list_operation = LinkedListOperations::INSERT_AT_HEAD;
			time_complexity = TimeComplexity::ONE;
			break;

		case FoodType::CHEESE:
			linked_list->insertNodeAtMiddle();
			last_linked_list_operation = LinkedListOperations::INSERT_AT_MID;
			time_complexity = TimeComplexity::N;
			break;

		case FoodType::APPLE:
			linked_list->removeNodeAtHead();
			last_linked_list_operation = LinkedListOperations::REMOVE_AT_HEAD;
			time_complexity = TimeComplexity::ONE;
			break;

		case FoodType::MANGO:
			linked_list->removeNodeAtMiddle();
			last_linked_list_operation = LinkedListOperations::REMOVE_AT_MID;
			time_complexity = TimeComplexity::N;
			break;

		case FoodType::ORANGE:
			linked_list->removeNodeAtTail();
			last_linked_list_operation = LinkedListOperations::REMOVE_AT_TAIL;
			time_complexity = TimeComplexity::N;
			break;

		case FoodType::POISION:
			linked_list->removeHalfNodes();
			last_linked_list_operation = LinkedListOperations::DELETE_HALF_LIST;
			time_complexity = TimeComplexity::N;
			break;

		case FoodType::ALCOHOL:
			current_snake_direction = linked_list->reverse();
			last_linked_list_operation = LinkedListOperations::REVERSE_LIST;
			time_complexity = TimeComplexity::N;
			break;
		}
	}

	int SnakeController::getPlayerScore()
	{
		return player_score;
	}

	TimeComplexity SnakeController::getTimeComplexity()
	{
		return time_complexity;
	}

	LinkedListOperations SnakeController::getLastOperation()
	{
		return last_linked_list_operation;
	}

	std::vector<sf::Vector2i> SnakeController::getCurrentSnakePositionList()
	{
		if (linked_list == nullptr)
			return std::vector<sf::Vector2i>();
		return linked_list->getNodesPositionList();
	}

	void SnakeController::update()
	{
		switch (current_snake_state)
		{
		case SnakeState::ALIVE:
			processPlayerInput();
			delayedUpdate();
			break;

		case SnakeState::DEAD:
			handleRestart();
			break;
		}
	}

	void SnakeController::processSnakeCollision()
	{
		processBodyCollision();
		processElementsCollision();
		processFoodCollision();
	}

	void SnakeController::processBodyCollision()
	{
		if (linked_list->processNodeCollision())
		{
			current_snake_state = SnakeState::DEAD;
			ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::DEATH);
		}
	}

	void SnakeController::processElementsCollision()
	{
		if (linked_list == nullptr) return;

		ElementService* element_service = ServiceLocator::getInstance()->getElementService();
		if (element_service->processElementsCollision(linked_list->getHeadNode()))
		{
			current_snake_state = SnakeState::DEAD;
			ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::DEATH);
		}
	}

	void SnakeController::render()
	{
		if (linked_list != nullptr)
		{
			linked_list->render();
		}
	}

	void SnakeController::processPlayerInput()
	{
		if (current_input_state != InputState::WAITING) return;

		EventService* event_service = ServiceLocator::getInstance()->getEventService();

		if (event_service->pressedUpArrowKey() && current_snake_direction != Direction::DOWN)
		{
			current_snake_direction = Direction::UP;
			current_input_state = InputState::PROCESSING;
		}
		else if (event_service->pressedDownArrowKey() && current_snake_direction != Direction::UP)
		{
			current_snake_direction = Direction::DOWN;
			current_input_state = InputState::PROCESSING;
		}
		else if (event_service->pressedLeftArrowKey() && current_snake_direction != Direction::RIGHT)
		{
			current_snake_direction = Direction::LEFT;
			current_input_state = InputState::PROCESSING;
		}
		else if (event_service->pressedRightArrowKey() && current_snake_direction != Direction::LEFT)
		{
			current_snake_direction = Direction::RIGHT;
			current_input_state = InputState::PROCESSING;
		}
	}

	void SnakeController::updateSnakeDirection()
	{
		if (linked_list != nullptr)
		{
			linked_list->updateNodeDirection(current_snake_direction);
		}
	}

	void SnakeController::moveSnake()
	{
		if (linked_list != nullptr)
		{
			linked_list->updateNodePosition();
		}
	}

	void SnakeController::handleRestart()
	{
		restart_counter += ServiceLocator::getInstance()->getTimeService()->getDeltaTime();

		if (restart_counter >= restart_duration)
		{
			respawnSnake();
		}
	}

	void SnakeController::spawnSnake()
	{
		if (linked_list == nullptr) return;

		for (int i = 0; i < initial_snake_length; i++)
		{
			linked_list->insertNodeAtTail();
		}
		setSnakeState(SnakeState::ALIVE);
	}

	void SnakeController::reset()
	{
		current_snake_state = SnakeState::ALIVE;
		current_snake_direction = default_direction;
		current_input_state = InputState::WAITING;
		elapsed_duration = 0.f;
		restart_counter = 0.f;
		player_score = 0;

		time_complexity = TimeComplexity::NONE;
		last_linked_list_operation = LinkedListOperations::NONE;
	}

	void SnakeController::delayedUpdate()
	{
		elapsed_duration += ServiceLocator::getInstance()->getTimeService()->getDeltaTime();

		if (elapsed_duration >= movement_frame_duration)
		{
			elapsed_duration = 0.f;
			updateSnakeDirection();
			processSnakeCollision();

			if (current_snake_state == SnakeState::ALIVE)
			{
				moveSnake();
				current_input_state = InputState::WAITING;
			}
		}
	}

	void SnakeController::respawnSnake()
	{
		if (linked_list != nullptr)
		{
			linked_list->removeAllNodes();
		}
		reset();
		spawnSnake();
	}

	void SnakeController::setSnakeState(SnakeState state)
	{
		current_snake_state = state;
	}

	SnakeState SnakeController::getSnakeState()
	{
		return current_snake_state;
	}

	void SnakeController::destroy()
	{
		if (linked_list != nullptr)
		{
			delete linked_list;
			linked_list = nullptr;
		}
	}
}
