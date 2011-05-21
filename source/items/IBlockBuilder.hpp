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

class CIBlockBuilder: public CItem {
public:
	void init(CBlock::BlockType);
	CIBlockBuilder();
	virtual ~CIBlockBuilder();
};

#endif /* IBLOCKBUILDER_HPP_ */
