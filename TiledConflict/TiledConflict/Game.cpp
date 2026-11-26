#include "Game.h"

Game::Game()
{
    m_units.emplace_back(1, 2, UnitType::Infantry, Team::Player);
    m_units.emplace_back(2, 3, UnitType::Tank, Team::Player);

    m_units.emplace_back(8, 5, UnitType::Infantry, Team::Enemy);
    m_units.emplace_back(7, 6, UnitType::Tank, Team::Enemy);
}

Game::~Game()
{
}

void Game::run()
{
	InitWindow(m_screenWidth, m_screenHeight, "TiledConflict");
	SetExitKey(KEY_NULL);

    SetTargetFPS(60);

    // Main game loop
    while (!m_exitWindow)
    {
        ShouldWindowClose();
        ProcessKeys();
        Update();
        Render();
    }

    CloseWindow();
}

void Game::ShouldWindowClose()
{
    if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) m_exitWindowRequested = true;

    if (m_exitWindowRequested)
    {
        if (IsKeyPressed(KEY_Y)) m_exitWindow = true;
        else if (IsKeyPressed(KEY_N)) m_exitWindowRequested = false;
    }
}

void Game::ProcessKeys()
{
    if (IsKeyPressed(KEY_D) && m_cursorX < m_columns - 1)
    {
        m_cursorX++;
    }

    if (IsKeyPressed(KEY_A) && m_cursorX > 0)
    {
        m_cursorX--;
    }

    if (IsKeyPressed(KEY_W) && m_cursorY > 0)
    {
        m_cursorY--;
    }

    if (IsKeyPressed(KEY_S) && m_cursorY < m_rows - 1)
    {
        m_cursorY++;
    }

    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
    {
        if (m_selectedUnit == -1)
        {
            // Select a unit
            int index = FindUnitAt(m_cursorX, m_cursorY);

            if (index != -1 && m_units[index].GetTeam() == Team::Player)
                m_selectedUnit = index;
        }
        else
        {
            if (CanMoveTo(m_cursorX, m_cursorY))
            {
                m_units[m_selectedUnit].SetPosition(m_cursorX, m_cursorY);
                m_selectedUnit = -1;
            }
            else if (CanAttack(m_cursorX, m_cursorY))
            {
                int t_target = FindUnitAt(m_cursorX, m_cursorY);
                int t_damage = m_units[m_selectedUnit].GetAttackDamage();
                m_units[t_target].TakeDamage(t_damage);
                m_selectedUnit = -1;
            }
        }
    }

    if (IsKeyPressed(KEY_BACKSPACE))
        m_selectedUnit = -1;
}

void Game::Update()
{
    
}

void Game::Render()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    if (m_exitWindowRequested)
    {
        DrawExitPrompt();
    }
    else
    {
        m_map.Draw();
        DrawMovementRange();
        DrawUnits();
        DrawCursor();
        DrawUnitInfo();
    }

    EndDrawing();
}

void Game::DrawCursor()
{
    Rectangle cursorBounds = {
        m_cursorX * m_cellWidth,
        m_cursorY * m_cellHeight,
        m_cellWidth,
        m_cellHeight
    };

    DrawRectangleLinesEx(cursorBounds, 3.0f, YELLOW);
}

void Game::DrawExitPrompt()
{
    DrawRectangle(0, 100, m_screenWidth, 200, BLACK);
    DrawText("Are you sure you want to exit program? [Y/N]", 40, 180, 30, WHITE);
}

void Game::DrawMovementRange()
{
    if (m_selectedUnit == -1)
        return;

    for (int y = 0; y < m_rows; y++)
    {
        for (int x = 0; x < m_columns; x++)
        {
            if (CanMoveTo(x, y))
            {
                DrawRectangleRec(
                    { x * m_cellWidth, y * m_cellHeight,
                      m_cellWidth, m_cellHeight },
                    Fade(DARKBLUE, 0.5f)
                );
            }
        }
    }
}

void Game::DrawUnits()
{
    for (Unit& unit : m_units)
    {
        if (unit.GetHealth() > 0)
            unit.Draw();
    }
}

void Game::DrawUnitInfo()
{
    int index = FindUnitAt(m_cursorX, m_cursorY);

    if (index == -1)
        return;

    Unit& unit = m_units[index];

    const char* unitName = "Unknown";

    switch (unit.GetUnitType())
    {
    case UnitType::Infantry:
        unitName = "Infantry";
        break;
    case UnitType::Tank:
        unitName = "Tank";
        break;
    default:
        unitName = "unassigned unit type";
        break;
    }

    DrawRectangle(620, 5, 175, 85, Fade(BLACK, 0.8f));

    DrawText(unitName, 630, 10, 20, WHITE);

    DrawText(
        unit.GetTeam() == Team::Player ? "Player" : "Enemy",
        630, 35, 16, WHITE
    );

    DrawText(
        TextFormat("Health: %d", unit.GetHealth()),
        630, 52, 14, WHITE
    );

    DrawText(
        TextFormat("Movement: %d", unit.GetMovementRange()),
        630, 70, 14, WHITE
    );

    if (CanAttack(m_cursorX, m_cursorY))
    {
        DrawText("Press Space/Enter to attack", m_cursorX, m_cursorY, 20, WHITE);
    }
}

bool Game::CanMoveTo(int t_x, int t_y)
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

    int t_terrainCost = t_tile->GetMovementCost(t_unit.GetUnitType());
    if (t_terrainCost == -1)
        return false;

    int t_distance = abs(t_unit.GetX() - t_x)
        + abs(t_unit.GetY() - t_y);

    int t_totalCost = t_distance + t_terrainCost - 1;

    return t_totalCost <= t_unit.GetMovementRange();
}

bool Game::CanAttack(int t_x, int t_y)
{
    if (m_selectedUnit == -1)
        return false;

    int t_target = FindUnitAt(t_x, t_y);

    if (t_target == -1)
        return false;

    Unit& t_attacker = m_units[m_selectedUnit];
    Unit& t_defender = m_units[t_target];

    if (t_attacker.GetTeam() == t_defender.GetTeam())
        return false;

    if (t_defender.GetHealth() <= 0)
        return false;

    int t_distance = abs(t_attacker.GetX() - t_x)
        + abs(t_attacker.GetY() - t_y);

    return t_distance == 1;
}

int Game::FindUnitAt(int x, int y)
{
    for (int i = 0; i < m_units.size(); i++)
    {
        if (m_units[i].GetX() == x &&
            m_units[i].GetY() == y)
        {
            return i;
        }
    }

    return -1;
}



