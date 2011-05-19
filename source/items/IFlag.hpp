/*
 * Flag.hpp
 *
 *  Created on: 18.05.2011
 *      Author: Sebastian
 */

#ifndef IFLAG_HPP_
#define IFLAG_HPP_

#include "../Sprite.hpp"
#include "../PhysicalObject.hpp"
#include "Item.hpp"


class CWorm;

class CIFlag : public CItem {
private:
	static CSprite * m_pSprite;

public:
	~CIFlag() {};



	static void setSprite(CSprite * pSprite) {
		CIFlag::m_pSprite = pSprite;
	}

	void init();
	void render();

	void onSetOwner(CWorm * pOwner);

	void update();
	void quit() {};

};

#endif /* FLAG_HPP_ */
