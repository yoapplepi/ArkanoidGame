#include "GameStatePlaying.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>

namespace ArkanoidGame
{
	void GameStatePlayingData::Init()
	{
		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));

		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color::Black);


		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::Yellow);

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(24);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Use arrow keys to move, ESC to pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

	}

	void GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PushState(GameStateType::ExitDialog, false);
			}
		}
	}

	void GameStatePlayingData::Update (float timeDelta)
	{
		platform.Update(timeDelta);

		ball.Update(timeDelta);

		if (ball.GetBounds().intersects(platform.GetBounds()))
		{
			ball.CollisionWithPlatform();
		}

		if (ball.GetBounds().top > SCREEN_HEIGHT)
		{
			Application::Instance().GetGame().PushState(GameStateType::GameOver, false);
		}
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		window.draw(background);

		platform.Draw(window);
		ball.Draw(window);

		window.draw(scoreText);
		window.draw(inputHintText);
	}
}