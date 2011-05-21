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
		MONEY = 0,
		ICONMONEY,
		DUMMYICON,
		ICONFLAG,
		FLAG,
		CLOUD,
		EXPLOSION,
		CANNONBALL,
		WORM,
		INVI,
		ICONINVI,
		ITEMBARFRONT,
		ITEMBARBACK,
		ICONWAND,
		ICONBLOCKBUILDER
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
