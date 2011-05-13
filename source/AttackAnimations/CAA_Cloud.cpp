/*
 * CAA_Cloud.cpp
 *
 *  Created on: 06.05.2011
 *      Author: Sebastian
 */

#include "CAA_Cloud.hpp"
#include "../Logfile.hpp"
#include "../Physics.hpp"

#include "../SDLgfx/SDL_gfxPrimitives.h"


CSprite * CAA_Cloud::m_pSprite;

using namespace std;

void CAA_Cloud::setSprite(CSprite * pSprite) {
	CAA_Cloud::m_pSprite = pSprite;
}

void CAA_Cloud::render() {
	m_pSprite->SetPos(CVec(getRect()));
	m_pSprite->Render();
	//Draw Lightening
	fil


}


void CAA_Cloud::update() {
	FloatRect r = getRect();
	r.x = m_pAimWorm->getRect().x-50.0f;

}

void CAA_Cloud::quit() {
	m_pAimWorm = NULL;//actually senseless!
}

void CAA_Cloud::init(CVec StartPos, CWorm * pAimWorm, CWorm * pOwnerWorm, int TeamID,
	list<CAttackAnimation*> * pAttackAnimations) {
	initKillTime(5.0f);
	FloatRect fr = StartPos.toFloatRect();
	fr.w = m_pSprite->GetRect().w;
	fr.h = m_pSprite->GetRect().h;
	fr.y = 0; //Clouds are on Heaven!
	setRect(fr);
	m_TeamID = TeamID;
	m_pAimWorm = pAimWorm;
	m_pOwnerWorm = pOwnerWorm;

	//don't do physics on that!
	setIsSolid(false);
	setCanMove(false);

	m_pAttackAnimations = pAttackAnimations;
}
