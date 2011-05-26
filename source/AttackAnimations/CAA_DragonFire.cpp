/*
 * CAA_DragonFire.cpp
 *
 *  Created on: 26.05.2011
 *      Author: Sebastian
 */

#include "CAA_DragonFire.hpp"
#include "../Game.hpp"
#include "../Spritepool.hpp"

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
		dir.x = -500.0f;
	} else {
		FR.x = dragonRect.x+dragonRect.w-FR.w;
		dir.x = 500.0f;
	}
	FR.y = dragonRect.y;
	if (m_bOrientation == OLEFT)//Physical rect is smaller then sprite ;) --> looks better
		FR.y -= 20.0f;
	else
		FR.w -= 20.0f;
	setDir(dir);
	setRect(FR);
	setHasGravity(false);

	initKillTime(1.5f);
}

void CAA_DragonFire::render() {
	m_pSprite->SetPos(CVec(getRect()));
	m_pSprite->Render(0.0f, m_bOrientation, m_TeamID);
}

void CAA_DragonFire::update() {
	if (getLastCollisionX().bIsCollision) {
		CBlockKoord blockKoord;
		CVec vec = CVec(	getRect().x+(m_bOrientation == OLEFT ? -3.0f : getRect().w+3.0f),	//x
							getRect().y + 50.0f);												//y
		blockKoord = vec.toBlockKoord();
		CBlock * pOldBlock = m_pGame->getBlock(blockKoord);
		if ((pOldBlock != NULL) && (pOldBlock->getBlockType() != CBlock::AIR)) {
			m_pGame->BuildBlock(blockKoord, CBlock::AIR, m_WormID, m_TeamID);
		}

		//TODO: save map in xml...


	}

}
