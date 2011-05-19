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
	setIsSolid(true);
	setCanMove(true);
	setIsAlive(true);
	setOwner(NULL);

	FloatRect FR;
	FR.x = m_pSprite->GetRect().x;
	FR.y = m_pSprite->GetRect().y;
	FR.w = m_pSprite->GetRect().w;
	FR.h = m_pSprite->GetRect().h;
	setRect(FR);

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




