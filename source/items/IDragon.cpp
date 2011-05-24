/*
 * IDragon.cpp
 *
 *  Created on: 24.05.2011
 *      Author: Sebastian
 */

#include "IDragon.hpp"
#include "../Timer.hpp"
#include "../FloatRect.hpp"
#include "../Worm.hpp"

CIDragon::CIDragon() {
	// TODO Auto-generated constructor stub

}

CIDragon::~CIDragon() {
	// TODO Auto-generated destructor stub
}

void CIDragon::init() {
	m_fAnimPhase = 0.0f;
	this->CItem::init();
	setName("Dragon");
	setDropable(true);


	setIcon(g_pSpritepool->at(SPRITEID::ICONDRAGON));
	m_pSpriteBody = g_pSpritepool->at(SPRITEID::DRAGONBODY);
	m_pSpriteWings = g_pSpritepool->at(SPRITEID::DRAGONWINGS);
	FloatRect FR;
	FR = m_pSpriteBody->GetRect();
	setRect(FR);
	m_bActive = false;
}

void CIDragon::update() {
	if (m_bActive) {
		//set pos under Owner!
		FloatRect worm = getOwner()->getRect();
		FloatRect dragon = getRect();

		dragon.x = worm.x-87;
		dragon.x = 0;

		setRect(dragon);

		m_fAnimPhase += 10.0f * g_pTimer->getElapsed();
		if (m_fAnimPhase > 3.0f)
			m_fAnimPhase -= 3.0f;
	}
}

void CIDragon::render() {
	if (!m_bActive) { //draw just if nobody has it!
		m_pSpriteBody->SetPos(CVec(getRect()));
		m_pSpriteBody->Render();
	} else {
		m_pSpriteBody->SetPos(CVec(getRect()));
		m_pSpriteBody->Render(getOwner()->getWormID());
		m_pSpriteWings->SetPos(CVec(getRect()));
		m_pSpriteWings->Render(m_fAnimPhase, getOwner()->getOrientation(), getOwner()->getWormID());
	}
}

void CIDragon::onSetOwner(CWorm * pNewOwner) {
	m_bActive = (pNewOwner != NULL);
	setCanMove(pNewOwner == NULL);//so itemICon wil be physical object!
	g_pLogfile->Textout("dragon changed  owner!");
}

void CIDragon::use() {
	//TODO: fill it!
}
