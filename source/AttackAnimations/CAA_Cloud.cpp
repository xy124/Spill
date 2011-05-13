/*
 * CAA_Cloud.cpp
 *
 *  Created on: 06.05.2011
 *      Author: Sebastian
 */

#include "CAA_Cloud.hpp"
#include "../Logfile.hpp"
#include "../Physics.hpp"
#include "../Framework.hpp"


CSprite * CAA_Cloud::m_pSprite;

using namespace std;

void CAA_Cloud::setSprite(CSprite * pSprite) {
	CAA_Cloud::m_pSprite = pSprite;
}

void CAA_Cloud::setTextureSprite(CSprite * pSprite) {
	CAA_Cloud::m_pTextureSprite = pSprite;
}

void CAA_Cloud::render() {
	CVec pos = CVec(getRect());
	m_pSprite->SetPos(pos);

	//Draw Lightening
	//if (m_fLighteningState > 3.0f) {//draw whole lightening
	if (true) {//TODO
		const int n = 7;
		Sint16 vx [n];
		Sint16 vy [n];
		//MBE cast pos...
		vx[0] = pos.x+70;
		vy[0] = 45;

		vx[1] = pos.x+75;
		vy[1] = 200;

		vx[2] = pos.x+100;
		vy[2] = 170;

		//Points on Aim!
		vx[3] = m_pAimWorm->getRect().x+10;
		vy[3] = m_pAimWorm->getRect().y+5;

		vx[4] = pos.x+60;
		vy[4] = 200;

		vx[5] = pos.x+40;
		vy[5] = 250;

		vx[6] = pos.x+50;//TODO = vx[0]
		vy[6] = 45;

		//als pointer übergeben???
		//arrays sind also immer zeiger auf den ersten wert... lustig
		g_pFramework->drawTexturedPolygon(vx, vy, 7, 255, 255, 0, m_pTextureSprite);
	}



	//render cloud over Polygon
	m_pSprite->Render();
}


void CAA_Cloud::update() {
	FloatRect r = getRect();
	r.x = m_pAimWorm->getRect().x-50.0f;

	m_fLighteningState += 1.0f * g_pTimer->getElapsed();

	setRect(r);

}

void CAA_Cloud::quit() {
	m_pAimWorm = NULL;//actually senseless!
}

void CAA_Cloud::init(CVec StartPos, CWorm * pAimWorm, CWorm * pOwnerWorm, int TeamID) {
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

	m_fLighteningState = 0.0f;
}
