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
#include <vector>

#define SPRITE_MONEY 7
#define SPRITE_ICONMONEY 6
#define SPRITE_DUMMYICON 5
#define SPRITE_ICONFLAG 4
#define SPRITE_FLAG 3
#define SPRITE_CLOUD 2
#define SPRITE_EXPLOSION 1
#define SPRITE_CANNONBALL 0
#define SPRITE_WORM 8
#define SPRITE_INVI 9
#define SPRITE_ICONINVI 10


class CSpritepool : public TSingleton<CSpritepool>  {
private:
	std::vector<CSprite*> m_pSprites;
public:
	CSpritepool();
	~CSpritepool();
	CSprite* at(int i);
	CSprite* last();
};

#define g_pSpritepool CSpritepool::get()


#endif /* SPRITEPOOL_HPP_ */
