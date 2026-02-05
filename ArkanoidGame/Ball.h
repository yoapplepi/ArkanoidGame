#pragma once
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
	class Ball
	{
	public:
		Ball();

		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);

		void CollisionWithPlatform();

		sf::FloatRect GetBounds() const { return shape.getGlobalBounds(); }

	private:
		sf::CircleShape shape;
		sf::Vector2f direction;
		float speed = 400.f;
		float radius = 10.f;

	};
}