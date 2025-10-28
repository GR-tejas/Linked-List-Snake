#include "UI/GameplayUI/GameplayUIController.h"
#include "Global/ServiceLocator.h"
#include "Player/SnakeController.h"
#include "Level/LevelService.h"
#include "Global/Config.h"

namespace UI
{
    namespace GameplayUI
    {
        using namespace Player;
        using namespace Level;
        using namespace Global;
        using namespace UI::UIElement;

        GameplayUIController::GameplayUIController()
        {
            level_number_text = nullptr;
            score_text = nullptr;
            time_complexity_text = nullptr;
            operation_text = nullptr;
            createTexts();
        }

        GameplayUIController::~GameplayUIController()
        {
            destroy();
        }

        void GameplayUIController::initialize()
        {
            initializeTexts();
        }

        void GameplayUIController::update()
        {
            updateLevelNumberText();
            updateScoreText();
            updateTimeComplexityText();
            updateOperationText();
        }

        void GameplayUIController::render()
        {
            if (level_number_text) level_number_text->render();
            if (score_text) score_text->render();
            if (time_complexity_text) time_complexity_text->render();
            if (operation_text) operation_text->render();
        }

        void GameplayUIController::show()
        {
            if (level_number_text) level_number_text->show();
            if (score_text) score_text->show();
            if (time_complexity_text) time_complexity_text->show();
            if (operation_text) operation_text->show();
        }

        void GameplayUIController::createTexts()
        {
            level_number_text = new UI::UIElement::TextView();
            score_text = new UI::UIElement::TextView();
            time_complexity_text = new UI::UIElement::TextView();
            operation_text = new UI::UIElement::TextView();
        }

        void GameplayUIController::initializeTexts()
        {
            initializeLevelNumberText();
            initializeScoreText();
            initializeTimeComplexityText();
            initializeOperationText();
        }

        void GameplayUIController::initializeLevelNumberText()
        {
            if (level_number_text)
            {
                level_number_text->initialize("Level : 1",
                    sf::Vector2f(level_number_text_x_position, text_y_position),
                    FontType::BUBBLE_BOBBLE,  // Make sure FontType is included
                    font_size,
                    sf::Color::Black);
            }
        }

        void GameplayUIController::initializeScoreText()
        {
            if (score_text)
            {
                score_text->initialize("Score : 0",
                    sf::Vector2f(score_text_x_position, text_y_position),
                    FontType::BUBBLE_BOBBLE,
                    font_size,
                    sf::Color::Black);
            }
        }

        void GameplayUIController::initializeTimeComplexityText()
        {
            if (time_complexity_text)
            {
                time_complexity_text->initialize("Time Complexity : O(1)",
                    sf::Vector2f(time_complexity_text_x_position, time_complexity_text_y_position),
                    FontType::BUBBLE_BOBBLE,
                    operations_font_size,
                    sf::Color::Black);
            }
        }

        void GameplayUIController::initializeOperationText()
        {
            if (operation_text)
            {
                operation_text->initialize("Last Operation : Insert at Middle",
                    sf::Vector2f(operations_text_x_position, operations_text_y_position),
                    FontType::BUBBLE_BOBBLE,
                    operations_font_size,
                    sf::Color::Black);
            }
        }

        void GameplayUIController::updateLevelNumberText()
        {
            if (level_number_text)
            {
                LevelNumber level_number = ServiceLocator::getInstance()->getLevelService()->getCurrentLevel();
                sf::String level_number_value = std::to_string(1 + static_cast<int>(level_number));

                level_number_text->setText("Level : " + level_number_value);
                level_number_text->update();
            }
        }

        void GameplayUIController::updateScoreText()
        {
            if (score_text)
            {
                int player_score = ServiceLocator::getInstance()->getPlayerService()->getPlayerScore();
                sf::String score_value = std::to_string(player_score);

                score_text->setText("Score : " + score_value);
                score_text->update();
            }
        }

        void GameplayUIController::updateTimeComplexityText()
        {
            if (time_complexity_text)
            {
                TimeComplexity time_complexity = ServiceLocator::getInstance()->getPlayerService()->getTimeComplexity();
                sf::String time_complexity_value;

                switch (time_complexity)
                {
                case TimeComplexity::NONE:
                    time_complexity_value = "";
                    break;
                case TimeComplexity::ONE:
                    time_complexity_value = "1";
                    break;
                case TimeComplexity::N:
                    time_complexity_value = "N";
                    break;
                default:
                    time_complexity_value = "";
                    break;
                }

                time_complexity_text->setText("Time Complexity : O(" + time_complexity_value + ")");
                time_complexity_text->update();
            }
        }

        void GameplayUIController::updateOperationText()
        {
            if (operation_text)
            {
                LinkedListOperations operation = ServiceLocator::getInstance()->getPlayerService()->getLastOperation();
                sf::String operation_value;

                switch (operation)
                {
                case LinkedListOperations::NONE:
                    operation_value = "";
                    break;
                case LinkedListOperations::INSERT_AT_HEAD:
                    operation_value = "Insert at Head";
                    break;
                case LinkedListOperations::INSERT_AT_TAIL:
                    operation_value = "Insert at Tail";
                    break;
                case LinkedListOperations::INSERT_AT_MID:
                    operation_value = "Insert at Mid";
                    break;
                case LinkedListOperations::REMOVE_AT_HEAD:
                    operation_value = "Remove at Head";
                    break;
                case LinkedListOperations::REMOVE_AT_TAIL:
                    operation_value = "Remove at Tail";
                    break;
                case LinkedListOperations::REMOVE_AT_MID:
                    operation_value = "Remove at Mid";
                    break;
                case LinkedListOperations::DELETE_HALF_LIST:
                    operation_value = "Delete Half List";
                    break;
                case LinkedListOperations::REVERSE_LIST:
                    operation_value = "Reverse List";
                    break;
                default:
                    operation_value = "";
                    break;
                }

                operation_text->setText("Last Operation : " + operation_value);
                operation_text->update();
            }
        }

        void GameplayUIController::destroy()
        {
            if (level_number_text)
            {
                delete level_number_text;
                level_number_text = nullptr;
            }

            if (score_text)
            {
                delete score_text;
                score_text = nullptr;
            }

            if (time_complexity_text)
            {
                delete time_complexity_text;
                time_complexity_text = nullptr;
            }

            if (operation_text)
            {
                delete operation_text;
                operation_text = nullptr;
            }
        }
    }
}
