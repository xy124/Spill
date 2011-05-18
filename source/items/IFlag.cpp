/*
 * Flag.cpp
 *
 *  Created on: 18.05.2011
 *      Author: Sebastian
 */

#include "IFlag.hpp"
#include "../FloatRect.hpp"
#include "../Worm.hpp"

CSprite * CIFlag::m_pSprite;

void CIFlag::init() {//MBE maybe its better to init sprites in inits (if not null... but where to set null?)
	setIsSolid(true);
	setCanMove(true);
	m_pOwner = NULL;

	//MBE: better typeconversation?
	FloatRect FR;
	FR.x = m_pSprite->GetRect().x;
	FR.y = m_pSprite->GetRect().y;
	FR.w = m_pSprite->GetRect().w;
	FR.h = m_pSprite->GetRect().h;
	setRect(FR);
}

void CIFlag::update() {
	if (m_pOwner != NULL) { //Move key on worm!
		FloatRect FR = getRect();
		FR.x = m_pOwner->getRect().x;
		FR.y = m_pOwner->getRect().y-FR.h;
		setRect(FR);
	}
}

void CIFlag::render() {
	m_pSprite->SetPos(CVec(getRect()));
	m_pSprite->Render();
}

void CIFlag::setPOwner(CWorm *m_pOwner)
{
	setCanMove((m_pOwner == NULL));

    this->m_pOwner = m_pOwner;
}




