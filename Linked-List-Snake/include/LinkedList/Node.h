#pragma once
#include "Player/BodyPart.h"

using namespace Player;

namespace LinkedList
{
    struct Node
    {
        BodyPart body_part;
        Node* next = nullptr;
    };
}
