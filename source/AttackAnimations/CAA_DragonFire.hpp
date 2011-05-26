/*
 * CAA_DragonFire.hpp
 *
 *  Created on: 26.05.2011
 *      Author: Sebastian
 */

#ifndef CAA_DRAGONFIRE_HPP_
#define CAA_DRAGONFIRE_HPP_

#include "AttackAnimation.hpp"
#include "../Sprite.hpp"

class CGame;


class CAA_DragonFire: public CAttackAnimation {
private:
	CGame * m_pGame;
	CSprite * m_pSprite;
	bool m_bOrientation;
	int m_TeamID, m_WormID;

public:
	CAA_DragonFire();
	virtual ~CAA_DragonFire();

	void init(FloatRect dragonRect, bool bOrientation, CGame * pGame, int WormID, int TeamID);
	void update();
	void render();
};

#endif /* CAA_DRAGONFIRE_HPP_ */
