#pragma once
#include "GameObject.h"
#include "Collidable.h"
#include "IDelay.h"

namespace ArkanoidGame
{
	class Block : public GameObject, public Colladiable
	{
	protected:
		int hitCount = 1;
		
	public:
		virtual void OnHit();
		Block(const sf::Vector2f& position, const sf::Color& color = sf::Color::Green, int hp = 1);		virtual ~Block();
		bool GetCollision(std::shared_ptr<Colladiable> collidableObject) const override;
		void Update(float timeDelta) override;

		virtual bool IsBroken();
	};
	
	class DurabilityBlock : public Block
	{
	public:
		DurabilityBlock(const sf::Vector2f& position);
		void OnHit() override; 
	};

	class GlassBlock : public Block
	{
	public:
		GlassBlock(const sf::Vector2f& position);
	};
	
	class SlowBrakeBlock : public Block, public IDelayedAction
	{
	protected:
		void OnHit() override;
		sf::Color color;
	public:
		SlowBrakeBlock(const sf::Vector2f& position, const sf::Color& color = sf::Color::Green);
		~SlowBrakeBlock() = default;
		void Update(float timeDelta) override;

		bool GetCollision(std::shared_ptr<Colladiable> collidableObject) const override;
		void FinalAction() override;
		void EachTickAction(float deltaTime) override;
	};

	class UnbreackableBlock : public Block
	{
	public:
		UnbreackableBlock(const sf::Vector2f& position);
		void OnHit() override;
		
		void Update(float) 
		{
			int i = 0;
			++i;
		};
	};
}