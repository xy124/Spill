/*
 * IInvi.hpp
 *
 *  Created on: 19.05.2011
 *      Author: Sebastian
 */

#ifndef IINVI_HPP_
#define IINVI_HPP_

#include "Item.hpp"

class CIInvi: public CItem {
private:
	static CSprite * m_pSprite;
	float m_fGotOwner;

public:
	~CIInvi() {};



	static void setSprite(CSprite * pSprite) {
		CIInvi::m_pSprite = pSprite;
	}

	void init();
	void render();

	void onSetOwner(CWorm * pOwner);

	void use();

	void update();
	void quit() {};
};

#endif /* IINVI_HPP_ */
