#include "Player/PlayerService.h"
#include "Player/SnakeController.h"

namespace Player
{
	PlayerService::PlayerService()
	{
		snake_controller = nullptr;
		createController();
	}

	PlayerService::~PlayerService()
	{
		destroy();
	}

	void PlayerService::createController()
	{
		snake_controller = new SnakeController();
	}

	void PlayerService::initialize()
	{
		if (snake_controller != nullptr)
			snake_controller->initialize();
	}

	void PlayerService::update()
	{
		if (snake_controller != nullptr)
			snake_controller->update();
	}

	void PlayerService::render()
	{
		if (snake_controller != nullptr)
			snake_controller->render();
	}

	void PlayerService::spawnPlayer(LinkedListType level_type)
	{
		if (snake_controller != nullptr)
		{
			snake_controller->createLinkedList(level_type);
			snake_controller->spawnSnake();
		}
	}

	int PlayerService::getPlayerScore()
	{
		if (snake_controller != nullptr)
			return snake_controller->getPlayerScore();
		return 0;
	}

	TimeComplexity PlayerService::getTimeComplexity()
	{
		if (snake_controller != nullptr)
			return snake_controller->getTimeComplexity();
		return TimeComplexity::NONE;
	}

	LinkedListOperations PlayerService::getLastOperation()
	{
		if (snake_controller != nullptr)
			return snake_controller->getLastOperation();
		return LinkedListOperations::NONE;
	}

	std::vector<sf::Vector2i> PlayerService::getCurrentSnakePositionList()
	{
		if (snake_controller != nullptr)
			return snake_controller->getCurrentSnakePositionList();
		return std::vector<sf::Vector2i>();
	}

	void PlayerService::destroy()
	{
		if (snake_controller != nullptr)
		{
			delete snake_controller;
			snake_controller = nullptr;
		}
	}

	bool PlayerService::isPlayerDead()
}
