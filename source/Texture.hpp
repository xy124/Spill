/*
 * CTexture.hpp
 *
 *  Created on: 13.05.2011
 *      Author: Sebastian
 */

#ifndef CTEXTURE_HPP_
#define CTEXTURE_HPP_

#include <SDL.h>
#include <string>

class CTexture {
public:
	CTexture() {};
	void Load		(const std::string sFilename);
	void SetColorKey(int R, int G, int B, int colorID);// beim Render transparente Farbe
	virtual ~CTexture();

	SDL_Surface * getSurface() {
		return m_pSurface;
	}
private:
	SDL_Surface * m_pSurface;
};

#endif /* CTEXTURE_HPP_ */
