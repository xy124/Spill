#include "Sprite.hpp"

using namespace std;

CSprite::CSprite(void) {
	m_pScreen = g_pFramework->getView(); //zeiger auf screen holen
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

	SDL_DisplayFormat(m_pImage);

	//Rect initialisieren
	m_Rect.x = 0;
	m_Rect.y = 0;
	m_Rect.w = m_pImage->w;
	m_Rect.h = m_pImage->h;

}

void CSprite::Load(const string sFilename, int NumFrames, int FrameWidth, int FrameHeight) { //L�d animierte Frames
	Load(sFilename); //load animated bmp!

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

	vector<S_ViewPort>::iterator it;
	for (it = g_pFramework->ViewPorts.begin(); it != g_pFramework->ViewPorts.end(); ++it) {
		SDL_Rect viewrect = it->m_View;
		if (g_pFramework->RectInView(rect, it)) { //TODO: use view collissionm, mthaat only tests x-Koords! for higher Performance
			rect.x -= viewrect.x;//calculate x in View!
			rect.x += it->m_ScreenPosition.x;
			SDL_BlitSurface(m_pImage, NULL, m_pScreen, &rect);
		}
	}



	//Parameter NULL da kein ausschnitt aus Sprite sondern gesamtes Sprite
}

void CSprite::Render(float fFrameNumber, bool bFlipped) { //aktuellen Frame reinrendern..
	//Render just if Rects are colliding:
	SDL_Rect rect;
	SDL_Rect viewrect;
	vector<S_ViewPort>::iterator it;
	for (it = g_pFramework->ViewPorts.begin(); it != g_pFramework->ViewPorts.end(); ++it) {
		rect = m_Rect; //where to draw it
		viewrect = it->m_View;
		if (g_pFramework->RectInView(rect, it)) { //TODO: use view collissionm, mthaat only tests x-Koords! for higher Performance
			rect.x -= viewrect.x;//calculate x in View!
			rect.x += it->m_ScreenPosition.x;

			//MBE: man könnte auch mit SDL_SetClipRect arbeiten
			//file:///D:/Daten/Programmierung/SDL-1.2.13_MINGW/docs/html/sdlsetcliprect.html
			//spalte berechnen
			int column = static_cast<int>(fFrameNumber)%m_NumFramesX;//Spalte

			int row = static_cast<int>(fFrameNumber)/m_NumFramesX;//Zeile

			//Rect berechnen:
			m_FrameRect.x = column * m_FrameWidth;
			m_FrameRect.y = row * m_FrameHeight;

			//Ausschnitt rendern
			//HINT:!! if Sprite is animated m_Rect has not the whole Height/width, just the height/width of one frame!!!
			if (bFlipped) {
				SDL_Rect spriteLine; //Line in Sprite
				spriteLine = m_FrameRect;
				spriteLine.w = 1; //Line!

				SDL_Rect worldLine; //Line in World
				worldLine = rect;
				worldLine.w = 1; //Line!

				worldLine.x += rect.w; //worldline fängt rechts an!
				while (spriteLine.x<m_FrameRect.x+m_FrameWidth) {//TODO: < or <= framwidth???
					spriteLine.x++;
					worldLine.x--;
					SDL_BlitSurface(m_pImage, &spriteLine, m_pScreen, &worldLine );
				}
			} else {
				SDL_BlitSurface(m_pImage, &m_FrameRect, m_pScreen, &rect); //von dem lettzterem Rect werden nur die x-Ywerte �bernommen!!!
			}
		}
	}//For viewports
}

CSprite::CSprite(const std::string sBlockFilename) {
	//CSprite();
	m_pScreen = g_pFramework->getView();
	Load(sBlockFilename);
}

void CSprite::SetPos(const CVec &newPos) {
	m_Rect.x = static_cast<int>(newPos.x);
	m_Rect.y = static_cast<int>(newPos.y);
}
