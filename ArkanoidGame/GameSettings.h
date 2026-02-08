#pragma once
#include <string>

namespace ArkanoidGame 
{
	// Resources path
	const std::string RESOURCES_PATH = "Resources/";
	const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
	const std::string FONTS_PATH = RESOURCES_PATH + "Fonts/";
	const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";

	const float ACCELERATION = 10.f;
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEIGHT = 600;
	const float TIME_PER_FRAME = 1.f / 60.f; 
	const int MAX_APPLES = 10;

	const unsigned int BALL_SIZE = 20;
	const unsigned int BALL_SPEED = 400;

	const unsigned int PLATFORM_WIDTH = 60;
	const unsigned int PLATFORM_HEIGHT = 20;
	const float PLATFORM_SPEED = 300.f;

	const int MAX_RECORDS_TABLE_SIZE = 5;
	extern const char* PLAYER_NAME;

	const std::string GAME_NAME = "ArkanoidGame";
}
