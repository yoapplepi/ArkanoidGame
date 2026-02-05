#include "GameState.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStatePauseMenu.h"
#include "GameStateMainMenu.h"
#include "GameStateRecords.h"

#include <assert.h>
#include <utility> // Для std::move

namespace ArkanoidGame
{
	GameState::GameState(GameStateType type, bool isExclusivelyVisible)
		: type(type)
		, isExclusivelyVisible(isExclusivelyVisible)
	{
		switch (type)
		{
		case GameStateType::MainMenu:
		{
			data = new GameStateMainMenuData();
			((GameStateMainMenuData*)data)->Init();
			break;
		}
		case GameStateType::Playing:
		{
			data = new GameStatePlayingData();
			((GameStatePlayingData*)data)->Init();
			break;
		}
		case GameStateType::GameOver:
		{
			data = new GameStateGameOverData();
			((GameStateGameOverData*)data)->Init();
			break;
		}
		case GameStateType::ExitDialog:
		{
			data = new GameStatePauseMenuData();
			((GameStatePauseMenuData*)data)->Init();
			break;
		}
		case GameStateType::Records:
		{
			data = new GameStateRecordsData();
			((GameStateRecordsData*)data)->Init();
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void GameState::CleanUp()
	{
		if (data)
		{
			switch (type)
			{
			case GameStateType::MainMenu:
				delete ((GameStateMainMenuData*)data);
				break;
			case GameStateType::Playing:
				delete ((GameStatePlayingData*)data);
				break;
			case GameStateType::GameOver:
				delete ((GameStateGameOverData*)data);
				break;
			case GameStateType::ExitDialog:
				delete ((GameStatePauseMenuData*)data);
				break;
			case GameStateType::Records:
				delete ((GameStateRecordsData*)data);
				break;
			default:
				assert(false);
				break;
			}
			data = nullptr;
		}
	}

	GameState::~GameState()
	{
		CleanUp();
	}

	GameState::GameState(const GameState& other)
		: type(other.type)
		, isExclusivelyVisible(other.isExclusivelyVisible)
	{
		data = CopyData(other);
	}

	// 4. Оператор присваивания (копирующий)
	GameState& GameState::operator=(const GameState& other)
	{
		if (this != &other)
		{
			CleanUp(); 
			type = other.type;
			isExclusivelyVisible = other.isExclusivelyVisible;
			data = CopyData(other);
		}
		return *this;
	}

	// 5. Конструктор перемещения
	GameState::GameState(GameState&& other) noexcept
	{
		// Просто используем оператор перемещения ниже
		*this = std::move(other);
	}

	// 6. Оператор перемещения
	GameState& GameState::operator=(GameState&& other) noexcept
	{
		if (this != &other)
		{
			CleanUp(); 

			type = other.type;
			isExclusivelyVisible = other.isExclusivelyVisible;
			data = other.data;

			other.data = nullptr;
			other.type = GameStateType::None;
		}
		return *this;
	}

	void GameState::Update(float timeDelta)
	{
		if (!data) return;

		switch (type)
		{
		case GameStateType::MainMenu:  ((GameStateMainMenuData*)data)->Update(timeDelta); break;
		case GameStateType::Playing:   ((GameStatePlayingData*)data)->Update(timeDelta); break;
		case GameStateType::GameOver:  ((GameStateGameOverData*)data)->Update(timeDelta); break;
		case GameStateType::ExitDialog:((GameStatePauseMenuData*)data)->Update(timeDelta); break;
		case GameStateType::Records:   ((GameStateRecordsData*)data)->Update(timeDelta); break;
		default: assert(false); break;
		}
	}

	void GameState::Draw(sf::RenderWindow& window)
	{
		if (!data) return;

		switch (type)
		{
		case GameStateType::MainMenu:  ((GameStateMainMenuData*)data)->Draw(window); break;
		case GameStateType::Playing:   ((GameStatePlayingData*)data)->Draw(window); break;
		case GameStateType::GameOver:  ((GameStateGameOverData*)data)->Draw(window); break;
		case GameStateType::ExitDialog:((GameStatePauseMenuData*)data)->Draw(window); break;
		case GameStateType::Records:   ((GameStateRecordsData*)data)->Draw(window); break;
		default: assert(false); break;
		}
	}

	void GameState::HandleWindowEvent(sf::Event& event)
	{
		if (!data) return;

		switch (type)
		{
		case GameStateType::MainMenu:  ((GameStateMainMenuData*)data)->HandleWindowEvent(event); break;
		case GameStateType::Playing:   ((GameStatePlayingData*)data)->HandleWindowEvent(event); break;
		case GameStateType::GameOver:  ((GameStateGameOverData*)data)->HandleWindowEvent(event); break;
		case GameStateType::ExitDialog:((GameStatePauseMenuData*)data)->HandleWindowEvent(event); break;
		case GameStateType::Records:   ((GameStateRecordsData*)data)->HandleWindowEvent(event); break;
		default: assert(false); break;
		}
	}

	void* GameState::CopyData(const GameState& state) const
	{
		if (!state.data) return nullptr;

		void* newData = nullptr;
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			newData = new GameStateMainMenuData();
			*((GameStateMainMenuData*)newData) = *(GameStateMainMenuData*)state.data;
			break;
		}
		case GameStateType::Playing:
		{
			newData = new GameStatePlayingData();
			*((GameStatePlayingData*)newData) = *(GameStatePlayingData*)state.data;
			break;
		}
		case GameStateType::GameOver:
		{
			newData = new GameStateGameOverData();
			*((GameStateGameOverData*)newData) = *(GameStateGameOverData*)state.data;
			break;
		}
		case GameStateType::ExitDialog:
		{
			newData = new GameStatePauseMenuData();
			*((GameStatePauseMenuData*)newData) = *(GameStatePauseMenuData*)state.data;
			break;
		}
		case GameStateType::Records:
		{
			newData = new GameStateRecordsData();
			*((GameStateRecordsData*)newData) = *(GameStateRecordsData*)state.data;
			break;
		}
		default:
			assert(false);
			break;
		}
		return newData;
	}
}