#pragma once
#include <SFML/Graphics.hpp>
#include "UI/UIElement/ImageView.h"
#include "Direction.h"

using namespace sf;

namespace Player
{
	class BodyPart
	{
	protected:
		UI::UIElement::ImageView* bodypart_image;

		sf::Vector2i grid_position;
		Direction direction;
		Direction previous_direction;

		float bodypart_width;
		float bodypart_height;

		void createBodyPartImage();
		void initializeBodyPartImage();
		sf::Vector2f getBodyPartScreenPosition();

		void destroy();

	public:
		BodyPart();
		~BodyPart();

		void initialize(float width, float height, Vector2i pos, Direction dir);
		float getRotationAngle();
		void setDirection(Direction direction);
		Direction getDirection();
		Direction getPreviousDirection();
		void setPosition(Vector2i position);
		Vector2i getPosition();
		void updatePosition();
		Vector2i getNextPosition();
		Vector2i getNextPositionDown();
		Vector2i getNextPositionUp();
		Vector2i getNextPositionLeft();
		Vector2i getNextPositionRight();
		sf::Vector2i getPrevPosition();
		void render();
	};
}
