#ifndef GLOBALS_H
#define GLOBALS_H

const int m_screenWidth = 800;
const int m_screenHeight = 450;
const int m_columns = 10;
const int m_rows = 8;

inline float m_cellWidth = (float)m_screenWidth / m_columns;
inline float m_cellHeight = (float)m_screenHeight / m_rows;

enum class TerrainType
{
	Grass,
	Forest,
	Mountain,
	Base
};

enum class UnitType
{
    Infantry,
    Tank
};

enum class Team
{
    Player,
    Enemy
};

#endif // !GLOBALS_H