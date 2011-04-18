#ifndef _SPRITE_HPP_
#define _SPRITE_HPP_

#include "Framework.hpp"
#include <string>
#include "Logfile.hpp"
#include "Vec.hpp"

class CSprite {
	public:
		CSprite			(void);
		~CSprite		(void);

		CSprite(const std::string sBlockFilename); //even fills the Sprite with the fitting Image
		//TODO ^^Standardcolorkey

		void Load		(const string sFilename);
		void Load		(const string sFilename, int NumFrames, int FrameWidth, int FrameHight);
		void SetColorKey(int R, int G, int B);// beim Render transparente Farbe
		void SetPos		(float fXPos, float fYPos);
		void SetPos		(const CVec &newPos);
		void Render		();
		void Render		(float fFrameNumber);
		SDL_Rect GetRect() {return m_Rect;}
	
	private:
		SDL_Surface *m_pScreen;	//Zeiger auf Screen des Framworks
		SDL_Surface *m_pImage;	//Das eigentliche Bild des Sprites
		SDL_Rect m_Rect;		//Rect des Sprites, enthält größe und position auf bildschirm wo gerendert wird
		SDL_Rect m_FrameRect;	//Ausschnitt für Animationsphase, ausschnitt aus Image der gerendert wird
		int m_NumFrames;		//Anzahl der Animationsphasen
		int m_FrameWidth;		//Breite einer Animationsphase
		int m_FrameHeight;		//Höhe einer Animationsphase
		int m_NumFramesX;			//Woe voeöe Anim-Phasen in X-Richtung ?

};

#endif
