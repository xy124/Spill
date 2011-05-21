/*
 * IMoney.cpp
 *
 *  Created on: 19.05.2011
 *      Author: Sebastian
 */

#include "IMoney.hpp"
#include "../Worm.hpp"
#include "../Spritepool.hpp"


CSprite * CIMoney::m_pSprite;


void CIMoney::render() {
	if (getOwner() == NULL) { //draw just if nobody has it!
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

void CIMoney::init() {
	this->CItem::init();
	setIsSolid(true);

	setIcon(g_pSpritepool->at(SPRITEID::ICONMONEY));
	setSprite(g_pSpritepool->at(SPRITEID::MONEY));

	FloatRect FR;
	FR.x = m_pSprite->GetRect().x+500;
	FR.y = m_pSprite->GetRect().y;
	FR.w = m_pSprite->GetRect().w;
	FR.h = m_pSprite->GetRect().h;
	setRect(FR);



	g_pLogfile->Textout("</ br>inited Money!");
}
