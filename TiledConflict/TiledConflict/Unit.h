#ifndef UNIT_H
#define UNIT_H

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
    Unit(int t_posX, int t_posY, UnitType t_unitType, Team t_team);
    ~Unit();

    void Draw();
    int GetX();
    int GetY();
    Team GetTeam();
    UnitType GetUnitType();
    int GetMovementRange();
    void SetPosition(int t_x, int t_y);

private:
    int m_x;
    int m_y;

    UnitType m_unitType;
    Team m_team;

    int m_health = 100;
    int m_movementRange;

    bool m_hasMoved = false;
    bool m_hasAttacked = false;

};

#endif // UNIT_H