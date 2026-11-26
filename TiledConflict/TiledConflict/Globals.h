#ifndef GLOBALS_H
#define GLOBALS_H

// Screen and grid constraints
const int m_screenWidth = 800;
const int m_screenHeight = 450;
const int m_columns = 10;
const int m_rows = 8;

// Size of grid cells
inline float m_cellWidth = (float)m_screenWidth / m_columns; // inline allows variable to be defined in multiple source files without linker errors
inline float m_cellHeight = (float)m_screenHeight / m_rows;

// Tile enum class for different tile types
enum class TerrainType
{
	Grass,
	Forest,
	Mountain,
	Base
};

// Unit enum class for unit types
enum class UnitType
{
    Infantry,
    Tank
};

// Enum class to assign team to units
enum class Team
{
    Player,
    Enemy
};

#endif // !GLOBALS_H