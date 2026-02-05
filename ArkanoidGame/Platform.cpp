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

	void Platform::Update(float timeDelta)
	{
		float speed = 500.f; 
		sf::Vector2f currentPos = shape.getPosition();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			currentPos.x -= speed * timeDelta;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			currentPos.x += speed * timeDelta;
		}

		// ќграничиваем, чтобы не улетала за экран
		// (width Ч это ширина твоей платформы, проверь еЄ им€ в классе)
		float platformWidth = shape.getSize().x;
		if (currentPos.x < 0) currentPos.x = 0;
		if (currentPos.x > SCREEN_WIDTH - platformWidth) currentPos.x = SCREEN_WIDTH - platformWidth;

		// ”станавливаем обновленную позицию обратно
		shape.setPosition(currentPos);
	}
	void Platform::Draw(sf::RenderWindow& window)
	{
		window.draw(shape);
	}
}