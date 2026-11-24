#ifndef MAP_H
#define MAP_H

#include "Globals.h"
#include "Tile.h"
#include <vector>

class Map
{
public:
	Map();
	~Map();
	void Init();
	// Draw actual Tiles on grid
	void Draw();
	Tile* GetTile(int t_x, int t_y);

private:
	void SetTileTerrain(int t_x, int t_y, TerrainType t_terrain);
	// draw the grid so we know visually if tiles are being drawn correctly
	void DrawMapGrid();
	std::vector<Tile> m_tiles;
};

#endif // !MAP_H