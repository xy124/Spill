/*
 * CAA_CannonBall.cpp
 *
 *  Created on: 06.05.2011
 *      Author: Sebastian
 */

#include "CAA_CannonBall.hpp"
#include "../Logfile.hpp"
#include "../Physics.hpp"
#include "CAA_Explosion1.hpp"


CSprite * CAA_CannonBall::m_pSprite;

using namespace std;

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
	dir = dir * 3.0f;
	setDir(dir);


	if (g_pPhysics->rectCollision(m_pAimWorm->getRect(), r)) {
		//wurm abziehen, Cannonbal zerstören
		m_pAimWorm->changeEnergyBy(-40.0f);
		m_pOwnerWorm->changePointsBy(40);
		m_pOwnerWorm->changeMoneyBy(1);
		this->setDead();
		//Make Explosion!! MBE: better with functionpointer????
		CAA_Explosion1 * pExplosion1;
		pExplosion1 = new CAA_Explosion1();
		pExplosion1->init(m_pAimWorm);
		m_pAttackAnimations->push_back(pExplosion1);
		pExplosion1 = NULL;

	}
}

void CAA_CannonBall::quit() {
	m_pAimWorm = NULL;//eigentlich senseless!
}

void CAA_CannonBall::init(CVec StartPos, CWorm * pAimWorm, CWorm * pOwnerWorm, int TeamID,
	list<CAttackAnimation*> * pAttackAnimations) {
	initKillTime(5.0f);
	FloatRect fr = StartPos.toFloatRect();
	fr.w = m_pSprite->GetRect().w;
	fr.h = m_pSprite->GetRect().h;
	fr.y -= (BLOCKSIZE+1.0f); //über der kanone starten!
	setRect(fr);
	m_TeamID = TeamID;
	m_pAimWorm = pAimWorm;
	m_pOwnerWorm = pOwnerWorm;
	setIsSolid(true);
	setCanMove(true);

	m_pAttackAnimations = pAttackAnimations;
}
