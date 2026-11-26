#include "Game.h"

Game::Game()
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
    if (IsKeyPressed(KEY_D))
    {
        m_battlefield.MoveCursorRight();
    }

    if (IsKeyPressed(KEY_A))
    {
        m_battlefield.MoveCursorLeft();
    }

    if (IsKeyPressed(KEY_W))
    {
        m_battlefield.MoveCursorUp();
    }

    if (IsKeyPressed(KEY_S))
    {
        m_battlefield.MoveCursorDown();
    }

    // unit selection
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
    {
        m_battlefield.UnitSelection();
    }

    // Allows user to select a unit
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        m_battlefield.ResetSelection();
    }
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
        m_battlefield.Render();
    }

    EndDrawing();
}

// Draws the exit prompt if started by user
void Game::DrawExitPrompt()
{
    DrawRectangle(0, 100, m_screenWidth, 200, BLACK);
    DrawText("Are you sure you want to exit program? [Y/N]", 40, 180, 30, WHITE);
}
