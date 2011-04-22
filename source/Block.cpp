#include "Block.hpp"


const int CBlock::BlockCosts[5]     = BLOCKCOSTS;//TODO
const float CBlock::BlockBouncingX[5] = BLOCKBOUNCING_X;
const float CBlock::BlockBouncingY[5] = BLOCKBOUNCING_Y;
CSprite * CBlock::m_pBlockSprites[5];

//DECLARATION: static CSprite * m_pBlockSprites[5];
void CBlock::InitBlockSprites() {
	//CBlock::m_pBlockSprites[5] = { //darf nciht const sein da ja ->render und so davon aufgerufen wird!
	m_pBlockSprites[0] = new CSprite(_DIRDATA_+"/BlockAir.bmp");
	m_pBlockSprites[1] = new CSprite(_DIRDATA_+"/BlockNormal.bmp");
	m_pBlockSprites[2] = new CSprite(_DIRDATA_+"/BlockShooting.bmp");
	m_pBlockSprites[3] = new CSprite(_DIRDATA_+"/BlockJumpboard.bmp");
	m_pBlockSprites[4] = new CSprite(_DIRDATA_+"/BlockInvisible.bmp");
}

void CBlock::FreeBlockSprites() {
	for (int i=0; i<5; i++) {
		if (m_pBlockSprites[i] != NULL) {
			delete (m_pBlockSprites[i]);
			m_pBlockSprites[i] = NULL;
		}
	}
}

CBlock::CBlock(BlockType BT) {
	m_BlockType = BT;
}

void CBlock::render(CBlockKoord &MyBlockPos) {
	CVec vec(MyBlockPos);
	if (this->m_BlockType != CBlock::AIR) {
		CBlock::m_pBlockSprites[this->m_BlockType]->SetPos(vec);
		CBlock::m_pBlockSprites[this->m_BlockType]->Render();
	}
}
