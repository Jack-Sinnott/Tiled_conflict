#include "Battlefield.h"

Battlefield::Battlefield()
{
    // Add units to vector initially
    m_units.emplace_back(1, 2, UnitType::Infantry, Team::Player);
    m_units.emplace_back(2, 3, UnitType::Tank, Team::Player);

    m_units.emplace_back(8, 5, UnitType::Infantry, Team::Enemy);
    m_units.emplace_back(7, 6, UnitType::Tank, Team::Enemy);
}

void Battlefield::Update()
{
}

void Battlefield::Render()
{
    m_map.Draw();
    DrawMovementRange();
    DrawUnits();
    DrawCursor();
    DrawUnitInfo();
}

void Battlefield::MoveCursorLeft()
{
    if (m_cursorX > 0)
    {
        m_cursorX--;
    }
}

void Battlefield::MoveCursorRight()
{
    if (m_cursorX < m_columns - 1)
    {
        m_cursorX++;
    }
}

void Battlefield::MoveCursorUp()
{
    if (m_cursorY > 0)
    {
        m_cursorY--;
    }
}

void Battlefield::MoveCursorDown()
{
    if (m_cursorY < m_rows - 1)
    {
        m_cursorY++;
    }
}

void Battlefield::UnitSelection()
{
    if (m_selectedUnit == -1)
    {
        // Select a unit
        int t_index = FindUnitAt(m_cursorX, m_cursorY);

        // if unit selection was valid
        if (t_index != -1 && m_units[t_index].GetTeam() == Team::Player)
            m_selectedUnit = t_index;
    }
    // if a unit is selected
    else
    {
        // check if movement is valid
        if (CanMoveTo(m_cursorX, m_cursorY))
        {
            m_units[m_selectedUnit].SetPosition(m_cursorX, m_cursorY);
            m_selectedUnit = -1;
        }
        // check if an opposition unit is adjacent and is selected
        else if (CanAttack(m_cursorX, m_cursorY))
        {
            int t_target = FindUnitAt(m_cursorX, m_cursorY);
            int t_damage = m_units[m_selectedUnit].GetAttackDamage();
            m_units[t_target].TakeDamage(t_damage);
            m_selectedUnit = -1;
        }
    }
}

void Battlefield::ResetSelection()
{
    m_selectedUnit = -1;
}

void Battlefield::DrawMovementRange()
{
    if (m_selectedUnit == -1)
        return;

    // nested loop to draw movement outline in all grids and columns relevant to unit
    for (int y = 0; y < m_rows; y++)
    {
        for (int x = 0; x < m_columns; x++)
        {
            // if we can move there legally
            if (CanMoveTo(x, y))
            {
                // Draw the movement outline
                DrawRectangleRec(
                    { x * m_cellWidth, y * m_cellHeight,
                      m_cellWidth, m_cellHeight },
                    Fade(DARKBLUE, 0.5f)
                );
            }
        }
    }
}

void Battlefield::DrawUnits()
{
    for (Unit& t_unit : m_units)
    {
        if (t_unit.GetHealth() > 0)
            t_unit.Draw();
    }
}

void Battlefield::DrawUnitInfo()
{
    // check if a unit exists in vector at specified position
    int t_index = FindUnitAt(m_cursorX, m_cursorY);

    if (t_index == -1)
        return;

    Unit& t_unit = m_units[t_index];

    // raylib expects a C-style string
    const char* t_unitName = "Unknown";

    // Switch based on unit type
    switch (t_unit.GetUnitType())
    {
    case UnitType::Infantry:
        t_unitName = "Infantry";
        break;
    case UnitType::Tank:
        t_unitName = "Tank";
        break;
    default:
        t_unitName = "unassigned unit type";
        break;
    }

    DrawRectangle(620, 5, 175, 85, Fade(BLACK, 0.8f));

    DrawText(t_unitName, 630, 10, 20, WHITE);

    DrawText(
        t_unit.GetTeam() == Team::Player ? "Player" : "Enemy",
        630, 35, 16, WHITE
    );

    DrawText(
        TextFormat("Health: %d", t_unit.GetHealth()),
        630, 52, 14, WHITE
    );

    DrawText(
        TextFormat("Movement: %d", t_unit.GetMovementRange()),
        630, 70, 14, WHITE
    );

    if (CanAttack(m_cursorX, m_cursorY))
    {
        DrawText("Press Space/Enter to attack", 630, 88, 20, WHITE);
    }
}

void Battlefield::DrawCursor()
{
    Rectangle cursorBounds = {
        m_cursorX * m_cellWidth,
        m_cursorY * m_cellHeight,
        m_cellWidth,
        m_cellHeight
    };

    DrawRectangleLinesEx(cursorBounds, 3.0f, YELLOW);
}

// checks vector for a unit at specified index
int Battlefield::FindUnitAt(int t_x, int t_y)
{
    for (int i = 0; i < m_units.size(); i++)
    {
        if (m_units[i].GetX() == t_x &&
            m_units[i].GetY() == t_y &&
            m_units[i].GetHealth() > 0)
        {
            return i;
        }
    }

    return -1;
}

bool Battlefield::CanMoveTo(int t_x, int t_y)
{
    if (m_selectedUnit == -1)
        return false;

    // refernece objects for later
    Unit& t_unit = m_units[m_selectedUnit];
    Tile* t_tile = m_map.GetTile(t_x, t_y);

    if (t_tile == nullptr)
        return false;

    int t_valid = FindUnitAt(t_x, t_y);

    if (t_valid != -1)
        return false;

    // different units = different movement amounts
    int t_terrainCost = t_tile->GetMovementCost(t_unit.GetUnitType());
    if (t_terrainCost == -1)
        return false;

    // Manhattan distance between unit and destination
    int t_distance = abs(t_unit.GetX() - t_x)
        + abs(t_unit.GetY() - t_y);

    // trying to account for destination with actual terrain cost
    int t_totalCost = t_distance + t_terrainCost - 1;

    return t_totalCost <= t_unit.GetMovementRange();
}

bool Battlefield::CanAttack(int t_x, int t_y)
{
    if (m_selectedUnit == -1)
        return false;

    int t_target = FindUnitAt(t_x, t_y);

    if (t_target == -1)
        return false;

    // reference for later
    Unit& t_attacker = m_units[m_selectedUnit];
    Unit& t_defender = m_units[t_target];

    if (t_attacker.GetTeam() == t_defender.GetTeam())
        return false;

    if (t_defender.GetHealth() <= 0)
        return false;

    // Manhattan distance between attacker and target
    int t_distance = abs(t_attacker.GetX() - t_x)
        + abs(t_attacker.GetY() - t_y);

    return t_distance == 1; // only allow if adjacent
}
