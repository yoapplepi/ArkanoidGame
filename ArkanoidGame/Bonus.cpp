#include "Bonus.h"

namespace ArkanoidGame
{
    Bonus::Bonus(BonusType t, sf::Vector2f position) : type(t) {
        shape.setRadius(12.f); // Размер шарика
        shape.setOrigin(12.f, 12.f); // Центрируем
        shape.setPosition(position);

        // Раскрашиваем бонусы, чтобы их отличать
        switch (type) {
        case BonusType::FireBall: 
            shape.setFillColor(sf::Color::Red); break;
        case BonusType::ExpandPaddle: 
            shape.setFillColor(sf::Color::Blue); break;
        case BonusType::FragileBlocks: 
            shape.setFillColor(sf::Color::Magenta); break;
        default: 
            shape.setFillColor(sf::Color::Green); break;
        }
    
        // Добавим обводку, чтобы красиво смотрелось
        shape.setOutlineThickness(2.f);
        shape.setOutlineColor(sf::Color::White);
    }

    void Bonus::update(float dt) {
        shape.move(0.f, speed * dt);
    }

    void Bonus::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(shape, states);
    }
}
