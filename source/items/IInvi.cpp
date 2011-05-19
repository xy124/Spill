/*
 * IInvi.cpp
 *
 *  Created on: 19.05.2011
 *      Author: Sebastian
 */

#include "IInvi.hpp"

#include "../Worm.hpp"
#include "../Spritepool.hpp"
#include "../Timer.hpp"
#include "../Logfile.hpp"


CSprite * CIInvi::m_pSprite;


void CIInvi::render() {
	if (getOwner() == NULL) { //draw just if nobody has it!
		m_pSprite->SetPos(CVec(getRect()));
		m_pSprite->Render();
	}
}

void CIInvi::onSetOwner(CWorm * pOwner) {
	setCanMove(pOwner == NULL);
}

void CIInvi::update() {
	if ((m_fGotOwner > 0.0f)//was activated
			&& (m_fGotOwner+15.0f < g_pTimer->now())){
		getOwner()->setVisibility(true); //MBE makes no sense to give a pointer with get!??
		//kill it!
		setIsAlive(false);
	}
}

void CIInvi::init() {
	this->CItem::init();
	setIsSolid(true);

	setIcon(g_pSpritepool->at(SPRITE_ICONINVI));
	setSprite(g_pSpritepool->at(SPRITE_INVI));
	//FIXME: itemicons aren't drawn

	FloatRect FR;
	FR.x = m_pSprite->GetRect().x+1200;
	FR.y = m_pSprite->GetRect().y;
	FR.w = m_pSprite->GetRect().w;
	FR.h = m_pSprite->GetRect().h;
	setRect(FR);

	m_fGotOwner = -1.0f;


	g_pLogfile->Textout("</ br>inited INVI!");
}

void CIInvi::use() {
	if (m_fGotOwner < 0.0f) {
		getOwner()->setVisibility(false);
		m_fGotOwner = g_pTimer->now();
		g_pLogfile->Textout("</br> INVI was used!");

	}
}



