/*
 * CAA_CannonBall.hpp
 *
 *  Created on: 06.05.2011
 *      Author: Sebastian
 */

#ifndef CAA_CANNONBALL_H_
#define CAA_CANNONBALL_H_

#include "AttackAnimation.hpp"
#include "../Sprite.hpp"
#include "../Worm.hpp"
#include <list>

class CWorm;

class CAA_CannonBall: public CAttackAnimation {
private:
	static CSprite * m_pSprite;
	int m_TeamID;
	CWorm * m_pAimWorm;
	CWorm * m_pOwnerWorm;

	std::list<CAttackAnimation*> * m_pAttackAnimations;
public:


	virtual void render();
	virtual void quit();
	virtual void init(CVec StartPos, CWorm * pAimWorm, CWorm * pOwnerWorm, int TeamID,
			std::list<CAttackAnimation*> * pAttackAnimations);
	virtual void update();

	~CAA_CannonBall() {};

	static void setSprite(CSprite * pSprite);

};

#endif /* CAA_CANNONBALL_H_ */
