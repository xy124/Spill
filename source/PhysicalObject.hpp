/*
 * PhysicalObject.hpp
 *
 *  Created on: 17.04.2011
 *      Author: Sebastian
 */

#ifndef PHYSICALOBJECT_HPP_
#define PHYSICALOBJECT_HPP_
#include "Vec.hpp"
#include "FloatRect.hpp"

class CPhysicalObject { //HINT: diese klasse nicht instanzieren!!!!!! nur vererben!!!
	//HINT: Blocks sind keine PhysicalObjects!!!!!
	private:
		FloatRect m_rect;
		bool m_bCanMove; //z.B. für Blocks false
		bool m_bIsSolid; //z.B. für Blocks wäre true, für wörmer aber z.B. false. zwei IsSolid=false objecte können durcheinander gehen.
		bool m_bCanJump; // nur wenn auf dem Boden ist!
		CVec m_dir; //direction, MovingVector per second!!!
	public: //HINT: wir machen das jez mal übern Stack... wat solls
		CPhysicalObject() {};
		virtual ~CPhysicalObject() {};

		bool getCanMove() const;
		CVec getDir() const;
		bool getIsSolid() const;
		FloatRect getRect();
		bool getCanJump() const;
		void setCanMove(bool bCanMove);
		void setDir(CVec dir);
		void setIsSolid(bool bIsSolid);
		void setRect(FloatRect rect);
		void setCanJump(bool bCanJump);
};






#endif /* PHYSICALOBJECT_HPP_ */
