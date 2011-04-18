#include "Block.hpp"


const int CBlock::BlockCosts[5] = {0, 5, 10, 10, 10}; //TODO!!!
void CBlock::InitBlockSprites() {
	CBlock::m_pBlockSprites[5] = { //darf nciht const sein da ja ->render und so davon aufgerufen wird!
			new CSprite("BlockAir.bmp"),
			new CSprite("BlockNormal.bmp"),
			new CSprite("BlockShooting.bmp"),
			new CSprite("BlockJumpboard.bmp"),
			new CSprite("BlockInvisible.bmp")
	};
}

CBlock::CBlock(BlockType BT) {
	m_BlockType = BT;
}

void CBlock::render(CBlockKoord &BlockPos) {
	CVec vec(BlockPos);
	CBlock::m_pBlockSprites[this->m_BlockType]->SetPos(vec);
	CBlock::m_pBlockSprites[this->m_BlockType]->Render();
}
