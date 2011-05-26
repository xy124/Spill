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
#include "Collision.hpp"

class CPhysicalObject { //HINT: diese klasse nicht instanzieren!!!!!! nur vererben!!!
	//HINT: Blocks sind keine PhysicalObjects!!!!!
	private:
		FloatRect m_rect;
		bool m_bCanMove; //z.B. f�r Blocks false
		bool m_bIsSolid; //z.B. f�r Blocks w�re true, f�r w�rmer aber z.B. false. zwei IsSolid=false objecte k�nnen durcheinander gehen.
		bool m_bCanJump; // nur wenn auf dem Boden ist!
		bool m_bHasGravity; //gravity let it fall down?
		CVec m_dir; //direction, MovingVector per second!!!

		S_Collision m_lastCollisionY;
		S_Collision m_lastCollisionX;
	public:
		CPhysicalObject() {
			m_bCanMove = false;
			m_bIsSolid = false;
			m_bCanJump = false;
			m_bHasGravity = true;
			m_dir = CVec(0.0f, 0.0f);
			m_lastCollisionY.bIsCollision = false;
			m_lastCollisionX.bIsCollision = false;
		};
		virtual ~CPhysicalObject() {};

		bool getCanMove() const;
		CVec getDir() const;
		bool getIsSolid() const;
		FloatRect getRect();//Todo not with stack!
		bool getCanJump() const;
		bool getHasGravity() const;
		void setCanMove(bool bCanMove);
		void setDir(CVec dir);
		void setIsSolid(bool bIsSolid);
		void setHasGravity(bool bHasGravity);
		void setRect(FloatRect &rect);
		void setCanJump(bool bCanJump);
		S_Collision getLastCollisionY();
		void setLastCollisionY(S_Collision &m_lastCollisionY);
		S_Collision getLastCollisionX();
		void setLastCollisionX(S_Collision &m_lastCollisionX);



};






#endif /* PHYSICALOBJECT_HPP_ */
