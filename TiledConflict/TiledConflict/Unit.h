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
    Unit();
    ~Unit();

private:
    int m_x;
    int m_y;

    UnitType m_type;
    Team m_team;

    int m_health;
    int m_movementRange;

    bool m_hasMoved;
    bool m_hasAttacked;

};

#endif // UNIT_H