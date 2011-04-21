/*
 * FloatRect.hpp
 *
 *  Created on: 17.04.2011
 *      Author: Sebastian
 */

#ifndef FLOATRECT_HPP_
#define FLOATRECT_HPP_

#include <SDL.h>

struct FloatRect {
	float x;
	float y;
	float w;
	float h;

	void operator = (const SDL_Rect &rhs) {
		x = rhs.x;
		y = rhs.y;
		w = rhs.w;
		h = rhs.h;
	};
};


#endif /* FLOATRECT_HPP_ */
