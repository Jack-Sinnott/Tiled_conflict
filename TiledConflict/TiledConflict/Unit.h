#ifndef UNIT_H
#define UNIT_H

#include "Globals.h"
#include "raylib.h"
#include <math.h>

enum class UnitType
{
    Infantry,
    Tank,
    Artillery
};

enum class Team
{
    Player,
    Enemy
};

class Unit
{
public:
    Unit(int t_x, int t_y, UnitType t_unitType, Team t_team);
    ~Unit();

    void Draw();
    int GetX() const;
    int GetY() const;
    Team GetTeam() const;
    UnitType GetUnitType() const;
    int GetMovementRange() const;
    void SetPosition(int t_x, int t_y);
    bool CanReach(int t_x, int t_y) const;
    bool MoveTo(int t_x, int t_y);

private:
    int m_x;
    int m_y;

    float m_unitWidth = m_cellWidth * 0.6f;
    float m_unitHeight = m_cellHeight * 0.6f;

    Rectangle m_bounds;
    Color m_colour;

    UnitType m_unitType;
    Team m_team;

    int m_health = 100;
    int m_movementRange;

    bool m_hasMoved = false;
    bool m_hasAttacked = false;

};

#endif // UNIT_H