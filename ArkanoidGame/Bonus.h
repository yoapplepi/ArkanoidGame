#pragma once 
#include <SFML/Graphics.hpp>
#include <memory>

namespace ArkanoidGame 
{ 

    enum class BonusType { SpeedUp, FireBall, ExpandPaddle, FragileBlocks };

    class Bonus : public sf::Drawable 
    {
    public:
        Bonus(BonusType t, sf::Vector2f position);
        
        void update(float dt);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        
        BonusType getType() const { return type; }
        sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }

    private:
        sf::CircleShape shape;
        BonusType type;
        float speed = 150.f;
    };

    class BonusFactory
    {
    public:
        static std::unique_ptr<Bonus> createRandomBonus(sf::Vector2f position)
        {
            BonusType type = static_cast<BonusType>(rand() % 4);
            return std::make_unique<Bonus>(type, position);
        }
    };
}