#ifndef GAME_HPP
#define GAME_HPP

#include "raylib.h"
#include "Globals.h"
#include "Map.h"
#include "Unit.h"

class Game
{
public:

	Game();
	~Game();

	void run();

private:

	void ShouldWindowClose();
	void ProcessKeys();
	void Update();
	void Render();
	void DrawCursor();
	void DrawExitPrompt();
	void DrawMovementRange();
	void DrawUnits();
	void DrawUnitInfo();
	int FindUnitAt(int t_x, int t_y);

	// Represents position of user selection on grid
	int m_cursorX = 0;
	int m_cursorY = 0;

	Map m_map;

	std::vector<Unit> m_units;
	int m_selectedUnit = -1;

	bool m_exitWindowRequested = false;
	bool m_exitWindow = false;
};

#endif // !GAME_HPP