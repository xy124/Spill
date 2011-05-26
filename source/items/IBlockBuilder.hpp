/*
 * IBlockBuilder.hpp
 *
 *  Created on: 21.05.2011
 *      Author: Sebastian
 */

#ifndef IBLOCKBUILDER_HPP_
#define IBLOCKBUILDER_HPP_

#include "Item.hpp"
#include "../Block.hpp"

class CGame;

class CIBlockBuilder: public CItem {
private:
	CGame * m_pGame;
	CBlock::BlockType m_BlockType;
public:
	void init(CBlock::BlockType BT, CGame * pGame);
	void use();
	CIBlockBuilder();
	virtual ~CIBlockBuilder();

	void onRenderIcon(int x, int y);
};

#endif /* IBLOCKBUILDER_HPP_ */
