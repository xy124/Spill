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
		void Quit();
		void Update();
		void Clear();
		void Flip();
		bool KeyDown (int Key_ID);
		SDL_Surface * getView() {return m_pView;}

		SFont_Font * pGameFont;

		void TextOut(std::string Text, int x, int y);
		void TextOut(std::string Text, CVec Where);

		void showDebugValue(const std::string Text, ...);
		void RenderDebugText();

		void setViewRect(SDL_Rect &ViewRect) {m_ViewRect = ViewRect;}
		SDL_Rect& getViewRect() {return m_ViewRect;}

		bool RectInView(SDL_Rect rect);

		SDL_Rect getWorldRect() {return m_WorldRect;}
		void setWorldRect(SDL_Rect &WorldRect) {m_WorldRect = WorldRect;}

	private:
		SDL_Surface * m_pView;
		Uint8 *m_pKeystate;	//arraay mit aktuellem Tastaturstatus
		std::string m_DebugValue;
		SDL_Rect m_ViewRect; //the rect that is shown
		SDL_Rect m_ScreenRect;//Size of the screen
		SDL_Rect m_WorldRect;


};

#endif
