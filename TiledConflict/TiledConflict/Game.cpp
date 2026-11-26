#include "Game.h"

Game::Game()
{
    // Add units to vector initially
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
        Render();
    }

    CloseWindow();
}

// If user is in the process of exiting, validate buttons to close window or keep it opem
void Game::ShouldWindowClose()
{
    if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) m_exitWindowRequested = true;

    if (m_exitWindowRequested)
    {
        if (IsKeyPressed(KEY_Y)) m_exitWindow = true;
        else if (IsKeyPressed(KEY_N)) m_exitWindowRequested = false;
    }
}

// Process all key bindings
void Game::ProcessKeys()
{
    // cursor movement
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

    // unit selection
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
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

    // Allows user to select a unit
    if (IsKeyPressed(KEY_BACKSPACE))
        m_selectedUnit = -1;
}

void Game::Render()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    // if user is trying to leave draw our exit confirmation text
    if (m_exitWindowRequested)
    {
        DrawExitPrompt();
    }
    // otherwise draw game
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

// Draws our cursor outline
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

// Draws the exit prompt if started by user
void Game::DrawExitPrompt()
{
    DrawRectangle(0, 100, m_screenWidth, 200, BLACK);
    DrawText("Are you sure you want to exit program? [Y/N]", 40, 180, 30, WHITE);
}

// Draw available movement positions if unit selected
void Game::DrawMovementRange()
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
                    {x * m_cellWidth, y * m_cellHeight,
                      m_cellWidth, m_cellHeight },
                    Fade(DARKBLUE, 0.5f)
                );
            }
        }
    }
}

// Draws all units in Vector if health > 0
void Game::DrawUnits()
{
    for (Unit& t_unit : m_units)
    {
        if (t_unit.GetHealth() > 0)
            t_unit.Draw();
    }
}

// Draw a text box so unit info is displayed
void Game::DrawUnitInfo()
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

// checks if a unit can move to a tile and if so returns true
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

// if unit is adjacent we can attack
bool Game::CanAttack(int t_x, int t_y)
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

// checks vector for a unit at specified grid position
int Game::FindUnitAt(int x, int y)
{
    for (int i = 0; i < m_units.size(); i++)
    {
        if (m_units[i].GetX() == x &&
            m_units[i].GetY() == y &&
            m_units[i].GetHealth() > 0)
        {
            return i;
        }
    }

    return -1;
}



