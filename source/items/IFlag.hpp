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


class CWorm;

class CIFlag : public CPhysicalObject {
private:
	CWorm * m_pOwner;
	static CSprite * m_pSprite;

public:
	CIFlag() {};
	virtual ~CIFlag() {};



	static void setSprite(CSprite * pSprite) {
		CIFlag::m_pSprite = pSprite;
	}

	void init();
	void render();
    void setPOwner(CWorm *m_pOwner);
    CWorm * getOwner() {
    	return m_pOwner;
    };
	void update();
	void quit() {};
};

#endif /* FLAG_HPP_ */
