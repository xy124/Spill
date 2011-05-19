/*
 * IMoney.hpp
 *
 *  Created on: 19.05.2011
 *      Author: Sebastian
 */

#ifndef IMONEY_H_
#define IMONEY_H_

#include "Item.hpp"

class CIMoney: public CItem {
private:
	static CSprite * m_pSprite;

public:
	~CIMoney() {};



	static void setSprite(CSprite * pSprite) {
		CIMoney::m_pSprite = pSprite;
	}

	void init();
	void render();

	void onSetOwner(CWorm * pOwner);

	void update();
	void quit() {};

};

#endif /* IMONEY_H_ */
