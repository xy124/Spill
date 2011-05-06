/*
 * CAA_CannonBall.h
 *
 *  Created on: 06.05.2011
 *      Author: Sebastian
 */

#ifndef CAA_CANNONBALL_H_
#define CAA_CANNONBALL_H_

#include "AttackAnimation.hpp"

class CAA_CannonBall: public CAttackAnimation {
public:
	CAA_CannonBall();

	void render();
	void quit();
	void init();//FIXME: fill it!

	virtual ~CAA_CannonBall();
};

#endif /* CAA_CANNONBALL_H_ */
