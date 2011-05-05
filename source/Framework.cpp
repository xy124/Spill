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

	//OpenGL
	/*int a = ColorDepth/3;
	a=8;//TODO stupid <-
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,	a);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,	a);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,	a);//a=8 for 24 bit...*/
	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,	1);//FIXME: ALphaBlending!!
	//TODO: other GL-Settings???
	//maybe these settings from http://www.sdltutorials.com/sdl-opengl-tutorial-basics/ works...
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,        8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,      8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,       8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,      8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,      16);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,     32);

	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,  8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);


	if (bFullscreen) {
		m_pScreen = SDL_SetVideoMode (ScreenWidth, ScreenHeight, 0,
				SDL_GL_DOUBLEBUFFER | SDL_FULLSCREEN | SDL_HWSURFACE | SDL_OPENGL); //open gl sets colordepth
	} else {
		m_pScreen = SDL_SetVideoMode (ScreenWidth, ScreenHeight, ColorDepth,
				SDL_GL_DOUBLEBUFFER | SDL_HWSURFACE | SDL_OPENGL);//SDL_DOUBLEBUF ist automatisch...
	}








	//other ogl settings
	//copied from: http://gpwiki.org/index.php/SDL:Tutorials:Using_SDL_with_OpenGL
	glEnable( GL_TEXTURE_2D );

	glClearColor( 1.0f, 1.0f, 1.0f, 0.0f );//change that!
	//red is 1.0f, 0.0f, 0.0f, 0.0f
	  glViewport(0, 0, 800, 600);

	    glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();

	    glOrtho(0, 800, 600, 0, 1, -1);

	    glMatrixMode(GL_MODELVIEW);

	    glEnable(GL_TEXTURE_2D);

	    glLoadIdentity();


	if (m_pScreen == NULL) {
		string describtion ("Videomodus konnte nicht gesetzt werden");
		describtion = describtion + SDL_GetError();

		g_pLogfile->FunctionResult("CFramework::Init", L_FAIL, describtion  );
		
		Quit();

		return (false);
	}


	//sets the gl koords to sdl koords...
	  glViewport(0, 0,               // coordinates of the
									 // lower left hand corner
									 // of the window which we
									 // will change in the
									 // glOrtho() call.
				 m_pScreen->w,          // Set the logical width
				 m_pScreen->h);         // and height of the
									 // window to match the
									 // actual width and
									 // height as measured in
									 // pixels.

	  // Set the coordinate system for the window moving (0,0)
	  // to the upper left hand corner of the window.
	  glOrtho(0.0,                   // left edge is zero
			  (GLdouble)m_pScreen->w,   // right edge is width
			  (GLdouble)m_pScreen->h,   // bottom edge is height
			  0.0f,                   // top edge is zero
			  0.0f, 1.0f);             // near and far clipping
									 // planes.

	  // Set the clear color to black.
	  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);




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

void CFramework::Quit() {
	SFont_FreeFont(pGameFont);
//MBE SDL_FreeSurface
	if (m_pScreen != NULL)
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


void CFramework::Clear() {//Aufgabe: Buffer löschen
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CFramework::Flip() {//surface umschalten, flippen
	SDL_GL_SwapBuffers();
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

void CFramework::drawLine(CVec v1, CVec v2, int r, int g, int b) {
	g_pLogfile->Textout("Drawline = todo, use opengl functions!");
	//FIXME: Fightanimatuion
	//FIXME draw just if viewable on viewport
	vector<S_ViewPort>::iterator it;
	for (it = g_pFramework->ViewPorts.begin(); it != g_pFramework->ViewPorts.end(); ++it) {
		//lineRGBA(m_pScreen, v1.x-it->m_ScreenPosition.x, v1.y, v2.x-it->m_ScreenPosition.x, v2.y, r, g, b, 255); //TODO Alphavalue 0 ok???
	}
}


