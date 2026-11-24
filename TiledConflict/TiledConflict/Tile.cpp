#include "Tile.h"

Tile::Tile(Rectangle t_bounds, TerrainType t_terrain)
{
	m_bounds = t_bounds;
	m_terrain = t_terrain;
}

Tile::~Tile()
{
}

void Tile::Draw()
{
	Color t_colour;
	switch (m_terrain)
	{
	case TerrainType::Grass:
		t_colour = GREEN;
		break;
	case TerrainType::Forest:
		t_colour = DARKGREEN;
		break;
	case TerrainType::Mountain:
		t_colour = BROWN;
		break;
	case TerrainType::Base:
		t_colour = BLUE;
		break;
	default:
		t_colour = WHITE;
		break;
	}
	DrawRectangleRec(m_bounds, t_colour);
}

TerrainType Tile::GetTerrain() const
{
	return m_terrain;
}

void Tile::SetTerrain(TerrainType t_terrain)
{
	m_terrain = t_terrain;
}

Rectangle Tile::GetBounds() const
{
	return m_bounds;
}
