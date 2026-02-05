#include "Ball.h"
#include "GameSettings.h"
#include <cmath>
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
	Ball::Ball()
	{
		shape.setRadius(radius);
		shape.setFillColor(sf::Color::Yellow);

		shape.setOrigin(radius, radius);

		shape.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 100.f);

		direction = { 0.5f, -1.f };

		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		direction /= length;

	}

	void Ball::Update(float timeDelta)
	{
		shape.move(direction * speed * timeDelta);

		if (shape.getPosition().x - radius < 0)
		{
			shape.setPosition(radius, shape.getPosition().y);
			direction.x = -direction.x;
		}

		else if(shape.getPosition().x + radius > SCREEN_WIDTH)
		{
			shape.setPosition(SCREEN_WIDTH - radius, shape.getPosition().y);
			direction.x = -direction.x;
		}

		if(shape.getPosition().y - radius < 0)
		{
			shape.setPosition(shape.getPosition().x, radius);
			direction.y = -direction.y;
		}
		else if (shape.getPosition().y + radius > SCREEN_HEIGHT)
		{
			shape.setPosition(shape.getPosition().x, SCREEN_HEIGHT - radius);
			direction.y = -direction.y;
		}
	}

	void Ball::Draw(sf::RenderWindow& window)
	{
		window.draw(shape);
	}

	void Ball::CollisionWothPlatform()
	{
		if (direction.y > 0)
		{
			direction.y = -direction.y;
		}
	}
}