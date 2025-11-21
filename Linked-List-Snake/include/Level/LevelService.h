#pragma once
#include "Level/LevelConfig.h" 

namespace Level
{
    class LevelController;

    class LevelService
    {
    private:
        LevelController* level_controller;
        LevelNumber current_level;
        LinkedListType current_linked_list_type; 

        void spawnLevelElements(LevelNumber level_to_load);
        void spawnFood();
        void spawnPlayer(LinkedListType linked_list_type); 

        void createLevelController();
        void destroy();

    public:
        LevelService();
        ~LevelService();

        void initialize();
        void update();
        void render();

        LevelNumber getCurrentLevel();
        LinkedListType getCurrentLinkedListType(); 

        void setCurrentLevelNumber(LevelNumber level_to_load);

        void createLevel(LinkedListType linked_list_type); 

        float getCellWidth();
        float getCellHeight();
    };
}
