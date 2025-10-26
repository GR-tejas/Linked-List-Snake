#include "Global/ServiceLocator.h"
#include "Main/GameService.h"

namespace Global
{
	using namespace Graphics;
	using namespace EventSpace;
	using namespace SoundSpace;
	using namespace UI;
	using namespace TimeSpace;
	using namespace Player;
	using namespace Level;
	using namespace Element;
	using namespace Main;
	using namespace Food;

	ServiceLocator::ServiceLocator()
	{
		graphic_service = nullptr;
		event_service = nullptr;
		sound_service = nullptr;
		ui_service = nullptr;
		time_service = nullptr;
		player_service = nullptr;
		level_service = nullptr;
		element_service = nullptr;
		food_service = nullptr;

		createServices();
	}

	ServiceLocator::~ServiceLocator() { clearAllServices(); }

	void ServiceLocator::createServices()
	{
		event_service = new EventService();
		graphic_service = new GraphicService();
		sound_service = new SoundService();
		ui_service = new UIService();
		time_service = new TimeService();
		level_service = new LevelService();
		player_service = new PlayerService();
		element_service = new ElementService();
		food_service = new Food::FoodService();

	}

	void ServiceLocator::initialize()
	{
		graphic_service->initialize();
		sound_service->initialize();
		event_service->initialize();
		ui_service->initialize();
		time_service->initialize();
		level_service->initialize();
		player_service->initialize();
		element_service->initialize();
		food_service->initialize();

	}

	void ServiceLocator::update()
	{
		graphic_service->update();
		event_service->update();
		time_service->update();
		level_service->update();
		player_service->update();
		if (GameService::getGameState() == GameState::GAMEPLAY)
		{
			element_service->update();
			food_service->update();
		}

		ui_service->update();
	}

	void ServiceLocator::render()
	{
		graphic_service->render();
		level_service->render();
		player_service->render();
		if (GameService::getGameState() == GameState::GAMEPLAY)
		{
			element_service->render(); 
			food_service->render();
		}

		ui_service->render();
	}

	void ServiceLocator::clearAllServices()
	{
		delete(ui_service);
		delete(graphic_service);
		delete(sound_service);
		delete(event_service);
		delete(time_service);
		delete(player_service);
		delete(level_service);
		delete(element_service);
		delete(food_service);

	}

	ServiceLocator* ServiceLocator::getInstance()
	{
		static ServiceLocator instance;
		return &instance;
	}

	EventService* ServiceLocator::getEventService() { return event_service; }

	GraphicService* ServiceLocator::getGraphicService() { return graphic_service; }

	SoundService* ServiceLocator::getSoundService() { return sound_service; }

	UIService* ServiceLocator::getUIService() { return ui_service; }

	TimeSpace::TimeService* ServiceLocator::getTimeService() { return time_service; }

	Player::PlayerService* ServiceLocator::getPlayerService() { return player_service; }

	Level::LevelService* ServiceLocator::getLevelService() { return level_service; }

	Element::ElementService* ServiceLocator::getElementService() { return element_service; }

	Food::FoodService* ServiceLocator::getFoodService() { return food_service; }

	void ServiceLocator::deleteServiceLocator() { delete(this); }
}