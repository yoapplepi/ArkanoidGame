#include "Platform.h"
#include "GameSettings.h"
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
	Platform::Platform()
	{
		shape.setSize(sf::Vector2f(100.f, 20.f));
		shape.setFillColor(sf::Color::Green);

		shape.setOrigin(shape.getSize().x / 2.f, shape.getSize().y / 2.f);
		shape.setPosition((SCREEN_WIDTH - shape.getSize().x) / 2, SCREEN_HEIGHT - shape.getSize().y - 10.f);
	}

	void Platform::Update(float timeDelta, const sf::RenderWindow& window)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			float newX = shape.getPosition().x - speed * timeDelta;
			if (newX < 0)
				newX = 0;
			shape.setPosition(newX, shape.getPosition().y);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			float newX = shape.getPosition().x + speed * timeDelta;
			if (newX + shape.getSize().x > SCREEN_WIDTH)
				newX = SCREEN_WIDTH - shape.getSize().x;
			shape.setPosition(newX, shape.getPosition().y);
		}

		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::Vector2f worldPos = window.mapPixelToCoords(mousePosition);

		shape.setPosition(worldPos.x, shape.getPosition().y);

		float halfWidth = shape.getSize().x / 2.f;
		float currentX = shape.getPosition().x;

		if (currentX - halfWidth < 0)
		{
			shape.setPosition(halfWidth, shape.getPosition().y);
		}

		if (currentX + halfWidth > SCREEN_WIDTH)
		{
			shape.setPosition(SCREEN_WIDTH - halfWidth, shape.getPosition().y);
		}
	}
	void Platform::Draw(sf::RenderWindow& window)
	{
		window.draw(shape);
	}
}