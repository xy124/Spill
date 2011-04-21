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
	m_pWorld = NULL;

	if (bFullscreen) {
		m_pView = SDL_SetVideoMode (ScreenWidth, ScreenHeight, ColorDepth,
										SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
	} else {
		m_pView = SDL_SetVideoMode (ScreenWidth, ScreenHeight, ColorDepth,
										SDL_HWSURFACE | SDL_DOUBLEBUF);
	}

	if (m_pView == NULL) {
		string describtion ("Videomodus konnte nicht gesetzt werden");
		describtion = describtion + SDL_GetError();

		g_pLogfile->FunctionResult("CFramework::Init", L_FAIL, describtion  );
		
		Quit();

		return (false);
	}

	m_ScreenRect.x = 0;
	m_ScreenRect.y = 0;
	m_ScreenRect.w = ScreenWidth;
	m_ScreenRect.h = ScreenHeight;

	m_ViewRect.w = ScreenWidth;
	m_ViewRect.h = ScreenHeight;

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

bool CFramework::InitWorld(int WorldWidth, int WorldHeight, int ColorDepth) {

	/*m_pWorldw = ScreenWidth;
	m_pWorldh = ScreenHeight;*/
	//SDL_Surface()
	m_pWorld;// = new SDL_Surface()


	Uint32 rmask, gmask, bmask, amask;

	    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
	       on the endianness (byte order) of the machine */
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	    rmask = 0xff000000;
	    gmask = 0x00ff0000;
	    bmask = 0x0000ff00;
	    amask = 0x000000ff;
	#else
	    rmask = 0x000000ff;
	    gmask = 0x0000ff00;
	    bmask = 0x00ff0000;
	    amask = 0xff000000;
	#endif
	m_pWorld = SDL_CreateRGBSurface(SDL_HWSURFACE, WorldWidth, WorldHeight, ColorDepth,
			rmask, gmask, bmask, amask );

	SDL_DisplayFormat(m_pWorld);

	g_pLogfile->fTextout(RED, "Init m_pWorld, w:%i, h:%i Adress:%i", m_pWorld->w, m_pWorld->h, m_pWorld);
	return (m_pWorld != NULL);
}

void CFramework::Quit() {
	SFont_FreeFont(pGameFont);
//MBE SDL_FreeSurface
	SDL_FreeSurface(m_pView);
	SDL_FreeSurface(m_pWorld);
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
	SDL_FillRect (m_pWorld, NULL, SDL_MapRGB(m_pWorld->format, 255, 255, 255));
	SDL_FillRect(m_pView, NULL, SDL_MapRGB(m_pView->format, 128,128,128));
	//fill Black
}

void CFramework::Flip() {//surface umschalten, flippen
	//SDL_
	SDL_Flip(m_pView);
	//SDL_Flip(m_pWorld); //hat ja kein doublebuffer...
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
	SFont_Write(m_pWorld, pGameFont, x, y, Text.c_str());
}
void CFramework::TextOut(std::string Text, CVec Where) {
	int xx = static_cast<int>(Where.x);
	int yy = static_cast<int>(Where.y);

	SFont_Write(m_pWorld, pGameFont, xx, yy, Text.c_str());
}

void CFramework::BlitView() {//TODO brauchen wir noch flip wenn wir eh mit 2 views arbeiten???
	if (SDL_BlitSurface(m_pWorld, &m_ViewRect, m_pView, NULL)==0)
		g_pLogfile->Textout("yes");
}


