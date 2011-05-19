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
	static CWorm * m_pOwner;

public:
	CIFlag() {};
	virtual ~CIFlag() {};



	static void setSprite(CSprite * pSprite) {
		CIFlag::m_pSprite = pSprite;
	}

	void init();
	void render();

	void update();
	void quit() {};

	void setPOwner(CWorm *m_pOwner);
	CWorm * getOwner() {
		return m_pOwner;
	};

};

#endif /* FLAG_HPP_ */
