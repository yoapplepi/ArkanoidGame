#include "Ball.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <assert.h>

namespace
{
	const std::string TEXTURE_ID = "ball";
}

namespace ArkanoidGame
{
	void Ball::Init()
	{
		assert(texture.loadFromFile(TEXTURES_PATH + TEXTURE_ID + ".png"));

		InitSprite(sprite, BALL_SIZE, BALL_SIZE, texture);
		sprite.setPosition({ SCREEN_WIDTH / 2.0, SCREEN_HEIGHT - PLATFORM_HEIGHT - BALL_SIZE / 2.f });

		const float angle = 45.f + rand() % 90; // [45, 135] degree
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

	void Ball::ReboundFromPlatform()
	{
		direction.y *= -1;
	}
}
