#pragma once

enum GameState
{
	// list of all game states 
	GS_LEVEL1 = 0,
	GS_LEVEL2,
	GS_LEVEL3, 
	GS_LEVEL4,

	// special game state. Do not change
	GS_RESTART,
	GS_QUIT,
	GS_NONE,
	GS_MAINMENU,
	GS_CUTSCENES1,
	GS_CUTSCENES2
};