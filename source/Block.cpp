#include "Block.hpp"


const int CBlock::BlockCosts[5] = {0, 5, 10, 10, 10}; //TODO!!!
const CSprite * CBlock::m_pBlockSprites[5] = {
		new CSprite("BlockAir.bmp"),
		new CSprite("BlockNormal.bmp"),
		new CSprite("BlockShooting.bmp"),
		new CSprite("BlockJumpboard.bmp"),
		new CSprite("BlockInvisible.bmp")
};//TODO in game ausgelagert aber ist das sinnvoll?
const int CBlock::BlockSize = 20;//Width and height of a block!

CBlock::CBlock(BlockType BT) {
	m_BlockType = BT;
}

void CBlock::render(CBlockKoord &BlockPos) {
	CVec vec(BlockPos);
	CBlock::m_pBlockSprites[this->m_BlockType]->SetPos(vec);
	CBlock::m_pBlockSprites[this->m_BlockType]->Render();
}
