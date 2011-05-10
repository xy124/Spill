#include "Framework.hpp"
#include "Sprite.hpp"
#include "AttackAnimations/CAA_Explosion1.hpp"
//MBE: make overview about includes!

//TODO: ITEMS ;)

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
	string s = _DIRDATA_; s+="/24P_Copperplate_Bluesmall.bmp";
	g_pLogfile->Textout("<br />"+s);
	SDL_Surface * pFontImage = SDL_LoadBMP((_DIRDATA_+"/24P_Copperplate_Blue_small.bmp").c_str());
	//SDL_SetColorKey(pFontImage, SDL_SRCCOLORKEY, SDL_MapRGB(pFontImage->format, 0, 0, 0)); //COLORKEY Black!
	//^^why should we need a color key here???
	pGameFont = SFont_InitFont(pFontImage);

	//init AttackAnimations
	InitAttackAnmimations();

	//Init Debugvalue
	m_DebugValue = "";

	return (true);
}

bool CFramework::InitViewPorts(int Amount) {
	S_ViewPort vp;
	vp.m_View.x = 0;//init coords on world
	vp.m_View.y = 0;
	vp.m_View.w = static_cast<int>((m_ScreenRect.w-(Amount-1)*VIEWPORTFRAMEWIDTH)/Amount);
	g_pLogfile->fTextout("<br />Viewportwidth = %i", vp.m_View.w);
	vp.m_View.h = m_ScreenRect.h;

	//init position on screen:
	vp.m_ScreenPosition = vp.m_View;
	for (int i=0; i<Amount; i++) {
		vp.m_ScreenPosition.x = i*(vp.m_View.w+VIEWPORTFRAMEWIDTH);
		g_pLogfile->fTextout(GREEN,"<br />Viewport%i .x = %i", i, vp.m_ScreenPosition.x);
		ViewPorts.push_back(vp);
	}
	g_pLogfile->fTextout("<br />Successfull created %i Viewport(s)", Amount);
	return true;
}

void CFramework::DestroyViewPorts() {
	ViewPorts.clear(); //HINT: thatn should be ok without memory leaks!
}

void CFramework::Quit() {
	DestroyViewPorts();
	SFont_FreeFont(pGameFont);
//MBE SDL_FreeSurface
	SDL_FreeSurface(m_pScreen);
	//TODO: free Attackanimations!?! free background!?! but i think the SDL does that automatically!
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
	SFont_Write(m_pScreen, pGameFont,
			x+ViewPorts.at(ViewPort).m_ScreenPosition.x, y, text.c_str());
}
void CFramework::TextOut(std::string &text, CVec &where, int ViewPort) {
	int xx = static_cast<int>(where.x);
	int yy = static_cast<int>(where.y);

	SFont_Write(m_pScreen, pGameFont,
			xx+ViewPorts.at(ViewPort).m_ScreenPosition.x, yy, text.c_str());
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

void CFramework::renderViewPortFrames() {
	vector<S_ViewPort>::iterator it;
	SDL_Rect border;
	border.y = 0;
	border.w = VIEWPORTFRAMEWIDTH;
	border.h = m_ScreenRect.h;
	it = ViewPorts.begin();//start with second ViewPort
	for (++it; it != ViewPorts.end(); ++it) {
		border.x = it->m_ScreenPosition.x-VIEWPORTFRAMEWIDTH;
		SDL_FillRect(m_pScreen, &border, SDL_MapRGB(m_pScreen->format, 128, 0, 0));
	}
}

void CFramework::drawLine(CVec v1, CVec v2, int r, int g, int b, bool doOnViewCheck) {
	vector<S_ViewPort>::iterator it;
	for (it = g_pFramework->ViewPorts.begin(); it != g_pFramework->ViewPorts.end(); ++it) {
		if ( (doOnViewCheck == false) ||
				((v1.inRect(it->m_View)) && (v2.inRect(it->m_View))) )  {
		lineRGBA(m_pScreen,
				v1.x + (it->m_ScreenPosition.x) - (it->m_View.x), v1.y,
				v2.x + (it->m_ScreenPosition.x) - (it->m_View.x), v2.y,
				r, g, b, 255);
		}
	}
}


void CFramework::InitAttackAnmimations() {
	CSprite * pCannonball = new CSprite();
	pCannonball->Load(_DIRDATA_+"/CannonBall.bmp");
	CAA_CannonBall::setSprite(pCannonball);
	pCannonball = NULL;
	CSprite * pExplosion1 = new CSprite();
	pExplosion1->Load(_DIRDATA_+"/Explosion1.bmp", 6, 30, 30);
	CAA_Explosion1::setSprite(pExplosion1);
		pExplosion1 = NULL;
}

int CFramework::ProcessEvents() {
	int result = 0;
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case (SDL_QUIT): {
				result = ESCAPED;
			} break;
			case (SDL_KEYDOWN): {
				switch (event.key.keysym.sym) {
					case (SDLK_ESCAPE): {
						result = ESCAPED;
					} break;
					default: //nothing
						break;
				} //switch event.key.keysym.sym
			} break;
		} //Switch event.type
	} //if
	return result;
}

