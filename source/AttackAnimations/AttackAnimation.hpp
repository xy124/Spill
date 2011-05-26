/*
 * AttackAnimation.hpp
 *
 *  Created on: 06.05.2011
 *      Author: Sebastian
 */

#ifndef ATTACKANIMATION_HPP_
#define ATTACKANIMATION_HPP_

#include "../PhysicalObject.hpp"
#include "../Logfile.hpp"

class CAttackAnimation : public CPhysicalObject {
private:
	float m_fKillTime;//when to destroy it
protected:
	void initKillTime(float liveTime);//HINT: make sure that all subclasses call this!
public:
	void setDead();

	bool isAlive();

	virtual void render() {
		g_pLogfile->Textout("rendered Attackanimation");
	};
	virtual void update() {};
	virtual void quit() {};

	virtual ~CAttackAnimation() {};
};

#endif /* ATTACKANIMATION_HPP_ */
