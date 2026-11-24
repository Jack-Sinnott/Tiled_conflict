#ifndef GAME_HPP
#define GAME_HPP

#include "raylib.h"
#include "Globals.h"

class Game
{
public:

	Game();
	~Game();

	void run();

private:

	void ShouldWindowClose();
	void ProcessKeys();
	void Update();
	void Render();
	void DrawCursor();

	// Represents position of user selection on grid
	int m_cursorX = 0;
	int m_cursorY = 0;

	bool m_exitWindowRequested = false;
	bool m_exitWindow = false;
};

#endif // !GAME_HPP