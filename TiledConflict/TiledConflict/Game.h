#ifndef GAME_HPP
#define GAME_HPP

#include "raylib.h"
#include "Globals.h"
#include "Battlefield.h"

class Game
{
public:

	Game();

	void run();

private:
	Battlefield m_battlefield;

	bool m_exitWindowRequested = false;
	bool m_exitWindow = false;

	void ShouldWindowClose(); // Check if user is sure they want to close window
	void ProcessKeys();
	void Render();	
	void DrawExitPrompt();

};

#endif // !GAME_HPP