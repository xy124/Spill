//#include "Game.hpp"
#include "Logfile.hpp"
#include "Highscorelist.hpp"
#include "Framework.hpp"
#include "Settings.hpp"
#include "Spritepool.hpp"

#include "Menu/MenuSystem.hpp"

#define HIGHSCOREFILE "highscore.hsc"

#include <SDL.h>


int main (int argc, char *argv[]) {
	CLogfile::get()->CreateLogfile("Logfile.html");

	CHighscorelist::get()->LoadFromFile(HIGHSCOREFILE);
	//TODO: show menu

	if (g_pFramework->Init(800, 635, 24, false) == false)//635 for itembar!
		return (0); //Fehler werden schon in Framework selbst abgehandelt!
	SDL_WM_SetCaption("Spill", "Spill");

	g_pSpritepool;//init Spritepool, load Sprites!

	g_pSettings->LoadFromFile("Settings.s");



	g_pMenuSystem->init();
	g_pMenuSystem->run();
	g_pMenuSystem->quit();




	//TODO: Start game selected in Menu!
	//HINT: game in stack... thats a good way???

	g_pSettings->SaveToFile("Settings.s");

	g_pPhysics->del();

	g_pSpritepool->del();

	g_pFramework->Quit();
	g_pFramework->del();

	CHighscorelist::get()->SaveToFile(HIGHSCOREFILE);
	CHighscorelist::del();
	CLogfile::del();
	return 0;
}
