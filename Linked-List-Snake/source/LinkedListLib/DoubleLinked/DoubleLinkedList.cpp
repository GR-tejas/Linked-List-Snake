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

            if (head_node == nullptr)
            {
                head_node = new_node;
                static_cast<DoubleNode*>(new_node)->previous = nullptr; 
                initializeNode(new_node, nullptr, Operation::TAIL);
                return;
            }

            Node* cur_node = head_node;
            while (cur_node->next != nullptr) 
            {
                cur_node = cur_node->next;
            }

            cur_node->next = new_node;
            static_cast<DoubleNode*>(new_node)->previous = cur_node;

            initializeNode(new_node, cur_node, Operation::TAIL);
        }

        void DoubleLinkedList::removeAllNodes()
        {
            if (head_node == nullptr) return;

            while (head_node != nullptr)
            {
                removeNodeAtHead();
            }
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
    }
}
