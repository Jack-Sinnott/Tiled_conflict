#include "Tile.h"

Tile::Tile(Rectangle t_bounds, TerrainType t_terrain)
{
	m_bounds = t_bounds;
	m_terrain = t_terrain;
	m_colour = WHITE;
}

void Tile::Draw()
{
	// For each Terrain Type we assign different colours
	switch (m_terrain)
	{
	case TerrainType::Grass:
		m_colour = GREEN;
		break;
	case TerrainType::Forest:
		m_colour = DARKGREEN;
		break;
	case TerrainType::Mountain:
		m_colour = BROWN;
		break;
	case TerrainType::Base:
		m_colour = LIGHTGRAY;
		break;
	default:
		m_colour = WHITE;
		break;
	}
	DrawRectangleRec(m_bounds, m_colour);
}

void Tile::SetTerrain(TerrainType t_terrain)
{
	m_terrain = t_terrain;
}

TerrainType Tile::GetTerrain() const
{
	return m_terrain;
}

Rectangle Tile::GetBounds() const
{
	return m_bounds;
}

int Tile::GetMovementCost(UnitType unitType) const
{
	// For each terrain type we assign a different MovementCost value
	switch(m_terrain)
	{
	case TerrainType::Grass:
	case TerrainType::Base:
		return 1;
	case TerrainType::Forest:
		return unitType == UnitType::Infantry ? 1 : 2;
	case TerrainType::Mountain:
		return unitType == UnitType::Infantry ? 2 : -1;
	}

	return -1; // impassable terrain is represented as -1
}
