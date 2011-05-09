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
#include "Collision.hpp"
#include "Singleton.hpp"
#include <SDL.h>

#define g_pPhysics CPhysics::get()

#include "Worm.hpp"

class CGame;

class CPhysics : public TSingleton<CPhysics>
{

	private:
		CGame* m_pGame;

		static const float Gravity = GRAVITY;			//Makes objects fall down
		static const float Friction = FRICTION; //Reibung
		S_Collision getCollision(const FloatRect &FR);//MBE eigentlich const was....
		CBlock::BlockType getBlockType(CVec &vec);

		static float Abs(float f) {
			return (f>=0 ? f : -f);
		}

	public:
		bool rectCollision(const FloatRect &FR1, const FloatRect &FR2);
		void init(CGame * game);
		bool doPhysics(); //changes X, Y, of Worms and other objects!, when no collision

		bool isEmpty(CBlockKoord &bc);

};
#endif
