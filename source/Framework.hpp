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

#define g_pFramework CFramework::get()

class CFramework : public TSingleton<CFramework> {
	public:
		bool Init(int ScreenWidth, int ScreenHeight,
					int ColorDepth, bool bFullscreen);
		void Quit();
		void Update();
		void Clear();
		void Flip();
		bool KeyDown (int Key_ID);
		SDL_Surface * GetScreen() {return m_pScreen;}

		SFont_Font * pGameFont;


		void showDebugValue(const std::string Text, ...);
		void RenderDebugText();

	private:
		SDL_Surface * m_pScreen;//Surface f�r Screen TODO: sp�ter trennen - screensurface und weltsurface, screensurface ist immer nur ein bestimmter Ausschnitt von Weltsurface
		Uint8 *m_pKeystate;	//arraay mit aktuellem Tastaturstatus
		std::string m_DebugValue;
};

#endif
