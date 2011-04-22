#include "Sprite.hpp"

using namespace std;

CSprite::CSprite(void) {
	m_pScreen = g_pFramework->getWorld(); //zeiger auf screen holen
	m_NumFrames = 0;
	m_FrameWidth = 0;
	m_FrameHeight = 0;
	m_FrameRect.x = 0;
	m_FrameRect.y = 0;
	m_FrameRect.w = 0;
	m_FrameRect.h = 0;
	m_NumFramesX = 1;
}

CSprite::~CSprite(void) {
	
	if (m_pImage != NULL)
		SDL_FreeSurface(m_pImage); //Surface freigeben, nicht per delete!!
	else
		g_pLogfile->Textout("<br />Error on freeing Image!<br />");
	
}

void CSprite::Load(const string sFilename) { //L�d nicht animiertes sprite
	m_pImage = SDL_LoadBMP(sFilename.c_str());

	//pr�fen ob alles glattging
	if (m_pImage == NULL) {
		string describtion("Error while Loading "+sFilename);
		describtion = describtion + SDL_GetError();
		g_pLogfile->FunctionResult("CSprite::Load", L_FAIL, describtion);
		//�Framework herunterfahren
		g_pFramework->Quit();

		//gesamtes Spiel beenden
		exit(1);
	}

	//Rect initialisieren
	m_Rect.x = 0;
	m_Rect.y = 0;
	m_Rect.w = m_pImage->w;
	m_Rect.h = m_pImage->h;

}

void CSprite::Load(const string sFilename, int NumFrames, int FrameWidth, int FrameHeight) { //L�d animierte Frames
	Load(sFilename); //animierte Bmp laden!

	//Rect f�r Animationsphase initialisieren, x&y kommt sp�ter :)
	m_NumFrames = NumFrames;
	m_FrameWidth = FrameWidth;
	m_FrameHeight = FrameHeight;
	m_FrameRect.w = FrameWidth;
	m_FrameRect.h = FrameHeight;

	m_Rect.w = FrameWidth;
	m_Rect.h = FrameHeight;

	m_NumFramesX = m_pImage->w / m_FrameWidth;
}

void CSprite::SetColorKey(int R, int G, int B) {//Colorkey = Transparentfarbe einstellen!
	SDL_SetColorKey(m_pImage, SDL_SRCCOLORKEY, SDL_MapRGB(m_pImage->format, R, G, B));
}

void CSprite::SetPos(float fXPos, float fYPos) {
	m_Rect.x = static_cast<int>(fXPos);
	m_Rect.y = static_cast<int>(fYPos);
}

void CSprite::Render() {//gesamtes Sprite auf Bildschirm rendern
	//Render just if Rects are colliding:
	SDL_Rect rect = m_Rect;
	SDL_Rect viewrect = g_pFramework->getViewRect();
	if (g_pFramework->RectInView(rect)) { //TODO: use view collissionm, mthaat only tests x-Koords! for higher Performance
		rect.x -= viewrect.x;//calculate x in View!
		SDL_BlitSurface(m_pImage, NULL, m_pScreen, &rect);
	}


	//Parameter NULL da kein ausschnitt aus Sprite sondern gesamtes Sprite
}

void CSprite::Render(float fFrameNumber) { //aktuellen Frame reinrendern..
	//Render just if Rects are colliding:
	SDL_Rect rect = m_Rect; //Rect auf screen
	SDL_Rect viewrect = g_pFramework->getViewRect();
	if (g_pFramework->RectInView(rect)) { //TODO: use view collissionm, mthaat only tests x-Koords! for higher Performance
		rect.x -= viewrect.x;//calculate x in View!

		//MBE: man könnte auch mit SDL_SetClipRect arbeiten
		//file:///D:/Daten/Programmierung/SDL-1.2.13_MINGW/docs/html/sdlsetcliprect.html
		//spalte berechnen
		int column = static_cast<int>(fFrameNumber)%m_NumFramesX;//Spalte

		int row = static_cast<int>(fFrameNumber)/m_NumFramesX;//Zeile

		//Rect berechnen:
		m_FrameRect.x = column * m_FrameWidth;
		m_FrameRect.y = row * m_FrameHeight;

		//Ausschnitt rendern
		//HINT:!! if Sprite is animated m_Rect hast not the whole Height/width, just the height/width of one frame!!!
		SDL_BlitSurface(m_pImage, &m_FrameRect, m_pScreen, &rect); //von dem lettzterem Rect werden nur die x-Ywerte �bernommen!!!
	}
}

CSprite::CSprite(const std::string sBlockFilename) {
	//CSprite();
	m_pScreen = g_pFramework->getWorld();
	Load(sBlockFilename);
}

void CSprite::SetPos(const CVec &newPos) {
	m_Rect.x = static_cast<int>(newPos.x);
	m_Rect.y = static_cast<int>(newPos.y);
}
