#pragma once
#include <SFML/Graphics.hpp>
#include "Collidable.h"
#include "GameObject.h"

namespace ArkanoidGame
{
	class Ball final : public GameObject, public Colladiable
	{
	public:
		Ball(const sf::Vector2f& position);
		~Ball() = default;

		void Update(float timeDelta)override;

		void InvertDirectionX();
		void InvertDirectionY();

		bool GetCollision(std::shared_ptr<Colladiable> collidable) const override;
		void ChangeAngle(float x);

	private:
		sf::Vector2f direction;		
		void OnHit();
		float lastAngle = 90;
	};
}