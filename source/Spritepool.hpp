/*
 * Spritepool.hpp
 *
 *  Created on: 19.05.2011
 *      Author: Sebastian
 */

#ifndef SPRITEPOOL_HPP_
#define SPRITEPOOL_HPP_


#include "Singleton.hpp"
#include "Sprite.hpp"
#include <map>

namespace SPRITEID {
	enum S {
		MONEY=7,
		ICONMONEY=6,
		DUMMYICON=5,
		ICONFLAG=4,
		FLAG=3,
		CLOUD=2,
		EXPLOSION=1,
		CANNONBALL=0,
		WORM=8,
		INVI=9,
		ICONINVI=10,
		ITEMBARFRONT=11,
		ITEMBARBACK=12
	};
}



class CSpritepool : public TSingleton<CSpritepool>  {
private:
	std::map<int, CSprite*> m_pSprites;
public:
	CSpritepool();
	~CSpritepool();
	CSprite* at(SPRITEID::S i);
};

#define g_pSpritepool CSpritepool::get()


#endif /* SPRITEPOOL_HPP_ */
