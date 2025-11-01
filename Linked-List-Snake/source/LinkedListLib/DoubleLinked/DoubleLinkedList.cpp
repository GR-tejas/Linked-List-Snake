#include "LinkedListLib/DoubleLinked/DoubleLinkedList.h"
#include "LinkedListLib/DoubleLinked/DoubleNode.h"

namespace LinkedListLib
{
    namespace DoubleLinked
    {
        DoubleLinkedList::DoubleLinkedList() : LinkedList()
        {

        }

        DoubleLinkedList::~DoubleLinkedList()
        {
            removeAllNodes();
        }

        Node* DoubleLinkedList::createNode()
        {
            return new DoubleNode();
        }

        void DoubleLinkedList::removeNodeAtMiddle()
        {
            if (head_node == nullptr) return;

            linked_list_size--;

            if (head_node->next == nullptr)
            {
                delete head_node;
                head_node = nullptr;
                return;
            }

            if (head_node->next->next == nullptr)
            {
                Node* second_node = head_node->next;
                head_node->next = nullptr;
                delete second_node;
                return;
            }

            Node* slow = head_node;
            Node* fast = head_node;

            while (fast != nullptr && fast->next != nullptr)
            {
                slow = slow->next;
                fast = fast->next->next;
            }

            Node* middle_node = slow;
            Node* previous_node = static_cast<DoubleNode*>(middle_node)->previous;
            Node* next_node = middle_node->next;

            if (previous_node != nullptr)
            {
                previous_node->next = next_node;
            }

            if (next_node != nullptr)
            {
                static_cast<DoubleNode*>(next_node)->previous = previous_node;
            }

            if (middle_node == head_node)
            {
                head_node = next_node;
            }

            middle_node->next = nullptr;
            delete middle_node;
        }

        void DoubleLinkedList::removeNodeAtHead()
        {
            if (head_node == nullptr) return;

            linked_list_size--;

            Node* cur_node = head_node;
            head_node = head_node->next;

            if (head_node != nullptr)
            {
                static_cast<DoubleNode*>(head_node)->previous = nullptr;
            }

            cur_node->next = nullptr;
            delete cur_node;
        }

        void DoubleLinkedList::insertNodeAtTail()
        {
            linked_list_size++;
            Node* new_node = createNode();
            Node* cur_node = head_node;

            if (cur_node == nullptr)
            {
                head_node = new_node;
                static_cast<DoubleNode*>(new_node)->previous = nullptr;
                initializeNode(new_node, nullptr, Operation::TAIL);
                return;
            }

            while (cur_node->next != nullptr)
            {
                cur_node = cur_node->next;
            }

            cur_node->next = new_node;
            static_cast<DoubleNode*>(new_node)->previous = cur_node;
            initializeNode(new_node, cur_node, Operation::TAIL);
        }

        void DoubleLinkedList::insertNodeAtIndex(int index)
        {
            if (index < 0 || index >= linked_list_size) return;

            if (index == 0)
            {
                insertNodeAtHead();
                return;
            }

            Node* new_node = createNode();
            int current_index = 0;
            Node* cur_node = head_node;
            Node* prev_node = nullptr;

            while (cur_node != nullptr && current_index < index)
            {
                prev_node = cur_node;
                cur_node = cur_node->next;
                current_index++;
            }

            prev_node->next = new_node;
            static_cast<DoubleNode*>(new_node)->previous = prev_node;
            new_node->next = cur_node;

            if (cur_node != nullptr)
            {
                static_cast<DoubleNode*>(cur_node)->previous = new_node;
            }

            initializeNode(new_node, prev_node, Operation::TAIL);
            linked_list_size++;

            shiftNodesAfterInsertion(new_node, cur_node, prev_node);
        }

        void DoubleLinkedList::insertNodeAtMiddle()
        {
            if (head_node == nullptr) {
                insertNodeAtHead();
                return;
            }

            int midIndex = findMiddleNode();
            insertNodeAtIndex(midIndex);
        }

        void DoubleLinkedList::removeAllNodes()
        {
            if (head_node == nullptr) return;

            while (head_node != nullptr)
            {
                removeNodeAtHead();
            }
        }

