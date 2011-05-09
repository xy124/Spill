/*
 * CAA_Explosion1.cpp
 *
 *  Created on: 09.05.2011
 *      Author: Sebastian
 */

#include "CAA_Explosion1.hpp"
#include "../Timer.hpp"



CSprite * CAA_Explosion1::m_pSprite;

void CAA_Explosion1::init(CWorm * pAimedWorm) {
	initKillTime(1.5f);
	m_fAnimPhase = 0.0f;
	m_pAimedWorm = pAimedWorm;
	setCanMove(false);
	setIsSolid(false);
}

void CAA_Explosion1::render() {
	m_pSprite->Render(m_fAnimPhase, false, 1);
}
void CAA_Explosion1::update() {
	m_fAnimPhase += 10.0f*g_pTimer->getElapsed();
	if (m_fAnimPhase >= 6.0f)
		m_fAnimPhase -= 6.0f;
	m_pSprite->SetPos(m_pAimedWorm->getRect().x,m_pAimedWorm->getRect().y);
}
