#pragma once
#include "GameObject.h"
#include "Ball.h"

namespace ArkanoidGame
{
	class Block : public GameObject
	{
	public:
		Block(const sf::Vector2f& position);

		void Update(float timeDelta) override;
		bool CheckCollisionWithBall(const Ball& ball) const;

	};

}
