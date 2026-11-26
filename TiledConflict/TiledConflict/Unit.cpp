#include "Unit.h"

Unit::Unit(int t_x, int t_y, UnitType t_unitType, Team t_team)
{
	m_x = t_x;
	m_y = t_y;
	m_unitType = t_unitType;
	m_team = t_team;

	// assigns variables to specific unit types
	switch (m_unitType)
	{
	case UnitType::Infantry:
		m_movementRange = 3;
		m_attackDamage = 25;
		break;
	case UnitType::Tank:
		m_movementRange = 5;
		m_attackDamage = 50;
		break;
	default:
		m_movementRange = 0;
		break;
	}

	// assigns unit to a team colour
	switch (m_team)
	{
	case Team::Player:
		m_colour = BLUE;
		break;
	case Team::Enemy:
		m_colour = RED;
		break;
	default:
		m_colour = WHITE;
		break;
	}

	// finalise the rectangle bounds by converting grid coordinates to screen coordinates and centralising the rectangle
	m_bounds = {
	m_x * m_cellWidth + (m_cellWidth - m_unitWidth) / 2,
	m_y * m_cellHeight + (m_cellHeight - m_unitHeight) / 2,
	m_unitWidth,
	m_unitHeight
	};
}

Unit::~Unit()
{
}

void Unit::Draw()
{
	DrawRectangleRec(m_bounds, m_colour);
}

int Unit::GetX() const
{
	return m_x;
}

int Unit::GetY() const
{
	return m_y;
}

Team Unit::GetTeam() const
{
	return m_team;
}

UnitType Unit::GetUnitType() const
{
	return m_unitType;
}

int Unit::GetMovementRange() const
{
	return m_movementRange;
}

int Unit::GetHealth() const
{
	return m_health;
}

int Unit::GetAttackDamage() const
{
	return m_attackDamage;
}

// Sets unit position in grid
void Unit::SetPosition(int t_x, int t_y)
{
	m_x = t_x;
	m_y = t_y;

	m_bounds.x = m_x * m_cellWidth +
		(m_cellWidth - m_unitWidth) / 2;

	m_bounds.y = m_y * m_cellHeight +
		(m_cellHeight - m_unitHeight) / 2;
}

// Removes health until it reaches 0
void Unit::TakeDamage(int t_damage)
{
	m_health -= t_damage;
	if (m_health < 0)
		m_health = 0;
}
