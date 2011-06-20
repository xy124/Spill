#include "Sprite.hpp"

#include "SDLgfx/SDL_imageFilter.h"

using namespace std;

CSprite::CSprite(void) {
	m_pScreen = g_pFramework->getScreen(); //zeiger auf screen holen
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
	vector<SDL_Surface*>::iterator it;
	for (it = m_pImages.begin(); it != m_pImages.end(); ++it) {
		if ((*it) != NULL )
			SDL_FreeSurface(*it); //don't delete Surfaces!
	}
}

void CSprite::Load(const string sFilename, bool isBackGround, bool isInWorld ) { //L�d nicht animiertes sprite
	m_bIsInWorld = isInWorld;

	m_ColorID = 0;

	const unsigned char change = 51;

	int max = (isBackGround ? 1 : MAXCOLORID);
	for (int i = 0; i < max; i++) {//Einzelne bilder erstellen.
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



		SDL_LockSurface(cpImage);//hoffe man kann so die adresse einer referenz erhalten!!!

		//Pixel manipulieren!
		int res = SDL_imageFilterAddByte(
				(unsigned char *)cpImage->pixels,
				(unsigned char *)cpImage->pixels,
				(cpImage->pitch * cpImage->h),
				(unsigned char) change * i
				);
		if (res != 0) {
			g_pLogfile->FunctionResult("CSPrite::Load", L_FAIL, SDL_GetError());
		}

		SDL_UnlockSurface(cpImage);

		int r,g,b;
		//ColorKeyBerechnen:
		r = COLORKEYR + i*change;
		if (r > 255)  r = 255;
		g = COLORKEYG + i*change;
		if (g > 255)  g = 255;
		b= COLORKEYB + i*change;
		if (b > 255)  b = 255;

		SDL_SetColorKey(cpImage, SDL_SRCCOLORKEY, SDL_MapRGB(cpImage->format, r, g, b) );

		SDL_Surface * cpImageInDisplayFormat;
		cpImageInDisplayFormat = SDL_DisplayFormat(cpImage);

		m_pImages.push_back(cpImageInDisplayFormat);

		cpImageInDisplayFormat = NULL;

		SDL_FreeSurface(cpImage);

		cpImage = NULL;
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

void CSprite::SetColorKey(int R, int G, int B, int colorID) {//Colorkey = Transparentfarbe einstellen!
	SDL_SetColorKey(m_pImages.at(colorID), SDL_SRCCOLORKEY,
			SDL_MapRGB(m_pImages.at(colorID)->format, R, G, B));

}

void CSprite::SetPos(float fXPos, float fYPos) {
	m_Rect.x = static_cast<int>(fXPos);
	m_Rect.y = static_cast<int>(fYPos);
}

void CSprite::Render() {//gesamtes Sprite auf Bildschirm rendern
	const SDL_Rect SpriteRect = m_Rect;//Position auf gesamter world
	SDL_Rect PositionRect;//Position relativ zu Viewport
	SDL_Rect FrameRect; //rect describes the shown part of the sprite

	if (!m_bIsInWorld) {
		FrameRect.x = 0;
		FrameRect.y = 0;
		FrameRect.w = SpriteRect.w;
		FrameRect.h = SpriteRect.h;
		PositionRect = SpriteRect;
		SDL_BlitSurface(m_pImages.at(m_ColorID), &FrameRect, m_pScreen, &PositionRect);
	} else {
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
	}//is in World
}

void CSprite::Render(float fFrameNumber, bool bFlipped, int colorID) { //aktuellen Frame reinrendern..
	setColorID(colorID);


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
	setColorID(colorID);
	Render();
}

void CSprite::setColorID(int colorID) {
	m_ColorID = colorID;
	if (colorID > MAXCOLORID)
		m_ColorID = 0;
}

CSprite::CSprite(const std::string sBlockFilename) {
	//CSprite();
	//TODO: don't we need standard construcotr here???
	m_pScreen = g_pFramework->getScreen();
	Load(sBlockFilename);
}

void CSprite::SetPos(const CVec &newPos) {
	m_Rect.x = static_cast<int>(newPos.x);
	m_Rect.y = static_cast<int>(newPos.y);
}
