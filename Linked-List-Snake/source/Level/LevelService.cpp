#include "Level/LevelService.h"
#include "Level/LevelController.h"
#include "Global/ServiceLocator.h"
#include "Food/FoodService.h"

namespace Level
{
	using namespace Global;

	LevelService::LevelService()
	{
		level_controller = nullptr;
		current_linked_list_type = LinkedListType::SINGLE_LINKED_LIST;

		createLevelController();
	}

	LevelService::~LevelService()
	{
		destroy();
	}

	void LevelService::createLevelController()
	{
		level_controller = new LevelController();
	}

	void LevelService::initialize()
	{
		level_controller->initialize();
	}

	void LevelService::update()
	{
		level_controller->update();
	}

	void LevelService::render()
	{
		level_controller->render();
	}

	void LevelService::setCurrentLevelNumber(LevelNumber level_to_load)
	{
		current_level = level_to_load;
	}

	void LevelService::createLevel(LinkedListType linked_list_type)
	{
		current_linked_list_type = linked_list_type; 

		spawnLevelElements(current_level);
		spawnFood();
		spawnPlayer(linked_list_type);
	}

	void LevelService::spawnFood()
	{
		ServiceLocator::getInstance()->getFoodService()->startFoodSpawning();
	}

	void LevelService::spawnLevelElements(LevelNumber level_to_load)
	{
		float cell_width = level_controller->getCellWidth();
		float cell_height = level_controller->getCellHeight();

		std::vector<Element::ElementData> element_data_list = level_controller->getElementDataList((int)level_to_load);
		ServiceLocator::getInstance()->getElementService()->spawnElements(element_data_list, cell_width, cell_height);
	}

	LevelNumber LevelService::getCurrentLevel()
	{
		return current_level;
	}

	LinkedListType LevelService::getCurrentLinkedListType()
	{
		return current_linked_list_type;
	}

	float LevelService::getCellWidth()
	{
		return level_controller->getCellWidth();
	}

	float LevelService::getCellHeight()
	{
		return level_controller->getCellHeight();
	}

	void LevelService::destroy()
	{
		delete level_controller;
	}

	void LevelService::spawnPlayer(LinkedListType linked_list_type)
	{
		ServiceLocator::getInstance()->getPlayerService()->spawnPlayer(current_linked_list_type);
	}
}
