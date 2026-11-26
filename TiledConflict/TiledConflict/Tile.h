#ifndef TILE_H
#define TILE_H

#include "raylib.h"
#include "Globals.h"

class Tile
{
public:
	Tile(Rectangle t_bounds, TerrainType t_terrain);
	~Tile();

	void Draw();
	TerrainType GetTerrain() const;
	Rectangle GetBounds() const;
	int GetMovementCost(UnitType unitType) const;
	void SetTerrain(TerrainType t_terrain);

private:

	Rectangle m_bounds;
	Color m_colour;
	TerrainType m_terrain;

};

#endif // !TILE_H