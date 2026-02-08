#include "Ball.h"
#include "GameSettings.h"
#include "Sprite.h"

namespace
{
	const std::string TEXTURE_ID = "ball";
}

namespace ArkanoidGame
{

	Ball::Ball(const sf::Vector2f& position)
		: GameObject(TEXTURES_PATH + TEXTURE_ID + ".png", position, BALL_SIZE, BALL_SIZE)
	{
		const float angle = 45.f + rand() % 90; 
		const auto pi = std::acos(-1.f);
		direction.x = std::cos(pi / 180.f * angle);
		direction.y = std::sin(pi / 180.f * angle);
	}
	

	void Ball::Update(float timeDelta)
	{
		const auto position = sprite.getPosition() + BALL_SPEED * timeDelta * direction;
		sprite.setPosition(position);

		if (position.x - BALL_SIZE / 2.f <= 0 || position.x + BALL_SIZE / 2.f >= SCREEN_WIDTH) 
			direction.x *= -1;

		if (position.y <= 0 || position.y >= SCREEN_HEIGHT)
		{
			if (position.y - BALL_SIZE / 2.f <= 0 || position.y + BALL_SIZE / 2.f >= SCREEN_HEIGHT)
				direction.y *= -1;
		}
	}

	void Ball::InvertDirectionX()
	{
		direction.x *= -1;
	}

	void Ball::InvertDirectionY()
	{
		direction.y *= -1;
	}
}
