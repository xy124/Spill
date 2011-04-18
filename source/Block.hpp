#ifndef _BLOCK_HPP
#define _BLOCK_HPP

#include "Sprite.hpp"
#include "PhysicalObject.hpp"
#include "BlockKoord.hpp"

class CBlockKoord;

class CSprite;

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

		CBlock() {}; //TODO: fill it
		CBlock(BlockType BT);
		~CBlock() {};

		void render(CBlockKoord &BlockPos);

		//Getters and Setters:
		int getTeamID() {return m_TeamID;};
		void setTeamID(int TeamID) {m_TeamID = TeamID;};

		int getBuilderID() {return m_BuilderID;};
		void setBuilderID(int BuilderID) {m_BuilderID = BuilderID;};

		BlockType getBlockType() {return m_BlockType;};
		void setBlockType(BlockType BlockType) {m_BlockType = BlockType;};

		static const int BlockCosts[5]; //The index is a Blocktype!
		static const int BlockSize;
		static const CSprite * m_pBlockSprites[5];//TODO hoffe das geht
	private:
			BlockType m_BlockType;
			int m_TeamID;
			int m_BuilderID;
};

#endif
