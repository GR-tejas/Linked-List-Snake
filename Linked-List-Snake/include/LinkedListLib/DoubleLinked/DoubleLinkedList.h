#pragma once
#include "LinkedListLib/LinkedList.h"
#include "LinkedListLib/DoubleLinked/DoubleNode.h"

namespace LinkedListLib
{
    namespace DoubleLinked
    {
        class DoubleLinkedList : public LinkedList
        {
        protected:
            virtual Node* createNode() override;

        private:
            void shiftNodesAfterInsertion(Node* new_node, Node* cur_node, Node* prev_node);
            void shiftNodesAfterRemoval(Node* cur_node);
            void removeNodeAtIndex(int index);

        public:
            DoubleLinkedList();
            ~DoubleLinkedList();

            void insertNodeAtTail() override;
            void insertNodeAtHead() override;
            void insertNodeAtMiddle() override;
            void insertNodeAtIndex(int index) override;

            void removeNodeAtTail() override;
            void removeNodeAtHead() override;
            void removeNodeAtMiddle() override;
            void removeNodeAt(int index) override;
            void removeAllNodes() override;
            void removeHalfNodes() override;

            Direction reverse() override;
        };
    }
}
