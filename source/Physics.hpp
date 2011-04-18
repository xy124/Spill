//pragma once heiﬂt deklariere einmal
#ifndef _PHYSICS_HPP_
#define _PHYSICS_HPP_

#include "Game.hpp"
#include "Timer.hpp"
#include "FloatRect.hpp"
#include "Vec.hpp"
#include "BlockKoord.hpp"
#include "Block.hpp"
#include <vector>
#include <map>

class CPhysics
{
	private:
		static const float Gravity;			//Makes objects fall down
		static const float BouncingFactor;	//Makes objects colliding with other ones to slow down on bouncing
		static bool isCollission(const FloatRect &FR, const Game * Game);
		static CBlock::BlockType getBlockType(const CVec &vec, const Game * Game);

	public:

		static bool doPhysics(const CGame * Game); //changes X, Y, of Worms and other objects!, when no collission
};
//TODO evtl alle von doPhysics bearbeiteten objekte als physical object definieren
#endif
