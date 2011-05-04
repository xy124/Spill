#include "Sprite.hpp"

//#include "SDLgfx/SDL_imageFilter.h"

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
	
	if (m_Textures.at(m_ColorID) != NULL)
		glDeleteTextures( 1, &m_Textures.at(m_ColorID) ); //Surface freigeben, nicht per delete!!
	//MBE: ist das richtig mit dem zeiger von der referenz???
	else
		g_pLogfile->Textout("<br />Error on freeing Image!<br />");
	
}

void CSprite::Load(const string sFilename, bool isBackGround ) { //L�d nicht animiertes sprite

	m_ColorID = 0;

	const int change = 45;



	SDL_Surface * cpImage;// This surface will tell us the details of the image
	GLuint texture;			// This is a handle to our texture object
	cpImage = SDL_LoadBMP(sFilename.c_str());
	GLenum texture_format;
	GLint  nOfColors;

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

	// Check that the image's width is a power of 2
	//TODO find out why!
	if ( (cpImage->w & (cpImage->w - 1)) != 0 ) {
		printf("warning: image.bmp's width is not a power of 2\n");
	}

	// Also check if the height is a power of 2
	if ( (cpImage->h & (cpImage->h - 1)) != 0 ) {
		printf("warning: image.bmp's height is not a power of 2\n");
	}

	int max = (isBackGround ? 1 : MAXCOLORID);
	for (int i = 0; i < max; i++) {//Einzelne bilder erstellen.

		// get the number of channels in the SDL cpImage
		nOfColors = cpImage->format->BytesPerPixel;
		if (nOfColors == 4)     // contains an alpha channel
		{
				if (cpImage->format->Rmask == 0x000000ff)
						texture_format = GL_RGBA;
				else
						texture_format = GL_BGRA;
		} else if (nOfColors == 3)     // no alpha channel
		{
				if (cpImage->format->Rmask == 0x000000ff)
						texture_format = GL_RGB;
				else
						texture_format = GL_BGR;
		} else {
				printf("warning: the image is not truecolor..  this will probably break\n");
				// TODO this error should not go unhandled
		}

		// Have OpenGL generate a texture object handle for us
		glGenTextures( 1, &texture );

		// Bind the texture object
		glBindTexture( GL_TEXTURE_2D, texture );

		// Set the texture's stretching properties
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		// Edit the texture object's image data using the information SDL_Surface gives us
		SDL_LockSurface(cpImage);

		glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, cpImage->w, cpImage->h, 0,
						  texture_format, GL_UNSIGNED_BYTE, cpImage->pixels );

		SDL_UnlockSurface(cpImage);

		//SDL_LockSurface(cpImage);//hoffe man kann so die adresse einer referenz erhalten!!!

		//Pixel manipulieren!//FIXME
		/*int res = SDL_imageFilterAddByte(
				(unsigned char *)cpImage->pixels,
				(unsigned char *)cpImage->pixels,
				(cpImage->pitch * cpImage->h),
				(unsigned char)(i*change));
		if (res != 0) {
			g_pLogfile->FunctionResult("CSPrite::Load", L_FAIL, SDL_GetError());
		}*/

		//SDL_UnlockSurface(cpImage);

		//FIXME Alpha in Pics!!!

		m_Textures.push_back(texture);



	}//for every colorID

	//TODO: do that only once:
	//Rect initialisieren
	m_Rect.x = 0;
	m_Rect.y = 0;
	m_Rect.w = cpImage->w;
	m_Rect.h = cpImage->h;


	// Free the SDL_Surface only if it was successfully created
	if ( cpImage ) {
		SDL_FreeSurface( cpImage );
		cpImage = NULL;
	}


	//FIXME PERFORMANCE!!!

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

	//fixme! m_NumFramesX needs to be defined!
	//m_NumFramesX = m_Textures.at(m_ColorID)->w / m_FrameWidth;
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
			//SDL_BlitSurface(m_pTextures.at(m_ColorID), &FrameRect, m_pScreen, &PositionRect);

			glBindTexture( GL_TEXTURE_2D, this->m_Textures.at(m_ColorID) );

			//FIXME render on right position
			glBegin( GL_QUADS );
			glTexCoord2i( 0, 0 );
				glVertex3f( 100.f, 100.f, 0.0f );

				//Bottom-right vertex (corner)
				glTexCoord2i( 1, 0 );
				glVertex3f( 228.f, 100.f, 0.f );

				//Top-right vertex (corner)
				glTexCoord2i( 1, 1 );
				glVertex3f( 228.f, 228.f, 0.f );

				//Top-left vertex (corner)
				glTexCoord2i( 0, 1 );
				glVertex3f( 100.f, 228.f, 0.f );//FIXME maybe these koords are wrong??^^^^^^
			glEnd();

		}

	}
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
					//SDL_BlitSurface(m_Textures.at(m_ColorID), &spriteLine, m_pScreen, &worldLine );
						//FIXME
						;//HINT -> ;;;;;;;;;;;
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
				//SDL_BlitSurface(m_Textures.at(m_ColorID), &FrameRect, m_pScreen, &PositionRect);
				//FIXME glRender!!
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
	m_pScreen = g_pFramework->getView();
	Load(sBlockFilename);
}

void CSprite::SetPos(const CVec &newPos) {
	m_Rect.x = static_cast<int>(newPos.x);
	m_Rect.y = static_cast<int>(newPos.y);
}
