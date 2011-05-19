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
