#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Platform.h"
#include "Ball.h"


namespace ArkanoidGame
{
	class Game;

	class GameStatePlayingData
	{
	public:
		void Init();
		void HandleWindowEvent(const sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);

	private:
		
		Platform platform;
		Ball ball;


		sf::Font font;
		sf::Text scoreText;
		sf::RectangleShape background;

		// UI data
		sf::Text inputHintText;
		sf::Sound gameOverSound;
	};

}
