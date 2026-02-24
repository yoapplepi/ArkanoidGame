#include "Block.h"
#include "Sprite.h"
#include <assert.h>

namespace
{
	const std::string TEXTURE_ID = "platform";
}

namespace ArkanoidGame
{
	Block::Block(const sf::Vector2f& position, const sf::Color& color, int hp)
		: GameObject(TEXTURES_PATH + TEXTURE_ID + ".png", position, BLOCK_WIDTH, BLOCK_HEIGHT)
	{
		hitCount = hp;
		sprite.setColor(color);
	}

	bool Block::GetCollision(std::shared_ptr<Colladiable> collidableObject) const {
		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidableObject);
		assert(gameObject);
		return GetRect().intersects(gameObject->GetRect());
	}

	void Block::OnHit() 
	{
		if (hitCount > 0) --hitCount;
	}

	bool Block::IsBroken() 
	{
		return hitCount <= 0;
	}
    
	void Block::Update(float timeDelta) {}

	Block::~Block() {}

	DurabilityBlock::DurabilityBlock(const sf::Vector2f& position)
		: Block(position, sf::Color::Red, 3) 
	{}

	void DurabilityBlock::OnHit() 
	{
		Block::OnHit();
		if (hitCount == 2) sprite.setColor(sf::Color::Yellow);
		if (hitCount == 1) sprite.setColor(sf::Color::Magenta);
	}

	GlassBlock::GlassBlock(const sf::Vector2f& position)
		: Block(position, sf::Color(173, 216, 230, 150), 1) // Полупрозрачный голубой
	{}

	UnbreackableBlock::UnbreackableBlock(const sf::Vector2f& position)
	   : Block(position, sf::Color(105, 105, 105), 1000) // Огромное HP
	{}

	void UnbreackableBlock::OnHit()
	{
		
	}

	SlowBrakeBlock::SlowBrakeBlock(const sf::Vector2f& position, const sf::Color& color)
	   : Block(position, color), color(color) {}
    
	void SlowBrakeBlock::Update(float timeDelta) { UpdateTimer(timeDelta); }

	void SlowBrakeBlock::OnHit() { StartTimer(BREAK_DELAY); }

	void SlowBrakeBlock::FinalAction() { --hitCount; }

	void SlowBrakeBlock::EachTickAction(float deltaTime) 
	{
		color.a = static_cast<sf::Uint8>(255 * currentTime_ / destroyTime_);
		sprite.setColor(color);
	}
	
	bool SlowBrakeBlock::GetCollision(std::shared_ptr<Colladiable> collidableObject) const
	{
		if (isTimerStarted_)
			return false;
       
		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidableObject);
		assert(gameObject);
		return GetRect().intersects(gameObject->GetRect());
	}
}
