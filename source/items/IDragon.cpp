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
	m_fFireAnimPhase = 0.0f;
	this->CItem::init();
	setIsSolid(true);
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

		worm.x = dragon.x + 87;
		worm.y = dragon.y;

		getOwner()->setRect(worm);

		m_fAnimPhase += 10.0f * g_pTimer->getElapsed();
		if (m_fAnimPhase > 3.0f)
			m_fAnimPhase -= 6.0f;

		ProcessMovingKeys();

		if (m_fFireAnimPhase > 0.0f) {//salve wurde abgefeuert!
			m_fFireAnimPhase += m_fAnimPhase += 10.0f * g_pTimer->getElapsed();

			if (m_fFireAnimPhase > 90.0f) {
				//TODO: destroy blocks, delete fire

			}
		}
	}
}

void CIDragon::render() {
	if (!m_bActive) { //draw just if nobody has it!
		m_pSpriteBody->SetPos(CVec(getRect()));
		m_pSpriteBody->Render();
	} else {
		m_pSpriteBody->SetPos(CVec(getRect()));
		m_pSpriteBody->Render(0.0f, getOwner()->getOrientation(), getOwner()->getWormID());
		m_pSpriteWings->SetPos(CVec(getRect()));
		m_pSpriteWings->Render( (m_fAnimPhase < 0 ? -m_fAnimPhase : m_fAnimPhase) //MBE use real ABS-Func!
				, getOwner()->getOrientation(), getOwner()->getWormID());
	}
}

void CIDragon::onSetOwner(CWorm * pNewOwner) {
	m_bActive = (pNewOwner != NULL);
	if (getOwner() != NULL) //alter owner kann scih bewegen!
		getOwner()->setCanMove(true);
	if (pNewOwner != NULL)
		pNewOwner->setCanMove(false);
	g_pLogfile->Textout("dragon changed  owner!");
}

void CIDragon::use() {
	//pay attention on Orientation
	//TODO: cooldown!

}

void CIDragon::ProcessMovingKeys() {
	CVec newDir = getDir();
	S_WormSettings settings;
	settings = (g_pSettings->s.WormSet[getOwner()->getWormID()]);//TODO senseless to handle it with pointer!

	//Jumping = Flying
	if (g_pFramework->KeyDown(settings.KeyJump)) { //Jump!
		newDir.y = DRAGONJUMPSPEED_Y;
	}

	//Left or Right!!
	if (g_pFramework->KeyDown(settings.KeyLeft) == true) {
		newDir.x += -DRAGONACCELERATION; //FIXME: USE DRAGON-Consts
		if (newDir.x < -DRAGONMAXSPEED_X) newDir.x = -DRAGONMAXSPEED_X;
	} else if (g_pFramework->KeyDown(settings.KeyRight) == true ) {
		newDir.x += +DRAGONACCELERATION;
		if (newDir.x > DRAGONMAXSPEED_X) newDir.x = DRAGONMAXSPEED_X;
	}

	setDir(newDir);
}
