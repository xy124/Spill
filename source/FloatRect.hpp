/*
 * FloatRect.hpp
 *
 *  Created on: 17.04.2011
 *      Author: Sebastian
 */

#ifndef FLOATRECT_HPP_
#define FLOATRECT_HPP_
#include "Vec.hpp"
#include <SDL.h>

struct FloatRect {
	float x;
	float y;
	float w;
	float h;

	/*FloatRect &operator = (SDL_Rect &rhs) {
		x = rhs.x;
		y = rhs.y;
		w = rhs.w;
		h = rhs.h;
		return *this; //und zurück geben
	}*/
};


#endif /* FLOATRECT_HPP_ */
