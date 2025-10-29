#pragma once
#include "Player/BodyPart.h"

namespace LinkedListLib
{
    using namespace Player;

    struct Node
    {
        BodyPart body_part;     // Common data for all nodes
        Node* next = nullptr;   // Common pointer for all nodes
    };
}
