#ifndef TILE_H
#define TILE_H

#include "raylib.h"
#include "Globals.h"

/// <summary>
/// Class for individual tiles we use to make map.
/// A tile can be one of four types: Grass, Forest, Mountain or Base
/// </summary>
class Tile
{
public:
	Tile(Rectangle t_bounds, TerrainType t_terrain);
	~Tile();

	void Draw();
	// Applies a terrain type from enum class TerrainType to the tile
	void SetTerrain(TerrainType t_terrain);
	TerrainType GetTerrain() const;
	Rectangle GetBounds() const;
	// Returns the tiles movement cost
	int GetMovementCost(UnitType unitType) const;

private:

	Rectangle m_bounds;
	Color m_colour;
	TerrainType m_terrain;

};

#endif // !TILE_H