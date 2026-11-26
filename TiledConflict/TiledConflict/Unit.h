#ifndef UNIT_H
#define UNIT_H

#include "Globals.h"
#include "raylib.h"
#include <math.h>

class Unit
{
public:
    Unit(int t_x, int t_y, UnitType t_unitType, Team t_team);
    ~Unit();

    void Draw();
    void SetPosition(int t_x, int t_y);
    void TakeDamage(int t_damage);
    int GetX() const;
    int GetY() const;
    int GetMovementRange() const;
    int GetHealth() const;
    int GetAttackDamage() const;
    Team GetTeam() const;
    UnitType GetUnitType() const;
    
    

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
    int m_attackDamage = 0;

};

#endif // UNIT_H