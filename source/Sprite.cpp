#include "Sprite.hpp"

using namespace std;

CSprite::CSprite(void) {
	m_pScreen = g_pFramework->GetScreen(); //zeiger auf screen holen
}

CSprite::~CSprite(void) {
	SDL_FreeSurface(m_pImage); //Surface freigeben, nicht per delete!!
}

void CSprite::Load(const string sFilename) { //Läd nicht animiertes sprite
	m_pImage = SDL_LoadBMP(sFilename.c_str());

	//prüfen ob alles glattging
	if (m_pImage == NULL) {
		string describtion("Error while Loading "+sFilename);
		describtion = describtion + SDL_GetError();
		g_pLogfile->FunctionResult("CSprite::Load", L_FAIL, describtion);
		//ÄFramework herunterfahren
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

void CSprite::Load(const string sFilename, int NumFrames, int FrameWidth, int FrameHeight) { //Läd animierte Frames
	Load(sFilename); //animierte Bmp laden!

	//Rect für Animationsphase initialisieren, x&y kommt später :)
	m_NumFrames = NumFrames;
	m_FrameWidth = FrameWidth;
	m_FrameHeight = FrameHeight;
	m_FrameRect.w = FrameWidth;
	m_FrameRect.h = FrameHeight;
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
	SDL_BlitSurface(m_pImage, NULL, m_pScreen, &m_Rect);
	//Parameter NULL da kein ausschnitt aus Sprite sondern gesamtes Sprite
}

void CSprite::Render(float fFrameNumber) { //aktuellen Frame reinrendern..
	//spalte berechnen
	int column = static_cast<int>(fFrameNumber)%m_NumFramesX;//Spalte

	int row = static_cast<int>(fFrameNumber)/m_NumFramesX;//Zeile

	//Rect berechnen:
	m_FrameRect.x = column * m_FrameWidth;
	m_FrameRect.y = row * m_FrameHeight;

	//Ausschnitt rendern
	SDL_BlitSurface(m_pImage, &m_FrameRect, m_pScreen, &m_Rect); //von dem lettzterem Rect werden nur die x-Ywerte übernommen!!!
}

CSprite::CSprite(const std::string sBlockFilename) {
	CSprite();
	Load(sBlockFilename);
}

void CSprite::SetPos(const CVec &newPos) {
	m_Rect.x = static_cast<int>(newPos.x);
	m_Rect.y = static_cast<int>(newPos.y);
}
