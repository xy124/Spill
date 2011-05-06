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

class CAA_Laser: public CAttackAnimation {
private:
	int m_rValue;
	int m_gValue;
	int m_bValue;

	CVec m_From;
	CVec m_To;

public:
	void init(float liveTime, CVec &from, CVec &to, int r, int g, int b);
	//HINT: its kind of senseless that also lasers are physical objects...




	virtual ~CAA_Laser();
};

#endif /* CAA_LASER_H_ */
