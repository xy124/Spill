#include "Game.hpp"
#include "Logfile.hpp"
#include "Highscorelist.hpp"
#include "Framework.hpp"

#define HIGHSCOREFILE "highscore.hsc"


int main (int argc, char *argv[]) {
	CLogfile::get()->CreateLogfile("Logfile.html");
	CHighscorelist::get()->LoadFromFile(HIGHSCOREFILE);
	//TODO: show menu

	if (g_pFramework->Init(800, 600, 16, true) == false)
		return (0); //Fehler werden schon in Framework selbst abgehandelt!

	//TODO: Start game selected in Menu!
	CGame game(1,40,30); //wir erstelllen das spiel im stack, im buch macht ers auch so (im heap w�re per new)
	//^^ergibt nur 1 bildschirmvoll, da 40*BlockSize=800 und co...

	game.run();

	game.quit();

	g_pFramework->Quit();
	g_pFramework->del();

	CHighscorelist::get()->SaveToFile(HIGHSCOREFILE);
	CHighscorelist::del();
	CLogfile::del();
	return 0;
}
