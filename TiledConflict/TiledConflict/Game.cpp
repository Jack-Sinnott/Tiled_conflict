#include "Game.h"

Game::Game()
{
    m_units.emplace_back(1, 2, UnitType::Infantry, Team::Player);
    m_units.emplace_back(2, 3, UnitType::Tank, Team::Player);
    m_units.emplace_back(2, 2, UnitType::Artillery, Team::Player);

    m_units.emplace_back(8, 5, UnitType::Infantry, Team::Enemy);
    m_units.emplace_back(7, 6, UnitType::Artillery, Team::Enemy);
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
            // Attempt to move the selected unit
            if (FindUnitAt(m_cursorX, m_cursorY) == -1)
            {
                if (m_units[m_selectedUnit].MoveTo(m_cursorX, m_cursorY))
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
            if (m_units[m_selectedUnit].CanReach(x, y))
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

    case UnitType::Artillery:
        unitName = "Artillery";
        break;
    }

    DrawRectangle(620, 5, 175, 65, Fade(BLACK, 0.8f));

    DrawText(unitName, 630, 10, 20, WHITE);

    DrawText(
        unit.GetTeam() == Team::Player ? "Player" : "Enemy",
        630, 35, 16, WHITE
    );

    DrawText(
        TextFormat("Movement: %d", unit.GetMovementRange()),
        630, 52, 14, WHITE
    );
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


