#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <list>

namespace ArkanoidGame
{
	class Ball;

	class Platform : public GameObject
	{

	public:
		Platform() = default;

		void Init()override;
		void Update(float timeDelta)override;

		bool CheckCollisionWithBall(const Ball& ball)const;

	private:
		void Move(float speed);
	};
}
