#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "LinkedList/Node.h"
#include "Player/Direction.h"

namespace LinkedList
{
	enum class Operation
	{
		HEAD,
		MID,
		TAIL,
	};

	class SingleLinkedList
	{
	private:
		Node* head_node;

		float node_width;
		float node_height;

		sf::Vector2i default_position;
		Direction default_direction;

		int linked_list_size;

		void shiftNodesAfterInsertion(Node* new_node, Node* cur_node, Node* prev_node);

		Node* createNode();

	public:
		SingleLinkedList();
		~SingleLinkedList();

		void initialize(float width, float height, sf::Vector2i position, Direction direction);
		void render();

		sf::Vector2i getNewNodePosition(Node* reference_node, Operation operation);
		void initializeNode(Node* new_node, Node* reference_node, Operation operation);

		Direction reverse();
		void reverseNodeDirections();
		Direction getReverseDirection(Direction reference_direction);

		void insertNodeAtTail();
		void insertNodeAtHead();
		void insertNodeAtIndex(int index);

		void removeNodeAtHead();
		void removeNodeAtTail();
		void removeNodeAtIndex(int index);
		void removeNodeAtMiddle();
		void removeHalfNodes();
		void removeAllNodes();

		void updateNodeDirection(Direction direction_to_set);
		void updateNodePosition();
		bool processNodeCollision();

		void insertNodeAtMiddle();
		int findMiddleNode();
		Node* findNodeAtIndex(int index);

		Node* getHeadNode();
		std::vector<sf::Vector2i> getNodesPositionList();
		int getSize();
	};
}
