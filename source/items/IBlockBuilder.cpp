/*
 * IBlockBuilder.cpp
 *
 *  Created on: 21.05.2011
 *      Author: Sebastian
 */

#include "IBlockBuilder.hpp"
#include "../Game.hpp"
#include "../Physics.hpp"

CIBlockBuilder::CIBlockBuilder() {
	m_pGame = NULL;
}

CIBlockBuilder::~CIBlockBuilder() {
	// TODO Auto-generated destructor stub
}

void CIBlockBuilder::use() {
	//FIXME: errors with keylock???
	if (getOwner()->getMoney() >= CBlock::BlockCosts[m_BlockType]) {//player has enough money
		//get field next to worm
		CVec vec(getOwner()->getRect());
		if (getOwner()->getOrientation() == ORIGHT)
			vec.x += (getOwner()->getRect().w + BLOCKSIZE);//next block
		else
			vec.x -= BLOCKSIZE;

		CBlockKoord pos = vec.toBlockKoord();

		//is field free???
		CBlock* buildingBlock = m_pGame->getBlock(pos);
		if ( (buildingBlock != NULL)
				&& (buildingBlock->getBlockType() == CBlock::AIR)
				&& (g_pPhysics->isEmpty(pos)) ) {
			if (m_pGame->BuildBlock(pos, m_BlockType,
					getOwner()->getWormID(), getOwner()->getTeamID())) {
				getOwner()->changeMoneyBy(-CBlock::BlockCosts[m_BlockType]);
				getOwner()->changePointsBy(1);
				getOwner()->m_BuiltBlocks.push_back(pos);

				g_pLogfile->fTextout("</br >Built BLock: "+CBlock::getBlockTypeString(m_BlockType)+" Costs:%i", CBlock::BlockCosts[m_BlockType]);
			}
		}
	}
}

void CIBlockBuilder::init(CBlock::BlockType BT, CGame * pGame) {
	this->CItem::init();
	setDropable(false);
	m_pGame = pGame;
	m_BlockType = BT;
	setIcon(g_pSpritepool->at(SPRITEID::ICONBLOCKBUILDER));
	setName(CBlock::getBlockTypeString(BT));
}

void CIBlockBuilder::onRenderIcon(int x, int y) {
	//render block under buildingtool-Icon
	CBlock::m_pBlockSprites[m_BlockType]->SetPos(static_cast<float>(x),static_cast<float>(y));
	CBlock::m_pBlockSprites[m_BlockType]->Render(0);
}
