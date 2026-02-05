#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include <list>

namespace ArkanoidGame
{
	class Platform
	{

	public:
		Platform();

		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);

		sf::FloatRect GetBounds() const { return shape.getGlobalBounds(); }

	private:
		sf::RectangleShape shape;
		float speed = 500.f;
	};
}
