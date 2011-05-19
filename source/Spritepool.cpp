/*
 * Spritepool.cpp
 *
 *  Created on: 19.05.2011
 *      Author: Sebastian
 */

#include "Spritepool.hpp"
#include "Block.hpp"
#include "Logfile.hpp"
#include "consts.hpp"

#include "AttackAnimations/CAA_Explosion1.hpp"
#include "AttackAnimations/CAA_Cloud.hpp"
#include "items/IFlag.hpp"
#include "items/IMoney.hpp"


using namespace std;

CSpritepool::CSpritepool() {
	//load all sprites in Heap!
	CSprite * pSprite;

//Cannonball
//0
	pSprite = new CSprite();
	pSprite->Load(_DIRDATA_+"/CannonBall.bmp");
	CAA_CannonBall::setSprite(pSprite);
	m_pSprites.push_back(pSprite);
	pSprite = NULL;

//Explosion
//1
	pSprite = new CSprite();
	pSprite->Load(_DIRDATA_+"/Explosion1.bmp", 6, 30, 30);
	CAA_Explosion1::setSprite(pSprite);
	m_pSprites.push_back(pSprite);
	pSprite = NULL;

//Cloud
//2
	pSprite = new CSprite();
	pSprite->Load(_DIRDATA_+"/cloudfinal.bmp", true);
	CAA_Cloud::setSprite(pSprite);
	m_pSprites.push_back(pSprite);
	pSprite = NULL;


	CTexture * pTexture;
	pTexture = new CTexture();
	pTexture->Load(_DIRDATA_+"/lightening.bmp");
	CAA_Cloud::setTextureSprite(pTexture);
	//TODO: pTexture isn't freed at the end!
	pTexture = NULL;

//Flag:
//3
	pSprite = new CSprite();
	pSprite->Load(_DIRDATA_+"/Flag.bmp", true);
	CIFlag::setSprite(pSprite);
	m_pSprites.push_back(pSprite);
	pSprite = NULL;
//4
	pSprite = new CSprite();
	pSprite->Load(_DIRDATA_+"/IconFlag.bmp", true, false);
	CIFlag::setIcon(pSprite);//MBE: static für jedes vererbete neue static??? ich hoffe doch mal!
	m_pSprites.push_back(pSprite);
	pSprite = NULL;

//DummyIcon:
//5
	pSprite = new CSprite();
	pSprite->Load(_DIRDATA_+"/EmptyItemSlot.bmp", true, false);
	CGame::setDummyItemIcon(pSprite);
	m_pSprites.push_back(pSprite);
	pSprite = NULL;

//Money
//6
	pSprite = new CSprite();
	pSprite->Load(_DIRDATA_+"/IconMoney.bmp", true, false);
	CIMoney::setIcon(pSprite);
	m_pSprites.push_back(pSprite);
	pSprite = NULL;
//7
	pSprite = new CSprite();
	pSprite->Load(_DIRDATA_+"/Money.bmp", true);
	CIMoney::setSprite(pSprite);
	m_pSprites.push_back(pSprite);
	pSprite = NULL;

//Blocksprites:
	CBlock::m_pBlockSprites[0] = new CSprite(_DIRDATA_+"/BlockAir.bmp");
	CBlock::m_pBlockSprites[1] = new CSprite(_DIRDATA_+"/BlockNormal.bmp");
	CBlock::m_pBlockSprites[2] = new CSprite(_DIRDATA_+"/BlockShooting.bmp");
	CBlock::m_pBlockSprites[3] = new CSprite(_DIRDATA_+"/BlockJumpboard.bmp");
	CBlock::m_pBlockSprites[4] = new CSprite(_DIRDATA_+"/BlockInvisible.bmp");
	CBlock::m_pBlockSprites[5] = new CSprite(_DIRDATA_+"/BlockCannon.bmp");
	CBlock::m_pBlockSprites[6] = new CSprite(_DIRDATA_+"/BlockCloudGen.bmp");
	for (int i = 0; i < BLOCKAMOUNT; i++) {//push them into the vector!
		m_pSprites.push_back(CBlock::m_pBlockSprites[i]);
	}
	g_pLogfile->Textout("<br />Successful loaded Sprites!");

//Worms:
//8
	//HINT: Important that worms are the last because they take their animation from back!
	pSprite = new CSprite();
	pSprite->Load(_DIRDATA_+"/christmaswormjustwalk.bmp", 3 , 25, 18);
	//Worm picks it out in itself!
	m_pSprites.push_back(pSprite);
	pSprite = NULL;
}

CSpritepool::~CSpritepool() {
	vector<CSprite*>::iterator it;
	for (it = m_pSprites.begin(); it != m_pSprites.end(); ++it) {
		delete ((*it));
	}
}

CSprite* CSpritepool::at(int i) {
	return m_pSprites.at(i);
}

CSprite* CSpritepool::last() {
	return m_pSprites.back();
}
