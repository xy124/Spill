#ifndef _BLOCK_HPP
#define _BLOCK_HPP

#include "Sprite.hpp"
#include "BlockKoord.hpp"
#include "Vec.hpp"
#include "consts.hpp"
#include <string>

class CBlock { //I don't want to vererben the
	//Different kinds of blocks:
	public:
		enum BlockType {
					AIR,
					NORMAL,
					SHOOTING,
					JUMPBOARD,
					INVISIBLE
		};
		static BlockType nextBlockType(BlockType now);
		static std::string BlockTypeString(BlockType bt);


		CBlock() {}; //MBE
		CBlock(BlockType BT);
		~CBlock() {};

		void render(CBlockKoord &MyBlockPos);

		//Getters and Setters:
		int getTeamID() {return m_TeamID;};
		void setTeamID(int TeamID) {m_TeamID = TeamID;};

		int getBuilderID() {return m_BuilderID;};
		void setBuilderID(int BuilderID) {m_BuilderID = BuilderID;};

		BlockType getBlockType() {return m_BlockType;};
		void setBlockType(BlockType BlockType) {m_BlockType = BlockType;};

		static const int BlockCosts[5]; //The index is a Blocktype!
		static const float BlockBouncingX[5];
		static const float BlockBouncingY[5];

		static const int BlockSize = BLOCKSIZE;
		static CSprite * m_pBlockSprites[5];
		static void InitBlockSprites();
		static void FreeBlockSprites();
	private:
			BlockType m_BlockType;
			int m_TeamID;
			int m_BuilderID;
};

#endif
