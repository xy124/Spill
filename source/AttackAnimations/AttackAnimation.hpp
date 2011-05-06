/*
 * AttackAnimation.hpp
 *
 *  Created on: 06.05.2011
 *      Author: Sebastian
 */

#ifndef ATTACKANIMATION_HPP_
#define ATTACKANIMATION_HPP_

#include "../PhysicalObject.hpp"

class CAttackAnimation : public CPhysicalObject {
private:
	float m_fKillTime;//when to destroy it
public:
	void initKillTime(float liveTime);//HINT: make sure that all subclasses call this!

	bool isAlive();

	virtual void render() {};
	virtual void quit() {};

	virtual ~CAttackAnimation() {};
};

#endif /* ATTACKANIMATION_HPP_ */
