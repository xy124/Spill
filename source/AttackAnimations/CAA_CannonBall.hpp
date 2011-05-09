/*
 * CAA_CannonBall.h
 *
 *  Created on: 06.05.2011
 *      Author: Sebastian
 */

#ifndef CAA_CANNONBALL_H_
#define CAA_CANNONBALL_H_

#include "AttackAnimation.hpp"
#include "../Sprite.hpp"
#include "../Worm.hpp"

class CWorm;

class CAA_CannonBall: public CAttackAnimation {
private:
	static CSprite * m_pSprite;
	int m_TeamID;
	CWorm * m_pAimWorm;
public:
	static void setSprite(CSprite * pSprite);

	virtual void render();
	virtual void quit();
	virtual void init(CVec StartPos, CWorm * pAimWorm, int TeamID);
	virtual void update();

	~CAA_CannonBall() {};

};

#endif /* CAA_CANNONBALL_H_ */
