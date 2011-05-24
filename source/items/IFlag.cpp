/*
 * Flag.cpp
 *
 *  Created on: 18.05.2011
 *      Author: Sebastian
 */

#include "IFlag.hpp"
#include "../FloatRect.hpp"
#include "../Worm.hpp"
#include "../Logfile.hpp"

CSprite * CIFlag::m_pSprite;

void CIFlag::init() {//MBE maybe its better to init sprites in inits (if not null... but where to set null?)
	this->CItem::init();
	setIsSolid(true);
	setName("Flag");

	setIcon(g_pSpritepool->at(SPRITEID::ICONFLAG));
	setSprite(g_pSpritepool->at(SPRITEID::FLAG));

	FloatRect FR;
	FR = m_pSprite->GetRect();
	setRect( FR );

	g_pLogfile->Textout("</ br>inited Flag!");
}

void CIFlag::update() {
	if (getOwner() != NULL) { //Move Flag on worm!
		FloatRect FR = getRect();
		FR.x = getOwner()->getRect().x;
		FR.y = getOwner()->getRect().y-16;
		setRect(FR);
	}
}

void CIFlag::render() {
	m_pSprite->SetPos(CVec(getRect()));
	m_pSprite->Render();
}

void CIFlag::onSetOwner(CWorm * pOwner) {
	setCanMove(pOwner == NULL);
}




