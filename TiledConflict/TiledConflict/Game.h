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
	// Check if user is sure they want to close window
	void ShouldWindowClose();
	void ProcessKeys();
	void Render();
	// Draw our selection cursor
	void DrawCursor();
	void DrawExitPrompt();
	void DrawMovementRange();
	void DrawUnits();
	void DrawUnitInfo();
	// Validates movement based on distance, destination terrain and tile occupancy.
	bool CanMoveTo(int t_x, int t_y);
	// Checks if there is a enemy adjacent so we can attack
	bool CanAttack(int t_x, int  t_y);
	// Checks if a unit is at location
	int FindUnitAt(int t_x, int t_y);
	

	// Represents position of user selection on grid
	int m_cursorX = 0;
	int m_cursorY = 0;

	Map m_map;

	// Stores all player and enemy units in game
	std::vector<Unit> m_units;
	// Store vector index of selected unit. Default to -1 as no unit selected
	int m_selectedUnit = -1;

	bool m_exitWindowRequested = false;
	bool m_exitWindow = false;
};

#endif // !GAME_HPP