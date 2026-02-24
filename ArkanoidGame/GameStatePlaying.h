#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Platform.h"
#include "Ball.h"
#include "GameStateData.h"


namespace ArkanoidGame
{
	class Game;
	class Block;

	class GameStatePlayingData:public GameStateData
	{
	public:
		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;

	private:
		void createBlock();
		void GetBallInverse(const sf::Vector2f& ballPos, const sf::FloatRect& blockRect, 
			bool& needInverseDirX, bool& needInverseDirY);
		
		sf::Texture appleTexture;
		sf::Texture rockTexture;
		sf::Font font;
		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;

		std::vector<std::shared_ptr<GameObject>> gameObjects;

		sf::Text scoreText;
		sf::Text inputHintText;
		sf::RectangleShape background;
		std::vector<std::shared_ptr<Block>> blocks;

		sf::Sound gameOverSound;
		
		
	};

}
