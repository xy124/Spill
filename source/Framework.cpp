#include "Framework.hpp"

using namespace std;

bool CFramework::Init(int ScreenWidth, int ScreenHeight, int ColorDepth, bool bFullscreen) {
	//alle Systeme die wir brauchen der SDL initialisieren
	if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1 ) {
		string describtion ("SDL konnte nicht initialisiert werden");
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
		string describtion ("Videomodus konnte nicht gesetzt werden");
		describtion = describtion + SDL_GetError();

		g_pLogfile->FunctionResult("CFramework::Init", L_FAIL, describtion  );
		
		Quit();

		return (false);
	}

	//Tastenstatusarray ZEIGER belegen

	m_pKeystate = SDL_GetKeyState(NULL);
	
	//Init SFont
	g_pLogfile->Textout("did sth.");
	string s = _DIRDATA_; s+="/24P_Copperplate_Blue.bmp";
	g_pLogfile->Textout("<br />"+s);
	SDL_Surface * pFontImage = SDL_LoadBMP((_DIRDATA_+"/24P_Copperplate_Blue.bmp").c_str());
	SDL_SetColorKey(pFontImage, SDL_SRCCOLORKEY, SDL_MapRGB(pFontImage->format, 0, 0, 0)); //COLORKEY Black!
	pGameFont = SFont_InitFont(pFontImage);

	//Init Debugvalue
	m_DebugValue = "";

	return (true);
}

void CFramework::Quit() {
	SFont_FreeFont(pGameFont);
	SDL_Quit();
}

void CFramework::Update() {
	//Timer...
	g_pTimer->Update();

	//Tastaturstatus ermittlen
	SDL_PumpEvents();
}

void CFramework::RenderDebugText() {
	//DebugText:
	if (m_DebugValue != "") {
		TextOut(m_DebugValue, 0,50);
	}
}

bool CFramework::KeyDown(int Key_ID) {
	return (m_pKeystate[Key_ID] ? true : false); //na das is ja mal sinnlos
}


void CFramework::Clear() {//Augabe: Buffer l�schen
	SDL_FillRect (m_pScreen, NULL, SDL_MapRGB(m_pScreen->format, 0, 0, 0));
	//mit hintergrundfarbe f�llen
}

void CFramework::Flip() {//surface umschalten, flippen
	SDL_Flip(m_pScreen);
}

void CFramework::showDebugValue(const string Text, ...) {
	char buffer[MAX_BUFFER];
	va_list pArgList;	//hierrein hauts jetzt die �bergebenen parameter!

	if (Text.length()+1>MAX_BUFFER) {
		g_pLogfile->FunctionResult("showDebugValue", L_FAIL, "*Text > MAX_BUFFER!");
		return;
	}

	va_start (pArgList, Text); //std::string aus Argumenten erstellen!
	vsprintf(buffer, Text.c_str(), pArgList);
	va_end (pArgList);


	//erzeugten std::string schreiben:
	m_DebugValue = buffer;
}

void CFramework::TextOut(std::string Text, int x, int y) {
	SFont_Write(m_pScreen, pGameFont, x, y, Text.c_str());
}
void CFramework::TextOut(std::string Text, CVec Where) {
	int xx = static_cast<int>(Where.x);
	int yy = static_cast<int>(Where.y);

	SFont_Write(m_pScreen, pGameFont, xx, yy, Text.c_str());
}


