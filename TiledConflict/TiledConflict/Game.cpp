#include "Game.h"

Game::Game()
{
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
        DrawRectangle(0, 100, m_screenWidth, 200, BLACK);
        DrawText("Are you sure you want to exit program? [Y/N]", 40, 180, 30, WHITE);
    }
    else
    {
    }

    EndDrawing();
}


