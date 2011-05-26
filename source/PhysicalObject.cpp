/*
 * PhysicalObject.cpp
 *
 *  Created on: 17.04.2011
 *      Author: Sebastian
 */

#include "PhysicalObject.hpp"

bool CPhysicalObject::getCanMove() const
{
    return m_bCanMove;
}

CVec CPhysicalObject::getDir() const
{
    return m_dir;
}

bool CPhysicalObject::getIsSolid() const
{
    return m_bIsSolid;
}

FloatRect CPhysicalObject::getRect()
{
    return m_rect;
}

bool CPhysicalObject::getCanJump() const
{
	return m_bCanJump;
}

bool CPhysicalObject::getHasGravity() const
{
	return m_bHasGravity;
}



void CPhysicalObject::setCanMove(bool bCanMove)
{
    this->m_bCanMove = bCanMove;
}

void CPhysicalObject::setDir(CVec dir)//nicht per reference!!
{
    this->m_dir = dir;
}

void CPhysicalObject::setIsSolid(bool bIsSolid)
{
    this->m_bIsSolid = bIsSolid;
}

void CPhysicalObject::setRect(FloatRect &rect)
{
    this->m_rect = rect;
}

void CPhysicalObject::setCanJump(bool bCanJump) 
{
	m_bCanJump = bCanJump;
}

void CPhysicalObject::setHasGravity(bool bHasGravity)
{
	m_bHasGravity = bHasGravity;
}

S_Collision CPhysicalObject::getLastCollisionY()
{
    return m_lastCollisionY;
}

void CPhysicalObject::setLastCollisionY(S_Collision &m_lastCollisionY)
{
    this->m_lastCollisionY = m_lastCollisionY;
}

S_Collision CPhysicalObject::getLastCollisionX()
{
    return m_lastCollisionX;
}

void CPhysicalObject::setLastCollisionX(S_Collision &m_lastCollisionX)
{
    this->m_lastCollisionX = m_lastCollisionX;
}



