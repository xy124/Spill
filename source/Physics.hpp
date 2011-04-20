//pragma once hei�t deklariere einmal
#ifndef _PHYSICS_HPP_
#define _PHYSICS_HPP_

#include <vector>
#include <map>
#include "Game.hpp"
#include "Timer.hpp"
#include "FloatRect.hpp"
#include "Vec.hpp"
#include "BlockKoord.hpp"
#include "Block.hpp"


#include "Worm.hpp"

class CGame;

class CPhysics
{
	private:
		static const float Gravity;			//Makes objects fall down
		static const float BouncingFactor;	//Makes objects colliding with other ones to slow down on bouncing
		static bool isCollission(const FloatRect &FR, CGame * Game);//MBE eigentlich const was....
		static CBlock::BlockType getBlockType(CVec vec, CGame * Game);
		static bool rectCollission(const FloatRect &FR1, const FloatRect &FR2);
	public:

		static bool doPhysics(CGame * Game); //changes X, Y, of Worms and other objects!, when no collission
};
//TODO evtl alle von doPhysics bearbeiteten objekte als physical object definieren
#endif
