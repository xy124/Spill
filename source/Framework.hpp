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

#define g_pFramework CFramework::get()

struct S_ViewPort {
	SDL_Rect m_View;
	SDL_Rect m_ScreenPosition;
};

class CFramework : public TSingleton<CFramework> {
	public:
		std::vector<S_ViewPort> ViewPorts;

		bool Init(int ScreenWidth, int ScreenHeight,
					int ColorDepth, bool bFullscreen);
		bool InitViewPorts(int Amount);

		void Quit();
		void Update();
		void Clear();
		void Flip();
		bool KeyDown (int Key_ID);
		SDL_Surface * getView() {return m_pScreen;}

		SFont_Font * pGameFont;

		void drawViewPortFrames();

		void TextOut(std::string &text, int x, int y, int ViewPort);
		void TextOut(std::string &text, CVec &where, int ViewPort);

		void showDebugValue(const std::string &sText, ...);
		void RenderDebugText();

		bool RectInView(SDL_Rect rect, int viewPort);
		bool RectInView(SDL_Rect rect, std::vector<S_ViewPort>::iterator &iter);

		SDL_Rect getWorldRect() {return m_WorldRect;}
		void setWorldRect(SDL_Rect &WorldRect) {m_WorldRect = WorldRect;}

	private:
		SDL_Surface * m_pScreen;
		Uint8 *m_pKeystate;	//arraay mit aktuellem Tastaturstatus
		std::string m_DebugValue;
		SDL_Rect m_ScreenRect;//Size of whole the screen
		SDL_Rect m_WorldRect;//Rect of whole world!


};

#endif
