#ifndef UNIT_H
#define UNIT_H

#include "Globals.h"
#include "raylib.h"
#include <math.h>

/// <summary>
/// Unit class
/// </summary>
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
    // grid coordinates
    int m_x;
    int m_y;

    // Constraints so that the unit only takes up 60% of a grid space
    float m_unitWidth = m_cellWidth * 0.6f;
    float m_unitHeight = m_cellHeight * 0.6f;

    Rectangle m_bounds;
    Color m_colour;

    // Enum that establishes unit type
    UnitType m_unitType;
    // Enum that establishes unit team
    Team m_team;

    int m_health = 100;
    // How far can the unit move in the grid
    int m_movementRange;
    // damage value of a specific unit (changes on type)
    int m_attackDamage = 0;

};

#endif // UNIT_H