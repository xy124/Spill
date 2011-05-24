#include "Block.hpp"


const int CBlock::BlockCosts[BLOCKAMOUNT]    	= BLOCKCOSTS;//TODO
const float CBlock::BlockBouncingX[BLOCKAMOUNT] = BLOCKBOUNCING_X;
const float CBlock::BlockBouncingY[BLOCKAMOUNT] = BLOCKBOUNCING_Y;
CSprite * CBlock::m_pBlockSprites[BLOCKAMOUNT];

//DECLARATION: static CSprite * m_pBlockSprites[5];

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
		CBlock::m_pBlockSprites[this->m_BlockType]->Render(this->m_TeamID+1);
	}
}


std::string CBlock::getBlockTypeString(CBlock::BlockType bt) {
	std::string s;
	switch (bt) {
		case (CBlock::AIR): 		s="AIR"; 		break;
		case (CBlock::INVISIBLE): 	s="INVISIBLE"; 	break;
		case (CBlock::JUMPBOARD): 	s="JUMPBOARD"; 	break;
		case (CBlock::NORMAL): 		s="NORMAL"; 	break;
		case (CBlock::SHOOTING): 	s="SHOOTING";	break;
		case (CBlock::CANNON): 		s="CANNON";		break;
		case (CBlock::CLOUDGEN):	s="CLOUDGEN";	break;
		default: 					s="None"; 		break;
	}
	return s;
}

CBlock::BlockType CBlock::nextBlockType(CBlock::BlockType &at) {
	CBlock::BlockType s;
	s = BlockType((at+1)%BLOCKAMOUNT);
	return s;
}
