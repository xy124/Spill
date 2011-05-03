#include "Sprite.hpp"

#include "SDLgfx/SDL_imageFilter.h"

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
	
	if (m_pImages.at(m_ColorID) != NULL)
		SDL_FreeSurface(m_pImages.at(m_ColorID)); //Surface freigeben, nicht per delete!!
	else
		g_pLogfile->Textout("<br />Error on freeing Image!<br />");
	
}

void CSprite::Load(const string sFilename) { //L�d nicht animiertes sprite

	m_ColorID = 0;

	for (int i = 0; i < MAXCOLORID; i++) {//Einzelne bilder erstellen.
		SDL_Surface * cpImage;
		cpImage = SDL_LoadBMP(sFilename.c_str());

		//pr�fen ob alles glattging
		if (cpImage == NULL) {
			string describtion("Error while Loading "+sFilename);
			describtion = describtion + SDL_GetError();
			g_pLogfile->FunctionResult("CSprite::Load", L_FAIL, describtion);


			//�Framework herunterfahren
			g_pFramework->Quit();

			//gesamtes Spiel beenden
			exit(1);
		}

		SDL_DisplayFormat(cpImage);

		SDL_LockSurface(cpImage);//hoffe man kann so die adresse einer referenz erhalten!!!

		//Pixel manipulieren!
		int res = SDL_imageFilterAddByte(
				(unsigned char *)cpImage->pixels,
				(unsigned char *)cpImage->pixels,
				(cpImage->pitch * cpImage->h),
				(unsigned char)(i*45));
		if (res != 0) {
			g_pLogfile->FunctionResult("CSPrite::Load", L_FAIL, SDL_GetError());
		}

		SDL_UnlockSurface(cpImage);

		m_pImages.push_back(cpImage);

		cpImage = NULL;
		//FIXME PERFORMANCE!!!
	}

	//Rect initialisieren
	m_Rect.x = 0;
	m_Rect.y = 0;
	m_Rect.w = m_pImages.at(m_ColorID)->w;
	m_Rect.h = m_pImages.at(m_ColorID)->h;

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

	m_NumFramesX = m_pImages.at(m_ColorID)->w / m_FrameWidth;
}

void CSprite::SetColorKey(int R, int G, int B) {//Colorkey = Transparentfarbe einstellen!
	SDL_SetColorKey(m_pImages.at(m_ColorID), SDL_SRCCOLORKEY, SDL_MapRGB(m_pImages.at(m_ColorID)->format, R, G, B));
}

void CSprite::SetPos(float fXPos, float fYPos) {
	m_Rect.x = static_cast<int>(fXPos);
	m_Rect.y = static_cast<int>(fYPos);
}

void CSprite::Render() {//gesamtes Sprite auf Bildschirm rendern
	const SDL_Rect SpriteRect = m_Rect;//Position auf gesamter world
	SDL_Rect PositionRect;//Position relativ zu Viewport
	SDL_Rect FrameRect; //rect describes the shown part of the sprite

	vector<S_ViewPort>::iterator it;
	for (it = g_pFramework->ViewPorts.begin(); it != g_pFramework->ViewPorts.end(); ++it) {
		const SDL_Rect ViewRect = it->m_View;//viewRect auf gesamter world
		if (g_pFramework->RectInView(SpriteRect, it)) { //TODO: use view collissionm, mthaat only tests x-Koords! for higher Performance
			FrameRect.x = 0;
			FrameRect.y = 0;
			FrameRect.w = SpriteRect.w;
			FrameRect.h = SpriteRect.h;

			PositionRect = SpriteRect;

			PositionRect.x = SpriteRect.x - ViewRect.x;

			if (SpriteRect.x < ViewRect.x) { //Left edge out of View
				FrameRect.x = ViewRect.x - SpriteRect.x;
				FrameRect.w = SpriteRect.w - FrameRect.x;
				PositionRect.x = 0;
			}

			if (SpriteRect.x+SpriteRect.w > ViewRect.x+ViewRect.w) { //Right edge out of View
				FrameRect.w = FrameRect.w - (SpriteRect.x+SpriteRect.w - (ViewRect.x+ViewRect.w));
				//Breite    = Breite      - überragende länge
			}


			// handle viewport
			PositionRect.x += it->m_ScreenPosition.x;
			SDL_BlitSurface(m_pImages.at(m_ColorID), &FrameRect, m_pScreen, &PositionRect);

		}

	}
}

void CSprite::Render(float fFrameNumber, bool bFlipped) { //aktuellen Frame reinrendern..


	SDL_Rect PositionRect;//Position relativ zu Viewport
	const SDL_Rect SpriteRect = m_Rect;


	vector<S_ViewPort>::iterator it;
	for (it = g_pFramework->ViewPorts.begin(); it != g_pFramework->ViewPorts.end(); ++it) {
		const SDL_Rect ViewRect = it->m_View;//viewRect auf gesamter world

		//Render just if Rects are colliding:
		if (g_pFramework->RectInView(SpriteRect, it)) { //TODO: use view collissionm, mthaat only tests x-Koords! for higher Performance
			PositionRect = SpriteRect; //damit erstmal w,h und y stimmen.

			PositionRect.x = SpriteRect.x - ViewRect.x;

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
				worldLine = PositionRect;
				worldLine.x += it->m_ScreenPosition.x;
				worldLine.w = 1; //Line!

				worldLine.x += m_FrameWidth; //worldline fängt rechts an!
				while (spriteLine.x<m_FrameRect.x+m_FrameWidth) {//MBE: < or <= framwidth???
					spriteLine.x++;
					worldLine.x--;
					if ((worldLine.x > it->m_ScreenPosition.x)
							&& (worldLine.x < it->m_ScreenPosition.x+it->m_ScreenPosition.w))
						//Render line JUST if on screen!
					SDL_BlitSurface(m_pImages.at(m_ColorID), &spriteLine, m_pScreen, &worldLine );
				}
			} else {

				//TODO: maybe we can do this test also for anim so that only once this test is done in render -animated
				SDL_Rect FrameRect = m_FrameRect;//rect of the final part of the sprite that will be rendered if not flipped
				if (SpriteRect.x < ViewRect.x) { //Left edge out of View
					FrameRect.x += (ViewRect.x - SpriteRect.x);
					FrameRect.w -= (ViewRect.x - SpriteRect.x);
					PositionRect.x = 0;
				}

				if (SpriteRect.x+m_FrameRect.w > ViewRect.x+ViewRect.w) { //Right edge out of View
					FrameRect.w = FrameRect.w - (SpriteRect.x+SpriteRect.w - (ViewRect.x+ViewRect.w));
					//Breite    = Breite      - überragende länge
				}


				// handle viewports-X
				PositionRect.x += it->m_ScreenPosition.x;
				SDL_BlitSurface(m_pImages.at(m_ColorID), &FrameRect, m_pScreen, &PositionRect);
			}//not flipped
		}
	}//For viewports
}



void CSprite::Render(int colorID) {//gesamtes Sprite auf Bildschirm rendern
	m_ColorID = colorID;
	if (colorID > MAXCOLORID)
		m_ColorID = 0;
	Render();
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
