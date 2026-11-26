#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "Map.h"
#include "Unit.h"

class Battlefield
{
public:
	Battlefield();

	void Update();
	void Render();
	void MoveCursorLeft();
	void MoveCursorRight();
	void MoveCursorUp();
	void MoveCursorDown();
	void UnitSelection();
	void ResetSelection();

private:
	int m_selectedUnit = -1; // Store vector index of selected unit. Default to -1 as no unit selected
	int m_cursorX = 0; // Represents x position of user selection on grid
	int m_cursorY = 0; // Represents y position of user selection on grid
	
	Map m_map;
	std::vector<Unit> m_units; // Stores all player and enemy units in game
	
	
	void DrawMovementRange();
	void DrawUnits();
	void DrawUnitInfo();
	void DrawCursor(); // Draw our selection cursor
	
	int FindUnitAt(int t_x, int t_y); // Checks if a unit is at location
	
	bool CanMoveTo(int t_x, int t_y); // Validates movement based on distance, destination terrain and tile occupancy.
	bool CanAttack(int t_x, int  t_y); // Checks if there is a enemy adjacent so we can attack

};

#endif // !BATTLEFIELD_H
