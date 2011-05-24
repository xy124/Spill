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
					INVISIBLE,
					CANNON,
					CLOUDGEN
		};

		static std::string getBlockTypeString(BlockType bt);


		CBlock() {};
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

		static const int BlockCosts[BLOCKAMOUNT]; //The index is a Blocktype!
		static const float BlockBouncingX[BLOCKAMOUNT];
		static const float BlockBouncingY[BLOCKAMOUNT];

		static const int BlockSize = BLOCKSIZE;
		static CSprite * m_pBlockSprites[BLOCKAMOUNT];
		static void InitBlockSprites();
		static void FreeBlockSprites();
		static BlockType nextBlockType(CBlock::BlockType &at);
	private:
			BlockType m_BlockType;
			int m_TeamID;
			int m_BuilderID;
};


/* MBE: instead of nextBlockType. Infact: nextBlockType is'nt used! SyntaxError.... How to....???? then delete nextBlock!
//laut wiki geht so die enuminkrementierung:
//source: http://de.wikibooks.org/wiki/C++-Programmierung:_Aufz%C3%A4hlungen

//Prä-Inkrement
CBlock::BlockType& operator++(BlockType& w) {
		  return (w = BCBlock::lockType((w+1)%BLOCKAMOUNT));
}
// Post-Inkrement
CBlock::BlockType operator++(BlockType& w, int) {
	CBlock::BlockType alt = w;
	++w;
	return alt;
}

*/

#endif
