/*
 * CBackGround.hpp
 *
 *  Created on: 25.04.2011
 *      Author: Sebastian
 */

#ifndef CBACKGROUND_H_
#define CBACKGROUND_H_

#include <SDL.h>
#include <vector>

#include "Sprite.hpp"

class CBackGround {
	public:
		void init(int gameWidth);
		void render();
		void quit();
	private:
		CSprite * m_pBackGroundSprite;
		std::vector<SDL_Rect> m_vPositions;
};

#endif /* CBACKGROUND_H_ */
