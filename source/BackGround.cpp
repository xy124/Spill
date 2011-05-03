/*
 * CBackGround.cpp
 *
 *  Created on: 25.04.2011
 *      Author: Sebastian
 */

#include "BackGround.hpp"

using namespace std;


void CBackGround::init(int gameWidth) {
	m_pBackGroundSprite = new CSprite;
	m_pBackGroundSprite->Load(_DIRDATA_+"/P1050738.bmp", true);



	for (int i = 0; i <= gameWidth; i+=m_pBackGroundSprite->GetRect().w) {
		SDL_Rect r;
		r.x = i;
		r.y = 0;
		//actually width and height aren't needed
		r.w = m_pBackGroundSprite->GetRect().w;
		r.h = m_pBackGroundSprite->GetRect().h;

		m_vPositions.push_back(r);
	}

}



void CBackGround::render() {
	vector<SDL_Rect>::iterator it;
	for (it = m_vPositions.begin(); it != m_vPositions.end(); ++it) {
		m_pBackGroundSprite->SetPos(it->x, it->y);
		m_pBackGroundSprite->Render(0);
	}
}



void CBackGround::quit() {
	if (m_pBackGroundSprite != NULL) {
		delete(m_pBackGroundSprite);
	}
}

