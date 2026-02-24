#include "Block.h"
#include "Sprite.h"
#include <assert.h>

namespace
{
	const std::string TEXTURE_ID = "platform";
}

namespace ArkanoidGame
{
	Block::Block(const sf::Vector2f& position, const sf::Color& color)
		: GameObject(TEXTURES_PATH + TEXTURE_ID + ".png", position, BLOCK_WIDTH, BLOCK_HEIGHT)
	{
		sprite.setColor(color);
	}

	bool Block::GetCollision(std::shared_ptr<Colladiable> collidableObject) const {
		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidableObject);
		assert(gameObject);
		sf::Rect rect = gameObject->GetRect();
		rect.width *= 1.1;
		return GetRect().intersects(gameObject->GetRect());
	}

	void Block::OnHit()
	{
		hitCount = 0;
	}

	bool Block::IsBroken()
	{
		return hitCount <= 0;
	}
	
	void Block::Update(float timeDelta)
	{
		
	}

	Block::~Block()
	{
		
	}

	SlowBrakeBlock::SlowBrakeBlock(const sf::Vector2f& position, const sf::Color& color)
		:Block(position, color), color (color)
	{
		
	}
	
	void SlowBrakeBlock::Update(float timeDelta)
	{
		UpdateTimer(timeDelta);
	}

	bool SlowBrakeBlock::GetCollision(std::shared_ptr<Colladiable> collidableObject) const
	{
		if (isTimerStarted_)
			return false;
		
		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidableObject);
		assert(gameObject);
		sf::Rect rect = gameObject->GetRect();
		rect.width *= 1.1f;
		return GetRect().intersects(gameObject->GetRect());
	}
	
	void SlowBrakeBlock::OnHit()
	{
		StartTimer(BREAK_DELAY);
	}

	void SlowBrakeBlock::FinalAction()
	{
		--hitCount;
	}

	void SlowBrakeBlock::EachTickAction(float deltaTime)
	{
		color.a = 255 * currentTime_ / destroyTime_;
		sprite.setColor(color);
	}
	
	UnbreackableBlock::UnbreackableBlock(const sf::Vector2f& position)
		: Block(position, sf::Color::Color(105, 105, 105))
	{
		
	}

	void UnbreackableBlock::OnHit() 
	{
		--hitCount ;
	}
}
