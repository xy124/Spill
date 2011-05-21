/*
 * IBlockActionWand.cpp
 *
 *  Created on: 21.05.2011
 *      Author: Sebastian
 */

#include "IBlockActionWand.hpp"

#include "../Timer.hpp"
#include "../Settings.hpp"
#include "../BlockAction.hpp"
#include "../Game.hpp"

#include <string>

using namespace std;


CIBlockActionWand::CIBlockActionWand() {
	m_pGame = NULL;
}

CIBlockActionWand::~CIBlockActionWand() {
	// TODO Auto-generated destructor stub
}

void CIBlockActionWand::init(CGame * pGame) {
	m_pGame = pGame;
	this->CItem::init();
	setDropable(false);
	m_fLastActionTime = 0.0f;
	setName("DoBlockaction with the blockactionWand");
	setIcon(g_pSpritepool->at(SPRITEID::ICONWAND));
}

void CIBlockActionWand::use() {
	bool canDoBlockAction = (g_pTimer->now()-m_fLastActionTime > LOADINGTIME);

	if (canDoBlockAction) {
		m_fLastActionTime = g_pTimer->now();
		CBlockAction::action(m_pGame, getOwner());
	}
}

void CIBlockActionWand::render() {//showCooldown
	string s;
	char buffer[1024];
	//MBE: as COOLDOWN for evgery item!
	int BlockEnergyState = static_cast<int>(100*(g_pTimer->now()-m_fLastActionTime)/LOADINGTIME);
	if (BlockEnergyState > 100) BlockEnergyState = 100;
	sprintf(buffer, "BlockEnergy: %i %%", BlockEnergyState);
	s = buffer;
	g_pFramework->TextOut(s, 0, 30, getOwner()->getViewPortID());
}
