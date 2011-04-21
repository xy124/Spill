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

#define g_pFramework CFramework::get()

class CFramework : public TSingleton<CFramework> {
	public:
		bool Init(int ScreenWidth, int ScreenHeight,
					int ColorDepth, bool bFullscreen);
		bool InitWorld(int ScreenWidth, int ScreenHeight, int ColorDepth);
		void Quit();
		void Update();
		void Clear();
		void Flip();
		bool KeyDown (int Key_ID);
		SDL_Surface * getWorld() {return m_pWorld;}

		SFont_Font * pGameFont;

		void TextOut(std::string Text, int x, int y);
		void TextOut(std::string Text, CVec Where);

		void showDebugValue(const std::string Text, ...);
		void RenderDebugText();

		void BlitView();

		void setViewRect(SDL_Rect &ViewRect) {m_ViewRect = ViewRect;}
		SDL_Rect& getViewRect() {return m_ViewRect;}

	private:
		SDL_Surface * m_pWorld;//Surface f�r Screen TODO: sp�ter trennen - screensurface und weltsurface, screensurface ist immer nur ein bestimmter Ausschnitt von Weltsurface
		SDL_Surface * m_pView;
		Uint8 *m_pKeystate;	//arraay mit aktuellem Tastaturstatus
		std::string m_DebugValue;
		SDL_Rect m_ViewRect; //the rect that is shown
};

#endif
