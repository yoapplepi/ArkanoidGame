#pragma once
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{

	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		ExitDialog,
		Records,
	};

	class GameState
	{
	public:
		GameState() = default;
		GameState(GameStateType type, bool isExclusivelyVisible);

		~GameState();

		GameState(const GameState& other);
		GameState& operator = (const GameState& other);

		GameState(GameState&& other) noexcept;
		GameState& operator = (GameState&& other) noexcept;

		GameStateType GetType() const { return type; }
		bool IsExclusivelyVisible() const { return isExclusivelyVisible; }

		template<class T>
		T* GetData() const {
			return static_cast<T*>(data);
		}

		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);
		void HandleWindowEvent(sf::Event& event);

	private:
		void CleanUp();
		void* CopyData(const GameState& state) const;

	private:
		GameStateType type = GameStateType::None;
		void* data = nullptr;
		bool isExclusivelyVisible = false;
	};
}