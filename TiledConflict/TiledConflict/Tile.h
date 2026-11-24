#ifndef TILE_H
#define TILE_H

#include "raylib.h"

enum class TerrainType
{
	Grass,
	Forest,
	Mountain,
	Base
};

class Tile
{
public:
	Tile(Rectangle t_bounds, TerrainType t_terrain);
	~Tile();

	void Draw();
	TerrainType GetTerrain() const;
	Rectangle GetBounds() const;
	void SetTerrain(TerrainType t_terrain);

private:

	Rectangle m_bounds;
	TerrainType m_terrain;

};

#endif // !TILE_H