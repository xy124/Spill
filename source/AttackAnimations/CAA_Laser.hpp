/*
 * CAA_Laser.h
 *
 *  Created on: 06.05.2011
 *      Author: Sebastian
 */

#ifndef CAA_LASER_H_
#define CAA_LASER_H_

#include "AttackAnimation.hpp"
#include "../Vec.hpp"
#include "../Worm.hpp"

class CWorm;

class CAA_Laser: public CAttackAnimation {
private:
	int m_rValue;
	int m_gValue;
	int m_bValue;

	CVec m_From;
	CWorm * m_pTo;

public:
	virtual void init(float liveTime, CVec &from, CWorm * pTo, int r, int g, int b);
	virtual void render();
	virtual void quit();
	~CAA_Laser() {};
	//HINT: its kind of senseless that also lasers are physical objects...




};

#endif /* CAA_LASER_H_ */
