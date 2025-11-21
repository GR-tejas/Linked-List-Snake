#include "LinkedListLib/LinkedList.h"
#include "Player/BodyPart.h"
#include "Level/LevelView.h"

namespace LinkedListLib
{
    using namespace Player;
    using namespace Level;

    LinkedList::LinkedList()
    {
        head_node = nullptr;
        linked_list_size = 0;
        node_width = 0.0f;
        node_height = 0.0f;
        default_position = sf::Vector2i(0, 0);
        default_direction = Direction::RIGHT;
    }

    LinkedList::~LinkedList()
    {
        //Destructor
    }

    void LinkedList::initialize(float width, float height, sf::Vector2i position, Direction direction)
    {
        node_width = width;
        node_height = height;
        default_position = position;
        default_direction = direction;
        linked_list_size = 0;
    }

    void LinkedList::render()
    {
        Node* cur_node = head_node;
        while (cur_node != nullptr)
        {
            cur_node->body_part.render();
            cur_node = cur_node->next;
        }
    }

    int LinkedList::findMiddleNode()
    {
        if (head_node == nullptr)
            return 0;

        Node* slow = head_node;
        Node* fast = head_node;
        int midIndex = 0;
        
        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
            midIndex++;
        }

        return midIndex;
    }

    Node* LinkedList::findNodeAtIndex(int index)
    {
        if (index < 0 || index >= linked_list_size || head_node == nullptr)
            return nullptr;

        Node* cur_node = head_node;
        for (int i = 0; i < index && cur_node != nullptr; i++)
        {
            cur_node = cur_node->next;
        }
        return cur_node;
    }

    sf::Vector2i LinkedList::getNewNodePosition(Node* reference_node, Operation operation)
    {
        if (reference_node == nullptr)
            return default_position;

        switch (operation)
        {
        case Operation::HEAD:
            return reference_node->body_part.getNextPosition();
        case Operation::TAIL:
            return reference_node->body_part.getPrevPosition();
        case Operation::MID:
            return reference_node->body_part.getNextPosition();
        }
        return default_position;
    }

    void LinkedList::initializeNode(Node* new_node, Node* reference_node, Operation operation)
    {
        if (new_node == nullptr)
            return;

        if (reference_node == nullptr)
        {
            new_node->body_part.initialize(node_width, node_height, default_position, default_direction);
            new_node->next = nullptr;
            return;
        }

        sf::Vector2i position = getNewNodePosition(reference_node, operation);
        new_node->body_part.initialize(node_width, node_height, position, reference_node->body_part.getDirection());
        new_node->next = nullptr;
    }

    Direction LinkedList::getReverseDirection(Direction reference_direction)
    {
        switch (reference_direction)
        {
        case Direction::UP:
            return Direction::DOWN;
        case Direction::DOWN:
            return Direction::UP;
        case Direction::LEFT:
            return Direction::RIGHT;
        case Direction::RIGHT:
            return Direction::LEFT;
        default:
            return Direction::RIGHT;
        }
    }

    void LinkedList::updateNodePosition()
    {
        Node* cur_node = head_node;
        while (cur_node != nullptr)
        {
            cur_node->body_part.updatePosition();
            cur_node = cur_node->next;
        }
    }

    void LinkedList::updateNodeDirection(Direction direction_to_set)
    {
        Node* cur_node = head_node;
        while (cur_node != nullptr)
        {
            Direction previous_direction = cur_node->body_part.getDirection();
            cur_node->body_part.setDirection(direction_to_set);
            direction_to_set = previous_direction;
            cur_node = cur_node->next;
        }
    }

    void LinkedList::reverseNodeDirections()
    {
        Node* curr_node = head_node;
        while (curr_node != nullptr)
        {
            Direction prev_dir = curr_node->body_part.getPreviousDirection();
            Direction reversed_dir = getReverseDirection(prev_dir);
            curr_node->body_part.setDirection(reversed_dir);
            curr_node = curr_node->next;
        }
    }

    bool LinkedList::processNodeCollision()
    {
        if (head_node == nullptr) return false;

        sf::Vector2i predicted_position = head_node->body_part.getNextPosition();

        Node* cur_node = head_node->next;
        while (cur_node != nullptr)
        {
            if (cur_node->body_part.getNextPosition() == predicted_position)
            {
                return true;
            }

            cur_node = cur_node->next;
        }

        return false;
    }


    Node* LinkedList::getHeadNode()
    {
        return head_node;
    }

    int LinkedList::getLinkedListSize()
    {
        return linked_list_size;
    }

    std::vector<sf::Vector2i> LinkedList::getNodesPositionList()
    {
        std::vector<sf::Vector2i> nodes_position_list;

        if (linked_list_size > 0)
            nodes_position_list.reserve(linked_list_size);

        Node* cur_node = head_node;
        while (cur_node != nullptr)
        {
            nodes_position_list.push_back(cur_node->body_part.getPosition());
            cur_node = cur_node->next;
        }
        return nodes_position_list;
    }
}
