#include "GameStatePlaying.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include "Ball.h"
#include "Block.h"
#include <assert.h>
#include <sstream>

namespace ArkanoidGame
{
	void GameStatePlayingData::Init()
	{
		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		assert(gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + "Death.wav"));

		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(0, 0, 0));

		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::Yellow);

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(24);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Use arrow keys to move, ESC to pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

		gameObjects.emplace_back(std::make_shared<Platform>(sf::Vector2f({ SCREEN_WIDTH / 2.0, SCREEN_HEIGHT - PLATFORM_HEIGHT / 2.f })));
		gameObjects.emplace_back(std::make_shared<Ball>(sf::Vector2f({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - PLATFORM_HEIGHT - BALL_SIZE / 2.f })));
		
		createBlocks();

		gameOverSound.setBuffer(gameOverSoundBuffer);
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

	void GameStatePlayingData::Update(float timeDelta)
	{
		static auto updateFunctor = [timeDelta](auto object)
			{
				object->Update(timeDelta);
			};

		std::for_each(gameObjects.begin(), gameObjects.end(), updateFunctor);
		std::for_each(block.begin(), block.end(), updateFunctor);

		std::shared_ptr <Platform> platform = std::dynamic_pointer_cast<Platform>(gameObjects[0]);
		std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(gameObjects[1]);

		auto isCollision = platform->CheckCollision(ball);

		if (isCollision) 
			ball->InvertDirectionY(); 

		bool invertDirectionX = false;
		bool invertDirectionY = false;

		bool hasBrokeOneBlock = false;
		block.erase(
			std::remove_if(block.begin(), block.end(),
				[ball, &hasBrokeOneBlock, &invertDirectionX, &invertDirectionY, this](auto block)
				{
					if ((!hasBrokeOneBlock) && block->CheckCollision(ball)) {
						hasBrokeOneBlock = true;
						const auto ballPos = ball->GetPosition();
						const auto blockRect = block->GetRect();

						GetBallInverse(ballPos, blockRect, invertDirectionX, invertDirectionY);
					}
					return block->IsBroken();
				}),
			block.end()
		);

		if (invertDirectionX)
			ball->InvertDirectionX();
		
		if (invertDirectionY)
			ball->InvertDirectionY();
		

		const bool isGameWin = block.size() == 0;
		const bool isGameOver = !isCollision && ball->GetPosition().y > platform->GetRect().top;
		Game& game = Application::Instance().GetGame();

		if (isGameWin) 
			game.PushState(GameStateType::GameWin, false);
		
		else if (isGameOver) 
		{
			gameOverSound.play();
			game.PushState(GameStateType::GameOver, false);
		}
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		window.draw(background);
		static auto drawFunc = [&window](auto block)
			{
				block->Draw(window);
			};

		std::for_each(gameObjects.begin(), gameObjects.end(), drawFunc);
		std::for_each(block.begin(), block.end(), drawFunc);

		scoreText.setString("Score: " + std::to_string(gameObjects.size() - 2));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);
		inputHintText.setPosition(SCREEN_WIDTH - 10.f, 10.f);
		window.draw(inputHintText);
	}

	void GameStatePlayingData::GetBallInverse(const sf::Vector2f& ballPos, const sf::FloatRect& blockRect, bool& needInverseDirecX, bool& needInverseDirecY)
	{
		if (ballPos.y > blockRect.top + blockRect.height)
			needInverseDirecY = true;
		
		if (ballPos.x < blockRect.left)
			needInverseDirecX = true;
		
		if (ballPos.x > blockRect.left + blockRect.width)
			needInverseDirecX = true;
	}

	void GameStatePlayingData::createBlocks()
	{

	}
}

	