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


	m_ScreenRect.x = 0;
	m_ScreenRect.y = 0;
	m_ScreenRect.w = ScreenWidth;
	m_ScreenRect.h = ScreenHeight;


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

bool CFramework::InitViewPorts(int Amount) {
	S_ViewPort vp;
	vp.m_View.x = 0;//init coords on world
	vp.m_View.y = 0;
	vp.m_View.w = static_cast<int>(m_ScreenRect.w/Amount);
	vp.m_View.h = m_ScreenRect.h;

	//init position on screen:
	vp.m_ScreenPosition = vp.m_View;
	for (int i=0; i<Amount; i++) {
		vp.m_ScreenPosition.x = i*vp.m_View.w;
		ViewPorts.push_back(vp);
	}
	g_pLogfile->fTextout("<br />Successfull created %i Viewport(s)", Amount);
	return true;
}

void CFramework::Quit() {
	SFont_FreeFont(pGameFont);
//MBE SDL_FreeSurface
	SDL_FreeSurface(m_pScreen);
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
		TextOut(m_DebugValue, 0, 50, 0);
	}
}

bool CFramework::KeyDown(int Key_ID) {
	return (m_pKeystate[Key_ID] ? true : false); //na das is ja mal sinnlos
}


void CFramework::Clear() {//Augabe: Buffer l�schen
	SDL_FillRect(m_pScreen, NULL, SDL_MapRGB(m_pScreen->format, 0,255,255));
	//fill Black
}

void CFramework::Flip() {//surface umschalten, flippen
	//SDL_
	SDL_Flip(m_pScreen);
}

void CFramework::showDebugValue(const string &sText, ...) {
	char buffer[MAX_BUFFER];
	va_list pArgList;	//hierrein hauts jetzt die �bergebenen parameter!

	if (sText.length()+1>MAX_BUFFER) {
		g_pLogfile->FunctionResult("showDebugValue", L_FAIL, "*Text > MAX_BUFFER!");
		return;
	}

	va_start (pArgList, sText); //std::string aus Argumenten erstellen!
	vsprintf(buffer, sText.c_str(), pArgList);
	va_end (pArgList);


	//erzeugten std::string schreiben:
	m_DebugValue = buffer;
}

void CFramework::TextOut(std::string &text, int x, int y, int ViewPort) {
	SFont_Write(m_pScreen, pGameFont, x, y, text.c_str());
}
void CFramework::TextOut(std::string &text, CVec &where, int ViewPort) {
	int xx = static_cast<int>(where.x);
	int yy = static_cast<int>(where.y);

	SFont_Write(m_pScreen, pGameFont, xx, yy, text.c_str());
}

bool CFramework::RectInView(SDL_Rect rect, int viewPort) {
	//überprüft ob sich zwei rects schneiden!
	const SDL_Rect &ViewRect = ViewPorts.at(viewPort).m_View;
	return ( (rect.y < ViewRect.y+ViewRect.h) && (rect.y+rect.h > ViewRect.y)
			&& (rect.x < ViewRect.x+ViewRect.w) && (rect.x+rect.w > ViewRect.x) );
}

bool CFramework::RectInView(SDL_Rect rect, std::vector<S_ViewPort>::iterator &iter) {
	const SDL_Rect &ViewRect = iter->m_View;
	return ( (rect.y < ViewRect.y+ViewRect.h) && (rect.y+rect.h > ViewRect.y)
			&& (rect.x < ViewRect.x+ViewRect.w) && (rect.x+rect.w > ViewRect.x) );
}

void CFramework::drawViewPortFrames() {
	vector<S_ViewPort>::iterator it;
	SDL_Rect border;
	border.y = 0;
	border.w = 12;
	border.h = m_ScreenRect.h;
	it = ViewPorts.begin();//start with second ViewPort
	for (++it; it != ViewPorts.end(); ++it) {
		border.x = it->m_ScreenPosition.x-6;
		SDL_FillRect(m_pScreen, &border, SDL_MapRGB(m_pScreen->format, 128, 0, 0));
	}
}


