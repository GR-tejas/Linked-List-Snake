#pragma once
#include "Graphics/GraphicService.h"
#include "Event/EventService.h"
#include "UI/UIService.h"
#include "Sound/SoundService.h"
#include "Level/LevelService.h"
#include "Time/TimeService.h"
#include "Player/PlayerService.h"
#include "Element/ElementService.h"
#include "Food/FoodService.h" 

namespace Global
{
    class ServiceLocator
    {
    private:
        EventSpace::EventService* event_service;
        Graphics::GraphicService* graphic_service;
        SoundSpace::SoundService* sound_service;
        UI::UIService* ui_service;
        Level::LevelService* level_service;
        TimeSpace::TimeService* time_service;
        Player::PlayerService* player_service;
        Element::ElementService* element_service;
        Food::FoodService* food_service;

        ServiceLocator();
        ~ServiceLocator();

        void createServices();
        void clearAllServices();

    public:
        static ServiceLocator* getInstance();

        void initialize();
        void update();
        void render();

        EventSpace::EventService* getEventService();
        Graphics::GraphicService* getGraphicService();
        SoundSpace::SoundService* getSoundService();
        UI::UIService* getUIService();
        Level::LevelService* getLevelService();
        TimeSpace::TimeService* getTimeService();
        Player::PlayerService* getPlayerService();
        Element::ElementService* getElementService();
        Food::FoodService* getFoodService();
        void deleteServiceLocator();
    };
}