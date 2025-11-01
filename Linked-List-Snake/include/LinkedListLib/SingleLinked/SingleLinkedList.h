#pragma once
#include <SFML/System/Vector2.hpp>
#include "Player/Direction.h"
#include "LinkedListLib/Node.h"
#include "LinkedListLib/LinkedList.h"

using namespace Player;

namespace LinkedListLib
{
	namespace SingleLinked
	{
		enum class Operation
		{
			HEAD,
			MID,
			TAIL,
		};

		class SingleLinkedList : public LinkedList
		{
		private:
			Node* head_node;

			float node_width;
			float node_height;

			sf::Vector2i default_position;
			Direction default_direction;

			int linked_list_size;

			Node* createNode();
			void initializeNode(Node* new_node, Node* reference_node, Operation operation);
			sf::Vector2i getNewNodePosition(Node* reference_node, Operation operation);
			Direction getReverseDirection(Direction reference_direction);

			void updateNodes(Direction directionToSet);
			int findMiddleNode();

		public:
			SingleLinkedList();
			~SingleLinkedList();

			void initialize(float width, float height, sf::Vector2i position, Direction direction);
			void render();

			void insertNodeAtTail();
			void insertNodeAtHead();
			void insertNodeAtMiddle();
			void insertNodeAtIndex(int index);
			void shiftNodesAfterInsertion(Node* new_node, Node* cur_node, Node* prev_node);

			void removeNodeAtTail();
			void removeNodeAtHead();
			void removeNodeAtMiddle();
			void removeNodeAt(int index);
			void removeNodeAtIndex(int index);
			void removeAllNodes();
			void removeHalfNodes();
			void shiftNodesAfterRemoval(Node* cur_node);

			Node* findNodeAtIndex(int index);
			Direction reverse();
			void reverseNodeDirections();
			void updateNodePosition();
			void updateNodeDirection(Direction direction_to_set);

			bool processNodeCollision();
			Node* getHeadNode();
			int getLinkedListSize();

			std::vector<sf::Vector2i> getNodesPositionList();
		};
	}
}