/*
 * Collision.hpp
 *
 *  Created on: 21.04.2011
 *      Author: Sebastian
 */

#ifndef COLLISION_HPP_
#define COLLISION_HPP_

#include "Block.hpp"

struct S_Collision {
	bool bIsCollision;
	CBlock::BlockType BlockType; //the one with the Biggest Index.

	float fBouncingFactorX; //the biggest bouncing factor is taken here!
	float fBouncingFactorY;
};


#endif /* COLLISION_HPP_ */
