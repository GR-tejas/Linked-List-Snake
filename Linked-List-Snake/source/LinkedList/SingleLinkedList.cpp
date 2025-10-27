#include "LinkedList/SingleLinkedList.h"
#include "Player/BodyPart.h"
#include "Level/LevelView.h"
#include <iostream>

namespace LinkedList
{
	SingleLinkedList::SingleLinkedList()
	{
		head_node = nullptr;
	}

	SingleLinkedList::~SingleLinkedList() = default;

	void SingleLinkedList::initialize(float width, float height, sf::Vector2i position, Direction direction)
	{
		node_width = width;
		node_height = height;
		default_position = position;
		default_direction = direction;
	}

	void SingleLinkedList::render()
	{
		Node* cur_node = head_node;

		while (cur_node != nullptr)
		{
			cur_node->body_part.render();
			cur_node = cur_node->next;
		}
	}

	Node* SingleLinkedList::createNode()
	{
		return new Node();
	}

	sf::Vector2i SingleLinkedList::getNewNodePosition(Node* reference_node, Operation operation)
	{
		switch (operation)
		{
		case Operation::HEAD:
			return reference_node->body_part.getNextPosition();
		case Operation::TAIL:
			return reference_node->body_part.getPrevPosition();
		}

		return default_position;
	}

	void SingleLinkedList::initializeNode(Node* new_node, Node* reference_node, Operation operation)
	{
		if (reference_node == nullptr)
		{
			new_node->body_part.initialize(node_width, node_height, default_position, default_direction);
			return;
		}

		sf::Vector2i position = getNewNodePosition(reference_node, operation);
		new_node->body_part.initialize(node_width, node_height, position, reference_node->body_part.getDirection());
	}

	void SingleLinkedList::insertNodeAtTail()
	{
		Node* new_node = createNode();

		if (head_node == nullptr)
		{
			initializeNode(new_node, nullptr, Operation::TAIL);
			head_node = new_node;
			new_node->next = nullptr;
			return;
		}

		// Find tail node
		Node* cur_node = head_node;
		while (cur_node->next != nullptr)
		{
			cur_node = cur_node->next;
		}

		initializeNode(new_node, cur_node, Operation::TAIL);
		cur_node->next = new_node;
		new_node->next = nullptr;
	}

	void SingleLinkedList::insertNodeAtHead()
	{
		Node* new_node = createNode();

		if (head_node == nullptr)
		{
			initializeNode(new_node, nullptr, Operation::HEAD);
			head_node = new_node;
			new_node->next = nullptr;
			return;
		}

		initializeNode(new_node, head_node, Operation::HEAD);
		new_node->next = head_node;
		head_node = new_node;
	}

	void SingleLinkedList::insertNodeAtIndex(int index)
	{
		if (index <= 0)
		{
			insertNodeAtHead();
			return;
		}

		Node* cur_node = head_node;
		for (int i = 0; i < index - 1 && cur_node != nullptr; i++)
		{
			cur_node = cur_node->next;
		}

		if (cur_node == nullptr)
		{
			insertNodeAtTail();
			return;
		}

		Node* new_node = createNode();
		initializeNode(new_node, cur_node, Operation::MID);
		new_node->next = cur_node->next;
		cur_node->next = new_node;
	}

	void SingleLinkedList::removeNodeAtHead()
	{
		if (head_node == nullptr) return;

		Node* node_to_remove = head_node;
		head_node = head_node->next;
		delete node_to_remove;
	}

	void SingleLinkedList::removeNodeAtTail()
	{
		if (head_node == nullptr) return;

		if (head_node->next == nullptr)
		{
			delete head_node;
			head_node = nullptr;
			return;
		}

		Node* cur_node = head_node;
		while (cur_node->next->next != nullptr)
		{
			cur_node = cur_node->next;
		}

		delete cur_node->next;
		cur_node->next = nullptr;
	}

	void SingleLinkedList::removeNodeAtIndex(int index)
	{
		if (index <= 0 || head_node == nullptr)
		{
			removeNodeAtHead();
			return;
		}

		Node* cur_node = head_node;
		for (int i = 0; i < index - 1 && cur_node->next != nullptr; i++)
		{
			cur_node = cur_node->next;
		}

		if (cur_node->next == nullptr) return;

		Node* node_to_remove = cur_node->next;
		cur_node->next = node_to_remove->next;
		delete node_to_remove;
	}

	void SingleLinkedList::removeAllNodes()
	{
		while (head_node != nullptr)
		{
			removeNodeAtHead();
		}
	}

	void SingleLinkedList::updateNodeDirection(Direction direction_to_set)
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

	void SingleLinkedList::updateNodePosition()
	{
		Node* cur_node = head_node;

		while (cur_node != nullptr)
		{
			cur_node->body_part.updatePosition();
			cur_node = cur_node->next;
		}
	}

	bool SingleLinkedList::processNodeCollision()
	{
		if (head_node == nullptr)
		{
			return false;
		}

		sf::Vector2i head_next_position = head_node->body_part.getNextPosition();
		Node* cur_node = head_node->next;

		while (cur_node != nullptr)
		{
			if (cur_node->body_part.getNextPosition().x == head_next_position.x &&
				cur_node->body_part.getNextPosition().y == head_next_position.y)
			{
				return true;
			}
			cur_node = cur_node->next;
		}

		return false;
	}

	std::vector<sf::Vector2i> SingleLinkedList::getNodesPositionList()
	{
		std::vector<sf::Vector2i> nodes_position_list;

		Node* cur_node = head_node;

		while (cur_node != nullptr)
		{
			nodes_position_list.push_back(cur_node->body_part.getPosition());
			cur_node = cur_node->next;
		}

		return nodes_position_list;
	}

	LinkedList::Node* SingleLinkedList::getHeadNode()
	{
		return head_node;
	}
}
