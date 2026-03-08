#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Collidable.h"

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
		
		bool GetCollision(std::shared_ptr<Colladiable> collidable) const  override;
		void ChangeAngle(float x);
		
		void SetIsFireball(bool value) {isFireBall = value;}
		bool IsFireBall() const {return isFireBall;}
		void SetPosition(const sf::Vector2f& position);
		
	private:
		sf::Vector2f direction;
		void OnHit();
		float lastAngle = 90;
		bool isFireBall = false;
	};
}