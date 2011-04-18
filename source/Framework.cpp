#include "Framework.hpp"

bool CFramework::Init(int ScreenWidth, int ScreenHeight, int ColorDepth, bool bFullscreen) {
	//alle Systeme die wir brauchen der SDL initialisieren
	if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1 ) {
		std::string describtion ("SDL konnte nicht initialisiert werden");
		describtion = describtion + SDL_GetError();

		g_pLogfile->FunctionResult("CFramework::Init", L_FAIL, describtion  );
		
		Quit();

		return (false);
	}

	//Fullscreen/Windowmode???
	if (bFullscreen) {
		m_pScreen = SDL_SetVideoMode (ScreenWidth, ScreenHeight, ColorDepth,
										SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
	} else {
		m_pScreen = SDL_SetVideoMode (ScreenWidth, ScreenHeight, ColorDepth,
										SDL_HWSURFACE | SDL_DOUBLEBUF);
	}

	if (m_pScreen == NULL) {
		std::string describtion ("Videomodus konnte nicht gesetzt werden");
		describtion = describtion + SDL_GetError();

		g_pLogfile->FunctionResult("CFramework::Init", L_FAIL, describtion  );
		
		Quit();

		return (false);
	}

	//Tastenstatusarray ZEIGER belegen

	m_pKeystate = SDL_GetKeyState(NULL);
	
	return (true);
}

void CFramework::Quit() {
	SDL_Quit();
}

void CFramework::Update() {
	//Timer...
	g_pTimer->Update();

	//Tastaturstatus ermittlen
	SDL_PumpEvents();
}

bool CFramework::KeyDown(int Key_ID) {
	return (m_pKeystate[Key_ID] ? true : false); //na das is ja mal sinnlos
}


void CFramework::Clear() {//Augabe: Buffer löschen
	SDL_FillRect (m_pScreen, NULL, SDL_MapRGB(m_pScreen->format, 0, 0, 0));
	//mit hintergrundfarbe füllen
}

void CFramework::Flip() {//surface umschalten, flippen
	SDL_Flip(m_pScreen);
}


