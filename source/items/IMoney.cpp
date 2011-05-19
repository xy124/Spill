/*
 * IMoney.cpp
 *
 *  Created on: 19.05.2011
 *      Author: Sebastian
 */

#include "IMoney.hpp"
#include "../Worm.hpp"

CSprite * CIMoney::m_pSprite;


void CIMoney::render() {
	if (getOwner() != NULL) { //draw just if nobody has it!
		m_pSprite->SetPos(CVec(getRect()));
		m_pSprite->Render();
	}
}

void CIMoney::onSetOwner(CWorm * pOwner) {
	setCanMove(pOwner == NULL);
}

void CIMoney::update() {
	if (getOwner() != NULL) {
		//give him Money!
		getOwner()->changeMoneyBy(300);
		//delete me!
		setIsAlive(false);
	}
}
