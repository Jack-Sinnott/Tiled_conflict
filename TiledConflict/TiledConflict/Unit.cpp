#include "Unit.h"

Unit::Unit(int t_X, int t_Y, UnitType t_unitType, Team t_team)
{
	m_x = t_X;
	m_y = t_Y;
	m_unitType = t_unitType;
	m_team = t_team;

	switch (m_unitType)
	{
	case UnitType::Infantry:
		m_movementRange = 3;
		break;
	case UnitType::Tank:
		m_movementRange = 5;
		break;
	case UnitType::Artillery:
		m_movementRange = 4;
		break;
	default:
		m_movementRange = 0;
		break;
	}
}

Unit::~Unit()
{
}

void Unit::Draw()
{
}

int Unit::GetX()
{
	return 0;
}

int Unit::GetY()
{
	return 0;
}

Team Unit::GetTeam()
{
	return Team();
}

UnitType Unit::GetUnitType()
{
	return UnitType();
}

int Unit::GetMovementRange()
{
	return 0;
}

void Unit::SetPosition(int t_x, int t_y)
{
}