        Direction DoubleLinkedList::reverse()
        {
            if (head_node == nullptr || head_node->next == nullptr)
            {
                return (head_node != nullptr) ? head_node->body_part.getDirection() : Direction::RIGHT;
            }

            Node* current = head_node;
            Node* new_head = nullptr;

            while (current != nullptr)
            {
                Node* next_node = current->next;

                DoubleNode* double_current = static_cast<DoubleNode*>(current);

                Node* temp = double_current->previous;
                double_current->previous = current->next;
                current->next = temp;

                new_head = current;

                current = next_node;
            }

            head_node = new_head;

            reverseNodeDirections();

            return head_node->body_part.getDirection();
        }

        void DoubleLinkedList::removeHalfNodes()
        {
            if (head_node == nullptr) return;

            if (linked_list_size <= 1)
            {
                removeAllNodes();
                return;
            }

            int nodes_to_remove = linked_list_size / 2;
            for (int i = 0; i < nodes_to_remove; i++)
            {
                if (head_node != nullptr)
                {
                    removeNodeAtHead();
                }
                else
                {
                    break;
                }
            }
        }

        void DoubleLinkedList::insertNodeAtHead()
        {
            linked_list_size++;
            Node* new_node = createNode();

            if (head_node == nullptr)
            {
                head_node = new_node;
                static_cast<DoubleNode*>(new_node)->previous = nullptr;
                initializeNode(new_node, nullptr, Operation::HEAD);
                return;
            }

            initializeNode(new_node, head_node, Operation::HEAD);

            new_node->next = head_node;

            static_cast<DoubleNode*>(head_node)->previous = new_node;

            head_node = new_node;
        }


        void DoubleLinkedList::removeNodeAtTail()
        {
            if (head_node == nullptr) return;

            linked_list_size--;

            if (head_node->next == nullptr)
            {
                delete head_node;
                head_node = nullptr;
                return;
            }

            Node* cur_node = head_node;
            while (cur_node->next != nullptr)
            {
                cur_node = cur_node->next;
            }

            Node* prev_node = static_cast<DoubleNode*>(cur_node)->previous;
            if (prev_node != nullptr)
            {
                prev_node->next = nullptr;
            }

            delete cur_node;
        }

        void DoubleLinkedList::removeNodeAt(int index)
        {
            if (index < 0 || index >= linked_list_size) return;

            if (index == 0)
            {
                removeNodeAtHead();
            }
            else
            {
                removeNodeAtIndex(index);
            }
        }

        void DoubleLinkedList::removeNodeAtIndex(int index)
        {
            int current_index = 0;
            Node* cur_node = head_node;

            while (cur_node != nullptr && current_index < index)
            {
                cur_node = cur_node->next;
                current_index++;
            }

            if (cur_node == nullptr) return;

            Node* prev_node = static_cast<DoubleNode*>(cur_node)->previous;
            Node* next_node = cur_node->next;

            if (prev_node != nullptr)
            {
                prev_node->next = next_node;
            }
            else
            {
                head_node = next_node; // cur_node was the head
            }

            if (next_node != nullptr)
            {
                static_cast<DoubleNode*>(next_node)->previous = prev_node;
            }

            shiftNodesAfterRemoval(cur_node);
            delete cur_node;
            linked_list_size--;
        }

        void DoubleLinkedList::shiftNodesAfterInsertion(Node* new_node, Node* cur_node, Node* prev_node)
        {
            Node* next_node = cur_node;
            cur_node = new_node;

            while (cur_node != nullptr && next_node != nullptr)
            {
                cur_node->body_part.setPosition(next_node->body_part.getPosition());
                cur_node->body_part.setDirection(next_node->body_part.getDirection());

                prev_node = cur_node;
                cur_node = next_node;
                next_node = next_node->next;
            }

            initializeNode(cur_node, prev_node, Operation::TAIL);
        }

        void DoubleLinkedList::shiftNodesAfterRemoval(Node* cur_node)
        {
            sf::Vector2i previous_node_position = cur_node->body_part.getPosition();
            Direction previous_node_direction = cur_node->body_part.getDirection();
            cur_node = cur_node->next;

            while (cur_node != nullptr)
            {
                sf::Vector2i temp_node_position = cur_node->body_part.getPosition();
                Direction temp_node_direction = cur_node->body_part.getDirection();

                cur_node->body_part.setPosition(previous_node_position);
                cur_node->body_part.setDirection(previous_node_direction);

                cur_node = cur_node->next;
                previous_node_position = temp_node_position;
                previous_node_direction = temp_node_direction;
            }
        }
    }
}
