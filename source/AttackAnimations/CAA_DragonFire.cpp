/*
 * CAA_DragonFire.cpp
 *
 *  Created on: 26.05.2011
 *      Author: Sebastian
 */

#include "CAA_DragonFire.hpp"
#include "../Game.hpp"
#include "../Spritepool.hpp"

CAA_DragonFire::CAA_DragonFire() {
	// TODO Auto-generated constructor stub

}

CAA_DragonFire::~CAA_DragonFire() {
	// TODO Auto-generated destructor stub
}

void CAA_DragonFire::init(FloatRect dragonRect, bool bOrientation, CGame * pGame, int WormID, int TeamID) {
	m_pGame = pGame;
	m_WormID = WormID;
	m_TeamID = TeamID;
	m_bOrientation = bOrientation;
	m_pSprite = g_pSpritepool->at(SPRITEID::DRAGONFIRE);
	FloatRect FR;
	CVec dir(0.0f,0.0f);
	setIsSolid(true);
	setCanMove(true);
	FR = m_pSprite->GetRect();
	if (m_bOrientation == OLEFT) {
		FR.x = dragonRect.x;
		dir.x = -100.0f;
	} else {
		FR.x = dragonRect.x+dragonRect.w-FR.w;
		dir.x = 100.0f;
	}
	setDir(dir);
	setRect(FR);
	setHasGravity(false);

	initKillTime(1.5f);
}

void CAA_DragonFire::render() {
	m_pSprite->SetPos(CVec(getRect()));
	m_pSprite->Render(m_TeamID);
}

void CAA_DragonFire::update() {
	if (getLastCollisionX().bIsCollision) {
		CBlockKoord blockKoord;
		CVec vec = CVec(getRect().x-(m_bOrientation == OLEFT ? -75 : 0), getRect().y + 38.0f);
		blockKoord = vec.toBlockKoord();
		m_pGame->BuildBlock(blockKoord, CBlock::AIR, m_WormID, m_TeamID);
		//Fixme: better collisiontest!



	}

}
