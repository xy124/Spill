#ifndef _FRAMEWORK_HPP_
#define _FRAMEWORK_HPP_

#include "Singleton.hpp"
#include "Timer.hpp"
#include "Logfile.hpp"
#include <string>
#include <SDL.h>

#include "SFont/SFont.h"
#include "stdarg.h"
#include "consts.hpp"
#include "Vec.hpp"
#include <vector>

#include "SDLgfx/SDL_gfxPrimitives.h"

#include "Texture.hpp"


#define g_pFramework CFramework::get()

struct S_ViewPort {
	SDL_Rect m_View;
	SDL_Rect m_ScreenPosition;
};

class CFramework : public TSingleton<CFramework> {
	private:
		bool m_bIsNewEvent;
		SDL_Surface * m_pScreen;

		Uint8 *m_pKeystate;	//arraay mit aktuellem Tastaturstatus
		std::string m_DebugValue;
		SDL_Rect m_ScreenRect;//Size of whole the screen

		SDL_Event m_lastEvent;

	public:

		std::vector<S_ViewPort> ViewPorts;

		bool Init(int ScreenWidth, int ScreenHeight,
					int ColorDepth, bool bFullscreen);
		bool InitViewPorts(int Amount);
		void DestroyViewPorts();
		void InitAttackAnmimations();

		void Quit();
		void Update();
		int ProcessEvents();//Processes Events for closing and so on!
		void Clear();
		void Flip();
		bool KeyDown (int Key_ID);
		SDL_Surface * getScreen() {return m_pScreen;}

		SFont_Font * pGameFont;

		void renderViewPortFrames();

		void TextOut(std::string &text, int x, int y, int ViewPort);
		void TextOut(std::string &text, CVec &where, int ViewPort);

		void showDebugValue(const std::string &sText, ...);
		void RenderDebugText();

		bool RectInView(SDL_Rect rect, int viewPort);
		bool RectInView(SDL_Rect rect, std::vector<S_ViewPort>::iterator &iter);

		void drawLine(CVec v1, CVec v2, int r, int g, int b, bool doOnViewCheck = true);//on viewcheck überprüft nur die endpunkte!!!!
		void drawFilledPolygon(
				const Sint16 *  	vx,
				const Sint16 *  	vy,
				int  	n,
				Uint8  	r,
				Uint8  	g,
				Uint8  	b);
		void drawTexturedPolygon(
				const Sint16 *  	vx,
				const Sint16 *  	vy,
				int n,
				CTexture * pTexture);

		//we need to handle events in this way to be able to use them on different positions in code!
		SDL_Event getLastEvent() {return m_lastEvent;}
		bool isNewEvent() {return m_bIsNewEvent;}

};

#endif
