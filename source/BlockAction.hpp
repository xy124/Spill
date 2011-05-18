/*
 * BlockAction.hpp
 *
 *  Created on: 18.05.2011
 *      Author: Sebastian
 */

#ifndef BLOCKACTION_HPP_
#define BLOCKACTION_HPP_

#include "Block.hpp"
#include "BlockKoord.hpp"
#include "Game.hpp"
#include "Worm.hpp"

class CGame;

class CBlockAction {
public:
	static void action(CGame * pGame, CWorm * pOwner);
};

#endif /* BLOCKACTION_HPP_ */
