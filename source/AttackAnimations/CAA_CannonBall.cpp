/*
 * CAA_CannonBall.cpp
 *
 *  Created on: 06.05.2011
 *      Author: Sebastian
 */

#include "CAA_CannonBall.hpp"


void CAA_CannonBall::setSprite(CSprite * pSprite) {
	CAA_CannonBall::m_pSprite = pSprite;
}

void CAA_CannonBall::render() {
	m_pSprite->SetPos(CVec(getRect()));
	m_pSprite->Render(m_TeamID);
}

void CAA_CannonBall::update() {
	CVec BallPos(getRect());
	CVec dir;
	dir = CVec(m_pAimWorm->getRect());
	dir -= BallPos;
	dir = dir / 10.0f;
	BallPos += dir;
	SDL_Rect r;
	r.x = BallPos.x;
	r.y = BallPos.y;

	//FIXME use as physical object!
}

void CAA_CannonBall::quit() {
//nothing
}

void CAA_CannonBall::init(CVec StartPos, CWorm * pAimWorm, int TeamID) {
	initKillTime(3.0f);
	SDL_Rect r = StartPos.toSDlRect;
	m_TeamID = TeamID;
}
