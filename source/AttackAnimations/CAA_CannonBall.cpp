/*
 * CAA_CannonBall.cpp
 *
 *  Created on: 06.05.2011
 *      Author: Sebastian
 */

#include "CAA_CannonBall.hpp"
#include "../Logfile.hpp"
#include "../Physics.hpp"

CSprite * CAA_CannonBall::m_pSprite;

void CAA_CannonBall::setSprite(CSprite * pSprite) {
	CAA_CannonBall::m_pSprite = pSprite;
}

void CAA_CannonBall::render() {
	m_pSprite->SetPos(CVec(getRect()));
	m_pSprite->Render(m_TeamID);
}

void CAA_CannonBall::update() {
	FloatRect r = getRect();
	CVec BallPos(r);
	CVec dir;
	dir = CVec(m_pAimWorm->getRect());
	dir -= BallPos;
	dir = dir / 10.0f;

	BallPos += dir;


	r = BallPos.toFloatRect(r);
	setRect(r);

	if (g_pPhysics->rectCollision(m_pAimWorm->getRect(), r)) {
		//wurm abziehen, Cannonbal zerstören
		float E = m_pAimWorm->getEnergy();
		E -= 40.0f;
		m_pAimWorm->setEnergy(E);
		this->setDead();
	}

	//FIXME use as physical object!
}

void CAA_CannonBall::quit() {
//nothing
}

void CAA_CannonBall::init(CVec StartPos, CWorm * pAimWorm, int TeamID) {
	initKillTime(5.0f);
	FloatRect fr = StartPos.toFloatRect();
	fr.w = m_pSprite->GetRect().w;
	fr.w = m_pSprite->GetRect().h;
	setRect(fr);
	m_TeamID = TeamID;
	m_pAimWorm = pAimWorm;
	setIsSolid(true);
	setCanMove(true);

}
